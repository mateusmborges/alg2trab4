/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#include "recuperacao.h"
#include "auxlib.h"

#define NAO 0
#define SIM 1

int leitura_arquivo_indice(struct indice ind[], int qtdregs, FILE* arqind){
	int paginas_indice = 0;			//inteiro para guardar quantas paginas de disco foram acessadas
	fseek(arqind,16000,SEEK_SET);	//pula pro começo dos registros
	paginas_indice++;				//incrementa os acessos
	//passa pelo arquivo de indice lendo
	for(int i = 0; i < qtdregs; i++){
		//verifica quando lê uma nova página de disco
		if((ftell(arqind) % 16000) == 0){
			paginas_indice++;
		}
		fread(&ind[i].nomeEscola,sizeof(char),28,arqind);	//le o nome da escola
		fread(&ind[i].rrn,sizeof(int),1,arqind);			//le o rrn
	}
	return paginas_indice;	//retorna a quantidade de acessos a paginas de disco do indice
}

int buscabinaria(struct indice ind[], int qtdregs, char* escola){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para laços for
		inicio = posição do inicio
		meio = posição do meio
		fim = posição do fim
		buffer = string de buffer para guardar o nome da escola lido na posicao meio
	*/
	int i, inicio, meio, fim, pos;
	char buffer[28];

	//atualiza o inicio, meio e fim, e o buffer
	inicio = 0;								//posicao do inicio é 0
	fim = qtdregs;							//posicao do fim é qtdregs
	meio = (inicio + fim)/2;				//rrn medio é o meio

	//atualiza o inicio, fim e meio até a busca ser igual	
	while(meio != fim && meio != inicio){
		memset(buffer,'\0',28);					//limpa o buffer
		strcpy(buffer,ind[meio].nomeEscola);	//le o nome da escola da posição meio e guarda no buffer
		
		//se a escola é antes do buffer
		if(strcmp(escola,buffer) < 0){
			fim = meio;								//atualiza o fim
			meio = (inicio + fim)/2;				//rrn medio é o meio
		}
		//se a escola é depois do buffer
		else if(strcmp(escola,buffer) > 0){
			inicio = meio;							//atualiza o inicio
			meio = (inicio + fim)/2;				//rrn medio é o meio
		}
		else if(strcmp(escola,buffer) == 0){
			for(pos = meio-1; pos == inicio; pos--){
				memset(buffer,'\0',28);				//limpa o buffer
				strcpy(buffer,ind[pos].nomeEscola);	//le o nome da escola da posição meio e guarda no buffer
				if(strcmp(escola,buffer) != 0){
					return pos + 1;
				}
			}
			return meio;
		}
	}
	return -1;
}

void recupera_registro(int rrn, FILE* arq){
	int nroInscricao, itcv, first = 0;
	double nota;
	char regrem, tag4, tag5;
	char data[11], campoVar[28];

	data[10] = '\0';

	fseek(arq,80*rrn,SEEK_CUR);
	fread(&regrem,sizeof(char),1,arq);
	if(regrem == '-'){
		fseek(arq,4,SEEK_CUR);
		fread(&nroInscricao,sizeof(int),1,arq);	//le os 4 bytes seguintes e coloca em nroInscricao
		//se o nroInscricao nao for nulo, printa
		if(nroInscricao != 1077952576){
			printf("%d",nroInscricao);
			first = SIM;
		}
		fread(&nota,sizeof(double),1,arq);		//le os 8 bytes seguintes e coloca em nota
		//se a nota nao for nula, printa
		if(nota != -1.0){
			//se é o primeiro a aparecer
			if(first){
				printf(" ");
			}
			printf("%.1f", nota);
			first = SIM;
		}
		fread(&data,sizeof(char),10,arq);		//le os 10 bytes seguintes e coloca em data
		//se a data nao for nula
		if(data[0] != '\0'){
			//se é o primeiro a aparecer
			if(first){
				printf(" ");
			}
			printf("%s", data);
			first = SIM;
		}
		fread(&itcv,sizeof(int),1,arq);		//le os 4 bytes seguintes e coloca em itcv
		//checa se itcv existe
		if(itcv != 1077952576){
			if(first){
				printf(" ");
			}
			first = SIM;
			printf("%d",itcv-2);						//printa o tamanho do campo variavel
			fread(&tag4,sizeof(char),1,arq);			//le o char da tag4
			fread(&campoVar,sizeof(char),itcv-1,arq);	//le o campo variavel
			printf(" %s",campoVar);						//printa o campo variavel
			fread(&itcv,sizeof(int),1,arq);				//le os 4 bytes seguintes e coloca em itcv
			//checa se itcv existe
			if(itcv != 1077952576){					
				if(first){
					printf(" ");
				}
				first = SIM;
				printf("%d",itcv-2);					//printa o tamanho do campo variavel
				fread(&tag5,sizeof(char),1,arq);		//le o char da tag5
				fread(&campoVar,sizeof(char),itcv-1,arq);//le o campo variavel 2
				printf(" %s",campoVar);					//printa o campo variavel 2
			}
		printf("\n");
		}
	}
}

