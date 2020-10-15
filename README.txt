Fernanda Catalina Cerda Rojas
Rol USM: 201804567-5


Notas:
-Si hay una función que no tiene Secret Level el programa imprime dos veces estos errores ya que primero los considera como basura y luego nota que pertenecían a una función que le falta el inicio. :(
-Si es que hay una funcion (Secret Level) que posea algun "jumps to", saldrá un error debido a que los parametros de la funcion no están definidos realmente, este funcionara solo cuando "jumps to" se encuentre dentro del start y end y los jugadores se encuentren definidos.
-En la funcion ejecutar_programa, no logre crear funcion, ni condicional, ni ciclo TT. Lo demás funciona, mientras no se encuentre dentro de uno de ellos. El programa se ejecutara cuando la verificacion sea correcta, pero los antes mencionados no harán nada porque si le lee uno de esos, se ejecuta "None", las otras funciones como add player, took, jumps to, show, needs a power up funcionan correctamente.
-Por lo anterior, significa que el programa funcionara al 100% cuando dentro de start game y game over tenga add player, took, jumps to, show o needs a power up.
-Lo que no verifica el programa: la sintaxis de una expresion logica, que un condicional no este vacio
-El programa asume que un Start Game o Game Over se encontrará en el archivo yahooo.txt solo una vez, por lo que solo verifica si se encuentra o no.
