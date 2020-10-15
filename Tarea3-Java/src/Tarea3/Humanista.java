package tarea3;

import java.util.Random;
import java.util.Scanner;
public class Humanista implements Trabajo{
/*

	Funcion: Trabajar

	Input: Adulto, Int

	Funcionalidad: Hace elegir adulto entre sus 2 pegas posibles, y eso una cantidad de Horas.
				   Si es que el cansancio es menor a 0, se setea cansancio a 0 y se para el ciclo.

	*/
    public void trabajar(Adulto adulto, int horas, Scanner lectura){
        int res;
    
        while(horas-- > 0){
                System.out.println(adulto.getNombre() + ":  ¿En que trabajare esta hora?");
                System.out.println("1-Enseñar");
                System.out.println("2-Escribir");
                res = lectura.nextInt();
                if(res == 1){
                    System.out.println(adulto.getNombre() + ": Voy a enseñarle algo a estos cabros inutiles");
            this.ensenar(adulto);
                }
                else{
                    System.out.println(adulto.getNombre() + ": Voy a empezar a escribir una nueva poesia!");
                    this.escribir(adulto);
                }
    
                if(adulto.getEnergia() < 0){
            adulto.setEnergia(0);
            System.out.println(adulto.getNombre() + ": Puff estoy muy cansado, no doy más. A veces me gustaría ser un fontanero que rescata princesas...");
            break;
                }
                if(horas == 0){
                    System.out.println(adulto.getNombre() + ": Hoy fue un día increible :D.");
                }
            }
        }
            
        /*
    
        Funcion: Enseñar
    
        Input: Adulto
    
        Funcionalidad: Por enseñar el adulto gana entre 9 a 13 monedas y 
                       pierde entre 6 a 9 de energia
    
        */
    
        public void ensenar(Adulto adulto){
        Random rand = new Random();
        int dinero, energia;
    
        dinero = rand.nextInt(5) + 9;
        energia = rand.nextInt(4) + 6;
    
        System.out.println(adulto.getNombre() + ": Los cabros no entendieron nada, pero lo bueno es que me pagan.");
        System.out.println(adulto.getNombre() + ": Gane  " + dinero + " aunque me canse  " + energia);
        adulto.setDinero(adulto.getDinero() + dinero);
        adulto.setEnergia(adulto.getEnergia() - energia);
        }
    
        /*
    
        Funcion: Escribir
    
        Input: Adulto
    
        Funcionalidad: Por experimentar el adulto gana entre 4 a 14 monedas y 
                       pierde entre 4 a 13 de energia
    
        */
    
        public void escribir(Adulto adulto){
        Random rand = new Random();
        int dinero, energia;
    
        dinero = rand.nextInt(11) + 4;
        energia = rand.nextInt(10) + 4;
    
        System.out.println(adulto.getNombre() + ": Waa quede todo inspirao con este escrito, me quedo weno si"); 
        System.out.println(adulto.getNombre() + ": Gane  " + dinero + " aunque me canse  " + energia);
        adulto.setDinero(adulto.getDinero() + dinero);
        adulto.setEnergia(adulto.getEnergia() - energia);
        }
    
    
    
}