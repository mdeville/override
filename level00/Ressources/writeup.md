# level00
## Program behaviour

1. Ask for `password`
2. Test `password` equal to `0x149c` (`5276`)
    - If equal, run `/bin/sh`

## Vulnerability

The password, here in a form of an `int`, is hardcoded into the binary.

## Exploitation

Enter the required password: `5276`

```sh
level00@OverRide:~$ ~/level00 
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```