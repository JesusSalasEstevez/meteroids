#include <iostream>
#include <cstdlib>
#include "Asteroides.h"
#include "PoliReg.h"
#include "Punto2D.h"
#include "raylib.h"

using namespace std;

void eliminaPos(Asteroides *ast, int pos_ini, int &util){
    for(int i = pos_ini; i < util-1 ;i++)
        ast[i] = ast[i+1];
    util --;
}

int main(){
    int m = 0;
    
    Punto2D aux;
    
    //Dimensiones de la pantalla
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    //Declaración de la nave
    aux.setXY(400,400);
    PoliReg pol_nave(3,aux,20);
    pol_nave.rotar(3.3*M_PI/4);
    aux.setXY(0.0, 0.0);
    Asteroides nave(pol_nave, aux, 0.0);
    
    //Declaración de los proyectiles
    int util_p = 0;
    int capacidad_p = 10;
    Asteroides proyectil[capacidad_p];
    
    
    //Declaración de los asteroides
    int util_a = 10;
    int capacidad_a = 10;
    Asteroides asteroides[capacidad_a];
    
    //Declaración de vidas
    int capacidad_v = 3;
    int util_v = 3;
    Asteroides vidas[capacidad_v];
    for(int i = 0; i < capacidad_v; i++){
        vidas[i].setVelocidad(aux);
        aux.setXY(screenWidth - 30*(i+1), 15);
        PoliReg vida_aux(nave.getRoca().getLados(),aux,15.0);
        vida_aux.rotar(3.3*M_PI/4);
        vidas[i].setRoca(vida_aux);
    }
    int margen = 30;
    
    //Velocidades predeterminadas
    Punto2D RIGHT(6.0,0.0);
    Punto2D LEFT(-6.0,0.0);
    Punto2D STOP(0.0,0.0);
    Punto2D VELPROYECTIL(0.0,-3.0);
    
    //Inicialización de la pantalla
    InitWindow(screenWidth, screenHeight, "Juego Asteroides");
    
    bool pause = false;
    
    SetTargetFPS(20);
    while(!WindowShouldClose() && !pause){
        //Movimiento de la nave
        if(IsKeyPressed(KEY_RIGHT))
            nave.setVelocidad(RIGHT);
        else if(IsKeyPressed(KEY_LEFT))
            nave.setVelocidad(LEFT);
        
        //Colisión de la nave con las paredes
        if(nave.getRoca().getCentro().getX()-nave.getRoca().getRadio() <= 0 && !IsKeyPressed(KEY_RIGHT)){
            nave.setVelocidad(STOP);
        }
        else if(nave.getRoca().getCentro().getX()+nave.getRoca().getRadio()>=screenWidth && !IsKeyPressed(KEY_LEFT)){
            nave.setVelocidad(STOP);
            nave.getRoca().getCentro().setXY(screenWidth-200-nave.getRoca().getRadio(),nave.getRoca().getCentro().getY());
        }
        
        //Mecanica de los proyectiles
        if(IsKeyPressed(KEY_UP) && util_p < capacidad_p){
            aux.setXY(nave.getRoca().getCentro().getX(), nave.getRoca().getCentro().getY());
            PoliReg proyect_ini(3, aux, 15.0);
            proyect_ini.rotar(3.3*M_PI/4);
            proyectil[util_p].setRoca(proyect_ini);
            proyectil[util_p].setVelocidad(VELPROYECTIL);
            proyectil[util_p].setGiro(0.0);
            util_p ++;
        }
        
        //Desaparición del proyectil
        if(proyectil[0].getRoca().getCentro().getY()+ proyectil[0].getRoca().getRadio() <= 0 && util_p > 0){
            if(util_p > 1)
                eliminaPos(proyectil, 0, util_p);
            else
                util_p--;
        }
        
        //Colision asteroides
        for(int i = util_a-1; i >= 0; i--){
            //Colision con otros asteroides
            for(int j = i+1; j < util_a; j++){
                if(asteroides[i].colisiones(asteroides[j])){
                    aux.setXY(asteroides[i].getVelocidad().getX(), asteroides[i].getVelocidad().getY());
                    asteroides[i].setVelocidad(asteroides[j].getVelocidad());
                    asteroides[j].setVelocidad(aux);
                }
            }
            
            //Colision con proyectiles
            for(int j = 0; j < util_p; j++)
                if(asteroides[i].colisiones(proyectil[j])){
                    if(asteroides[i].getRoca().getLados() > 3)
                        asteroides[i].eliminaVertice();
                    else
                        if(util_a > 1)
                            eliminaPos(asteroides, i, util_a);
                        else
                            util_a --;
                    eliminaPos(proyectil, j, util_p);
                    
                }
            //Colision con las paredes
            if(asteroides[i].getRoca().getCentro().getX() + asteroides[i].getRoca().getRadio() >= screenWidth)
                asteroides[i].cambiaX();
            else 
                if(asteroides[i].getRoca().getCentro().getX() - asteroides[i].getRoca().getRadio() <= 0)
                    asteroides[i].cambiaX();
            
            if(asteroides[i].getRoca().getCentro().getY() + asteroides[i].getRoca().getRadio() >= screenHeight){
                asteroides[i].cambiaY();
            }
            else if(asteroides[i].getRoca().getCentro().getY() - asteroides[i].getRoca().getRadio() <= 0){
                asteroides[i].cambiaY();
            }
            
            //Colisión con la nave
            
            if(asteroides[i].colisiones(nave) && util_v > 0 && margen > 40){
                util_v--;
                margen = 0;
            }
            
            
        }
        
        //Movimiento
        nave.mover();
        
        for(int i = 0; i < util_p; i++)
            proyectil[i].mover();
        
        for(int i = 0; i < util_a; i++){
            asteroides[i].mover();
            asteroides[i].rotar();
        }
        
        //Dibujar
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        DrawFPS(10,40);
        
        //Dibujar nave
        if((0 <= margen && margen <= 5) || (10 <= margen && margen <= 15) || (20 <= margen && margen <= 25) || (30 <= margen && margen <= 35) || 40 <= margen){
            for(int i = 0; i < nave.getRoca().getLados()- 1; i++)
                DrawLine(nave.getRoca().getVertice(i).getX(), nave.getRoca().getVertice(i).getY(), nave.getRoca().getVertice(i+1).getX(), nave.getRoca().getVertice(i+1).getY(), BLACK);
            DrawLine(nave.getRoca().getVertice(nave.getRoca().getLados()-1).getX(), nave.getRoca().getVertice(nave.getRoca().getLados()-1).getY(),nave.getRoca().getCentro().getX(), nave.getRoca().getCentro().getY(), BLACK);
            DrawLine(nave.getRoca().getCentro().getX(), nave.getRoca().getCentro().getY(), nave.getRoca().getVertice(0).getX(), nave.getRoca().getVertice(0).getY(), BLACK);
        }
        
        //Dibujar proyectiles
        for(int i = 0; i < util_p; i++){
            for(int j = 0; j < proyectil[i].getRoca().getLados()-1;j++)
                DrawLine(proyectil[i].getRoca().getVertice(j).getX(), proyectil[i].getRoca().getVertice(j).getY(), proyectil[i].getRoca().getVertice(j+1).getX(), proyectil[i].getRoca().getVertice(j+1).getY(), BLACK);
            DrawLine(proyectil[i].getRoca().getVertice(proyectil[i].getRoca().getLados()-1).getX(), proyectil[i].getRoca().getVertice(proyectil[i].getRoca().getLados()-1).getY(), proyectil[i].getRoca().getCentro().getX(), proyectil[i].getRoca().getCentro().getY(), BLACK);
            DrawLine(proyectil[i].getRoca().getCentro().getX(), proyectil[i].getRoca().getCentro().getY(), proyectil[i].getRoca().getVertice(0).getX(), proyectil[i].getRoca().getVertice(0).getY(), BLACK);
        }
        
        //Dibujar Asteroides
        for(int i = 0; i < util_a; i++){
            for(int j = 0; j < asteroides[i].getRoca().getLados()-1; j++)
                DrawLine(asteroides[i].getRoca().getVertice(j).getX(), asteroides[i].getRoca().getVertice(j).getY(), asteroides[i].getRoca().getVertice(j+1).getX(), asteroides[i].getRoca().getVertice(j+1).getY(), BLACK);
            DrawLine(asteroides[i].getRoca().getVertice(asteroides[i].getRoca().getLados()-1).getX(), asteroides[i].getRoca().getVertice(asteroides[i].getRoca().getLados()-1).getY(), asteroides[i].getRoca().getVertice(0).getX(),asteroides[i].getRoca().getVertice(0).getY(),BLACK);
        }
        
        //Dibujar Vidas
        for(int i = 0; i < util_v; i++){
            for(int j = 0; j < vidas[i].getRoca().getLados()-1; j++)
                DrawLine(vidas[i].getRoca().getVertice(j).getX(), vidas[i].getRoca().getVertice(j).getY(), vidas[i].getRoca().getVertice(j+1).getX(), vidas[i].getRoca().getVertice(j+1).getY(), BLACK);
            DrawLine(vidas[i].getRoca().getVertice(vidas[i].getRoca().getLados()-1).getX(),vidas[i].getRoca().getVertice(vidas[i].getRoca().getLados()-1).getY(), vidas[i].getRoca().getCentro().getX(), vidas[i].getRoca().getCentro().getY(),BLACK);
            DrawLine(vidas[i].getRoca().getCentro().getX(), vidas[i].getRoca().getCentro().getY(), vidas[i].getRoca().getVertice(0).getX(), vidas[i].getRoca().getVertice(0).getY(), BLACK);
        }
        if(util_v == 0|| util_a == 0){
            nave.setVelocidad(STOP);
            for(int i = 0; i < util_p; i++)
                proyectil[i].setVelocidad(STOP);
            for(int i = 0; i < util_a; i++)
                asteroides[i].setVelocidad(STOP);
            if(util_v == 0)
                DrawText("GAME OVER", 100, 200, 20, BLACK);
            else
                DrawText("WIN", 100, 200, 20, BLACK);
            if(m == 60)
                pause = true;
            m++;
        }
        margen ++;
        
        EndDrawing();
    }
    CloseWindow();
}
