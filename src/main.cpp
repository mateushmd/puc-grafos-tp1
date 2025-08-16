#include <iostream>
#include "grafo.hpp"

int main(void)
{
    int vertices[] = { 0, 1, 2, 3 };
    
    int **arestas = new int*[4];
    for(int i = 0; i < 4; i++) {
        arestas[i] = new int[2];
        arestas[i][0] = i;
        if(i + 1 > 3)
            arestas[i][1] = 0;
        else
            arestas[i][1] = i + 1;
    }

    Grafo* teste = new Grafo(4, vertices, 4, arestas, false);
    if(teste->adicionarVertice(6)){
        std::cout << "leu bunitu!" << std::endl;
    }else{
        std::cout << "rique feioso!" << std::endl;
    };
    teste->printGrafo();
    std::cout << "leu lindiu!" << std::endl;
    return 0;
}
