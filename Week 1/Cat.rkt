;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname Cat) (read-case-sensitive #t) (teachpacks ((lib "universe.rkt" "teachpack" "2htdp") (lib "image.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "universe.rkt" "teachpack" "2htdp") (lib "image.rkt" "teachpack" "2htdp")) #f)))
;HW 01 animal

(require 2htdp/image)

(define LIGHT-PINK (color 255 205 255)) ;(color 255 205 255): light pink
(define DARK-GRAY  (color 128 128 128)) ;(color 128 128 128): dark gray
(define LIGHT-GRAY (color 178 178 178)) ;(color 178 178 178): light gray


(define eye
  (overlay/align
   "center"
   "bottom"
   (above 
    (overlay 
     (circle 3 "solid" "black")
     (circle 5 "solid" "blue"))
     (circle 1.5 "solid" "white"))
     (circle 10 "solid" "white")
  )
)


(define nose
  (rotate 180
   (triangle 20 "solid" LIGHT-PINK)
  )
)

(define mouth
  (circle 10 "solid" "black")
)

(define left-ear
  (rotate 30
   (overlay
    (triangle 20 "solid" LIGHT-PINK)
    (triangle 40 "solid" DARK-GRAY)
   )
  )
)

(define right-ear
  (flip-horizontal left-ear)
)

(define whisker
  (above
   (flip-vertical
    (line 30 5 "black")
   )
   (crop 0 0 23 10 (line 30 5 "black"))
  )
)

(define cat-with-eyes-nose-mouth-whisker
 (overlay/align
   "center"
   "bottom"
  (above
   (rectangle 30 10 "solid" DARK-GRAY)
   (beside
    eye
    (circle 8 "solid" DARK-GRAY )
    eye
   )
   (beside
    (flip-horizontal whisker)
    nose
    whisker
   )
  (circle 2 "solid" DARK-GRAY )
   mouth
  )
  (circle 50 "solid" DARK-GRAY)
 )
)

(define cat-face
  (overlay/align
   "center"
   "top"
   (beside
    left-ear
    (rectangle 30 10 "solid" DARK-GRAY)
    right-ear
   )
   cat-with-eyes-nose-mouth-whisker
  )
)


(define cat-body (circle 60 "solid" LIGHT-GRAY))

(define cat-face-body (overlay/offset cat-face
                  40 60
                 cat-body))

(define cat-paw (circle 17 "solid" DARK-GRAY))
(define two-cat-paw (beside cat-paw (rectangle 30 0 "solid" DARK-GRAY) cat-paw))

(define cat-face-body-paw (overlay/offset two-cat-paw
                  -10 -73
                 cat-face-body))


(define cat-tail (overlay/offset
                   (overlay/offset
                    (overlay/offset
                      (overlay/offset
                           (circle 7 "solid" DARK-GRAY)
                            -1 7
                           (circle 9 "solid" LIGHT-GRAY))
                        -5 9
                       (circle 11 "solid" DARK-GRAY)
                      )
                     -8 15
                    (circle 13 "solid" LIGHT-GRAY))
                    -13 17
                    (circle 15 "solid" DARK-GRAY)
                   ))

(define cat-face-body-paw-tail (overlay/offset
                                   cat-face-body-paw
                                   85 -9
                                   cat-tail))

cat-face-body-paw-tail

