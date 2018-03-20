"""
Put numbers into 2 differen FIFOs w/o blocking
"""

import os


def main():
    in1 = os.open('in1', os.O_NONBLOCK | os.O_WRONLY)
    in2 = os.open('in2', os.O_NONBLOCK | os.O_WRONLY)

    for i in range(10):
        print(i, 10 - i - 1)
        os.write(in1, bytes(str(i) + '\n', 'ascii'))
        os.write(in2, bytes(str(10 - i - 1) + '\n', 'ascii'))

    os.close(in1)
    os.close(in2)


if __name__ == '__main__':
    main()
