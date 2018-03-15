"""
Разработать программу solution, которая по заданному pid, осуществляет поиск всех потомков процесса 
с этим идентификатором и выводит их количество (включая процесс с заданным pid).
"""

import os
import re
import sys

PPID_RE = re.compile('PPid:\t([0-9]+)')
PID = sys.argv[1]

counter = 1
for item in os.listdir('/proc/'):
    if item.isdigit():
        with open(os.path.join('/proc', str(item), 'status')) as status:
            for line in status:
                res = re.search(PPID_RE, line)
                if res:
                    ppid = res.group(1)
                    if ppid == PID:
                        counter += 1

print(counter)
