import os
def compare_triplets(a, b):
    alice_score = 0
    bob_score = 0
    for i in range(3):
        if a[i] > b[i]:
            alice_score += 1
        elif a[i] < b[i]:
            bob_score += 1
    return alice_score, bob_score
def main():
    a = list(map(int, input().rstrip().split()))
    b = list(map(int, input().rstrip().split()))
    result = compare_triplets(a, b)
    with open(os.environ['OUTPUT_PATH'], 'w') as fptr:
        fptr.write(' '.join(map(str, result)))
        fptr.write('\n')
if __name__ == '__main__':
    main()
