burst = {} # (pid, burst_time)

for i in range(419):
    p, b = input().split()
    p = int(p)
    b = int(b)
    if p in burst:
        burst[p] = max(burst[p], b)
    else:
        burst[p] = b

# print(burst)

for i in range(200):
    if i in burst:
        print(f"pid: {i}, burst_time: {burst[i]}")
