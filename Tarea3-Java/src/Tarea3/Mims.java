package tarea3;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Random;


public class Mims {
	static ArrayList<Personaje> personajes = new ArrayList<Personaje>();
	static ArrayList<Familia> familia = new ArrayList<Familia>();
	static int cant_acciones;
	
	/*
	La funcion crearAdulto es una funcion auxiliar que retorna un objeto de tipo Adulto.
	Esta funcion nos pedira datos para la creacion de un personaje y este será retornado para posteriormente agregarlo a una lista.
	*/
	static private Adulto crearAdulto(Scanner num, Scanner nom){
		int coso;
		String nombre;
		System.out.println("De que sexo desea su personaje?");
		System.out.println("1. Femenino");
		System.out.println("2. Masculino");
		System.out.print("Ingrese una opcion: ");
		coso = num.nextInt();
		System.out.print("Ingrese el nombre del adulto: ");
		nombre = nom.nextLine();
		if (coso == 1){
			Adulto adulto1 = new Adulto(nombre, "Femenino", 0, 18, 100, 30, 0);
			return adulto1;
		}
		else{
			Adulto adulto1 = new Adulto(nombre, "Masculino", 0, 18, 100, 30, 0);
			return adulto1;
		}
	}
	// Esta funcion únicamente agrega al adulto de la funcion anterior a la lista de personajes.
	static private void agregarAdulto(Adulto adultin){ 
		personajes.add(adultin);
	}

	/*
	La funcion casarse recibe 2 adultos que seran los novios. En caso de cumplir las condiciones necesarias, pasaran a formar una nueva familia.
	*/
	static private void casarse(Adulto ad1, Adulto ad2){
		System.out.println("---------------------");
		if (ad1 == ad2){
			System.out.println("No has encontrado a nadie que acepte casarte contigo mismo... Quiza intentalo en un par de decadas.");
			return;
		}
		for (int i = 0; i<familia.size(); i++){
			if ((familia.get(i).adulto1 == ad1) || (familia.get(i).adulto2 == ad2)){
				System.out.println("Uno de los personajes ya esta casado, no se puede volver a casar");
				return;
			}
			if ((familia.get(i).adulto1 == ad2) || (familia.get(i).adulto2 == ad1)){
				System.out.println("Uno de los personajes ya esta casado, no se puede volver a casar");
				return;
			}
		}
		Familia nuevo = new Familia();
		nuevo.adulto1 = ad1;
		nuevo.adulto2 = ad2;
		for (int i = 0; i<familia.size(); i++){
			for (int n = familia.get(i).hijos.size() - 1; n >= 0; n--){
				if ( (familia.get(i).hijos.get(n).getNombre().equals(ad1.getNombre())) || (familia.get(i).hijos.get(n).getNombre().equals(ad2.getNombre())) ){
					familia.get(i).hijos.remove(n);
				}
			}
		}
		System.out.println("Luego de una bonita ceremonia, " +ad1.getNombre()+" y "+ad2.getNombre()+" se han casado!");
		familia.add(nuevo);
		return;
	}
	// La funcion info_pj es una funcion auxiliar que imprime los datos de un personaje.
	static private void info_pj(Personaje pj){
		System.out.println("Nombre: " + pj.getNombre()+", Sexo: " + pj.getSexo()+", Edad: " + pj.getEdad() + ", Dinero: "+ pj.getDinero()+ ", Energia: " + pj.getEnergia()+", Fuerza: " + pj.getFuerza()+", Comida: " + pj.getComida());
	}
	/*
	La funcion lista_pjs es una funcion que ayuda al entendimiento del programa cuando se piden los datos por pantalla.
	Imprimira los personajes disponibles enumerados para poder seleccionar entre ellos.
	*/
	static private void lista_pjs(){
		System.out.println("--------------------------");
		for (int i= 0 ; i<personajes.size(); i++){
			System.out.println("Personaje numero "+ i + " : ");
			info_pj(personajes.get(i));
		}
		System.out.println("--------------------------");
	}
	/*
	La funcion lista_familiar es una funcion que ayuda al entendimiento del programa cuando se piden los datos por pantalla.
	Imprimira las familias disponibles enumeradas para poder seleccionar entre ellas.
	*/
	static private void lista_familias(){
		if (familia.size() == 0){
			System.out.println("No hay familias creadas. Debes casar dos adultos antes.");
			return;
		}
		int cont = 0;
		System.out.println("---------------------");
		System.out.println("Familias disponibles:");
		for (int i = 0; i < familia.size(); i++){
			System.out.println("----FAMILIA NUMERO "+cont+" ----");
			cont++;
			if ((familia.get(i).getAdulto1().getNombre()) == " " && (familia.get(i).getAdulto2().getNombre() == " ")){
				System.out.println("Padres: Muertos......");
			}
			else if ((familia.get(i).getAdulto1().getNombre()) == " " && (familia.get(i).getAdulto2().getNombre() != " ")){
				System.out.println("Padres: "+familia.get(i).getAdulto2().getNombre());
			}
			else if ((familia.get(i).getAdulto2().getNombre()) == " " && (familia.get(i).getAdulto1().getNombre() != " ")){
				System.out.println("Padres: "+familia.get(i).getAdulto1().getNombre());
			}
			else{
				System.out.println("Padres: " +familia.get(i).getAdulto1().getNombre()+" y "+familia.get(i).getAdulto2().getNombre());
			}
			if (familia.get(i).hijos.size() != 0){
				System.out.print("Hijos: ");
				hijos_familia(familia.get(i));
			}
			else{
				System.out.println("Esta familia no tiene hijos");
			}
		}
		System.out.println("---------------------");
	}

