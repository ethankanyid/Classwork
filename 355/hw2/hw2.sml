PART 1

1. fun a(x,y) = x+2*y;

    this function takes input x and y and adds 2y to x.

2. fun b(x,y) = x+y/2.0;

    this function takes input x and y and adds 1/2y to x

3. fun c(f) = fn y => f(y);

    this function takes a function f and returns the function of f applied to y.

4. fun d(f,x) = f(f(x)));

    has too many parantheses otherwise it wouldve:
        this function returns the function takes a function and an input to that function.
        it returns the value of the functions output inputted into the function

5. fun e(x,y,b) = if b(y) then x else y;

    this function takes a function and two values.
    if b(y) is a valid then x will be returned, otherwise y will.

PART 2

fun sumsquares(n) = if n < 1 then 0 else n * n + sumsquares(n-1);

sumsquares(4);
sumsquares(0);
sumsquares((0 - 1));

fun listdup(e, n) = if n < 1 then [] else e :: listdup(e, n - 1);

listdup("hello", 4);
listdup("test", 0);
listdup("test", 0-1);

fun zip([],[]) =  []
  | zip([],_) = []
  | zip(_,[]) = []
  | zip(x::s, y::p) = (x,y) :: zip(s,p);

zip([1,2,3],[4,5,6,7]);
zip([1,2,3],["a","b","c"]);
zip([],[]);
zip([1,2,3],[]);

fun unzip [] = ([], [])
  | unzip((x,y)::lst) = let
  val (x1, y1) = unzip(lst)
  in (x::x1, y::y1)
  end;

unzip(zip([1,2,3],[4,5,6,7]));
unzip(zip([],[]));
unzip(zip([1,2,3],[]));
unzip(zip([1,2,3],["a","b","c"]));

datatype exp =
  Constant of int
  | Double of exp
  | Add of exp * exp
  | Divide of exp * exp;

fun eval_exp(a) = case a of
  Constant i => i
  | Double e => 2 * eval_exp e
  | Add(e1,e2) => (eval_exp e1) + (eval_exp e2)
  | Divide (e1,e2) => (eval_exp e1) div (eval_exp e2);

eval_exp(Divide(Constant(4),Constant(2)));

eval_exp(Divide(Constant(4),Constant(0)));

fun no_especific_zero_division (Constant _) = true
  | no_especific_zero_division (Double e) = no_especific_zero_division e
  | no_especific_zero_division (Add (e1, e2)) =
      no_especific_zero_division e1 andalso no_especific_zero_division e2
  | no_especific_zero_division (Divide (e1, Constant 0)) = false
  | no_especific_zero_division (Divide (e1, e2)) = no_especific_zero_division e2;

no_especific_zero_division(Divide(Constant 10, Constant 0));

datatype IntTree = LEAF of int | NODE of (IntTree * IntTree);

fun sum (LEAF n) = n
  | sum (NODE (left, right)) = sum left + sum right;

sum (LEAF 3);
sum (NODE (LEAF 2, LEAF 3));
sum (NODE (LEAF 2, NODE (LEAF 1, LEAF 1)));

fun height (LEAF _) = 1
  | height (NODE (left, right)) = 1 + Int.max (height left, height right);

height (LEAF 3);
height (NODE (LEAF 2, LEAF 3));
height (NODE (LEAF 2, NODE (LEAF 1, LEAF 1)));

fun balanced (LEAF _) = true
  | balanced (NODE (left, right)) =
      let
        val left_height = height left
        val right_height = height right
      in
        (abs (left_height - right_height) <= 1) andalso balanced left andalso balanced right
      end;

balanced (LEAF 3);
balanced (NODE (LEAF 2, LEAF 3));
balanced (NODE (LEAF 2, NODE (LEAF 3, NODE (LEAF 1, LEAF 1))));
