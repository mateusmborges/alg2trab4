/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328

	Aluno: Natã Daniel Gomes de Almeida
	NUSP: 10851666 
* * * * * * * * * * * * * * * * * * */

#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

/*
	int estatisticas:
		Funcao que lê os dados de um arquivo de entrada e de um indice,
		printa os registros que satisfazem o valor dado,
		e compara a quantidade de páginas de disco acessadas com e sem o auxilio do indice
	char arqentrada:
		nome do arquivo de entrada a ser lido
	char arqindice:
		nome do arquivo de indice a ser lido
	char nomeCampo:
		nome do campo a ser criado o indice (no caso, nomeEscola)
	char valor:
		nome da escola a ser pesquisada
*/
int estatisticas(char* arqentrada, char* arqindice, char* nomeCampo, char* valor);

#endif