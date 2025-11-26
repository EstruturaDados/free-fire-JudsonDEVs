#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_COMPONENTES 20

// ===========================
// ======== NÍVEL 1 =========
// ===========================

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções Nível 1
void inserirItem(Item vetor[], int *total){
    if(*total >= MAX_ITENS){
        printf("Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("Digite o nome do item: ");
    fgets(novo.nome,30,stdin); novo.nome[strcspn(novo.nome,"\n")]=0;
    printf("Digite o tipo do item: ");
    fgets(novo.tipo,20,stdin); novo.tipo[strcspn(novo.tipo,"\n")]=0;
    printf("Quantidade: ");
    scanf("%d",&novo.quantidade); getchar();
    vetor[*total] = novo;
    (*total)++;
    printf("Item adicionado!\n");
}

void removerItem(Item vetor[], int *total){
    if(*total==0){ printf("Mochila vazia!\n"); return; }
    char nome[30];
    printf("Digite o nome do item a remover: ");
    fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    for(int i=0;i<*total;i++){
        if(strcmp(vetor[i].nome,nome)==0){
            for(int j=i;j<*total-1;j++) vetor[j]=vetor[j+1];
            (*total)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado!\n");
}

void listarItens(Item vetor[], int total){
    if(total==0){ printf("Mochila vazia!\n"); return; }
    printf("Itens na mochila:\n");
    for(int i=0;i<total;i++)
        printf("%d) %s | %s | %d\n", i+1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
}

void buscarItem(Item vetor[], int total){
    if(total==0){ printf("Mochila vazia!\n"); return; }
    char nome[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    int comparacoes=0;
    for(int i=0;i<total;i++){
        comparacoes++;
        if(strcmp(vetor[i].nome,nome)==0){
            printf("Item encontrado: %s | %s | %d\n", vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
            printf("Comparacoes: %d\n", comparacoes);
            return;
        }
    }
    printf("Item nao encontrado. Comparacoes: %d\n", comparacoes);
}

// ===========================
// ======== NÍVEL 2 =========
// ===========================

typedef struct No{
    Item dados;
    struct No *proximo;
} No;

// Vetor
int comparacoesSeqVetor=0;
int comparacoesBinVetor=0;

// Lista
int comparacoesSeqLista=0;

// Funções Vetor
void inserirItemVetor(Item vetor[], int *total){ inserirItem(vetor,total); }
void removerItemVetor(Item vetor[], int *total){ removerItem(vetor,total); }
void listarItensVetor(Item vetor[], int total){ listarItens(vetor,total); }

void buscarSequencialVetor(Item vetor[], int total){
    if(total==0){ printf("Mochila vazia!\n"); return; }
    char nome[30];
    printf("Digite o nome do item (vetor): ");
    fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    comparacoesSeqVetor=0;
    for(int i=0;i<total;i++){
        comparacoesSeqVetor++;
        if(strcmp(vetor[i].nome,nome)==0){
            printf("Item encontrado: %s | %s | %d\n", vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
            printf("Comparacoes: %d\n", comparacoesSeqVetor);
            return;
        }
    }
    printf("Item nao encontrado. Comparacoes: %d\n", comparacoesSeqVetor);
}

void ordenarVetor(Item vetor[], int total){
    for(int i=0;i<total-1;i++){
        for(int j=0;j<total-i-1;j++){
            if(strcmp(vetor[j].nome,vetor[j+1].nome)>0){
                Item tmp=vetor[j];
                vetor[j]=vetor[j+1];
                vetor[j+1]=tmp;
            }
        }
    }
    printf("Vetor ordenado por nome.\n");
}

int buscarBinariaVetor(Item vetor[], int total, char chave[]){
    int inicio=0, fim=total-1, meio;
    comparacoesBinVetor=0;
    while(inicio<=fim){
        meio=(inicio+fim)/2;
        comparacoesBinVetor++;
        int cmp=strcmp(chave,vetor[meio].nome);
        if(cmp==0) return meio;
        else if(cmp<0) fim=meio-1;
        else inicio=meio+1;
    }
    return -1;
}

// Funções Lista
void inserirItemLista(No **inicio){
    No *novo=(No*)malloc(sizeof(No));
    if(!novo){ printf("Erro de memoria!\n"); return; }
    printf("Nome: "); fgets(novo->dados.nome,30,stdin); novo->dados.nome[strcspn(novo->dados.nome,"\n")]=0;
    printf("Tipo: "); fgets(novo->dados.tipo,20,stdin); novo->dados.tipo[strcspn(novo->dados.tipo,"\n")]=0;
    printf("Quantidade: "); scanf("%d",&novo->dados.quantidade); getchar();
    novo->proximo=*inicio;
    *inicio=novo;
    printf("Item adicionado na lista!\n");
}

void removerItemLista(No **inicio){
    if(*inicio==NULL){ printf("Lista vazia!\n"); return; }
    char nome[30]; printf("Nome do item a remover: "); fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    No *atual=*inicio, *ant=NULL;
    while(atual){
        if(strcmp(atual->dados.nome,nome)==0){
            if(ant) ant->proximo=atual->proximo;
            else *inicio=atual->proximo;
            free(atual);
            printf("Item removido da lista!\n");
            return;
        }
        ant=atual;
        atual=atual->proximo;
    }
    printf("Item nao encontrado na lista!\n");
}

void listarItensLista(No *inicio){
    if(!inicio){ printf("Lista vazia!\n"); return; }
    int i=1;
    while(inicio){
        printf("%d) %s | %s | %d\n", i, inicio->dados.nome, inicio->dados.tipo, inicio->dados.quantidade);
        inicio=inicio->proximo;
        i++;
    }
}

void buscarSequencialLista(No *inicio){
    if(!inicio){ printf("Lista vazia!\n"); return; }
    char nome[30]; printf("Nome do item (lista): "); fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    comparacoesSeqLista=0;
    while(inicio){
        comparacoesSeqLista++;
        if(strcmp(inicio->dados.nome,nome)==0){
            printf("Item encontrado: %s | %s | %d\n", inicio->dados.nome, inicio->dados.tipo, inicio->dados.quantidade);
            printf("Comparacoes: %d\n", comparacoesSeqLista);
            return;
        }
        inicio=inicio->proximo;
    }
    printf("Item nao encontrado. Comparacoes: %d\n", comparacoesSeqLista);
}

// ===========================
// ======== NÍVEL 3 =========
// ===========================

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

void bubbleSortNome(Componente arr[], int n, int *comparacoes){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            (*comparacoes)++;
            if(strcmp(arr[j].nome,arr[j+1].nome)>0){
                Componente tmp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=tmp;
            }
        }
    }
}

void insertionSortTipo(Componente arr[], int n, int *comparacoes){
    for(int i=1;i<n;i++){
        Componente key=arr[i];
        int j=i-1;
        while(j>=0 && (++(*comparacoes), strcmp(arr[j].tipo,key.tipo)>0)){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

void selectionSortPrioridade(Componente arr[], int n, int *comparacoes){
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            (*comparacoes)++;
            if(arr[j].prioridade<arr[min].prioridade) min=j;
        }
        if(min!=i){
            Componente tmp=arr[i];
            arr[i]=arr[min];
            arr[min]=tmp;
        }
    }
}

int buscaBinariaPorNome(Componente arr[], int n, char chave[], int *comparacoes){
    int inicio=0, fim=n-1, meio;
    *comparacoes=0;
    while(inicio<=fim){
        meio=(inicio+fim)/2;
        (*comparacoes)++;
        int cmp=strcmp(chave,arr[meio].nome);
        if(cmp==0) return meio;
        else if(cmp<0) fim=meio-1;
        else inicio=meio+1;
    }
    return -1;
}

void mostrarComponentes(Componente arr[], int n){
    if(n==0){ printf("Nenhum componente cadastrado.\n"); return; }
    for(int i=0;i<n;i++)
        printf("%d) %s | %s | %d\n", i+1, arr[i].nome, arr[i].tipo, arr[i].prioridade);
}

// ===========================
// ======== MAIN ==============
// ===========================
int main(){
    int opcao;
    Item mochila[MAX_ITENS];
    int totalItens=0;
    No *inicioLista=NULL;
    Componente torre[MAX_COMPONENTES];
    int totalComponentes=0;

    do{
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Nivel 1: Mochila inicial\n");
        printf("2 - Nivel 2: Vetor vs Lista\n");
        printf("3 - Nivel 3: Torre de fuga\n");
        printf("0 - Sair\n");
        printf("Escolha: "); scanf("%d",&opcao); getchar();

        switch(opcao){
            case 1:{
                int op1;
                do{
                    printf("\n--- Nivel 1 ---\n1-Inserir 2-Remover 3-Listar 4-Buscar 0-Sair\nEscolha: "); scanf("%d",&op1); getchar();
                    switch(op1){
                        case 1: inserirItem(mochila,&totalItens); break;
                        case 2: removerItem(mochila,&totalItens); break;
                        case 3: listarItens(mochila,totalItens); break;
                        case 4: buscarItem(mochila,totalItens); break;
                    }
                }while(op1!=0);
                break;
            }
            case 2:{
                int op2;
                do{
                    printf("\n--- Nivel 2 ---\n1-Vetor Inserir 2-Vetor Remover 3-Vetor Listar 4-Vetor Busca Seq 5-Vetor Ordenar+Binaria\n");
                    printf("6-Lista Inserir 7-Lista Remover 8-Lista Listar 9-Lista Busca Seq 0-Sair\nEscolha: "); scanf("%d",&op2); getchar();
                    switch(op2){
                        case 1: inserirItemVetor(mochila,&totalItens); break;
                        case 2: removerItemVetor(mochila,&totalItens); break;
                        case 3: listarItensVetor(mochila,totalItens); break;
                        case 4: buscarSequencialVetor(mochila,totalItens); break;
                        case 5:{
                            ordenarVetor(mochila,totalItens);
                            char chave[30];
                            printf("Digite o item para busca binaria: ");
                            fgets(chave,30,stdin); chave[strcspn(chave,"\n")]=0;
                            int pos = buscarBinariaVetor(mochila,totalItens,chave);
                            if(pos!=-1) printf("Item encontrado: %s | %s | %d\n", mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade);
                            else printf("Item nao encontrado.\n");
                            printf("Comparacoes: %d\n", comparacoesBinVetor);
                            break;
                        }
                        case 6: inserirItemLista(&inicioLista); break;
                        case 7: removerItemLista(&inicioLista); break;
                        case 8: listarItensLista(inicioLista); break;
                        case 9: buscarSequencialLista(inicioLista); break;
                    }
                }while(op2!=0);
                break;
            }
            case 3:{
                printf("Quantos componentes cadastrar (max 20)? "); scanf("%d",&totalComponentes); getchar();
                if(totalComponentes>MAX_COMPONENTES) totalComponentes=MAX_COMPONENTES;
                for(int i=0;i<totalComponentes;i++){
                    printf("\nComponente %d\n",i+1);
                    printf("Nome: "); fgets(torre[i].nome,30,stdin); torre[i].nome[strcspn(torre[i].nome,"\n")]=0;
                    printf("Tipo: "); fgets(torre[i].tipo,20,stdin); torre[i].tipo[strcspn(torre[i].tipo,"\n")]=0;
                    printf("Prioridade (1-10): "); scanf("%d",&torre[i].prioridade); getchar();
                }
                int op3, comparacoes; char chave[30];
                do{
                    printf("\n--- Nivel 3 ---\n1-Bubble Nome 2-Insertion Tipo 3-Selection Prioridade 4-Busca Binaria 5-Mostrar 0-Sair\nEscolha: "); scanf("%d",&op3); getchar();
                    clock_t inicio,fim; double tempo;
                    switch(op3){
                        case 1: comparacoes=0; inicio=clock(); bubbleSortNome(torre,totalComponentes,&comparacoes); fim=clock(); tempo=((double)(fim-inicio))/CLOCKS_PER_SEC;
                                printf("Bubble Nome - Comparacoes: %d Tempo: %.6f s\n", comparacoes, tempo); break;
                        case 2: comparacoes=0; inicio=clock(); insertionSortTipo(torre,totalComponentes,&comparacoes); fim=clock(); tempo=((double)(fim-inicio))/CLOCKS_PER_SEC;
                                printf("Insertion Tipo - Comparacoes: %d Tempo: %.6f s\n", comparacoes, tempo); break;
                        case 3: comparacoes=0; inicio=clock(); selectionSortPrioridade(torre,totalComponentes,&comparacoes); fim=clock(); tempo=((double)(fim-inicio))/CLOCKS_PER_SEC;
                                printf("Selection Prioridade - Comparacoes: %d Tempo: %.6f s\n", comparacoes, tempo); break;
                        case 4: printf("Nome do componente chave: "); fgets(chave,30,stdin); chave[strcspn(chave,"\n")]=0;
                                int pos=buscaBinariaPorNome(torre,totalComponentes,chave,&comparacoes);
                                if(pos!=-1) printf("Encontrado: %s | %s | %d\n", torre[pos].nome, torre[pos].tipo, torre[pos].prioridade);
                                else printf("Nao encontrado.\n");
                                printf("Comparacoes: %d\n", comparacoes); break;
                        case 5: mostrarComponentes(torre,totalComponentes); break;
                    }
                }while(op3!=0);
                break;
            }
        }

    }while(opcao!=0);

    printf("Fim do programa.\n");
    return 0;
}
