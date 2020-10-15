package tarea3;

import java.util.Random;
import java.util.Scanner;
public class Artista implements Trabajo {

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
                System.out.println("1-Pintar");
                System.out.println("2-Esculpir");
                res = lectura.nextInt();
                if(res == 1){
                    System.out.println(adulto.getNombre() + ": Voy a pintar algo re lindo!");
            this.pintar(adulto);
                }
                else{
                    System.out.println(adulto.getNombre() + ": Manos a la obra en esta nueva escultura");
                    this.esculpir(adulto);
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
    
        Funcion: Pintar
    
        Input: Adulto
    
        Funcionalidad: Por pintar el adulto gana entre 4 a 8 monedas y 
                       pierde entre 3 a 7 de energia
    
        */
        public void pintar(Adulto adulto){
        Random rand = new Random();
        int dinero, energia;
    
        dinero = rand.nextInt(5) + 4;
        energia = rand.nextInt(5) + 3;
    
        System.out.println(adulto.getNombre() + ": Picasso se queda chico con esta pintura. Me las mande.");
        System.out.println(adulto.getNombre() + ": Gane  " + dinero + " aunque me canse  " + energia);
        adulto.setDinero(adulto.getDinero() + dinero);
        adulto.setEnergia(adulto.getEnergia() - energia);
        }
    
        /*
    
        Funcion: Esculpes
    
        Input: Adulto
    
        Funcionalidad: Por esculpir el adulto gana entre 4 a 14 monedas y 
                       pierde entre 4 a 13 de energia
    
        */
    
        public void esculpir(Adulto adulto){
        Random rand = new Random();
        int dinero, energia;
    
        dinero = rand.nextInt(11) + 4;
        energia = rand.nextInt(10) + 4;
            
        System.out.println(adulto.getNombre() + ": Igual esta medio chueco por el lado, pero de lejos se ve hermosa esta escultura."); 
        System.out.println(adulto.getNombre() + ": Gane  " + dinero + " aunque me canse  " + energia);
        adulto.setDinero(adulto.getDinero() + dinero);
        adulto.setEnergia(adulto.getEnergia() - energia);
        }
    
    
}