// Exercício 5, por João Victor de Souza Pimentel Cunha. 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int totalElementos = 0;

int indiceFilhoEsq(int x){
  int indice = (2*x)+1;
  if(x>totalElementos||indice>=totalElementos)
    return -1;
  else
    return indice;
}

int indiceFilhoDir(int x){
  int indice = (2*x)+2;
  if(x>totalElementos||indice>=totalElementos)
    return -1;
  else
    return indice;
}

int indicePai(int x){
  int indice = (int) floor((x-1)/2);
  if(x<=0 || x>= totalElementos)
    return -1;
  else
    return indice;
}

void ajustarSubindo(int *heap, int pos){
  if( pos != -1){
    int pai = indicePai(pos);
    if( pai != -1){
      if( heap[pos] < heap[pai]){
        int aux = heap[pos];
        heap[pos] = heap[pai];
        heap[pai] = aux;
        ajustarSubindo(heap,pai);

      }
    }
  }
}

void ajustarDescendo(int *heap, int pos){
  if( pos != -1 && indiceFilhoEsq(pos)!= -1){
    int indiceMenorFilho = indiceFilhoEsq(pos);
    if( indiceFilhoDir(pos) != -1 && heap[indiceMenorFilho] > heap[indiceFilhoDir(pos)])
      indiceMenorFilho = indiceFilhoDir(pos);

    if(heap[indiceMenorFilho] < heap[pos]){
      int aux = heap[pos];
      heap[pos] = heap[indiceMenorFilho];
      heap[indiceMenorFilho] = aux;
      ajustarDescendo(heap, indiceMenorFilho);
    }
  }
}

void inserir(int *heap, int x){
  heap[totalElementos] = x;
  totalElementos++;

  ajustarSubindo(heap, totalElementos-1);
}

int remover(int *heap){
  if(totalElementos == 0)
    return -1;
  else {
    int retorno = heap[0];
    heap[0] = heap[totalElementos-1];
    totalElementos--;
    ajustarDescendo(heap,0);
    return retorno;
  }
}

int main(){

  int heap[10];
  int n=0,x,i;

  printf("Considere um heap de 10 elementos\n");
  printf("1- Inserir Elemento\n");
  printf("2- Remover Elemento\n");
  printf("3- Imprimir Heap\n");
  printf("4- sair \n");


  while(n>-1){
    printf("O que deseja fazer: ");
    scanf("%d",&n);
    switch (n)
    {
      case 1:
        printf("Insira o valor que deseja adicionar ao heap: ");
        scanf("%d", &x);
        inserir(heap,x);
        printf("\n\n");
        break;
    
      case 2:
        x = remover(heap);
        printf("O valor removido foi: %d\n", x);
        printf("\n\n");
        break;
      
      case 3:
        printf("Os valores do heap sao: \n");
        for (i=0;i<totalElementos;i++)
          printf("%d ", heap[i]);
        printf("\n\n");
        break;

      case 4:
        return 0;
    }
  }
}