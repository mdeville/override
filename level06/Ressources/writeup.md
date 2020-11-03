# level06
## Program behaviour

1. Ask for `username` and `serial`
2. Test using `ptrace` if running in debugger
    - if yes, `exit`
3. Hash the `username` (see source code for details)
4. Check if `hashed(username)` equals `serial`
    - if yes run `system("/bin/sh")`

## Vulnerability

The `ptrace` method is not a valid anti-debugging technique.
It is still possible to break execution after the `ptrace` and change return value.

## Exploitation

1. First set a breakpoint after `ptrace` call and change the return value.
```gdb
(gdb) b *0x080487ba
Breakpoint 1 at 0x80487ba
(gdb) r
Starting program: /home/users/level06/level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: override
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 123456

Breakpoint 1, 0x080487ba in auth ()
(gdb) set $eax = 1
```

2. Set another breakpoint before the comparaison between `serial` and `hashed(username)` and print the content of `hashed(username)`
```gdb
(gdb) b *0x08048866
Breakpoint 2 at 0x8048866
(gdb) c
Continuing.

Breakpoint 2, 0x08048866 in auth ()
(gdb) p/d $eax      # this is the dummy input serial
$1 = 123456
(gdb) x/d $ebp-0x10  
0xffffdbc8:	6234511 # this is the hashed(username)
```

3. Run the program without `gdb` with the correct inputs
```sh
level06@OverRide:~$ ~/level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: override
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6234511
Authenticated!
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```