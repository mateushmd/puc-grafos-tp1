#include "Grafo.hpp"
#include "ListaAdjacencia.hpp"
#include "MatrizAdjacencia.hpp"
#include <chrono>
#include <iostream>

#define TAM 5

void testarImplementacao(Implementacao *impl, const std::string &nome,
                         bool direcionado, bool medirImpressoes) {
    const auto inicio_gera = std::chrono::high_resolution_clock::now();

    Grafo *grafo = new Grafo(impl, direcionado, false, false);

    for (int i = 0; i < TAM; i++)
        grafo->adicionarVertice(i);

    for (int i = 0; i < TAM; i++) {
        for (int j = i + 1; j < TAM; j++) {
            if ((i + j) % (TAM / 2) == 0)
                grafo->adicionarAresta(i, j, i + j);
        }
    }

    const auto fim_gera = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tempo_gerar =
        fim_gera - inicio_gera;

    std::chrono::duration<double, std::milli> tempo_imprimir =
        std::chrono::milliseconds::zero();
    if (medirImpressoes) {
        const auto inicio_imprime = std::chrono::high_resolution_clock::now();
        grafo->mostrar();
        const auto fim_imprime = std::chrono::high_resolution_clock::now();
        tempo_imprimir = fim_imprime - inicio_imprime;
    }

    const auto inicio_largura = std::chrono::high_resolution_clock::now();
    grafo->caminhamentoEmLargura(0);
    const auto fim_largura = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tempo_largura =
        fim_largura - inicio_largura;

    const auto inicio_profundidade = std::chrono::high_resolution_clock::now();
    grafo->caminhamentoEmProfundidade(0);
    const auto fim_profundidade = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tempo_profundidade =
        fim_profundidade - inicio_profundidade;

    std::cout << nome << std::endl;
    std::cout << "\nTempo para gerar: " << tempo_gerar.count() << " ms"
              << std::endl;
    if (medirImpressoes)
        std::cout << "\nTempo para exibir: " << tempo_imprimir.count() << " ms"
                  << std::endl;
    std::cout << "\nTempo do caminhamento em largura: " << tempo_largura.count()
              << " ms" << std::endl;
    std::cout << "\nTempo do caminhamento em profundidade: "
              << tempo_profundidade.count() << " ms" << std::endl;
    std::cout << "\nTempo total: "
              << tempo_imprimir.count() + tempo_gerar.count() +
                     tempo_largura.count() + tempo_profundidade.count()
              << " ms" << std::endl;

    delete grafo;
}

int main() {
    for (int i = 0; i < 2; ++i) {
        bool direcionado = bool(i & 1);

        std::cout
            << "\n==========================================================="
               "====================================="
            << std::endl;
        std::cout << "\t\t\tTestando Grafo: "
                  << (direcionado ? "Direcionado" : "Não-Direcionado") << ", "
                  << "Não-Ponderado, Não-Rotulado";
        std::cout
            << "\n==========================================================="
               "=====================================\n"
            << std::endl;

        testarImplementacao(new MatrizAdjacencia(), "Matriz de Adjacência", 
                            direcionado, true);

        std::cout
            << "\n-----------------------------------------------------------"
               "-------------------------------------\n"
            << std::endl;

        testarImplementacao(new ListaAdjacencia(), "Lista de Adjacência", 
                            direcionado, true);
    }

    return 0;
}
