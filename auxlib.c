/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "auxlib.h"


void binarioNaTela(char *nomeArquivoBinario) {

	/* Escolha essa função se você já fechou o ponteiro de arquivo 'FILE *'.
	*  Ela vai abrir de novo para leitura e depois fechar. */

	unsigned char *mb;
	unsigned long i;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar? Se você não fechou ele, pode usar a outra função, binarioNaTela1, ou pode fechar ele antes de chamar essa função!\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);
	for(i = 0; i < fl; i += sizeof(unsigned char)) {
		printf("%02X ", mb[i]);
		if((i + 1) % 16 == 0)	printf("\n");
	}
	free(mb);
	fclose(fs);
}

void binarioNaTela1(FILE *ponteiroArquivoBinario) {

	/* Escolha essa função se você ainda tem o ponteiro de arquivo 'FILE *' aberto.
	*  Lembrando que você tem que ter aberto ele no fopen para leitura também pra funcionar (exemplo: rb, rb+, wb+, ...) */

	unsigned char *mb;
	unsigned long i;
	size_t fl;
	fseek(ponteiroArquivoBinario, 0, SEEK_END);
	fl = ftell(ponteiroArquivoBinario);
	fseek(ponteiroArquivoBinario, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, ponteiroArquivoBinario);
	for(i = 0; i < fl; i += sizeof(unsigned char)) {
		printf("%02X ", mb[i]);
		if((i + 1) % 16 == 0)	printf("\n");
	}
	free(mb);
}

void trim(char *str) {

	/*
	*	Essa função arruma uma string de entrada "str".
	*	Manda pra ela uma string que tem '\r' e ela retorna sem.
	*	Ela remove do início e do fim da string todo tipo de espaçamento (\r, \n, \t, espaço, ...).
	*	Por exemplo:
	*
	*	char minhaString[] = "    \t TESTE  DE STRING COM BARRA R     \t  \r\n ";
	*	trim(minhaString);
	*	printf("[%s]", minhaString); // vai imprimir "[TESTE  DE STRING COM BARRA R]"
	*
	*/

	size_t len;
	char *p;

	for(len = strlen(str); len > 0 && isspace(str[len - 1]); len--); // remove espaçamentos do fim
	str[len] = '\0';
	for(p = str; *p != '\0' && isspace(*p); p++); // remove espaçamentos do começo
	len = strlen(p);
	memmove(str, p, sizeof(char) * (len + 1));
}


int ehNumero(char* str){
	if(str[0] == '\0'){
		return 0;
	}
	int i = 0;
	while(str[i] != '\0'){
		if(isdigit(str[i]) || str[i] == '.'){
			i++;
		}
		else{
			return 0;
		}
	}
	return 1;
}

int clearstring(char* str, int n){
	if(!str){
		return 0;
	}
	memset(str,'\0',n);
	return 1;
}

int vctoi(char* nomeCampo){
	if(strcmp(nomeCampo,"nroInscricao") == 0){
		return 1;
	}
	else if(strcmp(nomeCampo,"nota") == 0){
		return 2;
	}
	else if(strcmp(nomeCampo,"data") == 0){
		return 3;
	}
	else if(strcmp(nomeCampo,"cidade") == 0){
		return 4;
	}
	else if(strcmp(nomeCampo,"nomeEscola") == 0){
		return 5;
	}
	else{
		return 0;
	}
}

