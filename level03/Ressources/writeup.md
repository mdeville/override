# level03
## Program behaviour

1. Ask for `password` (parse as `unsigned int`)
2. `key = 0x1337d00d - password`
3. Test `key` with `21`
    - if `key` is bigger, call `decrypt` with a random number
    - else call `decrypt` with `key`
4. Decrypt the string ``"Q}|u`sfg~sf{}|a3"`` by XORing each byte with `key`
5. If result equals `"Congratulations!"`, run `/bin/sh`


## Vulnerability

If `A ^ B = C` then `A ^ C = B`.
This is a terrible encryption, we can derive the encryption `key` with the message and the cypher.

## Exploitation

1. `'Q' ^ 'C' = 18`
2. `0x1337d00d - 18 = 322424827`

```sh
level03@OverRide:~$ ~/level03 
***********************************
*		level03		**
***********************************
Password:322424827
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```