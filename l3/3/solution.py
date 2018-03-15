"""
Разработать программу solution, которая по заданному pid, осуществляет поиск пути в дереве процессов
до процесса с идентификатором 1 (init). Для каждого найденного процесса печатается в отдельной строке его идентификатор.
"""

import os
import re
import sys

PPID_RE = re.compile('PPid:\t([0-9]+)')
PID = sys.argv[1]


def step(pid):
    with open(os.path.join('/proc', pid, 'status')) as status:
        for line in status:
            res = re.search(PPID_RE, line)
            if res:
                return res.group(1)


last_ppid = PID
while last_ppid != '0':
    print(last_ppid)
    last_ppid = step(last_ppid)
