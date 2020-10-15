package tarea3;

import java.util.Scanner;
import java.util.Random;

public class Profesor implements Trabajo {


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
			System.out.println("1- Enviar mas tareas a los cabros");
			System.out.println("2- Hacer un control sorpresa");
			
			res = lectura.nextInt();
			if(res == 1){
				System.out.println(adulto.getNombre() + ": Voy a enviarles otra tarea, MUAHAHAHA");
				this.enviar_trabajos(adulto);
			}
			else{
				System.out.println(adulto.getNombre() + ": Y si... hago un control sorpresa? SOY UN GENIO, MUAAHAHAHA ");
				this.control(adulto);
			}

			if(adulto.getEnergia() < 0){
				adulto.setEnergia(0);
				System.out.println(adulto.getNombre() + ": Puff estoy muy cansado, no doy más. Se salvaron por ahora.");
				break;
			}
			if(horas == 0){
				System.out.println(adulto.getNombre() + ": Hoy fue un día increible :D.");
			}
		}
	}

	/*

	Funcion: Enviar Trabajos

	Input: Adulto

	Funcionalidad: Por enviar trabajos a los pobres estudiantes de la usm, el adulto gana entre 10 a 20 monedas y 
				   pierde entre 5 a 10 de energia

	*/

	public void enviar_trabajos(Adulto adulto){
		Random rand = new Random();
		int dinero, energia;

		//NextInt(11) -> 0, 10 -> 10 20
		dinero = rand.nextInt(11) + 10;
		energia = rand.nextInt(6) +5;

		System.out.println(adulto.getNombre() + ":Listo. Igual 1 dia de plazo esta bien, total no deben tener nada mas que hacer");
		System.out.println(adulto.getNombre() + ": Gane  " + dinero + " aunque me canse  " + energia);
		adulto.setDinero(adulto.getDinero() + dinero);
		adulto.setEnergia(adulto.getEnergia() - energia);
	}

	/*

	Funcion: Control

	Input: Adulto

	Funcionalidad: Por realizar un control sorpresa el adulto gana entre 10 a 30 monedas y 
				   pierde entre 10 a 20 de energia

	*/

	public void control(Adulto adulto){
		Random rand = new Random();
		int dinero, energia;

		dinero = rand.nextInt(21) + 10;
		energia = rand.nextInt(11) + 10;

		System.out.println(adulto.getNombre() + ": Pucha, igual aprobaron 5, voy a esforzarme mas para la otra"); 
		System.out.println(adulto.getNombre() + ": Gane  " + dinero + " aunque me canse  " + energia);
		adulto.setDinero(adulto.getDinero() + dinero);
		adulto.setEnergia(adulto.getEnergia() - energia);
	}





}