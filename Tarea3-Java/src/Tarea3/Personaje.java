package tarea3;

public abstract class Personaje {

	private String nombre;
	private String sexo;
	private int dinero;
	private int edad;
	private int energia;
	private int fuerza;
	private int comida;

	//Getters de cada atributo

	public String getNombre(){
		return this.nombre;
	}

	public String getSexo(){
		return this.sexo;
	}

	public int getDinero(){
		return this.dinero;
	}

	public int getEdad(){
		return this.edad;
	}
	public int getEnergia(){
		return this.energia;
	}

	public int getFuerza(){
		return this.fuerza;
	}

	public int getComida(){
		return this.comida;
	}

	//Setters de cada atributo
	public void setNombre(String nombre){
		this.nombre = nombre;
	}

	public void setSexo(String sexo){
		this.sexo = sexo;
	}

	public void setDinero(int dinero){
		this.dinero = dinero;
	}

	public void setEdad(int edad){
		this.edad = edad;
	}
	public void setEnergia(int energia){
		this.energia = energia;
	}

	public void setFuerza(int fuerza){
		this.fuerza = fuerza;
	}

	public void setComida(int comida){
		this.comida = comida;
	}

	//Metodos abstractos a implementar en cada clase hijo
	public abstract void comer(int comidita);

	public abstract void dameAlimento(int dinero);

	public abstract void dormir();
	

}