//Algoritmo de Busca Binária implementado de forma iterativa
//Algoritmo de Busca Linear

#include <bits/stdc++.h>

using namespace std;

int  binarySearch (int x, int tam, int* v) {
    
    int inicio, meio, fim;
    
    inicio = 0;
    fim = tam-1;
    
    while (inicio <= fim) {
        
        meio = (inicio + fim)/2;
        
        if (v[meio] == x) return meio;
        if (v[meio] < x) inicio = meio + 1;
        
        else fim = meio - 1;
    }
    return -1;
    
}

int linearSearch(int x, int tam, int* v){
    
    for(int i = 0 ; i < tam ; i++){
        if(v[i] == x){
            return i;
        }
    }
    
    return -1;
    
}

int main(){
    
    
    int* vetor = new int[10];
    
    
    for(int i = 0 ; i < 10 ; i++){
        vetor[i] = (i-1)*10;
    }
    
    int ans;
    
    ans = binarySearch(10, 10, vetor);
    
    if(ans != -1){
        printf("O valor 10 foi encontrado na posição %d pela Buscar Binária ;)\n", ans);
    }
    else{
        puts("O valor 10 não foi encontrado pela Busca Binária.. :(");
    }
    
    ans = linearSearch(5, 10, vetor);
    
    if(ans != -1){
        printf("O valor 5 foi encontrado na posição %d pela Buscar Linear ;)\n", ans);
    }
    else{
        puts("O valor 5 não foi encontrado pela Busca Linear.. :(");
    }
    
    delete vetor;
    
}
