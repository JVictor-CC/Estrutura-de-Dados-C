//Exercício 2 ED, por João Victor de Souza Pimentel Cunha.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct arvore
{
  int valor;
  struct arvore *esq;
  struct arvore *dir;
} arvore;

arvore *ler_arvore(FILE *arq)
{
  char c;
  int num;

  fscanf(arq, "%c", &c);     //ler '('
  fscanf(arq, "%int", &num); //ler a raiz

  if (num == -1) //é null?
  {
    fscanf(arq, "%c", &c);
    return NULL;
  }
  else
  {
    arvore *a;
    a = (arvore *)malloc(sizeof(arvore));
    a->valor = num;
    a->esq = ler_arvore(arq); //subesq
    a->dir = ler_arvore(arq); //subdir
    fscanf(arq, "%c", &c);    //ler')'
    return a;
  }
}

arvore *destruir(arvore *a)
{
  if (a == NULL)
    return a;
  a->esq = destruir(a->esq);
  a->dir = destruir(a->dir);
  free(a);
}

int altura(arvore *a)
{
  if (a == NULL)
    return 0;
  else
  {
    int he, hd;
    he = altura(a->esq);
    hd = altura(a->dir);

    if (he > hd)
      return he + 1;
    else
      return hd + 1;
  }
}

void nivel(arvore *a, int n) // auxilia a largura
{
  if (a != NULL)
  {
    if (n == 0)
      printf("%d ", a->valor);
    else
    {
      nivel(a->esq, n - 1);
      nivel(a->dir, n - 1);
    }
  }
}

int existe_x(arvore *a, int x)
{
  if (a == NULL)
    return 0;
  else if (a->valor == x)
    return 1;
  else if (a->valor >x)
    return existe_x(a->esq, x);
  else
    return existe_x(a->dir, x);
}


void imprimir_folhas_menores(arvore *a, int x){
  if(a!=NULL){
    if(a->valor < x) {
      if (a->esq==NULL && a->dir==NULL)
        printf("%d\n", a->valor);
      imprimir_folhas_menores(a->esq,x);
      imprimir_folhas_menores(a->dir,x);
    }
    else
      imprimir_folhas_menores(a->esq, x);
  }
}

void imprimir_nivel(arvore *a, int cont, int x)
{
  if (a != NULL)
  {
    if (a->valor == x)
      printf("\nO no %d esta no nivel %d \n\n\n", x, cont);
    else if(a->valor < x)
    {
      imprimir_nivel(a->dir, cont + 1, x);
    }
    else
    {
      imprimir_nivel(a->esq, cont + 1, x);
    }
  }
}

void imprimir_pre_ordem(arvore *a)
{
  if (a != NULL)
  {
    printf("%d ", a->valor);
    imprimir_pre_ordem(a->esq);
    imprimir_pre_ordem(a->dir);
  }
  else
    printf("(-1) ");
}

void imprimir_em_ordem(arvore *a)
{
  if (a != NULL)
  {
    imprimir_em_ordem(a->esq);
    printf("%d ", a->valor);
    imprimir_em_ordem(a->dir);
  }
  else
    printf("(-1) ");
}

void imprimir_pos_ordem(arvore *a)
{
  if (a != NULL)
  {
    imprimir_pos_ordem(a->esq);
    imprimir_pos_ordem(a->dir);
    printf("%d ", a->valor);
  }
  else
    printf("(-1) ");
}

void imprimir_em_largura(arvore *a)
{
    int h;
    h= altura(a);
    int i;
    for(i=0; i<h; i++)
    {
        nivel(a, i);
    }
}

arvore *inserir(arvore *a, int x){

    if(a==NULL){
        a=(arvore*)malloc(sizeof(arvore));
        a->valor=x;
        a->esq=NULL;
        a->dir=NULL;
    }else if(x<=a->valor){
        a->esq=inserir(a->esq,x);
    }else{
        a->dir=inserir(a->dir,x);
    }
    return a;

}

arvore *remover(arvore *a, int x){
    if(a!=NULL)
        if(a->valor==x)
            if(a->esq == NULL && a->dir==NULL){
                free(a);
                return NULL;
            }else if(a->esq==NULL){
                arvore *aux = a->dir;
                free(a);
                return aux;
            }else if(a->dir==NULL){
                arvore*aux=a->esq;
                free(a);
                return aux;
            }else{
                arvore*aux=a->esq;
                while(aux->dir!=NULL)
                    aux=aux->dir;

                a->valor=aux->valor;
                a->esq=remover(a->esq,aux->valor);
            }else if(x<a->valor)
                a->esq=remover(a->esq,x);
            else
                a->dir=remover(a->dir,x);
    return a;
}

int intermediarios(arvore *a, int x, int y){
	int cont = 0;
	if(a == NULL){
		return 0;
	}
	if(a->valor < x){
    printf("%d fora\n",a->valor);
    cont += intermediarios(a->dir, x, y);
    return cont;
  }else if(a->valor > y){
    printf("%d fora\n",a->valor);
    cont += intermediarios(a->esq, x, y);
    return cont;
  }
  else{
        cont++;
        printf("%d\n", a->valor);
        cont += intermediarios(a->esq, x, y);
        cont += intermediarios(a->dir, x, y);
        return cont;
	}
}

