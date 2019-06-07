/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#ifndef REMOCAO_H
#define REMOCAO_H

#include "indice.h"
#include <stdio.h>

/*	Caso seja para remover os registros baseado no numero de inscrição
	void casonumeroinscricao:
		Remove logicamente registros que satisfazem um critério dado na entrada
	int alvo:
		numero de inscricao no critério de entrada
	FILE* arquivo:
		ponteiro para um arquivo binário de entrada
*/
void casonumeroinscricao(int alvo, FILE* arquivo);

/*	Caso seja para remover os registros baseado na nota
	void casonota:
		Remove logicamente registros que satisfazem um critério dado na entrada
	double alvo:
		nota no critério de entrada
	FILE* arquivo:
		ponteiro para um arquivo binário de entrada
*/
void casonota(double alvo, FILE* arquivo);

/*	Caso seja para remover os registros baseado na data
	void casodata:
		Remove logicamente registros que satisfazem um critério dado na entrada
	char alvo:
		data no critério de entrada
	FILE* arquivo:
		ponteiro para um arquivo binário de entrada
*/
void casodata(char* alvo, FILE* arquivo);

/*	Caso seja para remover os registros baseado na cidade
	void casocidade:
		Remove logicamente registros que satisfazem um critério dado na entrada
	char alvo:
		cidade no critério de entrada
	FILE* arquivo:
		ponteiro para um arquivo binário de entrada
*/
void casocidade(char* alvo, FILE* arquivo);

/*	Caso seja para remover os registros baseado no nome da escola
	void casonomeescola:
		Remove logicamente registros que satisfazem um critério dado na entrada
	char alvo:
		nome da escola no critério de entrada
	FILE* arquivo:
		ponteiro para um arquivo binário de entrada
*/
void casonomeescola(char* alvo, FILE* arquivo);

/*
	int remocao:
		Função que realiza as remoções dos registros que satisfazem certos critérios dados na entrada
	char readFile:
		string que recebe o nome do arquivo de entrada
	int n:
		quantidade de critérios que serão lidos
*/
int remocao(char* readFile, int n);

/*
	void removedoindice:
		Função que remove o registro do indice também 
	struct indice ind[]:
		vetor de indices que será lido e removido
	int max:
		quantidade de registros que o indice possui
	int rrn:
		RRN do registro a ser removido
*/
void removedoindice(struct indice ind[], int max, int rrn);

/*	Caso seja para remover os registros baseado no numero de inscrição, e ter q remover de um indice também
	void casonumeroinscricaoindice:
		Remove logicamente registros no arquivo inteiro que satisfazem um critério dado na entrada,
		e remove logicamente o registro no índice
	int alvo:
		numero de inscricao no critério de entrada
	struct indice ind[]:
		vetor de indices que será lido e removido
	int max:
		quantidade de registros que o indice possui
	FILE* arquivo:
		ponteiro para um arquivo binário de entrada
*/
void casonumeroinscricaoindice(int alvo, struct indice ind[], int max, FILE* arquivo);

/*	Caso seja para remover os registros baseado na nota, e ter q remover de um indice também
	void casonotaindice:
		Remove logicamente registros no arquivo inteiro que satisfazem um critério dado na entrada,
		e remove logicamente o registro no índice
	double alvo:
		nota no critério de entrada
	struct indice ind[]:
		vetor de indices que será lido e removido
	int max:
		quantidade de registros que o indice possui
	FILE* arquivo:
		ponteiro para um arquivo binário de entrada
*/
void casonotaindice(double alvo, struct indice ind[], int max, FILE* arquivo);

/*	Caso seja para remover os registros baseado na data, e ter q remover de um indice também
	void casodataindice:
		Remove logicamente registros no arquivo inteiro que satisfazem um critério dado na entrada,
		e remove logicamente o registro no índice
	char alvo:
		data no critério de entrada
	struct indice ind[]:
		vetor de indices que será lido e removido
	int max:
		quantidade de registros que o indice possui
	FILE* arquivo:
		ponteiro para um arquivo binário de entrada
*/
void casodataindice(char* alvo, struct indice ind[], int max, FILE* arquivo);

/*	Caso seja para remover os registros baseado na cidade, e ter q remover de um indice também
	void casocidadeindice:
		Remove logicamente registros no arquivo inteiro que satisfazem um critério dado na entrada,
		e remove logicamente o registro no índice
	char alvo:
		cidade no critério de entrada
	struct indice ind[]:
		vetor de indices que será lido e removido
	int max:
		quantidade de registros que o indice possui
	FILE* arquivo:
		ponteiro para um arquivo binário de entrada
*/
void casocidadeindice(char* alvo, struct indice ind[], int max, FILE* arquivo);

/*	Caso seja para remover os registros baseado no nome da escola, e ter q remover de um indice também
	void casonomeescolaindice:
		Remove logicamente registros no arquivo inteiro que satisfazem um critério dado na entrada,
		e remove logicamente o registro no índice
	char alvo:
		nome da cidade no critério de entrada
	struct indice ind[]:
		vetor de indices que será lido e removido
	int max:
		quantidade de registros que o indice possui
	FILE* arquivo:
		ponteiro para um arquivo binário de entrada
*/
void casonomeescolaindice(char* alvo, struct indice ind[], int max, FILE* arquivo);

/*	
	void write_back_indice:
		Reescreve em um arquivo de indice baseado nos dados de um vetor de indice
	struct indice ind[]:
		vetor de indices que será lido e removido
	int max:
		quantidade de registros que o indice possui
	FILE* arqind:
		ponteiro para um arquivo binário de indice
*/
void write_back_indice(struct indice ind[], int max, FILE* arqind);

/*
	int remocaoindice:
		Função que realiza as remoções dos registros que satisfazem certos critérios dados na entrada,
		e também remove de um indice
	char readFile:
		string que recebe o nome do arquivo de entrada
	char indFile:
		string que recebe o nome do arquivo de indice
	int n:
		quantidade de critérios que serão lidos
*/
int remocaoindice(char* readFile, char* indFile, int n);

#endif