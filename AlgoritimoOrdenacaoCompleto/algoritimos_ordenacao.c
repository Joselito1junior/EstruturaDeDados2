#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define CASO_TESTE_MAX 1000000
#define QTD_TESTES 2
#define BUBBLE_SORT 1
#define SELECTION_SORT 2

#define BIG_O 1
#define BIG_THETA 2
#define BIG_OMEGA 3

enum estado {ENTRADA = 1, SAIDA};

typedef struct InfoVetor{
	int valor_inicial;
	int qtd_elementos;
	int vetorGerado[CASO_TESTE_MAX];

}t_infoVetor;

typedef struct InfoTimer{
	clock_t t_inicio;
	clock_t t_fim;
	clock_t t_decorrido;
}t_timer;

t_infoVetor vetor;

////////////////////////ASSINATURAS DE FUNÇÔES////////////////////////

void Recebe_array(t_infoVetor * vetor);
void Print_array_atual(t_infoVetor * vetor);
int Bubble_sort(t_infoVetor * vetor);
int Selection_sort(t_infoVetor * vetor);
void start_time(clock_t * t_inicio);
void end_time(clock_t * t_fim);
void calcula_time (t_timer * tempo);
void grava_log(char funcao, char estado);
char cria_caso_teste();
char MenuPrincipal(char complexidade);
void gera_vetor(int complexidade);
char SetVetor(t_infoVetor * vetor, char tipo);
void SetBigO(t_infoVetor * vetor);
void SetTheta(t_infoVetor * vetor);
void SetOmega(t_infoVetor * vetor);
void geraArquivo(t_infoVetor * vetor, int complexidade);
int save(t_infoVetor * vetor, int complexidade);
int insertion_sort(t_infoVetor * vetor);

///////////////////////////////////////////////////////////////////////
//////////////////////////////////MAIN/////////////////////////////////
int main()
{
	t_timer tempo;
	int i = 0;
	char set_vetor = 0;
	char sair = 0;

	memset(vetor.vetorGerado, 0, vetor.qtd_elementos);
	//Recebe_array(&vetor);
	

	for(i = 0; i <= QTD_TESTES; i++)
	{
		switch(i)
		{	
			case 0: sair = cria_caso_teste();
					if(sair)
						break;
					printf("Voce saiu!\n");
					return sair;
									
			case 1: grava_log(BUBBLE_SORT, ENTRADA); //função - indica a função que será realizada / estado - indica se é entrada ou saida 
					start_time(&tempo.t_inicio);
					Bubble_sort(&vetor);
					end_time(&tempo.t_fim);
					calcula_time (&tempo);
					grava_log(BUBBLE_SORT, SAIDA); //função - indica a função que será realizada / estado - indica se é entrada ou saida 
					break;

			case 2: grava_log(SELECTION_SORT, ENTRADA);
					start_time(&tempo.t_inicio);
					Selection_sort(&vetor);
					end_time(&tempo.t_fim);
					calcula_time (&tempo);
					grava_log(SELECTION_SORT, SAIDA); //função - indica a função que será realizada / estado - indica se é entrada ou saida 
					break;


		}
	}
	printf("\nFinalizado!\n");	
}

//////////////////////////////////////////////////////////////////////
//////////////////////////FUNÇÕES DE ORDENAÇÂO////////////////////////
void Recebe_array(t_infoVetor * vetor)
{
	int i = 0;

	for(i = 0; scanf("%d", &vetor->vetorGerado[i]) != EOF; i++)
	{
		if(!i) //Guarda o primeiro elemento em valor_inicial
			vetor->valor_inicial = *(vetor->vetorGerado);
	}
	vetor->qtd_elementos = i;

	printf("O elemento inicial e: %d\n", vetor->valor_inicial);
	printf("Ha %d elementos no vetor\n", vetor->qtd_elementos);
}

void Print_array_atual(t_infoVetor * vetor)
{
	int i = 0;

	for(i = 0; i < vetor->qtd_elementos; i++)
		printf("Posicao %d: %d\n", i, *(vetor->vetorGerado + i));
}

