;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname sorting) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
#|

Here is an algorithm for sorting lists of numbers

  - if the list has 0 elements or 1 element, it is sorted; return it.

  - if the list has 2 or more elements, divide the list into two
    halves and recursively sort them. Note that you can divide the
    elements in half multiple ways; it does not need to be the first
    half and second half; it may even be easier to take the odd numbered
    and even-numbered elements.

  - combine the two sorted sublists into a single one by merging them

Here is an algorithm for merging the two lists:

  - if either list is empty, return the other one
  
  - if both are not empty, pick the list with the
    smaller first element and break it up into
    it's first element and the rest of the list.
    Recur with the entire list whose first element is
    larger and the rest of the list whose first element
    is smaller. Then cons the first element onto the
    result of the recursive call.

Design functions that implement this sorting algorithm.
For each function, write down if it is generative recursion
or structural recursion. Also write down the running
time of each function using Big Oh notation.

|#

;; a list of number is either
;; -- empty
;; -- (cons number list)

;;Template:
;;(define (template-function l)
;;         (cond
;;           [(empty? l) ...]
;;           [else
;;            ...(first l)...
;;            ...(rest l) ...

;;merge-sort: [list-of-number] -> [list-of-number]
;;Sort a list of number
;;Recursion: Generative recursion
;;Big-O: O(N*log(N))
(check-expect (merge-sort (list 5 6 1)) (list 1 5 6))
(check-expect (merge-sort (list 45 72 12 32 44 89 12 54 78
                               6 1 7 456 89 5)) (list 1 5 6 7 12 12 32 44 45 54 72 78 89 89 456))
(check-expect (merge-sort (list 44 8 5 10)) (list  5 8 10 44));
(check-expect (merge-sort (list)) (list));
(check-expect (merge-sort (list 44)) (list 44));

(check-expect (merge-sort (list 33 1 44)) (list 1 33 44));
(check-expect (merge-sort (list 17 2)) (list 2 17))

(define (merge-sort l)
  (cond
    [(or (equal? (length l) 0)
         (equal? (length l) 1)) l]
    [else
     (local [(define left-hlf-to (+ 1 (round (/ (length l) 2))))
             (define right-hlf-from  left-hlf-to)
             (define right-hlf-to    (+ 1 (length l)))
             (define left-l  (merge-sort (get-lft-hlf  l (range 1 left-hlf-to 1))))
             (define right-l (merge-sort (get-rht-hlf  l (range right-hlf-from right-hlf-to 1))))]
       (merge left-l right-l))
     ]))


;;get-lft-hlf : [list-of-number] [list-of-number] -> [list-of-number]
;;Retrieve the first N (the length of second list) of first list
;;Recursion: Structural Recursion
;;Big-O: O(N)


(check-expect (get-lft-hlf (list 2 3 1 5 6) (list 1 2 3)) (list 2 3 1))
(check-expect (get-lft-hlf (list 2 3 1 5)   (list )) (list))
(define (get-lft-hlf l count-lst)
  (cond
    [(empty? count-lst) '()]
    [else
     (cons (first l)
           (get-lft-hlf (rest l) (rest count-lst)))]))

;;get-lft-hlf : [list-of-number] [list-of-number] -> [list-of-number]
;;Retrieve the last N (the length of second list) of first list
;;Recursion: Structural Recursion
;;Big-O: O(N)

(check-expect (get-rht-hlf (list 2 3 1 5 6) (list 4 5)) (list 5 6))
(check-expect (get-rht-hlf (list 2 3 1 5) (list )) (list))

(define (get-rht-hlf l count-lst)
  (cond
    [(empty? count-lst) '()]
    [else    
     (cons (list-ref l (- (first count-lst) 1) )
           (get-rht-hlf l (rest count-lst)))]))


;;merge : [list of x] [list of x] -> [list of x]
;;Merge two list by accending order
;;Recursion: Structural Recursion
;;Big-O: O(N), each element only compare once
(check-expect (merge '() (list 2)) (list 2))
(check-expect (merge (list 1) '() ) (list 1))
(check-expect (merge '() '() ) '()) 
(check-expect (merge (list 1) (list 2)) (list 1 2)) 
(check-expect (merge (list 1 3 5) (list 2 4))
              (list 1 2 3 4 5))
(check-expect (merge (list 2 15) (list 1 4 17))
              (list 1 2 4 15 17))


(check-expect (merge (list 2 8 20 35) (list 1 4 7 26 42)) (list 1 2 4 7 8 20 26 35 42))
(check-expect (merge (list 2 8 20 35 77 100) (list 5 7 65 84)) (list 2 5 7 8 20 35 65 77 84 100))
(check-expect (merge (list 2 8 20 35 77 100) (list)) (list 2 8 20 35 77 100))
(check-expect (merge (list) (list 5 7 65 84)) (list 5 7 65 84))
(check-expect (merge (list 35 84) (list 5 7 12)) (list 5 7 12 35 84))


(define (merge lft-l rght-l)
  (cond
    [(empty? lft-l) rght-l]
    [(empty? rght-l) lft-l]
    [else
     (cond
       [(<= (first lft-l)(first rght-l))
        (cons (first lft-l)
              (merge (rest lft-l) rght-l))]
       [(> (first lft-l)(first rght-l))
        (cons (first rght-l)
              (merge (rest rght-l) lft-l))]
        [else (error "can't merge")])]))
            
       
  