	//hijos_familia es una funcion auxiliar que imprime los datos de los personajes hijos de una familia recibida como parametro.
	static private void hijos_familia(Familia fm){
		int cont = 0;
		for (int i = 0; i< fm.hijos.size(); i++){
			System.out.println( "Hijo "+ cont + " : " + fm.hijos.get(i).getNombre()+ " Edad: " + fm.hijos.get(i).getEdad() +" |  ");
			cont++;
		}
	}
	/*
	La funcion tiempo suma un año de vida a todos los personajes cuando se han realizado 4 acciones. Revisa los casos en que los CabroChico se vuelvan adultos y 
	los casos donde los adultos cumplen 80 años. De darse el primer caso, los CabroChico pasan a ser adultos, obteniendo todas las acciones que estos pueden realizar. 
	De darse el segundo, los adultos mueren y se eliminan del juego.
	*/
	static private void tiempo(){
		Adulto adulto;
		System.out.println("--------------------------");
		System.out.println("Ha pasado un año!!!!!");
		for (int i = 0; i<personajes.size(); i++){ //sumar 1 a todas las edades
			personajes.get(i).setEdad(personajes.get(i).getEdad() + 1);
		}
		for (int j = personajes.size() - 1; j >= 0; j--){ //eliminarlos de atras para adelante
			if (personajes.get(j).getEdad() == 80){
				System.out.println(personajes.get(j).getNombre()+ " ha muerto. Vivio una larga y plena vida de 80 años. ");
				personajes.remove(personajes.get(j));
				}
		} 	
		for (int j = personajes.size() - 1; j >= 0; j--){
			if (personajes.get(j).getEdad() == 18){
				System.out.println(personajes.get(j).getNombre() + " ha crecido y esta hecho todo un adulto!!!!");
				adulto = new Adulto(personajes.get(j).getNombre(), personajes.get(j).getSexo(), personajes.get(j).getDinero(), 18 , personajes.get(j).getEnergia(), personajes.get(j).getFuerza(),personajes.get(j).getComida());
				personajes.set(j, adulto); //reemplaza el hijo de tipo cabrochico, por uno de tipo adulto
			}
		}
		for (int i = 0; i < familia.size(); i++){
			if(familia.get(i).adulto1.getEdad() == 80){
				familia.get(i).adulto1.setNombre(" ");
			}
			if(familia.get(i).adulto2.getEdad() == 80){
				familia.get(i).adulto2.setNombre(" ");
			}
		}
	}
	/*
	La funcion menos_fuerza resta 2 de fuerza a todos los personajes cuando se han realizado 4 acciones. Revisa los casos en que todos los personajes del juego lleguen a 0 de fuerza.
	De ser así, los personajes que cumplan, mueren y se eliminan del juego.
	*/
	static private void menos_fuerza(){
		System.out.println("--------------------------");	
		for (int i = 0; i<personajes.size(); i++){ //sumar 1 a todas las edades
			personajes.get(i).setFuerza(personajes.get(i).getFuerza() - 2);
		}
		for (int j = personajes.size() - 1; j >= 0; j--){ //eliminarlos de atras para adelante
			if (personajes.get(j).getFuerza() <= 0){
				System.out.println(personajes.get(j).getNombre()+ " ha muerto por ser un debilucho...... ");
				personajes.remove(personajes.get(j));
				if (personajes.size() == 0){
					return;
				}
				}
		} 
		for (int i = 0; i < familia.size(); i++){
			if(familia.get(i).adulto1.getFuerza() == 0){
				familia.get(i).adulto1.setNombre(" ");
			}
			if(familia.get(i).adulto2.getFuerza() == 0){
				familia.get(i).adulto2.setNombre(" ");
			}
		}
		for (int i = 0; i < familia.size(); i++){
			for (int j = familia.get(i).hijos.size() - 1; j >= 0; j--){ //eliminarlos de atras para adelante
				if (familia.get(i).hijos.get(j).getFuerza() == 0){
					System.out.println(personajes.get(j).getNombre()+ " ha muerto............... ");
					familia.get(i).hijos.remove(j);
				}
			}
		} 	
		System.out.println("--------------------------");	
	}
	
