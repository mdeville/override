#!/usr/bin/env python2
import struct
import sys

s = sys.argv[1]
s = s.replace("0x", "")

result = ""
for i in range(0, 80, 16):
    sub = s[i:i+16]
    for j in range(14, -2, -2):
        result += sub[j:j+2]

print result.decode('hex')
