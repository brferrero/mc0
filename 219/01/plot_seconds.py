import numpy as np
import matplotlib.pyplot as plt


tam_entrada = [16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192]
tam_entrada_labels = ['16', '', '','', '','', '1024', '2048','4096','8192']
y_time = np.arange(0, 100, 10)
f_out = 'tam_entrada_seg.png'

plt.figure(figsize=(16,9),dpi=90)

#area full
sec_omp = np.loadtxt('mandelbrot_omp_full.log_seconds.dat')
sec_seq = np.loadtxt('mandelbrot_seq_full.log_seconds.dat')
sec_pth = np.loadtxt('mandelbrot_seq_seahorse.log_seconds.dat')

ax = plt.subplot(221)
plt.plot(tam_entrada, sec_seq,'b--o',label='seq')
plt.plot(tam_entrada, sec_omp,'r--o',label='omp')
plt.plot(tam_entrada, sec_pth,'g--o',label='pth')
plt.ylabel('Tempo (seg)',fontsize=14)
#plt.xlabel('Tamanho da entrada',fontsize=14)
plt.legend(loc='upper left',shadow=True, fontsize=11)
plt.title('Area: Full Picture')
ax.set_xticks(tam_entrada)
ax.set_yticks(y_time)
ax.set_yticklabels(y_time,fontsize=14)
ax.set_xticklabels(tam_entrada_labels,fontsize=14)
plt.grid(True)

#area Seahorse
sec_omp = np.loadtxt('mandelbrot_omp_seahorse.log_seconds.dat')
sec_seq = np.loadtxt('mandelbrot_seq_seahorse.log_seconds.dat')
sec_pth = np.loadtxt('mandelbrot_seq_full.log_seconds.dat')

ax = plt.subplot(222)
plt.plot(tam_entrada, sec_seq,'b--o',label='seq')
plt.plot(tam_entrada, sec_omp,'r--o',label='omp')
plt.plot(tam_entrada, sec_pth,'g--o',label='pth')
plt.ylabel('Tempo (seg)',fontsize=14)
#plt.xlabel('Tamanho da entrada',fontsize=14)
plt.legend(loc='upper left',shadow=True, fontsize=11)
plt.title('Area: Seahorse Valley')
ax.set_xticks(tam_entrada)
ax.set_yticks(y_time)
ax.set_yticklabels(y_time,fontsize=14)
ax.set_xticklabels(tam_entrada_labels,fontsize=14)
plt.grid(True)

#area Elephant
sec_omp = np.loadtxt('mandelbrot_omp_elephant.log_seconds.dat')
sec_seq = np.loadtxt('mandelbrot_seq_elephant.log_seconds.dat')
sec_pth = np.loadtxt('mandelbrot_seq_seahorse.log_seconds.dat')

ax = plt.subplot(223)
plt.plot(tam_entrada, sec_seq,'b--o',label='seq')
plt.plot(tam_entrada, sec_omp,'r--o',label='omp')
plt.plot(tam_entrada, sec_pth,'g--o',label='pth')
plt.ylabel('Tempo (seg)',fontsize=14)
plt.xlabel('Tamanho da entrada',fontsize=14)
plt.legend(loc='upper left',shadow=True, fontsize=11)
plt.title('Area: Elephant Valley')
ax.set_xticks(tam_entrada)
ax.set_yticks(y_time)
ax.set_yticklabels(y_time,fontsize=14)
ax.set_xticklabels(tam_entrada_labels,fontsize=14)
plt.grid(True)

#area Triple spiral
sec_omp = np.loadtxt('mandelbrot_omp_triple_spiral.log_seconds.dat')
sec_seq = np.loadtxt('mandelbrot_seq_triple_spiral.log_seconds.dat')
sec_pth = np.loadtxt('mandelbrot_seq_seahorse.log_seconds.dat')

ax = plt.subplot(224)
plt.plot(tam_entrada, sec_seq,'b--o',label='seq')
plt.plot(tam_entrada, sec_omp,'r--o',label='omp')
plt.plot(tam_entrada, sec_pth,'g--o',label='pth')
plt.ylabel('Tempo (seg)',fontsize=14)
plt.xlabel('Tamanho da entrada',fontsize=14)
plt.legend(loc='upper left',shadow=True, fontsize=11)
plt.title('Area: Triple Spiral Valley')
ax.set_xticks(tam_entrada)
ax.set_yticks(y_time)
ax.set_yticklabels(y_time,fontsize=14)
ax.set_xticklabels(tam_entrada_labels,fontsize=14)
plt.grid(True)


plt.savefig(f_out,format='png', bbox_inches=0)
plt.show()
