"""
Разработать программу solution, которая при запуске себя "демонизирует" и остается в  памяти.
Перед закрытием стандартного потока вывода stdout унаследованного от родителя, 
программа должна вывести в него Pid процесса-демона.
"""

import os
import sys
import time

pid = os.fork()

if pid > 0:
    print(pid)
elif pid == 0:
    os.chdir('/')
    os.setsid()
    sys.stdin.close()
    sys.stdout.close()
    sys.stderr.close()
    time.sleep(10)
else:
    pass
