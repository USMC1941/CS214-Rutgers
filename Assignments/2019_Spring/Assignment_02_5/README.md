# CS 214: Systems Programming Extra Credit 0: Easter Egg Hunt

## Abstract

This assignment is individual. Please feel free to discuss it, but do not trade or offer code or exact information. For this assignment, you will duplicate the functionality of `ps aux`. The command stands for process status and is a tool that displays a lot of useful information about running processes. Using the `/proc` entries, you can find all the information `ps` prints out. It will however require a bit of digging and reading up on various data file formats in order to find all the little nuggets of information sprinkled about and hidden in the various 'files' under `/proc`.

## Introduction

The utility was originally written by Branko Lankester as something of a hack. Since then, it went through major revisions and about five authors, adding features like listing by PID, sorting, parsing from `/proc` and `dirent` integration. In order to build your own `ps` you should focus on the last two additions, namely using `opendir()` and `readdir()` to iterate through `/proc` and generating a line entry for each Process' information you find there.

As you may recall `/proc` is a 'directory' that has within it a directory for each Process' PID that is currently running. Each of those Process directories has in it a number of files that tell you about that Process' state. There are some elements that are repeated and some that are easier to parse out than others. The main difficulty is in figuring out where the information you need is contained in those 'directories' and then how to extract it. The `man`-pages and the Internet are your friends in this regard.

## Methodology and Implementation

You will need to open `/proc`, find each directory in it and open them in turn, opening data files you need and scraping out the information you need from them. One thing to keep in mind is the format of `ps`.

### Right-justified

If you run it, you will notice all the text is right-justified along the column headings:

| Left justified | Right justified |
| -------------- | --------------: |
| Heading        |         Heading |
| `data0`        |         `data0` |
| `data1`        |         `data1` |
| longdatastuff  |   longdatastuff |

That is however a fairly direct difference. You need to understand the various headings in `ps`.

### `ps` columns

For the purposes of this project you will need to implement nearly all the default `ps` headings:

```sh
$ ps aux | head -n 1
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
```

#### USER

`USER` is the username of the owner of a Process. In actuality, this is one of the more difficult data values to determine. This may seem counterintuitive, however the machine does not care about a user's name. All users are given a user number, and that number is used internally as a user's identifier in the OS. It is only converted when displaying things to the user, however you need to know how to do that conversion, since you now need to interpret OS metadata for the user. I'll give you some pointers:

1. There is one file in the machine where username and user ID are stored and referred to; the password file. When a user logs in, they enter their username and the system needs to find their user number and verify them as that user.
2. You need to query the password file programmatically. In other words, from within your code and not using the command prompt. As you can imagine, access to the password file is pretty well locked down and there is no way you can directly `open()` it. You will need to use a command to allow you look up something in it.
3. It sure would be nice if there was an [entire library of password commands](https://man7.org/linux/man-pages/man0/pwd.h.0p.html) that would allow you to [get a password file user struct](https://man7.org/linux/man-pages/man3/getpw.3.html), indexed by `uid`, and from there access the user's name.

#### `PID`

`PID` is the Process ID of each Process in `/proc`. It should not be difficult to find.

#### `CPU`

`%CPU` is the amount of CPU time a Process has used divided by how long it has been running. You'll need to find out when the Process started and how much time passed between then and now. Keep in mind you don't have to format this as minutes and hours. It is the percentage of time the Process has used the CPU vs its runtime. It is also rounded to a tenths of a percent.

#### `MEM`

`%MEM` is the ratio of the Process' resident set size vs the physical memory present on the machine. It is a measure of the percentage of the machine's physical main memory the Process is currently taking up. For this you need to know how much virtual memory the Process' resident set is consuming; a **v**irtual **m**emory **r**esident **s**et **s**ize, so to speak, and the amount total in the machine. The machine's total physical memory is not something that changes per Process, so that is likely not going to be in an individual Process' entry. That kind of **mem**ory **info**rmation does exist elsewhere though under `/proc`.

#### `VSZ`

`VSZ` is the virtual memory usage of the entire Process (in KB). This includes all the memory the Process is using, both resident and non-resident, or the Process' virtual memory size.

#### `RSS`

`RSS` is the Process resident set size, (in KB). You need this to figure out `%MEM`, above.

#### `TTY`

`TTY` means "teletypewriter", which was an early form of text-only fax. It was a way to encode electrical commands to a printer from a keyboard, so that you could type some text, encoding a document, and send those commands to any teletype to have it type out the document there. When you hear about the "AP Newswire", it used to be physically be a wire plugged in to a teletype. Since teletype was an existing standard for encoding keystrokes and typing actions (newline, tab, etc.) it was used as a way to encode user interaction for early computers. Naming terminal sessions after teletype ports stuck, so all textual command input is still referred to as `tty` for historical reasons. Why the story? Don't worry about this one. The way security is done on the iLabs actually makes this fairly hard for you to do (if not impossible). You might notice that often even iLabs does not know, and tells you `"?"` for the TTY number sometimes. Just print out `"?"` for this one.

#### `STAT`

`STAT` is one or two letters/symbols that tell you the state of a process. It consists of one major code and one minor code. The major code is not tough, you can find it printed in a file for you. The minor codes are more problematic. You will need to deduce if they apply from the other things you can find in the `/proc` entries. Wouldn't be nice if you had the entire table of all the minors codes and their meanings? The `man`-pages are your friends, and they want to help. You will need to hunt fairly deep in the weeds to find the data that will decide all of them.

#### `START`

`START` is fairly direct. It tells you the time a Process was started, if it was started today, or the day/month it was started, if it was not started today. Be sure to output time in a 24-hour format and dates as a two digit day code followed by a three character month abbreviation.

#### `TIME`

`TIME` is the amount of time this Process has run (_not_ the time it has been alive/active/since start).

#### `COMMAND`

`COMMAND` is the command inputted in to the terminal and invoked that resulted in starting this Process. This can be somewhat annoying since actual executable name is not hard to find, but in order to find the arguments it was called with you need to dig around a bit.

## Results

Submit an `Asst2.5.tgz` containing

-   A `Makefile` with at least the following directives
    -   `all` to build your source in to a `my_ps` executable
    -   `clean` to delete all your compiled code
-   A `my_ps.c` source file.
-   Any other files or libraries you wrote to support your code.

This assignment is individual. Please feel free to discuss it, but do not trade or offer code or exact information.

It is not necessary to accept any command-line parameters. Presume your code will be writing output akin to `ps` called with the `aux` options at all times.
