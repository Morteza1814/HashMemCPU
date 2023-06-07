import matplotlib.pyplot as plt
import numpy as np
 
dataAreaOpt = {'C++ Map':17.1, 'C++ Unordered Map':5.5, 'Hopscotch Map':3.2}
dataPerfOpt = {'C++ Map':49.1, 'C++ Unordered Map':15.8, 'Hopscotch Map':9.2}
xNames = list(dataAreaOpt.keys())
areaoptValues = list(dataAreaOpt.values())
perfoptValues = list(dataPerfOpt.values())
bar_width = 0.4
# use LaTeX fonts in the plot
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
index = np.arange(3)
# f = plt.figure() 
f, ax = plt.subplots()
# plot
ax.bar(index, areaoptValues, color='g', width=bar_width, label="Area Optimized", edgecolor='black')
ax.bar(index+bar_width, perfoptValues, color='maroon', width=bar_width, label="Performance Optimized", edgecolor='black')
# plt.xticks(y_pos, ks) 
# set labels (LaTeX can be used)
plt.title(r'\textbf{PIM Speedup}', fontsize=11)
# plt.xlabel(r'\textbf{CPU Implementations}', fontsize=11)
plt.ylabel(r'\textbf{Speedup}', fontsize=11)
ax.set_xticks(index + bar_width / 2)
ax.set_xticklabels(xNames)
plt.yticks(np.arange(0, max(perfoptValues)+1, 5))
ax.bar_label(ax.containers[0], label_type='edge')
ax.bar_label(ax.containers[1], label_type='edge')

ax.legend()
plt.show()
# save as PDF
f.savefig("mix.pdf", bbox_inches='tight')
