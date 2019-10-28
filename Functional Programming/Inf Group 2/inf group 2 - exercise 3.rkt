#lang racket

; Task 1: Define fibonacci(n) recursively and iteratively

(define (fib-rec n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib-rec (- n 1)) (fib-rec (- n 2))))))


(define (fib-iter n)
  (define (helper fib1 fib2 cur)
    (if (> cur n)
        fib2
        (helper fib2 (+ fib1 fib2) (+ cur 1))))

  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (helper 0 1 2))))


; Task 2: Define the following function
; f(n) = n if n < 3
; f(n) = f(n - 1) + 2f(n - 2) + 3f(n - 3), if n >= 3

(define (f n)
  (if (< n 3)
      n
      (+ (f (- n 1)) (* 2 (f (- n 2))) (* 3 (f (- n 3))))))

(define (f-iter n)
  (define (helper f1 f2 f3 curr-n)
    (if (> curr-n n)
        f3
        (helper f2 f3 (+ (* 3 f1) (* 2 f2) f3) (+ curr-n 1))))

  (if (< n 3)
      n
      (helper 0 1 2 3)))


; Task 3: Pascal's triangle

(define (binomial-coefficient row index)
  (if (= row 0)
      (if (= index 0)
          1
          0)
      (+ (binomial-coefficient (- row 1) index)
         (binomial-coefficient (- row 1) (- index 1)))))

; (define (binomial-coefficient-iter row index)
  ; use fact-iter to calculate binomial coefficient



      
