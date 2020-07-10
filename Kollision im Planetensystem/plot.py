
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib as mpl




data = pd.read_csv('Zeitentwicklung_singular.txt', header=None, sep='\t', usecols=[0]).values

# data = pd.read_csv('test.txt', header=None, sep='\t', usecols=[0]).values
# plt.plot(data[:,0], data[:, 1])
# plt.show()

# plt.plot(dataInitial[:,0], dataInitial[:,1], label='Massenverteilung initial')
# plt.plot(data500k[:,0], data500k[:,1], label='Massenverteilung 500k')
# plt.plot(data1mio[:,0], data1mio[:,1], label='Massenverteilung 1mio')
# plt.title('Massenverteilung')
# plt.xlabel('Masse des Bins in kg')
# plt.ylabel('Teilchenanzahl')
# plt.legend()
# plt.xscale('log')
# plt.yscale('log')
# plt.show()

print(data)
# print(data[:,0])

