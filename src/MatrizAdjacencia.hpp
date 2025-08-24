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
class MatrizAdjacencia {
private:
    bool direcionado;      ///< Indica se o grafo é direcionado.
    int tamanho;           ///< Quantidade de vértices no grafo.
    int **arestas;        ///< Matriz de adjacência para armazenar as conexões entre vértices.
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

    int buscarLabel(int buscar){
        int resp = -1;
        int dir = this->tamanho - 1, esq = 0, meio;
        while (esq <= dir) {
            meio = (esq + dir) / 2;
            if (buscar == this->labels[meio]){
                resp = meio;
                esq = this->tamanho;
            } else if (buscar > this->labels[meio]){
                esq = meio + 1;
            } else {
                dir = meio - 1;
            }
        }
        return resp;
    }

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
    MatrizAdjacencia(int tamanho, int *vertices, int quantidadeArestas, int **arestas , bool direcionado = false) 
        : direcionado(direcionado), tamanho(tamanho) {
        //Alocar espaco e cria o vetor de labels
        labels = new int[tamanho];
        std::copy(vertices, vertices+tamanho, labels);
        this->ordenarLabels();

        //Criando a matriz para as arestas
        this->arestas = new int*[this->tamanho];
        for(int i = 0; i < tamanho; i++){
            this->arestas[i] = new int[this->tamanho];
            for(int j = 0; j < this->tamanho; j++){
                this->arestas[i][j] = -1;
            }
        }

        //Criar as arestas
        for(int i = 0; i < quantidadeArestas; i++) {
            adicionarAresta(arestas[i][0], arestas[i][1], arestas[i][2]);
        }
    }
    ~MatrizAdjacencia(){
        //Desalocar vetor de labels
        delete[] this->labels;

        //Desalocar matriz de arestas
        for(int i = 0; i < this->tamanho; i++){
            delete[] this->arestas[i];
        }
        delete[] this->arestas;

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
                    printf("\t%d", this->arestas[i][j]);
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
        
        if(this->buscarLabel(v) != -1){
            //já existe vértice com esse nome
            return false;
        }else{
            //Realocar o espaco do vetor de labels
            realocarEspacoVetor(&this->labels, tamanho, tamanho+1);
            this->labels[tamanho] = v; //Atribuir novo label
            this->ordenarLabels(); //Ordenar labels
            
            realocarEspacoMatriz(&this->arestas, tamanho, tamanho+1);
            
            //Atribuir valores aos novos campos da matriz
            for(int i = 0; i < tamanho+1; i++){
                this->arestas[i][tamanho] = -1;
                this->arestas[tamanho][i] = -1;
            }

            this->tamanho++; //Atualizar o tamanho da matriz
            
            return true;
        }
    }

    /**
     * @brief Adiciona uma aresta entre dois vértices.
     * @param u Label do vértice de origem.
     * @param v Label do vértice de destino.
     * @param p Peso da aresta (padrão: 1).
     * @return true se a aresta foi adicionada, false caso contrário.
     */
    bool adicionarAresta(int u, int v, int p = 1) {
        //Buscar os indices do label na matriz
        int indiceU = this->buscarLabel(u), indiceV = this->buscarLabel(v);
        
        //Se os vetores existirem criar as arestas, caso contrario retornar false
        if(indiceU != -1 && indiceV != -1){
            this->arestas[indiceU][indiceV] = p;
            if(!direcionado) {
                this->arestas[indiceV][indiceU] = p;
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