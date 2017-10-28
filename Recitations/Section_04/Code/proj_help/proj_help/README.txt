------------------ DESCRIPTION ----------------------
1.
To compile:
   gcc -o proj1 ./proj1_sample.c -std=gnu99

2. 
Please check the pipe_sample.c file first. I just merge that code with hw5_sample.c to make this one works. Most of the explanations are already given in the .c file as comments. Here is to give you a layout of the project:

Once there is a file, you do fork. This pair of processes (child and parent processes) only handle one file. Once the child process is done, the parent process will report its child's pid to its parent:

eg. A --create--> B --create--> C (sorting file)
	A <--pid_c--- B <-Nothing-- C (done)

So we can see, the pair of processes for a file only need to send one pid to the parent.

Once there is a directory, you do fork. This pair of processes do differnt things: child process will process everything under given directory (new directories under current directory or files). This child process may create other child process if there is a new directory under current dir.

Parent process just wait for the child process to be done. If the child process is done, that means everything under current directory are already processed correctly. This time parent process will receive a message from its child process. This message may contains all the pids that it created when processing current directory. Parent process need to append its child process pid and then send this message to its parent.

Here I draw pictures to show why I must use break at the end of the child process part instead of using exit(0) directly.

EXAMPLE:
Here is a directory layout

./ --> dir1 | file1 | file2
         |
		 --> dir2 | file3
		      |
			  --> file 4

Step 1:
The first target is a directory dir1, do fork:
This time we get child p0'. The same as p0.

  p0         p0'
  ---       ---
 |   |     |   |
 |   |     |   |
 |   |     |   |
  ---       ---

step 2:
Since this is a directory, we recursively call function. So we go one level down. This time we are under dir1. Then we find that the first target under dir1 is another directory dir2. So we fork to get p0'' to handl this directory.

             p0'        p0''
            ---         ---
		   |   |       |   |
           |  -|-      |  -|-
		   | |   |     | |   |
		    --   |      --   |
			 |   |       |   |
			  ---         ---

step 3:
p0'' is processing dir2, we need to go one level down to enter dir2. Now we are under dir2. Then we find the target is a file. We do fork, to get p0'''.

						p0''        p0'''
		               ---         ---
         		      |   |       |   |
		              |  -|-      |  -|-
			          | |   |     | |   |
			           --  -|-     --  -|-
				        | |   |     | |   |
				         --   |      --   | 
						  |	  |	      |   |
						   ---         ---

step 4: 
Since p0''' copied the stack structure of p0'', once the file processing is done, p0''' need to return to previous function call. Then p0''' terminate and p0'' will send message to p0'.

		        p0''        p0'''         p0'''       p0'''
               ---         ---            ---          
   		      |   |       |   |          |   |
              |  -|-      |  -|-         |  -|-        ---
	          | |   |     | |   |        | |   |      |   |
	           --  -|-     --  -|-   -->  --   |  --> |   | 
		        | |   |     | |   |        |   |      |   |
		         --   |      --   |         ---        ---
				  |	  |	      |   |
				   ---         ---

Here you can see the reason why I say we cannot use exit(0) at the end of the child process part. We must use break to allow the p0''' to return to the first level and free all the allocated memories to avoid memory leak.


