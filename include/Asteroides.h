#ifndef ASTEROIDES_H
#define ASTEROIDES_H

#include "Punto2D.h"
#include "PoliReg.h"
#include <cstdlib>

class Asteroides{
	private:

		PoliReg roca;
		Punto2D veloc;
		float giro;


	public:
	
		Asteroides();
		Asteroides(const PoliReg & pol, const Punto2D & vel, float rads);
		void mover();
		void rotar();
		bool colisiones(const Asteroides & otro);
                PoliReg getRoca() const;
                Punto2D getVelocidad() const;
                float getGiro() const;
                void setVelocidad(const Punto2D & nuevaVel);
                void setGiro(const float g);
                void setRoca(const PoliReg & pol);
                Asteroides& operator =(const Asteroides & ast);
                void eliminaVertice();
                void cambiaX();
                void cambiaY();
                
};

#endif /*ASTEROIDES_H*/