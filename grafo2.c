/*
Autor: Pablo T. Monteiro
Data: 19/07/2022

>  Representação de GRAFOS: <
>   lista de adjacencia     <
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//cria estrutura do grafo e seus dados;
struct grafo{
    int ponderado;
    int nVertices;
    int grauMax;
    int** arestas;
    float** pesos;
    int* grau;
};
//define o tipo 'Grafo' com estrutura 'grafo',
typedef struct grafo Grafo;
//Cria um ponteiro do tipo "struct Grafo"
Grafo *gr;

//-------------protótipos-de-FUNCAO----------------
void printar(Grafo *gr);
int insertAresta(Grafo* gr, int origem, int destino, int digrafo, float peso);
void excGrafo(Grafo *gr);
Grafo *newGrafo(int nVertices, int grauMax, int ponderado);


//------------------MAIN---------------------
int main(){
    setlocale(LC_CTYPE,"Portuguese");
    Grafo *gr;
    int num1, num2, num3, menu=0;
    char opc;
    while(menu==0){
        printf("\n>>>>>>>>>>Menu<<<<<<<<<\n");
        graph:
        printf("\nDigite:\n1 - nº de vertices\n2 - nº do grau maximo\n3 - 1 se ponderado, 2 se nao ponterado\n");
        scanf(" %d %d %d",&num1, &num2, &num3);
        menu = 1;
        gr = newGrafo(num1,num2,num3);
    //system("pause");
    /*
    //exemplo grafo G={4,4} A={(0,1),(0,2),(1,2),(2,3)} sem peso
    insertAresta(gr, 0, 1, 0, 0);
    insertAresta(gr, 0, 2, 0, 0);
    insertAresta(gr, 1, 2, 0, 0);
    insertAresta(gr, 2, 3, 0, 0);
    //system("pause");
    */
    //exemplo grafo G={6,7} grafo bipartido GRUPO_1: V{0,1,2}, GRUPO_2: V{3,4,5}
    //insertAresta(gr, 0, 3, 0, 0);
    //insertAresta(gr, 0, 4, 0, 0);
    //insertAresta(gr, 1, 3, 0, 0);
    //insertAresta(gr, 1, 4, 0, 0);
    //insertAresta(gr, 1, 5, 0, 0);
    //insertAresta(gr, 2, 4, 0, 0);
    //insertAresta(gr, 2, 5, 0, 0);
    //system("pause");
        arest:
        printf("Inserir aresta? S or N\n");
        scanf(" %c",&opc);
        if(opc=='S' || opc=='s'){
            int org, dest, dig, pes;
            printf("\nDigite:\n1 - Vertice origem\n2 - Vertice destino\n3 - 1 para digrafo/0 para não direcionado\n4 - 1 para ponderado/0 para não ponderado\n");
            scanf("%d %d %d %d", &org, &dest, &dig, &pes);
            insertAresta(gr, org, dest, dig, pes);
            goto arest;
        }else if(opc=='N' || opc=='n'){
            submenu:
            printf("\nDeseja SAIR, criar novo GRAFO ou MOSTRAR o existente? S (sair) G (novo grafo) M (mostrar grafo)\n");
            scanf(" %c",&opc);
            if(opc=='S' || opc=='s'){
                system("cls");
                menu = 1;
            }else if(opc=='G' || opc=='g'){
                system("cls");
                excGrafo(gr);
                goto graph;
            }else if(opc=='M' || opc=='m'){
                system("cls");
                printar(gr);
                system("pause");
                system("cls");
                goto submenu;
            }else{
                goto arest;
            }
        }else{
            printf("\n\n>>>>> Digito incorreto <<<<<\n");
            goto arest;
        }

    }
    excGrafo(gr);
    //system("pause");
    return 0;
}
// Funcao que cria grafo, aloca memoria (para arestas, aloca valor fixo [grau Maximo])
Grafo* newGrafo(int nVertices, int grauMax, int ponderado){
    Grafo *gr = (Grafo*)malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->nVertices = nVertices;
        gr->grauMax = grauMax;
        gr->ponderado = (ponderado != 0)?1:0;
        gr->grau=(int*)calloc(nVertices,sizeof(int));
        gr->arestas=(int**)malloc(nVertices*sizeof(int*));
        for(i=0; i<nVertices; i++){
            gr->arestas[i]=(int*)malloc(grauMax*sizeof(int));
            if(gr->ponderado){
                gr->pesos=(float**)malloc(nVertices*sizeof(float*));
                for(i=0; i<nVertices; i++){
                    gr->pesos[i] = (float*)malloc(grauMax*sizeof(float));
                }
            }
        }
        return gr;
    }
}
//funcao para inserir dados das arestas (limitada ao grauMax)
int insertAresta(Grafo* gr, int origem, int destino, int digrafo, float peso){
    if(gr == NULL) {return 0;}
    if(origem < 0 || origem >= gr->nVertices) {return 0;}
    if(destino < 0 || destino >= gr->nVertices){return 0;}

    gr->arestas[origem][gr->grau[origem]] = destino;
    gr->grau[origem]++;
    if(digrafo == 0){
        insertAresta(gr, destino, origem, 1, peso);
    }
}
//função que libera a memoria alocada
void excGrafo(Grafo *gr){
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nVertices; i++){
            free(gr->arestas[i]);
        }
        free(gr->arestas);
        if(gr->ponderado){
            for(i=0; i<gr->nVertices; i++){
                free(gr->pesos[i]);
            }
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}
//funcoa para printar lista de adjacencia
void printar(Grafo *gr){
    printf("\nNumero de vertices: %d",gr->nVertices);
    printf("\nNumero de arestas: %d",sizeof(gr->arestas));
    for(int i = 0; i<gr->nVertices; i++){
        printf("\n\n>>Vertice %d:",i);
        for(int j=0; j<gr->grau[i]; j++){
            printf(" -> |%d|",gr->arestas[i][j]);
        }
    }
    printf("\n\n Executado com sucesso\n\n");
}
