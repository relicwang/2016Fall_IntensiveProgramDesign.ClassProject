;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname V1aa) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
#|
Persistent AA trees
An AA tree is a form of binary search tree that maintains the overall
shape of the tree (and thus good algorithmic properties) during insert
operations.
Here's the datastructure for it:
|#

;; An [AA-tree X] is:
;;  (make-tree [AA-node X] Natural [X X -> Boolean])
(define-struct tree (root size less-than))

#;
(define (tree-template a-tree)
  (node-template (tree-root a-tree)) ...
  (tree-size a-tree) ...
  (tree-less-than a-tree) ...)

;; An [AA-node X] is one of:
;;   - "leaf"
;;   - (make-node X Natural [AA-node X] [AA-node X])
(define-struct node (value level left right))

#;
(define (node-template a-node)
  (cond
    [(equal? "leaf" a-node) ...]
    [else (node-value a-node)
          (node-level a-node)
          (node-template (node-left a-node))
          (node-template (node-right a-node))]))

#|
The less-than operation must be a strict comparsion operation. That is,
it must be the case that, for any two possible x1 and x2 that are both Xs,
at most one of these two expressions can return #true:
  (less-than x1 x2)
  (less-than x2 x1)
This means that you can compare any two elements in the tree with a
`cond` expression like this one:
|#

#;
(cond
 [(less-than x1 x2) ...] ;; x1 < x2 
 [(less-than x2 x1) ...] ;; x1 > x2
 [else ...])             ;; x1 = x2


#|
As compared with the normal binary search tree, each node has an
additional natural number, the level.  There are a number of rules
that govern the relationship between the values of the level field of
a parent and its children. We collectively call these rules the AA
invariant. They are:
   - the level of a left-child is one less than the level of the
     parent
   - the level of a right child is either the same as the parent or
     one less. If it is the same, then the right child of the right
     child must be one less (so no two consecutive right children can
     have the same level)
where the level of a leaf node counts as 0.
And, of course, the binary search tree invariant also holds:
  - the values of all nodes in a left child are less than the value in
    the node
  - the values of all nodes in a right child are less than the value
    in that node
|#

;; nlevel : [AA-node X] -> Natural
(define (nlevel n)
  (cond
    [(equal? n "leaf") 0]
    [else (node-level n)]))

;; level invariants:
;; level-left is ONE LESS THAN level-parent DONE
;; level-right either EQUAL or ONE LESS THAN level-parent
;; if level-right equal, level-right-right is ONE LESS THAN level-right
;; level-"leaf" = 0 DONE

