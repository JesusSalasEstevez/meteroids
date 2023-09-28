#ifndef POLIREG_H
#define POLIREG_H

#include <cstdlib>
#include <cmath>
#include "Punto2D.h"
#include <iostream>
using namespace std;

class PoliReg{
    private:
        Punto2D *vertices;
        int N;
        Punto2D centro;
        float radio;
        static const int MAX_VERT = 200;
        static const int MIN_VERT = 3;
        static constexpr float MAX_RADIO = 200;
        static constexpr float MIN_RADIO = 15;
        static constexpr float PI= M_PI;
        
        void reservaMemoria(int tam);
        void liberaMemoria();
        
    public:
        
        void copiar(const PoliReg & rhs);
        PoliReg();
        
        PoliReg(int nroVert, const Punto2D & centro, float r);
        
        PoliReg(const PoliReg & otro);
        
        ~PoliReg();
        
        void agregaVertice();
        
        void eliminaVertice();
        
        void expande(int delta);
        
        void contrae(int delta);
        
        float perimetro() const;
	
	int getLados() const;
        
        void rotar(float rads);
        
        bool colision(const PoliReg & otro);
        
        void mover(float dx, float dy);
        
        PoliReg& operator=(const PoliReg& rhs);
        
        void generaVertices();
        
        Punto2D getCentro() const;
        
        float getRadio() const;
        
        Punto2D getVertice(int pos) const;
        
        int getNumVertices() const;
        
        bool operator==(const PoliReg &p2);
        
        bool operator<(const PoliReg &p2);
        
        friend ostream& operator<<(ostream &flujo, const PoliReg &poligono);
        friend istream& operator>>(istream &flujo, PoliReg &poligono);
};

#endif /*POLIREG_H*/
