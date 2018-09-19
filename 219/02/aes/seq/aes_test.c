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
#include <string.h>
#include <sys/stat.h>
#include "aes.h"


/*********************** FUNCTION DEFINITIONS ***********************/
void print_hex(BYTE str[], int len)
{
	int idx;

	for(idx = 0; idx < len; idx++)
		printf("%02x", str[idx]);
}

int aes_ecb_test()
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
}

int aes_cbc_test()
{
	WORD key_schedule[60];
	BYTE enc_buf[128];
	BYTE plaintext[1][32] = {
		{0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51}
	};
	BYTE ciphertext[1][32] = {
		{0xf5,0x8c,0x4c,0x04,0xd6,0xe5,0xf1,0xba,0x77,0x9e,0xab,0xfb,0x5f,0x7b,0xfb,0xd6,0x9c,0xfc,0x4e,0x96,0x7e,0xdb,0x80,0x8d,0x67,0x9f,0x77,0x7b,0xc6,0x70,0x2c,0x7d}
	};
	BYTE iv[1][16] = {
		{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f}
	};
	BYTE key[1][32] = {
		{0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4}
	};
	int pass = 1;

	//printf("* CBC mode:\n");
	aes_key_setup(key[0], key_schedule, 256);

	//printf(  "Key          : ");
	//print_hex(key[0], 32);
	//printf("\nIV           : ");
	//print_hex(iv[0], 16);

	aes_encrypt_cbc(plaintext[0], 32, enc_buf, key_schedule, 256, iv[0]);
	//printf("\nPlaintext    : ");
	//print_hex(plaintext[0], 32);
	//printf("\n-encrypted to: ");
	//print_hex(enc_buf, 32);
	//printf("\nCiphertext   : ");
	//print_hex(ciphertext[0], 32);
	pass = pass && !memcmp(enc_buf, ciphertext[0], 32);

	aes_decrypt_cbc(ciphertext[0], 32, enc_buf, key_schedule, 256, iv[0]);
	//printf("\nCiphertext   : ");
	//print_hex(ciphertext[0], 32);
	//printf("\n-decrypted to: ");
	//print_hex(enc_buf, 32);
	//printf("\nPlaintext   : ");
	//print_hex(plaintext[0], 32);
	pass = pass && !memcmp(enc_buf, plaintext[0], 32);

	//printf("\n\n");
	return(pass);
}

int aes_ctr_test()
{
	WORD key_schedule[60];
	BYTE enc_buf[128];
	BYTE plaintext[1][32] = {
		{0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a,0xae,0x2d,0x8a,0x57,0x1e,0x03,0xac,0x9c,0x9e,0xb7,0x6f,0xac,0x45,0xaf,0x8e,0x51}
	};
	BYTE ciphertext[1][32] = {
		{0x60,0x1e,0xc3,0x13,0x77,0x57,0x89,0xa5,0xb7,0xa7,0xf5,0x04,0xbb,0xf3,0xd2,0x28,0xf4,0x43,0xe3,0xca,0x4d,0x62,0xb5,0x9a,0xca,0x84,0xe9,0x90,0xca,0xca,0xf5,0xc5}
	};
	BYTE iv[1][16] = {
		{0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff},
	};
	BYTE key[1][32] = {
		{0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4}
	};
	int pass = 1;

	//printf("* CTR mode:\n");
	aes_key_setup(key[0], key_schedule, 256);

	//printf(  "Key          : ");
	//print_hex(key[0], 32);
	//printf("\nIV           : ");
	//print_hex(iv[0], 16);

	aes_encrypt_ctr(plaintext[0], 32, enc_buf, key_schedule, 256, iv[0]);
	//printf("\nPlaintext    : ");
	//print_hex(plaintext[0], 32);
	//printf("\n-encrypted to: ");
	//print_hex(enc_buf, 32);
	pass = pass && !memcmp(enc_buf, ciphertext[0], 32);

	aes_decrypt_ctr(ciphertext[0], 32, enc_buf, key_schedule, 256, iv[0]);
	//printf("\nCiphertext   : ");
	//print_hex(ciphertext[0], 32);
	//printf("\n-decrypted to: ");
	//print_hex(enc_buf, 32);
	pass = pass && !memcmp(enc_buf, plaintext[0], 32);

	//printf("\n\n");
	return(pass);
}

