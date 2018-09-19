/*********************************************************************
 * Filename:   des_test.c
 * Author:     Brad Conte (brad AT bradconte.com)
 * Copyright:
 * Disclaimer: This code is presented "as is" without any guarantees.
 * Details:    Performs known-answer tests on the corresponding DES
 implementation. These tests do not encompass the full
 range of available test vectors, however, if the tests
 pass it is very, very likely that the code is correct
 and was compiled properly. This code also serves as
 example usage of the functions.
 *********************************************************************/

/*************************** HEADER FILES ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <unistd.h>
#include "des.h"
#include <cuda_runtime.h>

/*********************** FUNCTION DEFINITIONS ***********************/
int des_test()
{
	BYTE pt1[DES_BLOCK_SIZE] = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xE7};
	BYTE pt2[DES_BLOCK_SIZE] = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};
	BYTE ct1[DES_BLOCK_SIZE] = {0xc9,0x57,0x44,0x25,0x6a,0x5e,0xd3,0x1d};
	BYTE ct2[DES_BLOCK_SIZE] = {0x85,0xe8,0x13,0x54,0x0f,0x0a,0xb4,0x05};
	BYTE key1[DES_BLOCK_SIZE] = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};
	BYTE key2[DES_BLOCK_SIZE] = {0x13,0x34,0x57,0x79,0x9B,0xBC,0xDF,0xF1};

	BYTE schedule[16][6];
	BYTE buf[DES_BLOCK_SIZE];

	BYTE *d_pt1;
	cudaMalloc((void **)&d_pt1, DES_BLOCK_SIZE);
	cudaMemcpy(d_pt1, pt1, DES_BLOCK_SIZE, cudaMemcpyHostToDevice);

	BYTE *d_ct1;
	cudaMalloc((void **)&d_ct1, DES_BLOCK_SIZE);
	cudaMemcpy(d_ct1, ct1, DES_BLOCK_SIZE, cudaMemcpyHostToDevice);

	BYTE *d_pt2;
	cudaMalloc((void **)&d_pt2, DES_BLOCK_SIZE);
	cudaMemcpy(d_pt2, pt2, DES_BLOCK_SIZE, cudaMemcpyHostToDevice);

	BYTE *d_ct2;
	cudaMalloc((void **)&d_ct2, DES_BLOCK_SIZE);
	cudaMemcpy(d_ct2, ct2, DES_BLOCK_SIZE, cudaMemcpyHostToDevice);

	BYTE *d_schedule;
	cudaMalloc((void **)&d_schedule, sizeof(schedule));

	BYTE *d_buf;
	cudaMalloc((void **)&d_buf, DES_BLOCK_SIZE);

	int pass = 1;

	des_key_setup(key1, schedule, DES_ENCRYPT);
	cudaMemcpy(d_schedule, schedule, sizeof(schedule), cudaMemcpyHostToDevice);
	des_crypt<<<1, 1>>>(d_pt1, d_buf, d_schedule, DES_BLOCK_SIZE);
	cudaMemcpy(buf, d_buf, DES_BLOCK_SIZE, cudaMemcpyDeviceToHost);
	pass = pass && !memcmp(ct1, buf, DES_BLOCK_SIZE);

	des_key_setup(key1, schedule, DES_DECRYPT);
	cudaMemcpy(d_schedule, schedule, sizeof(schedule), cudaMemcpyHostToDevice);
	des_crypt<<<1, 1>>>(d_ct1, d_buf, d_schedule, DES_BLOCK_SIZE);
	cudaMemcpy(buf, d_buf, DES_BLOCK_SIZE, cudaMemcpyDeviceToHost);
	pass = pass && !memcmp(pt1, buf, DES_BLOCK_SIZE);

	des_key_setup(key2, schedule, DES_ENCRYPT);
	cudaMemcpy(d_schedule, schedule, sizeof(schedule), cudaMemcpyHostToDevice);
	des_crypt<<<1, 1>>>(d_pt2, d_buf, d_schedule, DES_BLOCK_SIZE);
	cudaMemcpy(buf, d_buf, DES_BLOCK_SIZE, cudaMemcpyDeviceToHost);
	pass = pass && !memcmp(ct2, buf, DES_BLOCK_SIZE);

	des_key_setup(key2, schedule, DES_DECRYPT);
	cudaMemcpy(d_schedule, schedule, sizeof(schedule), cudaMemcpyHostToDevice);
	des_crypt<<<1, 1>>>(d_ct2, d_buf, d_schedule, DES_BLOCK_SIZE);
	cudaMemcpy(buf, d_buf, DES_BLOCK_SIZE, cudaMemcpyDeviceToHost);
	pass = pass && !memcmp(pt2, buf, DES_BLOCK_SIZE);

	return(pass);
}

void enc_dec_file(char *filename)
{
	BYTE *data; // ponteiro para os dados da imagem base que será criptografada.
	BYTE *encrypted_data; // ponteiro para os dados criptografados
	BYTE *decrypted_data; // ponteiro para os dados descriptografados
	//char *filename = "../../sample_files/king_james_bible.txt"; // endereço do arquivo que será utilizado como base

	BYTE key1[DES_BLOCK_SIZE] = {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF}; // chave de 64 bits
	BYTE schedule[16][6];

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

	BYTE *d_schedule;
	cudaMalloc((void **)&d_schedule, sizeof(schedule));

	int threadsPerBlock = 256;
	int blocksPerGrid =((data_size_bytes + threadsPerBlock - 1) / threadsPerBlock)/DES_BLOCK_SIZE;

	//des_key_setup<<<blocksPerGrid, threadsPerBlock>>>(key1, schedule, DES_ENCRYPT); // seta o schedule para encriptação
	des_key_setup(key1, schedule, DES_ENCRYPT); // seta o schedule para encriptação    
	cudaMemcpy(d_schedule, schedule, sizeof(schedule), cudaMemcpyHostToDevice);
	des_crypt<<<blocksPerGrid, threadsPerBlock>>>(d_data, d_encrypted_data, d_schedule, data_size_bytes); // criptografa o buffer e salva no data_enc

	//des_key_setup<<<blocksPerGrid, threadsPerBlock>>>(key1, schedule, DES_DECRYPT); // seta o schedule para desencriptação
	des_key_setup(key1, schedule, DES_DECRYPT); // seta o schedule para desencriptação
	cudaMemcpy(d_schedule, schedule, sizeof(schedule), cudaMemcpyHostToDevice);
	des_crypt<<<blocksPerGrid, threadsPerBlock>>>(d_encrypted_data, d_decrypted_data, d_schedule, data_size_bytes); // descriptografa o data_enc e salva no data_dec

	cudaMemcpy(encrypted_data, d_encrypted_data, data_size_bytes, cudaMemcpyDeviceToHost); 
	cudaMemcpy(decrypted_data, d_decrypted_data, data_size_bytes, cudaMemcpyDeviceToHost);

	// cria arquivos para a escrita dos dados cripto e descripto
	FILE *enc_file = fopen("file.enc", "wb+");
	FILE *dec_file = fopen("file.dec", "wb+");

	// escreve os dados nos respectivos arquivos criados
	fwrite(encrypted_data, data_size_bytes, 1, enc_file); 
	fwrite(decrypted_data, data_size_bytes, 1, dec_file);

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
	   printf("Des Tests: %s\n", aes_test() ? "SUCCEEDED" : "FAILED");
	 */
	return(0);
}
