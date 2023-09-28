#include <cstdlib>
#include <cmath>
#include "Punto2D.h"
#include "PoliReg.h"
using namespace std;

//Constructores

PoliReg::PoliReg(){

    radio = MIN_RADIO;
    N = MIN_VERT;
    centro.setXY(0,0);

    reservaMemoria(N);
    
    generaVertices();
}

PoliReg::PoliReg(int nroVert, const Punto2D & centro, float r){
    if(nroVert < MIN_VERT || MAX_VERT < nroVert)
        N = MIN_VERT;
    else
        N = nroVert;

    if(r < MIN_RADIO || MAX_RADIO < r)
        radio = MIN_RADIO;
    else
        radio = r;

    this->centro = centro;
    
    reservaMemoria(N);

    generaVertices();
}

PoliReg::PoliReg(const PoliReg & otro){
    copiar(otro);
}

//Destructor

PoliReg::~PoliReg(){
    delete[] vertices;
}

//Gestión de memoria
void PoliReg::reservaMemoria(int tam){
    vertices = new Punto2D [tam];
}

void PoliReg::liberaMemoria(){
    delete [] vertices;
}


//Métodos generales.

void PoliReg::copiar(const PoliReg & rhs){
    this->centro.setXY(rhs.centro.getX(), rhs.centro.getY());
    this->radio = rhs.radio;
    this->N = rhs.N;
    reservaMemoria(N);
    for(int i = 0; i < N; i++)
        this->vertices[i].setXY(rhs.vertices[i].getX(), rhs.vertices[i].getY());
}
void PoliReg::agregaVertice(){
    if(N < MAX_VERT){
        liberaMemoria();
        reservaMemoria(N+1);
        N += 1;
        generaVertices();
    }
}

void PoliReg::eliminaVertice(){
    if(N > MIN_VERT){
        liberaMemoria();
        reservaMemoria(N-1);
        N -= 1;
        generaVertices();
    }
}

void PoliReg::expande(int delta){
    if(radio + delta <= MAX_RADIO){
        radio = radio + delta;
        generaVertices();
    }
}

void PoliReg::contrae(int delta){
    if(radio - delta >= MIN_RADIO){
        radio = radio - delta;
        generaVertices();
    }
}

float PoliReg::perimetro() const{
    return vertices[0].distancia(vertices[1]) * N;
}

void PoliReg::rotar(float rads){
    for(int i = 0; i < N; i++)
        vertices[i].rotar(centro,rads);
}

bool PoliReg::colision(const PoliReg & otro){
    bool colisionan = true;
    if(centro.distancia(otro.centro) > radio + otro.radio)
        colisionan = false;
    return colisionan;
}

void PoliReg::mover(float dx, float dy){
    centro.mover(dx,dy);
    for(int i = 0; i < N; i++)
        vertices[i].mover(dx, dy);
}

void PoliReg::generaVertices(){
    float x,y;
    Punto2D p;
    for(int i = 0; i < N; i++){
        x = centro.getX() + radio * cos(2*PI*i/N);
        y = centro.getY() + radio * sin(2*PI*i/N);
        p.setXY(x,y);
        vertices[i] = p;
    }
}


//Getters

Punto2D PoliReg::getCentro() const{
    return centro;
}

float PoliReg::getRadio() const{
    return radio;
}

Punto2D PoliReg::getVertice(int pos) const{
    return vertices[pos];
}

int PoliReg::getNumVertices() const{
    return N;
}

int PoliReg::getLados() const{
    return N;
}
   
//Operadores

PoliReg& PoliReg::operator=(const PoliReg& rhs){
    liberaMemoria();
    copiar(rhs);
    return *this;
}

bool PoliReg::operator==(const PoliReg &p2){
    bool iguales = true;

    if(N == p2.N){
        for(int i = 0; i < N && iguales; i++)
            if(vertices[i].getX() != p2.vertices[i].getX() || vertices[i].getY() != p2.vertices[i].getY())
                iguales = false;
    }else
        iguales = false;

    return iguales;
}

bool PoliReg::operator<(const PoliReg &p2){
    bool es_menor = true;

    if(perimetro() >= p2.perimetro())
        es_menor = false;

    return es_menor;
}

ostream& operator<<(ostream &flujo, const PoliReg &poligono){
    for(int i = 0; i < poligono.N; i++)
        flujo << poligono.vertices[i] << "\n";

    return flujo;
}

istream& operator>>(istream &flujo, PoliReg &poligono){
    string cadena;
    float r;
    Punto2D c;
    int puntos;
    poligono.liberaMemoria();
    
    flujo >> cadena >> c;
    flujo >> cadena >> r;
    flujo >> cadena >> puntos;
    
    poligono.N = puntos;
    poligono.centro.setXY(c.getX(),c.getY());
    poligono.radio = r;
    poligono.reservaMemoria(puntos);
    poligono.generaVertices();
    
    return flujo;
}
