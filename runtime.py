import time
import os

os.system("gcc test_5.c")

t0 = time.monotonic()

os.system("a < t.in > t.out")

t1 = time.monotonic()

print(t1-t0)