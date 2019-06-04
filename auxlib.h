/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#ifndef AUXLIB_H
#define AUXLIB_H

#define ERR_NOTFUNC 0
#define ERR_NOTFILE 0
#define ERR_NOTCONSIST 0
#define ERR_NOTVALCMP 0
#define ERR_NOTNUMBER 0
#define ERR_REMOC 0
#define ERR_NOTTOKEN 0
#define ERR_REGNOTREM 0
#define ERR_ARENTREG 0


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

struct registro{
	char removido;
	int encadeamento;
	int nroInscricao;
	double nota;
	char data[11];
	int itcv1;
	char tag4;
	char cidade[25];
	int itcv2;
	char tag5;
	char nomeEscola[25];
};


void binarioNaTela(char *nomeArquivoBinario);
void binarioNaTela1(FILE *ponteiroArquivoBinario);
void trim(char *str);

/*
	int ehNumero:
		Função que verifica se uma string contem apenas dígitos.
		Retorna 1 caso sim, 0 caso não
	char* str:
		string que será verificada
*/
int ehNumero(char* str);

/*
	int clearstring:
		Função que limpa os n primeiros char de uma string (usando memset \0).
	char* str:
		string que será limpada
	int n:
		quantos caracteres serão limpados
*/
int clearstring(char* str, int n);

/*
	int vctoi:
		Função para decodificar o nome do campo lido e retornar um inteiro correspondente.
		(1 = nroInscricao)
		(2 = nota)
		(3 = data)
		(4 = cidade)
		(5 = nomeEscola)
	char* nomeCampo:
		string de entrada para a decodificação
*/
int vctoi(char* nomeCampo);

/*
	int ehnulo:
		Função que verifica se uma string possui a palavra NULO.
		Retorna 1 caso for nula, 0 caso contrário
	char* str:
		string para ser verificada
	int strlen:
		tamanho da string
*/
int ehnulo(char* str, int strlen);

/*
	int gerarregistros:
		Função para gerar os registros a partir de um arquivo.
		Retorna a quantidade de registros não-nulos gerados
	struct registro reg[]:
		vetor de registros que serão gerados
	int max:
		numero maximo de registros que existem
	FILE* arq:
		ponteiro para o arquivo que será lido
*/
int gerarregistros(struct registro reg[], int max, FILE* arq);

/*
	void gerarindice:
		Função para gerar um indice que guarda o numero de inscricao e sua posição correspondente no vetor de registros.
	int indice[][2]:
		matriz N x 2 chamada de indice.
		primeiro campo é o nroInscricao e segundo é a posição correspondente no vetor de registros
	struct registro reg[]:
		vetor de registros que será gerado o indice para nroInscricao
	int max:
		numero maximo de registros que existem
*/
void gerarindice(int indice[][3], struct registro reg[], int max);

/*
	void writeregbin:
		Função para escrever dados em binário em arquivo da saida.
	struct registro *reg:
		estrutura de registro que será lido
	FILE* saida:
		arquivo que será escrito
*/
void writeallregbin(int indice[][3], int total, struct registro *reg, FILE* saida);

/*
	void clonebin:
		Função para clonar dados em binário de um arquivo para o outro.
	FILE* entrada:
		arquivo que será lido
	FILE* saida:
		arquivo que será escrito
	int n:
		numero de bytes a serem clonados
*/
void clonebin(FILE* entrada, FILE* saida, int n);


#endif


