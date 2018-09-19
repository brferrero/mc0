/*********************************************************************
 * Filename:   aes_test.c
 * Author:     Brad Conte (brad AT bradconte.com)
 * Copyright:
 * Disclaimer: This code is presented "as is" without any guarantees.
 * Details:    Performs known-answer tests on the corresponding AES
 implementation. These tests do not encompass the full
 range of available test vectors and are not sufficient
 for FIPS-140 certification. However, if the tests pass
 it is very, very likely that the code is correct and was
 compiled properly. This code also serves as
 example usage of the functions.
 *********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/stat.h>
#include "aes.h"
#include <cuda_runtime.h>


/*********************** FUNCTION DEFINITIONS ***********************/
void print_hex(BYTE str[], int len)
{
	int idx;

	for(idx = 0; idx < len; idx++)
		printf("%02x", str[idx]);
}

/*int aes_ecb_test()
  {
  WORD key_schedule[60], idx;
  BYTE enc_buf[128];
  BYTE plaintext[2][16] = {
  {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a},
  {0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51}
  };
  BYTE ciphertext[2][16] = {
  {0xf3,0xee,0xd1,0xbd,0xb5,0xd2,0xa0,0x3c,0x06,0x4b,0x5a,0x7e,0x3d,0xb1,0x81,0xf8},
  {0x59,0x1c,0xcb,0x10,0xd4,0x10,0xed,0x26,0xdc,0x5b,0xa7,0x4a,0x31,0x36,0x28,0x70}
  };
  BYTE key[1][32] = {
  {0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4}
  };
  int pass = 1;

// Raw ECB mode.
//printf("* ECB mode:\n");
aes_key_setup(key[0], key_schedule, 256);
//printf(  "Key          : ");
//print_hex(key[0], 32);

for(idx = 0; idx < 2; idx++) {
aes_encrypt(plaintext[idx], enc_buf, key_schedule, 256);
//printf("\nPlaintext    : ");
//print_hex(plaintext[idx], 16);
//printf("\n-encrypted to: ");
//print_hex(enc_buf, 16);
pass = pass && !memcmp(enc_buf, ciphertext[idx], 16);

aes_decrypt(ciphertext[idx], enc_buf, key_schedule, 256);
//printf("\nCiphertext   : ");
//print_hex(ciphertext[idx], 16);
//printf("\n-decrypted to: ");
//print_hex(enc_buf, 16);
pass = pass && !memcmp(enc_buf, plaintext[idx], 16);

//printf("\n\n");
}

return(pass);
}*/

int aes_test()
{
	int pass = 1;

	//pass = pass && aes_ecb_test();
	//pass = pass && aes_cbc_test();
	//pass = pass && aes_ctr_test();
	//pass = pass && aes_ccm_test();

	return(pass);
}

void enc_dec_file(char *filename)
{
	/*********************** ABERTURA E LEITURA DO ARQUIVO DE ENTRADA ***********************/
	BYTE *data;
	BYTE *encrypted_data;
	BYTE *decrypted_data;
	//char *filename = "../../sample_files/hubble_1.tif";

	WORD key_schedule[60];

	BYTE key[1][32] = {
		{0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4}
	};

	struct stat st; // stat guarda informações sobre arquivos
	size_t data_size_bytes = 0;

	if (stat(filename, &st) == 0){ // provavelmente verifica se é possivel atribuir o stat st ao arquivo base, e caso sim
		data_size_bytes = sizeof(BYTE) * st.st_size;
		data = (BYTE *) malloc(data_size_bytes); // reserva o tamanho do arquivo base em memória para o ponteiro data.
	};

	FILE *file = fopen(filename, "rb"); // abre o arquivo do tipo nao texto ("rb")

	// copia a imagem para o vetor data
	if(data != NULL && file){ // se o ponteiro data e de arquivo ja foram alocados e abertos, respectivamente, entao prossegue
		int current_byte = 0; // define o byte atual

		// de byte em byte, copia o arquivo para o array data
		while(fread(&data[current_byte], sizeof(BYTE), 1, file) == 1){ 
			current_byte += 1; // atualiza o byte atual
		};
	};

	encrypted_data = (BYTE *) malloc(data_size_bytes); // reserva espaço em memoria para o arquivo criptogrfado
	decrypted_data = (BYTE *) malloc(data_size_bytes); // o mesmo para o arquivo decodificado

	BYTE *d_data; // ponteiro para os dados da imagem base no device
	BYTE *d_encrypted_data; // ponteiro para os dados criptografados no device
	BYTE *d_decrypted_data; // ponteiro para os dados descriptografados no device

	// alocação de memória para os devices
	cudaMalloc((void **)&d_data, data_size_bytes);
	cudaMalloc((void **)&d_encrypted_data, data_size_bytes);
	cudaMalloc((void **)&d_decrypted_data, data_size_bytes);

	cudaMemcpy(d_data, data, data_size_bytes, cudaMemcpyHostToDevice); // copia o array de dados para o device

	WORD *d_schedule;
	cudaMalloc((void **)&d_schedule, sizeof(key_schedule));

	int threadsPerBlock = 256;
	int blocksPerGrid =((data_size_bytes + threadsPerBlock - 1) / threadsPerBlock)/AES_BLOCK_SIZE;

	aes_key_setup(key[0], key_schedule, 256);
	cudaMemcpy(d_schedule, key_schedule, sizeof(key_schedule), cudaMemcpyHostToDevice);
	aes_encrypt<<<blocksPerGrid, threadsPerBlock>>>(d_data, d_encrypted_data, d_schedule, 256, data_size_bytes); // criptografa o buffer e salva no data_enc
	aes_decrypt<<<blocksPerGrid, threadsPerBlock>>>(d_encrypted_data, d_decrypted_data, d_schedule, 256, data_size_bytes); // descriptografa o data_enc e salva no data_dec

	cudaMemcpy(encrypted_data, d_encrypted_data, data_size_bytes, cudaMemcpyDeviceToHost); 
	cudaMemcpy(decrypted_data, d_decrypted_data, data_size_bytes, cudaMemcpyDeviceToHost);

	// cria arquivos para a escrita dos dados cripto e descripto
	FILE *enc_file = fopen("file.enc", "wb+");
	FILE *dec_file = fopen("file.dec", "wb+");

	// escreve os dados nos respectivos arquivos criados
	fwrite(encrypted_data, sizeof(BYTE) * st.st_size, 1, enc_file); 
	fwrite(decrypted_data, sizeof(BYTE) * st.st_size, 1, dec_file);

	// fecha os arquivos
	fclose(enc_file);
	fclose(dec_file);
};

int main(int argc, char *argv[])
{
	if (argc == 2) {
		enc_dec_file(argv[1]);
	}
	/*
	   printf("AES Tests: %s\n", aes_test() ? "SUCCEEDED" : "FAILED");
	 */
	return(0);
}
