import sys

def sum(args):
    x = 0
    y = 0
    z = 0
    for arg in args:
        n = int(arg)
        x += n
        y += n * n
        z += n * n * n
    return (x, y, z)

if __name__ == "__main__":
    args = sys.argv[1:]
    x, y, z = sum(args)
    print("Sum=%d Sum2=%d Sum3=%d" % (x, y, z))
