#pragma once

#include <iostream>

#include "Implementacao.hpp"

class Grafo {
private:
    Implementacao *impl;
    bool rotulado;
    int tLabels = 0, tLabelsMax = 10;
    unsigned int* labels = nullptr;

    void realocarEspacoVetor(unsigned int **origem, int tamanhoOrigem, int tamanhoFinal){
        unsigned int* temp = new unsigned int[tamanhoFinal]; //Criando vetor com o novo tamanho
        std::copy(*origem, *origem+tamanhoOrigem, temp); //Copiando os dados do vetor de origem para o novo vetor
        delete[] *origem;  //Desalocando espaço do vetor de origem
        *origem = temp; //Apontando origem para o novo vetor
    }

    int buscarLabel(int buscar){
        int resp = -1;
        for (int i = 0; i < tLabels; i++){
            if (labels[i] == buscar){
                resp = i;
                i = tLabels;
            }
        }
        return resp;
    }
public:
    Grafo(Implementacao *implementacao, bool rotulado) : 
        tLabels(0), tLabelsMax(10), impl(implementacao), rotulado(rotulado) {
        if(rotulado){
            labels = new unsigned int[tLabelsMax];
        }
    }

    ~Grafo() {
        delete impl;
    }

    void mostrar() {
        if(rotulado){
            impl->mostrar(labels);
        } else {
            impl->mostrar();
        }
    }
    
    bool adicionarVertice(unsigned int v) {
        int novo = impl->adicionarVertice();

        if(novo == -1)
            return false;
        
        if(tLabels == tLabelsMax) {
            tLabelsMax += 10;
            realocarEspacoVetor(&labels, tLabels, tLabelsMax);
        }

        labels[novo] = v;
        tLabels++;

        return true;
    }

    bool adicionarAresta(int u, int v, int p = 0){
        if(rotulado){
            int indiceU = buscarLabel(u), indiceV = buscarLabel(v);
            if(indiceU != -1 && indiceV != -1)
                return impl->adicionarAresta(indiceU, indiceV, p);
            else
                return false;
        } else {
            return impl->adicionarAresta(u, v, p);
        }
    }

    int getTamanho() {
        return impl->getTamanho();
    }
};