int aes_ccm_test()
{
	int mac_auth;
	WORD enc_buf_len;
	BYTE enc_buf[128];
	BYTE plaintext[3][32] = {
		{0x20,0x21,0x22,0x23},
		{0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f},
		{0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37}
	};
	BYTE assoc[3][32] = {
		{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07},
		{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f},
		{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13}
	};
	BYTE ciphertext[3][32 + 16] = {
		{0x71,0x62,0x01,0x5b,0x4d,0xac,0x25,0x5d},
		{0xd2,0xa1,0xf0,0xe0,0x51,0xea,0x5f,0x62,0x08,0x1a,0x77,0x92,0x07,0x3d,0x59,0x3d,0x1f,0xc6,0x4f,0xbf,0xac,0xcd},
		{0xe3,0xb2,0x01,0xa9,0xf5,0xb7,0x1a,0x7a,0x9b,0x1c,0xea,0xec,0xcd,0x97,0xe7,0x0b,0x61,0x76,0xaa,0xd9,0xa4,0x42,0x8a,0xa5,0x48,0x43,0x92,0xfb,0xc1,0xb0,0x99,0x51}
	};
	BYTE iv[3][16] = {
		{0x10,0x11,0x12,0x13,0x14,0x15,0x16},
		{0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17},
		{0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b}
	};
	BYTE key[1][32] = {
		{0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f}
	};
	int pass = 1;

	//printf("* CCM mode:\n");
	//printf("Key           : ");
	//print_hex(key[0], 16);

	//print_hex(plaintext[0], 4);
	//print_hex(assoc[0], 8);
	//print_hex(ciphertext[0], 8);
	//print_hex(iv[0], 7);
	//print_hex(key[0], 16);

	aes_encrypt_ccm(plaintext[0], 4, assoc[0], 8, iv[0], 7, enc_buf, &enc_buf_len, 4, key[0], 128);
	//printf("\nNONCE        : ");
	//print_hex(iv[0], 7);
	//printf("\nAssoc. Data  : ");
	//print_hex(assoc[0], 8);
	//printf("\nPayload       : ");
	//print_hex(plaintext[0], 4);
	//printf("\n-encrypted to: ");
	//print_hex(enc_buf, enc_buf_len);
	pass = pass && !memcmp(enc_buf, ciphertext[0], enc_buf_len);

	aes_decrypt_ccm(ciphertext[0], 8, assoc[0], 8, iv[0], 7, enc_buf, &enc_buf_len, 4, &mac_auth, key[0], 128);
	//printf("\n-Ciphertext  : ");
	//print_hex(ciphertext[0], 8);
	//printf("\n-decrypted to: ");
	//print_hex(enc_buf, enc_buf_len);
	//printf("\nAuthenticated: %d ", mac_auth);
	pass = pass && !memcmp(enc_buf, plaintext[0], enc_buf_len) && mac_auth;


	aes_encrypt_ccm(plaintext[1], 16, assoc[1], 16, iv[1], 8, enc_buf, &enc_buf_len, 6, key[0], 128);
	//printf("\n\nNONCE        : ");
	//print_hex(iv[1], 8);
	//printf("\nAssoc. Data  : ");
	//print_hex(assoc[1], 16);
	//printf("\nPayload      : ");
	//print_hex(plaintext[1], 16);
	//printf("\n-encrypted to: ");
	//print_hex(enc_buf, enc_buf_len);
	pass = pass && !memcmp(enc_buf, ciphertext[1], enc_buf_len);

	aes_decrypt_ccm(ciphertext[1], 22, assoc[1], 16, iv[1], 8, enc_buf, &enc_buf_len, 6, &mac_auth, key[0], 128);
	//printf("\n-Ciphertext  : ");
	//print_hex(ciphertext[1], 22);
	//printf("\n-decrypted to: ");
	//print_hex(enc_buf, enc_buf_len);
	//printf("\nAuthenticated: %d ", mac_auth);
	pass = pass && !memcmp(enc_buf, plaintext[1], enc_buf_len) && mac_auth;


	aes_encrypt_ccm(plaintext[2], 24, assoc[2], 20, iv[2], 12, enc_buf, &enc_buf_len, 8, key[0], 128);
	//printf("\n\nNONCE        : ");
	//print_hex(iv[2], 12);
	//printf("\nAssoc. Data  : ");
	//print_hex(assoc[2], 20);
	//printf("\nPayload      : ");
	//print_hex(plaintext[2], 24);
	//printf("\n-encrypted to: ");
	//print_hex(enc_buf, enc_buf_len);
	pass = pass && !memcmp(enc_buf, ciphertext[2], enc_buf_len);

	aes_decrypt_ccm(ciphertext[2], 32, assoc[2], 20, iv[2], 12, enc_buf, &enc_buf_len, 8, &mac_auth, key[0], 128);
	//printf("\n-Ciphertext  : ");
	//print_hex(ciphertext[2], 32);
	//printf("\n-decrypted to: ");
	//print_hex(enc_buf, enc_buf_len);
	//printf("\nAuthenticated: %d ", mac_auth);
	pass = pass && !memcmp(enc_buf, plaintext[2], enc_buf_len) && mac_auth;

	//printf("\n\n");
	return(pass);
}

