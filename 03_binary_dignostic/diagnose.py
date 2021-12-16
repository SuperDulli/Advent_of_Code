file = open("input", "r")
report = file.read().split("\n")
#report = [int(s, 2) for s in report]
print(report)

# gamma will hold the most common bit for each position
# epsilon the least common bit
gamma = ""
epsilon = ""
for i in range(12):
    count = 0
    for r in report:
        if r[i] == '1':
            count += 1
    if count > len(report)/2:
        gamma += '1'
        epsilon += '0'
    else:
        gamma += '0'
        epsilon += '1'

power = int(gamma, 2) * int(epsilon, 2)
print(power)
