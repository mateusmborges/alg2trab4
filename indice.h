/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#ifndef INDICE_H
#define INDICE_H

#include "auxlib.h"

struct indice{
	char nomeEscola[28];
	int nroInscricao;
	int rrn;
};

int cmpNomeEscola(const void* a, const void* b);

int leituraindice(struct indice ind[], int max, FILE* arq);

int criarindice(char* arqentrada, char* arqindice);

#endif