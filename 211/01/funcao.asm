;ATENCAO, os numeros de entrada devem estar entre 2 e 65535
;o programa identifica como fim de arquivo, uma sequencia de 8 ou mais caracteres iguais
;as rotinas de abertura/leitura/escrita em arquivo foram copiadas do exemplo feito por Marcelo Reis.

;/****************************************************************
;*
;* Nome : Bruno Ferrero                             N.USP 3690142
;* Nome : Tiago Nicolosi Bomventi                   N.USP 3690177
;* Curso: BCC                                 Disciplina: MAC 211
;* Data : 30/03/2010                          Exercic. Programa 1
;* Montador utilizado: NASM version 2.03.01 
;*
;*****************************************************************/

segment .data

;setando parametros para abertura de arquivo (escrito por Marcelo Reis)
;mensagem de erro
err     db      "Erro ao abrir arquivo!",0xa
len_err     equ     $ - err

;alguns modos de abertura de arquivo
O_RDONLY   equ 	00
O_WRONLY   equ	01
O_CREAT    equ  0100
O_TRUNC    equ  0x0200

;file descriptors (fd)
STDIN    equ     0  ;codigo do fd da entrada padrao
STDOUT   equ     1  ;codigo do fd da saida padrao

cont1            times 4 db 0 ;contador auxiliar
char_anterior    times 4 db 0 ;guarda o caracter lido anteriormente (para identificar fim de arquivo)
equal_char_cont  times 4 db 0 ;conta o numero de caracteres lidos iguais
conta_primo      times 4 db 0 ;conta o numero de primos encontrados

segment .bss

buffer      resb 200     ;buffer auxiliar
arq_in      resb 4       ;guarda o arquivo descritor (fd) do arquivo de entrada
arq_out     resb 4       ;guarda o arquivo descritor (fd) do arquivo de saida
numstring   resb 8       ;guarda o numero atual em processamento no formato string
num_atual   resb 4       ;guarda o numero atual em formato short int
nump        resb 4       ;numero p
numr        resb 4       ;numero r

segment .text 
    global filtra_os_primos

filtra_os_primos:

;salva a base da pilha e os registradores
    push   ebp
    mov    ebp, esp
    pusha

;acessa os elementos na pilha empilhados pelo caller
    mov    eax, [ebp + 8]      ;recupera p
    mov    [nump], eax
    mov    eax, [ebp + 12]     ;recupera r
    mov    [numr], ax
    
;abre o arquivo para leitura
    mov    ebx, [ebp + 16]     ;apontador para onde esta o nome do arquivo de entrada
    mov    ecx, O_RDONLY       ;abre o arquivo pra leitura
    mov    edx, 0              ;indiferente neste caso
    mov    eax, 5              ;numero da syscall de abertura de arquivo (sys_open)
    int    0x80                ;interrupcao 80 (chamada ao nucleo)

    cmp    eax, 1              ;se o arquivo nao foi aberto, exibe erro
    jl     erro
    mov    [arq_in], eax       ;guardo o fd em arq_in

;criacao do arquivo se ele nao existe
    mov    ebx, [ebp + 20]     ;apontador para onde esta o nome do arquivo de saida
    mov    ecx, O_CREAT        ;cria arquivo se ele nao existe
    mov	   edx, 0o664          ;setamos as flags para permissoes de leitura/escrita/execucao
    mov    eax, 5
    int    0x80

    cmp    eax, 1              ;verifica se o arquivo existe e/ou foi criado com sucesso
    jl     erro

    mov    ebx, [ebp + 20]  
    mov    ecx, O_TRUNC        ;apaga o conteudo do arquivo
    mov	   edx, 0          
    mov    eax, 5               ;syscall (sys_open)
    int    0x80
    
;abre o arquivo para escrita
    mov    ebx, [ebp + 20]  
    mov    ecx, O_WRONLY        ;abre arquivo para escrita
    mov	   edx, 0          
    mov    eax, 5               ;syscall (sys_open)
    int    0x80

    cmp    eax, 1              ;verifica se o arquivo pode ser aberto para escrita
    jl     erro

    mov    [arq_out], eax      ;guardo o fd em arq_out
    jmp    le_numero

