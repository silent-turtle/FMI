#lang racket

; some functions i use for the tasks

(define (foldr* f nv l)
  (if (null? l)
      nv
      (f (car l) (foldr f nv (cdr l)))))


(define (foldl* f acc l)
  (if (null? l)
      acc
      (foldl* f (f (car l) acc) (cdr l))))


(define (zip-with f xs ys)
  (if (or (null? xs) (null? ys))
      '()
      (cons (f (car xs) (car ys)) (zip-with f (cdr xs) (cdr ys)))))


(define (member? elem l)
  (cond ((null? l) #f)
        ((= elem (car l)) #t)
        (else (member? elem (cdr l)))))
                         
; Task 1: Define dimensions(m) which returns a pair of the numbers of rows cols of matrix m.

(define (dimensions m)
  (cons (length m) (length (car m))))


; Task 2: Define reverse-columns(m) which reverses the order of the columns in the matrix m.
; example: (reverse-columns '((1 2 3) (4 5 6) (7 8 9)) returns '((3 2 1) (6 5 4) (9 8 7))

(define (reverse l)
  (define (helper l res)
    (if (null? l)
        res
        (helper (cdr l) (cons (car l) res))))

  (helper l '()))

(define (reverse-columns l)
  (if (null? (cdr l))
      (reverse (car l))
      (list (reverse (car l)) (reverse-columns (cdr l)))))


; Task 3: Define nth-column(m, n) which returns a list of the elements in the nth column
; of the matrix m.

(define (find-nth-elem l n)
  (define (helper l cnt)
    (cond ((null? l) #f)
          ((= cnt n) (car l))
          (else (helper (cdr l) (+ cnt 1)))))
  (helper l 1))

(define (nth-column m n)
  (if (null? m)
      m
      (cons (find-nth-elem (car m) n) (nth-column (cdr m) n))))


; Task 4: Define main-diagonal(m) which returns a list of the elements in the main diagonal of
; the matrix m.

(define (main-diagonal m)
  (define (helper m cur)
    (if (null? m)
        m
        (cons (find-nth-elem (car m) cur) (helper (cdr m) (+ cur 1)))))
  (helper m 1))


; Task 5: Define transpose(m) which returns the transposed matrix of m.

(define (transpose m)
  (define len (length (car m)))
  (define (helper res cur)
    (if (> cur len)
        (reverse res)
        (helper (cons (nth-column m cur) res) (+ cur 1))))

  (helper '() 1))


; Task 6: Define for-all-columns?(m, p) which checks if p is true for every column of m.

(define (for-all? l p)
  (equal? l (filter p l)))

(define (for-all-columns? m p)
  (define len (if (null? m) 0 (length m)))
  (define (helper res cur)
    (if (> cur len)
        res
        (helper (and (for-all? (nth-column m cur) p) res) (+ cur 1))))

  (helper (and) 1))


; Task 7: Define prime-in-each-column?(m) which checks if each column of m has a prime number.

(define (count-divisors-iter n)
  (define (helper i n)
    (if (= i 0)
        0
        (if (= (remainder n i) 0)
            (+ 1 (helper (- i 1) n))
            (helper (- i 1) n))))
  
  (helper n n))

(define (prime? n)
  (= (count-divisors-iter n) 2))

(define (prime-in-list? l)
  (foldr* (lambda (x y) (or (if (prime? x) #t #f) y)) (or) l))

(define (prime-in-each-column? m)
  (define len (if (null? m) 0 (length (car m))))
  (define (helper res cur)
    (if (> cur len)
        res
        (helper (and (prime-in-list? (nth-column m cur)) res) (+ cur 1))))

  (helper (and) 1))



; Task 8: Define multiply(a, b) which returns the product of the two matrices a and b.

(define (calculate-matrix-multiplication-element xs ys)
  (foldl* + 0 (zip-with * xs ys)))

(define cmme calculate-matrix-multiplication-element)

(define (multiply a b)
  (define transposed-b (transpose b))
  (define len-a (if (null? a) 0 (length a)))
  (define len-b (if (null? transposed-b) 0 (length transposed-b)))
  (define (helper result-matrix current-row i j xss yss)
    (cond ((> i len-a) (reverse result-matrix))
          ((> j len-b) (helper (cons (reverse current-row) result-matrix) '() (+ i 1) 1 (cdr xss) transposed-b))
          (else (helper result-matrix (cons (cmme (car xss) (car yss)) current-row) i (+ j 1) xss (cdr yss)))))

  (helper '() '() 1 1 a transposed-b))
  
  
; Task 9: Define find-columns(m) which finds the number of columns such that each element
; could be found in another row of the matrix.
; example: (find-columns '((1 4 3) (4 5 6) (7 4 9)) returns 1 as 4, 5 and 4 can be found in the
; second row.

(define (sublist? xs ys)
  (cond ((null? xs) #t)
        ((and (null? ys) (not (null? xs))) #f)
        (else (and (member? (car xs) ys) (sublist? (cdr xs) ys)))))

(define (find-columns m)
  (define len (if (null? m) 0 (length (car m))))
  (define (helper cnt current-col matrix)
    (cond ((> current-col len) cnt)
          ((null? matrix) (helper cnt (+ current-col 1) m))
          ((sublist? (nth-column m current-col) (car matrix)) (helper (+ cnt 1) current-col (cdr matrix)))
          (else (helper cnt current-col (cdr matrix)))))

  (helper 0 1 m))
        
        
    

