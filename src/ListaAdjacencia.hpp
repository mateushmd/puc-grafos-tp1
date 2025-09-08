/**
 * @file ListaAdjacencia.hpp
 * @brief Implementação de um grafo utilizando lista de adjacência compacta.
 *
 * Esta classe implementa uma estrutura de dados para grafos baseada em listas
 * de adjacência, armazenando vértices e arestas em arrays dinâmicos. Suporta g
 * afos direcionados e ponderados.
 *
 * Estrutura:
 * - Cada vértice possui um índice no array `vertices`, que aponta para o início
 * de sua lista de vizinhos no array `arestas`.
 * - O array `arestas` armazena pares (vértice, peso) representando as conexões.
 *
 * Funcionalidades principais:
 * - Adição de vértices e arestas (com ou sem peso).
 * - Impressão da lista de adjacência, com ou sem rótulos personalizados.
 * - Gerenciamento dinâmico de memória para expansão dos arrays.
 */

#pragma once

#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <cstddef>

#include "Implementacao.hpp"

/**
 * @struct tupla
 * @brief Estrutura auxiliar para armazenar um vizinho e o peso da aresta.
 *
 * Campos:
 * - vertice: índice do vértice vizinho.
 * - peso: peso da aresta (ou 1 se não ponderado).
 */
typedef struct {
    int vertice = -1;
    int peso = -1;
} tupla;

/**
 * @class ListaAdjacencia
 * @brief Classe que representa um grafo usando lista de adjacência compacta.
 *
 * Herda de Implementacao e implementa métodos para manipulação de grafos.
 *
 * Membros protegidos:
 * - int* vertices: Array que armazena o índice inicial da lista de vizinhos de
 * ada vértice.
 * - int tArestas: Quantidade total de arestas armazenadas.
 * - tupla* arestas: Array de tuplas representando as arestas (vértice vizinho e
 * eso).
 *
 * Métodos públicos:
 * - ListaAdjacencia(bool direcionado, bool ponderado): Construtor.
 * - ~ListaAdjacencia(): Destrutor, libera memória alocada.
 * - void mostrar() override: Imprime a lista de adjacência.
 * - void mostrar(unsigned int* labels) override: Imprime a lista de adjacência
 * om rótulos personalizados.
 * - int adicionarVertice() override: Adiciona um novo vértice ao grafo.
 * - bool adicionarAresta(int u, int v, int p = 1) override: Adiciona uma aresta
 * entre os vértices u e v, com peso p.
 * - int getTamanho() override: Retorna o número de vértices no grafo.
 */
class ListaAdjacencia : public Implementacao {
  protected:
    int *vertices = nullptr; ///< Matriz de adjacência para armazenar as
                             ///< onexões entre vértices.
    int tArestas;
    tupla *arestas = nullptr;

  public:
    /**
     * @brief Construtor da classe ListaAdjacencia.
     *
     * Inicializa um grafo vazio, configurando se é direcionado e/ou ponderado.
     * Inicializa os ponteiros de vértices e arestas como nulos e os contadores
     * omo zero.
     *
     * @param direcionado Indica se o grafo é direcionado.
     * @param ponderado Indica se o grafo é ponderado.
     */
    ListaAdjacencia() = default;

    /**
     * @brief Destrutor da classe ListaAdjacencia.
     *
     * Libera a memória alocada dinamicamente para os arrays de vértices e a
     * estas.
     */
    ~ListaAdjacencia() override {
        delete[] this->arestas;
        delete[] this->vertices;
    }

