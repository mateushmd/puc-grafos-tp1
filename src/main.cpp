#include "Grafo.hpp"
#include "ListaAdjacencia.hpp"
#include "MatrizAdjacencia.hpp"
#include <chrono>
#include <iostream>

#define TAM 9 // Reduzido para não poluir excessivamente o terminal

/**
 * @brief Testa e compara as implementações de Matriz e Lista de Adjacência para
 * um dado tipo de grafo.
 *
 * @param direcionado Se o grafo é direcionado.
 * @param ponderado Se o grafo é ponderado.
 * @param rotulado Se o grafo é rotulado.
 */
void testarImplementacoes(bool direcionado, bool ponderado, bool rotulado) {
    std::cout << "\n==========================================================="
                 "====================================="
              << std::endl;
    std::cout << "\t\t\tTestando Grafo: "
              << (direcionado ? "Direcionado" : "Não-Direcionado") << ", "
              << (ponderado ? "Ponderado" : "Não-Ponderado") << ", "
              << (rotulado ? "Rotulado" : "Não-Rotulado");
    std::cout << "\n==========================================================="
                 "=====================================\n"
              << std::endl;

    // Teste com Matriz de Adjacência
    auto inicio_criacao_matriz = std::chrono::high_resolution_clock::now();

    MatrizAdjacencia *matriz = new MatrizAdjacencia();
    Grafo *grafoMatriz = new Grafo(matriz, direcionado, ponderado, rotulado);

    for (int i = 0; i < TAM; i++) {
        grafoMatriz->adicionarVertice(i);
    }
    for (int i = 0; i < TAM; i++) {
        for (int j = i + 1; j < TAM; j++) {
            if ((i + j) % (TAM / 2) == 0)
                grafoMatriz->adicionarAresta(i, j, i + j);
        }
    }

    auto fim_criacao_matriz = std::chrono::high_resolution_clock::now();
    auto inicio_exibicao_matriz = std::chrono::high_resolution_clock::now();
    grafoMatriz->mostrar();
    auto fim_exibicao_matriz = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tempo_criacao_matriz =
        fim_criacao_matriz - inicio_criacao_matriz;
    std::chrono::duration<double, std::milli> tempo_exibicao_matriz =
        fim_exibicao_matriz - inicio_exibicao_matriz;
    std::cout << "\nTempo para gerar: " << tempo_criacao_matriz.count() << " ms"
              << std::endl;
    std::cout << "\nTempo para exibir: " << tempo_exibicao_matriz.count()
              << " ms" << std::endl;

    std::cout << "\nTempo total: "
              << tempo_exibicao_matriz.count() + tempo_criacao_matriz.count()
              << " ms" << std::endl;
    delete grafoMatriz;

    std::cout << "\n-----------------------------------------------------------"
                 "-------------------------------------\n"
              << std::endl;

    // Teste com Lista de Adjacência
    ListaAdjacencia *lista = new ListaAdjacencia();
    Grafo *grafoLista = new Grafo(lista, direcionado, ponderado, rotulado);

    auto inicio_criacao_lista = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < TAM; i++) {
        grafoLista->adicionarVertice(i);
    }
    for (int i = 0; i < TAM; i++) {
        for (int j = i + 1; j < TAM; j++) {
            if ((i + j) % (TAM / 2) == 0) {
                grafoLista->adicionarAresta(i, j, i + j);
            }
        }
    }
    auto fim_criacao_lista = std::chrono::high_resolution_clock::now();

    auto inicio_exibicao_lista = std::chrono::high_resolution_clock::now();
    grafoLista->mostrar();
    auto fim_exibicao_lista = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tempo_exibicao_lista =
        fim_exibicao_lista - inicio_exibicao_lista;
    std::chrono::duration<double, std::milli> tempo_criacao_lista =
        fim_criacao_lista - inicio_criacao_lista;
    std::cout << "\nTempo para gerar: " << tempo_criacao_lista.count() << " ms"
              << std::endl;
    std::cout << "\nTempo para exibir: " << tempo_exibicao_lista.count()
              << " ms" << std::endl;
    std::cout << "\nTempo total: "
              << tempo_exibicao_lista.count() + tempo_criacao_lista.count()
              << " ms" << std::endl;

    delete grafoLista;
}

int main() {
    // Gera testes para todas as 8 combinações de tipos de grafo
    for (int i = 0; i < 8; ++i) {
        bool direcionado = (i & 1) != 0;
        bool ponderado = (i & 2) != 0;
        bool rotulado = (i & 4) != 0;
        testarImplementacoes(direcionado, ponderado, rotulado);
    }

    return 0;
}
