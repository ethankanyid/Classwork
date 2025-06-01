;Write a function intmax which takes a number pair and returns the greater of its two.
(defun intmax (x y)
  (cond
  ((> x y) x)
  ((< x y) y)
  ((equal x y) nil)
  )
)

;Define a function dup which takes a single element of any type
;and returns a tuple with the element duplicated.
(defun dup (x)
  (list x x)
)

;Define a recursive function to add up all the integers from 1 to a given upper limit
(defun add2lim (x)
  (cond
  ((< x 0) nil)
  ((equal x 1) 1)
  (t (+ x (add2lim (- x 1))))
  )
)

;Write a function, backwards, to returns a list
;with a reversed order list of the elements.
;The function is a simple version of the problem where only
;work on the elements of the list and not of any sublists!
(defun backwards (x)
  (cond
  ((equal (cdr x) nil) (list (car x)))
  (t (append (backwards (cdr x)) (list (car x))))
  )
)

;Write a function, totalbackwards, to returns a list
;with a reversed order list of the elements.
;In this version of the problem is necessary
;reverser the elements of the list and the sublists.
(defun totalbackwards (x)
  (cond
  ((equal (atom x) t)  x)
  ((equal (cdr x) nil) (list (totalbackwards (car x))))
  (t (append (totalbackwards (cdr x)) (list (totalbackwards (car x)))))
  )
)
;Write a function, palindrome, that takes a list as input
;and returns T if the list is a palindrome
(defun palindrome (x)
  (cond
  ((equal (totalbackwards x) x) T)
  (t nil)
  )
)

;; TESTING CASES ;;

(print "(intmax 12 4)")
(print (intmax 12 4))
;expected 12

(print "(intmax 12 12)")
(print (intmax 12 12))
;expected nil

(print "(intmax 5 13)")
(print (intmax 5 13))
;expected 13

(print "(dup 12)")
(print (dup 12))
;expected 12 12

(print "(add2lim 5)")
(print (add2lim 5))
;expected 15

(print "(add2lim -1)")
(print (add2lim -1))
;expected nil

(print  "(backwards (quote (a b c h i)))")
(print  (backwards (quote (a b c h i))))
;(print "(I H C B A)") ;(expected)

(print  "(backwards (quote ()))")
(print  (backwards (quote ())))
;(print "NIL") ;(expected)

(print "(totalbackwards (quote (a (b c) ((l k (t)) h i))))")
(print (totalbackwards (quote (a (b c) ((l k (t)) h i)))))
;(print "((I H ((T) K L)) (C B) A)") ;(expected)

(print "(totalbackwards (quote ()))")
(print  (totalbackwards (quote ())))
;(print "NIL") ;(expected)

(print "(palindrome (quote (r o t o r)))")
(print (palindrome (quote (r o t o r))))
;expected T

(print "(palindrome (quote (m a m a)))")
(print (palindrome (quote (m a m a))))
;expected nil

(print "(palindrome (quote (a)))")
(print (palindrome (quote (a))))
;expected T

(print "(palindrome (quote ()))")
(print (palindrome (quote ())))
;expected T


;which one is the correct or more appropriate set of test cases?
;There are possible defects that would not be detected by this set of four test cases?
; - it depends on what the application is doing to know how many test cases you need.
;   in the case of integers, you often have to test three cases:
;   negatives, 0, and postive numbers.
;   if you are testing strings, you may want to test the
;   null string, 1 char, and a full string.
; - there are definitely some applications that need many tests though
;   especially when provided with user input.
