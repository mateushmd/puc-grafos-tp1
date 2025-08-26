#include "Grafo.hpp"
#include "ListaAdjacencia.hpp"
#include "MatrizAdjacencia.hpp"
#include <iostream>

#define TAM 6

int main()
{
    MatrizAdjacencia *m = new MatrizAdjacencia();
    Grafo *teste = new Grafo(m, true, true, true);

    for (int i = TAM - 1; i >= 0; i--)
        teste->adicionarVertice(i);

    for (int i = 0; i < TAM; i++)
    {
        for (int j = i + 1; j < TAM; j++)
            teste->adicionarAresta(i, j, i + j);
    }

    teste->mostrar();
}
