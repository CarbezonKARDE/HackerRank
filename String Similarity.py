def z(w, T):
    T.append(len(w))
    l = r = 0
    for i in range(1, len(w)):
        k = 0
        if i < r:
            k = min(r-i, T[i-l])
        while i+k<len(w) and w[i+k] == w[k]:
            k += 1
        T.append(k)
        if i+k > r:
            l = i
            r = i+k

N = int(input())
for i in range(N):
    curr = input()
    count = 0
    T = []
    z(curr, T)
    for j in range(len(T)):
        count += T[j]
    print(count)
