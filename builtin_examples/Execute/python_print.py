#https://en.wikiversity.org/wiki/Python_Concepts/Console_Output
#to run execute "python python_write.py"

import sys
#import os


#use for output for using
def print_xclu(s):
    sys.stdout.write(s + '\n')
    sys.stdout.flush()

#use for informing
def print_xclu_err(s):
    sys.stderr.write(s + '\n')
    sys.stderr.flush()
    

#just inform to xclu execute console
print_xclu_err('Executing Python write test')

#value for using in xclu
print_xclu('This is Python result'); 

