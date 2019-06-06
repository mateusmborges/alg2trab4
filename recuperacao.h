/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#ifndef RECUPERACAO_H
#define RECUPERACAO_H

#include "auxlib.h"
#include "indice.h"
#include <stdio.h>

int leitura_arquivo_indice(struct indice ind[], int qtdregs, FILE* arqind);

int buscabinaria(struct indice ind[], int qtdregs, char* escola);

void recupera_registro(int rrn, FILE* arq);

int recuperacao(char* readFile);

int recuperacaoindice(char* readFile, char* indFile, char* nomeCampo, char* valor);

#endif