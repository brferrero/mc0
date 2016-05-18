#lang scheme

(define (map-aux f l backward-result)
  (cond 
    [(null? l) (reverse backward-result)]
    [else (map-aux f (cdr l) (cons (f (car l)) backward-result))]))

(define (map f l)
  (map-aux f l '()))

;; Note que a funcao map-aux poderia ser uma funcao local 
;; definida dentro da funcao map:
;;(define (map f l)
;;  (define (map-aux f l backward-result)
;;    (cond 
;;      [(null? l) (reverse backward-result)]
;;      [else (map-aux f (cdr l) (cons (f (car l)) backward-result))]))
;;  (map-aux f l '()))

