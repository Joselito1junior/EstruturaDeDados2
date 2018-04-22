#include <stdio.h>
#include <stdlib.h>

////////////////////STRUCTS E VARIAVEIS////////////////////

typedef struct InfoVetor{
	int valor_inicial;
	int qtd_elementos;
	int * vetorGerado;
}t_infoVetor;

#define BIG_O 1
#define BIG_THETA 2
#define BIG_OMEGA 3


///////////////ASSINATURA DE FUNÇÔES///////////////////////
char MenuPrincipal(char complexidade);
char SetVetor(t_infoVetor * vetor, char tipo);
void inicializa_vetor_gerado(t_infoVetor * vetor);
int create_file();
int save(t_infoVetor * vetor,int complexidade);
void SetBigO(t_infoVetor * vetor);
void geraArquivo(t_infoVetor * vetor, int complexidade);
void SetOmega(t_infoVetor * vetor);
void SetTheta(t_infoVetor * vetor);


//////////////////////////////////////////////////////////
//////////////////FUNÇÂO PRINCIPAL////////////////////////

int main()
{
	char complexidade = 0;
	int * array = NULL; //Armazena o endereço do vetor gerado nas funções geradoras
	t_infoVetor vetor;

	while(1)
	{
		char deveCriarVetor = 0;
		
		do{
		complexidade = MenuPrincipal(complexidade);
		} while (complexidade < 0 | complexidade > 3);

		if(!complexidade)
			return 0;

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
		free(vetor.vetorGerado);
	}	
}



///////////////////////////////////////////////////////////
////////////////PROTOTIPOS DE FUNÇOES//////////////////////

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

void inicializa_vetor_gerado(t_infoVetor * vetor)
{
	int i = 0;

	for (i = 0; i < vetor->qtd_elementos; i++)
	{
		vetor->vetorGerado[i] = 0;
	}
}

void geraArquivo(t_infoVetor * vetor, int complexidade)
{
	int i = 0;

	for(i = 0; i < vetor->qtd_elementos; i++)
	{
		printf("Valor %d: %d\n", i + 1, vetor->vetorGerado[i]);
	}

	//create_file();
	save(vetor, complexidade);
}

int create_file()
{
	FILE *fp;

	if((fp = fopen("CasoDeTeste.txt", "w")) == NULL)
	{
		printf("O arquivo nao pode ser aberto.\n");
		return 0;
	}
	printf("O arquivo foi criado com sucesso!");
	
	fclose(fp);
	return 1;
}

int save(t_infoVetor * vetor, int complexidade)
{
	FILE *fp;
	register int i = 0;
	int erro = 0;
	char * nome_arquivo = NULL;

	if(complexidade ==  1)
		nome_arquivo = "BigO_PiorCaso.txt";
	else if(complexidade == 2)
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
			printf("Erro de escrita no arquivo");
	}
	fclose(fp);
}

void SetBigO(t_infoVetor * vetor)
{
	int i = 0, j = 0;

	vetor->vetorGerado = (int *) malloc(vetor->qtd_elementos * sizeof(int));

	inicializa_vetor_gerado(vetor);

	for(i = vetor->qtd_elementos; i > 0; i--, j++)
	{
		vetor->vetorGerado[j] = vetor->valor_inicial;
		vetor->valor_inicial -= 1;
	}
}

void SetTheta(t_infoVetor * vetor)
{
	int i = 0;

	vetor->vetorGerado = (int *) malloc(vetor->qtd_elementos * sizeof(int));

	inicializa_vetor_gerado(vetor);

	for (i = 0; i < vetor->qtd_elementos; i++)
    {
        /* gerando valores aleatórios entre zero e 100 */
        vetor->vetorGerado[i] = rand() % 1073741820; //valor maximo de um int(4 bytes) dividido ao meio
    }
}

void SetOmega(t_infoVetor * vetor)
{
	int i = 0;

	vetor->vetorGerado = (int *) malloc(vetor->qtd_elementos * sizeof(int));

	inicializa_vetor_gerado(vetor);

	for(i = 0; i < vetor->qtd_elementos; i++)
	{
		vetor->vetorGerado[i] = vetor->valor_inicial;
		vetor->valor_inicial += 1;
	}
}