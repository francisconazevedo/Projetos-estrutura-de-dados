# include <windows.h>
# include <stdlib.h>
# include <stdio.h>
# include "AVL-funcoes.h"

void criaGalhoNulo(arv**raiz)
{
    *raiz = NULL;
}

void galho(arv**raiz, int elemento, int pos)
{
    *raiz = (arv*)malloc(sizeof(arv));
    (*raiz)->num = elemento;
    (*raiz)->linha_arquivo = pos;
    (*raiz)->esq = NULL;
    (*raiz)->dir = NULL;

}

int insereElemento(arv**raiz, int elemento, int pos)
{
    int retorno = 1;
    if(*raiz == NULL)
    {
        galho(&*raiz, elemento,pos);
    }
    else
    {
        if((*raiz)->num > elemento)
        {
            retorno = insereElemento(&(*raiz)->esq,elemento, pos);
            if(balanceamento(*raiz) < -1 || balanceamento(*raiz) > 1)
            {
                if(elemento < (*raiz)->esq->num)
                {
                    aviso();
                    *raiz = rotacaoDireita(*raiz);
                    return 1;
                }
                else
                {
                    aviso1();
                    *raiz = duplaEsquerda(*raiz);
                    return 1;
                }
            }
        }
        if((*raiz)->num < elemento)
        {
            retorno = insereElemento(&(*raiz)->dir,elemento, pos);
            if(balanceamento(*raiz) < -1 || balanceamento(*raiz) > 1)
            {
                if(elemento > (*raiz)->dir->num)
                {
                    aviso2();
                    *raiz = rotacaoEsquerda(*raiz);
                    return 1;
                }
                else
                {
                    aviso3();
                    *raiz = duplaDireita(*raiz);
                    return 1;
                }
            }
        }
        if((*raiz)->num == elemento)
        {
            mensagem();
            return 0;
        }
    }

    return retorno;
}

void impressao(arv*raiz)
{
    if(raiz!=NULL)
    {
        printf("(");
        printf("%d",(raiz)->num);
        printf(",(");
        impressao(raiz->esq);
        printf("),(");
        impressao(raiz->dir);
        printf(")");
        printf(")");

    }
}

arv** menorDireito(arv*raiz)
{
    arv** aux = &raiz;
    if((*aux)->dir != NULL)
    {
        aux = &(*aux)->dir;
        while((*aux)->esq != NULL)
        {
            aux = &(*aux)->esq;
        }
    }
    return aux;
}


arv** maiorEsquerdo(arv*raiz)
{
    arv** aux = &raiz;
    if((*aux)->esq != NULL)
    {
        aux = &(*aux)->esq;
        while((*aux)->dir != NULL)
        {
            aux = &(*aux)->dir;
        }
    }
    return aux;
}


int busca(arv *raiz, int elemento)
{
    if(raiz != NULL)
    {
        if((raiz)->num > elemento)
        {
            printf("%d,",raiz->num);
            return busca(raiz->esq, elemento);

        }
        else
        {
            if(raiz->num < elemento)
            {
                printf("%d,",raiz->num);
                return busca(raiz->dir, elemento);

            }
            else
            {
                if(raiz->num == elemento)
                {
                    printf("%d",raiz->num);
                    return raiz->linha_arquivo;
                }
            }
        }

    }
    else
    {
        printf ("\nEsses sao os codigos existentes no banco.");
        printf("\nNumero nao encontrado!");
        getch();
        system("cls");

    }
    return -1;
}


