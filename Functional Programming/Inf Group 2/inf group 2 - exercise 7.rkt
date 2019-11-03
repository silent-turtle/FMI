#lang racket

(define (key-member? x l)
  (cond ((null? l) #f)
        ((= x (car (car l))) #t)
        (else (key-member? x (cdr l)))))

(define (foldl* f acc l)
  (if (null? l)
      acc
      (foldl* f (f (car l) acc) (cdr l))))

 -
; Task 1: Define run-length-encode(l) which encodes the list l in an association list - a list of
; pairs (<key>, <value>) where <key> is an element of l and <value> is how many times the <key>
; consists sequentially in the list l.
; example: (run-length-encode '(8 7 7 2 2 2 2 3 3 2)) returns '((8 . 1) (7 . 2) (2 . 4) (3 . 2) (2 . 1))

(define (run-length-encode l)
  (define (cnt-helper x l res)
    (if (or (null? l) (not (= x (car l))))
        res
        (cnt-helper x (cdr l) (+ res 1))))
  (define (helper res l)
    (cond ((null? l) (reverse res))
          ((and (not (null? res)) (= (car l) (caar res))) (helper res (cdr l)))
          (else (helper (cons (cons (car l) (cnt-helper (car l) l 0)) res) (cdr l)))))

  (helper '() l))


; Task 2: Define run-length-decode(code) which restores the list that's encoded by run-length-
; encode from the previous task in an association list code.
; example: (run-length-decode '((1 . 2) (3 . 4) (5 . 2))) returns '(1 1 3 3 3 3 5 5).

(define (run-length-decode code)
  (define (unzip l)
    (define (helper res cnt)
      (if (>= cnt (cadr l))
          res
          (helper (cons (car l) res) (+ cnt 1))))
    (helper '() 0))
  (define (helper res l)
    (if (null? l)
        res
        (helper (append res (unzip (car l))) (cdr l))))
  (if (null? code)
      code
      (helper (unzip (car code)) (cdr code))))



; Task 3: Define histogram(l) which returns a histogram of the appearances of each element in
; l in the form of an association list.
; example: (histogram '(8 7 1 7 8 2 2 8 2 7 8 1)) returns '((8 . 4) (7 . 3) (1 . 2) (2 . 3)).

(define (count-elem el l)
  (foldl* (lambda (x y) (if (= x el) (+ y 1) y)) 0 l))

(define (histogram l)
  (define (helper res l)
    (cond ((null? l) (reverse res))
          ((key-member? (car l) res) (helper res (cdr l)))
          (else (helper (cons (cons (car l) (count-elem (car l) l)) res) (cdr l)))))

  (helper '() l))


; Task 4: Define group-by(f, l) which returns an association list such that the keys are
; the values of f after being applied to the elements of l and the value is a list of each
; element el such that f(el) equals the respective key.
; example: (group-by (lambda (x) (remainder x 3)) '(0 1 2 3 4 5 6 7 8)) returns '((0 0 3 6)
; (1 1 4 7) (2 2 5 8)).


(define (group-by f l)
  (define (create-list-with-values res f key l)
    (cond ((null? l) (reverse res))
          ((= (f (car l)) key) (create-list-with-values (cons (car l) res) f key (cdr l)))
          (else (create-list-with-values res f key (cdr l)))))
  
  (define (helper res l)
    (cond ((null? l) (reverse res))
          ((key-member? (f (car l)) res) (helper res (cdr l)))
          (else (helper (cons (cons (f (car l)) (create-list-with-values '() f (f (car l)) l)) res) (cdr l)))))
  
  (helper '() l))