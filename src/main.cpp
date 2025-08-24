#include <iostream>
#include "ListaAdjacencia.hpp"
#include "MatrizAdjacencia.hpp"

int main(void)
{
    int vertices[] = { 0, 1, 2, 3, 5};
    
    int **arestas = new int*[4];
    for(int i = 0; i < 4; i++) {
        arestas[i] = new int[2];
    }

    arestas[0][0] = 0;
    arestas[0][1] = 1;
    arestas[0][2] = 3;

    arestas[1][0] = 0;
    arestas[1][1] = 2;
    arestas[1][2] = 2;

    arestas[2][0] = 1;
    arestas[2][1] = 3;
    arestas[2][2] = 7;

    arestas[3][0] = 2;
    arestas[3][1] = 4;
    arestas[3][2] = 8;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            printf("\t%d", arestas[i][j]);
        }
        std::cout << std::endl;
    }

    MatrizAdjacencia* teste = new MatrizAdjacencia(5, vertices, 4, arestas, false);
    if(teste->adicionarVertice(6)){
        std::cout << "leu bunitu!" << std::endl;
    }else{
        std::cout << "rique feioso!" << std::endl;
    }; 
    teste->printGrafo();
    return 0;
}
/* int main() {
  int qtdVertices = 4;
    int qtdArestas = 4;

    // cada aresta no formato {u, v}
    int a1[2] = {0, 1};
    int a2[2] = {0, 2};
    int a3[2] = {1, 3};
    int a4[2] = {2, 3};

    // vetor de ponteiros para cada aresta
    int* arestas[4] = {a1, a2, a3, a4};

    // cria grafo não direcionado
    ListaAdjacencia g(qtdVertices, qtdArestas, arestas, false);

     // imprime grafo
    g.printGrafo();

    // imprime quantidade de vértices usando getTamanho()
    std::cout << "Número de vértices: " << g.getTamanho() << std::endl;

    std::cout << "Matriz de Adjacência - Grafo Ponderado:" << std::endl;

    int qtdVertices = 4;
    int qtdArestas = 4;

    // cada aresta no formato {u, v}
    int a1[2] = {0, 1};
    int a2[2] = {0, 2};
    int a3[2] = {1, 3};
    int a4[2] = {2, 3};

    // vetor de ponteiros para cada aresta
    int* arestas[4] = {a1, a2, a3, a4};

    // cria grafo não direcionado
    MatrizAdjacencia g(qtdVertices, qtdArestas, arestas, false);

     // imprime grafo
    g.printGrafo();

    // imprime quantidade de vértices usando getTamanho()
    std::cout << "Número de vértices: " << g.getTamanho() << std::endl;

    return 0;
} */