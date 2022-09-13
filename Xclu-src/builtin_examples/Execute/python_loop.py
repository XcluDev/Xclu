#this program reads string from input and prints it to output

#https://en.wikiversity.org/wiki/Python_Concepts/Console_Output
#to run execute "python python_loop.py"

import sys
import time
#import os

#use for output for using
def print_xclu(s):
    sys.stdout.write(s + '\n')
    sys.stdout.flush()

#use for informing
def print_xclu_err(s):
    sys.stderr.write(s + '\n')
    sys.stderr.flush()
    
    
#Just inform
print_xclu_err("Python program started, it expects some values...");

while 1:
    #Read input
    val = input()
    
    #Output for using
    print_xclu('Python outputs input: ' + val)
    
    #time.sleep(1)
    
    #break
    
    

