#lang racket

;recursion simple PeriS
(define (PeriS lados)
  (if (empty? lados) 0
      (+ (first lados) (PeriS (rest lados)))
      )
  )

;recursion de cola  PeriC
(define(PeriC lados)
  (let perimetro((lista lados)(a 0))
    (if(null? lista) a
       (perimetro(cdr lista)(+ a(car lista))))))


(PeriS '(1 2 3 4 5 6 7 8 9 10))
(PeriC '(1 2 3 4 5 6 7 8 9 10))

