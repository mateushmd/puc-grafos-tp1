#pragma once

class Implementacao {
    protected:
        bool direcionado;
        bool ponderado;
        int tamanho;

    public:
        virtual ~Implementacao() {}
        virtual void mostrar() = 0;
        virtual void mostrar(unsigned int *labels) = 0;
        virtual int adicionarVertice() = 0;
        virtual bool adicionarAresta(int u, int v, int p = 1) = 0;
        virtual int getTamanho() = 0;
};