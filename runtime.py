import time
import os

os.system("gcc test_2.c")

t0 = time.monotonic()

os.system("a < input > output")

t1 = time.monotonic()

print(t1-t0)