int aes_test()
{
	int pass = 1;

	pass = pass && aes_ecb_test();
	pass = pass && aes_cbc_test();
	pass = pass && aes_ctr_test();
	pass = pass && aes_ccm_test();

	return(pass);
}

void enc_dec_file(char *filename)
{
	/*********************** ABERTURA E LEITURA DO ARQUIVO DE ENTRADA ***********************/
	BYTE *data;
	BYTE *encrypted_data;
	BYTE *decrypted_data;
	//char *filename = "../../sample_files/king_james_bible.txt";

	WORD key_schedule[60], idx;
	BYTE enc_buf[128];

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

	BYTE data_buf[AES_BLOCK_SIZE]; // cria um array de 8 posições (uma por bloco) para cada byte da chave
	BYTE data_enc[AES_BLOCK_SIZE]; 
	BYTE data_dec[AES_BLOCK_SIZE];

	for(int i = 0; i < st.st_size; i++){ // para cada byte da imagem
		// de 8 em 8 bytes, ou de bloco em bloco, atribui parte do arquivo ao buffer
		for(int j = 0; j < AES_BLOCK_SIZE; j++){ // para cada byte do bloco do des
			if(i < st.st_size){ // para i nao ultrapassar o tamanho do arquivo, ja que i é incrementado dentro desse if
				data_buf[j] = data[i]; // atribui uma parte da imagem ao buffer de dados
				i++;
			};
		};

		aes_key_setup(key[0], key_schedule, 256);

		aes_encrypt(data_buf, data_enc, key_schedule, 256);
		aes_decrypt(data_enc, data_dec, key_schedule, 256);

		i -= AES_BLOCK_SIZE; // decrementa o i
		for(int k = 0; k < AES_BLOCK_SIZE; k++){ // para cada byte do bloco do des
			if(i < st.st_size){
				// atribui o byte criptografado e descriptografado para os respectivos arrays da imagem finals
				encrypted_data[i] = data_enc[k]; 
				decrypted_data[i] = data_dec[k];
				i++;
			};
		};

		i--;
	};

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
