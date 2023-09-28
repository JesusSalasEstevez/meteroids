#include "Asteroides.h"

Asteroides::Asteroides(){
    Punto2D centro(rand()%400,rand()%400);
    PoliReg pol(rand()%8, centro, rand()%50);
    roca = pol;
    giro = rand()%10;
    veloc.setXY(rand()%10, rand()%10);
}

Asteroides::Asteroides(const PoliReg & pol, const Punto2D & vel, float rads):roca(pol),veloc(vel){
    giro = rads;
}

void Asteroides::mover(){
    roca.mover(veloc.getX(), veloc.getY());
}

void Asteroides::rotar(){
    roca.rotar(giro);
}

bool Asteroides::colisiones(const Asteroides & otro){
    return roca.colision(otro.getRoca());
}

void Asteroides::setVelocidad(const Punto2D & nuevaVel){
    veloc.setXY(nuevaVel.getX(),nuevaVel.getY());
}

PoliReg Asteroides::getRoca() const{
    return roca;
}

Punto2D Asteroides::getVelocidad() const{
    return veloc;
}

float Asteroides::getGiro() const{
    return giro;
}

void Asteroides::setGiro(const float g){
    giro = g;
}

void Asteroides::setRoca(const PoliReg & pol){
    roca = pol;
}

Asteroides& Asteroides::operator =(const Asteroides & ast){
    giro = ast.getGiro();
    roca = ast.getRoca();
    veloc = ast.getVelocidad();
    
    return *this;
}

void Asteroides::eliminaVertice(){
    roca.eliminaVertice();
}

void Asteroides::cambiaX(){
    veloc.setXY(veloc.getX() * -1, veloc.getY());
}

void Asteroides::cambiaY(){
    veloc.setXY(veloc.getX(), veloc.getY() * -1);
}


