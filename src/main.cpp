#include "Grafo.hpp"
#include "ListaAdjacencia.hpp"
#include "MatrizAdjacencia.hpp"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>

#define TAM 300

std::vector<std::pair<int, int>> *gerarArestasDenso(bool direcionado) {
    std::vector<std::pair<int, int>> *arestas =
        new std::vector<std::pair<int, int>>();

    if (!direcionado) {
        for (int i = 0; i < TAM; i++) {
            for (int j = i + 1; j < TAM; j++) {
                arestas->push_back({i, j});
            }
        }
    } else {
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (i != j)
                    arestas->push_back({i, j});
            }
        }
    }

    return arestas;
}

std::vector<std::pair<int, int>> *gerarArestasEsparso(bool direcionado) {
    auto arestas = gerarArestasDenso(direcionado);

    std::mt19937 rng(std::time(nullptr));
    std::shuffle(arestas->begin(), arestas->end(), rng);

    int max = TAM / 3;
    arestas->erase(arestas->begin() + max, arestas->end());
    return arestas;
}

void testarImplementacao(Grafo *grafo, const std::string &nome,
                         bool medirImpressoes) {
    std::chrono::duration<double, std::milli> tempo_imprimir =
        std::chrono::milliseconds::zero();
    if (medirImpressoes) {
        const auto inicio_imprime = std::chrono::high_resolution_clock::now();
        grafo->mostrar();
        const auto fim_imprime = std::chrono::high_resolution_clock::now();
        tempo_imprimir = fim_imprime - inicio_imprime;
    }

    std::chrono::duration<double, std::milli> soma_tempos =
        std::chrono::milliseconds::zero();
    for (int i = 0; i < 100; i++) {
        const auto inicio_largura = std::chrono::high_resolution_clock::now();
        grafo->caminhamentoEmLargura(0);
        const auto fim_largura = std::chrono::high_resolution_clock::now();
        soma_tempos += fim_largura - inicio_largura;
    }
    std::chrono::duration<double, std::milli> tempo_largura = soma_tempos / 100;

    soma_tempos = std::chrono::milliseconds::zero();
    for (int i = 0; i < 100; i++) {
        const auto inicio_profundidade =
            std::chrono::high_resolution_clock::now();
        grafo->caminhamentoEmProfundidade(0);
        const auto fim_profundidade = std::chrono::high_resolution_clock::now();
        soma_tempos += fim_profundidade - inicio_profundidade;
    }
    std::chrono::duration<double, std::milli> tempo_profundidade =
        soma_tempos / 100;

    std::size_t tamanhoKb = grafo->getMemoriaOcupada() / 1024;

    std::cout << "\nEspaço ocupado em memória: " << tamanhoKb << " KB"
              << std::endl;

    if (medirImpressoes)
        std::cout << "\nTempo para exibir: " << tempo_imprimir.count() << " ms"
                  << std::endl;
    std::cout << "\nTempo do caminhamento em largura: " << tempo_largura.count()
              << " ms" << std::endl;
    std::cout << "\nTempo do caminhamento em profundidade: "
              << tempo_profundidade.count() << " ms" << std::endl;
    std::cout << "\nTempo total: "
              << tempo_imprimir.count() + tempo_largura.count() +
                     tempo_profundidade.count()
              << " ms" << std::endl;
}

int main() {
    for (int i = 0; i < 4; ++i) {
        bool direcionado = bool(i & 1);
        bool denso = bool(i & 2);

        Grafo *gMatriz =
            new Grafo(new MatrizAdjacencia(), direcionado, false, false);
        Grafo *gLista =
            new Grafo(new ListaAdjacencia(), direcionado, false, false);

        std::vector<std::pair<int, int>> *arestas = nullptr;
        if (denso)
            arestas = gerarArestasDenso(direcionado);
        else
            arestas = gerarArestasEsparso(direcionado);

        for (int i = 0; i < TAM; i++) {
            gMatriz->adicionarVertice(i);
            gLista->adicionarVertice(i);
        }

        for (int i = 0; i < arestas->size(); i++) {
            gMatriz->adicionarAresta(arestas->at(i).first,
                                     arestas->at(i).second);
            gLista->adicionarAresta(arestas->at(i).first,
                                    arestas->at(i).second);
        }

        std::cout
            << "\n==========================================================="
               "====================================="
            << std::endl;
        std::cout << "\t\t\tTestando Grafo: "
                  << (direcionado ? "Direcionado" : "Não-Direcionado") << ", "
                  << "Não-Ponderado, Não-Rotulado, "
                  << (denso ? "Denso" : "Esparso");
        std::cout
            << "\n==========================================================="
               "=====================================\n"
            << std::endl;

        testarImplementacao(gMatriz, "Matriz de Adjacência", false);

        std::cout
            << "\n-----------------------------------------------------------"
               "-------------------------------------\n"
            << std::endl;

        testarImplementacao(gLista, "Lista de Adjacência", false);

        delete gMatriz;
        delete gLista;
    }

    return 0;
}
