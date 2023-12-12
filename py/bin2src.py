import os

# Skip first 7 bytes
skip = 7

def bin2src(binfile, srcfile):
    with open(binfile, 'rb') as f:
        data = f.read()
    with open(srcfile, 'w') as f:
        f.write("_charset:\n")
        f.write("    db ");
        for i, b in enumerate(data):
            if i < skip:
                continue
            f.write(f"${hex(b)[2:]:02s}")
            if (i-skip) % 8 == 7 and i < len(data) - (skip+1):
                f.write('\n')
                f.write("    db ")
            elif i == len(data)-1:
                f.write('\n')
            else:
                f.write(', ')


if __name__ == '__main__':
    binfile = os.path.join(os.path.dirname(__file__), "../_assets/data/char.sc1")
    srcfile = os.path.join(os.path.dirname(__file__), "../asm/src/char.sc1")
    bin2src(binfile, srcfile) 
    with open(srcfile, "r") as fp:
        print(fp.read())

