;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname V7alpaca-genealogy_Unrevised) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
#|
Problems

The Alpaca Owners and Breeders Association needs
your help! They’re having trouble using the database of
detailed pedigree records that they keep for all registered
alpacas.

But first, some background. For every alpaca in the
registry, they keep several different pieces of
information:

- name
- sex
- date of birth
- fleece color
- sire (father), if known
- dam (mother), if known

Unsurprisingly, AOBA uses DrRacket to store and query the
alpaca registry, with the following data definitions:
|#

; A Sex is one of:
; - "female"
; - "male"

; A DoB is (make-date Year Month Day)
;   where
; Year is an Integer in [1900, 2100]
; Month is an Integer in [1, 12]
; Day is an Integer in [1, 31]
(define-struct date (year month day))

; An Alpaca is one of:
; - (make-alpaca String Sex DoB Color Alpaca Alpaca)
; - "unknown"
(define-struct alpaca (name sex dob color sire dam))



;;a list-of-Alpaca is either:
;;-'()
;;-(cons Alpaca list-of-Alpaca)



;; An examples, here’s the representation of the record for some Alpacas:

(define dana-andrews
  (make-alpaca "Dana Andrews"
               "female"
               (make-date 1996 8 14)
               "silver"
               "unknown"
               "unknown"))
(define jericho
  (make-alpaca "Jericho de Chuchata"
               "male"
               (make-date 1997 11 23)
               "black"
               "unknown"
               "unknown"))
(define sylvan 
  (make-alpaca "MA Sylvan"
               "male"
               (make-date 2001 5 16)
               "black"
               "unknown"
               "unknown"))
(define mfa
  (make-alpaca "MFA Independence"
               "female"
               (make-date 2002 7 2)
               "black"
               jericho
               dana-andrews))
(define irene
  (make-alpaca "Irene of Acorn Alpacas"
               "female"
               (make-date 2007 5 21)
               "silver"
               sylvan
               mfa))

#|

First, add two more alpacas.
(Come back here and add more Alpacas that
you think would make good test cases as
you design the rest of the functions for
this homework assignment.)



|#

(define maleA1
  (make-alpaca "maleA1"
               "male"
               (make-date 2008 5 21)
               "black"
               sylvan
               mfa))

(define maleA2
  (make-alpaca "maleA2"
               "male"
               (make-date 1953 5 21)
               "black"
               sylvan
               mfa))

(define maleA2-sex-error
  (make-alpaca "maleA2-sex-error"
               "male"
               (make-date 1953 5 21)
               "black"
                mfa
               sylvan
               ))


(define maleA3
  (make-alpaca "maleA3"
               "male"
               (make-date 2010 5 21)
               "black"
               maleA2
               mfa))


(define maleA3-sex-error
  (make-alpaca "maleA3-sex-error"
               "male"
               (make-date 2010 5 21)
               "black"      
               mfa
               maleA2))


(define maleA3-drt-A2-sex-er
  (make-alpaca "maleA3-drt-A2-sex-er"
               "male"
               (make-date 2010 5 21)
               "black"
               maleA2-sex-error
               mfa))


(define maleA3-drt-A2-sex-er-and-itslf
  (make-alpaca "maleA3-drt-A2-sex-er-and-itslf"
               "male"
               (make-date 2010 5 21)
               "black"
               mfa
               maleA2-sex-error
               ))

;;No father
(define maleA4
  (make-alpaca "maleA4"
               "male"
               (make-date 2008 5 21)
               "black"
               "unknown"
               mfa))

#|
Second, AOBA would like a program to make a rather simple
query: Given an alpaca, they would like to find out the
names of all the female-line ancestors of the given alpaca
in a list, youngest to oldest, and including the given
alpaca. So for example, given the structure for Irene above,
it should return the list

(list "Irene of Acorn Alpacas"
      "MFA Independence"
      "Dana Andrews")

which contains Irene's name, her mother's name, and her
grandmother's name, and then stops because her great
grandmother is unknown. Design the function female-line.
(You probably need a new data definition in order to write
the correct signature.)

|#







;;sk-fm-acst: Alpaca -> a list-of-Alpaca
;;find the names of all the female-lin ancetors of the given alpaca in a list
;;Eample: see test section
(check-expect (sk-fm-acst  irene)
              (list irene
                    mfa
                    dana-andrews))


