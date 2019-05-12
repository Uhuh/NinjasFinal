import os
import sys
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from math import sqrt

sizes = [5,10,15,20,25,30,35,40]#,45,50,55,60,65,70,75,80,85,90,95,100]

diff = []

for size in sizes:
	os.system('./driver {} {}'.format(size, 1))
	os.system('./a.out {}'.format(size))
	with open('output.txt', 'r') as f:
	    matrix1 = [[float(num) for num in line.split(' ')] for line in f]
	with open('output2.txt', 'r') as f:
	    matrix2 = [[float(num) for num in line.split(' ')] for line in f]

	tot = 0
	for i in range(size):
		for j in range(size):
			tot += (matrix1[i][j]-matrix2[i][j])**2
	tot = sqrt((1/size)**2 * tot)
	diff.append(tot)

plt.figure()
df1 = pd.DataFrame(list(zip(sizes,diff)), columns=['N','Error'])
plt.plot(df1['N'],df1['Error'], '--r')
plt.title('Norm 2 Error using Choleski')
plt.xlabel( 'N')
plt.ylabel( 'Error')
plt.legend('Cholesky')
plt.savefig('errorplot.png')
plt.clf()
