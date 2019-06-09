/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328

	Aluno: Natã Daniel Gomes de Almeida
	NUSP: 10851666 
* * * * * * * * * * * * * * * * * * */

#include "remocao.h"
#include "auxlib.h"
#include "indice.h"
#include "recuperacao.h"

void casonumeroinscricao(int alvo, FILE* arquivo){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = inteiro para laços for
		topoPilha = inteiro para guardar o topo da pilha
		encont = inteiro para guardar a qtd de registros encontrados
		nira = inteiro para ler o nroInscricao do registro atual
		regrem = char para ler se o registro está removido ou nao
		endoffile = char para verificar se nao acabou o arquivo
	*/
	int i, topoPilha, encont = 0, nira;
	char regrem, endoffile;

	//le o topo da pilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fread(&topoPilha,sizeof(int),1,arquivo);
	//vai pro começo dos registros
	fseek(arquivo,16000,SEEK_SET);
	
	//passa o arquivo inteiro até acabar
	while(arquivo){
		fseek(arquivo,5,SEEK_CUR); //pula 5 bytes para ler o nroInscricao do registro
		fread(&nira,sizeof(int),1,arquivo);		
		//verifica se o numero da entrada é igual ao numero de inscricao do registro atual
		if(alvo == nira){
			fseek(arquivo,-9,SEEK_CUR); 				//volta pro começo do registro
			fread(&regrem,sizeof(char),1,arquivo); 	//le o byte do campo removido
			//se o byte for '-' é pq o registro nao foi removido ainda
			if(regrem == '-'){
				encont++;
				fseek(arquivo,-1,SEEK_CUR);
				fputc('*',arquivo); //atualiza o campo para removido
				fwrite(&topoPilha,sizeof(int),1,arquivo); //atualiza o topo da pilha
				//transforma todos os outros campos do registro em lixo
				for(i = 0; i < 75; i++){
					fputs("@",arquivo);
				}
				topoPilha = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o topoPilha com o RRN do registro atual
				//atualiza o topoPilha no cabeçalho
				fseek(arquivo,1,SEEK_SET);
				fwrite(&topoPilha,sizeof(int),1,arquivo);
				break;
			}
			//se o registro já estiver removido
			else{
				fseek(arquivo,79,SEEK_CUR);
			}
		}
		//se o numero de entrada nao for igual ao numero de insc do registro atual
		else{
			fseek(arquivo,71,SEEK_CUR);
		}

		fread(&endoffile,sizeof(char),1,arquivo);
		//verifica se nao acabou o arquivo
		if(feof(arquivo)){
			if(encont == 0){	//se nao encontrou nenhum registro, retorna inexistente
				//printf("Registro inexistente.");
			}
			break;
		}
		//se nao acabou, volta 1 byte
		else{
			fseek(arquivo,-1,SEEK_CUR);
		}
	} //fim do while arquivo

	//atualiza o topoPilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fwrite(&topoPilha,sizeof(int),1,arquivo);
}

void casonota(double alvo, FILE* arquivo){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = inteiro para laços for
		topoPilha = inteiro para guardar o topo da pilha
		encont = inteiro para guardar a qtd de registros encontrados
		nora = double para ler a nota do registro atual
		regrem = char para ler se o registro está removido ou nao
		endoffile = char para verificar se nao acabou o arquivo
	*/
	int i, topoPilha, encont = 0;
	double nora;
	char regrem, endoffile;

	//le o topo da pilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fread(&topoPilha,sizeof(int),1,arquivo);
	//vai pro começo dos registros
	fseek(arquivo,16000,SEEK_SET);
	
	//passa o arquivo inteiro até acabar
	while(arquivo){
		fseek(arquivo,9,SEEK_CUR); //pula 9 bytes para ler a nota do registro atual
		fread(&nora,sizeof(double),1,arquivo);
		//verifica se o numero da entrada é igual a nota do registro atual
		if(alvo == nora){
			fseek(arquivo,-17,SEEK_CUR); 			//volta pro começo do registro
			fread(&regrem,sizeof(char),1,arquivo); 	//le o byte do campo removido
			//se o byte for '-' é pq o registro nao foi removido ainda
			if(regrem == '-'){
				encont++;
				fseek(arquivo,-1,SEEK_CUR);
				fputc('*',arquivo); //atualiza o campo para removido
				fwrite(&topoPilha,sizeof(int),1,arquivo); //atualiza o topo da pilha
				//transforma todos os outros campos do registro em lixo
				for(i = 0; i < 75; i++){
					fputs("@",arquivo);
				}
				topoPilha = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o topoPilha com o RRN do registro atual
			}
			//se o registro já estiver removido
			else{
				fseek(arquivo,79,SEEK_CUR);
			}
		}
		//se o numero de entrada nao for igual a nota do registro atual
		else{
			fseek(arquivo,63,SEEK_CUR);
		}
		
		fread(&endoffile,sizeof(char),1,arquivo);
		//verifica se nao acabou o arquivo
		if(feof(arquivo)){
			if(encont == 0){	//se nao encontrou nenhum registro, retorna inexistente
				//printf("Registro inexistente.");
			}
			break;
		}
		//se nao acabou, volta 1 byte
		else{
			fseek(arquivo,-1,SEEK_CUR);
		}
	} //fim do while arquivo
	
	//atualiza o topoPilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fwrite(&topoPilha,sizeof(int),1,arquivo);
}

