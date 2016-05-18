#lang plai
; EP0 - Bruno Ferrero
; MAC316   20/03/2011

; Ex. (1)
(define (simple-merge l1 l2)
  (cond
    [(empty? l1) l2]
    [(empty? l2) l1]
    [(< (first l1) (first l2))
         (cons (first l1) (simple-merge (rest l1) l2))]
    [else (cons (first l2) (simple-merge l1 (rest l2)))]))

;testes
(test (simple-merge (list) (list)) empty)
(test (simple-merge (list) (list 1)) (list 1))
(test (simple-merge (list 1 2 6 100) (list 2 2 5) ) (list 1 2 2 2 5 6 100))
(test (simple-merge (list 1 4 6) (list 2 5 5 7 8)) (list 1 2 4 5 5 6 7 8))

; Ex. (2)
; baseado no map2.rkt
; http://www.ime.usp.br/~reverbel/CLP-11/exemplos/map2.rkt
(define  (merge l1 l2)
  (define (merge-aux l1 l2 backward-result)
    (cond
      [(and (null? l1) (null? l2)) (reverse backward-result)]
      [(null? l1) (merge-aux l1 (cdr l2) (cons (car l2) backward-result))]
      [(null? l2) (merge-aux (cdr l1) l2 (cons (car l1) backward-result))]
      [(< (car l1) (car l2)) (merge-aux (cdr l1) l2 (cons (car l1) backward-result))]
      [else (merge-aux l1 (cdr l2) (cons (car l2) backward-result))]))
  (cond
    [(null? l1) l2]
    [(null? l2) l1]
    [else (merge-aux l1 l2 empty)]))

;testes
(test (merge (list) (list)) empty)
(test (merge (list) (list 1)) (list 1))
(test (merge (list 1 2 6 100) (list 2 2 5) ) (list 1 2 2 2 5 6 100))
(test (merge (list 1 4 6) (list 2 5 5 7 8)) (list 1 2 4 5 5 6 7 8))
  
  

