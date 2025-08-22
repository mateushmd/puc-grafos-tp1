#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool cicloValido(bool **matrizAdjacencia, vector<int> &vertices, int numVertices)
{
    for (int i = 0; i < numVertices; ++i)
    {
        int u = vertices[i];
        int v = vertices[(i + 1) % numVertices];
        if (!matrizAdjacencia[u][v])
            return false;
    }
    return true;
}

void encontrarCiclosPorPermutacao(bool **matrizAdjacencia, int numVertices)
{
    vector<int> vertices(numVertices);
    int contador = 0;

    // Inicializar os vértices
    for (int i = 0; i < numVertices; ++i)
    {
        vertices[i] = i;
    }

    // r = número de vértices no ciclo
    // (um ciclo deve ter pelo menos 3 vértices)
    for (int r = 3; r <= numVertices; r++)
    {
        int tmp = contador;
        cout << endl
             << "Ciclos com " << r << " vértices: " << endl;

        vector<bool> selecionados(numVertices);
        fill(selecionados.end() - r, selecionados.end(), true);

        do
        {
            vector<int> combinacao;
            for (int i = 0; i < numVertices; i++)
            {
                if (selecionados[i])
                {
                    combinacao.push_back(vertices[i]);
                }
            }

            do
            {
                if (cicloValido(matrizAdjacencia, combinacao, r))
                {
                    contador++;
                    for (int v : combinacao)
                    {
                        cout << char('A' + v) << " ";
                    }

                    cout << char('A' + combinacao[0]) << endl;
                }
            } while (next_permutation(combinacao.begin(), combinacao.end()));
        } while (next_permutation(selecionados.begin(), selecionados.end()));

        cout << "Número total de ciclos com " << r << " vértices: " << contador - tmp << endl
             << endl;
    }

    cout << "-- Número total de ciclos: " << contador << " --" << endl;
}