void casodata(char* alvo, FILE* arquivo){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = inteiro para laços for
		topoPilha = inteiro para guardar o topo da pilha
		encont = inteiro para guardar a qtd de registros encontrados
		dra = string para ler a data do registro atual
		regrem = char para ler se o registro está removido ou nao
		endoffile = char para verificar se nao acabou o arquivo
	*/
	int i, topoPilha, encont = 0;
	char dra[11], regrem, endoffile;

	//le o topo da pilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fread(&topoPilha,sizeof(int),1,arquivo);
	//vai pro começo dos registros
	fseek(arquivo,16000,SEEK_SET);
	
	dra[10] = '\0'; //coloca o ultimo byte de dra como '\0'
	
	//passa o arquivo inteiro até acabar
	while(arquivo){
		fseek(arquivo,17,SEEK_CUR); //pula 17 bytes para ler a data do registro atual
		fread(&dra,sizeof(char),10,arquivo);
		//verifica se a string da entrada é igual a data do registro atual
		if(strcmp(alvo,dra) == 0){
			fseek(arquivo,-27,SEEK_CUR); 			//volta pro começo do registro
			fread(&regrem,sizeof(char),1,arquivo); 	//le o byte do campo removido
			//se o byte for '-' é pq o registro nao foi removido ainda
			if(regrem == '-'){
				encont++;
				fseek(arquivo,-1,SEEK_CUR);
				fputc('*',arquivo); //atualiza o campo para removido
				fwrite(&topoPilha,sizeof(int),1,arquivo); //atualiza o topo da pilha
				//transforma todos os outros campos do registro em lixo
				for(i = 0; i < 75; i++){
					fputs("@",arquivo);
				}
				topoPilha = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o topoPilha com o RRN do registro atual
			}
			//se o registro já estiver removido
			else{
				fseek(arquivo,79,SEEK_CUR);
			}
		}
		//se a string de entraad nao for igual a data do registro atual
		else{
			fseek(arquivo,53,SEEK_CUR);
		}
		
		fread(&endoffile,sizeof(char),1,arquivo);
		//verifica se nao acabou o arquivo
		if(feof(arquivo)){
			if(encont == 0){	//se nao encontrou nenhum registro, retorna inexistente
				//printf("Registro inexistente.");
			}
			break;
		}
		//se nao acabou, volta 1 byte
		else{
			fseek(arquivo,-1,SEEK_CUR);
		}
	} //fim do while arquivo
	
	//atualiza o topoPilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fwrite(&topoPilha,sizeof(int),1,arquivo);
}

void casocidade(char* alvo, FILE* arquivo){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = inteiro para laços for
		topoPilha = inteiro para guardar o topo da pilha
		encont = inteiro para guardar a qtd de registros encontrados
		itcv = inteiro para armazenar o indicador de tamanho do campo variavel
		cra = string para ler a data do registro atual
		regrem = char para ler se o registro está removido ou nao
		endoffile = char para verificar se nao acabou o arquivo
		tag4 = char para comparar com a tag do campo 4
	*/
	int i, topoPilha, encont = 0, itcv;
	char cra[30], regrem, endoffile, tag4;

	//le o topo da pilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fread(&topoPilha,sizeof(int),1,arquivo);
	//vai pro começo dos registros
	fseek(arquivo,16000,SEEK_SET);

	cra[29] = '\0'; //coloca o ultimo byte de cra como '\0'

	//passa o arquivo inteiro até acabar
	while(arquivo){
		fseek(arquivo,31,SEEK_CUR); //pula 31 bytes para ler a tag do primeiro campo variavel do registro atual
		fread(&tag4,sizeof(char),1,arquivo); //le o que era pra ser a tag da cidade
		//se o char lido corresponder a tag da cidade ('4')
		if(tag4 == '4'){
			fseek(arquivo,-5,SEEK_CUR); 			//volta 5 bytes para ler o indicador de tamanho do campo variavel
			fread(&itcv,sizeof(int),1,arquivo);	//le os 4 bytes seguintes e armazena o indicador de tamanho do campo variavel
			fread(&tag4,sizeof(char),1,arquivo);	//le o proximo byte e armazena em tag4
			fread(&cra,sizeof(char),itcv-1,arquivo);//le uma string do campo variavel
			//verifica se a string da entrada é igual a cidade do registro atual
			if(strcmp(alvo,cra) == 0){
				fseek(arquivo,-(31 + itcv),SEEK_CUR); 	//volta pro começo do registro
				fread(&regrem,sizeof(char),1,arquivo); 	//le o byte do campo removido
				//se o byte for '-' é pq o registro nao foi removido ainda
				if(regrem == '-'){
					encont++;
					fseek(arquivo,-1,SEEK_CUR);
					fputc('*',arquivo); //atualiza o campo para removido
					fwrite(&topoPilha,sizeof(int),1,arquivo); //atualiza o topo da pilha
					//transforma todos os outros campos do registro em lixo
					for(i = 0; i < 75; i++){
						fputs("@",arquivo);
					}
					topoPilha = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o topoPilha com o RRN do registro atual
				}
				//se o registro já estiver removido
				else{
					fseek(arquivo,79,SEEK_CUR);
				}
			}
			//se a string de entrada nao for igual a cidade do registro atual
			else{
				fseek(arquivo,80-(31+itcv),SEEK_CUR);
			}
		}
		//se o char lido nao for '4'
		else{
			fseek(arquivo,48,SEEK_CUR);
		}				

		fread(&endoffile,sizeof(char),1,arquivo);
		//verifica se nao acabou o arquivo
		if(feof(arquivo)){
			if(encont == 0){	//se nao encontrou nenhum registro, retorna inexistente
				//printf("Registro inexistente.");
			}
			break;
		}
		//se nao acabou, volta 1 byte
		else{
			fseek(arquivo,-1,SEEK_CUR);
		}
	} //fim do while arquivo
	
	//atualiza o topoPilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fwrite(&topoPilha,sizeof(int),1,arquivo);
}

