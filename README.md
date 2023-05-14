# 0x16. C - Simple Shell

## Learning Materials

- [Everything you need to know to start coding your own shell](https://www.notion.so/C-Programming-f13cdb9661db464f8ea326c5a2654e8e)
- [Unix shell](https://en.wikipedia.org/wiki/Unix_shell)
- [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)
- [Thompson shell](https://en.wikipedia.org/wiki/Thompson_shell)



---

<details>
<summary>Allowable functions and system calls for the project</summary>

+ `access` (man 2 access)
+ `chdir` (man 2 chdir)
+ `close` (man 2 close)
+ `closedir` (man 3 closedir)
+ `execve` (man 2 execve)
+ `exit` (man 3 exit)
+ `\_exit` (man 2 \_exit)
+ `fflush` (man 3 fflush)
+ `fork` (man 2 fork)
+ `free`(man 3 free)
+ `getcwd` (man 3 getcwd)
+ `getline` (man 3 getline)
+ `getpid` (man 2 getpid)
+ `isatty` (man 3 isatty)
+ `kill` (man 2 kill)
+ `malloc` (man 3 malloc)
+ `open` (man 2 open)
+ `opendir` (man 3 opendir)
+ `perror` (man 3 perror)
+ `read` (man 2 read)
+ `readdir` (man 3 readdir)
+ `signal` (man 2 signal)
+ `stat` (\_\_xstat) (man 2 stat)
+ `lstat` (\_\_lxstat) (man 2 lstat)
+ `fstat` (\_\_fxstat) (man 2 fstat)
+ `strtok` (man 3 strtok)
+ `wait` (man 2 wait)
+ `waitpid` (man 2 waitpid)
+ `wait3` (man 2 wait3)
+ `wait4` (man 2 wait4)
+ `write` (man 2 write)

</details>

<details>
<summary>The shell is compiled this way:</summary>
<pre>$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 \*.c -o hsh</pre>
</details>

## Testing

<details>
<summary>The shell works like this in interactive mode:</summary>
<pre>$ ./hsh<br>($) /bin/ls<br>hsh main.c shell.c<br>($)<br>($) exit<br>$</pre>
</details>

<details>
<summary>But also in non-interactive mode:</summary>
<pre>$ echo "/bin/ls" | ./hsh<br>hsh main.c shell.c test\_ls\_2<br>$<br>$ cat test\_ls\_2<br>/bin/ls<br>/bin/ls<br>$<br>$ cat test\_ls\_2 | ./hsh<br>hsh main.c shell.c test\_ls\_2<br>hsh main.c shell.c test\_ls\_2<br>$</pre>
</details>

## Authors

- Adedayo Akinade (akinadeadedayo1@gmail.com)

- 
