 /* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#ifndef INDICE_H
#define INDICE_H

#include "auxlib.h"
/*
	struct indice = estrutura para guardar o indice secundário fortemente ligado 
	com o campo nomeEscola a ser indexado
		char nomeEscola = string para guardar o nome da escola
		int rrn = inteiro para guardar o rrn relacionado
*/
struct indice{
	char nomeEscola[28];
	int rrn;
};

/*
	int cmpNomeEscola:
		Função de comparação a ser usada no quicksort. Ela compara duas strings e
		se forem iguais, é comparado o rrn delas
		Retorna -X caso o primeiro dado "a" é menor,
		+X caso o segundo dado "b" é menor,
		e 0 caso os dados são iguais
	void* a:
		primeiro dado a ser comparado
	void* b:
		segundo dado a ser comparado
*/
int cmpNomeEscola(const void* a, const void* b);

/*
	int leituraindice:
		Função que lê o arquivo de entrada e gera um indice ind
		Retorna o número de registros não nulos do arquivo de entrada
	struct indice ind[]:
		vetor de indices que será gerado
	int max:
		quantidade máxima de registros que o arquivo de entrada pode ter
	FILE* arq:
		ponteiro para o arquivo binário de entrada
*/
int leituraindice(struct indice ind[], int max, FILE* arq);

/*
	void escritaindice:
		Função que lê o vetor de indice e escreve de volta para um arquivo de entrada
	struct indice ind[]:
		vetor de indices que será lido
	int max:
		quantidade máxima de registros que o indice possui
	FILE* arqsaida:
		ponteiro para o arquivo binário de saida
*/
void escritaindice(struct indice ind[], int max, FILE* arqsaida);

/*
	int criarindice:
		Função que lê o arquivo de entrada e gera um arquivo de indice
	char arqentrada:
		string que recebe o nome do arquivo de entrada
	char arqindice:
		string que recebe o nome do arquivo do indice
*/
int criarindice(char* arqentrada, char* arqindice);

#endif