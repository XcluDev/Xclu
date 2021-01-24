#https://en.wikiversity.org/wiki/Python_Concepts/Console_Output
#to run execute "python python_write.py"

import sys
#import os

print ('python print test')

sys.stdout.write('python write test\n')
sys.stdout.flush()
#os.write(1, b'line 3 to stdout  ')

#sys.stderr.write('python stderr write test\n') ; sys.stderr.flush()