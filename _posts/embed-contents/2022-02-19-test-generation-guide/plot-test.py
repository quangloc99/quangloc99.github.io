import matplotlib.pyplot as plt
import math
from sys import argv, stderr
from os import getenv

test_filename = argv[1]
out_img_filename = argv[2]
out_dir = getenv("IMAGE_OUT_DIR", "./")  # output dir because I'm making a blog
out_img_fullname = f"{out_dir}/{out_img_filename}"
print(f"Reading {test_filename} and exporting image {out_img_fullname}", file=stderr)

plt.figure(figsize=(8, 4), dpi=120)
plt.style.use('dark_background')

with open(test_filename, 'r') as f:
    ntest = int(f.readline())
    max_val = 0
    for testcase in range(1, ntest + 1):
        n = int(f.readline())
        a = list(map(int, f.readline().split()))
        plt.plot(a, label=f"case {testcase} (n = {n})")
        max_val = max(max_val, *a)
    p10 = 10 ** int(math.log10(max_val))
    plt.xlabel("position $i$")
    plt.ylabel("value $a_i$")
    plt.yticks([0, p10, max_val * 1.1])
    plt.legend()
    plt.tight_layout()
    plt.savefig(out_img_fullname)
    # plt.show()
