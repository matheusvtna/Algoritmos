/*------------------------------GRAFO-------------------------------*/
/* Implementação com estruturas de dados de C++ com resquícios de C */

#include <bits/stdc++.h>
#define UNVISITED 0
#define VISITED 1

using namespace std;

//Componentes conexos
int cc;

//Pilha para o topoSort shortestRoute
stack<int> pilha;

//Fila dos vértices a serem processados na BFS
queue<int> fila;

typedef struct{
    int** matrix;     //Matriz de adjacências
    int numEdges;     //Número de arestas
    int numNodes;     //Número de vértices
    int* mark;        //Array auxiliar de marcação
} Graph;


//Inicializando a estrutura com 'n' vértices
Graph* createGraph(int n){
    Graph* g = (Graph *) malloc(sizeof(Graph));
    int i;
    
    g->mark = (int *) calloc(n, sizeof(int));
    
    g->matrix = (int **) calloc(n, sizeof(int *));
    
    for(i=0 ; i<n ; i++){
        g->matrix[i] = (int*) calloc(n, sizeof(int));
    }
    
    g->numNodes = n;
    
    g->numEdges = 0;
    
    return g;
}

//Retorna o número de vértices de um grafo
int n(Graph* g){
    return g->numNodes;
}

// Apaga o grafo
void destructyGraph(Graph* g){
    int i;
    
    for(i=0 ; i<n(g) ; i++){
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g->mark);
    free(g);
}

//Retorna o número de arestas de um grafo
int e(Graph* g){
    return g->numEdges;
}

//Retorna o primeiro vértice ligado ao vértice de índice 'v'
int first(Graph* g, int v){
    int i;
    
    for(i=0 ; i<n(g) ; i++){
        if(g->matrix[v][i] != 0) return i;
    }
    
    return n(g);
}

//Retorna o próximo vértice ligado ao vértice de indice 'v' após o vértice de índice 'w'
int next(Graph* g, int v, int w){
    int i;
    
    for(i=w+1 ; i<n(g) ; i++){
        if(g->matrix[v][i] != 0) return i;
    }
    
    return n(g);
}

//Cria uma aresta entre os vértices de índices 'i' e 'j' com peso 'wt'
void setEdge(Graph* g, int i, int j, int wt){
    if(wt == 0){
        return;
    }
    
    if(g->matrix[i][j] == 0){
        g->numEdges++;
    }
    
    g->matrix[i][j] = wt;
    
    //Caso queira um grafo não-dirigido seria necessário
    //setar outra aresta entre os vértices, saindo de 'j'
    //e chegando em 'i'
    
}

//Retorna um booleano que indica a existência de aresta entre os vértices de índices 'i' e 'j'
int isEdge(Graph* g, int i, int j){
    return g->matrix[i][j];
}

//Deleta a aresta entre os vértices de índices 'i' e 'j'
void delEdge(Graph* g, int i, int j){
    
    if(isEdge(g, i, j)){
        g->numEdges--;
    }
    
    g->matrix[i][j] = 0;
}

//Retorna o peso da aresta entre os vértices de índices 'i' e 'j'
int weight(Graph* g, int i, int j){
    return g->matrix[i][j];
}

//Seta um valor 'val' na posição de índice 'v' do array auxilar com alguma flag
void setMark(Graph* g, int v, int val){
    g->mark[v] = val;
}

//Verifica qual a marcação na posição de índice 'v' do array auxiliar
int getMark(Graph* g, int v){
    return g->mark[v];
}

//Busca o primeiro filho não-visitado do vértice atual
void DFS(Graph* g, int v){
    int w;
    
    setMark(g, v, VISITED);
    
    w = first(g, v);
    
    while(w < n(g)){
        
        if(getMark(g, w) == UNVISITED){
            DFS(g, w);
        }
        
        w = next(g, v, w);
    }
    
}

