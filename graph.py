import matplotlib.pyplot as plt
import numpy as np
import sys

# inserting x values
def read_in(x):
    with open(x,"r") as ins:
        x = []
        y = []
        for line in ins:
            x.append(float(line))
            if float(line) == 42:
                break
    return x

## variable declaration 
## error checking
if len(sys.argv) < 4:
    print ("error not enough arguments. You need three arguments to proceed")
elif len(sys.argv) >= 5:
    print ("error to many arguments. You need three arguments to proceed")
## variable declaration 
else:
    file1 = read_in(sys.argv[1])
    file2 = read_in(sys.argv[2])
    file3 = read_in(sys.argv[3])
    weight = []
    numbins = range(32)
    
    for i in range(0,len(file1) ):
        weight.append( 1 / int(len(file1)))
    ## Plot values
    plt.title('Probabiliy of Heads from 32 Coin Tosses')
    plt.xlabel('% heads')
    plt.ylabel('relative frequency')
    plt.hist(file1,weights=weight,align="mid",stacked = True,alpha=.5)
    plt.hist(file2,weights=weight,align="mid",stacked = True,alpha=.5)
    plt.hist(file3,weights=weight,align="mid",stacked = True,alpha=.5)
    
    plt.show()