void excluirElemento(arv**raiz, int elemento, int pos)
{
    arv **aux1, *aux2;
    arv* aux = *raiz;

    if(*raiz != NULL)
    {
        if((*raiz)->num == elemento)
        {
            if((*raiz)->esq == (*raiz)->dir)
            {
                printf("\nr = %d\n",elemento);
                free(*raiz);
                *raiz = NULL;
            }
            else
            {
                if((*raiz)->esq != NULL)
                {
                    aux1 = maiorEsquerdo(*raiz);
                    aux2 = *aux1;
                    (*aux1) = (*aux1)->esq;
                }
                else
                {
                    aux1 = menorDireito(*raiz);
                    aux2 = *aux1;
                    (*aux1) = (*aux1)->dir;
                }
                (*raiz)->num = aux2->num;
                (*raiz)->linha_arquivo = aux2->linha_arquivo;
                free(aux2);
                aux2 = NULL;
            }
        }
        else
        {
            if((*raiz)->num < elemento)
            {
                excluirElemento(&(*raiz)->dir,elemento, pos);
                atualizaEsq(&(*raiz),elemento);
            }
            if((*raiz)->num > elemento)
            {
                excluirElemento(&(*raiz)->esq,elemento, pos);
                atualizaDir(&(*raiz),elemento);
            }
        }
    }
    else
    {
        printf("Numero nao encontrado!!");
        getch();
        system("cls");
    }

}



int contEsq(arv*raiz)
{
    arv* aux = raiz;
    int cont = 0;

    if(aux->esq == NULL)
    {
        return 0;
    }
    else
    {
        while(aux->esq != NULL)
        {
            aux = aux->esq;
            cont = cont + 1;
            if(aux->esq == NULL && aux->dir != NULL)
            {
                while(aux->dir != NULL)
                {
                    cont = cont + 1;
                    aux = aux->dir;
                }
            }
        }
        return cont;
    }
}

int contDir(arv*raiz)
{
    arv* aux = raiz;
    int cont = 0;
    if(aux->dir == NULL)
    {
        return 0;
    }
    else
    {
        while(aux->dir != NULL)
        {
            aux = aux->dir;
            cont = cont + 1;
            if(aux->dir == NULL && aux->esq != NULL)
            {
                while(aux->esq != NULL)
                {
                    cont = cont + 1;
                    aux = aux->esq;
                }
            }
        }
        return cont;
    }
}

int balanceamento(arv*raiz)
{
    arv* aux = raiz;
    int bl = 0;
    bl = contDir(aux) - contEsq(aux);
    return bl;
}

arv* duplaEsquerda(arv*raiz)
{
    arv* aux = raiz;
    aux->esq = rotacaoEsquerda(aux->esq);
    aux = rotacaoDireita(aux);
    return aux;
}

arv* duplaDireita(arv*raiz)
{
    arv* aux = raiz;
    aux->dir = rotacaoDireita(aux->dir);
    aux = rotacaoEsquerda(aux);
    return aux;
}

arv* rotacaoDireita(arv*raiz)
{
    arv* aux = raiz;
    arv* A = aux;
    arv* B = aux->esq;
    A->esq = B->dir;
    B->dir = A;
    return B;
}

arv* rotacaoEsquerda(arv*raiz)
{
    arv* aux = raiz;
    arv* A = aux;
    arv* B = aux->dir;
    A->dir = B->esq;
    B->esq = A;
    return B;
}

void atualizaDir(arv**raiz, int elemento)
{
    arv* aux1 = (*raiz)->dir;
    arv* aux = *raiz;

    while((aux) != NULL)
    {
        if(balanceamento(aux) < -1 || balanceamento(aux) > 1)
        {
            if(aux1->dir != NULL)
            {
                *raiz = rotacaoEsquerda(*raiz);
                break;
            }
            else
            {
                *raiz = duplaDireita(*raiz);
                break;
            }

        }
        (aux) = (aux)->dir;
    }
}

void atualizaEsq(arv**raiz, int elemento)
{
    arv* aux1 = (*raiz)->esq;
    arv* aux = *raiz;

    while(aux != NULL)
    {
        if(balanceamento(aux) < -1 || balanceamento(aux) > 1)
        {
            if(aux1->esq == NULL)
            {
                *raiz = duplaEsquerda(*raiz);
                break;
            }
            else
            {

                *raiz = rotacaoDireita(*raiz);
                break;
            }
        }
        (aux) = (aux)->esq;
    }
}


void aviso()
{
    printf("AVISO! Sera realizado uma rotacao simples a direita!");
    getch();
    system("cls");
}

