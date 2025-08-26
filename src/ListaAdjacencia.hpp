#pragma once

#include <iostream>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "Implementacao.hpp"

/**
 * @class Grafo
 * @brief Classe que representa um grafo utilizando matriz de adjacência.
 *
 * Permite a criação de grafos direcionados ou não, com operações para adicionar vértices e arestas,
 * além de imprimir a matriz de adjacência do grafo.
 */
class ListaAdjacencia : public Implementacao {
protected:
    int *vertices = nullptr;        ///< Matriz de adjacência para armazenar as conexões entre vértices.

    int tArestas;
    int *arestas = nullptr;
public:
    /**
     * @brief Construtor da classe Grafo.
     * @param tamanho Quantidade de vértices.
     * @param vertices Vetor com os labels dos vértices.
     * @param quantidadeArestas Quantidade de arestas.
     * @param arestas Matriz com as arestas (pares de vértices).
     * @param direcionado Indica se o grafo é direcionado (padrão: false).
     */
    
    ListaAdjacencia(bool direcionado, bool ponderado){  
        this-> direcionado = direcionado; 
        this-> ponderado = ponderado;
        this-> tamanho = 0;
        this-> tArestas = 0;
    }

    ~ListaAdjacencia() override {
        delete[] this->arestas;
        delete[] this->vertices;
    }

    /**
     * @brief Imprime a matriz de adjacência do grafo.
     */
    void mostrar() override {
        // Imprime cabeçalho com quantidade de vértices e arestas armazenadas
        std::cout << "Lista de Adjacência (" << tamanho << " vértices, "
                << tArestas << " arestas armazenadas):\n";

        // Percorre cada vértice do grafo
        for (int i = 0; i < tamanho; i++) {

            // Posição inicial da lista de vizinhos do vértice i
            int inicio = vertices[i];

            // Posição final da lista de vizinhos:
            // - se houver próximo vértice com arestas, fim = índice inicial do próximo
            // - caso contrário (último vértice ou próximo sem vizinhos), fim = total de arestas
            int fim = (i < tamanho - 1 && vertices[i + 1] != -1) ? vertices[i + 1] : tArestas;

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

    void mostrar(unsigned int *labels) override {
        // Imprime cabeçalho com quantidade de vértices e arestas armazenadas
        std::cout << "Lista de Adjacência (" << tamanho << " vértices, "
                << tArestas << " arestas armazenadas):\n";

        // Percorre cada vértice do grafo
        for (int i = 0; i < tamanho; i++) {

            // Posição inicial da lista de vizinhos do vértice i
            int inicio = vertices[i];

            // Posição final da lista de vizinhos:
            // - se houver próximo vértice com arestas, fim = índice inicial do próximo
            // - caso contrário (último vértice ou próximo sem vizinhos), fim = total de arestas
            int fim = (i < tamanho - 1 && vertices[i + 1] != -1) ? vertices[i + 1] : tArestas;

            // Calcula o grau do vértice (quantos vizinhos ele tem)
            int grau = (inicio == -1) ? 0 : (fim - inicio);

            // Imprime índice do vértice e o grau
            std::cout << labels[i] << " (grau " << grau << "): ";

            if (grau == 0) {
                // Caso o vértice não tenha vizinhos
                std::cout << "(sem vizinhos)";
            } else {
                // Percorre a lista de vizinhos e imprime cada vizinho
                for (int j = inicio; j < fim; j++) {
                    std::cout << labels[arestas[j]] << " ";
                }
            }

            // Quebra de linha para o próximo vértice
            std::cout << "\n";
        }
    }

    int adicionarVertice() override {
        if(vertices == nullptr)
            vertices = new int[1];
        else
        {
            int *temp = new int[tamanho + 1];
            std::copy(vertices, vertices+tamanho, temp);
            delete[] vertices;
            vertices = temp;
        }
        
        if(vertices == nullptr)
            return -1;

        vertices[tamanho] = -1;
        tamanho++;

        return tamanho;
    }

    bool adicionarAresta(int u, int v, int p = 1) override {
        int aumentarTamanho = 1;
        if(direcionado){
            aumentarTamanho+= 1;
        }
        if(arestas == nullptr)
            arestas = new int[aumentarTamanho];
        else {
            int *temp = new int[tArestas + aumentarTamanho];
            std::copy(arestas, arestas+tArestas, temp);
            delete[] arestas;
            arestas = temp;
        }
        
        if(arestas == nullptr)
            return false;
        
        // Se o vértice u não for o último da lista, 
        // é necessário deslocar os ponteiros e arestas
        if(u < tamanho - 1) {
            int endPos = tArestas;
            for(int i = u + 1; i < tamanho; i++) {
                if(vertices[i] != -1)
                {
                    endPos = vertices[i];
                    break;
                }
            }

            for(int i = tArestas; i > endPos; i--)
                arestas[i] = arestas[i - 1];
            for(int i = u + 1; i < tamanho; i++)
                if(vertices[i] > -1) vertices[i]++;
                
            if(vertices[u] == -1)
                vertices[u] = endPos;
            arestas[endPos] = v;
        }
        else if(vertices[u] == -1)
            vertices[u] = tArestas;

        tArestas++;

        //Se direcionado
        if(!direcionado){
            // Se o vértice v não for o último da lista, 
            // é necessário deslocar os ponteiros e arestas
            if(v < tamanho - 1) {
                int endPos = tArestas;
                for(int i = v + 1; i < tamanho; i++) {
                    if(vertices[i] != -1)
                    {
                        endPos = vertices[i];
                        break;
                    }
                }

                for(int i = tArestas; i > endPos; i--)
                    arestas[i] = arestas[i - 1];
                for(int i = v + 1; i < tamanho; i++)
                    if(vertices[i] > -1) vertices[i]++;
                    
                if(vertices[v] == -1)
                    vertices[v] = endPos;
                arestas[endPos] = u;
            }
            else if(vertices[v] == -1)
                vertices[v] = tArestas;
        }
        
        tArestas++;

        return true;
    }

    int getTamanho() override {
        return this->tamanho;
    }
};