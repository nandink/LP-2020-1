class Pila:  #Clases de Pila y arbol
     def __init__(self):
         self.items = []
     def push(self, item):
         self.items.append(item)
     def pop(self):
         return self.items.pop()
class Arbol_binario:
    def __init__(self,rootObj):
        self.dato = rootObj
        self.leftChild = None
        self.rightChild = None

    def insertar_izq(self,newNode):
        if self.leftChild == None:
            self.leftChild = Arbol_binario(newNode)
        else:
            t = Arbol_binario(newNode)
            t.leftChild = self.leftChild
            self.leftChild = t

    def insertar_der(self,newNode):
        if self.rightChild == None:
            self.rightChild = Arbol_binario(newNode)
        else:
            t = Arbol_binario(newNode)
            t.rightChild = self.rightChild
            self.rightChild = t


    def nodo_der(self):
        return self.rightChild

    def nodo_izq(self):
        return self.leftChild

    def valor_raiz(self,obj):
        self.dato = obj

    def getRootVal(self):
        return self.dato
#Clases y funciones arbol_mate y evaluar_expresion_numerica fuente de runestone, modificados un poco.
import re
#Expresiones regulares utilizadas para el programa.
nombre=re.compile(r'\b[A-Za-z][A-Za-z0-9]*\b')
inicio=re.compile(r'\bStart Game\b\n?')
final=re.compile(r'\bGame Over\b\n?')
newplayer=re.compile(r'\bAdd Player ([A-Za-z][A-Za-z0-9]*)\b\n?')
output=re.compile(r'\bshow ([A-Za-z][A-Za-z0-9]*|-?[0-9]+)\b\n?')
asignacion=re.compile(r'\b([A-Za-z][A-Za-z0-9]*) took (-?[0-9]+)\b\n?')
inpput= re.compile(r'\b([A-Za-z][A-Za-z0-9]*) needs a power up\b\n?')
operador_mate=r'\+|\-|\/|\*'
mate=r'\b([A-Za-z][A-Za-z0-9]+|[0-9]+)(\+|\-|\/|\*){1}([A-Za-z][A-Za-z0-9]+|[0-9]+)\b'
exp_mate=re.compile(r'([A-Za-z][A-Za-z0-9]*) jumps to (.+)\n?')
operador=r'and|or'
comparador=r'(\>|\>\=|\=\=|\<|\<\=)'
exprlog= '\(([A-Za-z][A-Za-z0-0]*|[0-9]*)'+comparador+'([A-Za-z][A-Za-z0-0]*|[0-9]*)\)'
sif= re.compile(r'\bIt\'s a me a conditional .+ Yahoo\b\n?')
selse=re.compile("Mamma Mia...\n?")
fincondicional=re.compile("Let's Go!\n?")
ciclo=re.compile(r'YA MA .+ YAHOO!\n?')
finciclo=re.compile("AH HA!\n?")
funcion=re.compile(r'Secret Level ([A-Za-z]+) (([A-Za-z][A-Za-z0-9]*|[0-9]+)(-([A-Za-z][A-Za-z0-9]*|[0-9]+))*)\n?')
entra=re.compile(r'([A-Za-z][A-Za-z0-9]*) enters ([A-Za-z]+) (([A-Za-z][A-Za-z0-9]*|[0-9]+)(-([A-Za-z][A-Za-z0-9]*|[0-9]+))*)\n?')
retornofx=re.compile(r'\bReturn to Level ([A-Za-z][A-Za-z0-9]*|[0-9]+)\b\n?')

#Variables globales para hacer mas facil el manejo entre funciones
error_global=1
antes_S=0
player={}
despues_G=0
print("-----Consola----")
'''
len_arch
———————–
Parametro 1 (archivo) : string, recibe el nombre de un archivo de texto.
————————
La funcion cuenta las lineas del archivo de texto, retornando asi su largo.'''
def len_arch(archivo): #retorna el largo de un archivo de texto (+1)
  cont=0
  txt=open(archivo)
  for linea in txt:
    cont+=1
  txt.close()
  return cont