    /**
     * @brief Imprime a lista de adjacência do grafo.
     *
     * Exibe, para cada vértice, seus vizinhos e os pesos das arestas (se
     * onderado). Mostra também o grau de cada vértice.
     */
    void mostrar() override {
        // Imprime cabeçalho com quantidade de vértices e arestas armazenadas
        std::cout << "Lista de Adjacência (" << tamanho << " vértices, "
                  << tArestas << " arestas armazenadas):\n"
                  << std::endl;

        // Percorre cada vértice do grafo
        for (int i = 0; i < tamanho; i++) {

            // Posição inicial da lista de vizinhos do vértice i
            int inicio = vertices[i];

            // Posição final da lista de vizinhos:
            // - se houver próximo vértice com arestas, fim = índice inicial do
            // pr ximo
            // - caso contrário (último vértice ou próximo sem vizinhos), fim =
            // tot l de arestas
            int fim = (i < tamanho - 1 && vertices[i + 1] != -1)
                          ? vertices[i + 1]
                          : tArestas;

            // Calcula o grau do vértice (quantos vizinhos ele tem)
            int grau = (inicio == -1) ? 0 : (fim - inicio);

            // Imprime índice do vértice e o grau
            std::cout << "\t" << i << " (grau " << grau << "): ";

            if (grau == 0) {
                // Caso o vértice não tenha vizinhos
                std::cout << "(sem vizinhos)";
            } else {
                // Percorre a lista de vizinhos e imprime cada vizinho
                for (int j = inicio; j < fim; j++) {
                    std::cout << arestas[j].vertice << "(" << arestas[j].peso
                              << ")" << " ";
                }
            }

            // Quebra de linha para o próximo vértice
            std::cout << "\n";
        }
    }

    /**
     * @brief Imprime a lista de adjacência do grafo utilizando rótulos p
     * rsonalizados.
     *
     * Exibe, para cada vértice, seus vizinhos e os pesos das arestas (se
     * onderado), utilizando os rótulos fornecidos no array labels.
     *
     * @param labels Array de rótulos personalizados para os vértices.
     */
    void mostrar(unsigned int *labels) override {
        // Imprime cabeçalho com quantidade de vértices e arestas armazenadas
        std::cout << "Lista de Adjacência (" << tamanho << " vértices, "
                  << tArestas << " arestas armazenadas):\n"
                  << std::endl;

        // Percorre cada vértice do grafo
        for (int i = 0; i < tamanho; i++) {

            // Posição inicial da lista de vizinhos do vértice i
            int inicio = vertices[i];

            // Posição final da lista de vizinhos:
            // - se houver próximo vértice com arestas, fim = índice inicial do
            // pr ximo
            // - caso contrário (último vértice ou próximo sem vizinhos), fim =
            // tot l de arestas
            int fim = tArestas;
            for (int k = i + 1; k < tamanho; k++) {
                if (vertices[k] != -1) {
                    fim = vertices[k];
                    k = tamanho;
                }
            }
            /* int fim = (i < tamanho - 1 && vertices[i + 1] != -1)
                          ? vertices[i + 1]
                          : tArestas;
 */
            // Calcula o grau do vértice (quantos vizinhos ele tem)
            int grau = (inicio == -1) ? 0 : (fim - inicio);

            // Imprime índice do vértice e o grau
            std::cout << "\t" << labels[i] << " (grau " << grau << "): ";

            if (grau == 0) {
                // Caso o vértice não tenha vizinhos
                std::cout << "(sem vizinhos)";
            } else {
                // Percorre a lista de vizinhos e imprime cada vizinho
                for (int j = inicio; j < fim; j++) {
                    std::cout << labels[arestas[j].vertice] << "("
                              << arestas[j].peso << ")" << " ";
                }
            }

            // Quebra de linha para o próximo vértice
            std::cout << "\n";
        }
    }

    /**
     * @brief Adiciona um novo vértice ao grafo.
     *
     * Realoca o array de vértices para acomodar o novo vértice e inicializa sua
     * l sta de adjacência como vazia.
     *
     * @return Novo tamanho do grafo (quantidade de vértices) ou -1 em caso de
     * alha de alocação.
     */
    int adicionarVertice() override {
        if (vertices == nullptr)
            vertices = new int[1];
        else {
            int *temp = new int[tamanho + 1];
            std::copy(vertices, vertices + tamanho, temp);
            delete[] vertices;
            vertices = temp;
        }

        if (vertices == nullptr)
            return -1;

        vertices[tamanho] = -1;
        tamanho++;

        return tamanho - 1;
    }

