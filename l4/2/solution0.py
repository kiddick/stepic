"""
В текущем каталоге есть 2 канала in1 in2, в которые в случайном порядке поступают числа, 
которые необходимо просуммировать и вывести окончательную сумму на экран. 
Сумма выводится в отдельной строке, завершающейся символом конца строки. 
Признаком окончания подачи символов в каналы является закрытие этих каналов посылающей стороной.

Подсказка: для неблокирующего чтения использовать select.
Замечание: ﻿протокол обмена по каналу текстовый, то есть числа представлены строками
"""

import io
import os
import select
import time

f1 = os.open('in1', os.O_NONBLOCK | os.O_RDONLY)
f2 = os.open('in2', os.O_NONBLOCK | os.O_RDONLY)

read_list = [f1, f2]
print('Descriptors: ', read_list)


def read_next(read_list, index):
    try:
        fd = read_list[index]
    except IndexError:
        return
    print('{} ready to read'.format(fd))
    print(os.read(fd, 100))


r, w, x = select.select(read_list, [], read_list)
# while True:
while read_list:
    for fd in read_list:
        print('{} ready to read'.format(fd))
        data = os.read(fd, 100)
        if not data:
            read_list.remove(fd)
        print(data)