'''
antes
———————–
Parametro 1 (archivo) : string, recibe el nombre de un archivo de texto.
————————
La funcion cuenta las lineas que hay antes del "Start Game". Si es que nunca encuentra el inicio, retorna 1. 
Si lo encuentra, retorna una lista de las lineas anteriores al inicio'''
def antes(archivo): #retorna una lista de las lineas antes de start game, vacia si no hay y 1 si no hay start game
    y=len_arch(archivo)
    global error_global
    global antes_S
    lista_antes=[]
    txt=open(archivo,"r")
    for linea in txt:
        if inicio.fullmatch(linea)!=None:
            txt.close()
            return lista_antes
        else:
            lista_antes.append(linea)
            antes_S+=1
    if antes_S==y:
        txt.close()
        return 1
'''
despues
———————–
Parametro 1 (archivo) : string, recibe el nombre de un archivo de texto.
————————
La funcion cuenta las lineas que hay despues del "Game Over". Si es que nunca encuentra el final, retorna 1. 
Si lo encuentra, retorna una lista de las lineas posteriores al final'''
def despues(archivo):#retorna una lista de las lineas despues de game over, vacia si no hay y 1 si no hay game over
    global despues_G
    x=len_arch(archivo)
    funciones=[]
    funciones2=[]
    texto2=open(archivo,"r")
    lines=texto2.readlines()
    for linea in reversed(lines):
        if final.fullmatch(linea)!=None:
            for elemento in reversed(funciones):
              funciones2.append(elemento)
            texto2.close()
            return funciones2
        else:
            funciones.append(linea)
            despues_G+=1
    if despues_G==x:
        texto2.close()
        return 1
'''
verificar_expremate
———————–
Parametro 1 (linea) : string, recibe un string.
————————
La funcion revisa que la linea recibida cumpla ciertos requisitos para ser una expresion matematica. 
La funcion retorna 1 en caso de no cumplir formato y una lista con los elementos de la operacion en caso de si cumplirlo.'''
def verificar_expremate(linea):
    a=0
    listit= []
    numero = ''
    parentesis=0
    while a < len(linea):
        if linea[a] not in ['+', '-', '*', '/', ')','(']:  #se asume que las variables no tendran estos caracteres
            numero=numero+linea[a]
            if linea[a+1] not in ['+', '-', '*', '/', ')','(']: #esto ayuda si es que el numero es de mas de un digito
                a+=1
                continue
            else:
                listit.append(numero)
                numero=''
                a+=1
        elif linea[a] in ['+', '-', '*', '/']:
            if linea[a+1] in ['+', '-', '*', '/']: #no puede haber un operador luego de otro 
                return 1
            else:
                listit.append(linea[a])
                a+=1
                numero=''
        else:
            if linea[a] == '(':
                if a==0: #primer parentesis
                    listit.append(linea[a])
                    parentesis+=1
                    a+=1
                elif linea[a+1] == ')': #no puede haber un ()
                    return 1
                elif linea[a-1] not in ['+', '-', '*', '/', ')','(']: #no puede haber un numero antes de un (
                    return 1
                else:
                    listit.append(linea[a])
                    parentesis+=1
                    a+=1
            elif linea[a] == ')' :
                if a==(len(linea)-1): #ultimo parentesis
                    listit.append(linea[a])
                    parentesis-=1
                    a+=1
                elif linea[a+1] == '(':  #no puede haber un )(
                    return 1
                elif linea[a+1] not in ['+', '-', '*', '/', ')','(']:  #no puede haber un numero despues de un )
                    return 1
                else:
                    listit.append(linea[a])
                    parentesis-=1
                    a+=1
    if listit[0]!='(':
        return 1
    if listit[len(listit)-1]!= ')':
        return 1
    if parentesis==0:
        return listit
    else:
        return 1
'''
evaluar_expresion_numerica
———————–
Parametro 1 (root) : Recibe la raiz de un arbol
————————
La funcion recursiva, recorre el arbol y resuelve las operaciones que haya en este. Retorna el resultado total de estas.'''
def evaluar_expresion_numerica(root):
    if root.leftChild is None and root.rightChild is None: 
        return int(root.dato) 
    suma_izq = evaluar_expresion_numerica(root.leftChild) 
    suma_der = evaluar_expresion_numerica(root.rightChild) 
   
    if root.dato == '+': 
        return suma_izq + suma_der    
    elif root.dato == '-': 
       return suma_izq - suma_der     
    elif root.dato == '*': 
        return suma_izq * suma_der       
    else: 
        return suma_izq / suma_der 

