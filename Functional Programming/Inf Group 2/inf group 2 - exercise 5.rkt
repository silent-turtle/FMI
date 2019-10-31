#lang racket

(define (accumulate op nv a b term next)
  (if (> a b)
      nv
      (op (term a) (accumulate op nv (next a) b term next))))

; Task 1: Define length(l) which counts the elements in the list l.

(define l (list 1 2 3 4 5 6))

(define (length l)
  (if (null? l)
      0
      (+ 1 (length (cdr l)))))

; Task 2: Define sum(l) which sums the elements in l.

(define (sum l)
  (if (null? l)
      0
      (+ (car l) (sum (cdr l)))))

; Task 3: Define member?(l, x) which checks if x is an element in l.

(define (member? l x)
  (cond ((null? l) #f)
        ((= (car l) x) #t)
        (else (member? (cdr l) x))))


; Task 4: Define last(l) which returns the last element in l.

(define (last l)
  (if (null? (cdr l))
      (car l)
      (last (cdr l))))


; Task 5: Define nth(l, n) which returns the element in the nth position in l, starting from 0.

(define (nth l n)
  (define (helper res curr)
    (cond ((null? res) #f)
          ((= curr n) (car res))
          (else (helper (cdr res) (+ curr 1)))))

  (helper l 1))


; Task 6: Define scale(l, x) which returns the elements of l multiplied by x.

(define (scale l x)
  (if (null? l)
      l
      (cons (* (car l) x) (scale (cdr l) x))))


; Task 7: Define reverse(l) which returns a list the element of which are the elements of l
; in reverse order.

(define (reverse l)
  (define (helper l res)
    (if (null? l)
        res
        (helper (cdr l) (cons (car l) res))))

  (helper l '()))



; Task 8: Define add-last(l, x) which adds the element x to the end of l.

(define (add-last l x)
  (if (null? l)
      (cons x l)
      (cons (car l) (add-last (cdr l) x))))



; Task 9: Define append(l1, l2) which concatenates lists l1 and l2.

(define (append l1 l2)
  (if (null? l1)
      l2
      (cons (car l1) (append (cdr l1) l2))))



; Task 10: Define map(l, f) which applies f on all elements of l.

(define (map l f)
  (if (null? l)
      l
      (cons (f (car l)) (map (cdr l) f))))



; Task 11: Define filter(l, p) which returns a list of elements from l such that p is true for them.

(define (filter l p)
  (cond ((null? l) l)
        ((p (car l)) (cons (car l) (filter (cdr l) p)))
        (else (filter (cdr l) p))))



; Task 12: Define the acculumate procedure for lists

(define (accumulate-l op nv l)
  (if (null? l)
      nv
      (op (car l) (accumulate-l op nv (cdr l)))))


; ------------------
; Part 2


; Task 1: Define maximum(l) which finds the biggest number in l.

(define (maximum l)
  (define (helper max l)
    (cond ((null? l) max)
          ((> (car l) max) (helper (car l) (cdr l)))
          (else (helper max (cdr l)))))

  (if (null? l)
      'error
      (helper (car l) (cdr l))))



; Task 2: Define remove(l, x) which returns a new list such that the first x in l is removed.

(define (remove l x)
  (cond ((null? l) l)
        ((= (car l) x) (cdr l))
        (else (cons (car l) (remove (cdr l) x)))))



; Task 3: Define selection-sort(l)

(define (selection-sort l)
  (define (helper res l)
    (define max (maximum l))
    (if (null? l)
        res
        (helper (cons max res) (remove l max))))

  (helper '() l))



; Task 4: Define partition(p, l) which returns a list of 2 sublists such that:
; - the first one has the elements of l that the predicate p is true for
; - the second one contains the rest of the elements.

(define (partition p l)
  (define (helper res1 res2 l)
    (cond ((null? l) (list res1 res2))
          ((p (car l)) (helper (cons (car l) res1) res2 (cdr l)))
          (else (helper res1 (cons (car l) res2) (cdr l)))))

  (helper '() '() l))



; Task 5: Define flatten(l) which takes a list of numbers and lists of numbers
; and return a list of all numbers.
; example (flatten '((1 2) 3 (4 5) (6 7))) returns '(1 2 3 4 5 6 7)

(define (flatten l)
  (cond ((null? l) l)
        ((list? (car l)) (append (car l) (flatten (cdr l))))
        (else (cons (car l) (flatten (cdr l))))))


; Task 6: Define map-deep(f, l) which applies f on numbers and lists of numbers

(define (map-deep f l)
  (cond ((null? l) l)
        ((list? (car l)) (cons (map-deep f (car l)) (map-deep f (cdr l))))
        (else (cons (f (car l)) (map-deep f (cdr l))))))


; Task 7: Define zip(a, b) which compacts an element of a with an element of b. The new list
; is as long as the shorter of a and b

(define (zip a b)
  (cond ((null? a) a)
        ((null? b) b)
        (else (cons (cons (car a) (cons (car b) '())) (zip (cdr a) (cdr b))))))



; Task 8: Define remove-duplicates(l) which removes diplicates from l.

(define (remove-duplicates l)
  (cond ((null? l) l)
        ((member? (cdr l) (car l)) (remove-duplicates (cdr l)))
        (else (cons (car l) (remove-duplicates (cdr l))))))


; Task 9:

(define (chunk l n)
  (define (helper l res cnt)
    (cond ((null? l) (reverse res))
          ((= (modulo cnt n) 0) (list (reverse (cons (car l) res)) (helper (cdr l) '() (+ cnt 1))))
          (else (helper (cdr l) (cons (car l) res) (+ cnt 1)))))

  (helper l '() 1))
   