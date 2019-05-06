import time
import subprocess as sp 
import os 
import csv
import pandas as pd
import matplotlib.pyplot as plt

times1=[]
times2=[]
sizes=[5,10,15,20,25,30,35,40]#,45]#,50,55,60,65,70,75,80,85,90,95,100]
time_diff = 0

for size in sizes:
    t0 = time.time()
    os.system('./driver {}'.format(size))
    t1 = time.time()
    time_diff = t1-t0
    times1.append(time_diff)
    print('With N = {} it took {} secs to run the program'.format(size,time_diff))

# for size in sizes:
#     t0 = time.time()
#     os.system('./scaled {}'.format(size))
#     t1 = time.time()
#     time_diff = t1-t0
#     times2.append(time_diff)
#     print('With N = {} it took {} secs to run the program'.format(size,time_diff))

plt.figure()
df1 = pd.DataFrame(list(zip(sizes,times1)), columns=['N','times'])
plt.plot(df1['N'],df1['times'], '--r')
plt.title('Runtimes using LUFactorization')
plt.xlabel( 'N')
plt.ylabel( 'Time Secs')
plt.legend('cholesky')
plt.savefig('./data/lu_plot.png')
plt.clf()

# df2 = pd.DataFrame(list(zip(sizes,times2)), columns=['N','times'])
# plt.plot(df2['N'],df2['times'], '--g')
# plt.title('Runtimes using Scaled')
# plt.xlabel( 'N')
# plt.ylabel( 'Time Secs')
# plt.legend('scaled')
# plt.savefig('./data/scaled_plot.png')
# plt.clf()

# plt.plot(df1['N'],df1['times'], '--r')
# plt.plot(df2['N'],df2['times'], '--g')
# plt.title('Runtimes using LU Factorization and Scaled P.P')
# plt.xlabel( 'N')
# plt.ylabel( 'Time Secs')
# plt.legend(['cholesky','scaled'])
# plt.savefig('./data/both.png')