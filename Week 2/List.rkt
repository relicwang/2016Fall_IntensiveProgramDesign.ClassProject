;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname list) (read-case-sensitive #t) (teachpacks ((lib "universe.rkt" "teachpack" "2htdp") (lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "universe.rkt" "teachpack" "2htdp") (lib "image.rkt" "teachpack" "2htdp")) #f)))
(require 2htdp/universe)


#|

Design the following functions:


;; squares : list-of-number -> list-of-number
;; compute the perfect squares of numbers in `l`
(define (squares l) ...)

;; contains-telephone : list-of-string -> boolean
;; returns #true if 'l' contains the symbol 'telephone, #false otherwise
(define (contains-telephone l) ...)


;; shortest : NE-list-of-string -> string
;; returns the shortest string in 'l' -- read this for help:
;; http://www.ccs.neu.edu/home/matthias/HtDP2e/part_two.html#%28part._sec~3alists~3ane%29
;; also look up the 'string-length' function in the documentation (type f1 to open the docs)
(define (shortest l) ...)

;; mean : list-of-number -> list-of-number
;; computes the average of the elements of 'l'
;; return 0 if 'l' list is empty
(define (mean l) ...)

|#






;;A list-of-number is either:
;;-'()
;;-(cons number list-of-number)


;; squares : list-of-number -> list-of-number
;; compute the perfect squares of numbers in `l`

;;Example:
;;- (squares '() -> '()
;;- (squares (list 15)) ->  (list 225)
;;- (squares (list 1 2 3 4)) -> list 1 4 9 16)

(check-expect (squares '()) '())
(check-expect (squares (list 15)) (list 225))
(check-expect (squares (list 1 2 3 4)) (list 1 4 9 16))


#;
(define (template-for-list-of-any-variable l)
  (cond
    [(empty? l) ...]
    [else ... (first l) ...
          ... (shortest (rest l)) ...]))



(define (squares l)
  (cond
    [(empty? l) '()]
    [else
     (cons (* (first l) (first l))
            (squares(rest l)))]       
    )
  )


;;Return the elements in l that is perfect squars
(define (squares l)
  (cond
    [(empty? l) '()]
    [else
     (cond
      [(integer? (sqrt (first l))) (cons (first l)  (squares (rest l)))]
      [else (squares (rest l))])])
     
    )
  





;;A list-of-string is either:
;;-'()
;;-(cons string list-of-string)


;;Contains-telephone : list-of-string -> boolean
;;Returns #true if 'l' contains the symbol 'telephone, #false otherwise



;; Example:
;; If you input empty list, it should return an empty list
;; If you input a list containing "telephone",'(), it should return true
;; If you input a list containing "mobilephone",'(), it should return false
;; If you input a list containing "telephone", "mobilephone",'(), it should return true
;; If you input a list containing "mobilephone", "telephone",'(), it should return true
;; If you input a list containing "mobilephone", "radio",'(), it should return false



(check-expect (contains-telephone (list "telephone")) #true)
(check-expect (contains-telephone (list "mobilephone")) #false)
(check-expect (contains-telephone (list "telephone"   "mobilephone")) #true)
(check-expect (contains-telephone (list "mobilephone"  "telephone" )) #true)
(check-expect (contains-telephone (list "mobilephone"  "telephone" "mobilephone")) #true)
(check-expect (contains-telephone (list "mobilephone"  "radio")) #false)
(check-expect (contains-telephone (list "mobilephone"  "mobilephone" "mobilephone" "telephone")) #true)

#;
(define (template-for-list-of-any-variable l)
  (cond
    [(empty? l) ...]
    [else ... (first l) ...
          ... (shortest (rest l)) ...]))


;A KEYWORD is seach symbol that is expected
(define KEYWORD "telephone")

(define (contains-telephone l)
  (cond
    [(string=? (first l) KEYWORD) #true]   
    [(not (empty? (rest l))) (contains-telephone (rest l))]
    [(empty? (rest l)) #false])  
  )



(define (is-tlp fallers-pos )
       (cond
         [(empty? fallers-pos) empty]
         [else
          (cond
            [(string=? (first fallers-pos) "tlp") (cons (first fallers-pos) (is-tlp (rest fallers-pos) ))]
            [else (is-tlp (rest fallers-pos) )])]))

;;A list-of-string is either:
;;-'()
;;-(cons string list-of-string)


;; shortest : NE-list-of-string -> string
;; returns the shortest string in 'l' (the list is not empty,
;; if the list contains two string has the same length, it will return the string with smaller index)



;;Example:
;;- (shortest(list "abc" "iccd" "a")-> "a"
;;- (shortest(list "abc" "iccd" "a")-> "a"
;;- (shortest(list "a" "iccd" "ab")-> "a"
;;- (shortest(list "a" "cd" "aaab"))-> "a"
;;- (shortest(list "a" "b" "aaab"))-> "a"

(check-expect  (shortest(list  "a")) "a")
(check-expect  (shortest(list "abc" "iccd" "a")) "a")
(check-expect  (shortest(list "a" "iccd" "ab")) "a")
(check-expect  (shortest(list "a" "cd" "aaab")) "a")
(check-expect  (shortest(list "a" "b" "aaab")) "a")


#;
(define (template-for-list-of-any-variable l)
  (cond
    [(empty? l) ...]
    [else ... (first l) ...
          ... (shortest (rest l)) ...]))



(define (shortest l)
  (cond
    [(empty? (rest l)) (first l)]
    [else
     (local [(define rb (shortest (rest l)))]
       (cond
         [(> (string-length (first l)) (string-length rb))
          rb]
         [else (first l)]))]))





#|Approach 2:
(define (shortest l)
  (first (sort-new l)))


 (define (sort-new l)
    (cond
      [(empty? l) l]
      [else (insert  (first l) (sort-new (rest l)))]))

  (define (insert x l)
    (cond
      [(empty? l) (list x)]
      [else (cond
              [(< (string-length x) (string-length (first l))) (cons x l)]
              [else (cons (first l) (insert x (rest l)))])]))
|#



  
;;A list-of-number is either:
;;-'()
;;-(cons number list-of-number)

  
;; mean : list-of-number -> list-of-number
;; computes the average of the elements of 'l'
;; return 0 if 'l' list is empty



;;Example:
;;-(mean '()) ->0
;;-(mean (list 1 2 3 4)) -> 2.5
;;-(mean (list 4 3 3 4)) -> 3.5
;;-(mean (list 1 2 3)) -> 2
;;-(mean (list 0)) -> 0
  
(check-expect (mean '()) 0)
(check-expect (mean (list 1 2 3 4)) 2.5)
(check-expect (mean (list 4 3 3 4)) 3.5)
(check-expect (mean (list 1 2 3)) 2)
(check-expect (mean (list 0)) 0)

#;
(define (template-for-list-of-any-variable l)
  (cond
    [(empty? l) ...]
    [else ... (first l) ...
          ... (shortest (rest l)) ...]))


(define (mean l)
  (local [(define lst-sz (length l))]
  (cond
    [(= lst-sz 0) 0]
    [else (/ (sum l) (length l))]))    
 )


;; sum : list-of-number -> number
;; computes the sum of the elements of 'l'
;; return 0 if 'l' list is empty



;;Example:
;;-(sum '()) ->0
;;-(sum (list 1 2 3 4)) -> 10
;;-(sum (list 4 3 3 4)) -> 14
;;-(sum (list 1 2 3)) -> 6
;;-(sum (list 0)) -> 0
  
(check-expect (sum '()) 0)
(check-expect (sum (list 1 2 3 4)) 10)
(check-expect (sum (list 4 3 3 4)) 14)
(check-expect (sum (list 1 2 3)) 6)
(check-expect (sum (list 0)) 0)


#;
(define (template-for-list-of-any-variable l)
  (cond
    [(empty? l) ...]
    [else ... (first l) ...
          ... (shortest (rest l)) ...]))

(define (sum l)
  (cond
    [(empty? l) 0]
    [else
     (+(first l)
          (sum (rest l)))]
  ))




