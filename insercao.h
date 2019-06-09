/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328

	Aluno: Natã Daniel Gomes de Almeida
	NUSP: 10851666 
* * * * * * * * * * * * * * * * * * */

#ifndef INSERCAO_H
#define INSERCAO_H

#include <stdio.h>
#include "indice.h"

/*
	int insercao:
		Função que lê o arquivo de entrada e um numero de vezes que será rodado 
	char readFile:
		string que recebe o nome do arquivo de entrada
	int n:
		inteiro que recebe a quantidade de vezes que a função irá rodar
*/
int insercao(char* readFile, int n);

void append_indice(struct indice indi[], int max, char *escola, int RRN);

int insercaoindice(char *arqentrada, char *arqindice, int n);

#endif