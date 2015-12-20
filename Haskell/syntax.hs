-- Definitions.
doubleMe x = x + x
doubleUs x y = doubleMe x + doubleMe y

-- If cases are expressions.
doubleSmallNumber x = if x > 100
                        then x
                        else doubleMe x

num1 = [4,1,4,3]
-- ++ operator must walk through entire list on the left.
-- : operator is instantaneous, adds to beginning of list.
num2 = [4,1] ++ [4,3]
num3 = 4:1:4:3:[]

val1 = True
val2 = not False
val3 = "hello" == ['h','e','l','l','o']
val4 = 'h' ==  ['h','e','l','l','o'] !! 0

-- Lists are compared in lexicographical order. Headfirst.
val5 = [3,2,1] > [2,3,1]

-- Some list functions: head, tail, last, init, length, null, reverse, take
-- drop, maximum, minimum, sum, product, elem

-- lists from 1 to 20 inclusive, a to z, every 2nd value, every 3rd value
-- second value is upper limit
num5 = [1..20]
num6 = ['a'..'z']
num7 = [2,4..20]
num8 = [3,6..20]
-- [20..1] doesn't work, must do [20,19..1]

-- First 24 multiples of 13
num9 = take 24 [13,26..]

-- Backtick to have infix syntax
num10 = 24 `take` [13,26..]

-- Some infinite lists producers: cycle, repeat

-- List comprehension
num11 = [x * 2 | x <- [1..10]]
num12 = [x * 2 | x <- [1..10], x * 2 >= 12, x /= 8]

-- Pulling from two lists uses all combinatinos of the lists
num13 = [ x * y | x <- [2, 5, 100], y <- [8, 10, 11]]

length' xs = sum [1 | _ <- xs]

-- Tuples
val6 = 4 == fst (4, 3)
val7 = 3 == snd (4, 3)

-- Function type declaration
removeNonUppercase :: [Char] -> String
removeNonUppercase st = [ c | c <- st, c `elem` ['A'..'Z']]


--Integer class has no bounds, Int does.
--Typeclasses, like traits!
--Define a type constaint
adding :: (Num x) => x -> x -> x
adding x y = x + y