	/*
	La funcion jugar_pj es una funcion que desplega un menu luego de seleccionar un personaje para jugar. El menu mostrara todas las acciones disponibles para un adulto.
	Luego de seleccionar una accion para realizar, esta se ejecutara.
	*/
	static private void jugar_pj(int n, Scanner num){
		int x,b;
		System.out.println("1. Comer");
		System.out.println("2. Comprar alimento");
		System.out.println("3. Estudiar");
		System.out.println("4. Trabajar");
		System.out.println("5. Dormir");
		System.out.print("Ingresa una opcion: ");
		x = num.nextInt();
		if ( x == 1){
			System.out.print("Cuanto deseas comer?: ");
			b = num.nextInt();
			personajes.get(n).comer(b);
		}
		else if ( x == 2){ 
			System.out.print("Cuantas monedas deseas gastar en alimento? : ");
			b = num.nextInt();
			personajes.get(n).dameAlimento(b);
		}
		else if ( x == 3){
			if(personajes.get(n).getEnergia() <= 0){
				System.out.println("No puedes realizar esta accion, debes dormir porfi");
			}
			else{
				((Adulto)personajes.get(n)).aux_estudio(num);
				cant_acciones+=1;
				if (cant_acciones == 4){
					tiempo();
					cant_acciones=0;
				}
				menos_fuerza();
			}
		}
		else if ( x == 4){
			if (personajes.get(n).getEnergia() <= 0){
				System.out.println("No puedes realizar esta accion, debes dormir porfi");
			}
			else if (((Adulto)personajes.get(n)).getEstudios() == 0){
				System.out.println("No has estudiado nada, por ende, no puedes trabajar :(");
			}
			else{
				System.out.print("Cuantas horas deseas trabajar?");
				b= num.nextInt();
				((Adulto)personajes.get(n)).trabajo.trabajar((Adulto)personajes.get(n), b, num);
				cant_acciones += 1;
				if (cant_acciones == 4){
					tiempo();
					cant_acciones=0;

				}
				menos_fuerza();
			}
		}
		else {
			personajes.get(n).dormir();
			cant_acciones+= 1;
			if (cant_acciones == 4){
				tiempo();
				cant_acciones=0;
			}
			menos_fuerza();
		}
		
	}
	/*
	La funcion jugar_fam es una funcion que desplega un menu luego de seleccionar una familia para jugar. El menu mostrara todas las acciones disponibles para una familia.
	Luego de seleccionar una accion para realizar, esta se ejecutara.
	*/
	static private void jugar_fam(Familia fam, Scanner num, Scanner nom, Random rand){
		int x,a,chance;
		String name;
		if ( (fam.getAdulto1().getNombre().equals(" ")) && (fam.getAdulto2().getNombre().equals(" "))){
			System.out.println("Los padres estan muertos...... No se pueden realizar acciones de familia. Puedes jugar con los hijos seleccionandolos desde los personajes.");
			return;
		}
		System.out.println("1. Hacer hijo");
		System.out.println("2. Alimentar hijos");
		System.out.println("3. Acostar hijos");
		System.out.print("Ingresa una opcion: ");
		x = num.nextInt();
		if ( x == 1){
			chance = rand.nextInt(2);
        	if (chance == 0){
           		System.out.println("La cigueña trajo un niño!!!!! Como desea que se llame?");
            	name = nom.nextLine();
            	personajes.add(fam.hacerHijo(name, 0));
        	}
        	else if (chance == 1){
            	System.out.println("La cigueña trajo una niña!!!! Como desea que se llame?");
            	name = nom.nextLine();
            	personajes.add(fam.hacerHijo(name, 1));
        	}
			cant_acciones+=1;
			if (cant_acciones == 4){
				tiempo();
				cant_acciones=0;
			}
			menos_fuerza();
		}
		else if ( x == 2){ 
			if (fam.adulto1.getNombre().equals(" ") && (fam.adulto2.getNombre() != " ")) {
				System.out.println("Solo esta vivo el adulto 2");
				System.out.print("Cuantas unidades de comida?: ");
				a = num.nextInt();
				fam.alimentarHjos(fam.adulto2.getNombre(), a);
			}
			else if (fam.adulto2.getNombre().equals(" ") && (fam.adulto1.getNombre() != " ")){
				System.out.println("Solo esta vivo el adulto 1");
				System.out.print("Cuantas unidades de comida?: ");
				a = num.nextInt();
				fam.alimentarHjos(fam.adulto1.getNombre(), a);
			}
			else{
				System.out.println("Que adulto desea que de la comida? : "+fam.getAdulto1().getNombre()+ " o "+fam.adulto2.getNombre());
				System.out.print("Escriba el nombre del adulto: ");
				name = nom.nextLine();
				System.out.print("Cuantas unidades de comida?: ");
				a = num.nextInt();
				if (fam.adulto1.getNombre().equalsIgnoreCase(name)){
					fam.alimentarHjos(fam.adulto1.getNombre(), a);
				}
				else if (fam.adulto2.getNombre().equalsIgnoreCase(name)){
					fam.alimentarHjos(fam.adulto2.getNombre(), a);
				}
				else{
					System.out.println("El nombre ingresado no corresponde a ninguno de los 2 adultos, xfi no me trolees la tarea, ultimo aviso");
				}
			}
			cant_acciones+=1;
			if (cant_acciones == 4){
				tiempo();
				cant_acciones=0;
			}
			menos_fuerza();
		}
		else if ( x == 3){
			fam.acostarHijos();
			cant_acciones+=1;
			if (cant_acciones == 4){
				tiempo();
				cant_acciones=0;
			}
			menos_fuerza();
		}
	}
			