int Bubble_sort(t_infoVetor * vetor)
{
	int pos_aux = 0;
	int finaliza = 0;
	int j = 0;
	//Print_array_atual(vetor);
	do
	{
		register int i = 0;
		finaliza = 0;
		int teste;
		
		for(i = 0; i < vetor->qtd_elementos - 1; i++)
		{	
			if(*(vetor->vetorGerado + i) > *(vetor->vetorGerado + (i + 1)))
			{
				finaliza = 1;
				pos_aux = *(vetor->vetorGerado + i);
				*(vetor->vetorGerado + i) = *(vetor->vetorGerado + i + 1);
				*(vetor->vetorGerado + i + 1) = pos_aux;
			}
		}

	}while(finaliza);
}

int Selection_sort(t_infoVetor * vetor)
{
	register int i = 0, j = 0;
	int pos_aux = 0;
	int * indice_aux = NULL;
	//printf("O menor elemento e: %d\n", menor_valor);
	
	for(j = 0; j < vetor->qtd_elementos; j++)
	{
		unsigned long int menor_valor = 2114125312;

		for(i = j; i < vetor->qtd_elementos; i++)
		{	
			if(*(vetor->vetorGerado + i) < menor_valor)
			{
				menor_valor = *(vetor->vetorGerado + i);
				indice_aux = vetor->vetorGerado + i;
			}
		}

		pos_aux = *(vetor->vetorGerado + j);
		*(vetor->vetorGerado + j) = menor_valor;
		*(indice_aux) = pos_aux;							
	}
}

int insertion_sort(t_infoVetor * vetor)
{

}

void start_time(clock_t * t_inicio)
{
    *t_inicio = clock();
    //printf("\nStarting of the program, start_t = %ld\n", *t_inicio);
}

void end_time(clock_t * t_fim)
{
	*t_fim = clock();
	//printf("End of the big loop, end_t = %ld\n", *t_fim);
}

void calcula_time (t_timer * tempo)
{
	tempo->t_decorrido = ((tempo->t_fim - tempo->t_inicio) / (CLOCKS_PER_SEC / 1000));

	//printf("Tempo Decorrido em milisegundos: %ld\n", tempo->t_decorrido);// : 
	printf("Tempo Decorrido em segundos: %lf", tempo->t_decorrido / 1000.0);
}

void grava_log(char funcao, char estado)
{
	switch(estado)
	{
		case ENTRADA: printf("\n[ENTRADA] ");
				break;
		case SAIDA: printf("\n[SAIDA] ");
				break;
	}
	switch(funcao)
	{
		case 1: printf("- Bubble_sort\n");
				break;
		case 2: printf("- Selection_sort\n");
				break;
	}
}


///////////////////////////////////////////////////////////////
/////////////////GERADOR DE CASO DE TESTES/////////////////////

char cria_caso_teste()
{
	char complexidade = 0;
	
	do{
		complexidade = MenuPrincipal(complexidade);
	} while (complexidade < 0 | complexidade > 3);

	if(!complexidade)
		return 0;

	gera_vetor(complexidade);

	return complexidade;
}

char MenuPrincipal(char complexidade)
{
	printf("\n/////////////////////////\n");
	printf("Gerador de casos de teste\n");
	printf("/////////////////////////\n");
	printf("1 - Big (O) - (Pior caso)\n");
	printf("2 - Big (theta) (Caso Medio)\n");
	printf("3 - Big (Omega) (Melhor caso)\n");
	printf("0 - sair\n");
	printf("Digite uma opcao: ");
	scanf("%d", &complexidade);

	return complexidade;
}

void gera_vetor(int complexidade)
{
	char deveCriarVetor = 0;

	switch(complexidade)
	{
		case 1: printf("\nComplexidade escolhida foi: Big(O)\n");
				deveCriarVetor = SetVetor(&vetor, BIG_O);
				if(!deveCriarVetor)
				break;
				SetBigO(&vetor);
				geraArquivo(&vetor, BIG_O);
				break;
		
		case 2: printf("\nComplexidade escolhida foi: Big(Theta)\n");
				deveCriarVetor = SetVetor(&vetor, BIG_THETA);
				if(!deveCriarVetor)
				break;
				SetTheta(&vetor);
				geraArquivo(&vetor, BIG_THETA);
				break;

		case 3: printf("\nComplexidade escolhida foi: Big(Omega)\n");
				deveCriarVetor = SetVetor(&vetor, BIG_OMEGA);
				if(!deveCriarVetor)
				break;
				SetOmega(&vetor);
				geraArquivo(&vetor, BIG_OMEGA);
				break;
	}
}