    /**
     * @brief Adiciona uma aresta entre dois vértices.
     *
     * Insere uma nova aresta do vértice u para o vértice v, com peso p (ou 1 se
     * n o ponderado). Se o grafo não for direcionado, adiciona também a aresta
     * i versa. Realoca e ajusta os arrays conforme necessário.
     *
     * @param u Índice do vértice de origem.
     * @param v Índice do vértice de destino.
     * @param p Peso da aresta (opcional, padrão 1).
     * @return true se a aresta foi adicionada com sucesso, false em caso de
     * falha de alocação.
     */
    bool adicionarAresta(int u, int v, int p = 1) override {
        if (arestas == nullptr) {
            arestas = new tupla[1];
            arestas->vertice = v;
            arestas->peso = p;
        } else {
            tupla *temp = new tupla[tArestas + 1];
            std::copy(arestas, arestas + tArestas, temp);
            delete[] arestas;
            arestas = temp;
        }

        if (arestas == nullptr)
            return false;

        // Se o vértice u não for o último da lista,
        // é necessário deslocar os ponteiros e arestas
        int endPos = tArestas;
        if (u < tamanho - 1) {
            for (int i = u + 1; i < tamanho; i++) {
                if (vertices[i] != -1) {
                    endPos = vertices[i];
                    break;
                }
            }

            for (int i = tArestas; i > endPos; i--)
                arestas[i] = arestas[i - 1];
            for (int i = u + 1; i < tamanho; i++)
                if (vertices[i] > -1)
                    vertices[i]++;

            if (vertices[u] == -1)
                vertices[u] = endPos;

        } else if (vertices[u] == -1)
            vertices[u] = tArestas;

        arestas[endPos].vertice = v;
        arestas[endPos].peso = p;
        tArestas++;

        return true;
    }

    /**
     * @brief Retorna o número de vértices do grafo.
     *
     * @return Quantidade de vértices atualmente no grafo.
     */
    int getTamanho() override { return this->tamanho; }

    bool caminhamentoEmProfundidade(int v) override {
        bool *marca = new bool[tamanho];
        for (int i = 0; i < tamanho; i++) {
            marca[i] = false;
        }

        std::stack<int> *fila = new std::stack<int>;
        int i = 0, j = 0;
        fila->push(v);

        while (!fila->empty()) {
            // insere na fila
            // label[8] = 3 significa q o 4º vértice (vertice[3]) chama 3
            // vertice[3] tem a posição do 4º vértice na lista de adjacência (are
            // tas[vertice[3]])
            int y = fila->top();
            fila->pop();
            if (!marca[y]) {
                int x = vertices[y];
                if (x != -1) {
                    int endPos = tArestas;
                    for (int i = y + 1; i < tamanho; i++)
                        if (vertices[i] != -1) {
                            endPos = vertices[i];
                            i = tamanho;
                        }
                    while (x < endPos) {
                        fila->push(arestas[x].vertice);
                        x++;
                    }
                }
                marca[y] = true;
            }
        }

        delete[] marca;
        delete fila;
        return true;
    }

    bool caminhamentoEmLargura(int v) override {
        bool *marca = new bool[tamanho];
        for (int i = 0; i < tamanho; i++) {
            marca[i] = false;
        }
        std::queue<int> *fila = new std::queue<int>;
        int i = 0, j = 0;
        fila->push(v);

        while (!fila->empty()) {
            // insere na fila
            // label[8] = 3 significa q o 4º vértice (vertice[3]) chama 3
            // vertice[3] tem a posição do 4º vértice na lista de adjacência (are
            // tas[vertice[3]])
            int y = fila->front();
            fila->pop();
            if (!marca[y]) {
                int x = vertices[y];
                if (x != -1) {
                    int endPos = tArestas;
                    for (int i = y + 1; i < tamanho; i++)
                        if (vertices[i] != -1) {
                            endPos = vertices[i];
                            i = tamanho;
                        }
                    while (x < endPos) {
                        fila->push(arestas[x].vertice);
                        x++;
                    }
                }
                marca[y] = true;
            }
        }

        delete[] marca;
        delete fila;
        return true;
    }

    std::size_t getMemoriaOcupada() override {
        std::size_t t = sizeof(int *);
        t += sizeof(int) * tamanho;
        t += sizeof(tupla *);
        t += sizeof(tupla) * tArestas;
        return t;
    }
};