void casonomeescola(char* alvo, FILE* arquivo){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = inteiro para laços for
		topoPilha = inteiro para guardar o topo da pilha
		encont = inteiro para guardar a qtd de registros encontrados
		itcv1 = inteiro para armazenar o indicador de tamanho do campo variavel
		itcv2 = inteiro para armazenar o indicador de tamanho do campo variavel
		cra = string para ler a data do registro atual
		nera = string para ler o nome da escola do registro atual
		regrem = char para ler se o registro está removido ou nao
		endoffile = char para verificar se nao acabou o arquivo
		tag4 = char para comparar com a tag do campo 4
		tag5 = char para comparar com a tag do campo 5
	*/
	int i, topoPilha, encont = 0, itcv1, itcv2;
	char cra[30], nera[30], regrem, endoffile, tag4, tag5;

	//le o topo da pilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fread(&topoPilha,sizeof(int),1,arquivo);
	//vai pro começo dos registros
	fseek(arquivo,16000,SEEK_SET);

	nera[29] = '\0'; //coloca o ultimo de nera byte como '\0'
	cra[29] = '\0'; //coloca o ultimo de cra byte como '\0'

	//passa o arquivo inteiro até acabar
	while(arquivo){
		fseek(arquivo,31,SEEK_CUR); //pula 31 bytes para ler a tag do primeiro campo variavel do registro atual
		fread(&tag5,sizeof(char),1,arquivo); //le o que era pra ser a tag da cidade
		//se o char lido corresponder a tag do nomeEscola ('5')
		if(tag5 == '5'){
			fseek(arquivo,-5,SEEK_CUR); 			//volta 5 bytes para ler o indicador de tamanho do campo variavel
			fread(&itcv1,sizeof(int),1,arquivo);	//le os 4 bytes seguintes e armazena o indicador de tamanho do campo variavel
			fread(&tag5,sizeof(char),1,arquivo);	//le o proximo byte e armazena em tag5
			fread(&nera,sizeof(char),itcv1-1,arquivo);//le uma string do campo variavel					
			//verifica se a string da entrada é igual ao nome de escola do registro atual
			if(strcmp(alvo,nera) == 0){
				fseek(arquivo,-(31 + itcv1),SEEK_CUR); 	//volta pro começo do registro
				fread(&regrem,sizeof(char),1,arquivo); 	//le o byte do campo removido
				//se o byte for '-' é pq o registro nao foi removido ainda
				if(regrem == '-'){
					encont++;
					fseek(arquivo,-1,SEEK_CUR);
					fputc('*',arquivo); //atualiza o campo para removido
					fwrite(&topoPilha,sizeof(int),1,arquivo); //atualiza o topo da pilha
					//transforma todos os outros campos do registro em lixo
					for(i = 0; i < 75; i++){
						fputs("@",arquivo);
					}
					topoPilha = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o topoPilha com o RRN do registro atual
				}
				//se o registro já estiver removido
				else{
					fseek(arquivo,79,SEEK_CUR);
				}
			}
			//se a string de entrada nao for igual ao nome da escola do registro atual
			else{
				fseek(arquivo,80-(itcv1 + 31),SEEK_CUR);
			}
		}
		//se o char lido corresponder a tag da cidade ('4')
		else if(tag5 == '4'){
			fseek(arquivo,-5,SEEK_CUR); 			//volta 5 bytes para ler o indicador de tamanho do campo variavel
			fread(&itcv1,sizeof(int),1,arquivo);	//le os 4 bytes seguintes e armazena o indicador de tamanho do campo variavel
			fread(&tag4,sizeof(char),1,arquivo);	//le o proximo byte e armazena em tag4
			fread(&cra,sizeof(char),itcv1-1,arquivo);//le uma string do campo variavel
			fseek(arquivo,4,SEEK_CUR);			//pula 5 bytes
			fread(&tag5,sizeof(char),1,arquivo);	//le o byte e coloca em tag5
			//verifica se o byte lido é a tag do campo nomeEscola
			if(tag5 == '5'){
				fseek(arquivo,-5,SEEK_CUR);			//volta 5 bytes para ler o indicador de tamanho do campo variavel
				fread(&itcv2,sizeof(int),1,arquivo);	//le os 4 bytes seguintes e armazena o indicador de tamanho do campo variavel
				fread(&tag5,sizeof(char),1,arquivo);	//le o proximo byte e armazena em tag5
				fread(&nera,sizeof(char),itcv2-1,arquivo);//le uma string do campo variavel
				//verifica se a string da entrada é igual ao nome de escola do registro atual
				if(strcmp(alvo,nera) == 0){
					fseek(arquivo,-(itcv2 + 4 + itcv1 + 31),SEEK_CUR);	//volta pro começo do registro 
					fread(&regrem,sizeof(char),1,arquivo);				//le o byte do campo removido
					//se o byte for '-' é pq o registro nao foi removido ainda
					if(regrem == '-'){
						encont++;
						fseek(arquivo,-1,SEEK_CUR);
						fputc('*',arquivo); //atualiza o campo para removido
						fwrite(&topoPilha,sizeof(int),1,arquivo); //atualiza o topo da pilha
						//transforma todos os outros campos do registro em lixo
						for(i = 0; i < 75; i++){
							fputs("@",arquivo);
						}
						topoPilha = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o topoPilha com o RRN do registro atual
					}
					//se o registro já estiver removido
					else{
						fseek(arquivo,79,SEEK_CUR);
					}	
				}
				//se a string de entrada nao for igual ao nome da escola do registro atual
				else{
					fseek(arquivo,80-(itcv2 + 4 + itcv1 + 31),SEEK_CUR);
				}
			}
			//se nao for a tag do campo nomeEscola
			else{
				fseek(arquivo,80-(itcv1 + 5 + 31),SEEK_CUR);
			}
		}
		//se o char lido nao for nem '4' nem '5'	
		else{
			fseek(arquivo,48,SEEK_CUR);
		}			

		fread(&endoffile,sizeof(char),1,arquivo);
		//verifica se nao acabou o arquivo
		if(feof(arquivo)){
			if(encont == 0){	//se nao encontrou nenhum registro, retorna inexistente
				//printf("Registro inexistente.");
			}
			break;
		}
		//se nao acabou, volta 1 byte
		else{
			fseek(arquivo,-1,SEEK_CUR);
		}
	} //fim do while arquivo
	
	//atualiza o topoPilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fwrite(&topoPilha,sizeof(int),1,arquivo);
}