(check-expect (sk-fm-acst  sylvan)
              '())

(check-expect (sk-fm-acst  mfa)
              (list  mfa dana-andrews))

(check-expect (sk-fm-acst  maleA1)
             (list   mfa   dana-andrews))


(check-expect (sk-fm-acst  maleA4)
             (list   mfa   dana-andrews))



(define (sk-fm-acst alp)
        (cond        
          [(string=? "female" (alpaca-sex alp))
           (cond
                       [(not (equal? "unknown" (alpaca-dam alp)))
                        (cons alp  (sk-fm-acst (alpaca-dam alp)))]
                       [else (cons alp '())])]
          [(string=? "male" (alpaca-sex alp))
           (cond
                       [(not (equal? "unknown" (alpaca-dam alp)))
                        (sk-fm-acst (alpaca-dam alp))]
                        [else '()])]                    
           ))
          

#|
Many breeders raise alpacas for their fleece, which comes in
a wide variety of colors and may be made into a wide variety
of textiles. Some breeders are interested in breeding
alpacas with new colors and patterns, and to do so, they
need to understand how fleece colors and patterns are
inherited.

You can help them by designing a function has-color? that
takes an alpaca pedigree and a color, and reports whether or
not that color is known to appear anywhere in the pedigree tree.
|#




;;has-color: Alpaca color ->boolean
;;reports whether or not that color is known to appear anywhere in the pedigree tree
;;Example: see test section
(check-expect (has-color? maleA1 "black") #true )
(check-expect (has-color? irene "black") #true )
(check-expect (has-color? irene "pink") #false )
(check-expect (has-color? irene "silver") #true )




(define (has-color? alp clr)
  (or (equal? clr (alpaca-color alp))
      (cond
        [(not (equal? "unknown" (alpaca-dam alp)))
         (has-color? (alpaca-dam alp) clr)]
        [else #false])
      (cond
        [(not (equal? "unknown" (alpaca-sire alp)))
         (has-color? (alpaca-sire alp) clr)]
        [else #false]))
  )    


  





#|
AOBA is worried about fraud in their registry. Eventually
they’ll send investigators into the field, but first they’d
like to run a simple sanity check on the database. Given the
pedigree record for an alpaca, there are two simple errors
that you can find:

Some alpaca in the tree has a birthday before one of his or
her parents.

Some alpaca in the tree has a male alpaca listed as dam or a
female alpaca listed as sire.

Design a function pedigree-error? that returns true if a
given Alpaca has one of those two obvious errors in his or
her pedigree, and false otherwise.
|#

;;pedigree-error?: Alpaca  ->boolean

;;Check whether the alpaca has the following issues (either or both):
;;-Some alpaca in the tree has a birthday before one of his or her parents.
;;-Some alpaca in the tree has a male alpaca listed as dam or a
;; female alpaca listed as sire.

;;Example: see test section
(check-expect (pedigree-error? maleA3)  #true) ;;Age incorrect, gender correct

(check-expect (pedigree-error? irene) #false) ;;Age correct, gender correct

(check-expect (pedigree-error? maleA3-drt-A2-sex-er)   #true );;Age correct, gender incorrect
(check-expect (pedigree-error? maleA2-sex-error)   #true );;Age incorrect, gender incorrect

(define (pedigree-error? alp)
  (or (wrong-dob? alp)
     (wrong-prt-gdr? alp)))




;;wrong-prt-gdr?: Alpaca  ->boolean
;;Check whether the alpaca has the following issue:
;;-Some alpaca in the tree has a male alpaca listed as dam or a
;; female alpaca listed as sire.

;;Example: see test section

(check-expect (wrong-prt-gdr? maleA3) #false)
(check-expect (wrong-prt-gdr? maleA3-sex-error) #true)
(check-expect (wrong-prt-gdr? maleA3-drt-A2-sex-er) #true)
(check-expect (wrong-prt-gdr? maleA3-drt-A2-sex-er-and-itslf) #true)
(check-expect (wrong-prt-gdr? irene) #false)
(check-expect (wrong-prt-gdr? maleA4) #false)

(define (wrong-prt-gdr? alp)
  (cond
  [(and (equal? "unknown" (alpaca-dam alp))
        (equal? "unknown" (alpaca-sire alp)))
   #false]

  [else
   (or
      (not (equal? "female" (alpaca-sex (alpaca-dam alp))))
      (not (equal? "male" (alpaca-sex (alpaca-sire alp))))    
       (cond
         [(not (equal? "unknown" (alpaca-dam alp)))
          (wrong-prt-gdr? (alpaca-dam alp) )]
         [else #false])
       (cond
         [(not (equal? "unknown" (alpaca-sire alp)))
          (wrong-prt-gdr?  (alpaca-sire alp))]
         [else #false]))]))
  








;;wrong-dob?: Alpaca  ->boolean
;;Check whether the alpaca has the following issue:
;;-Some alpaca in the tree has a birthday before one of his or her parents.

;;Example see test section
(check-expect (wrong-dob? mfa) #false)
(check-expect (wrong-dob? maleA2) #true)
(check-expect (wrong-dob? maleA3) #true)



(define (wrong-dob? alp)
  (cond
  [(and (equal? "unknown" (alpaca-dam alp))
        (equal? "unknown" (alpaca-sire alp)))
   #false]
  ;;[(equal? "unknown" (alpaca-sire alp)) #true]
  [else
   (or (earlier? (alpaca-dob alp) (alpaca-dob (alpaca-dam alp)))
       (earlier? (alpaca-dob alp) (alpaca-dob (alpaca-sire alp)))
       (cond
         [(not (equal? "unknown" (alpaca-dam alp)))
          (wrong-dob? (alpaca-dam alp) )]
         [else #false])
       (cond
         [(not (equal? "unknown" (alpaca-sire alp)))
          (wrong-dob? (alpaca-sire alp))]
         [else #false]))]))
  


     
;;earlier?: date date -> boolean
;;Compare two dates, if date1 is earlier than date2 than return #true, else return #false
;;Example: see test section


;;Create the test cases
(define tst1 (make-date 1993 5 5))
(define tst2 (make-date 1993 5 5))
(define tst3 (make-date 1994 5 5))
(define tst4 (make-date 1993 6 5))
(define tst5 (make-date 1993 5 6))
(define tst6 (make-date 1993 5 4))
(define tst7 (make-date 1993 5 7))

(check-expect (earlier? tst1 tst2) #true)
(check-expect (earlier? tst1 tst3) #true)
(check-expect (earlier? tst1 tst4) #true)
(check-expect (earlier? tst1 tst5) #true)
(check-expect (earlier? tst3 tst1) #false)
(check-expect (earlier? tst4 tst1) #false)
(check-expect (earlier? tst6 tst1) #true)
(check-expect (earlier? tst7 tst1) #false)

(define (earlier? dt1 dt2)
  (cond
   [(< (date-year dt1) (date-year dt2)) #true]
   [(> (date-year dt1) (date-year dt2)) #false]
   [else
    (cond
      [(< (date-month dt1) (date-month dt2))#true]
      [(> (date-month dt1) (date-month dt2))#false]
      [else
       (cond
         [(< (date-day dt1) (date-day dt2))#true]
         [(= (date-day dt1) (date-day dt2))#true]
         [else #false])])]))

#|
For all other problems in this assignment, you may assume
that all alpaca records are valid, in the sense that
pedigree-error? answers false for them. In the next problem,
for example, it will save you trouble if you don’t have to
consider the possibility that any alpaca’s date of birth
could precede its parents’.

Tracing back an alpaca’s ancestry as far as possible is a
point of pride in the alpaca-raising community. Design a
function oldest-ancestor that, given an alpaca’s pedigree
record, returns its oldest known ancestor's name and
returns #false if there is no known ancestor.

Hint: Use a data definition:

  An maybe-name is either:
     #false
     string

and write functions that operate on it, discovering which
ones you need as you work out oldest-ancestor.
|#


;;An maybe-name is either:
;;    #false
;;    string

;;oldest-ancestor: Alpaca  -> An maybe-name
;;Find the oldest-ancestor of given ancestor,
;;if the alpaca does not have a ancestor, then return #false
;;else find the oldest ancestor

;;Example: see test section
(check-expect (oldest-ancestor irene) dana-andrews)
(check-expect (oldest-ancestor jericho) #false)

(define (oldest-ancestor alp)
  (cond [(and (equal? "unknown" (alpaca-dam alp))
                    (equal? "unknown" (alpaca-sire alp)))
               #false]
              [else
               (get-oldest-exst-ancestor alp)]))

;;oldest-ancestor: Alpaca  -> Alpaca
;;Find the oldest-ancestor of given ancestor,
;;find the oldest ancestor OF alpaca
;;Example: see test section

;;Origin
(define irene-o-a-1
  (make-alpaca "Irene OA1"
               "female"
               (make-date 2007 5 21)
               "silver"
               sylvan
               mfa))

;;without mother
(define irene-o-a-2  
  (make-alpaca "Irene OA2"
               "female"
               (make-date 2007 5 21)
               "silver"
               sylvan
               "unknown"))

;;without father
(define irene-o-a-3  
  (make-alpaca "Irene of OA3"
               "female"
               (make-date 2007 5 21)
               "silver"             
               "unknown"
                mfa))


(check-expect (get-oldest-exst-ancestor irene) dana-andrews)

(check-expect (get-oldest-exst-ancestor irene-o-a-2) sylvan)
(check-expect (get-oldest-exst-ancestor irene-o-a-3) dana-andrews)


(define (get-oldest-exst-ancestor alp)            
        (cond
          ;;have both parents
          [(and (not (equal? "unknown" (alpaca-dam alp)))
                (not (equal? "unknown" (alpaca-sire alp))))
           (get-older-alpaca
            (get-oldest-exst-ancestor
             (alpaca-dam alp))
            (get-oldest-exst-ancestor
             (alpaca-sire alp)))]
          
           ;;have only mather
          [(and (not (equal? "unknown" (alpaca-dam alp)))
                (equal? "unknown" (alpaca-sire alp)))
           (get-oldest-exst-ancestor (alpaca-dam alp))]

          ;;have only father
          [(and (equal? "unknown" (alpaca-dam alp))
                (not (equal? "unknown" (alpaca-sire alp))))
           (get-oldest-exst-ancestor (alpaca-sire alp))]

          [else alp] ))


;;get-older-alpaca: alpaca alpaca -> alpaca
;;return the older alpaca
;;Example: see test section

;;Origin
(define sylvan1
  (make-alpaca "MA Sylvan"
               "male"
               (make-date 2001 5 16)
               "black"
               "unknown"
               "unknown"))
;;Same date 
(define sylvan2
  (make-alpaca "MA Sylvan"
               "male"
               (make-date 2001 5 16)
               "black"
               "unknown"
               "unknown"))


;;Has early date 
(define sylvan3
  (make-alpaca "MA Sylvan"
               "male"
               (make-date 1901 5 16)
               "black"
               "unknown"
               "unknown"))
(check-expect (get-older-alpaca dana-andrews jericho) dana-andrews)
(check-expect (get-older-alpaca sylvan1 sylvan3) sylvan3)

(define (get-older-alpaca alp1 alp2)
(cond
  [(earlier? (alpaca-dob alp1) (alpaca-dob alp2)) alp1]
  [else alp2]))



;;get-older-alpaca: alpaca alpaca -> alpaca
;;return the younger alpaca
;;Example: see test section
(check-expect (get-younger-alpaca dana-andrews jericho) jericho)
(check-expect (get-younger-alpaca sylvan1 sylvan3) sylvan1)

(define (get-younger-alpaca alp1 alp2)
(cond
  [(earlier? (alpaca-dob alp1) (alpaca-dob alp2)) alp2]
  [else alp1]))


;;A list-of-alpaca is either:
;;-'()
;;-(cons alpaca list-of-alpaca)
        
;;has-no-prt-list: Alpaca  -> A list-of-alpaca
;;Find the oldest-ancestor of given ancestor, if

;;(check-expect (has-no-prt-list irene) (list dana-andrews jericho sylvan ))

#|
(define (has-no-prt-list alp)
        (cond
          [(equal? "unknown" alp) '()]
          [(and (equal? "unknown" (alpaca-dam alp)) (equal? "unknown" (alpaca-sire alp)))
            alp ]

               

           (cond
             [(no-parents? alp) alp  ]                                
             [(not (equal? "unknown" (alpaca-dam alp)))
              (has-color? (alpaca-dam alp) clr)]
             
             [(not (equal? "unknown" (alpaca-sire alp)))
              (has-color? (alpaca-sire alp) clr)]
       


  )|#

;(check-expect (sk-m-acst  irene)
          ;    (list jericho sylvan))
           
(define (sk-m-acst alp)
        (cond        
          [(equal? "male" (alpaca-sex alp))
           (cond
                       [(not (equal? "unknown" (alpaca-sire alp)))
                        (cons alp  (sk-m-acst (alpaca-sire alp)))]
                        [(not (equal? "unknown" (alpaca-dam alp)))
                        (sk-m-acst (alpaca-sire alp))]
                       [else (cons alp '())])]
          
          [(equal? "female"(alpaca-sex alp))
           (cond
                       [(not (equal? "unknown" (alpaca-sire alp)))
                        (sk-m-acst (alpaca-sire alp))]
                       [(not (equal? "unknown" (alpaca-dam alp)))
                        (sk-m-acst (alpaca-sire alp))]
                        [else '()])]                    
           ))





(define (no-parents? alp)
    (cond
      [(and (equal? "unknown" (alpaca-dam alp)) (equal? "unknown" (alpaca-sire alp))) #true]
      [else false])) 


#|
AOBA also wants a way to list all the known ancestors of a
given alpaca (including the given alpaca) in reverse birth
order. For example, for Irene, the result would be:

  (list irene
        mfa
        sylvan
        jericho
        dana-andrews)

Design a function all-ancestors/sorted to perform this task.

Hint: In order to do so, you will need a data definition for
a list of alpacas (the conventional one will do), and you
will likely need a helper function merge-alpacas that, given
two sorted lists of alpacas, merges them into a single
sorted list of alpacas. See HTDP/2e section 26.5 for how
to design a template for this:

  http://www.ccs.neu.edu/home/matthias/HtDP2e/part_four.html#%28part._sec~3atwo-inputs~3adesign%29

|#

;;Template:
;;

;;rtv-lst-alp-ord: alpaca -> A list-of-alpaca
;;Retrieve the known ancestors of a
;;given alpaca (including the given alpaca) in reverse birth order

;;Example: see test section


(check-expect (rtv-lst-alp-ord "unknown") '())
(check-expect (rtv-lst-alp-ord mfa) (list mfa jericho dana-andrews  ))
(check-expect (rtv-lst-alp-ord irene) (list irene mfa sylvan jericho dana-andrews ))


(define (rtv-lst-alp-ord alp)
   (sort (get-all-alp alp)))



;;A list-of-alpaca is either:
;;-'()
;;-(cons alpaca list-of-alpaca)

;;sort: list-of-alpaca   -> A list-of-alpaca

(define (sort l)
    (cond
      [(empty? l) l]
      [else (insert  (first l) (sort (rest l)))]))

(define (insert alp l)
    (cond
      [(empty? l) (list alp)]
      [else (cond
              [(not (earlier? (alpaca-dob alp)  (alpaca-dob (first l)))) (cons alp l)]
               ;(< (string-length x) (string-length (first l))) (cons x l)]
              [else (cons (first l) (insert alp (rest l)))])]))


;;get-all-alp: Alpaca  -> A list-of-alpaca
;;Find theancestor of the given ancestor includes the input alpaca

(check-expect (get-all-alp "unknown") '())
(check-expect (get-all-alp dana-andrews) (list dana-andrews))
(check-expect (get-all-alp mfa) (list mfa dana-andrews jericho ))

;;test only father case
(check-expect (get-all-alp irene-o-a-2) (list irene-o-a-2  sylvan   ))
;;test only mother case
(check-expect (get-all-alp irene-o-a-3) (list irene-o-a-3 mfa dana-andrews jericho  ))

(define (get-all-alp alp)
    (cond [ (equal? "unknown" alp)                   
               '()]
              [else
               (get-all-exist-alp alp)])
  )



;;get-all-alp Alpaca  -> A list-of-alpaca
;;Find theancestor of the given ancestor (it is not "unknown") includes the input alpaca

;;(check-expect (has-no-prt-list irene) (list dana-andrews jericho sylvan ))

(check-expect (get-all-exist-alp dana-andrews) (list dana-andrews))
(check-expect (get-all-exist-alp mfa) (list mfa dana-andrews jericho ))

;;test only father case
(check-expect (get-all-exist-alp irene-o-a-2) (list irene-o-a-2  sylvan   ))
;;test only mother case
(check-expect (get-all-exist-alp irene-o-a-3) (list irene-o-a-3 mfa dana-andrews jericho  ))


(define (get-all-exist-alp alp)
     (cond
          ;;have both parents
          [(and (not (equal? "unknown" (alpaca-dam alp)))
                (not (equal? "unknown" (alpaca-sire alp))))
           (append (cons alp '())
                   (get-all-exist-alp (alpaca-dam alp))
                   (get-all-exist-alp (alpaca-sire alp)))]

          
           ;;have only mather
          [(and (not (equal? "unknown" (alpaca-dam alp)))
                (equal? "unknown" (alpaca-sire alp)))
           
           (append (cons alp '())
                    (get-all-alp (alpaca-dam alp))
                 )]

          ;;have only father
          [(and (equal? "unknown" (alpaca-dam alp))
                (not (equal? "unknown" (alpaca-sire alp))))           
             (append (cons alp '())
                    (get-all-exist-alp (alpaca-sire alp))
                 )]

          [else (list alp)] ))
