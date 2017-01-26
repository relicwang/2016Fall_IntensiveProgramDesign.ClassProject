;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-reader.ss" "lang")((modname functions-haridu) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))

#|
The City of Chicago regulates taxi fares, setting two kinds of rates:
there are meter fares for most pickups, and flat-rate fares for known
distances such as rides from hotels to the airport. The meter rates
are set as follows: The base fare for any ride is $3.05, and it costs
$1.80 per mile of travel.

How much does a 0.5 mi. ride cost? How about 1 mi.? 2 mi.?

Make a table that shows the fare for distances of 0.5  mi., 1 mi, 1.5
mi, 2 mi., 2.5 mi., 3 mi.

Create a formula for calculating fares from trip distances.

Use the formula to design a function that computes a taxi fare given
the distance traveled.
|#

#|

distance   |   fare
___________|____________________
0.5m       | 3.95
1mi        | 4.85
1.5mi      | 5.75
2mi        | 6.65
2.5mi      | 7.55
3mi        | 8.45


Formula:
fare = 3.05 + (1.80 * miles)

Data:
numbers

Signature, purpose, and header

taxi-fare: Number -> Number
calculates the fare depending on the distance traveled
(define (taxi-fare distance)... )

Examples:

(taxi-fare 1) should be 4.85
(taxi-fare 2.5) should be 7.55
(taxi-fare 3) should be 8.45

|#

; Body:

(define (taxi-fare miles)
  (+ 3.05 (* 1.80 miles))
)

; Tests:

(check-expect (taxi-fare 1) 4.85)
(check-expect (taxi-fare 2.5) 7.55)
(check-expect (taxi-fare 3) 8.45)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

#|
To supplement my meager teaching income, I shovel snow for some of my
neighbors. For shoveling a sidewalk and driveway, I charge each
neighbor $10 per job plus $5 per inch of snowfall to be shoveled.

How much do I get paid if I shovel for one neighbor after a storm that
drops 1 inch of snow? What if 4 neighbors hire me after a blizzard
puts down 14 inches?

Make a table that shows my income in terms of both inches of snow and
the number of neighbors that hire me. (The table should have at least
9 values.)

Create a formula for calculating how much I earn if I shovel d inches
of snow for each of n neighbors.

Use the formula to design a function that computes my snow shoveling
income given both the number of inches and number of neighbors.
|#

#|

inches of snow  | number of neighbors  |  income
________________|______________________|_____________
1               |          1           |   15
2               |          3           |   60
3               |          6           |  150
4               |          5           |  150
5               |          3           |  105
6               |          7           |  280
7               |         10           |  450
8               |          3           |  150
9               |          5           |  275
14              |          4           |  320

Formula:

income = n*(10 + (d*5))

Data:
number

Signature, purpose, and header:

income: Number Number -> Number
determine the income based on the inches of snowfall and the number of neghbors
(define (income d n)...)

Examples:

(income 1 1) should be 15
(income 14 4) should be 320
(income 9 5) should be 275

|#

; Body:

(define (income d n)
  (* n (+ 10 (* d 5)))
)

;Tests:

(check-expect (income 1 1) 15)
(check-expect (income 14 4) 320)
(check-expect (income 9 5) 275)