void aviso1()
{
    printf("AVISO! Sera realizado uma rotacao dupla a esquerda!");
    getch();
    system("cls");
}

void aviso2()
{
    printf("AVISO! Sera realizado uma rotacao simples a esquerda!");
    getch();
    system("cls");
}

void aviso3()
{
    printf("AVISO! Sera realizado uma rotacao dupla a direita!");
    getch();
    system("cls");
}

void aviso4()
{
    printf("Produto excluido com sucesso!");
    getch();
    system("cls");
}


void aviso5()
{
    printf("Produto alterado com sucesso!");
    getch();
    system("cls");
}

void mensagem()
{
    printf("Este codigo de produto ja esta na lista !");
    getch();
    system("cls");
}

int menu()
{
    int op = 99;
    printf("======================================\n");
    printf("\t BANCO DE PRODUTOS\n");
    printf("======================================\n");
    printf("1. Inserir Produto\n");
    printf("2. Visualizar Produtos\n");
    printf("3. Buscar Produto\n");
    printf("4. Excluir Produto\n");
    printf("0. Sair\n");
    printf("Digite uma opcao: ");
    scanf("%d",&op);
    return op;
}

void lerNumero(int *numero)
{
    system("cls");
    printf("\nDigite o codigo do produto: ");
    scanf("%d",numero);
    system("cls");
}

int carregaArquivo(arv**raiz)
{
    long int pos = 0;
    produto prod;
    FILE* arquivo;
    arquivo = fopen("avl.txt","r");
    fseek(arquivo,0,SEEK_END);
    if(ftell(arquivo) == 0)
    {
        return 0;
    }

    fseek(arquivo,0,SEEK_SET);
    if(arquivo == NULL)
    {
        return 0;
    }
    else
    {
        while(fread(&prod, sizeof(struct BancoDeDados), 1, arquivo)== 1)
        {
            pos++;

            if(prod.codigo != 0)
            {
                insereElemento(&(*raiz),prod.codigo, pos);
            }
        }
    }


    fclose(arquivo);
    return pos;
}

void lerDadosProduto(int linha)
{
    printf("\nLendo dados...\n");
    printf("Numero da linha: %d", linha-1);
    produto prod;
    FILE* arquivo;
    arquivo = fopen("avl.txt","r");
    fseek(arquivo,0,SEEK_END);
    if(ftell(arquivo) == 0)
    {
        return;
    }
    int z = linha-1;
    if(z == -1)
    {
        z=0;
    }
    fseek(arquivo,z*sizeof(struct BancoDeDados),SEEK_SET);

    if(arquivo == NULL)
    {
        return;
    }
    else
    {
        fread(&prod, sizeof(struct BancoDeDados), 1, arquivo);
        printf("\nNumero Produto: %d \n", prod.codigo);
        printf("Nome: %s", prod.Nome);

        fclose(arquivo);
    }
}
void criarArquivo(FILE* arquivo)
{
    arquivo = fopen("avl.txt", "r");
    if(arquivo == NULL)
    {

        arquivo = fopen("avl.txt", "a");
        fclose(arquivo);
    }
    else
    {
        fclose(arquivo);
        return;
    }

}

void EscreverArquivo(FILE* arquivo, produto prod, int pos)
{
    arquivo = fopen("avl.txt", "a+b");

    fwrite(&prod,sizeof(struct BancoDeDados),1, arquivo);

    fclose(arquivo);
}

void excluiElementoArquivo(int pos)
{
    system("cls");
    printf("Excluindo: %d \n", pos-1);
    produto prod;
    FILE* arquivo;
    arquivo = fopen("avl.txt","r+b");
    if (arquivo == NULL)
    {
        printf("Erro na abertura do arquivo\n");
        system("pause");
        exit(1);
    }

    fseek(arquivo,(pos-1)*sizeof(struct BancoDeDados), SEEK_SET);

    prod.codigo = 0;
    fwrite(&prod,sizeof(struct BancoDeDados),1,arquivo);
    system("cls");
    aviso4();
    fclose(arquivo);
}

