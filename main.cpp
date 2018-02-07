/*
   Snake avec MiniWin et Pau Fernandez. -> http://www.youtube.com/watch?v=67nH1GOddlM
                                           http://www.youtube.com/watch?v=FwhnaLZPUcQ
*/
#include "miniwin.h"
#include <list>
#include <cstdlib>
#include <sstream>
using namespace miniwin;
using namespace std;

const int XTAM = 65, YTAM = 40;
const int SZ = 20;   //12

struct Punto{
   int x;
   int y;
};

void cuadrado(const Punto& P, int c){
   color(c);
   rectangulo_lleno(P.x*SZ, P.y*SZ,(P.x+1)*SZ-1,(P.y+1)*SZ-1);
}

bool hay_choque(const Punto& cabeza, const list<Punto>& cola){
   if(cabeza.x >= XTAM || cabeza.x < 0) return true;
   if(cabeza.y >= YTAM || cabeza.y < 0) return true;
   list<Punto>::const_iterator it;
   for(it = cola.begin(); it != cola.end(); it++){
      if(cabeza.x == it->x && cabeza.y == it->y) return true;
   }
   return false;
}

Punto al_azar(){
   Punto p = {rand()% XTAM, rand()% YTAM};
   return p;
}

string vers_string(int puntos){
   stringstream sout;
   sout << puntos;
   return sout.str();
}

int main() {
   vredimensiona(XTAM*SZ, YTAM*SZ);
   JEU:
   Punto cabeza = {30,20};
   Punto comida = al_azar();
   list <Punto> cola;
   int vx= 1, vy = 0;   // Velocidad (en que direccion se esta moviendo)
   int engorda = 0;
   int retraso = 0;
   int t = tecla();
   int points = 0;
   bool choque = false;

   while(t!=ESCAPE && !choque){
      retraso++;
      //Logica del juego
      if(t==ARRIBA && vy!=1){
         vx = 0; vy = -1;
      }
      else if(t==ABAJO && vy!=-1 ){
         vx = 0; vy = +1;
      }
      else if(t==DERECHA && vx!=-1){
         vx = 1; vy = 0;
      }
      else if(t==IZQUIERDA && vx!=1){
         vx = -1; vy = 0;
      }
      if(retraso==8){
         cola.push_front(cabeza);
         if(engorda>0){
            engorda--;
         }else{
            cola.pop_back();
         }
         cabeza.x += vx;
         cabeza.y += vy;
         if(hay_choque(cabeza, cola)){
            choque = true;
         }else if (cabeza.x == comida.x && cabeza.y == comida.y){
            engorda = 5;
            points += 20;
            comida = al_azar();
            while(hay_choque(comida,cola) || comida.x == cabeza.x && comida.y == cabeza.y ){
                  comida = al_azar();
            }
         }
         retraso = 0;
      }
      if(!choque){
         //Pintar
         borra();
         list<Punto>::const_iterator it;
         for(it = cola.begin(); it != cola.end();it++){  // it est la position, de l'element
            cuadrado(*it, VERDE);                        // *it est l'element
         }
         cuadrado(cabeza, ROJO);
         cuadrado(comida, AMARILLO);
         texto((XTAM*SZ) -150, 10,"Score");
         texto((XTAM*SZ) -110, 10, vers_string(points));
         refresca();
      }
      //----------------------------------------------
      espera(10);
      t=tecla();
   }
   //borra();
   color(AMARILLO);
   texto((XTAM/2)*SZ -50, (YTAM/2)*SZ-5, "GAME OVER  !");
   refresca();
   espera(1500);
   borra();
   texto((XTAM/2)*SZ -50, (YTAM/2)*SZ-15, "RE-JOUER ?");
   texto((XTAM/2)*SZ -50, (YTAM/2)*SZ   , " [Espace] ");
   refresca();
   while(t!=ESCAPE){
         t=tecla();
         if(t==ESPACIO){
            goto JEU;
         }
         if(t==ESCAPE){
            vcierra();
         }
         refresca();
   }
   vcierra();
   return 0;
}