int remocao(char* readFile, int n){	
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para laços for
		vci = valor do campo inteiro
		atual = variavel do laço para ler todas as linhas de entrada
		decodvalor = inteiro para decodificar o valor do campo para o switch
		vcf = valor do campo flutuante
		status = char para guardar o status do arquivo
		nomeCampo = string para guardar o nome do campo
		valorCampo = string para guardar o valor do campo
	*/
	int i, vci, atual, decodvalor;
	double vcf;
	char status, nomeCampo[n][50], valorCampo[n][50];

	trim(readFile);	//tira os \n e \r da string, se tiver

	//verifica se o arquivo readFile existe
	FILE *arqbin = fopen(readFile,"r+b");	//abre o arquivo readFile
	if(!arqbin){							//se nao conseguir abrir, retorna o erro
		printf("Falha no processamento do arquivo.");	
		return ERR_NOTFILE;
	}

	//verifica se o arquivo está consistente
	fread(&status,sizeof(char),1,arqbin);
	if(status != '1'){						//se o arquivo nao está consistente
		printf("Falha no processamento do arquivo.");
		return ERR_NOTCONSIST;
	}

	//volta um byte para reescrever o status
	fseek(arqbin,-1,SEEK_CUR);
	//atualiza o status
	status = '0';
	fwrite(&status,sizeof(char),1,arqbin);

	//limpa as strings acima
	for(i = 0; i < n; i++){
		clearstring(nomeCampo[i],50);
		clearstring(valorCampo[i],50);
	}

	/* Laço para passar lendo a entrada n vezes */
	for(atual = 0; atual < n; atual++){
		//ler a proxima entrada
		char entrada[100];
		clearstring(entrada,100);
		fgets(entrada,100,stdin);
		
		trim(entrada); 		//tira o \n e o \r da entrada

		//funcao para gerar uma string nomeCampo[atual] e uma string valorCampo[atual]
		char *token = strtok(entrada, " ");
		if(!token){
			return ERR_NOTTOKEN;
		}
		for(i = 0; i < 6; i++){
			if(i == 0 && token){
				strcpy(nomeCampo[atual],token);
			}
			else if(i == 1 && token){
				strcpy(valorCampo[atual],token);
			}						
			else if(i > 1 && token){
				strcat(valorCampo[atual]," ");
				strcat(valorCampo[atual],token);
			}
			else if(!token){
				break;
			}
			token = strtok(NULL," ");
		}

		//tira os \n e \r das strings acima
		trim(nomeCampo[atual]);
		trim(valorCampo[atual]);

		//o if abaixo serve para tirar as aspas se a entrada em valorCampo for uma string
		if(valorCampo[atual][0] == '\"'){
			i = 1;
			while(valorCampo[atual][i] != '\"'){
				valorCampo[atual][i-1] = valorCampo[atual][i];
				i++;
			}
			valorCampo[atual][i-1] = '\0';
		}

		decodvalor = vctoi(nomeCampo[atual]);

		switch(decodvalor){
			//caso o valorCampo for nroInscricao
			case 1:
				//transforma o valorCampo em inteiro
				vci = strtol(valorCampo[atual],NULL,10);				
				casonumeroinscricao(vci, arqbin);
			break;
			//caso o valorCampo for nota
			case 2:
				//transforma o valorCampo em um double
				vcf = strtod(valorCampo[atual],NULL);
				casonota(vcf, arqbin);
			break;
			//caso o valorCampo for data
			case 3:		
				casodata(valorCampo[atual], arqbin);
			break;
			//caso o valorCampo for cidade
			case 4:
				casocidade(valorCampo[atual], arqbin);
			break;
			//caso o valorCampo for nomeEscola
			case 5:
				casonomeescola(valorCampo[atual], arqbin);
			break;
			default:
				printf("Falha no processamento do arquivo.\n");
				return ERR_NOTVALCMP;
		} 	//acaba o switch
	}	//acaba o for de atual a n

	//volta pro primeiro byte para atualizar o status
	fseek(arqbin,0,SEEK_SET);
	//atualiza o status para consistente
	status = '1';
	fwrite(&status,sizeof(char),1,arqbin);

	//printa o arquivo no stdout com a função feita pelo monitor
	binarioNaTela1(arqbin);		

	//fecha o arquivo de leitura/escrita
	fclose(arqbin);

	return 0;
}

void removedoindice(struct indice ind[], int max, int rrn){	
	//passa por todos os registros pra verificar
	for(int i = 0; i < max; i++){
		//se o rrn bater, exclui logicamente o registro no vetor de indice
		if(rrn == ind[i].rrn){
			 ind[i].rrn = -1;		//seta o rrn como -1		
			 strcpy(ind[i].nomeEscola,"");//limpa o nome da escola
			 return;
		}
	}
}

void casonumeroinscricaoindice(int alvo, struct indice ind[], int max, FILE* arquivo){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = inteiro para laços for
		topoPilha = inteiro para guardar o topo da pilha
		encont = inteiro para guardar a qtd de registros encontrados
		nira = inteiro para ler o nroInscricao do registro atual
		rrn = inteiro para guardar o rrn do registro removido
		regrem = char para ler se o registro está removido ou nao
		endoffile = char para verificar se nao acabou o arquivo
	*/
	int i, topoPilha, encont = 0, nira, rrn;
	char regrem, endoffile;

	//le o topo da pilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fread(&topoPilha,sizeof(int),1,arquivo);
	//vai pro começo dos registros
	fseek(arquivo,16000,SEEK_SET);
	
	//passa o arquivo inteiro até acabar
	while(arquivo){
		fseek(arquivo,5,SEEK_CUR); //pula 5 bytes para ler o nroInscricao do registro
		fread(&nira,sizeof(int),1,arquivo);		
		//verifica se o numero da entrada é igual ao numero de inscricao do registro atual
		if(alvo == nira){
			fseek(arquivo,-9,SEEK_CUR); 				//volta pro começo do registro
			fread(&regrem,sizeof(char),1,arquivo); 		//le o byte do campo removido
			//se o byte for '-' é pq o registro nao foi removido ainda
			if(regrem == '-'){
				encont++;
				fseek(arquivo,-1,SEEK_CUR);
				fputc('*',arquivo); 					//atualiza o campo para removido
				fwrite(&topoPilha,sizeof(int),1,arquivo);//atualiza o topo da pilha
				//transforma todos os outros campos do registro em lixo
				for(i = 0; i < 75; i++){
					fputs("@",arquivo);
				}
				rrn = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o RRN
				topoPilha = rrn;						//atualiza o topoPilha com o RRN do registro atual
				//atualiza o topoPilha no cabeçalho
				fseek(arquivo,1,SEEK_SET);
				fwrite(&topoPilha,sizeof(int),1,arquivo);

				//remove o rrn do indice também
				removedoindice(ind,max,rrn);

				break;
			}
			//se o registro já estiver removido
			else{
				fseek(arquivo,79,SEEK_CUR);
			}
		}
		//se o numero de entrada nao for igual ao numero de insc do registro atual
		else{
			fseek(arquivo,71,SEEK_CUR);
		}

		fread(&endoffile,sizeof(char),1,arquivo);
		//verifica se nao acabou o arquivo
		if(feof(arquivo)){
			if(encont == 0){	//se nao encontrou nenhum registro, retorna inexistente
				//printf("Registro inexistente.");
			}
			break;
		}
		//se nao acabou, volta 1 byte
		else{
			fseek(arquivo,-1,SEEK_CUR);
		}
	} //fim do while arquivo

	//atualiza o topoPilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fwrite(&topoPilha,sizeof(int),1,arquivo);
}

