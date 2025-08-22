#include <iostream>
#include <sstream>

using namespace std;

void DFSUtil(bool **matrizAdjacencia, int numVertices, int vertice, bool *visitado, int *caminho, int indiceCaminho, int verticeInicial, string *ciclosEncontrados, int &qtdCiclos)
{
    visitado[vertice] = true;
    caminho[indiceCaminho] = vertice;
    indiceCaminho++;

    // Explora todos os vizinhos do vértice atual
    for (int i = 0; i < numVertices; i++)
    {
        if (matrizAdjacencia[vertice][i])
        { // Se há uma aresta entre vertice -> i
            if (!visitado[i])
            {
                DFSUtil(matrizAdjacencia, numVertices, i, visitado, caminho, indiceCaminho, verticeInicial, ciclosEncontrados, qtdCiclos);
            }
            else if (i == verticeInicial && indiceCaminho > 2)
            {
                // Encontramos um ciclo válido (volta ao início e tem pelo menos 3 vértices)

                // Usando stringstream para formatar corretamente o ciclo
                stringstream ciclo;
                for (int j = 0; j < indiceCaminho; j++)
                {
                    ciclo << char('A' + caminho[j]) << " "; // Concatena o vértice atual no ciclo
                }
                ciclo << char('A' + verticeInicial); // Fecha o ciclo, incluindo o vértice inicial

                string cicloStr = ciclo.str(); // Converte para string

                // Verifica se o ciclo já foi encontrado
                bool jaEncontrado = false;
                for (int k = 0; k < qtdCiclos; k++)
                {
                    if (ciclosEncontrados[k] == cicloStr)
                    {
                        jaEncontrado = true;
                        break;
                    }
                }

                if (!jaEncontrado)
                {
                    // Se o ciclo não foi encontrado antes, imprime e armazena
                    cout << "Ciclo encontrado: " << cicloStr << endl;
                    ciclosEncontrados[qtdCiclos] = cicloStr; // Armazena o ciclo
                    qtdCiclos++;                             // Incrementa o contador
                }
            }
        }
    }

    // Retrocede para explorar outros caminhos
    visitado[vertice] = false;
}

void encontrarCiclosDFS(bool **matrizAdjacencia, int numVertices)
{
    bool *visitado = new bool[numVertices]();                    // Array de vértices visitados
    int *caminho = new int[numVertices];                         // Array para armazenar o caminho atual
    string *ciclosEncontrados = new string[numVertices * numVertices]; // Array para armazenar ciclos encontrados
    int qtdCiclos = 0;                                           // Contador de ciclos encontrados

    // Chama DFS para cada vértice
    for (int i = 0; i < numVertices; i++)
    {
        DFSUtil(matrizAdjacencia, numVertices, i, visitado, caminho, 0, i, ciclosEncontrados, qtdCiclos);
    }

    // Libera a memória alocada
    delete[] visitado;
    delete[] caminho;
    delete[] ciclosEncontrados;
}
