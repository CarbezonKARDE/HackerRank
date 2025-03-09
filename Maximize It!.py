from itertools import *
N=  input().split()
n,k = int(N[0]) , int(N[1])
a = []
for i in range(n):
    a.append(map(int,input().split()[1:]))
Max = -1
for i in product(*a): 
    Max = max(sum(map(lambda x : x**2,i))%k,Max) 
print(Max)
