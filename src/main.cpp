#include <iostream>
#include "ListaAdjacencia.hpp"
#include "MatrizAdjacencia.hpp"
#include "Grafo.hpp"

#define TAM 6

int main(){
    ListaAdjacencia* m = new ListaAdjacencia(false, false);
    Grafo* teste = new Grafo(m, true);
    
    for(int i = TAM - 1; i >= 0; i--)
        teste->adicionarVertice(i);

    /*for(int i = 0; i < TAM; i++)
     {
        for(int j = i + 1; j < TAM; j++)
            teste->adicionarAresta(i, j);
    } */
   teste->adicionarAresta(3, 4, 3);

    teste->mostrar();
}