'''
arbol_mate
———————–
Parametro 1 (listita) : lista, recibe una lista con los elementos de una operacion
————————
La funcion pasa una expresion matematica anteriormente revisada a un arbol. Retorna el valor de usar la funcion evaluar_expresion_matematica'''
def arbol_mate(listita):
    pilita = Pila()
    arbolito = Arbol_binario('')
    pilita.push(arbolito)
    curr = arbolito
    global player
    for i in listita:
        if i == '(':
            curr.insertar_izq('')
            pilita.push(curr)
            curr = curr.nodo_izq()

        elif i in ['+', '-', '*', '/']:
            curr.valor_raiz(i)
            curr.insertar_der('')
            pilita.push(curr)
            curr= curr.nodo_der()

        elif i == ')':
            curr = pilita.pop()

        elif i not in ['+', '-', '*', '/', ')']:
            try:  #si es que el valor se puede pasar a entero, pasarlo
                curr.valor_raiz(int(i))
                parent = pilita.pop()
                curr = parent
            except: #si el valor es una variable, insertar el valor del jugador
                a=player[i]
                curr.valor_raiz(int(a))
                parent = pilita.pop()
                curr = parent
    return evaluar_expresion_numerica(arbolito)

'''
verifica_funcion
———————–
Parametro 1 (lista) : Tipo lista de strings, recibe la lista retornada por la funcion "antes" o "despues"
————————
La funcion revisa las funciones que existen en el programa, imprime como errores las lineas que se consideran erroneas.
Retorna 1 si se encontraron errores y 0 si no se encontraron errores.'''

def verifica_funcionUp(lista,count): #verifica funciones
    global error_global
    flag_funcion=False
    flag_if=False
    flag_else=False
    marcador=False
    cicle=[]
    i=0
    aux=0
    for elemento in lista:
        if funcion.fullmatch(elemento):
            if flag_funcion==False: #primer secret level o funcion retornada antes
                flag_funcion=True
                aux=i #posicion del ultimo secret level
                marcador=True
                i+=1
            else: #si no hay un retorno previo
                for eleme in lista[aux:]: #desde el ultimo secret level en adelante
                    if eleme== lista[aux]:
                        print(f'woooooooohhh! {error_global}:{lista[aux]}')
                        error_global+=1
                        continue
                    elif funcion.fullmatch(eleme): #imprime como error hasta encontrar el siguiente secret level
                        aux=i
                        marcador=True
                        break
                    else:
                        print(f'woooooooohhh! {error_global}:{eleme}')
                        error_global+=1
                i+=1
        elif retornofx.fullmatch(elemento):
            if flag_funcion==True:
                flag_funcion=False
                aux=i #ultimo return to level
                marcador=False
                i+=1
            else: #falto definir una funcion antes
                if retornofx.fullmatch(lista[i-1]):
                    print(f'woooooooohhh! {error_global}:{lista[i]}')
                    error_global+=1
                    continue
                else:
                    for eleme in lista[aux:]: #desde el ultimo secret level en adelante
                        if eleme==lista[aux]:
                            print(f'woooooooohhh! {error_global}:{lista[aux]}')
                            error_global+=1
                            continue
                        if retornofx.fullmatch(eleme): #imprime como error hasta encontrar el siguiente return to
                            print(f'woooooooohhh! {error_global}:{eleme}')
                            marcador=False
                            error_global+=1
                            aux=i
                            break
                        else:
                            print(f'woooooooohhh! {error_global}:{eleme}')
                            error_global+=1
        else:
            if marcador==True:
                if ciclo.fullmatch(elemento):
                    cicles.append(elemento) #se agrega el inicio del ciclo a una lista
                    i+=1
                elif finciclo.fullmatch(elemento):
                    cicles.pop() #borramos el ultimo inicio de ciclo, esta lista deberia qudar de largo 0
                    i+=1
                elif sif.fullmatch(elemento):
                    if flag_if==False: #si no hay un if abierto antes
                        flag_if=True
                        i+=1
                    else:
                        error_global+=1
                        print("Error en condicional")  #REVISAR
                elif selse.fullmatch(elemento):
                    if flag_if==True and flag_else==False: #si hay un if abierto y aun no un else 
                        flag_else=True
                        i+=1
                    else: 
                        error_global+=1
                        print("Error en condicional")
                elif fincondicional.fullmatch(elemento):
                    if flag_if==True and flag_else==True: #si hay un if y un else abiertos
                        flag_if=False
                        flag_else= False #se cierran estos if y else
                    else: 
                        error_global+=1
                        print("Condicional incompleto")
                elif newplayer.fullmatch(elemento)!=None:
                    i+=1
                elif asignacion.fullmatch(elemento)!=None:
                    i+=1
                elif inpput.fullmatch(elemento)!= None:
                    i+=1
                elif output.fullmatch(elemento)!=None:
                    i+=1
                elif exp_mate.fullmatch(elemento)!=None:
                    expresion2= exp_mate.fullmatch(elemento)
                    expresion3= expresion2.group(2)
                    if verificar_expremate(expresion3)==1:
                        print(f'woooooooohhh! {error_global}:{elemento}')
                        error_global+=1
                        i+=1
                    else:
                        i+=1
                else:
                    print(f'woooooooohhh! {error_global}:{elemento}')
                    error_global+=1
                    i+=1
            else:
                print(f'woooooooohhh! {error_global}:{elemento}')
                error_global+=1
                i+=1
    if flag_funcion==True: #ultimo secret sin return
        for eleme in lista[aux:]: #desde el ultimo secret level en adelant
            print(f'woooooooohhh! {error_global}:{eleme}')
            error_global+=1
            i+=1
    if len(cicle)>0:
        print("Error en un ciclo del programa")
        print(f'woooooooohhh! {error_global}:{cicle}')
        error_global+=1
    if error_global!=1:
        return 1
    else:
        return 0
