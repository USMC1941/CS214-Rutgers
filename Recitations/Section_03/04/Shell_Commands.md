# Shell Commands

- [Shell Commands](#shell-commands)
  - [Launch Matlab](#launch-matlab)
  - [Operate file in usr/lib](#operate-file-in-usrlib)
  - [More shell commands](#more-shell-commands)
    - [cd](#cd)
    - [ls](#ls)
    - [cp](#cp)
      - [cp Examples](#cp-examples)
    - [mv](#mv)
      - [mv Example](#mv-example)
    - [nano](#nano)
        - [nano Example](#nano-example)
    - [mkdir](#mkdir)
      - [mkdir Example](#mkdir-example)
    - [ps](#ps)
    - [kill / killall / xkill](#kill--killall--xkill)
      - [kill Example](#kill-example)
    - [| (Pipe)](#-pipe)
      - [Pipe Example](#pipe-example)
    - [Redirection: > and >>](#redirection--and-)
    - [tee](#tee)
    - [pwd](#pwd)
      - [pwd Example](#pwd-example)
    - [df -h](#df--h)
    - [du](#du)
      - [du Example](#du-example)
    - [Run Python program](#run-python-program)
    - [Execute a shell file](#execute-a-shell-file)

## Launch Matlab

```sh
cd /usr/local/MATLAB/R2016b/bin

./matlab -softwareopengl
./matlab -r "opengl info"
./matlab
```

## Operate file in usr/lib

```sh
gksudo nautilus
```

Reference: [The 5-Minute Essential Shell Tutorial](http://community.linuxmint.com/tutorial/view/100)

## More shell commands

### cd

Move backward

```sh
cd .. # <==> cd ../
cd ../../
```

Move forward

```
cd foldername/
```

Move into a specific folder

```sh
cd /some/other/path
```

### ls

```sh
ls -hl
```

-  `h` means showing file sizes in human readable format (K, M, Gbyte) instead of bytes
-  `l` means providing a longer listing format including permissions, owners, sizes and data modified

```sh
ls foldername/ -hl
ls ../ -hl
ls /some/other/path -hl
```

### cp

Copies specified file to the given path.

```sh
cp file /path/to/folder
```

Copies recursively the contents of the folder (everything in the folder and everything in the subfolders underneath that folder) to another folder.

```sh
cp -r folder /path/to/folder
```

Copies files matching the given extension to the new folder. To copy all `.doc` files, it becomes `cp *.doc /path/to/folder` and the folder must exist.

```sh
cp *.extension /path/to/folder
```

Copies all files starting with `'name'` to the given folder. To copy all files starting with `example`, it becomes `cp example* /path/to/folder` and the folder must exist.

```sh
cp name* /path/to/folder
```

#### cp Examples

```sh
bash-4.1$ cd /ilab/users/gq19/Documents/TA
bash-4.1$ cp STUDENT_LIST ../Unix/
bash-4.1$ ls ../Unix/ -hl
total 12K
-rw------- 1 gq19 allusers 659 Nov 21 23:04 new file~
-rw------- 1 gq19 allusers 659 Nov 21 23:06 shell_commands
-rw------- 1 gq19 allusers 108 Nov 22 21:43 STUDENT_LIST
bash-4.1$ cd /ilab/users/gq19/Documents/TA
bash-4.1$ cp -r  Assignment3 ../Unix/
bash-4.1$ ls -hl ../Unix/
total 20K
drwx------ 4 gq19 allusers 4.0K Nov 22 21:53 Assignment3
-rw------- 1 gq19 allusers  659 Nov 21 23:04 new file~
-rw------- 1 gq19 allusers 1.7K Nov 22 21:52 shell_commands
-rw------- 1 gq19 allusers 1.7K Nov 22 21:50 shell_commands~
-rw------- 1 gq19 allusers  108 Nov 22 21:43 STUDENT_LIST
bash-4.1$ cd /ilab/users/gq19/Documents/TA
bash-4.1$ cp  *.c  ../Unix/
bash-4.1$ ls -hl ../Unix/
total 28K
drwx------ 4 gq19 allusers 4.0K Nov 22 21:53 Assignment3
-rw------- 1 gq19 allusers  659 Nov 21 23:04 new file~
-rw------- 1 gq19 allusers 7.0K Nov 22 21:57 pa3_ta_test.c
-rw------- 1 gq19 allusers 2.1K Nov 22 21:54 shell_commands
-rw------- 1 gq19 allusers 1.7K Nov 22 21:52 shell_commands~
-rw------- 1 gq19 allusers  108 Nov 22 21:43 STUDENT_LIST
bash-4.1$ cd /ilab/users/gq19/Documents/TA
bash-4.1$ cp Example*  ../Unix/
bash-4.1$ ls -hl ../Unix/
total 40K
drwx------ 4 gq19 allusers 4.0K Nov 22 21:53 Assignment3
-rw------- 1 gq19 allusers  108 Nov 22 21:59 Example1
-rw------- 1 gq19 allusers  108 Nov 22 21:59 Example2
-rw------- 1 gq19 allusers  108 Nov 22 21:59 Example3
-rw------- 1 gq19 allusers  659 Nov 21 23:04 new file~
-rw------- 1 gq19 allusers 7.0K Nov 22 21:57 pa3_ta_test.c
-rw------- 1 gq19 allusers 2.6K Nov 22 21:57 shell_commands
-rw------- 1 gq19 allusers 2.1K Nov 22 21:54 shell_commands~
-rw------- 1 gq19 allusers  108 Nov 22 21:43 STUDENT_LIST
```

### mv

Moves specified file to the given folder.

```sh
mv file /path/to/folder
```

Moves the contents of the folder, including everything in the subfolders, to another folder.

```sh
mv folder /path/to/folder
```

Moves files matching the given extension to the given folder.

```sh
mv *.extension /path/to/folder
```

Moves all files starting with 'name' to the given folder.

```sh
mv name* /path/to/folder
```

#### mv Example

```sh
bash-4.1$ cd /ilab/users/gq19/Documents/Unix
bash-4.1$ mv pa3_ta_test.c New/
bash-4.1$ mv Assignment3  New/
bash-4.1$ mv *.pdf New/
bash-4.1$ mv Example*  New/
bash-4.1$ mv STUDENT_LIST  New/
```

### nano

A full command line text editor in terminal. It can handle plain text files.

Creates a new file

```sh
nano  newfile.whatever
```

Opens an existing file

```sh
nano  existingfile.whatever
```

Saves file by pressing enter

```
CTRL + o
```

Exits nano

```
CTRL + x
```

##### nano Example

```sh
bash-4.1$ cd /ilab/users/gq19/Documents/Unix/New
bash-4.1$ nano NewProgrammingFile.cpp
bash-4.1$ nano NewProgrammingFile.cpp
```

### mkdir

Create directories (i.e., create folders)

Creates a folder with the specified name.

```sh
mkdir foldername
```

Creates each folder as necessary. `-p` will make both 1st and 2nd folder

```sh
mkdir -p foldername1/foldername2
```

#### mkdir Example

```sh
bash-4.1$ cd /ilab/users/gq19/Documents/Unix/New
bash-4.1$ mkdir gang
bash-4.1$ mkdir -p qiao/gang
```

### ps

List all processes in detail running on the system, including user, Process ID (PID), and name of process.

Using this, one can view their process list and if necessary, kill unnecessary or stalled processes.

```sh
bash-4.1$ ps aux
USER     PID   %CPU  %MEM    VSZ   RSS  TTY   STAT  START   TIME COMMAND
root       1    0.0  0.0  23600  1604    ?     Ss   Oct22   0:18 /sbin/init
root       2    0.0  0.0      0     0    ?     S    Oct22   0:00 [kthreadd]
root       3    0.0  0.0      0     0    ?     S    Oct22   0:00 [migration/0]
...       ...   ...  ...    ...   ...  ...    ...   ...     ...     ...
root     26229  0.0  0.0      0     0    ?     S<   Oct22   0:00 [kslowd000]
root     26230  0.0  0.0      0     0    ?     S<   Oct22   0:00 [kslowd001]
root     26231  0.0  0.0      0     0    ?     S    Oct22   0:06 [nfsiod]
gq19     26918  0.0  0.0 270280  7524    ?     S    Nov23   0:00 kdeinit4: kio_f
root     28714  0.0  0.0 115368  1220    ?     Ss   Nov11   0:02 crond
gq19     31300  0.0  0.0 267284  6080    ?     Ss   Nov21   0:00 kdeinit4: kdein
gq19     31301  0.0  0.0 270896  8252    ?     S    Nov21   0:01 kdeinit4: klaun
gq19     31303  0.0  0.0 354380 14444    ?     S    Nov21   0:03 kdeinit4: kded4
gq19     31305  0.0  0.0  11960  1236    ?     S    Nov21   0:00 /usr/libexec/ga
yn85     31966  0.4  0.4 145628 75000    ?     Sl   12:46   0:30 /usr/local/Adob
```

### kill / killall / xkill

Kill offending processes

Typing in `xkill` should present a skull-and-crossbones icon and the next window clicked on will be killed.

One should obtain the PID of a process from a command like ps aux. If a process refuses to die, one can alternatively specify `kill -9 PID` which should terminate the process by any means, even uncleanly or if it will mess up the system.

Kills a specific process whose ID is PID

```sh
kill PID
```

If there are for example 3 firefox sessions open, `killall firefox` will just kill all firefox sessions, while `kill PID` would simply take the specified PID of the offending firefox process you wish to kill, and kill that one only.

Kills all instances of said program.

```sh
(4) killall program
```

#### kill Example

Launch Matlab and firefox

```sh
bash-4.1$ xkill
Select the window whose client you wish to kill with button 1....
xkill:  killing creator of resource 0x380003e

bash-4.1$ killall firefox
```

### | (Pipe)

`'|'` is called a pipe. It passes the output of a command which is on the left of the pipe to another command (not to a file) which is on the right of the pipe

#### Pipe Example

Use the ps command to get a list of processes running on the system, and pass the list to the command `grep` to search for lines containing "matlab". (Usually, it'll find two: the matlab, and the process executing `grep matlab`.)

```sh
bash-4.1$ ps aux | grep matlab
gq19     22375 11.6  2.4 3981624 404464 ?      Sl   14:42   0:15 /.autofs/system/koko_system/matlab2013a/bin/glnxa64/MATLAB -desktop
gq19     23215  0.0  0.0 103304   912 pts/0    S+   14:44   0:00 grep matlab
bash-4.1$ kill 22375
```

In this example, at the first shell prompt, I show the contents of the file `apple.txt` to you. In the next shell prompt, I use the `cat` command to display the contents of the `apple.txt` file, but I send the display not to the screen, but through a pipe to the `wc` (word count) command. The `wc` command then does its job and counts the lines, words, and characters of what it got as input.

```sh
bash-4.1$ cd /ilab/users/gq19/Documents/Unix/New
bash-4.1$ cat apple.txt
core
worm seed
jewel
bash-4.1$ cat apple.txt | wc
      3       4      21       # number of lines, number of words, number of characters
```

### Redirection: > and >>

Send the output of a command to a file instead of the terminal.

`>` is used to either create a new file (if the file does't exist) and send the output of the command to this file, or _overwrite_ the content of a file (if exists) by replacing its content with the output of the command.

`>>` is used to _append_ information to the currently existing file. This is useful for logging.

```sh
bash-4.1$ cd /ilab/users/gq19/Documents/Unix/New
bash-4.1$ ps aux | grep matlab > processes.log
bash-4.1$ ps aux | grep firefox >> processes.log
bash-4.1$ ps aux | grep matlab > processes.log
```

### tee

Used in conjunction with `'|'` to send the output of a command to both a file and the terminal

This is useful if there are errors which fly by the screen before you can read them, this way whatever goes on the screen is also captured to a file.

dmesg shows the initial boot info, and the `'|'` sends the output of dmesg to tee, which then does its job by sending it to the terminal and to the log file `boot.txt`.

```sh
bash-4.1$ cd /ilab/users/gq19/Documents/Unix/New
bash-4.1$ dmesg | tee boot.txt
```

### pwd

Used to print working directory

#### pwd Example

```sh
bash-4.1$ pwd
/.autofs/ilab/ilab_users/gq19
bash-4.1$ cd /ilab/users/gq19/Documents/Unix
bash-4.1$ pwd
/ilab/users/gq19/Documents/Unix
```

### df -h

Used to calculate disk space.

```sh
bash-4.1$ df -h
Filesystem            Size  Used Avail Use% Mounted on
/dev/sda7             9.9G  453M  9.0G   5% /
tmpfs                 7.8G  5.3M  7.8G   1% /dev/shm
/dev/sda8             144G   26G  111G  19% /.freespace
/dev/sda1             5.0G  161M  4.6G   4% /boot
/dev/sda5             9.9G  157M  9.2G   2% /tmp
/dev/sda3              50G   29G   19G  61% /usr
/dev/sda6             9.9G  2.6G  6.8G  28% /var
koko-14:/vol/vol1/ilab/users
                      1.6T  1.3T  323G  80% /.autofs/ilab/ilab_users
Administrator@127.0.0.1:/cygdrive/C/Users/ADMINI~1/X2GO~1/S-0D7E~1/spool
                       28G   25G  3.4G  89% /tmp/.x2go-gq19/spool/C-gq19-50-1450284129_stDXFCE_dp32
```

### du

Used to calculate the size of a specified folder

```sh
du -cksh target_name
```

Used to calculate the size of the current folder

```sh
du -cksh
```

#### du Example

```sh
bash-4.1$ pwd
/.autofs/ilab/ilab_users/gq19
bash-4.1$ du -cksh /ilab/users/gq19/Documents/Unix
42M	/ilab/users/gq19/Documents/Unix
42M	total
bash-4.1$ cd /ilab/users/gq19/Documents/Unix
bash-4.1$ du -cksh
42M	.
42M	total
```

### Run Python program

`'./'` literally means "in the current directory"

```sh
bash-4.1$ python /ilab/users/gq19/Documents/Unix/py_program/expression.py
('Area is', 10)
('Perimeter is', 14)
bash-4.1$ cd /ilab/users/gq19/Documents/Unix/py_program
bash-4.1$ python ./expression.py
('Area is', 10)
('Perimeter is', 14)
```

### Execute a shell file

`'./'` literally means "in the current directory"

```sh
bash-4.1$ pwd
/.autofs/ilab/ilab_users/gq19
bash-4.1$ sh /ilab/users/gq19/Documents/Unix/testbench 0
total 36K
drwxr-xr-x 2 gq19 allusers 4.0K Dec 15 13:37 Desktop
drwx------ 6 gq19 allusers 4.0K Nov 22 21:59 Documents
drwx------ 2 gq19 allusers 4.0K Dec 16 14:55 Downloads
lrwxrwxrwx 1 gq19 allusers   21 Dec 17 15:56 media -> /tmp/.x2go-gq19/media
drwx------ 2 gq19 allusers 4.0K Sep 24 18:25 Music
drwx------ 2 gq19 allusers 4.0K Sep 24 18:25 Pictures
drwx------ 2 gq19 allusers 4.0K Sep 24 18:25 Public
drwx------ 3 gq19 allusers 4.0K Sep 24 19:58 Software
drwx------ 2 gq19 allusers 4.0K Sep 24 18:25 Templates
drwx------ 2 gq19 allusers 4.0K Sep 24 18:25 Videos
bash-4.1$ cd /ilab/users/gq19/Documents/Unix
bash-4.1$ sh ./testbench 0
total 48K
drwx------ 5 gq19 allusers 4.0K Dec  1 14:09 New
-rw------- 1 gq19 allusers  659 Nov 21 23:04 new file~
drwxr-xr-x 2 gq19 allusers 4.0K Dec 17 16:34 py_program
-rw------- 1 gq19 allusers  13K Dec 17 16:42 shell_commands
-rw------- 1 gq19 allusers  13K Dec 17 16:41 shell_commands~
-rwx------ 1 gq19 allusers   47 Dec 17 16:54 testbench
-rw------- 1 gq19 allusers  317 Dec 15 14:42 testbench~
```
