#pragma once

#include <iostream>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

/**
 * @class Grafo
 * @brief Classe que representa um grafo utilizando matriz de adjacência.
 *
 * Permite a criação de grafos direcionados ou não, com operações para adicionar vértices e arestas,
 * além de imprimir a matriz de adjacência do grafo.
 */
class ListaAdjacencia {
private:
    bool direcionado;      ///< Indica se o grafo é direcionado.

    int tVertices;           ///< Quantidade de vértices no grafo.
    int *vertices = nullptr;        ///< Matriz de adjacência para armazenar as conexões entre vértices.

    int tArestas;
    int *arestas;

    int tLabels;
    int *labels;           ///< Vetor que mapeia o label do vértice para o índice na matriz.

    bool _adicionarVertice(int v) {
        if(vertices == nullptr)
            vertices = new int[1];
        else
        {
            int *temp = new int[tVertices + 1];
            std::memcpy(&temp, &vertices, sizeof temp);
            delete[] vertices;
            vertices = temp;
        }
        
        if(vertices == nullptr)
            return false;
        
        vertices[tVertices] = -1;
        tVertices++;

        return true;
    }

    bool _adicionarAresta(int u, int v, int p = 1) {
        if(arestas == nullptr)
            arestas = new int[1];
        else {
            int *temp = new int[tArestas + 1];
            std::copy(arestas, arestas+tArestas, temp);
            //std::memcpy(&temp, &arestas, sizeof temp);
            delete[] arestas;
            arestas = temp;
        }
        
        if(arestas == nullptr)
            return false;
        
        // Se o vértice u não for o último da lista, 
        // é necessário deslocar os ponteiros e arestas
        if(u < tVertices - 1) {
            int endPos = tArestas;
            for(int i = u + 1; i < tVertices; i++) {
                if(vertices[i] != -1)
                {
                    endPos = vertices[i];
                    break;
                }
            }

            for(int i = tArestas; i > endPos; i--)
                arestas[i] = arestas[i - 1];
            for(int i = u + 1; i < tVertices; i++)
                if(vertices[i] > -1) vertices[i]++;
                
            if(vertices[u] == -1)
                vertices[u] = endPos;
            arestas[endPos] = v;
        }
        else if(vertices[u] == -1)
            vertices[u] = tArestas;
        
        tArestas++;

        return true;
    }

public:
    /**
     * @brief Construtor da classe Grafo.
     * @param tamanho Quantidade de vértices.
     * @param vertices Vetor com os labels dos vértices.
     * @param quantidadeArestas Quantidade de arestas.
     * @param arestas Matriz com as arestas (pares de vértices).
     * @param direcionado Indica se o grafo é direcionado (padrão: false).
     */
    ListaAdjacencia(int tamanhoVertices, int tamanhoArestas, int **arestas, bool direcionado): direcionado(direcionado), tVertices(0), tArestas(0){  
        //Inicializar o vertor com a quantidade de vertices determinada apontando para lugar algum (-1)
        for(int i = 0; i < tamanhoVertices; i++){
            _adicionarVertice(i);
        }
        
        //Criar todas as arestas da matriz arestas[][2]
        for(int i = 0; i < tamanhoArestas; i++){
            _adicionarAresta(arestas[i][0], arestas[i][1]);
        }
    }

    /**
     * @brief Imprime a matriz de adjacência do grafo.
     */
    void printGrafo() {
        // Imprime cabeçalho com quantidade de vértices e arestas armazenadas
        std::cout << "Lista de Adjacência (" << tVertices << " vértices, "
                << tArestas << " arestas armazenadas):\n";

        // Percorre cada vértice do grafo
        for (int i = 0; i < tVertices; i++) {

            // Posição inicial da lista de vizinhos do vértice i
            int inicio = vertices[i];

            // Posição final da lista de vizinhos:
            // - se houver próximo vértice com arestas, fim = índice inicial do próximo
            // - caso contrário (último vértice ou próximo sem vizinhos), fim = total de arestas
            int fim = (i < tVertices - 1 && vertices[i + 1] != -1) ? vertices[i + 1] : tArestas;

            // Calcula o grau do vértice (quantos vizinhos ele tem)
            int grau = (inicio == -1) ? 0 : (fim - inicio);

            // Imprime índice do vértice e o grau
            std::cout << i << " (grau " << grau << "): ";

            if (grau == 0) {
                // Caso o vértice não tenha vizinhos
                std::cout << "(sem vizinhos)";
            } else {
                // Percorre a lista de vizinhos e imprime cada vizinho
                for (int j = inicio; j < fim; j++) {
                    std::cout << arestas[j] << " ";
                }
            }

            // Quebra de linha para o próximo vértice
            std::cout << "\n";
        }
    }

    int getTamanho() const {
        return tVertices;
    }
};