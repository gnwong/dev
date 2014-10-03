"""
Copyright (c) 2014 George Wong
"""

# Parses argv, assuming argv is passed
def ParseArgv(argv):
  args = []
  i = 0
  while i < len(argv):
    if i==0: 
      i+=1
      continue
    if argv[i][0]=='-':
      if len(argv[i].split(':'))==2:
        args.append(argv[i].split(':'))
      else:
        args.append(argv[i])
    else:
      args.append(argv[i])
    i+=1
  return args

# Parses a file, given a filename
def ParseFile(fname,delimiter='='):
  parsed = {}
  fptr = open(fname,'r')
  for line in fptr:
    line = line.strip()

    # This is a comment
    try:
      if line[0]=='/': continue 
    except: pass

    # Actually parse
    line_data = line.split(delimiter)
    if len(line_data)==2:
      data = line_data[1].strip()
      try:
        indata = float(data)
      except:
        indata = data
      parsed[line_data[0].strip()] = indata

  fptr.close()

  return parsed

