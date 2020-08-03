
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib as mpl




data = pd.read_csv(r'C:\Users\hi84qur\source\repos\Kollision im Planetensystem\Kollision im Planetensystem\Messwerte\Aufgabe 8\Zeitentwicklung_25mio_randomFragmente.txt', sep='\t')

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

#data.drop(data.columns[range(378,378)], axis=1, inplace=True)
#data.drop(data.columns[range(1,35)], axis=1, inplace=True)

#data_dropTable = np.linspace(1, len(data.columns)-1, num=round(len(data.columns)/50), dtype=int)
#data.drop(data.columns[data_dropTable], axis=1, inplace=True)

fig, ax = plt.subplots(figsize=(10, 8))

#for i in range(1,50):


data.plot(x='Bin-size',logy=False, legend=False, cmap='viridis',logx=True)


plt.xlabel('Teilchengröße', fontsize=18)
plt.ylabel('Masse im Bin', fontsize=18)
plt.title('Unbekannte Anzahl Fragmente', fontsize=21)
plt.tight_layout()
plt.savefig("Aufgabe8_randomFragmente_log.pdf")