#this program reads image 8 bit rgb from input and prints its size to console
#https://stackoverflow.com/questions/2850893/reading-binary-data-from-stdin
#https://stackoverflow.com/questions/42450547/python-2-7-how-to-programmatically-read-binary-data-from-stdin


#to run execute "python python_image.py"

import sys
import os


i = 0

while 1:
    #val = input()
    #print('python putput', val)

    #sys.stdout.write('python write test\n')
    #sys.stdout.flush()

    #break

    w = 100
    h = 100
    ch = 3
    n = w*h*ch
    #print("expect",n)
    
    #buf = sys.stdin.read()
    buf = os.read(0,40000)
    print(i,len(buf))
    i = i+1
    #sys.stdout.write('python write test\n')
    sys.stdout.flush()