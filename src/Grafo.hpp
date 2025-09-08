#pragma once

#include <iostream>

#include "Implementacao.hpp"

/**
 * @class Grafo
 * @brief Classe que representa um grafo, podendo ser rotulado ou não.
 *
 * Esta classe encapsula a implementação de um grafo, permitindo a manipulação de 
 * értices e arestas, além de suportar rótulos para os vértices caso o grafo se 
 * rotulado.
 *
 * @private
 * - Implementacao *impl: Ponteiro para a implementação interna do grafo.
 * - bool rotulado: Indica se o grafo possui rótulos nos vértices.
 * - int tLabels: Quantidade atual de rótulos armazenados.
 * - int tLabelsMax: Capacidade máxima atual do vetor de rótulos.
 * - unsigned int* labels: Vetor dinâmico que armazena os rótulos dos vértices.
 *
 * @private
 * void realocarEspacoVetor(unsigned int **origem, int tamanhoOrigem, int
 * tamanhoFinal): Realoca o vetor de rótulos para um novo tamanho, copiando os 
 * ados existentes.
 *
 * int buscarLabel(int buscar):
 *     Busca o índice de um rótulo no vetor de rótulos.
 *
 * @public
 * Grafo(Implementacao *implementacao, bool rotulado):
 *     Construtor da classe. Inicializa a implementação e, se necessário, o ve
 * or de rótulos.
 *
 * ~Grafo():
 *     Destrutor da classe. Libera a memória alocada para a implementação.
 *
 * void mostrar():
 *     Exibe o grafo, utilizando os rótulos se o grafo for rotulado.
 *
 * bool adicionarVertice(unsigned int v):
 *     Adiciona um novo vértice ao grafo, atribuindo um rótulo se necessário.
 *
 * bool adicionarAresta(int u, int v, int p = 0):
 *     Adiciona uma aresta entre dois vértices, utilizando rótulos se o grafo f
 * r rotulado.
 *
 * int getTamanho():
 *     Retorna o tamanho (número de vértices) do grafo.
 */

class Grafo {
  private:
    Implementacao *impl;
    bool direcionado, ponderado, rotulado;
    int tLabels = 0, tLabelsMax = 10;
    unsigned int *labels = nullptr;

    void realocarEspacoVetor(unsigned int **origem, int tamanhoOrigem,
                             int tamanhoFinal) {
        unsigned int *temp =
            new unsigned int[tamanhoFinal]; // Criando vetor com o novo tamanho
        std::copy(
            *origem, *origem + tamanhoOrigem,
            temp); // Copiando os dados do vetor de origem para o novo vetor
        delete[] *origem; // Desalocando espaço do vetor de origem
        *origem = temp;   // Apontando origem para o novo vetor
    }

    int buscarLabel(int buscar) {
        int resp = -1;
        for (int i = 0; i < tLabels; i++) {
            if (labels[i] == buscar) {
                resp = i;
                i = tLabels;
            }
        }
        return resp;
    }

  public:
    /**
     * @brief Construtor da classe Grafo.
     *
     * Inicializa um novo objeto Grafo com a implementação fornecida e define se o
     * grafo é rotulado. Caso o grafo seja rotulado, aloca espaço inicial para 
     * s labels dos vértices.
     *
     * @param implementacao Ponteiro para a implementação do grafo (ex: matriz d
     *  adjacência, lista, etc).
     * @param rotulado Indica se o grafo possui rótulos nos vértices.
     */
    Grafo(Implementacao *implementacao, bool direcionado, bool ponderado,
          bool rotulado)
        : tLabels(0), tLabelsMax(10), impl(implementacao),
          direcionado(direcionado), ponderado(ponderado), rotulado(rotulado) {
        if (rotulado) {
            labels = new unsigned int[tLabelsMax];
        }
    }

    /**
     * @brief Destrutor da classe Grafo.
     *
     * Libera a memória alocada para a implementação do grafo.
     */
    ~Grafo() { delete impl; }

    /**
     * @brief Exibe o grafo.
     *
     * Chama o método de exibição da implementação, passando os labels caso o graf
     * seja rotulado.
     */
    void mostrar() {
        if (rotulado) {
            impl->mostrar(labels);
        } else {
            impl->mostrar();
        }
    }

    /**
     * @brief Adiciona um novo vértice ao grafo.
     *
     * Caso o grafo seja rotulado, armazena o rótulo do novo vértice.
     * Realoca o vetor de labels se necessário.
     *
     * @param v Rótulo do vértice a ser adicionado.
     * @return true se o vértice foi adicionado com sucesso, false caso 
     * ontrário.
     */
    bool adicionarVertice(unsigned int v) {
        int novo = impl->adicionarVertice();

        if (novo == -1)
            return false;

        if (rotulado) {
            if (tLabels == tLabelsMax) {
                tLabelsMax += 10;
                realocarEspacoVetor(&labels, tLabels, tLabelsMax);
            }

            labels[novo] = v;
            tLabels++;
        }

        return true;
    }

    /**
     * @brief Adiciona uma aresta entre dois vértices.
     *
     * Se o grafo for rotulado, busca os índices dos vértices a partir dos r
     * tulos. Caso contrário, utiliza os índices diretamente.
     *
     * @param u Índice ou rótulo do vértice de origem.
     * @param v Índice ou rótulo do vértice de destino.
     * @param p Peso da aresta (opcional, padrão 0).
     * @return true se a aresta foi adicionada com sucesso, false caso
     * contrário.
     */
    bool adicionarAresta(int u, int v, unsigned int p = 0) {
        int iU = u, iV = v;

        if (!ponderado)
            p = 1;

        if (rotulado) {
            iU = buscarLabel(u), iV = buscarLabel(v);
            if (iU == -1 || iV == -1)
                return false;
        }

        impl->adicionarAresta(iU, iV, p);

        if (!direcionado)
            impl->adicionarAresta(iV, iU, p);

        return true;
    }

    /**
     * @brief Retorna o número de vértices do grafo.
     *
     * @return Quantidade de vértices presentes no grafo.
     */
    int getTamanho() { return impl->getTamanho(); }

    void print() {
        for (int i = 0; i < tLabels; i++)
            std::cout << labels[i] << " ";
    }

    bool caminhamentoEmLargura(int v) {
        if (rotulado) {
            int indiceV = buscarLabel(v);
            if (indiceV == -1)
                return false;

            return impl->caminhamentoEmLargura(indiceV);
        } else {
            return impl->caminhamentoEmLargura(v);
        }
    }

    bool caminhamentoEmProfundidade(int v) {
        if (rotulado) {
            int indiceV = buscarLabel(v);
            if (indiceV == -1)
                return false;

            return impl->caminhamentoEmProfundidade(indiceV);
        } else {
            return impl->caminhamentoEmProfundidade(v);
        }
    }

    std::size_t getMemoriaOcupada() { return impl->getMemoriaOcupada(); }
};
