#pragma once

#include <iostream>
#include <utility>
#include <stdio.h>
#include <stdlib.h>

/**
 * @class Grafo
 * @brief Classe que representa um grafo utilizando matriz de adjacência.
 *
 * Permite a criação de grafos direcionados ou não, com operações para adicionar vértices e arestas,
 * além de imprimir a matriz de adjacência do grafo.
 */
class Grafo {
private:
    bool direcionado;      ///< Indica se o grafo é direcionado.
    int tamanho;           ///< Quantidade de vértices no grafo.
    int **conexoes;        ///< Matriz de adjacência para armazenar as conexões entre vértices.
    int tamanhoLabels;     ///< Tamanho do vetor de labels.
    int *labels;           ///< Vetor que mapeia o label do vértice para o índice na matriz.

public:
    /**
     * @brief Construtor da classe Grafo.
     * @param tamanho Quantidade de vértices.
     * @param vertices Vetor com os labels dos vértices.
     * @param quantidadeArestas Quantidade de arestas.
     * @param arestas Matriz com as arestas (pares de vértices).
     * @param direcionado Indica se o grafo é direcionado (padrão: false).
     */
    Grafo(int tamanho, int *vertices, int quantidadeArestas, int **arestas , bool direcionado = false) 
        : direcionado(direcionado), tamanho(tamanho) {

        int maiorLabel = -1;
        for(int i = 0; i < quantidadeArestas; i++) {
            if(vertices[i] > maiorLabel)
                maiorLabel = vertices[i];
        }
        labels = new int[maiorLabel + 1];
        tamanhoLabels = maiorLabel + 1;

        for(int i = 0; i < tamanho; i++) {
            labels[vertices[i]] = i;
        }

        this->conexoes = new int*[this->tamanho];
        for(int i = 0; i < tamanho; i++){
            this->conexoes[i] = new int[this->tamanho];
            for(int j = 0; j < this->tamanho; j++){
                this->conexoes[i][j] = -1;
            }
        }

        for(int i = 0; i < quantidadeArestas; i++) {
            adicionarAresta(arestas[i][0], arestas[i][1]);
        }
    }

    /**
     * @brief Imprime a matriz de adjacência do grafo.
     */
    void printGrafo() {
        printf("Tamanho: %d\n", tamanho);
        printf("\t");
        
        for (int i = 0; i < tamanhoLabels; i++) {
            if(labels[i] != -1)
                printf("\t%d", i);
        }
        std::cout << std::endl;
        for(int i = 0; i < tamanhoLabels; i++) {
            if(labels[i] == -1) continue;

            printf("\t%d", i);

            for(int j = 0; j < tamanhoLabels; j++) {
                if(labels[j] != -1) 
                    printf("\t%d", this->conexoes[labels[i]][labels[j]]);
            }

            std::cout << std::endl; 
        }
    }
    
    /**
     * @brief Adiciona um novo vértice ao grafo.
     * @param v Label do vértice a ser adicionado.
     * @return true se o vértice foi adicionado, false se já existe.
     */
    bool adicionarVertice(unsigned int v) {
        if(tamanhoLabels <= v) {
            labels = (int*)realloc(labels, (v + 1) * sizeof(int));
            
            for(int i = tamanhoLabels; i < v + 1; i++) {
                labels[i] = -1;
            }

            tamanhoLabels = v + 1;
        }
        
        if(labels[v] == -1) {
            labels[v] = tamanho;
            conexoes = (int **)realloc(conexoes, sizeof(int*) * (tamanho + 1));

            for(int i = 0; i < tamanho + 1; i++){
                conexoes[i] = (int*)realloc(conexoes[i], (tamanho + 1) * sizeof(int));
                conexoes[i][tamanho] = -1;
            }
            
            for(int i = 0; i < tamanho + 1; i++){
                conexoes[tamanho][i] = -1;
            }

            tamanho = tamanho+1;
            return true;
        } 

        //já existe vértice com esse nome
        return false;
    }

    /**
     * @brief Adiciona uma aresta entre dois vértices.
     * @param u Label do vértice de origem.
     * @param v Label do vértice de destino.
     * @param p Peso da aresta (padrão: 1).
     * @return true se a aresta foi adicionada, false caso contrário.
     */
    bool adicionarAresta(int u, int v, int p = 1) {
        if(tamanhoLabels <= u || tamanhoLabels <= v) {
            return false;
        }

        int _u = labels[u], _v = labels[v];
        
        conexoes[_u][_v] = p;
        if(!direcionado) {
            conexoes[_v][_u] = p;
        }
        
        return true;
    }
    
    /**
     * @brief Retorna a quantidade de vértices do grafo.
     * @return Número de vértices.
     */
    int getTamanho() {
        return tamanho;
    }
};