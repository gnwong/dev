"""
Simple module that takes csv files and turns them
into .tex tables.

Copyright (c) 2014 George Wong
"""

import random
import numpy as np

# Generates a sample csv file
def genSample(fname):
  depth = int(random.random()*8)+1
  width = int(random.random()*4)+1
  fptr = open(fname,'w')
  for y in range(depth):
    line = ""
    for x in range(width):
      line += '{0:0.2f}'.format(random.random()*random.random()*20)
      line += ","
    line = line[:-1]
    fptr.write(line + "\n")
  fptr.close()

