# CS214 Final Study Guide

These are suggested readings to reinforce material covered in lecture. I recommend doing a little reading every day.


## Computer Systems: A Programmer's Perspective (3rd Edition)

### Chapter 8 - Exceptional Control Flow 721

#### 8.2 Processes 732

8.2.1 Logical Control Flow 732

8.2.2 Concurrent Flows 733

8.2.3 Private Address Space 734

8.2.4 User and Kernel Modes 734

8.2.5 Context Switches 736

#### 8.3 System Call Error Handling 737

#### 8.4 Process Control 738

8.4.1 Obtaining Process IDs 739

8.4.2 Creating and Terminating Processes 739

8.4.3 Reaping Child Processes 743

8.4.4 Putting Processes to Sleep 749

8.4.5 Loading and Running Programs 750

8.4.6 Using fork and execve to Run Programs 753

#### 8.5 Signals 756

8.5.1 Signal Terminology 758

8.5.2 Sending Signals 759

8.5.3 Receiving Signals 762

8.5.4 Blocking and Unblocking Signals 764

8.5.5 Writing Signal Handlers 766

8.5.6 Synchronizing Flows to Avoid Nasty Concurrency Bugs 776

8.5.7 Explicitly Waiting for Signals 778

___

### Chapter 10 - System-Level I/O 889

#### 10.1 Unix I/O 890

#### 10.2 Files 891

#### 10.3 Opening and Closing Files 893

#### 10.4 Reading and Writing Files 895

#### 10.6 Reading File Metadata 903

#### 10.7 Reading Directory Contents 905

#### 10.8 Sharing Files 906

#### 10.9 I/O Redirection 909

#### 10.10 Standard I/O 911

#### 10.11 Putting It Together: Which I/O Functions Should I Use? 911

___


### Chapter 11 - Network Programming    917

#### 11.1 The Client-Server Programming Model    918

#### 11.2  Networks    919

#### 11.3    The Global IP Internet    924

11.3.1   IP Addresses    925

11.3.2   Internet Domain Names    927

11.3.3   Internet Connections    929

#### 11.4     The Sockets Interface    932

11.4.1   Socket Address Structures    933

11.4.2   The socket Function    934

11.4.3   The connect Function    934

11.4.4   The bind Function    935

11.4.5   The listen Function    935

11.4.6   The accept Function    936

11.4.7   Host and Service Conversion    937

11.4.8   Helper Functions for the Sockets Interface    942

11.4.9   Example Echo Client and Server    944

___


### Chapter 12 - Concurrent Programming    971

#### 12.1 Concurrent Programming with Processes    973

12.1.1   A Concurrent Server Based on Processes    974

12.1.2   Pros and Cons of Processes    975

#### 12.2 Concurrent Programming with I/O Multiplexing    977

12.2.1   A  Concurrent  Event-Driven  Server  Based  on  I/O Multiplexing    980

12.2.2   Pros and Cons of I/O Multiplexing    985

#### 12.3 Concurrent Programming with Threads    985

12.3.1   Thread Execution Model    986

12.3.2   Posix Threads    987

12.3.3   Creating Threads    988

12.3.4   Terminating Threads    988

12.3.5   Reaping Terminated Threads    989

12.3.6   Detaching Threads    989

12.3.7   Initializing Threads    990

12.3.8   A Concurrent Server Based on Threads    991

#### 12.4    Shared Variables in Threaded Programs    992

12.4.1   Threads Memory Model    993

12.4.2   Mapping Variables to Memory    994

12.4.3   Shared Variables    995

#### 12.5    Synchronizing Threads with Semaphores    995

12.5.2   Semaphores    1001

12.5.3   Using Semaphores for Mutual Exclusion    1002

12.5.4   Using Semaphores to Schedule Shared Resources    1004

12.5.5   Putting It Together: A Concurrent Server Based on Prethreading    1008

#### 12.6     Using Threads for Parallelism    1013

#### 12.7     Other Concurrency Issues    1020

12.7.1   Thread Safety    1020

12.7.2   Reentrancy    1023

12.7.3   Using Existing Library Functions in Threaded Programs    1024

12.7.4   Races    1025

12.7.5   Deadlocks    1027



