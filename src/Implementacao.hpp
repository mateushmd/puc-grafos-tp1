/**
 * @brief Classe base abstrata para implementações de grafos.
 *
 * Esta classe define a interface para diferentes implementações de grafos,
 * permitindo a manipulação de grafos direcionados e/ou ponderados.
 */
#pragma once

class Implementacao {
  protected:
    /**
     * @brief Número de vértices no grafo.
     */
    int tamanho;

  public:
    /**
     * @brief Destrutor virtual.
     */
    virtual ~Implementacao() {}

    /**
     * @brief Exibe a representação do grafo.
     */
    virtual void mostrar() = 0;

    /**
     * @brief Exibe a representação do grafo utilizando rótulos personalizados pa
     * a os vértices.
     * @param labels Vetor de rótulos para os vértices.
     */
    virtual void mostrar(unsigned int *labels) = 0;

    /**
     * @brief Adiciona um novo vértice ao grafo.
     * @return Índice do novo vértice adicionado.
     */
    virtual int adicionarVertice() = 0;

    /**
     * @brief Adiciona uma aresta entre dois vértices.
     * @param u Índice do vértice de origem.
     * @param v Índice do vértice de destino.
     * @param p Peso da aresta (padrão = 1).
     * @return true se a aresta foi adicionada com sucesso, false caso
     * contrário.
     */
    virtual bool adicionarAresta(int u, int v, int p) = 0;

    /**
     * @brief Obtém o número de vértices no grafo.
     * @return Número de vértices.
     */
    virtual int getTamanho() = 0;
    virtual bool BFS(int v) = 0;
    virtual bool DFS(int v) = 0;
};