void casonotaindice(double alvo, struct indice ind[], int max, FILE* arquivo){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = inteiro para laços for
		topoPilha = inteiro para guardar o topo da pilha
		encont = inteiro para guardar a qtd de registros encontrados
		rrn = inteiro para guardar o rrn do registro removido
		nora = double para ler a nota do registro atual
		regrem = char para ler se o registro está removido ou nao
		endoffile = char para verificar se nao acabou o arquivo
	*/
	int i, topoPilha, encont = 0, rrn;
	double nora;
	char regrem, endoffile;

	//le o topo da pilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fread(&topoPilha,sizeof(int),1,arquivo);
	//vai pro começo dos registros
	fseek(arquivo,16000,SEEK_SET);
	
	//passa o arquivo inteiro até acabar
	while(arquivo){
		fseek(arquivo,9,SEEK_CUR); //pula 9 bytes para ler a nota do registro atual
		fread(&nora,sizeof(double),1,arquivo);
		//verifica se o numero da entrada é igual a nota do registro atual
		if(alvo == nora){
			fseek(arquivo,-17,SEEK_CUR); 			//volta pro começo do registro
			fread(&regrem,sizeof(char),1,arquivo); 	//le o byte do campo removido
			//se o byte for '-' é pq o registro nao foi removido ainda
			if(regrem == '-'){
				encont++;
				fseek(arquivo,-1,SEEK_CUR);
				fputc('*',arquivo); //atualiza o campo para removido
				fwrite(&topoPilha,sizeof(int),1,arquivo); //atualiza o topo da pilha
				//transforma todos os outros campos do registro em lixo
				for(i = 0; i < 75; i++){
					fputs("@",arquivo);
				}
				rrn = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o RRN
				topoPilha = rrn;						//atualiza o topoPilha com o RRN do registro atual

				//remove o rrn do indice também
				removedoindice(ind,max,rrn);

			}
			//se o registro já estiver removido
			else{
				fseek(arquivo,79,SEEK_CUR);
			}
		}
		//se o numero de entrada nao for igual a nota do registro atual
		else{
			fseek(arquivo,63,SEEK_CUR);
		}
		
		fread(&endoffile,sizeof(char),1,arquivo);
		//verifica se nao acabou o arquivo
		if(feof(arquivo)){
			if(encont == 0){	//se nao encontrou nenhum registro, retorna inexistente
				//printf("Registro inexistente.");
			}
			break;
		}
		//se nao acabou, volta 1 byte
		else{
			fseek(arquivo,-1,SEEK_CUR);
		}
	} //fim do while arquivo
	
	//atualiza o topoPilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fwrite(&topoPilha,sizeof(int),1,arquivo);
}

void casodataindice(char* alvo, struct indice ind[], int max, FILE* arquivo){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = inteiro para laços for
		topoPilha = inteiro para guardar o topo da pilha
		encont = inteiro para guardar a qtd de registros encontrados
		rrn = inteiro para guardar o rrn do registro removido
		dra = string para ler a data do registro atual
		regrem = char para ler se o registro está removido ou nao
		endoffile = char para verificar se nao acabou o arquivo
	*/
	int i, topoPilha, encont = 0, rrn;
	char dra[11], regrem, endoffile;

	//le o topo da pilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fread(&topoPilha,sizeof(int),1,arquivo);
	//vai pro começo dos registros
	fseek(arquivo,16000,SEEK_SET);
	
	dra[10] = '\0'; //coloca o ultimo byte de dra como '\0'
	
	//passa o arquivo inteiro até acabar
	while(arquivo){
		fseek(arquivo,17,SEEK_CUR); //pula 17 bytes para ler a data do registro atual
		fread(&dra,sizeof(char),10,arquivo);
		//verifica se a string da entrada é igual a data do registro atual
		if(strcmp(alvo,dra) == 0){
			fseek(arquivo,-27,SEEK_CUR); 			//volta pro começo do registro
			fread(&regrem,sizeof(char),1,arquivo); 	//le o byte do campo removido
			//se o byte for '-' é pq o registro nao foi removido ainda
			if(regrem == '-'){
				encont++;
				fseek(arquivo,-1,SEEK_CUR);
				fputc('*',arquivo); //atualiza o campo para removido
				fwrite(&topoPilha,sizeof(int),1,arquivo); //atualiza o topo da pilha
				//transforma todos os outros campos do registro em lixo
				for(i = 0; i < 75; i++){
					fputs("@",arquivo);
				}
				rrn = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o RRN
				topoPilha = rrn;						//atualiza o topoPilha com o RRN do registro atual

				//remove o rrn do indice também
				removedoindice(ind,max,rrn);
			}
			//se o registro já estiver removido
			else{
				fseek(arquivo,79,SEEK_CUR);
			}
		}
		//se a string de entraad nao for igual a data do registro atual
		else{
			fseek(arquivo,53,SEEK_CUR);
		}
		
		fread(&endoffile,sizeof(char),1,arquivo);
		//verifica se nao acabou o arquivo
		if(feof(arquivo)){
			if(encont == 0){	//se nao encontrou nenhum registro, retorna inexistente
				//printf("Registro inexistente.");
			}
			break;
		}
		//se nao acabou, volta 1 byte
		else{
			fseek(arquivo,-1,SEEK_CUR);
		}
	} //fim do while arquivo
	
	//atualiza o topoPilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fwrite(&topoPilha,sizeof(int),1,arquivo);
}

