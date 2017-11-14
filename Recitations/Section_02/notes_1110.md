### exerceise
   Write a function that uses threads to synchronize printing between them to print out a triangle.
 
  Make two threads, one to print out even rows, one to print out odd. The goal is to print out:

```
*
**
***
****
*****
******
```
.. where each line is printed by a different thread. Have thread 0 print out the even lines (2 stars, 4 stars, etc) and thread 1 print out the odd ones (1 star, 3 stars, etc).
 
  At first, just run them with no synchronization. You'll get an interleaving of rows ... likely you'll get a batch of rows and then another batch of rows.
 
  Next add a pair of mutexex to trade off control between the threads. They should trade off using the mutexes to synchronize between them.
 
  Sometimes thread 0 may be scheduled before thread 1 and you get the rows printed in the wrong order. You need to make sure the first thread gets the mutex first - but you can't, really since you do not have control of the scheduler.
 
  Change the mutex in to a binary semaphore. This way if the wrong thread starts first, it will block until the other thread gets to run.
 
  Thread 1 ought to notify/produce and thread 0 ought to wait/consume. This way you can trade control in an intentional manner.

### threads 

one sentences defination
POSIX threads -> pthread.

same with process:
aims to perform tasks concurrently
diff with process:
  
  - single process could contain multiple threads.
  - for the memory management(29-1) share which space, isolate which space.
  - threads are executed concurrently, if one thread is blocked on I/O, others threads are still eligible to execute

multiprocess vs multithread

  - it is difficult to share information between processes. since parent and child don't share memory(other than read-only text segment), we need to use some inter process communication mechanism to change info between process. For thread model, sharing infomation is easy, just need to copy data into shared space(heap or global), which also lead to another problem (multiple threads try to update the same information we use synchroniztion to solve it 30)

  - fork() call is time consuming compared with thread creating. thread creation is ten times faster or better because many attributes in fork is shared by thread model

thread share what info?
29.1

other remarks
each thread has their own errno to represent the error state of each thread.

how to represent a thread?

how to create thread?
when a program is started, there is thread called initial or main thread, [example](https://github.com/angrave/SystemProgramming/wiki/Pthreads%2C-Part-1%3A-Introduction)，attention to the defination of the four parameters in function(how to pointer to a function)

wait thread to be end?
pthread_join
Allows the calling thread to wait for the ending of the target thread.
refer to 

https://www.ibm.com/support/knowledgecenter/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/ptjoin.htm(the second parameter is pointing to the return value of the ending thread) 

why use pthread_join?

  - Wait for a thread to finish
  - Clean up thread resources
  - Grabs the return value of the thread

how to terminate a thread?
  
  - in the logic of thread, return instruction
  - thread call pthread_exit()
  - thread call pthread_cancel()
  - any of the thread call exit() (this will cause the termination of the process) or the main thread perform return (in the main function), **which will cause all threads terminated immediately**.  

user state threads 

### process vs threads

### race condition

### thread_safety


## Synchronization

the concepts of threads -> execute in concurency -> shared partial memory -> cost, synchronization

#### how to analyse the data inconsistance
divide all the read and write oeprations into the three step (get value, operaion, writevalue) arrange them in different order.

#### transfer into thread safe section
figure out the critical section(one thread for those instructions at one time), for same shared memory space, using same semaphore, for different shared memory space, using different mutex lock.

refer to 
https://github.com/angrave/SystemProgramming/wiki/Synchronization%2C-Part-3%3A-Working-with-Mutexes-And-Semaphores

tricky:
you can't assume the behavior of instructions for multithread operation.

version1
use lock to protect the data, not the operation, same data access, same mutex lock.

version2
using same lock, but (1) result may out of date (2) no protection for underflow(poping on empty stack, pushing into a full stack)

version3 
put mutex as a part of the memory struct and use pthread_mutex_init to initialize it

version4
force threads to wait if the stack is empty or full, counting semaphores

semaphore plus mutex lock
the semaphore using is a little hard to analyse, try to keep in mind some classical cases


### mutex lock

use lock without unlock

use unlock without lock

### mutual exclusive

### exclusive lock

### dead lock

### mutex lock


### semaphores
more flexible problem, like we had a shared variable where we wanted any number of threads to read
the variable, but only one thread to write it.

counting semaphore

https://github.com/angrave/SystemProgramming/wiki/Synchronization%2C-Part-2%3A-Counting-Semaphores

binary semaohore

http://www.cs.umd.edu/~shankar/412-Notes/10-BinarySemaphores.html

classical semophre problem
http://perugini.cps.udayton.edu/teaching/courses/cps346/lecture_notes/classical.html

### semaphore vs pthread mutex
53.5
same:
both of them could be used to synchronize the actions of threads within same process, performance is similar.
diff:
semaphore is more flexible(increas in one thread, decrease in other thread), but it could casued to less structured synchronizartion design

mutex is more preferable.(both lock and unlock operation will be in same thread)  

binary siganal with semaphore（refer to http://www.geeksforgeeks.org/mutex-vs-semaphore/）

There is an ambiguity between binary semaphore and mutex. We might have come across that a mutex is binary semaphore. But they are not! The purpose of mutex and semaphore are different. May be, due to similarity in their implementation a mutex would be referred as binary semaphore.

Strictly speaking, a mutex is **locking mechanism** used to synchronize access to a resource. Only one task (can be a thread or process based on OS abstraction) can acquire the mutex. It means there is ownership associated with mutex, and only the owner can release the lock (mutex).

Semaphore is **signaling mechanism (“I am done, you can carry on” kind of signal).** For example, if you are listening songs (assume it as one task) on your mobile and at the same time your friend calls you, an interrupt is triggered upon which an interrupt service routine (ISR) signals the call processing task to wakeup.


### condition variables

condition variable vs semaphore
If all of your threads are waiting for some event, e.g., submission of a task, then you can wake them all up by using a condition variable upon an event.

If you have a limited resource, say 10 pages of memory reserved for your threads, then you will need them to wait until a page is available. When this happens, you will need to let just one thread start execution. In this case you can use a semaphore unlock up as many threads as available pages.


### spurious wakeup
It is recommended that all threads check the condition after returning from pthread_cond_wait because there are several reasons the condition might not be true. One of these reasons is a spurious wakeup; that is, a thread might get woken up even though no thread signalled the condition.

For performance. On multi-CPU systems it is possible that a race-condition could cause a wake-up (signal) request to be unnoticed. The kernel may not detect this lost wake-up call but can detect when it might occur. To avoid the potential lost signal the thread is woken up so that the program code can test the condition again.
(https://github.com/angrave/SystemProgramming/wiki/Synchronization%2C-Part-5%3A-Condition-Variables)


### why need mutex for wait

http://cs241.cs.illinois.edu/wikibook/synchronization-part-5-condition-variables.html

https://stackoverflow.com/questions/16522858/understanding-of-pthread-cond-wait-and-pthread-cond-signal

### refer to 

https://github.com/angrave/SystemProgramming/wiki

https://github.com/angrave/SystemProgramming/wiki/Synchronization%2C-Part-3%3A-Working-with-Mutexes-And-Semaphores (thread safe stack)

https://github.com/angrave/SystemProgramming/wiki

https://cs61.seas.harvard.edu/wiki/images/1/12/Lec19-Semaphores.pdf

