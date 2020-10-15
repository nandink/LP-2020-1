package tarea3;
import java.util.Random;
import java.util.Scanner;

public class Adulto extends Personaje{

	public int estudios;
	public Trabajo trabajo;


	public int getEstudios(){
		return this.estudios;
	}
	public void setEstudios(int nombre){
		this.estudios = nombre;
	}
	public Trabajo getTrabajo(){
		return this.trabajo;
	}
	public void setTrabajo(Trabajo nombre){
		this.trabajo = nombre;
	}
	Adulto(String nombre, String sexo, int dinero, int edad, int energia, int fuerza, int comida){
		this.setNombre(nombre);
		this.setSexo(sexo);
		this.setDinero(dinero);
		this.setEdad(edad);
		this.setEnergia(energia);
		this.setFuerza(fuerza);
		this.setComida(comida);
	}
	/*
    La funcion comer es una funcion de Personajes y alimenta al personaje una cantidad "comidita" de unidades de comida.
    Segun esta cantidad, aumentara la fuerza de nuestro personaje.
    */
	public void comer(int comidita){
		int fuerza, aux;
		if (comidita > this.getComida()){
			System.out.println("No tienes la comida suficiente!!");
			return;
		}
		else if (comidita < 6){
			System.out.println("Comiste, pero no te alcanzo para subir tu fuerza");
			this.setComida(this.getComida() - comidita);
			return;
		}
		else{
			fuerza = comidita / 6;
			this.setFuerza(this.getFuerza() + fuerza);
			System.out.println("MMMMMMMH....... Comi " + comidita +  " platos (cuando tengo hambre me como una olla) y gane" +fuerza+ "de fuerza" );
			aux =  fuerza * 6;
			this.setComida(this.getComida() - aux);
		}
	}

 	/*
    La funcion dameAlimento es una funcion de Personajes e intercambia dinero por unidades de comida.
    Segun la cantidad de dinero, el personaje obtendra unidades de comida, siendo agregadas a su inventario, mientras le resta el dinero del mismo.
    */
	public void dameAlimento(int dinero){
		if (dinero > this.getDinero()){
			System.out.println("No tienes esa cantidad de dinero ahorrada!!!");
			return;
		}
		if (dinero < 4){
			System.out.println("La vendedora mira las pocas monedas que traes y te pregunta si es una broma. No puedes comprar con tan pocas monedas");
			return;
		}
		int cantidad;
		cantidad = dinero/4;
		this.setComida(this.getComida() + (cantidad*6));
		this.setDinero(this.getDinero() - (cantidad*4)); //le restara solo el dinero que ocupo, el resto lo seguira teniendo
		System.out.println("Compre " +(cantidad * 6) + " de comidita");
	} 
	/*
    La funcion dormir es una funcion de Personajes y pone a dormir al personaje para obtener un aumento aleatorio de su energia.
    Esta cantidad aleatoria sera agregada a su energia actual.
    */
	public void dormir(){
		if (this.getEnergia() == 100){
			System.out.println("Eri bien flojo durmiendo porque si, tu energia ya esta al maximo");
			return;
		}
		Random rand = new Random();
		int recupera;
		recupera = rand.nextInt(31) + 20; //recupera entre 20 a 50 de energia
		this.setEnergia(this.getEnergia() + recupera);
		if (this.getEnergia() > 100 ){
			this.setEnergia(100);
		}
		System.out.println("Estuvo weno el tutito, recupere " + recupera + " de energia");
	}
	/*
	La funcion aux_estudio es una funcion auxiliar que desplega un menu de las profesiones disponibles al estudiar.
	El usuario selecciona una profesion y esta se asignara como su empleo actual. Con la cual podra trabajar.
    */
	public void aux_estudio(Scanner lectura){
		int tr;
		System.out.println("Que deseas estudiar?");
		System.out.println("1.Cientifico");
		System.out.println("2. Humanista");
		System.out.println("3. Artista");
		System.out.println("4. Profesor de la USM (no pls)");
		System.out.print("Opcion: ");
		tr = lectura.nextInt();
		if (tr == 1){
			Cientifico cientif = new Cientifico();
			this.trabajo = cientif;
			System.out.println(this.getNombre()+ ": Ahora soy cientifico!!");
		}
		else if ( tr == 2){
			Humanista human = new Humanista();
			this.trabajo = human;
			System.out.println(this.getNombre()+ ": Ahora soy Humanista!!");

		}
		else if ( tr == 3){
			Artista art = new Artista();
			this.trabajo = art;
			System.out.println(this.getNombre()+ ": Ahora soy Artista!!");

		}
		else{
			Profesor prof = new Profesor();
			this.trabajo = prof;
			System.out.println(this.getNombre()+ ": Ahora soy Profesor.... de la usm...");
		}
		estudiar(tr);
	}
	/*
	La funcion estudiar recibe un entero identificador de cierta profesion, la cual se asigna al trabajo de nuestro personaje adulto.
	*/
	public void estudiar(int trabajito){
		this.setEstudios(trabajito);
		this.setEnergia(this.getEnergia() - 50);
		if (this.getEnergia() <= 0){
			this.setEnergia(0);
			System.out.println("Te quedaste sin energia :( debes dormir");
		}
	}
}