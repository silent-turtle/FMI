#lang racket

(define (pred n)
  (- n 1))

(define (succ n)
  (+ n 1))

; Task 1: Define fact(n) (iterative factorial)

(define (fact-iter n)
  (define (helper production current-count max-count)
    (if (> current-count max-count)
        production
        (helper (* production current-count) (succ current-count) max-count)))
  
  (if (= n 0)
      1
      (helper 1 1 n)))


; Task 2: Define sum(start, end) which sums the numbers from start to end iteratively

(define (sum-iter start end)
  (define (helper sum current-num end)
    (if (> current-num end)
        sum
        (helper (+ sum current-num) (succ current-num) end)))
  
  (helper 0 start end))


; Task 3: Define expt(x, n) which calculates x^n iteratively

(define (expt-iter x n)
  (define (helper product current-count max-count)
    (if (> current-count max-count)
        product
        (helper (* product x) (succ current-count) max-count)))
  
  (if (= n 0)
      1
      (helper 1 1 n)))


; Task 4: Define count-digits(n) which counts the number of digits in n

(define (count-digits n)
  (if (= (quotient n 10) 0)
      1
      (+ 1 (count-digits (quotient n 10)))))


(define (count-digits-iter n)
  (define (helper count n)
    (if (= n 0)
        count
        (helper (succ count) (quotient n 10))))
  
  (helper 0 n))


; Task 5: Define sum-digits(n) which sums the digits of n

(define (sum-digits n)
  (if (= (quotient n 10) 0)
      n
      (+ (remainder n 10)
         (sum-digits (quotient n 10)))))


(define (sum-digits-iter n)
  (define (helper sum n)
    (if (= n 0)
        sum
        (helper (+ sum (remainder n 10)) (quotient n 10))))
  
  (helper 0 n))


; Task 6: Define reverse-digits(n) which reverses the digits in n

(define (reverse-digits n)
  (if (= (quotient n 10) 0)
      n
      (+ (* (remainder n 10)
            (expt-iter 10 (pred (count-digits n))))
         (reverse-digits (quotient n 10)))))

(define (reverse-digits-iter n)
  (define (helper res n)
    (if (= n 0)
        res
        (helper (+ (* res 10) (remainder n 10)) (quotient n 10))))

  (helper 0 number))


; Task 7: Define count-divisors(n) which counts the number of divisors of n

(define (count-divisors-iter n)
  (define (helper i n)
    (if (= i 0)
        0
        (if (= (remainder n i) 0)
            (+ 1 (helper (pred i) n))
            (helper (pred i) n))))
  
  (helper n n))


; Task 8: Define sum-divisors(n) which sums the divisors of n

(define (sum-divisors-iter n) 
  (define (helper sum i)
    (cond ((= i n)               (+ sum n))
          ((= (remainder n i) 0) (helper (+ sum i) (succ i)))
           (else                 (helper sum (succ i)))))
  
  (helper 0 1))


; Task 9: Define prime?(n) which checks if n is prime or not

(define (prime? n)
  (= (count-divisors-iter n) 2))

; Task 10: Define fast-expt-iter(x, n)

(define (fast-expt-iter x n)
  (define (helper res mult current-cnt max-cnt)
    (if (> current-cnt max-cnt)
        res
        (helper (* mult res) mult (succ current-cnt) max-cnt)))

  (if (= (remainder n 2) 0)
      (helper 1 (* x x) 1 (quotient n 2))
      (helper x (* x x) 1 (quotient n 2))))