char SetVetor(t_infoVetor * vetor, char tipo)
{
	vetor->qtd_elementos = 0;

	printf("\n///////////////////\n");
	printf("Configuracao do vetor\n");
	printf("///////////////////\n");

	if(tipo != 2)
	{
		if(tipo == 1)
			printf("Digite o ULTIMO valor do vetor de inteiros: ");
		else printf("Digite o PRIMEIRO valor do vetor de inteiros: ");	
		scanf("%d", &vetor->valor_inicial);
	}
	printf("Digite o tamanho do vetor de inteiros que sera gerado: ");
	scanf("%d", &vetor->qtd_elementos); 

	if(!vetor->qtd_elementos)
	{
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("ERRO - Vetores nao podem ter 0 elementos\n");
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		return 0;
	}

	if(tipo == 1)
	{
		if (!vetor->valor_inicial)
		{
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			printf("ERRO - Nessa complexidade nao e permitido iniciar em 0\n");
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			return 0;
		}

		if (vetor->qtd_elementos > vetor->valor_inicial)
		{
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			printf("ERRO - Digite um valor inicial maior ou igual ao tamanho do vetor\n");
			printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			return 0;
		}
	}
	return 1;
}

void SetBigO(t_infoVetor * vetor)
{
	int i = 0, j = 0;

	//vetor->vetorGerado = (int *) malloc(vetor->qtd_elementos * sizeof(int));

	//inicializa_vetor_gerado(vetor);

	for(i = vetor->qtd_elementos; i > 0; i--, j++)
	{
		vetor->vetorGerado[j] = vetor->valor_inicial;
		vetor->valor_inicial -= 1;
	}
}

void geraArquivo(t_infoVetor * vetor, int complexidade)
{
	int i = 0;

	save(vetor, complexidade);
}

int save(t_infoVetor * vetor, int complexidade)
{
	FILE *fp;
	register int i = 0;
	int erro = 0;
	char * nome_arquivo = NULL;

	if(complexidade ==  BIG_O)
		nome_arquivo = "BigO_PiorCaso.txt";
	else if(complexidade == BIG_THETA)
		nome_arquivo = "BigTheta_CasoMedio.txt";
	else
		nome_arquivo = "BigOmega_MelhorCaso.txt";

	
	if((fp = fopen(nome_arquivo, "w")) == NULL)
	{
		printf("O arquivo nao pode ser aberto no momento da gravacao.\n");
		return 0;
	}
	
	for(i = 0; i < vetor->qtd_elementos; i++)
	{	
		erro = fprintf(fp, "%d\n", vetor->vetorGerado[i]);
		
		if(erro < 0)
			printf("--------------------------\nErro de escrita no arquivo\n--------------------------\n");
	}
	if(erro >= 0)
		printf("--------------------------\nArquivo gerado com sucesso!\n--------------------------\n");

	fclose(fp);
}

void SetTheta(t_infoVetor * vetor)
{
	int i = 0;

	//vetor->vetorGerado = (int *) malloc(vetor->qtd_elementos * sizeof(int));

	//inicializa_vetor_gerado(vetor);

	for (i = 0; i < vetor->qtd_elementos; i++)
    {
        /* gerando valores aleatórios entre zero e 100 */
        vetor->vetorGerado[i] = rand() % 1073741820; //valor maximo de um int(4 bytes) dividido ao meio
    }
}

void SetOmega(t_infoVetor * vetor)
{
	int i = 0;

	//vetor->vetorGerado = (int *) malloc(vetor->qtd_elementos * sizeof(int));

	//inicializa_vetor_gerado(vetor);

	for(i = 0; i < vetor->qtd_elementos; i++)
	{
		vetor->vetorGerado[i] = vetor->valor_inicial;
		vetor->valor_inicial += 1;
	}
}