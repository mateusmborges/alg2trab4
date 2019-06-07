/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#ifndef RECUPERACAO_H
#define RECUPERACAO_H

#include "auxlib.h"
#include "indice.h"
#include <stdio.h>

/*
	int leitura_arquivo_indice:
		Função que lê o arquivo do indice e gera o vetor de indices 
		Retorna a quantidade de páginas de disco acessadas ao ler o arquivo de indice
	struct indice ind[]:
		vetor de indices que será gerado
	int qtdregs:
		quantidade de registros que o indice possui
	FILE* arqind:
		ponteiro para o arquivo binário do indice
*/
int leitura_arquivo_indice(struct indice ind[], int qtdregs, FILE* arqind);

/*
	int buscabinaria:
		Função que faz uma busca binária de uma string escola no vetor de indices
		Retorna a posição do primeiro nome de escola que é igual ao nome da escola buscado,
		ou -1 se não encontrar
	struct indice ind[]:
		vetor de indices que será lido
	int qtdregs:
		quantidade de registros que o indice possui
	char* escola:
		nome da escola alvo da busca
*/
int buscabinaria(struct indice ind[], int qtdregs, char* escola);

/*
	void recupera_registro:
		Função que recebe um rrn e procura esse registro relacionado no arquivo de entrada,
		printando os dados lidos do acesso direto
	int rrn:
		RRN relacionado ao registro que será buscado no arquivo de entrada via acesso direto
	FILE* arq:
		ponteiro para o arquivo binário de entrada
*/
void recupera_registro(int rrn, FILE* arq);

/*
	int recuperacao:
		Funcao que lê os dados de um arquivo de entrada e exibe eles no stdout
	char readFile:
		nome do arquivo a ser lido
*/
int recuperacao(char* readFile);

/*
	int recuperacaoindice:
		Funcao que lê os dados de um arquivo de entrada e de um indice,
		e printa os registros que satisfazem o valor dado
	char readFile:
		nome do arquivo de entrada a ser lido
	char indFile:
		nome do arquivo de indice a ser lido
	char nomeCampo:
		nome do campo a ser criado o indice (no caso, nomeEscola)
	char valor:
		nome da escola a ser pesquisada
*/
int recuperacaoindice(char* readFile, char* indFile, char* nomeCampo, char* valor);

#endif