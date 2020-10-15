package tarea3;

import java.util.Scanner;
import java.util.Random;

public class Cientifico implements Trabajo {


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
			System.out.println("1-Investigar");
			System.out.println("2-Experimentar");
			
			res = lectura.nextInt();
			if(res == 1){
				System.out.println(adulto.getNombre() + ": Voy a empezar a escribir un nuevo paper!");
				this.investigar(adulto);
			}
			else{
				System.out.println(adulto.getNombre() + ": Vamos al laboratorio a experimentar!");
				this.experimentar(adulto);
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

	Funcion: Investigar

	Input: Adulto

	Funcionalidad: Por investigar el adulto gana entre 10 a 20 monedas y 
				   pierde entre 10 a 15 de energia

	*/

	public void investigar(Adulto adulto){
		Random rand = new Random();
		int dinero, energia;

		//NextInt(11) -> 0, 10 -> 10 20
		dinero = rand.nextInt(11) + 10;
		energia = rand.nextInt(6) + 10;

		System.out.println(adulto.getNombre() + ": OOOH! Este paper me salio de pana banana");
		System.out.println(adulto.getNombre() + ": Gane  " + dinero + " aunque me canse  " + energia);
		adulto.setDinero(adulto.getDinero() + dinero);
		adulto.setEnergia(adulto.getEnergia() - energia);
	}

	/*

	Funcion: Experimentar

	Input: Adulto

	Funcionalidad: Por experimentar el adulto gana entre 10 a 30 monedas y 
				   pierde entre 10 a 20 de energia

	*/

	public void experimentar(Adulto adulto){
		Random rand = new Random();
		int dinero, energia;

		dinero = rand.nextInt(21) + 10;
		energia = rand.nextInt(11) + 10;

		System.out.println(adulto.getNombre() + ": *BOOOM* Uf casi exploto el lugar, pero fue un experimento interesante!"); 
		System.out.println(adulto.getNombre() + ": Gane  " + dinero + " aunque me canse  " + energia);
		adulto.setDinero(adulto.getDinero() + dinero);
		adulto.setEnergia(adulto.getEnergia() - energia);
	}





}