int Similares(arvore *a, arvore *b){
    if(a == NULL || b == NULL){
        if(a == NULL && b == NULL){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        int esq, dir;
        esq = Similares( a->esq, b->esq);
        dir = Similares( a->dir, b->dir);
        if (esq == 0 || dir == 0){
            return 0;
        }
        else{
            return 1;
        }
    }
}

int menu(arvore *a,arvore *b)
{
  char nomarq[30];
  int op, x, folha,y;
  FILE *arq;

  while (op != 1000)
  {
    system("cls");
    printf("Escolha uma das opcoes:\n\n");
    printf("1 - Ler Arvore\n\n");
    printf("2 - Imprimir Arvore\n\n");
    printf("3 - Procurar Por Um Elemento\n\n");
    printf("4 - Imprimir o Nivel De Um No\n\n");
    printf("5 - Imprimir Nos Folhas Menores que um valor x.\n\n");
    printf("6 - Inserir no na Arvore\n\n");
    printf("7 - Remover no da Arvore\n\n");
    printf("8 - Checar Nós Entre Dois Valores(X e Y)\n\n");
    printf("9 - Checar Se Duas Arvores São Similares\n\n");
    printf("10 - Sair\n\n");
    scanf("%d", &op);
    system("cls");
    switch (op)
    {
    case 1:
      do
      {
        printf("Digite o nome do arquivo(.txt): ");
        scanf("%s", nomarq);
        fflush(stdin);
        arq = fopen(nomarq, "rt");
      } while (arq == NULL);

      a = ler_arvore(arq);
      fclose(arq);
      printf("\n\n\nArvore Carregada!!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
      system("pause");
      break;

    case 2:
      printf("Escolha uma forma de ordenacao:\n");
      do
      {
        printf("1 - Pre-ordem\n");
        printf("2 - Em-ordem\n");
        printf("3 - Pos-Ordem\n");
        printf("4 - Largura\n");
        printf("5 - Voltar\n");

        scanf("%d", &x);
        fflush(stdin);
        if (x < 1 || x > 4)
        {
          printf("Digite uma opcao valida!\n");
        }

        switch (x)
        {
        case 1:
          printf("Pre Ordem:\n");
          imprimir_pre_ordem(a);
          printf("\n\n\n");
          system("pause");
          break;

        case 2:
          printf("\nEm Ordem:\n");
          imprimir_em_ordem(a);
          printf("\n\n\n");
          system("pause");
          break;

        case 3:
          printf("\nPos Ordem:\n");
          imprimir_pos_ordem(a);
          printf("\n\n\n");
          system("pause");
          break;

        case 4:
          printf("\nEm Largura\n");
          imprimir_em_largura(a);
          printf("\n\n\n");
          system("pause");
          break;
        }

      } while (x != 5);

      break;

    case 3:

      printf("Digite o numero que quer procurar:\n");
      scanf("%d", &x);
      if (existe_x(a, x) == 1)
      {
        printf("\nEste numero pertence a arvore.\n\n\n");
      }
      else
      {
        printf("\nEste numero nao pertence a arvore.\n\n\n");
      }
      system("pause");
      break;

    case 4:
        printf("Voce deseja saber o nivel de qual no?\n");
      scanf("%d", &x);
      if (existe_x(a, x) == 1){
        imprimir_nivel(a, 0, x);
      }
    system("pause");
      break;

    case 5:
      printf("Digite o valor:\n");
      scanf("%d", &x);
      printf("\n\n");
      imprimir_folhas_menores(a,x);
      printf("\n\n");
      system("pause");
      break;

    case 6:
        printf("Qual Valor Deseja Inserir:\n");
        scanf("%d", &x);
        a=inserir(a,x);
        system("pause");
      break;

    case 7:
        printf("Qual Valor Deseja Remover:\n");
        scanf("%d", &x);
        a=remover(a,x);
        system("pause");
      break;

    case 8:
        printf("Digite os valores: ");
        scanf("%d %d",&x,&y);
        printf("\n\n");
        printf("\nExistem %d nos entre esses valores\n",intermediarios(a,x,y));
        system("pause");
      break;
    case 9:
        if(Similares(a,b)==0){
            printf("As Arvores Nao Sao Similares\n\n");
        }
        else{
            printf("As Arvores Sao Similares");
        }
        system("pause");
        break;

    case 10:
        a = destruir(a);
        return 0;
        break;

    default:
      printf("\n\nDigite uma opcao valida\n\n\n\n\n");
      system("pause");
      break;
    }
  }
}

int main()
{
    FILE *arqb;
    arvore *a = NULL;
    arvore *b = NULL;
    arqb = fopen("AVL.txt", "rt");
    b = ler_arvore(arqb);
    fclose(arqb);
  menu(a,b);

  return 0;
}
