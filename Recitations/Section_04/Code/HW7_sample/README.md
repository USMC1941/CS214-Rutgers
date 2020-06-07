# HW7 Sample

1. `hw7_demo_a.c` and `hw7_demo_b.c`

   In `hw7_demo_a.c`, I just create a program to do infinite loop.
   In `hw7_demo_b.c`, I try to accept a pid number from user input and then send `SIGINT` to the process whose pid is the input number.

   You can do:

   ```sh
   $ ./hw7a &
     My pid is 31234

   $ jobs

   $ ./hw7b 31234
   ```

   The first line is to run `hw7a` (which is the infinite loop program) to run in background. & in command line is to tell the shell to run this program in the background.

   You can now run jobs command to see the running process. `hw7a` should be there.

   You can see the pid of `hw7a` is printed out. Then, you run `hw7b` and input the pid of `hw7a` to interrupt `hw7a`. You can see the message that `hw7a` is interrupted.

   You can do jobs again to check if `hw7a` is running or not.

2. `hw7_demo_c.c`
   This is to show you how to send a signal to the program itself with `kill()` system call. This program will print out five dots and then be interrupted by itself. You can try to comment the `kill()` function line to see the difference.

3. To compile for example:

   ```sh
   gcc -o hw7a ./hw7_demo_a.c
   ```