;exibe uma msg de erro e termina o programa
erro:
    mov    edx, len_err
    mov    ecx, err
    mov    ebx, STDOUT          ;escreve msg de erro em stdout
    mov    eax, 4
    int    0x80
    ;retorna ao sistema
    mov    ebx, 0
    mov    eax, 1
    int    0x80

;faz a leitura de um numero
le_numero:
    mov    eax, 0
    mov    [num_atual], eax          ;zerando a variavel que armazena o numero atual lido
    mov    [cont1], eax              ;zerando o contador de 32 bits

;le o proximo byte
le_byte:
    mov    edx, 1                   ;numero de bytes que eu quero
    mov    ecx, buffer              ;ptr do inicio de buf
    mov    ebx, [arq_in]            ;fd do arquivo de entrada
    mov    eax, 3                   ;numero da syscall de leitura (sys_read)
    int    0x80                     ;chamada ao nucleo
    
    mov    al, [buffer]             ;coloca digito lido em AL
    call   quantos_char_iguais      ;conta quantos caracteres iguais foram lidos em sequencia ate o momento

    cmp    al, 48     
    jl     verifica_numero
    cmp    al, 57     
    jg     verifica_numero
    mov    edi, [cont1]             ;coloca valor do contador do string lido em EDI
    mov    ebx, numstring           ;posicao inicial do string do numero
    mov    dl, [buffer] 
    mov    [ebx + edi], dl          ;move o digito lido para a posicao correta na string do numero
    sub    al, 48                   ;transforma em numero
    mov    cx, ax                   
    mov    ax, [num_atual]          ;move o numero atual calculado para AX, para multiplicar por dez
    mov    bx, 10
    mul    bx
    add    ax, cx
    mov    [num_atual], ax
    inc    word[cont1]              ;incremeta o contador de digitos lidos
    jmp    le_byte                  ;le novo byte

imprime_numero:
    mov    edx, [cont1]            ;tamanho da mensagem
    mov    ecx, numstring          ;endereco inicial da mensagem
    mov    ebx, [arq_out]       
    mov    eax, 4
    int    0x80
    inc    dword[conta_primo]
    jmp    le_numero

;verifica se os digitos lidos formam um numero dentro da faixa especificada
verifica_numero:
    mov    al, [equal_char_cont]
    cmp    al, 8                   ;verifica se chegou no fim do arquivo, nesse caso, 8 digitos sequenciais iguais
    jg    fim
    
    mov    eax, [cont1]            ;verifica se foi lido algum numero
    cmp    eax, 0
    je     le_numero
    
    mov    edi, [cont1]            ;adiciona um espaco (ascii 32) ao fim da string representando o numero
    mov    ebx, numstring         
    mov    dl, 32 
    mov    [ebx + edi], dl        
    inc    word[cont1]

    mov    ax, [nump]
    cmp    [num_atual], ax          ;verifica se o numero lido eh maior do que p
    jb     le_numero
    mov    ax, [numr]
    cmp    [num_atual], ax          ;verifica se o numero lido eh menor do que r
    ja     le_numero
    jmp    fatora

fim:
    ;fecha o arquivo de entrada
    mov	   ebx, [arq_in]     
    mov    eax, 6
    int    0x80
    ;fecha o arquivo de saida
    mov	   ebx, [arq_out]      
    mov    eax, 6
    int    0x80
    ;restaura valor dos registradores
    popa
    pop    ebp                      ;restaura base da pilha
    mov    eax, [conta_primo]       ;passa o numero de primos encontrados por eax
    ret

;fatora o numero lido, por todos os numeros de 2 ate o numero lido menos um
fatora:
    mov    cx, 1
novo_fator:
    inc    cx
    cmp    cx, [num_atual]
    jae    imprime_numero           ;se chegou ate o numero, entao ele eh primo

    mov    ax, [num_atual]
    mov    dx, 0
    div    cx
    cmp    dx, 0
    je     le_numero                ;se achou algum resto de divisao igual a zero, entao ele eh composto
    jmp    novo_fator

;conta o numero de char iguais em sequencia
quantos_char_iguais:
    cmp    al, [char_anterior]
    je     soma    
    mov    dl, 0
    mov    [equal_char_cont], dl
    mov    [char_anterior], al
    ret

;soma um ao contador de caracteres repetidos em sequencia
soma:
    mov    dl, [equal_char_cont]    
    inc    dl
    mov    [equal_char_cont], dl
    ret