//Busca todos os filhos não-visitados do vértice atual em fila
void BFS(Graph* g, int start){
    
    int v, w;
    
    //Fila dos vértices a serem processados
    queue<int> fila;
    
    fila.push(start);
    
    setMark(g, start, VISITED);
    
    while(!fila.empty()){
        
        v = fila.front();
        
        fila.pop();
        
        w = first(g, v);
        
        while(w < n(g)){
            
            if(getMark(g, w) == UNVISITED){
                setMark(g, w, VISITED);
                fila.push(w);
            }
            
            w = next(g, v, w);
        }
    }
}

//Define qual tipo de travessia será feita no grafo
void traverse(Graph* g, int v){
    int op;
    
    puts("Digite o tipo de travessia desejada:");
    puts("1. DFS");
    puts("2. BFS");
    
    scanf("%d", &op);
    
    if(op==1){
        DFS(g, v);
    }
    else{
        BFS(g, v);
    }
    
}

// Ordena topologicamente um grafo 
void topoSort(Graph* g, int v){
    int w;
    
    setMark(g, v, VISITED);
    
    w = first(g, v);
    
    while(w < n(g)){
        
        if(getMark(g, w) == UNVISITED){
            topoSort(g, w);
        }
        
        w = next(g, v, w);
    }
    
    pilha.push(v);
    
}

// Travessia no grafo
void graphTraverse(Graph* g){
    int v;
    
    for(v=0 ; v<n(g) ; v++){
        setMark(g, v, UNVISITED);
    }
    for(v=0 ; v<n(g) ; v++){
        if(getMark(g, v) == UNVISITED){
            
            traverse(g, v);
        }
        
    }
}

//Printar a matriz de adjacências
void printMatriz(Graph* g){
    int i, j;
    
    for(i=0 ; i<n(g) ; i++){
        for(j=0 ; j<n(g) ; j++){
            printf("%d ", g->matrix[i][j]);
        }
        puts("");
    }
}

//Printar a pilha originada no topoSort
void printPilha(){
    
    while(!pilha.empty()){
        printf("%d ", pilha.top() + 1);
        pilha.pop();
    }
}

//Menor caminho entre dois vértices, em que todas as arestas apresentam o mesmo peso
void shortestRoute(Graph* g, int start, int end){
    
    int* pred = (int *) malloc(n(g)*sizeof(int));
    int hasFound = 0;
    int i;
    int v = start;
    queue<int> FILA;
    
    for(i=0 ; i<n(g) ; i++){
        setMark(g, i, UNVISITED);
        pred[i] = -1;
    }
    
    FILA.push(v);
    setMark(g, v, VISITED);
    
    while(!FILA.empty()){
        v = FILA.front();
        FILA.pop();
        
        int w = first(g, v);
        
        while(w < n(g)){
            
            if(getMark(g, w) == UNVISITED){
                setMark(g, w, VISITED);
                FILA.push(w);
                pred[w] = v;
                
                if(w == end){
                    hasFound = 1;
                    break;
                }
            }
            w = next(g, v, w);
            
        }
        
        if(hasFound){
            break;
        }
    }
    
    if(hasFound){
        v = end;
        
        pilha.push(v);
        
        while(pred[v] != start){
            pilha.push(pred[v]);
            v = pred[v];
        }
        
        pilha.push(start);
        printPilha();
    }
    
    free(pred);
    
}

int main(){
    int k;
    int m;
    
    while(scanf("%d %d", &k, &m), k+m){
        Graph* g;
        
        g = createGraph(k);
        
        while(m--){
            int i, j;
            scanf("%d %d", &i, &j);
            setEdge(g, i-1, j-1, 1);
        }
        
        for(int i=0 ; i<n(g) ; i++){
            if(getMark(g, i) == UNVISITED) topoSort(g, i);
        }
        printPilha();
        puts("");
        destructyGraph(g);
    }
    
    
    return 0;
}