void casocidadeindice(char* alvo, struct indice ind[], int max, FILE* arquivo){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = inteiro para laços for
		topoPilha = inteiro para guardar o topo da pilha
		encont = inteiro para guardar a qtd de registros encontrados
		itcv = inteiro para armazenar o indicador de tamanho do campo variavel
		rrn = inteiro para guardar o rrn do registro removido
		cra = string para ler a data do registro atual
		regrem = char para ler se o registro está removido ou nao
		endoffile = char para verificar se nao acabou o arquivo
		tag4 = char para comparar com a tag do campo 4
	*/
	int i, topoPilha, encont = 0, itcv, rrn;
	char cra[30], regrem, endoffile, tag4;

	//le o topo da pilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fread(&topoPilha,sizeof(int),1,arquivo);
	//vai pro começo dos registros
	fseek(arquivo,16000,SEEK_SET);

	cra[29] = '\0'; //coloca o ultimo byte de cra como '\0'

	//passa o arquivo inteiro até acabar
	while(arquivo){
		fseek(arquivo,31,SEEK_CUR); //pula 31 bytes para ler a tag do primeiro campo variavel do registro atual
		fread(&tag4,sizeof(char),1,arquivo); //le o que era pra ser a tag da cidade
		//se o char lido corresponder a tag da cidade ('4')
		if(tag4 == '4'){
			fseek(arquivo,-5,SEEK_CUR); 			//volta 5 bytes para ler o indicador de tamanho do campo variavel
			fread(&itcv,sizeof(int),1,arquivo);	//le os 4 bytes seguintes e armazena o indicador de tamanho do campo variavel
			fread(&tag4,sizeof(char),1,arquivo);	//le o proximo byte e armazena em tag4
			fread(&cra,sizeof(char),itcv-1,arquivo);//le uma string do campo variavel
			//verifica se a string da entrada é igual a cidade do registro atual
			if(strcmp(alvo,cra) == 0){
				fseek(arquivo,-(31 + itcv),SEEK_CUR); 	//volta pro começo do registro
				fread(&regrem,sizeof(char),1,arquivo); 	//le o byte do campo removido
				//se o byte for '-' é pq o registro nao foi removido ainda
				if(regrem == '-'){
					encont++;
					fseek(arquivo,-1,SEEK_CUR);
					fputc('*',arquivo); //atualiza o campo para removido
					fwrite(&topoPilha,sizeof(int),1,arquivo); //atualiza o topo da pilha
					//transforma todos os outros campos do registro em lixo
					for(i = 0; i < 75; i++){
						fputs("@",arquivo);
					}
					rrn = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o RRN
					topoPilha = rrn;						//atualiza o topoPilha com o RRN do registro atual

					//remove o rrn do indice também
					removedoindice(ind,max,rrn);
				}
				//se o registro já estiver removido
				else{
					fseek(arquivo,79,SEEK_CUR);
				}
			}
			//se a string de entrada nao for igual a cidade do registro atual
			else{
				fseek(arquivo,80-(31+itcv),SEEK_CUR);
			}
		}
		//se o char lido nao for '4'
		else{
			fseek(arquivo,48,SEEK_CUR);
		}				

		fread(&endoffile,sizeof(char),1,arquivo);
		//verifica se nao acabou o arquivo
		if(feof(arquivo)){
			if(encont == 0){	//se nao encontrou nenhum registro, retorna inexistente
				//printf("Registro inexistente.");
			}
			break;
		}
		//se nao acabou, volta 1 byte
		else{
			fseek(arquivo,-1,SEEK_CUR);
		}
	} //fim do while arquivo
	
	//atualiza o topoPilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fwrite(&topoPilha,sizeof(int),1,arquivo);
}

