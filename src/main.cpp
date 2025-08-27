#include "Grafo.hpp"
#include "ListaAdjacencia.hpp"
#include "MatrizAdjacencia.hpp"
#include <iostream>

#define TAM 11

int main()
{
    MatrizAdjacencia *m = new MatrizAdjacencia();
    Grafo *teste = new Grafo(m, false, false, false);

    for (int i = TAM - 1; i >= 0; i--){

        teste->adicionarVertice(i);
        teste->print();
    }

/*     for (int i = 0; i < TAM; i++)
    {
        for (int j = i + 1; j < TAM; j++)
            teste->adicionarAresta(i, j, i + j);
    } */


    

    teste->adicionarAresta(0, 1);
    teste->adicionarAresta(0, 2);
    teste->adicionarAresta(1, 4);
    teste->adicionarAresta(1, 6);
    teste->adicionarAresta(2, 3);
    teste->adicionarAresta(3, 5);
    teste->adicionarAresta(3, 10);
    teste->adicionarAresta(4, 5);
    teste->adicionarAresta(4, 7);
    teste->adicionarAresta(4, 5);
    teste->adicionarAresta(5, 9);
    teste->adicionarAresta(5, 10);
    teste->adicionarAresta(5, 8);
    teste->adicionarAresta(6, 7);
    teste->adicionarAresta(7, 8);

    teste->mostrar();

    teste->DFS(0);
}
