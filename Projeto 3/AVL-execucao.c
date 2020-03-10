# include <stdio.h>
# include <stdlib.h>
# include "AVL-codigo.c"


main()
{
    int num, nnum;
    int pos = 0;
    produto Produto;

    FILE *arquivo;
    arv *raiz;
    criaGalhoNulo(&raiz);
    criarArquivo(arquivo);
    pos = carregaArquivo(&raiz) + 1;
    system("cls");
    while(num!=0)
    {
        num = menu();
        switch(num){
            case 1:
                system("cls");
                printf("\nDigite o codigo do produto: ");
                scanf("%d", &Produto.codigo);
                system("cls");
                if(insereElemento(&raiz,Produto.codigo,pos) == 1)
                {
                    system("cls");
                    printf("\nDigite o nome do produto:");
                    getchar();
                    gets(Produto.Nome);
                    fflush(stdin);
                    system("cls");
                    EscreverArquivo(arquivo, Produto, pos);
                    printf("\ni = %d\n",Produto.codigo);
                    impressao(raiz);
                    pos++;
                    Produto=vaziaStruct;
                }
                break;

            case 2:

                impressao(raiz);
                break;

            case 3:

                lerNumero(&nnum);
                int buscaTres = busca(raiz, nnum);
                if(buscaTres != -1)
                {
                    lerDadosProduto(buscaTres);
                }
                buscaTres=-1;
                break;

            case 4:

                lerNumero(&Produto.codigo);
                int bus = busca(raiz,Produto.codigo);

                if(bus != -1)
                {
                    excluirElemento(&raiz,Produto.codigo, bus);
                    excluiElementoArquivo(bus);
                }
                impressao(raiz);
                bus=-1;
                break;

            }
        getch();
        system("cls");
    }
}
