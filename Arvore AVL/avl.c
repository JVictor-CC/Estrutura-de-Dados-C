//Exercício 3 ED, por João Victor de Souza Pimentel Cunha.

#include <stdlib.h>
#include <stdio.h>


typedef struct arvore
{
  int valor;
  int FB;
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

void ajustarfb(arvore *a){
    if(a!=NULL){
        int he,hd;
        he=altura(a->esq);
        hd=altura(a->dir);
        a->FB=hd-he;
        ajustarfb(a->esq);
        ajustarfb(a->dir);
    }
}

arvore *leravl(FILE *arq){
    arvore *a = ler_arvore(arq);
    ajustarfb(a);
    return a;
}

arvore *destruir(arvore *a)
{
  if (a == NULL)
    return a;
  a->esq = destruir(a->esq);
  a->dir = destruir(a->dir);
  free(a);
}



void auxlarg(arvore *a, int n) // auxilia a largura
{
  if (a != NULL)
  {
    if (n == 0)
      printf("%d \t", a->valor);
    else
    {
      auxlarg(a->esq, n - 1);
      auxlarg(a->dir, n - 1);
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
        auxlarg(a, i);
        printf("\n");
    }
}

arvore *RotacaoDirSimples (arvore *r)
{
    arvore *a = r->esq;
    arvore *b = r;
    b->esq = a->dir;
    a->dir = b;
    if (a->FB == -1){
        a->FB = 0;
        b->FB = 0;
    }
    else
    {
        a->FB = 1;
        b->FB = -1;
    }
    r = a;
    return r;
}

arvore *RotacaoDirDupla(arvore *r)
{
    arvore *c = r;
    arvore *a = c->esq;
    arvore *b = a->dir;
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;
    switch(b->FB){
        case -1:
            a->FB = 0;
            c->FB = 1;
            break;
        case 0:
            a->FB = 0;
            c->FB = 0;
            break;
        case +1:
            a->FB = -1;
            c->FB = 0;
            break;
    }
    b->FB = 0;
    r = b;
    return r;
}

arvore *RotacaoDir (arvore *r)
{
  if (r->esq->FB == 1)
    r = RotacaoDirDupla(r);
  else
    r = RotacaoDirSimples(r);
  return r;
}

arvore *RotacaoEsqSimples (arvore *r)
{
    arvore *a = r;
    arvore *b=a->dir;
    a->dir = b->esq;
    b->esq = a;
    if (b->FB == 1){
        a->FB = 0;
        b->FB = 0;
    }
    else
    {
        a->FB = 1;
        b->FB = -1;
    }
    r=b;
    return r;
}

arvore *RotacaoEsqDupla(arvore *r)
{
    arvore *a = r;
    arvore *c = a->dir;
    arvore *b = c->esq;
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;
    switch(b->FB){
        case -1:
            a->FB = 0;
            c->FB = 1;
            break;
        case 0:
            a->FB = 0;
            c->FB = 0;
            break;
        case +1:
            a->FB = -1;
            c->FB = 0;
            break;
    }
    b->FB = 0;
    r = b;
    return r;
}

arvore *RotacaoEsq (arvore *r)
{
  if (r->dir->FB == -1)
    r =  RotacaoEsqDupla(r);
  else
    r = RotacaoEsqSimples(r);
  return r;
}

arvore *Inserir(arvore *r, int x, int *hMudou)
{
  if (r == NULL){
  r = (arvore*) malloc (sizeof(arvore));
  r->valor = x;
  r->esq = NULL;
  r->dir = NULL;
  r->FB = 0;
  *hMudou = 1;
  } else{
    if (x <= r->valor){
      r->esq = Inserir (r->esq,x,hMudou);
      if (*hMudou == 1){
        switch (r->FB){
          case -1:
            r = RotacaoDir(r);
            *hMudou = 0;
            break;
          case 0:
            r->FB = -1;
            *hMudou = 1;
            break;
          case +1:
            r->FB = 0;
            *hMudou = 0;
            break;
        }
      }
    }
  else
  {
  r->dir = Inserir (r->dir,x,hMudou);
  if (*hMudou == 1){
        switch (r->FB){
          case -1:
            r->FB = 0;
            *hMudou = 0;
            break;
          case 0:
            r->FB = +1;
            *hMudou = 1;
            break;
          case +1:
            r = RotacaoEsq (r);
            *hMudou = 0;
            break;
        }
      }
    }
  }
  return r;
}

arvore *Remover (arvore *r, int x, int *hMudou)
{
  if (r != NULL){
    if (r->valor == x){
      //Verificar se é folha
      if (r->esq == NULL && r->dir == NULL){
        free (r);
        *hMudou = 1;
        return NULL;
      }
      //Verificar se um dos filhos é nulo
      else if (r->esq == NULL || r->dir == NULL){
        arvore *aux;
        if (r->esq == NULL)
        aux = r->dir;
        else
        aux = r->esq;
        free(r);
        *hMudou = 1;
        return aux;
      }
      //Nenhum filho nulo
      else{
        arvore *maiorEsq = r->esq;
        while (maiorEsq->dir != NULL)
          maiorEsq = maiorEsq->dir;
        r->valor = maiorEsq->valor;
        r->esq = Remover(r->esq,r->valor,hMudou);
        if (*hMudou == 1){
          switch(r->FB){
            case -1:
              r->FB = 0;
              *hMudou = 1;
              break;

            case 0:
              r->FB = 1;
              *hMudou = 0;
              break;

            case +1:
            {
              int aux = r->dir->FB;
              r = RotacaoEsq(r);
              if (aux == 0)
                *hMudou = 0;
              else
                *hMudou = 1;
              break;
            }
          }
        }
      }
    }
    else if (x < r->valor){
      r->esq = Remover(r->esq, x, hMudou);
      if (*hMudou == 1){
        switch(r->FB)
        {
          case -1:
            r->FB = 0;
            *hMudou = 1;
            break;

          case 0:
            r->FB = 1;
            *hMudou = 0;
            break;

          case +1:
          {
            int aux = r->dir->FB;
            r = RotacaoEsq(r);
            if (aux == 0)
              *hMudou = 0;
            else
              *hMudou = 1;
            break;
          }
        }
      }
    }else {
      r->dir = Remover(r->dir, x, hMudou);
      if (*hMudou == 1){
        switch(r->FB){
          case +1:
            r->FB = 0;
            *hMudou = 1;
            break;
          case 0:
            r->FB = -1;
            *hMudou = 0;
            break;
          case -1:
          {
            int aux = r->esq->FB;
            r = RotacaoDir(r);
            if (aux == 0)
              *hMudou = 0;
            else
              *hMudou = 1;
            break;
          }
        }
      }
    }
    return r;
  }
}


int menu(arvore *a)
{
  char nomarq[30];
  int op, x, folha;
  int h=0;
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
    printf("8 - Sair\n\n");
    fflush(stdin);
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

      a = leravl(arq);
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
        a=Inserir(a,x,&h);
        system("pause");
      break;

    case 7:
        printf("Qual Valor Deseja Remover:\n");
        scanf("%d", &x);
        a=Remover(a,x,&h);
        system("pause");
      break;

    case 8:
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
  arvore *a = NULL;
  menu(a);

  return 0;
}
