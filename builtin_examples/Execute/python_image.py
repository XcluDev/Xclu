#this program reads image 8 bit rgb from input and prints its size to console
#https://stackoverflow.com/questions/2850893/reading-binary-data-from-stdin
#https://stackoverflow.com/questions/42450547/python-2-7-how-to-programmatically-read-binary-data-from-stdin


#to run execute "python python_image.py"

import sys
import os


#use for output for using
def print_xclu(s):
    sys.stdout.write(s + '\n')
    sys.stdout.flush()

#use for informing
def print_xclu_err(s):
    sys.stderr.write(s + '\n')
    sys.stderr.flush()
 

 
w = 100
h = 100
ch = 3

print_xclu_err('Starting Python loop program, it expects images ' + str(w) + 'x' + str(h) + 'x' + str(ch))

i = 0

while 1:
    n = w*h*ch
    
    #buf = sys.stdin.read()
    buf = os.read(0,40000)
    print_xclu(str(i) + " " + str(len(buf)))
    i = i+1
 