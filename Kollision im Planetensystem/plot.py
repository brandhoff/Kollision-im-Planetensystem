
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

dataFrag = pd.read_csv(r"Fragmente.txt", sep='\t')
dataFrag.plot(x='masse', y='zahl')