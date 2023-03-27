import math

def schwefel(x):
    d = len(x)
    sum = 0
    for xi in x:
        sum += xi * math.sin(math.sqrt(abs(xi)))
    return 418.9829 * d - sum

x = input()
x = [float(i) for i in x.split()]

result = schwefel(x)
print("Schwefel function value:", result)
