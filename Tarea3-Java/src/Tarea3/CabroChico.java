package tarea3;
import java.util.Random;

public class CabroChico extends Personaje{
    Random rand = new Random();
    CabroChico(String nombre, String sexo, int dinero, int edad, int energia, int fuerza, int comida){
        this.setNombre(nombre);
		this.setSexo(sexo);
		this.setDinero(dinero);
		this.setEdad(edad);
		this.setEnergia(energia);
		this.setFuerza(fuerza);
        this.setComida(comida);
    }

    /*
    La funcion jugar es exclusiva de CabroChico y poner a jugar a un hijo menor de 18 años. 
    El cabrochico podra encontrar comida o dinero aleatoriamente, pero siempre lo cansara.
    */
    public void jugar(){ 
        Random rand = new Random();
        int alimento, energia, dinero;
        dinero = rand.nextInt(10); //de 0 a 9, como son 10 numeros (100%) si sale 0, cumple el 10%
        alimento = rand.nextInt(20); // de 0 a 19(100%), si sale 0 cumple el 5%
        if (dinero == 0){
            dinero = rand.nextInt(2) + 2;
            this.setDinero(this.getDinero() + dinero);
            System.out.println("Me encontre "+dinero+ " monedas jugando! pal chanchito");
        }
        if (alimento == 0 ){
            alimento = rand.nextInt(2) + 1;
            this.setEnergia(this.getComida() + alimento);
            System.out.println("Me encontre "+alimento+ " galletitas en el suelo, no creo que pase nada si las guardo");

        }
        energia = rand.nextInt(9) + 2;
        this.setEnergia(this.getEnergia() - energia);
        System.out.println("Mami, ya me canse, no es menor perder "+energia+ " de energia");
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
        else if (comidita < 3){
			System.out.println("Comiste, pero no te alcanzo para subir tu fuerza");
			this.setComida(this.getComida() - comidita);
		}
		fuerza = comidita / 3;
		this.setFuerza(this.getFuerza() + fuerza);
        System.out.println("MMMMMMMH....... Comi " + comidita + " platitos (porque estoy chiquito) y gane " +fuerza+ " de fuerza >:)" );
        aux = fuerza * 3;
        this.setComida(this.getComida() - aux);
	}
    /*
    La funcion dameAlimento es una funcion de Personajes e intercambia dinero por unidades de comida.
    Segun la cantidad de dinero, el personaje obtendra unidades de comida, siendo agregadas a su inventario, mientras le resta el dinero del mismo.
    */
	public void dameAlimento(int dinero){
        int cantidad;
        if (dinero > this.getDinero()){
            System.out.println("No tienes suficiente dinero :(");
            return;
        }
        else if (dinero < 4){
            System.out.println("No te alcanza ni una unidad de comida");
            return;
        }
		cantidad = dinero/4;
		this.setComida(this.getComida() + (cantidad*6));
		this.setDinero(this.getDinero() - (cantidad*4) ); //le restara solo el dinero que ocupo, el resto lo seguira teniendo
		System.out.println("Compre " +(cantidad * 6)+ " de comidita");
	}
    /*
    La funcion dormir es una funcion de Personajes y pone a dormir al personaje para obtener un aumento aleatorio de su energia.
    Esta cantidad aleatoria sera agregada a su energia actual.
    */
	public void dormir(){
        if (this.getEnergia() == 100){
			System.out.println(this.getNombre() + ": Tengo mi energia al max, pero duermo porque soy flojo");
			return;
		}
        int recupera;
		recupera = rand.nextInt(31) + 20; //recupera entre 20 a 50 de energia
		this.setEnergia(this.getEnergia() + recupera);
		if (this.getEnergia() > 100 ){
			this.setEnergia(100);
		}
		System.out.println("Estuvo weno el tutito, recupere " + recupera + " de energia");
    }

}