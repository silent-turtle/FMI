#lang racket

; Task 1: Define the function add(x, y) that sums x and y.

(define (add x y)
  (+ x y))

; Task 1b: using pred and succ

(define (pred n)
  (- n 1))

(define (succ n)
  (+ n 1))

(define (add2 x y)
  (if (= x 0)
      y
      (+ 1 (add2 (pred x) y))))


; Task 2: Define the predicate even?(n) and the predicate odd?(n)

(define (even? n)
  (= (remainder n 2) 0))

(define (odd? n)
  (not (even? n)))

; Task 3: Define the function signum(x) that returns -1, 0, 1 depending on whether x is a negative number, 0 or a positive number.

(define (signum x)
  (cond ((< x 0) -1)
        ((> x 0) 1)
        (else 0)))

; Task 4: Define the function factorial(n)

(define (factorial n)
  (if (= n 0)
      1
      (* n (factorial (- n 1)))))


; Task 5: Define the function sum(start, end)

(define (sum start end)
  (if (= start end)
      start
      (+ start (sum (succ start) end))))

; Task 6: Define expt(x, n) x^n

(define (expt x n)
  (if (= n 1)
      x
      (* x (expt x (pred n)))))


; Task 7: Define fast-expt(x, n) [if n is even, then x^n = (x^(n/2))^2]

(define (fast-expt x n)
  (if (= n 0)
      1
      (if (= n 1)
          x
          (if (= (remainder n 2) 0)
              (* x (fast-expt x (quotient n 2)))
              (* x (fast-expt x (quotient (pred n) 2)))))))
