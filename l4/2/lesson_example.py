import io
import os
import select

f1 = os.open('f1.fifo', os.O_RDWR)
f2 = os.open('f2.fifo', os.O_RDWR)

read_list = [f1, f2]
print('Descriptors: ', read_list)


def read_next(read_list, index):
    try:
        fd = read_list[index]
    except IndexError:
        return
    print(os.read(fd, 100))


while True:
    r, w, x = select.select(read_list, [], [])
    print('rlist, wlist, xlist:', r, w, x)
    read_next(r, 0)
    read_next(r, 1)
