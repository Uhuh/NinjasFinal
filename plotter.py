import os
import sys
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

if len(sys.argv) != 3:
    print("Must have (size) and (alg)orithm type arguments!")
    sys.exit()

size = int(sys.argv[1])
alg = int(sys.argv[2])

os.system('./driver {} {}'.format(size, alg))
with open('output.txt', 'r') as f:
    matrix = [[float(num) for num in line.split(' ')] for line in f]

x = y = np.arange(0,size+1,1)
X, Y = np.meshgrid(x,y)
z = np.array(matrix)
Z = z.reshape(X.shape)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X,Y,Z,rstride=1,cstride=1,cmap='hsv')

plt.show()
