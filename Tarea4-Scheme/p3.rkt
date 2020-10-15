#lang racket

(define (merge l1 l2)
  (define cont (+ (length l1) (length l2)))
  (define num_append 0)
  (do ((i cont (- i 1)) (laux '() (append laux (list num_append))))
    ((zero? i) laux)
    (cond
      ((null? l1) ;si a l1 no le quedan elementos
       (set! num_append (car l2)) ;agregar los elementos de l2 a la lista a retornar
       (set! l2 (cdr l2)))
      ((null? l2) ;si a l2 no le quedan elementos
       (set! num_append (car l1)) ;agregar los elementos de l1 a la lista a retornar
       (set! l1 (cdr l1)))
    (else  ;si ambas listas tienen elementos, comparar los primeros elementos de ambas para saber cual es mayor y agregarlo a la lista a retornar
     (cond
       ((< (car l1) (car l2))
        (set! num_append (car l1))
        (set! l1 (cdr l1)))
       (else
        (set! num_append (car l2))
        (set! l2 (cdr l2))))))))
     
          
  

(merge '(4 6 8 10) '(5 7 9 11))
