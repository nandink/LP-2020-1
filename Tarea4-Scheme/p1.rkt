#lang racket
;se define una lista para poder retornarla al final
(define listita'())

;nombre funcion: tipo, parametro: un numero
;esta funcion verifica que tipo de numero es el numero recibido por parámetro y agrega este tipo a la lista
;no retorna nada, solo agrega el tipo de numero a la lista
(define (tipo num)
  (cond
    ((integer? num) (cons 'E listita))
    ((real? num) (cons 'R listita))
    ((complex? num) (cons 'C listita))
    (else
     (cons '0 listita))))

(define (tipos numeros)
  (cond ((null? numeros) listita)  ;cuando ya no queden, retorna la lista
        (else
         (cons (tipo (car numeros))
               (tipos (cdr numeros))))))

(tipos '(4 5.1 3+4i))
