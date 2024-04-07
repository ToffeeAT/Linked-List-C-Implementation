gcc -Wall -Werror mtll.c main.c -o program

function run_test() {
    local input=$1
    local expected_output=$2

    # Run the program with input and capture the output
    actual_output=$(echo "$input" | ./program)

    # Compare the actual output with expected output
    if [ "$actual_output" == "$expected_output" ]; then
        echo "Test Passed!"
    else
        echo "Test Failed!"
        echo "Expected Output:"
        echo "$expected_output"
        echo "Actual Output:"
        echo "$actual_output"
    fi
}

# Test Case 1: New function of 4 different types and viewing
input1="NEW 4
i
love
3.14
9
VIEW 0
TYPE 0"
expected_output1="List 0: i -> love -> 3.14 -> 9
i -> love -> 3.14 -> 9
char -> string -> float -> int"
run_test "$input1" "$expected_output1"

# Test Case 2: View all function
input2="NEW 3
a
b
c
VIEW ALL"
expected_output2="List 0: a -> b -> c
Number of lists: 1
List 0"
run_test "$input2" "$expected_output2"

# Test Case 3: Removing a list after making it
input3="NEW 3
a
b
c
REMOVE 0"
expected_output3="List 0: a -> b -> c
List 0 has been removed.

Number of lists: 0"
run_test "$input3" "$expected_output3"


# Test Case 4: Invalid Commands
input4="REMOVE 0
REMOVE 1
REMOVE 0
NEW -3
VIEW 4
TYPE 8
VIEW ALL"
expected_output4="INVALID COMMAND: REMOVE
INVALID COMMAND: REMOVE
INVALID COMMAND: REMOVE
INVALID COMMAND: NEW
INVALID COMMAND: VIEW
INVALID COMMAND: TYPE
Number of lists: 0"
run_test "$input4" "$expected_output4"

# Test Case 5: HUGE LIST EDGE
input5="NEW 30
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30"
expected_output5="List 0: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> 11 -> 12 -> 13 -> 14 -> 15 -> 16 -> 17 -> 18 -> 19 -> 20 -> 21 -> 22 -> 23 -> 24 -> 25 -> 26 -> 27 -> 28 -> 29 -> 30"
run_test "$input5" "$expected_output5"


# Test Case 6: Inserting multiple nodes ALOT EDGE
input6="NEW 2
a
z
INSERT 0 1 b
INSERT 0 -2 y
INSERT 0 2 c
INSERT 0 -3 x
INSERT 0 3 c
INSERT 0 -4 w
INSERT 0 4 d
INSERT 0 -5 v
INSERT 0 5 e
INSERT 0 -6 u
INSERT 0 6 f
INSERT 0 -7 t
INSERT 0 7 g
INSERT 0 -8 s
INSERT 0 8 h
INSERT 0 -9 r
INSERT 0 9 i
INSERT 0 -10 q
INSERT 0 10 j
INSERT 0 -11 p
INSERT 0 11 k
INSERT 0 -12 o
INSERT 0 12 l
INSERT 0 -13 n
INSERT 0 13 m
INSERT 0 -14 z"
expected_output6="List 0: a -> z
List 0: a -> b -> z
List 0: a -> b -> y -> z
List 0: a -> b -> c -> y -> z
List 0: a -> b -> c -> x -> y -> z
List 0: a -> b -> c -> c -> x -> y -> z
List 0: a -> b -> c -> c -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> r -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> i -> r -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> i -> q -> r -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> i -> j -> q -> r -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> i -> j -> p -> q -> r -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> i -> j -> k -> p -> q -> r -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> i -> j -> k -> o -> p -> q -> r -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> i -> j -> k -> l -> o -> p -> q -> r -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> i -> j -> k -> l -> n -> o -> p -> q -> r -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> i -> j -> k -> l -> m -> n -> o -> p -> q -> r -> s -> t -> u -> v -> w -> x -> y -> z
List 0: a -> b -> c -> c -> d -> e -> f -> g -> h -> i -> j -> k -> l -> m -> z -> n -> o -> p -> q -> r -> s -> t -> u -> v -> w -> x -> y -> z"

run_test "$input6" "$expected_output6"


# Test Case 7: DELETE EDGE try deleting a node that doesnt exist
input7="NEW 3
a
b
c
REMOVE 0
DELETE 0 1"
expected_output7="List 0: a -> b -> c
List 0 has been removed.

Number of lists: 0
INVALID COMMAND: INPUT"
run_test "$input7" "$expected_output7"