void casonomeescolaindice(char* alvo, struct indice ind[], int max, FILE* arquivo){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = inteiro para laços for
		topoPilha = inteiro para guardar o topo da pilha
		encont = inteiro para guardar a qtd de registros encontrados
		itcv1 = inteiro para armazenar o indicador de tamanho do campo variavel
		itcv2 = inteiro para armazenar o indicador de tamanho do campo variavel
		rrn = inteiro para guardar o rrn do registro removido
		cra = string para ler a data do registro atual
		nera = string para ler o nome da escola do registro atual
		regrem = char para ler se o registro está removido ou nao
		endoffile = char para verificar se nao acabou o arquivo
		tag4 = char para comparar com a tag do campo 4
		tag5 = char para comparar com a tag do campo 5
	*/
	int i, topoPilha, encont = 0, itcv1, itcv2, rrn;
	char cra[30], nera[30], regrem, endoffile, tag4, tag5;

	//le o topo da pilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fread(&topoPilha,sizeof(int),1,arquivo);
	//vai pro começo dos registros
	fseek(arquivo,16000,SEEK_SET);

	nera[29] = '\0'; //coloca o ultimo de nera byte como '\0'
	cra[29] = '\0'; //coloca o ultimo de cra byte como '\0'

	//passa o arquivo inteiro até acabar
	while(arquivo){
		fseek(arquivo,31,SEEK_CUR); //pula 31 bytes para ler a tag do primeiro campo variavel do registro atual
		fread(&tag5,sizeof(char),1,arquivo); //le o que era pra ser a tag da cidade
		//se o char lido corresponder a tag do nomeEscola ('5')
		if(tag5 == '5'){
			fseek(arquivo,-5,SEEK_CUR); 			//volta 5 bytes para ler o indicador de tamanho do campo variavel
			fread(&itcv1,sizeof(int),1,arquivo);	//le os 4 bytes seguintes e armazena o indicador de tamanho do campo variavel
			fread(&tag5,sizeof(char),1,arquivo);	//le o proximo byte e armazena em tag5
			fread(&nera,sizeof(char),itcv1-1,arquivo);//le uma string do campo variavel					
			//verifica se a string da entrada é igual ao nome de escola do registro atual
			if(strcmp(alvo,nera) == 0){
				fseek(arquivo,-(31 + itcv1),SEEK_CUR); 	//volta pro começo do registro
				fread(&regrem,sizeof(char),1,arquivo); 	//le o byte do campo removido
				//se o byte for '-' é pq o registro nao foi removido ainda
				if(regrem == '-'){
					encont++;
					fseek(arquivo,-1,SEEK_CUR);
					fputc('*',arquivo); //atualiza o campo para removido
					fwrite(&topoPilha,sizeof(int),1,arquivo); //atualiza o topo da pilha
					//transforma todos os outros campos do registro em lixo
					for(i = 0; i < 75; i++){
						fputs("@",arquivo);
					}
					rrn = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o RRN
					topoPilha = rrn;						//atualiza o topoPilha com o RRN do registro atual

					//remove o rrn do indice também
					removedoindice(ind,max,rrn);
				}
				//se o registro já estiver removido
				else{
					fseek(arquivo,79,SEEK_CUR);
				}
			}
			//se a string de entrada nao for igual ao nome da escola do registro atual
			else{
				fseek(arquivo,80-(itcv1 + 31),SEEK_CUR);
			}
		}
		//se o char lido corresponder a tag da cidade ('4')
		else if(tag5 == '4'){
			fseek(arquivo,-5,SEEK_CUR); 			//volta 5 bytes para ler o indicador de tamanho do campo variavel
			fread(&itcv1,sizeof(int),1,arquivo);	//le os 4 bytes seguintes e armazena o indicador de tamanho do campo variavel
			fread(&tag4,sizeof(char),1,arquivo);	//le o proximo byte e armazena em tag4
			fread(&cra,sizeof(char),itcv1-1,arquivo);//le uma string do campo variavel
			fseek(arquivo,4,SEEK_CUR);			//pula 5 bytes
			fread(&tag5,sizeof(char),1,arquivo);	//le o byte e coloca em tag5
			//verifica se o byte lido é a tag do campo nomeEscola
			if(tag5 == '5'){
				fseek(arquivo,-5,SEEK_CUR);			//volta 5 bytes para ler o indicador de tamanho do campo variavel
				fread(&itcv2,sizeof(int),1,arquivo);	//le os 4 bytes seguintes e armazena o indicador de tamanho do campo variavel
				fread(&tag5,sizeof(char),1,arquivo);	//le o proximo byte e armazena em tag5
				fread(&nera,sizeof(char),itcv2-1,arquivo);//le uma string do campo variavel
				//verifica se a string da entrada é igual ao nome de escola do registro atual
				if(strcmp(alvo,nera) == 0){
					fseek(arquivo,-(itcv2 + 4 + itcv1 + 31),SEEK_CUR);	//volta pro começo do registro 
					fread(&regrem,sizeof(char),1,arquivo);				//le o byte do campo removido
					//se o byte for '-' é pq o registro nao foi removido ainda
					if(regrem == '-'){
						encont++;
						fseek(arquivo,-1,SEEK_CUR);
						fputc('*',arquivo); //atualiza o campo para removido
						fwrite(&topoPilha,sizeof(int),1,arquivo); //atualiza o topo da pilha
						//transforma todos os outros campos do registro em lixo
						for(i = 0; i < 75; i++){
							fputs("@",arquivo);
						}
						topoPilha = (ftell(arquivo) - 16000 - 80)/80;	//atualiza o topoPilha com o RRN do registro atual
					}
					//se o registro já estiver removido
					else{
						fseek(arquivo,79,SEEK_CUR);
					}	
				}
				//se a string de entrada nao for igual ao nome da escola do registro atual
				else{
					fseek(arquivo,80-(itcv2 + 4 + itcv1 + 31),SEEK_CUR);
				}
			}
			//se nao for a tag do campo nomeEscola
			else{
				fseek(arquivo,80-(itcv1 + 5 + 31),SEEK_CUR);
			}
		}
		//se o char lido nao for nem '4' nem '5'	
		else{
			fseek(arquivo,48,SEEK_CUR);
		}			

		fread(&endoffile,sizeof(char),1,arquivo);
		//verifica se nao acabou o arquivo
		if(feof(arquivo)){
			if(encont == 0){	//se nao encontrou nenhum registro, retorna inexistente
				//printf("Registro inexistente.");
			}
			break;
		}
		//se nao acabou, volta 1 byte
		else{
			fseek(arquivo,-1,SEEK_CUR);
		}
	} //fim do while arquivo
	
	//atualiza o topoPilha no cabeçalho
	fseek(arquivo,1,SEEK_SET);
	fwrite(&topoPilha,sizeof(int),1,arquivo);
}

void write_back_indice(struct indice ind[], int max, FILE* arqind){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para laços for
		cont = contador para guardar a quantidade de registros nao removidos do indice
		status = char para guardar o status (consistencia ou inconsistencia) do arquivo
	*/
	int i, j, cont = 0;
	char status;
	
	//escreve o status de inconsistente
	status = '0';
	fseek(arqind,0,SEEK_SET);
	fwrite(&status,sizeof(char),1,arqind);

	//pula pro começo dos registros
	fseek(arqind,16000,SEEK_SET);
	//passa por todos os elementos do indice
	for(i = 0; i < max; i++){
		//se o registro nao foi removido do indice, reescreve no indice e incrementa contador
		if(ind[i].rrn != -1){
			fwrite(&ind[i].nomeEscola,sizeof(char),strlen(ind[i].nomeEscola)+1,arqind);
			for(j = 0; j < 28 - (strlen(ind[i].nomeEscola) + 1); j++){
				fputs("@",arqind);
			}
			fwrite(&ind[i].rrn,sizeof(int),1,arqind);
			cont++;
		}
	}

	//deixa o arquivo consistente novamente
	status = '1';
	fseek(arqind,0,SEEK_SET);
	fwrite(&status,sizeof(char),1,arqind);
	fwrite(&cont,sizeof(int),1,arqind);
	for(i = 0; i < 15995; i++){
		fputs("@",arqind);
	}
}

