; HW05 : Stream
; By : Yibing & Relic

#lang dssl

;; a Stream is:
;;   (make-stream number (-> Stream))
(define-struct stream (num rest))

#;
(define (stream-template stream)
 .. (stream-num stream)
 .. (stream-template ((stream-rest stream))))

; take : Nat Stream -> (Listof Numbers)
; to find the nth element of the stream.
; structural template on Nat.

(check-expect (take 10 nats)
              (list 1 2 3 4 5 6 7 8 9 10))


(define (take n stream)
  (cond
    [(zero? n) '()]
    [else (cons (stream-num stream)
                (take (- n 1) ((stream-rest stream))))]))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; add1-stream : Stream -> Stream
; Take a steam and returns a stream with every element added
; one more than previous element.

(check-expect (take 10 nats)
              (list 1 2 3 4 5 6 7 8 9 10))
           
(define (add1-stream stream)
  (make-stream (add1 (stream-num stream))
               (lambda () (add1-stream ((stream-rest stream))))))

(define nats (make-stream 1 (lambda () (add1-stream nats))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; square-stream : Stream -> Stream
; Take a stream and returns a stream with every element squared.

(check-expect (take 10 squares)
              (list 0 1 4 9 16 25 36 49 64 81))
(check-expect (take 20 squares)
(list 0 1 4 9 16 25 36 49 64 81 100 121 144 169 196 225 256 289 324 361))

(define (square-stream stream)
  (make-stream (sqr (stream-num stream))
               (lambda () (square-stream ((stream-rest stream))))))

(define squares 
  (make-stream 0
               (lambda () (square-stream nats))))
;------------------------------------------------------------------

; negetive-or-positive-multi : number -> number
; Take a number to determine next even number.
; - Zero : 2
; - Positive : it's negetive number
; - Negative : abs(number) + 2

(check-expect (negetive-or-positive-multi 0) 2)
(check-expect (negetive-or-positive-multi 2) -2)
(check-expect (negetive-or-positive-multi -4) 6)

(define (negetive-or-positive-multi number)
  (cond
    [(positive? number) (- 0 number)]
    [else
     (+ (* number -1) 2)]))

; even-stream : stream -> stream
; generate a stream with all even numbers

(check-expect
 (take 10 evens)
 (list 0 2 -2 4 -4 6 -6 8 -8 10))

(define (even-stream stream)
  (make-stream (negetive-or-positive-multi (stream-num stream))
               (lambda () (even-stream ((stream-rest stream))))))

(define evens
  (make-stream 0
               (lambda () (even-stream evens))))



;------------------------------------------------------------------

; fibonacci-stream : stream number -> stream
; add the element to the next.

(check-expect (take 15 fibs)
              (list 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377))

(check-expect (take 30 fibs)
              (list 0 1 1 2 3 5 8 13 21 34 55 89 144 233 377
                    610 987 1597 2584 4181 6765 10946 17711 28657
                    46368 75025 121393 196418 317811 514229))

(check-expect (take 20 fibs-without-zero)
(list 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 4181 6765))

(define (fibonacci-stream stream n)
  (make-stream (+ (stream-num stream) n)
               (lambda () (fibonacci-stream ((stream-rest stream))
                                            (stream-num stream)))))
(define fibs
  (make-stream 0
               (lambda () (fibonacci-stream fibs 1))))

(define fibs-without-zero
  (make-stream 1
               (lambda () (fibonacci-stream fibs-without-zero 0))))
