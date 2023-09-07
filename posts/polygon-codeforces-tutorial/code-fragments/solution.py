testcount = int(input())
for testcase in range(testcount):
    n = int(input())
    v = list(map(int, input().split()))
    a, b = [0] * n, [0] * n
    a[0] = v[0]
    has_ans = True
    for i in range(1, n):
        a[i] = min(a[i - 1], v[i] - b[i - 1])
        if a[i] < 0:
            has_ans = False
            break
        b[i] = v[i] - a[i]
    print("YES" if has_ans else "NO")
