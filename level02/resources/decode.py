import struct

s = "756e50523437684845414a3561733951377a7143574e6758354a35686e47587348336750664b394d"

for i in range(0, 80, 16):
    sub = s[i:i+16]
    for j in range(14, -2, -2):
        print(sub[j:j+2], end="")
print()
