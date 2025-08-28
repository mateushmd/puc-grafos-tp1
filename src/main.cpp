#include "Grafo.hpp"
#include "ListaAdjacencia.hpp"
#include "MatrizAdjacencia.hpp"
#include <chrono>
#include <iostream>

#define TAM 15 // Reduzido para não poluir excessivamente o terminal

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

    // Testa matriz de adjacência

    const auto inicio_gera_matriz = std::chrono::high_resolution_clock::now();

    MatrizAdjacencia *matriz = new MatrizAdjacencia();
    Grafo *grafoMatriz = new Grafo(matriz, direcionado, ponderado, rotulado);

    for (int i = 0; i < TAM; i++)
        grafoMatriz->adicionarVertice(i);

    for (int i = 0; i < TAM; i++) {
        for (int j = i + 1; j < TAM; j++) {
            if ((i + j) % (TAM / 2) == 0)
                grafoMatriz->adicionarAresta(i, j, i + j);
        }
    }

    const auto fim_gera_matriz = std::chrono::high_resolution_clock::now();

    const auto inicio_imprime_matriz =
        std::chrono::high_resolution_clock::now();
    grafoMatriz->mostrar();
    const auto fim_imprime_matriz = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> tempo_gerar_matriz =
        fim_gera_matriz - inicio_gera_matriz;
    std::chrono::duration<double, std::milli> tempo_imprimir_matriz =
        fim_imprime_matriz - inicio_imprime_matriz;

    std::cout << "\nTempo para gerar: " << tempo_gerar_matriz.count() << " ms"
              << std::endl;

    std::cout << "\nTempo para exibir: " << tempo_imprimir_matriz.count()
              << " ms" << std::endl;

    std::cout << "\nTempo total: "
              << tempo_imprimir_matriz.count() + tempo_gerar_matriz.count()
              << " ms" << std::endl;
    delete grafoMatriz;

    std::cout << "\n-----------------------------------------------------------"
                 "-------------------------------------\n"
              << std::endl;

    // Testa lista de adjacência

    const auto inicio_gera_lista = std::chrono::high_resolution_clock::now();

    ListaAdjacencia *lista = new ListaAdjacencia();
    Grafo *grafoLista = new Grafo(lista, direcionado, ponderado, rotulado);

    for (int i = 0; i < TAM; i++)
        grafoLista->adicionarVertice(i);

    for (int i = 0; i < TAM; i++) {
        for (int j = i + 1; j < TAM; j++) {
            if ((i + j) % (TAM / 2) == 0)
                grafoLista->adicionarAresta(i, j, i + j);
        }
    }

    const auto fim_gera_lista = std::chrono::high_resolution_clock::now();

    const auto inicio_imprime_lista = std::chrono::high_resolution_clock::now();
    grafoLista->mostrar();
    const auto fim_imprime_lista = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> tempo_imprimir_lista =
        fim_imprime_lista - inicio_imprime_lista;
    std::chrono::duration<double, std::milli> tempo_gerar_lista =
        fim_gera_lista - inicio_gera_lista;

    std::cout << "\nTempo para gerar: " << tempo_gerar_lista.count() << " ms"
              << std::endl;

    std::cout << "\nTempo para exibir: " << tempo_imprimir_lista.count()
              << " ms" << std::endl;

    std::cout << "\nTempo total: "
              << tempo_imprimir_lista.count() + tempo_gerar_lista.count()
              << " ms" << std::endl;

    delete grafoLista;
}

int main() {
    for (int i = 0; i < 8; ++i) {
        bool direcionado = bool(i & 1);
        bool ponderado = bool(i & 2);
        bool rotulado = bool(i & 4);
        testarImplementacoes(direcionado, ponderado, rotulado);
    }

    return 0;
}