int recuperacao(char* readFile){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para laços for
		acessos = contador de páginas de disco acessadas
		numReg = contador de numero de registros lidos
		encadeamento = inteiro para guardar o encadeamento
		nroInscricao = inteiro para guardar o nroInscricao
		itcv = inteiro para guardar o indicador do tamanho do campo variavel
		nota = double para guardar a nota
		status = char para guardar o status do arquivo
		regrem = char para ver se o registro é removido ou nao
		arroba = char para passar pelos @
		tag4 = char para guardar a tag 4		
		tag5 = char para guardar a tag 5		
		first = booleano para apoio ao print dos espaços
		campoVar = string para guardar o campo variavel 1
		campoVar2 = string para guardar o campo variavel 2
		data = string para guardar a data
	*/
	int i, acessos = 0, numReg = 0, encadeamento, nroInscricao, itcv;
	double nota;
	char status, regrem, arroba, tag4, tag5;
	int first = NAO;
	char campoVar[25], campoVar2[25], data[11];

	//abre o arquivo de leitura
	FILE *arqbin = fopen(readFile,"rb");	//abre o arquivo readFile
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

	//seta o ponteiro pro primeiro registro (segunda pagina)
	fseek(arqbin,16000,SEEK_SET);

	//verifica se existem registros na segunda pagina
	if(feof(arqbin)){
		printf("Registro inexistente.");
		return ERR_ARENTREG;
	}
	acessos++;	//incrementa os acessos a disco
	numReg++; 	//incrementa a qtd de registros lidos

	//seta o ponteiro pro começo do buffer
	fseek(arqbin,16000,SEEK_SET);
	acessos++; //incrementa os acessos a disco

	//limpa as strings abaixo
	clearstring(campoVar, 25);
	clearstring(campoVar2, 25);
	clearstring(data, 11);

	/* Loop para percorrer o arquivo */
	while(arqbin){
		//incrementa os acessos a disco a cada 200 registros lidos
		if(numReg >= 200){
			numReg = 0;
			acessos++;
		}

		fread(&regrem,sizeof(char),1,arqbin);	//le o char do status do registro
		//se o registro nao estiver removido
		if(regrem == '-'){
			fread(&encadeamento,sizeof(int),1,arqbin);	//le os 4 bytes seguintes e coloca em encadeamento
			fread(&nroInscricao,sizeof(int),1,arqbin);	//le os 4 bytes seguintes e coloca em nroInscricao
			//se o nroInscricao nao for nulo, printa
			if(nroInscricao != 1077952576){
				printf("%d",nroInscricao);
				first = SIM;
			}
			fread(&nota,sizeof(double),1,arqbin);		//le os 8 bytes seguintes e coloca em nota
			//se a nota nao for nula, printa
			if(nota != -1.0){
				//se é o primeiro a aparecer
				if(first){
					printf(" ");
				}
				printf("%.1f", nota);
				first = SIM;
			}
			fread(&data,sizeof(char),10,arqbin);		//le os 10 bytes seguintes e coloca em data
			//se a data nao for nula
			if(data[0] != '\0'){
				//se é o primeiro a aparecer
				if(first){
					printf(" ");
				}
				printf("%s", data);
				first = SIM;
			}
			fread(&itcv,sizeof(int),1,arqbin);		//le os 4 bytes seguintes e coloca em itcv
			//checa se itcv existe
			if(itcv != 1077952576){
				if(first){
					printf(" ");
				}
				first = SIM;
				printf("%d",itcv-2);							//printa o tamanho do campo variavel
				fread(&tag4,sizeof(char),1,arqbin);				//le o char da tag4
				fread(&campoVar,sizeof(char),itcv-1,arqbin);	//le o campo variavel
				printf(" %s",campoVar);							//printa o campo variavel
				fread(&itcv,sizeof(int),1,arqbin);		//le os 4 bytes seguintes e coloca em itcv
				//checa se itcv existe
				if(itcv != 1077952576){					
					if(first){
						printf(" ");
					}
					first = SIM;
					printf("%d",itcv-2);					//printa o tamanho do campo variavel
					fread(&tag5,sizeof(char),1,arqbin);		//le o char da tag5
					fread(&campoVar2,sizeof(char),itcv-1,arqbin);//le o campo variavel 2
					printf(" %s",campoVar2);				//printa o campo variavel 2
				}
				//se itcv nao existe
				else{
					fseek(arqbin,80-(ftell(arqbin) % 80),SEEK_CUR);	//passa pro proximo registro
				}
			}
			//se itcv nao existe
			else{
				fseek(arqbin,80-(ftell(arqbin) % 80),SEEK_CUR);		//passa pro proximo registro
			}
			printf("\n");
		}
		//se o registro estiver removido
		else{
			fseek(arqbin,79,SEEK_CUR);
		}

		int faltante = ftell(arqbin) % 80;
		if(faltante != 0){
			faltante = 80 - faltante;
		}
		fseek(arqbin,faltante,SEEK_CUR);

		//incrementa a quantidade de registros
		numReg++;

		char endoffile;
		fread(&endoffile,sizeof(char),1,arqbin);
		//verifica se o arquivo nao acabou
		if(!feof(arqbin)){
			fseek(arqbin,-1,SEEK_CUR);
		}
		else{
			break;
		}
	} //sai do loop qnd acabar o arquivo

	//printa a qtd de acessos a paginas de disco
	printf("Número de páginas de disco acessadas: %d",acessos);

	//fecha o arquivo
	fclose(arqbin);
}

