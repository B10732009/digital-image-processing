import matplotlib.pyplot as plt

size = [64, 128, 256]
dct = [275, 2344, 40867]
fdct = [7, 48, 523]

plt.xlabel('Size(pixel)')
plt.ylabel('Time(ms)')
plt.plot(size, dct, label='dct')
plt.plot(size, fdct, label='fdct')
plt.show()