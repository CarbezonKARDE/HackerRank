def reverseArray(A):
    start = 0
    end = len(A) - 1
    while start < end:
        A[start], A[end] = A[end], A[start]
        start += 1
        end -= 1
    return A
def readInput():
    import sys
    input = sys.stdin.read
    data = input().split()
    N = int(data[0])
    A = list(map(int, data[1:]))
    return A
def printOutput(reversed_array):
    print(' '.join(map(str, reversed_array)))
def main():
    A = readInput()
    reversed_array = reverseArray(A)
    printOutput(reversed_array)
if __name__ == "__main__":
    main()