int recuperacaoindice(char* readFile, char* indFile, char* nomeCampo, char* valor){
	/* 	DECLARAÇÃO DE VARIÁVEIS 
		i = variavel para laços for
		status = char para guardar o status de um arquivo
	*/
	int i, qtdregs = 0, rrn = 0, inicio = 0, media = 0, fim = 0, acessos_indice = 0, acessos_arquivo = 0, posicao_certa = 0;
	char status;
	char buffer[28];

	//abre o arquivo binario de entrada
	FILE *arqbin = fopen(readFile,"rb");	//abre o arquivo readFile
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

	//verifica se o arquivo inteiro está consistente
	fread(&status,sizeof(char),1,arqbin);
	if(status != '1'){						//se o arquivo nao está consistente
		printf("Falha no processamento do arquivo.");
		return ERR_NOTCONSIST;
	}

	//verifica se o arquivo de indice está consistente
	fread(&status,sizeof(char),1,arqind);
	if(status != '1'){						//se o arquivo nao está consistente
		printf("Falha no processamento do arquivo.");
		return ERR_NOTCONSIST;
	}

	//le a quantidade de registros que possui o arquivo de indice
	fread(&qtdregs,sizeof(int),1,arqind);

	//cria um vetor que conta quantas paginas de disco do arquivo são acessadas
	int vetor_acessos_arquivo[(qtdregs/200)+1];

	//limpa o vetor acima
	for(i = 0; i < (qtdregs/200 + 1); i++){
		vetor_acessos_arquivo[i] = 0;
	}

	//cria a struct indice com essa quantidade de registros
	struct indice ind[qtdregs];

	//limpar a struct acima
	for(i = 0; i < qtdregs; i++){
		memset(ind[i].nomeEscola,'\0',28);
		ind[i].nroInscricao = -1;
		ind[i].rrn = -1;
	}

	//le o arquivo de indice e passa pra uma struct indice, contando quantas páginas de disco foram acessadas
	acessos_indice = leitura_arquivo_indice(ind, qtdregs, arqind);

	//retorna a posicao certa do valor no 
	posicao_certa = buscabinaria(ind, qtdregs, valor);

	if(posicao_certa != -1){
		vetor_acessos_arquivo[0]++;
		while(strcmp(ind[posicao_certa].nomeEscola,valor) == 0){
			fseek(arqbin,16000,SEEK_SET);
			recupera_registro(ind[posicao_certa].rrn,arqbin);
			if(vetor_acessos_arquivo[(ind[posicao_certa].rrn/500)] == 0){
				vetor_acessos_arquivo[(ind[posicao_certa].rrn/500)]++;
			}
			posicao_certa++;
		}
	}
	else{
		printf("Registro inexistente.");
		return 0;
	}

	for(i = 0; i < (qtdregs/200 + 1); i++){
		acessos_arquivo += vetor_acessos_arquivo[i];
	}

	printf("Número de páginas de disco para carregar o arquivo de índice: %d\n",acessos_indice);
	printf("Número de páginas de disco para acessar o arquivo de dados: %d",acessos_arquivo);

	//fecha o arquivo
	fclose(arqbin);

	return 0;
}

		

