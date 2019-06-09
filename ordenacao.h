/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328

	Aluno: Natã Daniel Gomes de Almeida
	NUSP: 10851666 
* * * * * * * * * * * * * * * * * * */

#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <stdio.h>

/*
	int cmpcresc:
		Função para o quicksort. Compara os números em ordem crescente.
	const void* a:
		constante a (no nosso caso, vai ser inteiro)
	const void* b:
		constante b (no nosso caso, vai ser inteiro)
*/
int cmpcresc(const void* a, const void* b);

/*
	int ordenacao:
		Função para realizar a funcionalidade 8 do trabalho 3.
	char* inFile:
		string com o nome do arquivo de entrada a ser aberto
	char* outFile:
		string com o nome do arquivo de saida a ser feito
*/
int ordenacao(char* inFile, char* outFile);

#endif