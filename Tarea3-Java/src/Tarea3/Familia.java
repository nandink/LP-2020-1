package tarea3;
import java.util.*;

public class Familia{
    public Adulto adulto1;
	public Adulto adulto2;
    public ArrayList<Personaje> hijos = new ArrayList<Personaje>();
    public ArrayList<Personaje> reverse = new ArrayList<Personaje>();
    Random rand = new Random();
    Scanner scan = new Scanner(System.in);

    //Getters de la clase familia
    public Adulto getAdulto1(){
		return this.adulto1;
    }
    public Adulto getAdulto2(){
		return this.adulto2;
    }
    //Setters de la clase familia
    public void setAdulto1(Adulto ad1){
		this.adulto1 = ad1;
    }
    public void setAdulto2(Adulto ad2){
		this.adulto2 = ad2;
    }


    //Esta funcion crea una lista auxiliar que revierte una lista.
    public void reverseList(ArrayList<Personaje> list, ArrayList<Personaje> reverse) {
		for (int i = list.size() - 1; i >= 0; i--) {
			reverse.add(list.get(i));
		}

		return;
	}
    /*
    La funcion alimentarHijos recibe el nombre del adulto que gastara comida para sus hijos y la cantidad de comida que se le dara si o si a cada hijo.
    */
    public void alimentarHjos(String adult, int cant){
        if (reverse.size() != 0){
        reverse.clear();
        }
        reverseList(hijos, reverse);
        if (adult == adulto1.getNombre()){ // es el adulto 1 quien da la comida
            for (int i=0; i<reverse.size();i++){
                if (adulto1.getComida() > cant){
                    reverse.get(i).setComida(reverse.get(i).getComida() + cant);
                    adulto1.setComida(adulto1.getComida() - cant);
                }
                reverse.get(i).setComida(reverse.get(i).getComida() + adulto1.getComida()); //si quedan hijos sin alimentar, le doy el resto de comida al ultimo y f
            }
        }
        else if (adult == adulto2.getNombre()){ //es el adulto 2 quien da la comida
            for (int i=0; i<reverse.size();i++){
                if (adulto2.getComida() > cant){
                    reverse.get(i).setComida(reverse.get(i).getComida() + cant);
                    adulto2.setComida(adulto2.getComida() - cant);
                }
                reverse.get(i).setComida(reverse.get(i).getComida() + adulto2.getComida()); //si quedan hijos sin alimentar, le doy el resto de comida al ultimo y f
            }
        }
    }

    /*
    La funcion hacerHijo recibe un string con el nombre del hijo que les va a llevar la cigueña, ademas se agregó como parametro un entero que indica el sexo del hijo.
    */ 
    public CabroChico hacerHijo(String hijo, int sex){
        if (sex == 0){
            CabroChico nuevo = new CabroChico(hijo,"Masculino" , 0, 0, 100, 30, 0);
            hijos.add(nuevo);
            return nuevo;
        }
        else{
            CabroChico nuevo = new CabroChico(hijo,"Femenino" , 0, 0, 100, 30, 0);
            hijos.add(nuevo);
            return nuevo;
        }
    }
    /*
    En la funcion acostarHijos los adultos de la familia ponen a dormir a cada uno de sus hijos.
    */ 
    public void acostarHijos(){
        for (int i=0; i<hijos.size();i++){
            hijos.get(i).dormir();
        }
    }
}