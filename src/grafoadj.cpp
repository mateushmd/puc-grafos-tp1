#include <iostream>


using namespace std;

void inicializarMatrizAdjacencia(bool **matrizAdjacencia, int numVertices)
{
    for (int i = 0; i < numVertices; i++)
    {
        matrizAdjacencia[i] = new bool[numVertices]();
    }

    cout << endl
         << "Digite as arestas do grafo no formato (v1 v2). Digite (0 0) para encerrar:" << endl;

    char v1, v2;
    while (true)
    {
        cin >> v1 >> v2;

        if (v1 == '0' && v2 == '0')
        {
            break;
        }

        if (v1 == v2)
        {
            cout << "Laços não são permitidos em grafos simples! Digite uma aresta válida." << endl;
            continue;
        }

        if (v1 < 'A' || v1 >= 'A' + numVertices || v2 < 'A' || v2 >= 'A' + numVertices)
        {
            cout << "Vértices inválidos! Digite vértices entre A e " << char('A' + numVertices - 1) << endl;
            continue;
        }

        int i = v1 - 'A';
        int j = v2 - 'A';

        matrizAdjacencia[i][j] = true;
        matrizAdjacencia[j][i] = true; // Grafo não direcionado
    }
}

void imprimirMatrizAdjacencia(bool **matrizAdjacencia, int numVertices)
{
    cout << endl
         << "A matriz de adjacência é: " << endl;

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            cout << matrizAdjacencia[i][j] << " ";
        }
        cout << endl;
    }
}
