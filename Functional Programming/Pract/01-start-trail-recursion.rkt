#lang racket

; EXERCISE: implement a iterative factorial
(define (fact-iter n)
  (define (helper res current-num)
    (if (> current-num n)
        res
        (helper (* res current-num) (+ current-num 1))))
  (helper 1 1))

; fibonacci - classic example of hugely ineffective recursive function
; EXERCISE:
(define (fib n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib (- n 1)) (fib (- n 2))))))

; but do it iterative, by using an inner helper to hold and pass previous values
; EXERCISE:
(define (fib-iter n)
  (define (helper current-num fib1 fib2)
    (if (> current-num n)
        fib1
        (helper (+ current-num 1) fib2 (+ fib1 fib2))))
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (helper 1 0 1))))

; EXERCISE: count the digits of a number
; (digits-num 5) -- 1
; (digits-num 123) -- 3
(define (digits-num number)
  (if (= (quotient number 10) 0)
      1
      (+ 1 (digits-num (quotient number 10)))))

(define (digits-num-iter number)
  (define (helper count n)
    (if (= n 0)
        count
        (helper (+ count 1) (quotient n 10))))
  (helper 0 number))

; implement this however you like
; Exercise: reversing a number
; (reverse-num 0) -- 0
; (reverse-num 123) -- 321
(define (reverse-num number)
  (if (= (quotient number 10) 0)
      number
      (+ (* (remainder number 10)
            (expt 10 (- (digits-num-iter number) 1)))
         (reverse-num (quotient number 10)))))

(define (reverse-num-iter number)
  (define (helper res n)
    (if (= n 0)
        res
        (helper (+ (* res 10) (remainder n 10)) (quotient n 10))))
  (helper 0 number))

; EXERCISE: recursive ackermann
; ack(m, n) = n + 1                     if m == 0
; ack(m, n) = ack(m - 1, 1)             if m > 0 and n = 0
; ack(m, n) = ack(m - 1, ack(m, n - 1)) if m > 0 and n > 0
(define (ack m n)
  (cond ((= m 0) (+ n 1))
        ((and (> m 0) (= n 0)) (ack (- m 1) 1))
        ((and (> m 0) (> n 0)) (ack (- m 1) (ack m (- n 1))))))

; EXERCISE: ackermann but iteratively
(define (ack-iter m n) void)