'''
verifica_main
———————–
Parametro 1 (archivo) : string, recibe el nombre de un archivo de texto.
————————
La funcion revisa todas las lineas que se encuentran entre Start Game y Game Over, imprime como errores las lineas que tengan errores.
Al igual que verificar_funcion retorna 0 si no encuentra errores y 1 si los encuentra.'''
def verifica_main(archivo): 
    global error_global
    global antes_S
    global despues_G
    desp= len_arch(archivo)-despues_G
    flag_if=False
    flag_else=False
    cicles=[]
    texto=open(archivo,"r")
    i=0
    lineas=texto.readlines()
    for linea in lineas[antes_S:desp]:
        if ciclo.fullmatch(linea):
            cicles.append(linea) #se agrega el inicio del ciclo a una lista
            i+=1
        elif finciclo.fullmatch(linea):
            cicles.pop() #borramos el ultimo inicio de ciclo, esta lista deberia qudar de largo 0
            i+=1
        elif sif.fullmatch(linea):
            if flag_if==False: #si no hay un if abierto antes
                flag_if=True
                i+=1
            else:
                error_global+=1
                print("Error en condicional")  #REVISAR
        elif selse.fullmatch(linea):
            if flag_if==True and flag_else==False: #si hay un if abierto y aun no un else 
                flag_else=True
                i+=1
            else: 
                error_global+=1
                print("Error en condicional")
        elif fincondicional.fullmatch(linea):
            if flag_if==True and flag_else==True: #si hay un if y un else abiertos
                flag_if=False
                flag_else= False #se cierran estos if y else
            else: 
                error_global+=1
                print("Condicional incompleto")
        elif newplayer.fullmatch(linea)!=None:
            i+=1
        elif asignacion.fullmatch(linea)!=None:
            i+=1
        elif inpput.fullmatch(linea)!= None:
            i+=1
        elif entra.fullmatch(linea)!=None:
            i+=1
        elif output.fullmatch(linea)!=None:
            i+=1
        elif exp_mate.fullmatch(linea)!=None:
            expresion=exp_mate.fullmatch(linea)
            oper= expresion.group(2)
            if verificar_expremate(oper)==1:
                print(f'woooooooohhh! {error_global}:{linea}')
                error_global+=1
            else:
                i+=1
                continue
        elif inicio.fullmatch(linea)!=None:
            i+=1
            continue
        elif final.fullmatch(linea)!=None:
            i+=1
            continue
        else:
            print(f'woooooooohhh! {error_global}:{linea}')
            error_global+=1
    texto.close()
    if len(cicles)>0:
        print("Error en los ciclos del programa")
        print(f'woooooooohhh! {error_global}:{cicles}')
        error_global+=1
    if error_global!=1:
        return 1
    else:
        return 0
