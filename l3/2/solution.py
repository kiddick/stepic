"""
Разработать программу solution, которая осуществляет поиск и подсчет числа процессов
с именем genenv в системе Linux на которой выполняется программа.
"""

import os

counter = 0
for item in os.listdir('/proc/'):
    if item.isdigit():
        with open(os.path.join('/proc', str(item), 'status')) as status:
            if status.readline().split('\t')[1][:-1] == 'genenv':
                counter += 1

print(counter)