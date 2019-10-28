#lang racket

; Task 1: Define a more general accumulator accepting
; a function that calculates the next value of the num a

(define (accumulate op nv a b term next)
  (if (> a b)
      nv
      (op (term a) (accumulate op nv (next a) b term next))))

(define (sum a b term next)
  (accumulate + 0 a b term next))

(define (product a b term next)
  (accumulate * 1 a b term next))

; iterative version

(define (acc-iter op nv a b term next)
  (define (helper res current-n)
    (if (> current-n b)
        res
        (helper (op res (term current-n)) (next current-n))))
  (helper nv a))

(define (sum-iter a b term next)
  (acc-iter + 0 a b term next))

(define (prod-iter a b term next)
  (acc-iter * 1 a b term next))


; Task 2: Define count(predicate, a, b) which counts the number of elements in the
; range [a,b] such that predicate is true for them.

(define (count predicate a b)
  (acc-iter + 0 a b predicate (lambda (x) (+ x 1))))


; Task 3: Define count-palindromes(a, b) which counts the number of palindromes in the range [a,b]

(define (reverse-num number)
  (define (helper res n)
    (if (= n 0)
        res
        (helper (+ (* res 10) (remainder n 10)) (quotient n 10))))
  (helper 0 number))

(define (palindrome? n)
  (= n (reverse-num n)))

(define (count-palindromes a b)
  (accumulate + 0 a b (lambda (x) (if (palindrome? x) 1 0)) (lambda (x) (+ x 1))))


; Task 4: Define exists?(predicate, a, b) which checks if an integer exists in the range
; [a,b] such that predicate is true for it.

(define (exist? p? a b)
  (accumulate (lambda (x y) (or x y)) (or) a b (lambda (x) (if (p? x) #t #f)) (lambda (x) (+ x 1)))) 


; Task 5: Define for-all?(predicate, a, b) which checks if predicate is true for all integers
; in the range [a,b]

(define (for-all? p? a b)
  (accumulate (lambda (x y) (and x y)) (and) a b (lambda (x) (if (p? x) #t #f)) (lambda (x) (+ x 1))))


; Task 6: Define double which takes a function as an argument and returns a function which applies
; the taken function twice.

(define (double f)
  (lambda (x) (f(f x))))


; Task 7: Let f and g be function with one argument. Composition f ∘ g is the function
; x -> f(g(x)). Define compose(f, g) which returns the composition f ∘ g.

(define (compose f g)
  (lambda (x) (f (g x))))


; Task 8: Let f be a function with one argument and n be a non-negative integer. Define
; repeated which applies the function f n times.

(define (repeated n f)
  (define (helper res-func curr)
    (if (= curr n)
        res-func
        (helper (lambda (x) (f (res-func x))) (+ 1 curr))))

  (if (= n 0)
      (lambda (x) x)
      (helper f 1)))
