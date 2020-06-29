
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib as mpl
mpl.rcParams['text.usetex'] = True

# = pd.read_csv(r"Zeitentwicklung.txt", sep='\t')
#xZeitEntwicklung = data_Zeitentwicklung['Weite'].values
#xZeitEntwicklung = 1/xZeitEntwicklung

#yZeitEntwicklung = data_Zeitentwicklung['Aenderung'].values

#plt.plot(xZeitEntwicklung, yZeitEntwicklung)
#plt.gca().invert_yaxis()
#plt.xscale('log')

# dataFrag = pd.read_csv(r"Fragmente.txt", sep='\t')
# dataFrag.plot(x='masse', y='zahl')

# Massenverteilung
dataInitial = pd.read_csv("C:/Users/Bolzj/Documents/Visual Studio 2019/Workspace/CP_KiP/Kollision-im-Planetensystem/Kollision im Planetensystem/Massenverteilung_singular.txt", 
                   sep="\t", header=0, names=['Masse das Bins', 'Anzahl der Teilchen']).values
data500k = pd.read_csv("C:/Users/Bolzj/Documents/Visual Studio 2019/Workspace/CP_KiP/Kollision-im-Planetensystem/Kollision im Planetensystem/nach500kEntwicklung.txt", 
                   sep="\t", header=0, names=['Masse das Bins', 'Anzahl der Teilchen']).values
data1mio = pd.read_csv("C:/Users/Bolzj/Documents/Visual Studio 2019/Workspace/CP_KiP/Kollision-im-Planetensystem/Kollision im Planetensystem/nach1mioEntwicklung.txt", 
                   sep="\t", header=0, names=['Masse das Bins', 'Anzahl der Teilchen']).values

plt.plot(dataInitial[:,0], dataInitial[:,1], label='Massenverteilung initial')
plt.plot(data500k[:,0], data500k[:,1], label='Massenverteilung 500k')
plt.plot(data1mio[:,0], data1mio[:,1], label='Massenverteilung 1mio')
plt.title('Massenverteilung')
plt.xlabel('Masse des Bins in kg')
plt.ylabel('Teilchenanzahl')
plt.legend()
plt.xscale('log')
plt.yscale('log')
plt.show()







# Kollisionsrate
data = pd.read_csv("C:/Users/Bolzj/Documents/Visual Studio 2019/Workspace/CP_KiP/Kollision-im-Planetensystem/Kollision im Planetensystem/Kollisionsrate.txt", 
                    sep="\t", header=0, names=['Masse das Bins', 'Kollisionsrate'])
data_val = data.values
plt.plot(data_val[:,0], data_val[:,1])
plt.title('Kollisionsrate')
plt.xlabel('Masse des Bins in kg')
plt.ylabel('Kollisionsrate')
plt.xscale('log')
plt.yscale('log')
plt.show()
