/**
 * @class MatrizAdjacencia
 * @brief Implementa um grafo utilizando uma matriz de adjacência.
 *
 * Esta classe herda de Implementacao e representa um grafo (direcionado ou não, ponderado ou não)
 * usando uma matriz de adjacência para armazenar as conexões entre vértices.
 * Permite adicionar vértices e arestas, além de exibir a matriz de adjacência.
 *
 * Métodos privados:
 * - realocarEspacoVetor: Realoca o espaço de um vetor de inteiros para um novo tamanho.
 * - realocarEspacoMatriz: Realoca o espaço da matriz de adjacência para acomodar novos vértices.
 *
 * Métodos públicos:
 * - MatrizAdjacencia: Construtor que inicializa o grafo conforme direcionamento e ponderação.
 * - ~MatrizAdjacencia: Destrutor que desaloca a matriz de adjacência.
 * - mostrar: Imprime a matriz de adjacência, com ou sem labels personalizados.
 * - adicionarVertice: Adiciona um novo vértice ao grafo, realocando a matriz conforme necessário.
 * - adicionarAresta: Adiciona uma aresta (ponderada ou não) entre dois vértices.
 * - getTamanho: Retorna o número de vértices do grafo.
 *
 * A matriz de adjacência é representada por um ponteiro duplo (int **arestas), onde cada posição
 * indica a existência (e peso, se ponderado) de uma aresta entre dois vértices.
 */
#pragma once

#include <iostream>
#include <utility>
#include <stdio.h>
#include <stdlib.h>

#include "Implementacao.hpp"


class MatrizAdjacencia : public Implementacao {
private:
    int **arestas = nullptr;        ///< Matriz de adjacência para armazenar as conexões entre vértices.
    int ultimoVertice;

    /**
     * @brief Realoca o espaço de um vetor de inteiros para um novo tamanho.
     * 
     * @param origem Ponteiro para o vetor de origem que será realocado.
     * @param tamanhoOrigem Tamanho atual do vetor de origem.
     * @param tamanhoFinal Novo tamanho desejado para o vetor.
     * 
     * Esta função cria um novo vetor com o tamanho especificado, copia os dados do vetor de origem para o novo vetor,
     * desaloca o vetor antigo e atualiza o ponteiro de origem para apontar para o novo vetor.
     */
    void realocarEspacoVetor(int **origem, int tamanhoOrigem, int tamanhoFinal){
        int* temp = new int[tamanhoFinal]; //Criando vetor com o novo tamanho
        std::copy(*origem, *origem+tamanhoOrigem, temp); //Copiando os dados do vetor de origem para o novo vetor
        delete[] *origem;  //Desalocando espaço do vetor de origem
        *origem = temp; //Apontando origem para o novo vetor
    }


    /**
     * @brief Realoca o espaço de uma matriz de inteiros para um novo tamanho.
     * 
     * @param origem Ponteiro para a matriz de origem que será realocada.
     * @param tamanhoOrigem Tamanho atual da matriz (número de linhas/colunas).
     * @param tamanhoFinal Novo tamanho desejado para a matriz (número de linhas/colunas).
     * 
     * Esta função realoca cada linha da matriz para o novo tamanho, cria um novo vetor de ponteiros para as linhas,
     * copia os ponteiros antigos, desaloca o vetor antigo e aloca espaço para as novas linhas.
     */
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
     * @brief Construtor da classe MatrizAdjacencia.
     * 
     * @param direcionado Indica se o grafo é direcionado (padrão: false).
     * @param ponderado Indica se o grafo é ponderado (padrão: false).
     * 
     * Inicializa os atributos de direcionamento e ponderação do grafo.
     */
    MatrizAdjacencia(bool direcionado = false, bool ponderado = false) {
        this->direcionado = direcionado;
        this->ponderado = ponderado;
        this->tamanho;
    }

    /**
     * @brief Destrutor da classe MatrizAdjacencia.
     * 
     * Libera toda a memória alocada para a matriz de adjacência.
     */
    ~MatrizAdjacencia() override {

        //Desalocar matriz de arestas
        for(int i = 0; i < this->tamanho; i++){
            delete[] this->arestas[i];
        }
        delete[] this->arestas;

    }

    
    /**
     * @brief Imprime a matriz de adjacência do grafo na saída padrão.
     * 
     * Exibe o tamanho do grafo e a matriz de adjacência, mostrando as conexões entre os vértices.
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

    /**
     * @brief Imprime a matriz de adjacência do grafo utilizando rótulos personalizados para os vértices.
     * 
     * @param labels Vetor de rótulos a serem exibidos para os vértices.
     * 
     * Exibe o tamanho do grafo e a matriz de adjacência, utilizando os rótulos fornecidos para identificar os vértices.
     */
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
     * 
     * Realoca a matriz de adjacência para acomodar o novo vértice e inicializa suas conexões como -1 (sem aresta).
     * 
     * @return O índice do novo vértice adicionado.
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
     * @brief Adiciona uma aresta entre dois vértices do grafo.
     * 
     * @param u Índice do primeiro vértice.
     * @param v Índice do segundo vértice.
     * @param p Peso da aresta (padrão: 1).
     * 
     * Cria uma aresta entre os vértices u e v. Se o grafo for ponderado, utiliza o peso informado.
     * Se o grafo não for direcionado, adiciona a aresta em ambas as direções.
     * 
     * @return true se a aresta foi adicionada com sucesso, false se os índices dos vértices forem inválidos.
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
     * @brief Obtém o número de vértices do grafo.
     * 
     * @return O tamanho atual (número de vértices) da matriz de adjacência.
     */
    int getTamanho() override {
        return tamanho;
    }
};