int remocaoindice(char* readFile, char* indFile, int n){	
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para laços for
		vci = valor do campo inteiro
		atual = variavel do laço para ler todas as linhas de entrada
		decodvalor = inteiro para decodificar o valor do campo para o switch
		qtdregs = quantidade de registros que o indice possui
		vcf = valor do campo flutuante
		status = char para guardar o status do arquivo
		nomeCampo = string para guardar o nome do campo
		valorCampo = string para guardar o valor do campo
	*/
	int i, vci, atual, decodvalor, qtdregs;
	double vcf;
	char status, nomeCampo[n][50], valorCampo[n][50];

	trim(readFile);	//tira os \n e \r da string, se tiver

	//verifica se o arquivo readFile existe
	FILE *arqbin = fopen(readFile,"r+b");	//abre o arquivo readFile
	if(!arqbin){							//se nao conseguir abrir, retorna o erro
		printf("Falha no processamento do arquivo.");	
		return ERR_NOTFILE;
	}

	//abre o arquivo de indice
	FILE *arqind = fopen(indFile,"rb");		//abre o arquivo readFile
	if(!arqind){							//se nao conseguir abrir, retorna o erro
		printf("Falha no processamento do arquivo.");	
		return ERR_NOTFILE;
	}

	//verifica se o arquivo está consistente
	fread(&status,sizeof(char),1,arqbin);
	if(status != '1'){						//se o arquivo nao está consistente
		printf("Falha no processamento do arquivo.");
		return ERR_NOTCONSIST;
	}

	//volta um byte para reescrever o status no arquivo de entrada
	fseek(arqbin,-1,SEEK_CUR);
	//atualiza o status
	status = '0';
	fwrite(&status,sizeof(char),1,arqbin);

	//limpa as strings acima
	for(i = 0; i < n; i++){
		clearstring(nomeCampo[i],50);
		clearstring(valorCampo[i],50);
	}

	//le a quantidade de registros que o indice possui
	fseek(arqind,1,SEEK_SET);
	fread(&qtdregs,sizeof(int),1,arqind);

	//cria um vetor de struct indice para guardar o indice
	struct indice ind[qtdregs];

	//limpar a struct acima
	for(i = 0; i < qtdregs; i++){
		memset(ind[i].nomeEscola,'\0',28);
		ind[i].rrn = -1;
	}

	//le o arquivo de indice e passa pra uma struct indice
	leitura_arquivo_indice(ind, qtdregs, arqind);

	//fecha o arquivo de indice
	fclose(arqind);

	/* Laço para passar lendo a entrada n vezes */
	for(atual = 0; atual < n; atual++){
		//ler a proxima entrada
		char entrada[100];
		clearstring(entrada,100);
		fgets(entrada,100,stdin);

		trim(entrada); 		//tira o \n e o \r da entrada

		//funcao para gerar uma string nomeCampo[atual] e uma string valorCampo[atual]
		char *token = strtok(entrada, " ");
		if(!token){
			return ERR_NOTTOKEN;
		}
		for(i = 0; i < 6; i++){
			if(i == 0 && token){
				strcpy(nomeCampo[atual],token);
			}
			else if(i == 1 && token){
				strcpy(valorCampo[atual],token);
			}						
			else if(i > 1 && token){
				strcat(valorCampo[atual]," ");
				strcat(valorCampo[atual],token);
			}
			else if(!token){
				break;
			}
			token = strtok(NULL," ");
		}

		//tira os \n e \r das strings acima
		trim(nomeCampo[atual]);
		trim(valorCampo[atual]);

		//o if abaixo serve para tirar as aspas se a entrada em valorCampo for uma string
		if(valorCampo[atual][0] == '\"'){
			i = 1;
			while(valorCampo[atual][i] != '\"'){
				valorCampo[atual][i-1] = valorCampo[atual][i];
				i++;
			}
			valorCampo[atual][i-1] = '\0';
		}

		decodvalor = vctoi(nomeCampo[atual]);

		switch(decodvalor){
			//caso o valorCampo for nroInscricao
			case 1:
				//transforma o valorCampo em inteiro
				vci = strtol(valorCampo[atual],NULL,10);				
				casonumeroinscricaoindice(vci, ind, qtdregs, arqbin);
			break;
			//caso o valorCampo for nota
			case 2:
				//transforma o valorCampo em um double
				vcf = strtod(valorCampo[atual],NULL);
				casonotaindice(vcf, ind, qtdregs, arqbin);
			break;
			//caso o valorCampo for data
			case 3:		
				casodataindice(valorCampo[atual], ind, qtdregs, arqbin);
			break;
			//caso o valorCampo for cidade
			case 4:
				casocidadeindice(valorCampo[atual], ind, qtdregs, arqbin);
			break;
			//caso o valorCampo for nomeEscola
			case 5:
				casonomeescolaindice(valorCampo[atual], ind, qtdregs, arqbin);
			break;
			default:
				printf("Falha no processamento do arquivo.\n");
				return ERR_NOTVALCMP;
		} 	//acaba o switch
	}	//acaba o for de atual a n

	//abre o arquivo de indice
	FILE* arqind2 = fopen(indFile,"w+b");		//abre o arquivo readFile
	if(!arqind2){							//se nao conseguir abrir, retorna o erro
		printf("Falha no processamento do arquivo.");	
		return ERR_NOTFILE;
	}

	//escreve de volta o arquivo de indice
	write_back_indice(ind,qtdregs,arqind2);

	//volta pro primeiro byte para atualizar o status
	fseek(arqbin,0,SEEK_SET);
	//atualiza o status para consistente
	status = '1';
	fwrite(&status,sizeof(char),1,arqbin);

	//printa o arquivo no stdout com a função feita pelo monitor
	binarioNaTela1(arqind2);		

	//fecha os arquivos 
	fclose(arqbin);
	fclose(arqind2);

	return 0;
}