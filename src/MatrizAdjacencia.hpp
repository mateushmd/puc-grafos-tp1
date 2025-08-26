#pragma once

#include <iostream>
#include <utility>
#include <stdio.h>
#include <stdlib.h>

#include "Implementacao.hpp"

/**
 * @class Grafo
 * @brief Classe que representa um grafo utilizando matriz de adjacência.
 *
 * Permite a criação de grafos direcionados ou não, com operações para adicionar vértices e arestas,
 * além de imprimir a matriz de adjacência do grafo.
 */
class MatrizAdjacencia : public Implementacao {
private:
    int **arestas = nullptr;        ///< Matriz de adjacência para armazenar as conexões entre vértices.
    int ultimoVertice;

    void realocarEspacoVetor(int **origem, int tamanhoOrigem, int tamanhoFinal){
        int* temp = new int[tamanhoFinal]; //Criando vetor com o novo tamanho
        std::copy(*origem, *origem+tamanhoOrigem, temp); //Copiando os dados do vetor de origem para o novo vetor
        delete[] *origem;  //Desalocando espaço do vetor de origem
        *origem = temp; //Apontando origem para o novo vetor
    }

    void realocarEspacoMatriz(int ***origem, int tamanhoOrigem, int tamanhoFinal){
        //Relocar o espaco da dos vetores
        for(int i = 0; i < tamanhoOrigem; i++){
            realocarEspacoVetor(&((*origem)[i]), tamanhoOrigem, tamanhoFinal);
        }
        int** temp = new int*[tamanhoFinal]; //Criando vetor de apontadores com o novo tamanho
        std::copy(*origem, *origem+tamanhoOrigem, temp); //Copiando os dados do vetor de origem para o novo vetor
        delete[] *origem; //Desalocando espaço do vetor de origem
        *origem = temp; //Apontando origem para o novo vetor
        int diferencaDeTamanho = tamanhoFinal - tamanhoOrigem; //Diferença do novo tamanho
        //Alocar espaço de novo vetores para o vetor de apontadores
        for(int i = 0; i < diferencaDeTamanho; i++){
            (*origem)[tamanhoOrigem+i] = new int[tamanhoFinal];
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
    MatrizAdjacencia(bool direcionado = false, bool ponderado = false) {
        this->direcionado = direcionado;
        this->ponderado = ponderado;
        this->tamanho;
    }

    ~MatrizAdjacencia() override {

        //Desalocar matriz de arestas
        for(int i = 0; i < this->tamanho; i++){
            delete[] this->arestas[i];
        }
        delete[] this->arestas;

    }

    /**
     * @brief Imprime a matriz de adjacência do grafo.
     */
    void mostrar() override {
        printf("Tamanho: %d\n", tamanho);
        printf("\t");
        
        for (int i = 0; i < tamanho; i++) {
            printf("\t%d", i);
        }
        std::cout << std::endl;
        for(int i = 0; i < tamanho; i++) {

            printf("\t%d", i);

            for(int j = 0; j < tamanho; j++) {
                    printf("\t%d", this->arestas[i][j]);
            }

            std::cout << std::endl; 
        }
    }

    void mostrar(unsigned int *labels) override {
        printf("Tamanho: %d\n", tamanho);
        printf("\t");
        
        for (int i = 0; i < tamanho; i++) {
            printf("\t%d", labels[i]);
        }
        std::cout << std::endl;
        for(int i = 0; i < tamanho; i++) {

            printf("\t%d", labels[i]);

            for(int j = 0; j < tamanho; j++) {
                    printf("\t%d", arestas[i][j]);
            }

            std::cout << std::endl; 
        }
    }
    
    /**
     * @brief Adiciona um novo vértice ao grafo.
     * @param v Label do vértice a ser adicionado.
     * @return true se o vértice foi adicionado, false se já existe.
     */
    int adicionarVertice() override {
            
        if(arestas == nullptr){
            arestas = new int*[1];
            arestas[0] = new int[1];
        } else {
            realocarEspacoMatriz(&this->arestas, tamanho, tamanho+1);
        }
        
        //Atribuir valores aos novos campos da matriz
        for(int i = 0; i < tamanho+1; i++){
            this->arestas[i][tamanho] = -1;
            this->arestas[tamanho][i] = -1;
        }

        this->tamanho++; //Atualizar o tamanho da matriz
        
        return tamanho - 1;
    }

    /**
     * @brief Adiciona uma aresta entre dois vértices.
     * @param u Label do vértice de origem.
     * @param v Label do vértice de destino.
     * @param p Peso da aresta (padrão: 1).
     * @return true se a aresta foi adicionada, false caso contrário.
     */
    bool adicionarAresta(int u, int v, int p = 1) override {
        //Se os vetores forem numeros validos criar as arestas, caso contrario retornar false
        if((u >= 0 && u < this->tamanho) && (v >= 0 && v < this->tamanho)){
            if(this->ponderado){
                this->arestas[v][u] = p;
                if(!direcionado) {
                    this->arestas[u][v] = p;
                }
            }else {
                this->arestas[v][u] = 1;
                if(!direcionado) {
                    this->arestas[u][v] = 1;
                }
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
    int getTamanho() override {
        return tamanho;
    }
};