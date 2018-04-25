#include <stdio.h>
#include <stdlib.h>

#define CASO_TESTE_MAX 100000


typedef struct InfoVetor{
	int valor_inicial;
	int qtd_elementos;
	int vetorGerado[CASO_TESTE_MAX];
}t_infoVetor;


void Recebe_array(t_infoVetor * vetor);
void Print_array_atual(t_infoVetor * vetor);
int Bubble_sort(t_infoVetor * vetor);


///////////////////////////////////////////////////////////////////////
//////////////////////////////////MAIN/////////////////////////////////
int main()
{
	t_infoVetor vetor;

	Recebe_array(&vetor);
	Bubble_sort(&vetor);
}

//////////////////////////////////////////////////////////////////////
///////////////////////////////FUNÇÕES////////////////////////////////
void Recebe_array(t_infoVetor * vetor)
{
	int i = 0;

	for(i = 0; scanf("%d", &vetor->vetorGerado[i]) != EOF; i++)
	{
		if(!i); //Guarda o primeiro elemento em valor_inicial
			vetor->valor_inicial = *(vetor->vetorGerado);
	}
	vetor->qtd_elementos = i;

	printf("O elemento inicial e: %d\n", vetor->valor_inicial);
	printf("Ha %d elementos no vetor\n", vetor->qtd_elementos);
}

////////////////////////////////////////////////////////////////////////

void Print_array_atual(t_infoVetor * vetor)
{
	int i = 0;

	for(i = 0; i < vetor->qtd_elementos; i++)
		printf("Posicao %d: %d\n", i, *(vetor->vetorGerado + i));
}

////////////////////////////////////////////////////////////////////////

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

	Print_array_atual(vetor);

	printf("Finalizado!\n");
}

////////////////////////////////////////////////////////////////////////