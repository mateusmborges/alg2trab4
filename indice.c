/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#include "indice.h"
#include "auxlib.h"

int cmpNomeEscola(const void* a, const void* b){
	
	struct indice *indiceA = (struct indice*)a;
	struct indice *indiceB = (struct indice*)b;

	if(strcmp(indiceA->nomeEscola,indiceB->nomeEscola) == 0){
		return(indiceA->rrn - indiceB->rrn);
	}
	else{
		return(strcmp(indiceA->nomeEscola,indiceB->nomeEscola));
	}
}

int leituraindice(struct indice ind[], int max, FILE* arq){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para laços for
		atual = inteiro para contar quantos registros nao estao removidos
		buffercv = buffer para guardar o indicador de tamanho do campo variavel
		faltante = quantidade de bytes faltantes para acabar o registro
		regrem = char para verificar qual é o status do registro
		bufftag = char de buffer para os campos de tag
	*/
	int i, atual = 0, buffercv = 0, faltante = 0;
	char regrem, bufftag;

	//pula pro começo dos registros
	fseek(arq,16000,SEEK_SET);
	//faça max vezes
	for(i = 0; i < max; i++){
		fread(&regrem,sizeof(char),1,arq);						//le o char do status do registro
		//se o registro não estiver removido
		if(regrem == '-'){
			fseek(arq,8,SEEK_CUR);								//pula 4 bytes
			fseek(arq,18,SEEK_CUR);								//pula 4 bytes
			fread(&buffercv,sizeof(int),1,arq);					//guarda o inteiro lido em um buffer
			fread(&bufftag,sizeof(char),1,arq);					//guarda o char lido em um buffer
			//se a tag corresponder ao campo cidade
			if(bufftag == '4'){
				fseek(arq,buffercv-1,SEEK_CUR);					//pula pro proximo campo variavel
				fread(&buffercv,sizeof(int),1,arq);				//guarda o inteiro lido em um buffer
				fread(&bufftag,sizeof(char),1,arq);				//guarda o char lido em um buffer
				//se a tag corresponder ao campo nomeEscola
				if(bufftag == '5'){
					fread(&ind[atual].nomeEscola,sizeof(char),buffercv-1,arq);	//le o campo nomeEscola e coloca no indice
				}
			}
			//se a tag corresponder ao campo nomeEscola
			else if(bufftag == '5'){
				fread(&ind[atual].nomeEscola,sizeof(char),buffercv-1,arq);		//le o campo nomeEscola e coloca no indice
			}
			if(strcmp(ind[atual].nomeEscola,"") != 0){
				ind[atual].rrn = (ftell(arq)-16001) / 80;
				atual++;
			}
		}
		//pula pro proximo registro
		faltante = ftell(arq) % 80;
		if(faltante > 0){
			fseek(arq,80-(ftell(arq) % 80),SEEK_CUR);
		}
	}
	return atual;
}

void escritaindice(struct indice ind[], int max, FILE* arqsaida){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para laços for
		j = variavel para laços for
		bufflen = buffer inteiro para guardar o tamanho da string do nome da escola
		status = char para guardar o status do arquivo
	*/
	int i, j, bufflen = 0;
	char status;

	fseek(arqsaida,0,SEEK_SET);				//vai pro inicio do arquivo
	status = '0';							//atualiza o status para inconsistente
	fwrite(&status,sizeof(char),1,arqsaida);//escreve o status no arquivo
	fwrite(&max,sizeof(int),1,arqsaida);	//escreve a quantidade de registros

	//percorre a primeira pagina de disco e preenche com lixo até o final dela
	for(i = 0; i < 15995; i++){
		fputs("@",arqsaida);
	}

	//coloca os indices no arquivo
	for(i = 0; i < max; i++){	
		bufflen = strlen(ind[i].nomeEscola) + 1;					//le o tamanho da string		
		fwrite(&ind[i].nomeEscola,sizeof(char),bufflen,arqsaida);	//escreve a string no arquivo
		//completa a string com lixo
		for(j = 0; j < 28-bufflen; j++){	
			fputs("@",arqsaida);
		}
		fwrite(&ind[i].rrn,sizeof(int),1,arqsaida);					//escreve o rrn do registro correspondente
	}

	fseek(arqsaida,0,SEEK_SET);				//vai pro inicio do arquivo
	status = '1';							//atualiza o status para inconsistente
	fwrite(&status,sizeof(char),1,arqsaida);//escreve o status no arquivo
}

int criarindice(char* arqentrada, char* arqindice){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para laços for
		qtdmaxreg = inteiro que guarda a quantidade máxima de registros que é possível ter no arquivo de entrada
		total = inteiro que guarda a quantidade de registros não nulos do arquivo de entrada
		status = char para guardar o status do arquivo

	*/
	int i, qtdmaxreg = 1, total;
	char status;

	trim(arqentrada);	//tira os \n e \r da string, se tiver
	trim(arqindice);	//tira os \n e \r da string, se tiver

	//verifica se o arquivo arqentrada existe
	FILE *entrada = fopen(arqentrada,"rb");	//abre o arquivo arqentrada
	if(!entrada){							//se nao conseguir abrir, retorna o erro
		printf("Falha no processamento do arquivo.");	
		return ERR_NOTFILE;
	}

	//verifica se o arquivo arqindice existe
	FILE *saida = fopen(arqindice,"w+b");	//abre o arquivo arqindice
	if(!saida){								//se nao conseguir abrir, retorna o erro
		printf("Falha no processamento do arquivo.");	
		return ERR_NOTFILE;
	}

	//verifica se o arquivo de entrada está consistente
	fread(&status,sizeof(char),1,entrada);
	if(status != '1'){						//se o arquivo nao está consistente
		printf("Falha no processamento do arquivo.");
		return ERR_NOTCONSIST;
	}

	//verifica se o arquivo de indice está consistente
	fread(&status,sizeof(char),1,saida);
	if(status != '1'){						//se o arquivo nao está consistente
		printf("Falha no processamento do arquivo.");
		return ERR_NOTCONSIST;
	}

	fseek(entrada,0,SEEK_END);
	qtdmaxreg = (ftell(entrada)-16000) / 80;

	//struct dos indices do nomeEscola
	struct indice ind[qtdmaxreg];

	//limpar a struct acima
	for(i = 0; i < qtdmaxreg; i++){
		memset(ind[i].nomeEscola,'\0',28);
		ind[i].rrn = -1;
	}

	total = leituraindice(ind,qtdmaxreg,entrada);

	/*
	qsort: 
		Função de ordenação quicksort, incluso na biblioteca stdlib.h
	argumentos:
		primeiro numero,
		qtd total de numeros,
		tamanho em bytes,
		funcao de comparação
	*/
	qsort(ind[0].nomeEscola, total, sizeof(ind[0]), cmpNomeEscola);

	escritaindice(ind,total,saida);

	//printa o arquivo no stdout com a função feita pelo monitor
	binarioNaTela1(saida);

	fclose(entrada);
	fclose(saida);

	return 0;
}