;; aa-invariant? : [AA-node X] -> Boolean
;; checks that the AA invariant is working
(define (aa-invariant? n)
  (cond
    [(equal? "leaf" n) #true]
    [(level-check? n)
     (and (aa-invariant? (node-left n))
          (aa-invariant? (node-right n)))]
    [else #false]))


;; level-check? [AA-node X] -> Boolean
;; Checks that the level of the left node is ONE LESS THAN the level of a parent node
;; and checks that the level of the right node is either equal to the parent or
;; one less than the parent. If equal to the parent, the right child of the right child
;; must be one less than the right child.
(define (level-check? n)
  (and (= (nlevel (node-left n)) (- (nlevel n) 1)) ;; checks left node

       (or (= (nlevel (node-right n)) (- (nlevel n) 1))

           (and (= (nlevel (node-right n)) (nlevel n))
                (= (nlevel (node-right (node-right n))) (- (nlevel n) 1))))))

;; bs-invariant? :: [AA-node X] [AA-tree X] -> Boolean
;;  - the values of all nodes in a left child are less than the value in
;;    the node
;;  - the values of all nodes in a right child are less than the value
;;    in that node
(define (bs-invariant? n t)
  (cond
    [(or (equal? "leaf" n)
         (equal? "leaf" (node-left n))
         (equal? "leaf" (node-right n))) #true]
    [(and ((tree-less-than t) (node-value (node-left n)) (node-value n))
          ((tree-less-than t) (node-value n) (node-value (node-right n))))
     
     (and (bs-invariant? (node-left n) t)
          (bs-invariant? (node-right n) t))]
    [else #false]))

;; invariant-working? : [AA-tree X] -> Boolean
(define (invariant-working? t)
  (and (bs-invariant? (tree-root t) t)
       (aa-invariant? (tree-root t))))
         

;; binary search invariant:
;; left-node-value < node-value < right-node-value

;; Examples.

;; Define the example [AA-tree number] that has only the number 0
;; in it and uses < and = as the less than and comparison operation.
(define zero (make-tree (make-node 0 1 "leaf" "leaf") 1 <=))

(check-expect (invariant-working? zero) #true)



;; There is only one [AA-tree number] that has the numbers 1, 2, and 3 in
;; it, using < and = as the less than and comparison operation. Define it.
(define one-two-three (make-tree (make-node 2 2 (make-node 1 1 "leaf" "leaf") (make-node 3 1 "leaf" "leaf")) 3 <=))

(check-expect (invariant-working? one-two-three) #true)

;; Similarly, there is only one that has the strings "one" "two" and "three"
;; in it, using string<? as the comparison predicate. Define it.
(define one-two-three-string (make-tree (make-node "three" 2 (make-node "one" 1 "leaf" "leaf") (make-node "two" 1 "leaf" "leaf")) 3 string<?))

(check-expect (invariant-working? one-two-three-string) #true)

;; There are two [AA-tree number]s that have the numbers 1, 2, 3, and
;; 4 in them (when using < and =). Define them both. The constraint
;; that all "leaf"s have level 0 means that many of the trees that
;; you might think are AA trees really are not.
(define one-two-three-four-a (make-tree (make-node 2 2
                                                   (make-node 1 1 "leaf" "leaf")
                                                   (make-node 3 1 "leaf"
                                                              (make-node 4 1 "leaf" "leaf")))
                                        4 <=))
(define one-two-three-four-b (make-tree (make-node 3 2
                                                   (make-node 2 1 "leaf"
                                                              (make-node 1 1 "leaf" "leaf"))
                                                   (make-node 4 1 "leaf" "leaf"))
                                        4 <=))

(check-expect (invariant-working? one-two-three-four-a) #true)
(check-expect (invariant-working? one-two-three-four-b) #true)

;; Define an [AA-tree number] that has at least 6 numbers in it.
;; Use > and = as the comparsion and equality.
(define six-nodes (make-tree (make-node 4 3
                                        (make-node 2 2
                                                   (make-node 1 1 "leaf" "leaf")
                                                   (make-node 3 1 "leaf" "leaf"))
                                        (make-node 6 2
                                                   (make-node 5 1 "leaf" "leaf")
                                                   (make-node 7 1 "leaf" "leaf")))
                             7 <=))
                                        

(check-expect (invariant-working? six-nodes) #true)

#|
The first function we are going to design is a lookup function.
It should look in the tree only in places that might have the
number. In other words, be sure that the function you write takes
advantage of the binary search tree invariant.
|#

;; lookup : [AA-tree X] X -> Boolean
;; to determine if `x` occurs in `tree

(define (lookup t x)
  (cond
    [(equal? (nlevel (tree-root t)) 0) #false]
    [(equal? (node-value (tree-root t)) x) #true]
    [((tree-less-than t) x (node-value (tree-root t))) (lookup (next-tree t "left") x)]
    [((tree-less-than t) (node-value (tree-root t)) x) (lookup (next-tree t "right") x)]))

;; next-tree : [AA-tree X] String -> [AA-tree X]
;; determines the next subtree to search and adjusts the size of the tree correctly
(define (next-tree t s)
  (cond
    [(string=? s "left")  (make-tree (node-left (tree-root t))
                                    (- (/ (tree-size t) 2) 1)
                                    (tree-less-than t))]
    [(string=? s "right") (make-tree (node-right (tree-root t))
                                    (- (/ (tree-size t) 2) 1)
                                    (tree-less-than t))]))

(check-expect (lookup six-nodes 7) #true)
(check-expect (lookup six-nodes 8) #false)
(check-expect (lookup six-nodes 1) #true)
(check-expect (lookup six-nodes 3) #true)
(check-expect (lookup one-two-three-string "one") #true)
(check-expect (lookup one-two-three-string "four") #false)
                                                          

#|
Our next goal is to design an insertion function.
Start by designing a function that inserts a number into a given tree
without regard for the 'level' invariants, paying attention only to
the binary search tree invariant.  It should insert the new value in
the place of some leaf node and leave all of the other levels alone.
The new node should have level 1.
|#
;; insert-wrong : [AA-node X] X [X X -> Boolean] -> [AA-node X]
;; inserts 'value' into 'node' using 'less-than' without
;; regard to the AA invariant.
(check-expect (insert-wrong (make-node 4 1 "leaf" "leaf") 5 <=) (make-node 4 1 "leaf" (make-node 5 1 "leaf" "leaf")))
(check-expect (insert-wrong (make-node 4 1 "leaf" "leaf") 3 <=) (make-node 4 1 (make-node 3 1 "leaf" "leaf") "leaf"))
(check-expect (insert-wrong (make-node 3 1 "leaf" "leaf") 3 <=) (make-node 3 1 "leaf" "leaf"))
(check-expect (insert-wrong (make-node 5 2 (make-node 4 1 "leaf" "leaf") (make-node 6 1 "leaf" "leaf")) 7 <=)
              (make-node 5 2 (make-node 4 1 "leaf" "leaf") (make-node 6 1 "leaf" (make-node 7 1 "leaf" "leaf")))
              )
(check-expect (insert-wrong (make-node 5 2 (make-node 4 1 "leaf" "leaf") (make-node 6 1 "leaf" "leaf")) 3 <=)
              (make-node 4 1 (make-node 3 1 "leaf" "leaf") "leaf"))

(define (insert-wrong given v less-than)
  (cond
    [(equal? v (node-value given)) given]
    [(less-than v (node-value given))
     (cond
          
       [(equal? (node-left given) "leaf")

        (make-node
         (node-value given)
         (node-level given)
         (make-node v 1 "leaf" "leaf")
         (node-right given))]

       [else (insert-wrong (node-left given) v less-than)])]
    [(less-than (node-value given) v)
     (cond

       [(equal? (node-right given) "leaf")

        (make-node
         (node-value given)
         (node-level given)
         (node-left  given) 
         (make-node v 1 "leaf" "leaf"))]

       [else (insert-wrong (node-right given) v less-than)])]))

#|
Next, find two example AA-nodes and numbers such that, when passed to
insert-wrong, each returns a tree that is not an AA-tree. One of the
examples should violate the constraint that the left child is one
level lower than its parent and the other should violate the contraint
that the right-right grandchild is (at least) one level below the parent.
Add these two examples as test cases.
|#

(define test1 (make-node 5 1 "leaf" "leaf"))
;; inserting 4 into test1 violates the constraint that the left child is one level
;; lower than its parent

(define test2 (make-node 10 1 "leaf" (make-node 11 1 "leaf" "leaf")))
;; inserting 12 into test2 violates the constraint that the right-right grandchild
;; is (at least) one level below the parent


#|
The invariant-preserving version of AA tree insert looks very much like
incorrect one, except that, each time it recursively processes a
"node", it performs two additional operations, a 'skew' and a 'split' on
the result before returning it.
In order to define those operations we first need to define two helper
functions, rotate-left and rotate-right.
The rotate-left function adjusts the nodes in a BST in a way that
preserves the ordering but changes the shape of the tree.
Specifically, if you have a tree with three nodes (A B C D) at
the top and then four trees (t1 t2 t3 t4) below them in this shape:
     B
    / \
   /   \
  A     C
 / \   / \
t1 t2 t3 t4
then you can rotate it to the left to produce this tree:
      C
     / \
    B   t4
   / \
  A   t3
 / \ 
t1 t2
If the first tree supported the binary search tree invariant, then so
does this tree. As you can see, in the original tree, we had A < B < C
and that also holds in the new tree. Verify for yourself that the
elements of the subtrees (t1 t2 t3 t4) are okay. For example, you know
that the elements of t2 must all be bigger than A and less than B from
their position in the first tree. Is that the case in the second?
Does that work for the other subtrees?
The rotate-right function does the same thing, but in the other
direction.  Show what a right rotation looks like on this (same) tree:
     B
    / \
   /   \
  A     C
 / \   / \
t1 t2 t3 t4


      A
     / \
    t1   B
        / \
       t2  C
          / \
         t3 t4
Design the rotate-right and rotate-left functions.
|#

(define rotationtest (make-node 2 2
                                (make-node 1 1 "leaf" "leaf")
                                (make-node 3 1 "leaf" "leaf")))

;; rotate-right : [AA-node X] -> [AA-node X]
;; ASSUMPTION: `node` is not "leaf", and `(node-left node)` is not "leaf"


(check-expect (rotate-right rotationtest)
              (make-node 1 2 "leaf"
                         (make-node 2 2 "leaf"
                                    (make-node 3 1 "leaf" "leaf"))))

(check-expect (rotate-right (tree-root six-nodes))
              (make-node 2 3 (make-node 1 2 "leaf" "leaf")
                         (make-node 4 3 (make-node 3 2 "leaf" "leaf")
                                    (make-node 6 2 (make-node 5 1 "leaf" "leaf") (make-node 7 1 "leaf" "leaf")))))
              

(define (rotate-right n)
  (make-node
   (node-value (node-left n))
   (node-level n)
   (adjust-level (node-left (node-left n)))
   (make-node
    (node-value n)
    (node-level n)
    (adjust-level (node-right (node-left n)))
    (node-right n))))

;; adjust-level : [AA-node X] -> [AA-node X]
;; incriments the level of a node by 1
(define (adjust-level n)
  (cond
    [(equal? n "leaf") "leaf"]
    [else (make-node
           (node-value n)
           (+ 1 (node-level n))
           (node-left n)
           (node-right n))]))

;; rotate-left : [AA-node X] -> [AA-node X]
;; ASSUMPTION: `node` is not "leaf", and `(node-right node)` is not "leaf"
(check-expect (rotate-left rotationtest)
                     (make-node 3 3
                                (make-node 2 2 (make-node 1 1 "leaf" "leaf") "leaf") "leaf"))

(check-expect (rotate-left (tree-root six-nodes))
                     (make-node 6 4
                                (make-node 4 3
                                           (make-node 2 2
                                                      (make-node 1 1 "leaf" "leaf") (make-node 3 1 "leaf" "leaf"))
                                           (make-node 5 2 "leaf" "leaf"))
                                (make-node 7 2 "leaf" "leaf")))
                           
                           

(define (rotate-left n)
  (make-node
   (node-value (node-right n))
   (+ 1 (node-level n))
   (make-node
    (node-value n)
    (node-level n)
    (node-left n)
    (adjust-level (node-left (node-right n))))
  (adjust-level (node-right (node-right n)))))


#|
After finishing the rotation functions, we're ready to design split
and skew. Skew is slightly simpler so we start with it: it accepts a
tree and, if the tree is a node and if the left subtree has the same
level as the original tree (which would violate the AA invariant),
then it performs a rotate right.
|#

;; Skew : [AA-tree X] -> [AA-node X]
;; if tree is a node and left subtree has same level as original tree
;; performs rotate right
(define skewtest (make-tree (make-node 5 2 (make-node 4 2 "leaf" "leaf") "leaf") 2 <=))

(check-expect (nlevel (skew (make-tree "leaf" 0 <=))) 0)
(check-expect (skew six-nodes) (tree-root six-nodes))
(check-expect (skew skewtest) (make-node 4 2 "leaf" (make-node 5 2 "leaf" "leaf")))

(define (skew t)
  (cond
    [(equal? (tree-root t) "leaf") (tree-root t)]
    [(equal? (node-level (tree-root t))
             (node-level (node-left (tree-root t))))
     (rotate-right (tree-root t))]
    [else (tree-root t)]))
#|
Split accepts a tree and, if the tree is a node and if the right
subtree is also a node, and the right subtree of the right subtree has
the same level as the tree (which would violate the AA invariant),
then it performs a rotate-left and it increments the level of the
result of the rotation.
(Don't forget: the leaf node counts as having a level 0.)
|#

;; Split : [AA-tree X] -> [AA-node X]
;; if tree is a node and right subtree is also a node and the right subtree of
;; the right subtree has the same level as the tree, performs rotate-left AND
;; increments level of result of rotation
(define splittest (make-tree (make-node 4 1 "leaf" (make-node 5 1 "leaf" (make-node 6 1 "leaf" "leaf"))) 3 <=))

(check-expect (nlevel (split (make-tree "leaf" 0 <=))) 0)
(check-expect (split (make-tree (make-node 1 1 "leaf" "leaf") 1 <=)) (make-node 1 1 "leaf" "leaf"))
(check-expect (split (make-tree (make-node 3 2 "leaf" (make-node 4 1 "leaf" "leaf")) 2 <=)) (make-node 3 2 "leaf" (make-node 4 1 "leaf" "leaf")))
(check-expect (split splittest) (make-node 5 2 (make-node 4 1 "leaf" "leaf") (make-node 6 2 "leaf" "leaf")))

(define (split t)
  (cond
    [(equal? (tree-root t) "leaf") (tree-root t)]
    [(equal? (node-right (tree-root t)) "leaf") (tree-root t)]
    [(equal? (nlevel (tree-root t)) (nlevel (node-right (node-right (tree-root t)))))
     (rotate-left (tree-root t))]
    [else (tree-root t)]))



#|
Finally, we're ready to design insert. For the first step, look at
the pdf slides here:
  http://faculty.ycp.edu/~dbabcock/PastCourses/cs350/lectures/AATrees.pdf
They show a series of trees that you get (and the skews and splits) by
inserting the numbers (in order): 6, 2, 8, 16, 10, and 1. Write each of
those down as test cases (i.e. write them down as [AA-node X]s)
and then finish the design of insert.
Note that when you write test cases, you are not allowed to pass functions
(or structures that have functions inside them) to check-expect. So,
for example, this:
  (check-expect (make-tree "leaf" 0 < =) (make-tree "leaf" 0 < =))
will raise an error. To avoid this problem, write test cases that check
only the root field and size field of your insertion function (by calling
selectors on the result of insert).
|#

(define inserted-nothing
  (make-tree "leaf" 0 <=))
(define inserted-6
  (make-tree (make-node 6 1 "leaf" "leaf") 1 <=))
(define inserted-6-2
  (make-tree (make-node 2 1 "leaf" (make-node 6 1 "leaf" "leaf")) 2 <=))
(define inserted-6-2-8
  (make-tree (make-node 6 2 (make-node 2 1 "leaf" "leaf") (make-node 8 1 "leaf" "leaf")) 3 <=))
(define inserted-6-2-8-16
  (make-tree (make-node 6 2 (make-node 2 1 "leaf" "leaf") (make-node 8 1 "leaf" (make-node 16 1 "leaf" "leaf"))) 4 <=))
(define inserted-6-2-8-16-10
  (make-tree (make-node 6 2 (make-node 2 1 "leaf" "leaf") (make-node 10 2 (make-node 8 1 "leaf" "leaf") (make-node 16 1 "leaf" "leaf"))) 5 <=))
(define inserted-6-2-8-16-10-1
  (make-tree (make-node 6 2 (make-node 1 1 "leaf" (make-node 2 1 "leaf" "leaf")) (make-node 10 2 (make-node 8 1 "leaf" "leaf") (make-node 16 1 "leaf" "leaf"))) 6 <=))
#|
`
(check-expect (tree-root (insert inserted-nothing 6)) (make-node 6 1 "leaf" "leaf"))
(check-expect (tree-size (insert inserted-nothing 6)) 1)

(check-expect (tree-root (insert inserted-6 2)) (make-node 2 1 "leaf" (make-node 6 1 "leaf" "leaf")))
(check-expect (tree-size (insert inserted-6 2)) 2)

(check-expect (tree-root (insert inserted-6-2 8)) (make-node 6 2 (make-node 2 1 "leaf" "leaf") (make-node 8 1 "leaf" "leaf")))
(check-expect (tree-size (insert inserted-6-2 8)) 3)

;;(check-expect (tree-root (insert inserted 6-2-8 16)) 4)
;;(check-expect (tree-size (insert inserted-6-2-8 16)) 4)

(check-expect (tree-root (insert inserted-6-2-8-16 10)) (make-node 6 2 (make-node 2 1 "leaf" "leaf") (make-node 10 2 (make-node 8 1 "leaf" "leaf") (make-node 16 1 "leaf" "leaf"))))
(check-expect (tree-size (insert inserted-6-2-8-16 10)) 5)

;;(check-expect (insert inserted-6-2-8-16 10) inserted-6-2-8-16-10)
;;(check-expect (tree-size (insert inserted-6-2-8-16-10 1)) 6)


;; insert : [AA-tree X] X -> [AA-tree X]
;; inserts `x` into `tree

(define (insert t x)
  (cond
    ;; Case 1: tree is empty
    [(= (tree-size t) 0)
     (make-tree
      (make-node x 1 "leaf" "leaf")
      1 (tree-less-than t))]
    ;; Case 2: x is 'less-than' root of given tree
    [((tree-less than t) x (tree-root t))
     (cond
    |#