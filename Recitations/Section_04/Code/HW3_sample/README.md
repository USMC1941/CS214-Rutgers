# HW3 Sample

In the [HW3_sample.c](HW3_sample.c), there are 4 different experiments. You can remove the comment from the experiment you want to do and comment the rest. For experiment 1 and 2, you do not need to provide any input. For experiment 3 and 4, you need to provide input as follow:
e.g.

```sh
./sample "Original text" "text" "string" # (experiment 3)
```

That means your original string is "Original text" and you want to replace "text" with "string".

To compile the program, please do:

```sh
gcc -o test HW3_sample.c -g -std=c99
```

Then run:

```sh
./test # (experiment 1 or 2)
```

or

```sh
./test "string from" "from" "to" # (experiment 3)
```

or

```sh
./test "first string " "second string" # (experiment 4)
```
