/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328

	Aluno: Natã Daniel Gomes de Almeida
	NUSP: 10851666 
* * * * * * * * * * * * * * * * * * */

#include "estatisticas.h"
#include "recuperacao.h"
#include "auxlib.h"

int estatisticas(char *arqentrada, char *arqindice, char *nomeCampo, char *valor){
    /* 	DECLARAÇÃO DE VARIÁVEIS 
		acessos = conta a quantidade de paginas de disco acessadas na funcionalidade 3 (arquivo inteiro)
        acessos12 = conta a quantidade de páginas de disco acessadas na funcionalidade 12 (arquivo de indice)
        certos = conta quantas vezes achou algum registro que satisfaça o valor dado
        buffercv = buffer para indicador de tamanho de campo variavel
        rrn = RRN relacionado ao registro que é pra ser buscado
        faltante = quantos bytes faltam para acabar o registro
        diferenca = a diferenca entre os acessos da funcionalidade 3 e da 12
        status = char que armazena o status do arquivo
        regrem = char que armazena o status do registro
        tag = char que armazena as tags dos campos variaveis dos registros
        valorCampo = string que armazena o valor do campo nome escola dos registros
	*/
    int acessos = 0, acessos12 = 0, certos = 0, buffercv, rrn = 0, faltante, diferenca;
    char status, regrem, tag, valorCampo[30];

    valorCampo[29] = '\0'; //anula o ultimo byte

    //abre o arquivo de leitura
    FILE *arqbin = fopen(arqentrada, "rb"); //abre o arquivo readFile
    if (!arqbin)
    { //se nao conseguir abrir, retorna o erro
        printf("Falha no processamento do arquivo.");
        return 0;
    }

    //abre o arquivo de indice
    FILE *arqind = fopen(arqindice, "rb"); //abre o arquivo readFile
    if (!arqind)
    { //se nao conseguir abrir, retorna o erro
        printf("Falha no processamento do arquivo.");
        return 0;
    }

    //verifica a integridade do arquivo (le o primeiro byte se eh '0')
    fseek(arqbin,0,SEEK_SET);
    fread(&status,sizeof(char),1,arqbin);
    if(status != '1'){
        printf("Falha no processamento do arquivo.");
        return 0;
    }

    //verifica a integridade do arquivo (le o primeiro byte se eh '0')
    fseek(arqind, 0, SEEK_SET);
    fread(&status, sizeof(char), 1, arqind);
    if (status != '1')
    {
        printf("Falha no processamento do arquivo.");
        return 0;
    }

    //le a proxima pagina de disco
    fseek(arqbin,16000,SEEK_SET);

    //printa a primeira linha da especificação
    printf("*** Realizando a busca sem o auxílio de índice\n");

    //enquanto tiver arquivo a ser lido
    while(arqbin){
        //verifica se uma nova pagina de disco foi acessada
        if (((ftell(arqbin) - 16001) / 80) % 200 == 0)
        {
            acessos++; //incrementa o numero de acessos a disco
        }

        fread(&regrem,sizeof(char),1,arqbin);   //le o status do registro
        //se o arquivo acabou
        if(feof(arqbin)){
            if (certos > 0)
            { //se tiver achado algum registro correspondente, printa o numero de paginas acessadas
                printf("Número de páginas de disco acessadas: %d\n", acessos);
                break;
            }
            else
            { //se nao tiver achado, entao printa registro inexistente
                printf("Registro inexistente.");
                break;
            }
        }

        //se o registro nao estiver removido
        if(regrem == '-'){    
            fseek(arqbin,26,SEEK_CUR);	//pula 27 bytes
            fread(&buffercv,sizeof(int),1,arqbin);//le o tamanho do campo variavel, se tiver
            fread(&tag,sizeof(char),1,arqbin);//le a tag
            //se a tag for do campo cidade
            if(tag == '4'){
                fseek(arqbin, buffercv - 1, SEEK_CUR);  //pula pro proximo campo variavel
                fread(&buffercv,sizeof(int),1,arqbin);  //le o tamanho do campo variavel, se tiver
                fread(&tag, sizeof(char), 1, arqbin);   //le a tag
                //se a tag for do campo nomeEscola
                if(tag == '5'){
                    fread(&valorCampo,sizeof(char),buffercv-1,arqbin);  //le o nome da escola desse registro
                    //verifica se o nome da escola lido do registro corresponde ao nome escola dado na entrada
                    if(strcmp(valorCampo,valor) == 0){
                        rrn = (ftell(arqbin)- 16001 ) / 80; //calcula o rrn desse registro
                        certos++;                           //incrementa a quantidade de registros correspondentes
                        recupera_registro(rrn,arqbin);      //printa o registro
                    }
                }
            }
            //se a tag for do campo nomeEscola
            else if(tag == '5'){
                fread(&valorCampo, sizeof(char), buffercv - 1, arqbin); //le o nome da escola desse registro
                //verifica se o nome da escola lido do registro corresponde ao nome escola dado na entrada
                if (strcmp(valorCampo, valor) == 0){
                    rrn = (ftell(arqbin) - 16001) / 80;     //calcula o rrn desse registro
                    certos++;                               //incrementa a quantidade de registros correspondentes
                    recupera_registro(rrn, arqbin);         //printa o registro
                }
            }

            //pula pro proximo registro
            faltante = ftell(arqbin) % 80;
            if (faltante > 0)
            {
                fseek(arqbin, 80 - (ftell(arqbin) % 80), SEEK_CUR);
            }       
        }
        //se o registro estiver removido
        else if(regrem == '*'){
            fseek(arqbin,79,SEEK_CUR);
        }

    } //acaba loop while

    //fecha o arquivo
    fclose(arqbin);

    //printa a linha da especificação
    printf("\n*** Realizando a busca com o auxílio de um índice secundário fortemente ligado\n");

    //chama a funcionalidade 12 e calcula a quantidade de paginas de disco que foram acessadas com o auxilio do indice
    acessos12 = recuperacaoindice(arqentrada,arqindice,nomeCampo,valor);

    //calcula a diferença entre eles
    diferenca = acessos - acessos12;

    //printa a diferença
    printf("\n\nDiferença no número de páginas de disco acessadas: %d",diferenca);

    return 0;
}
