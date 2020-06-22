
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
data = pd.read_csv("C:/Users/Bolzj/Documents/Visual Studio 2019/Workspace/CP_KiP/Kollision-im-Planetensystem/Kollision im Planetensystem/Massenverteilung.txt", 
                   sep="\t", header=0, names=['Masse das Bins', 'Anzahl der Teilchen'])
data_val = data.values
plt.plot(data_val[:,0], data_val[:,1])
plt.title('Massenverteilung')
plt.xlabel('Masse des Bins in kg')
plt.ylabel('Teilchenanzahl')
plt.xscale('log')
plt.yscale('log')
plt.show()

print(sum(data_val[:,0] * data_val[:,1]))


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