	/*	
	La funcion jugar_cabrochico es una funcion que desplega un menu luego de seleccionar un personaje para jugar. El menu mostrara todas las acciones disponibles para un cabrochico.
	Luego de seleccionar una accion para realizar, esta se ejecutara.
	*/
	static private void jugar_cabrochico(CabroChico cabro, Scanner num, Scanner nom){
		int x,b;	
		System.out.println("Que accion?");
		System.out.println("1. Comer");
		System.out.println("2. Comprar alimento");
		System.out.println("3. Dormir");
		System.out.println("4. Jugar");
		System.out.print("Ingresa una opcion: ");
		x = num.nextInt();
		if ( x == 1){
			System.out.print("Cuanto deseas comer?: ");
			b = num.nextInt();
			cabro.comer(b);
		}
		else if ( x == 2){ 
			System.out.print("Cuantas monedas deseas gastar en alimento? : ");
			b = num.nextInt();
			cabro.dameAlimento(b);
		}
		else if ( x ==3){
			cabro.dormir();
			cant_acciones+=1;
			if (cant_acciones == 4){
				tiempo();
				cant_acciones=0;
			}
			menos_fuerza();
		}	
		else{
			cabro.jugar();
			cant_acciones+=1;
			if (cant_acciones == 4){
				tiempo();
				cant_acciones=0;
			}
			menos_fuerza();
		}
	}
	/*
	La funcion menu principal desplegara un menu inicial que acompañara durante todo el juego. 
	En este menu se puede escoger que realizara el usuario y segun eso, se llevara a otro menu o a la accion correspondiente.
	Por otro lado, con este menu podemos finalizar el juego.
	*/
	static private void menuppal( int a, Scanner num, Scanner nom, Random rand){
		int b,c;
		do{
			System.out.println("---------------------");
			System.out.println("Que deseas hacer ahora?");
			System.out.println("1. Escoger un personaje (para que realice una accion)"); 
			System.out.println("2. Escoger una familia (para que realice una accion)"); 
			System.out.println("3. Casar a dos personajes");
			System.out.println("4. Agregar un personaje adulto");
			System.out.println("5. Salir");
			System.out.println("---------------------");
			System.out.print("Ingrese una opcion:");
			a = num.nextInt();
			if (a == 1){
				if (personajes.size() == 0 ){
					System.out.println("No hay personajes vivos, debes crear uno o terminar el juego.");
				}
				else{
					lista_pjs();
					System.out.println("Con que personaje desea realizar una accion?");
					System.out.print("Numero:");
					b= num.nextInt(); //jugar con el pj de la posicion b de la lista personajes
					if (personajes.get(b).getEdad() >=18){
						jugar_pj(b,num);
					}
					else{
						jugar_cabrochico((CabroChico)personajes.get(b), num, nom);
					}
				}
			}

			if ( a == 2){
				if (personajes.size() == 0 ){
					System.out.println("No hay personajes vivos, debes crear uno o terminar el juego.");
				}
				else{
					lista_familias();
					if (familia.size() != 0){
						System.out.println("Con que familia desea jugar?");
						System.out.print("Numero:");
						b= num.nextInt(); //jugar con la familia de la posicion b de la lista familia
						if (b>familia.size()){
							System.out.println("No existe esa familia porfi no me trolees la tareaAaa");
						}
						else{
							jugar_fam(familia.get(b), num, nom, rand);
						}
					}
				}
			}

			if (a == 3){
				if (personajes.size() == 0 ){
					System.out.println("No hay personajes vivos, debes crear uno o terminar el juego.");
				}
				else{
					System.out.println("Quienes son los novios?");
					lista_pjs();
					System.out.print("Primer personaje: ");
					b= num.nextInt();
					System.out.print("Segundo personaje: ");
					c= num.nextInt();
					casarse((Adulto)personajes.get(b), (Adulto)personajes.get(c));
					cant_acciones+=1;
					if (cant_acciones == 4){
						tiempo();
						cant_acciones=0;
					}
					menos_fuerza();

				}
			}
			if (a == 4){
				agregarAdulto(crearAdulto(num,nom));
			}
		}while (a != 5);
	}
	

	//Funcion main de nuestro programa.
	public static void main(String[] args) {
		cant_acciones = 0;
		int a = 0;
		Scanner nom = new Scanner(System.in);
		Scanner num = new Scanner(System.in);
		Random rand = new Random();
		System.out.println("BIENVENIDO A MIMS!");
		System.out.println("Para empezar el juego, debes crear 4 personajes adultos.");
		for (int i=0; i<4;i++){
			System.out.println("---------------------");
			System.out.println("Creemos el personaje numero "+i);
			agregarAdulto(crearAdulto(num,nom));
		}
		System.out.println("Personajes creados!");
		System.out.println("---------------------");
		menuppal(a, num, nom,rand);
		num.close();	
		nom.close();	
	}
}


