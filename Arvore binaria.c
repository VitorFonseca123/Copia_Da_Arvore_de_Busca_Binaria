#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct estrutura1
{
    int chave;
    struct estrutura1 *prox;
    struct estrutura1 *ant;
} NO2;
typedef struct
{
    NO2 *cab;
} LISTA;
void inicializar(LISTA *l)
{
    l->cab = (NO2 *)malloc(sizeof(NO2));
    l->cab->prox = l->cab;
    l->cab->ant = l->cab;
}
NO2 *buscaSeqOrd(int ch, LISTA l, NO2 **ant)
{

    NO2 *p = l.cab->prox;
    *ant = l.cab;
    l.cab->chave = ch; // usa cab como sentinela
    while (p->chave < ch)
    {
        *ant = p;
        p = p->prox;
    }
    if ((p != l.cab) && (p->chave == ch))
        return (p);
    else
        return (NULL);
}
bool inserirElemListaOrd(int ch, LISTA **l)
{

    NO2 *novo;
    NO2 *ant;
    novo = buscaSeqOrd(ch, **l, &ant);
    if (novo)
        return (false);
    novo = (NO2 *)malloc(sizeof(NO2));
    novo->chave = ch;
    novo->prox = ant->prox;
    novo->ant = ant;
    novo->prox->ant = novo;
    ant->prox = novo;
    return (true);
}
void exibirLista(LISTA l)
{
    NO2 *p = l.cab->prox;
    while (p != l.cab)
    {

        printf("%d ", p->chave); // deve ser int
        p = p->prox;
    }
}

typedef struct estrutura
{
    int chave;
    struct estrutura *esq;
    struct estrutura *dir;
} NO;

void inicializarArvore(NO **raiz)
{
    *raiz = NULL;
}

bool arvoreVazia(NO *raiz)
{
    if (!raiz)
        return (true);
    else
        return (false);
}
NO *buscaNo(NO *raiz, int ch, NO **pai)
{
    NO *atual = raiz;
    *pai = NULL;
    while (atual)
    {
        if (atual->chave == ch)
            return (atual);
        *pai = atual;
        if (ch < atual->chave)
            atual = atual->esq;
        else
            atual = atual->dir;
    }
    return (NULL);
}
bool inserir(NO **raiz, int ch)
{
    NO *pai = NULL;
    NO *atual = buscaNo(*raiz, ch, &pai);
    if (atual)
        return false;
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->chave = ch;
    novo->esq = NULL;
    novo->dir = NULL;
    if (pai)
    {
        if (ch < pai->chave)
            pai->esq = novo;
        else
            pai->dir = novo;
    }
    else
        *raiz = novo;
    return true;
}
void exibir(NO *p)
{ // pré ordem

    if (p)
    {

        printf("%d ", p->chave);
        exibir(p->esq);
        exibir(p->dir);
    }
}
void copyToLista(NO *p, LISTA *l)
{
    if (p)
    {

        inserirElemListaOrd(p->chave, &l);
        copyToLista(p->esq, l);

        copyToLista(p->dir, l);
    }
}
int contarElementosL(LISTA *l)
{
    int resp = 0;
    NO2 *p = l->cab->prox;
    // printf("\n");
    while (p)
    {
        if (p == l->cab)
            break;
        // printf("%d ", p->chave);
        resp++;

        p = p->prox;
    }
    return (resp);
}
void vaiPraFrente(LISTA *l, int mediana)
{
    int cont = 1;
    NO2 *p = l->cab->prox;
    while (p)
    {
        if (p == l->cab)
            break;
        if (cont == mediana)
            break;
        cont++;
        p = p->prox;
    }
    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
    p->prox = l->cab->prox;
    p->ant = l->cab;
    l->cab->prox = p;
}
void inserirNovo(LISTA l, NO *copia)
{

    NO2 *p = l.cab->prox;
    while (p != l.cab)
    {

        inserir(copia, p->chave);

        p = p->prox;
    }
}
/*void criarArvore(LISTA l, NO **A, int nivel, NO **copia)
{
    printf("\n%d\n", nivel);
    exibir(A, nivel);
    printf("\nt");

    copyToLista(A, &l);
    exibirLista(l);
    int mediana = (contarElementosL(&l) / 2) + 1;
    // printf("%d ", mediana);
    vaiPraFrente(&l, mediana);
    printf("\n");
    exibirLista(l);
    printf("\n");
}*/
void ListaToArvore(LISTA l, NO *A)
{
    NO2 *p = l.cab->prox;
    while (p != l.cab)
    {
        // printf("%d ", p->chave); // deve ser int
        inserir(A, p->chave);
        p = p->prox;
    }
}

int altura(NO *raiz)
{
    if (raiz == NULL)
    {
        return -1;
    }
    else
    {
        int esq = altura(raiz->esq);
        int dir = altura(raiz->dir);
        if (esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}
NO *copiaCompleta(NO *raiz)
{
    //exibir(raiz);
    //printf("\n");
    
    LISTA l;
    inicializar(&l);
    copyToLista(raiz, &l);
    // printf("\n");
    // exibirLista(l);
    int mediana = (contarElementosL(&l) / 2) + 1;
    // printf("\nmediana: %d", mediana);
    vaiPraFrente(&l, mediana);
    // printf("\n");
    //  exibirLista(l);
    //  printf("\n");
    NO *copia = NULL;
    ListaToArvore(l, &copia);
    // exibir(copia, 0);
    int h_esq = altura(copia->esq);
    int h_dir = altura(copia->dir);
    //printf("\n %d %d\n", h_dir, h_esq);
    if (h_dir != h_esq)
    {
        if (h_dir > h_esq)
            copiaCompleta(copia->dir);
        if (h_esq > h_dir)
            copiaCompleta(copia->esq);

        return copia;
    }

    // exibir(raiz);
    return copia;
    // printf("\naltura:%d, %d", h_esq, h_dir);
}
int main()
{
    LISTA l;
    inicializar(&l);
    NO *A;
    NO *copia;
    inicializar(&copia);
    inicializarArvore(&A);
    int n = 7;
    int vetor[7] = {3, 1, 2, 4, 5, 6, 8};

    for (int i = 0; i < n; i++)
    {
        inserir(&A, vetor[i]);
        // inserirElemListaOrd(vetor[i], &l);
    }

    copia = copiaCompleta(A);
    exibir(copia);
    // printf("\n%d\n", nivel);
    // criarArvore(l, A, nivel, &copia);
}
