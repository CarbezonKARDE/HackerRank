import os
def a_very_big_sum(ar):
    return sum(ar)

def main():
    ar_count = int(input().strip())
    ar = list(map(int, input().rstrip().split()))
    result = a_very_big_sum(ar)
    with open(os.environ['OUTPUT_PATH'], 'w') as fptr:
        fptr.write(str(result) + '\n')

if __name__ == '__main__':
    main()
