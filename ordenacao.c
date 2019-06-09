/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328

	Aluno: Natã Daniel Gomes de Almeida
	NUSP: 10851666 
* * * * * * * * * * * * * * * * * * */

#include "ordenacao.h"
#include "auxlib.h"


int cmpcresc(const void* a, const void* b){
	return (*(int*)a - *(int*)b);
}

int ordenacao(char* inFile, char* outFile){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para loops
		j = variavel para loops
		qtdmaxreg = inteiro para guardar a quantidade máxima de registros
		qtdreg = inteiro para guardar a quantidade de registros não removidos
		total = quantidade total de registros não nulos
		menosum = constante -1
		status = char para verificar qual é o status do arquivo
	*/
	int i, j, qtdmaxreg, total = 0;
	const int menosum = -1;
	char status;

	//cria e verifica se o arquivo inFile existe
	FILE *arqentrada = fopen(inFile, "rb");
	if(!arqentrada){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTFILE;
	}
	//cria e verifica se o arquivo outFile existe
	FILE *arqsaida = fopen(outFile, "w+b");
	if(!arqsaida){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTFILE;
	}
	//verifica se o arquivo de entrada está consistente ou não
	fread(&status,sizeof(char),1,arqentrada);
	if(status == '0'){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTCONSIST;
	}
	//verifica se o arquivo de saida está consistente ou não
	fread(&status,sizeof(char),1,arqsaida);
	if(status == '0'){
		printf("Falha no processamento do arquivo.");
		return ERR_NOTCONSIST;
	}

	fseek(arqentrada,0,SEEK_END);
	qtdmaxreg = ((ftell(arqentrada) - 16000) / 80);

	//cria um vetor de registros
	struct registro reg[qtdmaxreg];

	//matriz de inteiros para guardar o nroInscricao e o RRN: indice[nroInscricao][RRNcorrespondente]
	int indice[qtdmaxreg][3];

	//limpa a matriz indice
	for(i = 0; i < qtdmaxreg; i++){
		for(j = 0; j < 3; j++){
			indice[i][j] = -1;
		}
	}

	//funcao para gerar os registros a partir de um arquivo
	gerarregistros(reg,qtdmaxreg,arqentrada);

	//conta quantos registros não removidos existem e guarda em qtdreg
	for(i = 0; i < qtdmaxreg; i++){
		if(reg[i].nroInscricao == -1 || reg[i].nroInscricao == 0){
			total = i;
			break;
		}
		total = qtdmaxreg;
	}

	//funcao para gerar o "indice" dos registros baseado no nroInscricao
	gerarindice(indice,reg,total);
	
	/*
	qsort: 
		Função de ordenação quicksort, incluso na biblioteca stdlib.h
	argumentos:
		primeiro numero,
		qtd total de numeros,
		tamanho em bytes,
		funcao de comparação
	*/
	qsort(indice[0], total, 3*sizeof(int), cmpcresc);

	//volta pro começo dos arquivos para clonar o cabeçalho
	fseek(arqentrada,0,SEEK_SET);
	fseek(arqsaida,0,SEEK_SET);
	//copia o cabecalho do arquivo de entrada para o arquivo de saida
	clonebin(arqentrada, arqsaida, 16000);

	//volta pro começo do cabeçalho e atualiza o status('0') e o topoPilha (-1)
	fseek(arqsaida,0,SEEK_SET);
	status = '0';
	fwrite(&status,sizeof(char),1,arqsaida);
	fwrite(&menosum,sizeof(int),1,arqsaida);

	//pula pro inicio dos registros
	fseek(arqsaida,16000,SEEK_SET);

	//copia todos os registros não removidos para o arquivo de saida 
	writeallregbin(indice,total,reg,arqsaida);

	//volta pro começo do cabeçalho e atualiza o status('1')
	fseek(arqsaida,0,SEEK_SET);
	status = '1';
	fwrite(&status,sizeof(char),1,arqsaida);

	//printa o arquivo no stdout com a função feita pelo monitor
	binarioNaTela1(arqsaida);

	fclose(arqentrada);
	fclose(arqsaida);

	return 0;
}