'''
ejecutar_programa
———————–
Parametro 1 (archivo) : string, recibe el nombre de un archivo de texto.
————————
La funcion lee las lineas del archivo de texto y las va ejecutando, segun lo que estas realicen.
Esta funcion no tiene retorno.'''
def ejecutar_programa(archivo): #si está todo bien se pasa a ejecutar
  txt=open(archivo,"r")
  global player
  for linea in txt:
    if inicio.fullmatch(linea):
      pass
    elif final.fullmatch(linea):
      pass
    elif newplayer.fullmatch(linea): #agregar jugadores a una lista
      pl=newplayer.fullmatch(linea)
      player[pl.group(1)]=None
    elif asignacion.fullmatch(linea): #asignar valor (group 2) a variable (group 1)
      cant=asignacion.fullmatch(linea)
      player[cant.group(1)]=int(cant.group(2))
    elif inpput.fullmatch(linea):
      pla= inpput.fullmatch(linea)
      b=input("Input:")
      player[pla.group(1)]=b
    elif output.fullmatch(linea):
      out=output.fullmatch(linea)
      if nombre.fullmatch(out.group(1)):
        print(player[out.group(1)])
      else:
        print(out.group(1))
    elif exp_mate.fullmatch(linea):
        operacion= exp_mate.fullmatch(linea)
        jubador= operacion.group(1)
        operacion1= operacion.group(2)
        li= verificar_expremate(operacion1)
        print(arbol_mate(li))
        resul=arbol_mate(li)
        player[jubador]=resul
        
    else:
        None  #como x dios como hacer una funcion o un if o un while dios 
    txt.close()
'''
main
———————–
Parametro 1 : No recibe nada por parametro.
————————
Esta funcion analiza los resultados obtenidos de las funciones de verificar y segun estos se ve si llamar o no a la funcion ejecutar.
Retorna 1 en el caso de que no se pueda pasar a ejecutar el programa.'''
def main(): 
    print("Ejecutando codigo...")
    a=antes("yahooo.txt")
    d=despues("yahooo.txt")
    if a==1 or d==1: #no hay inicio o fin
        None
    elif a==[]:#no hay funciones antes de start game
        if d==[]:# no hay funciones despues de start game
            if verifica_main("yahooo.txt")==1:
                None
            else:
                ejecutar_programa("yahooo.txt")
        if d!=[]: #hay funciones solo despues de game over
            if verifica_funcionUp(d,despues_G)==1:
                verifica_main("yahooo.txt")
            else:
                if verifica_main("yahooo.txt")==1:
                    None
                else:
                   ejecutar_programa("yahooo.txt")
    elif a!=[]: #hay funciones antes de start game
        if d==[]: #solo hay funciones antes de start game
            if verifica_funcionUp(a,antes_S)==1:
                verifica_main("yahooo.txt")
            else:
                if verifica_main("yahooo.txt")==1:
                    None
                else:
                    ejecutar_programa("yahooo.txt")
        elif d!=[]: #hay funciones en ambos lados
            if verifica_funcionUp(a,antes_S)==0:
                if verifica_funcionUp(d,despues_G)==0:
                    if verifica_main("yahooo.txt")==0:
                        ejecutar_programa("yahooo.txt")
                    else:
                       None
                else:
                    verifica_main("yahooo.txt")
            else:
                verifica_funcionUp(d,despues_G)
                verifica_main("yahooo.txt")
    return("Termino la ejecucion.")
    


print(main()) 