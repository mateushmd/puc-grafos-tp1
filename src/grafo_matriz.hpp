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
    int *labels;           ///< Vetor que mapeia o label do vértice para o índice na matriz.

    void ordenarLabels(){
        for (int i = 1; i < this->tamanho; i++) {
            int tmp = labels[i];
            int j = i - 1;
            while ( (j >= 0) && (labels[j] > tmp) ){
                labels[j + 1] = labels[j]; // Deslocamento
                j--;
            }
            labels[j + 1] = tmp;
        }
    }

    void realocarEspacoVetor(int **origem, int tamanhoOrigem, int tamanhoFinal){
        int* temp = new int[tamanhoFinal];
        std::copy(*origem, *origem+tamanhoOrigem, temp);
        delete[] *origem;
        *origem = temp;
        *origem[tamanhoFinal] = -1;
    }

    void realocarEspacoMatriz(int ***origem, int tamanhoOrigem, int tamanhoFinal){
        std::cout<<"tam Final: "<<tamanhoFinal<<std::endl;
        int** temp = new int*[tamanhoFinal];
        std::copy(*origem, *origem+tamanhoOrigem, temp);
        delete[] *origem;
        *origem = temp;
        for(int i = 0; i < tamanhoOrigem; i++){
            *origem[i][tamanhoFinal] = -1;
        }
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
    Grafo(int tamanho, int *vertices, int quantidadeArestas, int **arestas , bool direcionado = false) 
        : direcionado(direcionado), tamanho(tamanho) {

        int maiorLabel = -1;

        labels = new int[tamanho];

        std::copy(vertices, vertices+tamanho, labels);

        this->ordenarLabels();

        this->conexoes = new int*[this->tamanho];
        for(int i = 0; i < tamanho; i++){
            this->conexoes[i] = new int[this->tamanho];
            for(int j = 0; j < this->tamanho; j++){
                this->conexoes[i][j] = -1;
            }
        }

        for(int i = 0; i < quantidadeArestas; i++) {
            adicionarAresta(arestas[i][0], arestas[i][1], arestas[i][2]);
        }
    }

    /**
     * @brief Imprime a matriz de adjacência do grafo.
     */
    void printGrafo() {
        printf("Tamanho: %d\n", tamanho);
        printf("\t");
        
        for (int i = 0; i < tamanho; i++) {
            printf("\t%d", this->labels[i]);
        }
        std::cout << std::endl;
        for(int i = 0; i < tamanho; i++) {

            printf("\t%d", this->labels[i]);

            for(int j = 0; j < tamanho; j++) {
                    printf("\t%d", this->conexoes[i][j]);
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
        
        this->tamanho++; //Atualizar o tamanho da matriz
        realocarEspacoVetor(&this->labels, tamanho-1, tamanho);
        this->ordenarLabels(); //Ordenar labels
    
        /* std::cout<<"tam Final: "<<tamanhoFinal<<std::endl;
        int** temp;
        temp = new int*[tamanhoFinal];
        std::copy(this->conexoes, this->conexoes+(tamanho-1), temp);
        delete[] this->conexoes;
        this->conexoes = temp; */
        realocarEspacoMatriz(&this->conexoes, tamanho-1, tamanho);
        //conexoes = (int **)realloc(conexoes, sizeof(int*) * (tamanho)); //Realoc


        for(int i = 0; i < tamanho; i++){
            realocarEspacoVetor(&conexoes[i], tamanho-1, tamanho);
            //conexoes[i] = (int*)realloc(conexoes[i], (tamanho) * sizeof(int));
        }
        
        for(int i = 0; i < tamanho + 1; i++){
            conexoes[i][tamanho] = -1;
            conexoes[tamanho][i] = -1;
        }

        tamanho = tamanho+1;
        return true;

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
        int indiceU = 0, indiceV = 0;
        while(indiceU < this->tamanho && this->labels[indiceU] != u){
            indiceU++;
        }

        while(indiceV < this->tamanho && this->labels[indiceV] != v){
            indiceV++;
        }
        
        if(indiceU < this->tamanho && indiceV < this->tamanho){
            conexoes[indiceU][indiceV] = p;
            if(!direcionado) {
                conexoes[indiceV][indiceU] = p;
            }
        }else{
            return false;
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