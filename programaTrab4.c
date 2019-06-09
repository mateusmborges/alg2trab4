/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328

	Aluno: Natã Daniel Gomes de Almeida
	NUSP: 10851666 
* * * * * * * * * * * * * * * * * * */

#include "remocao.h"
#include "recuperacao.h"
#include "insercao.h"
#include "indice.h"
#include "auxlib.h"
#include "ordenacao.h"
#include "estatisticas.h"

int main(){
	
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para laços for
		func = inteiro para armazenar a funcionalidade
		n = numero de iteraçoes para o caso de remocao, insercao e atualizacao
		camposEntrada = strings com os campos da entrada
		entrada = string para armazenar a entrada lida de stdin
		valorCampo = string para armazenar o valor do campo a ser criado o indice
	*/
	int i, func = 0, n = 0;
	char camposEntrada[4][30], entrada[100];		

	//para printar os acentos certos
	setlocale(LC_CTYPE,"Portuguese"); 
	
	//limpa as strings camposEntrada
	for(i = 0; i < 3; i++){
		clearstring(camposEntrada[i],30);
	}

	clearstring(entrada,100);		//limpa a entrada
	fgets(entrada,100,stdin);		//pega a entrada

	//funcao para gerar strings dos camposEntrada
	char *token = strtok(entrada, " ");
	for(i = 0; i < 10; i++){
		if(i == 0 && token){
			func = strtol(token,NULL,10);
		}
		if(i == 1 && token){
			strcpy(camposEntrada[0],token);
		}
		if(i == 2 && token){
			strcpy(camposEntrada[1],token);
		}
		if(i == 3 && token){
			strcpy(camposEntrada[2],token);
		}
		if(i == 4 && token){
			strcpy(camposEntrada[3],token);
		}
		if(i > 4 && token){
			strcat(camposEntrada[3]," ");
			strcat(camposEntrada[3],token);
		}
		token = strtok(NULL," ");	
	}

	//tira os \n e \r das strings, se tiver
	for(i = 0; i < 4; i++){
		trim(camposEntrada[i]);
	}
	
	i = 0;
	//tira as aspas do nome da escola
	if(camposEntrada[3][i] == '\"'){
		camposEntrada[3][i] = camposEntrada[3][i+1];
		while(camposEntrada[3][i] != '\"'){
			camposEntrada[3][i] = camposEntrada[3][i+1];
			i++;
		}
		if(camposEntrada[3][i-1] == '\"'){
			camposEntrada[3][i-1] = '\0';
		}
	}



	//verificar qual é a funcionalidade escolhida
	switch(func){
		//se for a funcionalidade 2
		case 2:
			recuperacao(camposEntrada[0]);
		break;
		//se for a funcionalidade 5
		case 5:
			n = strtol(camposEntrada[1],NULL,10);
			remocao(camposEntrada[0], n);
		break;
		//se for a funcionalidade 6
		case 6:
			//insercao(camposEntrada[0], camposEntrada[1]);
		break;
		//se for a funcionalidade 7
		case 7:
			//atualizacao(camposEntrada[0], camposEntrada[1]);
		break;
		//se for a funcionalidade 8
		case 8:
			//ordenacao(camposEntrada[0], camposEntrada[1]);
		break;
		//se for a funcionalidade 9
		case 9:
			//uniao(camposEntrada[0], camposEntrada[1], camposEntrada[2]);
		break;
		//se for a funcionalidade 10
		case 10:
			//interseccao(camposEntrada[0], camposEntrada[1], camposEntrada[2]);
		break;
		//se for a funcionalidade 11
		case 11:
			criarindice(camposEntrada[0], camposEntrada[1]);
		break;
		//se for a funcionalidade 12
		case 12:
			recuperacaoindice(camposEntrada[0], camposEntrada[1], camposEntrada[2], camposEntrada[3]);
		break;
		//se for a funcionalidade 13
		case 13:
			n = strtol(camposEntrada[2],NULL,10);
			remocaoindice(camposEntrada[0], camposEntrada[1], n);
		break;
		//se for a funcionalidade 14
		case 14:
			n = strtol(camposEntrada[2], NULL, 10);
			insercaoindice(camposEntrada[0], camposEntrada[1], n);
		break;
		//se for a funcionalidade 15
		case 15:
			estatisticas(camposEntrada[0], camposEntrada[1], camposEntrada[2], camposEntrada[3]);
		break;
		
		//caso nao exista a funcionalidade ainda
		default:
			printf("Funcionalidade %d não implementada.\n",func);
			return ERR_NOTFUNC;
	}

	return 0;
}