int ehnulo(char* str, int strlen){
	for(int i = 0; i < strlen-4; i++){
		if(str[i] == 'N'){
			if(str[i+1] == 'U'){
				if(str[i+2] == 'L'){
					if(str[i+3] == 'O'){
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int gerarregistros(struct registro reg[], int max, FILE* arq){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para loops
		atual = inteiro para contar quantos registros nao estao removidos
		buffercv = buffer para guardar o indicador de tamanho do campo variavel
		regrem = char para verificar qual é o status do registro
		bufftag = char de buffer para os campos de tag
	*/
	int i, atual = 0, buffercv = 0;
	char regrem, bufftag;

	//pula pro começo dos registros
	fseek(arq,16000,SEEK_SET);
	//faça max vezes
	for(i = 0; i < max; i++){
		fread(&regrem,sizeof(char),1,arq);						//le o char do status do registro
		//se o registro não estiver removido
		if(regrem == '-'){
			fseek(arq,-1,SEEK_CUR);								//volta 1 byte
			fread(&reg[atual].removido,sizeof(char),1,arq);		//le o char do status
			fread(&reg[atual].encadeamento,sizeof(int),1,arq);	//le o int do encadeamento
			fread(&reg[atual].nroInscricao,sizeof(int),1,arq);	//le o int do nroInscricao
			fread(&reg[atual].nota,sizeof(double),1,arq);		//le o double da nota
			fread(&reg[atual].data,sizeof(char),10,arq);		//le a string da data
			reg[atual].data[10] = '\0';							//anula o ultimo byte da data
			//se a data for nula
			if(reg[atual].data[0] == '\0'){
				memset(reg[atual].data,'\0',11);				//limpa a string da data
			}
			fread(&buffercv,sizeof(int),1,arq);					//guarda o inteiro lido em um buffer
			fread(&bufftag,sizeof(char),1,arq);					//guarda o char lido em um buffer
			//se a tag for 4 (se existir o campo cidade)
			if(bufftag == '4'){
				reg[atual].itcv1 = buffercv;
				reg[atual].tag4 = bufftag;
				fread(&reg[atual].cidade,sizeof(char),reg[atual].itcv1-1,arq);
				fread(&buffercv,sizeof(int),1,arq);
				//se existir o campo nomeEscola (e se existir o campo cidade)
				if(buffercv != 1077952576){
					reg[atual].itcv2 = buffercv;
					fread(&reg[atual].tag5,sizeof(char),1,arq);
					fread(&reg[atual].nomeEscola,sizeof(char),reg[atual].itcv2-1,arq);
				}
				//se nao existir o campo nomeEscola (mas se existir o campo cidade)
				else{
					reg[atual].itcv2 = -1;
					reg[atual].tag5 = '\0';
					memset(reg[atual].nomeEscola,'\0',25);

				}
			}
			//se a tag for 5 (se nao existir o campo cidade e existir o campo nomeEscola)
			else if(bufftag == '5'){
				reg[atual].itcv1 = -1;
				reg[atual].tag4 = '\0';
				memset(reg[atual].cidade,'\0',25);
				reg[atual].itcv2 = buffercv;
				reg[atual].tag5 = bufftag;
				fread(&reg[atual].nomeEscola,sizeof(char),reg[atual].itcv2-1,arq);
			}
			//se a tag nao existir (se nao existir nenhum campo)
			else{
				reg[atual].itcv1 = -1;
				reg[atual].tag4 = '\0';
				memset(reg[atual].cidade,'\0',25);
				reg[atual].itcv2 = -1;
				reg[atual].tag5 = '\0';
				memset(reg[atual].nomeEscola,'\0',25);
			}
			atual++;										
		} //end if regrem
		if((ftell(arq)%80) == 0){
			fseek(arq,-80,SEEK_CUR);
		}
		fseek(arq,80-(ftell(arq)%80),SEEK_CUR);
	}
	//limpa os registros que sobraram
	for(i = atual; i < max; i++){
		reg[i].removido = '*';
		reg[i].encadeamento = -1;
		reg[i].nroInscricao = -1;
		reg[i].nota = -1.0;
		reg[i].itcv1 = -1;
		reg[i].tag4 = '\0';
		memset(reg[i].cidade,'\0',25);
		reg[i].itcv2 = -1;
		reg[i].tag5 = '\0';
		memset(reg[i].nomeEscola,'\0',25);
	}
	
	return atual;
}

void gerarindice(int indice[][3], struct registro reg[], int max){
	int i;

	for(i = 0; i < max; i++){
		if(reg[i].nroInscricao != -1 && reg[i].nroInscricao != 0){
			indice[i][0] = reg[i].nroInscricao;
			indice[i][1] = i;
		}
	}
}

void writeallregbin(int indice[][3], int total, struct registro reg[], FILE* saida){
	int i, pos = 0, qtdbytes = 0;
	for(i = 0; i < total; i++){
		qtdbytes = 0;
		pos = indice[i][1];
		fwrite(&reg[pos].removido,sizeof(char),1,saida);
		fwrite(&reg[pos].encadeamento,sizeof(int),1,saida);
		fwrite(&reg[pos].nroInscricao,sizeof(int),1,saida);
		fwrite(&reg[pos].nota,sizeof(double),1,saida);
		if(reg[pos].data[0] == '\0'){
			fputc('\0',saida);
			for(int j = 0; j < 9; j++){
				fputs("@",saida);
			}
		}
		else{
			fwrite(&reg[pos].data,sizeof(char),10,saida);
		}
		qtdbytes += 27;
		if(reg[pos].itcv1 != -1){
			fwrite(&reg[pos].itcv1,sizeof(int),1,saida);
			fwrite(&reg[pos].tag4,sizeof(char),1,saida);
			fwrite(&reg[pos].cidade,sizeof(char),reg[pos].itcv1-1,saida);
			qtdbytes += reg[pos].itcv1 + sizeof(int);
		}
		if(reg[pos].itcv2 != -1){
			fwrite(&reg[pos].itcv2,sizeof(int),1,saida);
			fwrite(&reg[pos].tag5,sizeof(char),1,saida);
			fwrite(&reg[pos].nomeEscola,sizeof(char),reg[pos].itcv2-1,saida);
			qtdbytes += reg[pos].itcv2 + sizeof(int);
		}
		for(int i = 0; i < 80-qtdbytes; i++){
			fputc('@',saida);
		}
	}
}

void clonebin(FILE* entrada, FILE* saida, int n){
	char c;	//char que serve de buffer
	//repete n vezes
	for(int i = 0; i < n; i++){
		fread(&c,sizeof(char),1,entrada);	//le o char da entrada
		fwrite(&c,sizeof(char),1,saida);	//escreve esse char na saida
	}
}