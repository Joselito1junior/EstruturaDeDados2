#include <stdio.h>
#include <stdlib.h>

typedef struct InfoVetor{
	int valor_inicial;
	int qtd_elementos;
	int * vetorGerado;
}t_infoVetor;



////////Assinatura de funções/////////
char MenuPrincipal(char complexidade);
char SetVetor(t_infoVetor * vetor, char tipo);
void inicializa_vetor_gerado(t_infoVetor * vetor);
int create_file();
int save(t_infoVetor * vetor);
void SetBigO(t_infoVetor * vetor);
void geraArquivo(t_infoVetor * vetor);


//////////////////////////////////////
////////////FUNÇÂO PRINCIPAL//////////
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
			case 1: printf("\ncomplexidade escolhida foi: Big(O)\n");
					deveCriarVetor = SetVetor(&vetor, 1);
					if(!deveCriarVetor)
						break;
					SetBigO(&vetor);
					geraArquivo(&vetor);
					break;

			case 2: printf("\ncomplexidade escolhida foi: Big(Theta)\n");
					SetVetor(&vetor, 2);
					break;
		}
		free(vetor.vetorGerado);
	}	
}

///////////////////////////////////////////////////////////
//////////////////////////FUNÇOES//////////////////////////
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

void geraArquivo(t_infoVetor * vetor)
{
	int i = 0;

	for(i = 0; i < vetor->qtd_elementos; i++)
	{
		printf("Valor %d: %d\n", i + 1, vetor->vetorGerado[i]);
	}

	create_file();
	save(vetor);
}

int create_file()
{
	FILE *fp;

	if((fp = fopen("CasoDeTeste.txt", "w")) == NULL)
	{
		printf("O arquivo nao pode ser aberto.\n");
		return 0;
	}
	printf("O arquivo foi  criado com sucesso!");
	
	fclose(fp);
	return 1;
}

int save(t_infoVetor * vetor)
{
	FILE *fp;
	register int i = 0;
	int erro = 0;
	
	if((fp = fopen("CasoDeTeste.txt", "w")) == NULL)
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
