#!/usr/bin/python
#
# faz os boxplots para as 4 areas comparando a versao seq com a versao MPI
# o tamanho de entrada foi 8192 para as duas implementacoes 
# foram executadas pelos menos 20 execucoes com run_measurements.sh
#
#

import numpy as np
import matplotlib.pyplot as plt
import os

dir_log='./data'

areas = ['full', 'seahorse', 'elephant' , 'triple_spiral']
tipos = ['boxplot', 'desvio']
experimentos = ['mpi1i8t', 'mpi2i4t', 'mpi4i2t', 'mpi8i1t']


# gera os graficos dos experimentos sequenciais
# splot = 1
# fout = 'boxplot_sequencial.png'
# plt.figure(figsize=(16,9),dpi=90)
# for area in areas:
#    m_seq = np.loadtxt (dir_log + '/mandelbrot_seq_8192_' + area + '_seconds.dat')
#    seq_seconds = m_seq
#    ax = plt.subplot(2,2,splot)
#    plt.title('Sequencial: ' + area) 
#    plt.boxplot(m_seq,showmeans=True,meanline=True)
#    plt.ylabel('Tempo (seg)',fontsize=14)
#    plt.grid(True)
#    ax.set_xticklabels(['20 execucoes '],fontsize=14)
#    splot = splot+1

# plt.savefig(fout, format='png', bbox_inches=0)

# gera os graficos dos experimentos mpi
for area in areas:
    #for exp in experimentos:
    fout = 'boxplot_ompi_' + area + '.png'
    # trocar o nome dos logs pra cara um dos experimentos do MPI: 2vm4c; 4vm2c; 8vm1c
    mpi_1 = np.loadtxt (dir_log + '/boxplot_' + experimentos[0] + '_' + area + '.dat')
    mpi_2 = np.loadtxt (dir_log + '/boxplot_' + experimentos[1] + '_' + area + '.dat')
    mpi_3 = np.loadtxt (dir_log + '/boxplot_' + experimentos[2] + '_' + area + '.dat')
    mpi_4 = np.loadtxt (dir_log + '/boxplot_' + experimentos[3] + '_' + area + '.dat')
    
    mpi_1_seconds = mpi_1
    mpi_2_seconds = mpi_2
    mpi_3_seconds = mpi_3
    mpi_4_seconds = mpi_4

    # boxplot
    plt.figure(figsize=(16,9),dpi=90)
    ax = plt.subplot(221)
    plt.title('Open MPI 1 VM com 8 cores: ' + area) 
    plt.boxplot(mpi_1_seconds,showmeans=True,meanline=True)
    plt.ylabel('Tempo (seg)',fontsize=14)
    plt.grid(True)
    ax.set_xticklabels(['10 execucoes '],fontsize=14)
    #ax.set_ylim([0, 30])

    ax = plt.subplot(222)
    plt.title('Open MPI 2 VM com 4 cores: ' + area) 
    plt.boxplot(mpi_2_seconds,showmeans=True,meanline=True)
    plt.ylabel('Tempo (seg)',fontsize=14)
    ax.set_xticklabels(['10 execucoes '],fontsize=14)
    plt.grid(True)
    #ax.set_ylim([0, 30])

    ax = plt.subplot(223)
    plt.title('Open MPI 4 VM com 2 cores: ' + area) 
    plt.boxplot(mpi_3_seconds,showmeans=True,meanline=True)
    plt.ylabel('Tempo (seg)',fontsize=14)
    ax.set_xticklabels(['10 execucoes '],fontsize=14)
    plt.grid(True)
    #ax.set_ylim([0, 30])

    ax = plt.subplot(224)
    plt.title('Open MPI 8 VM com 1 cores: ' + area) 
    plt.boxplot(mpi_4_seconds,showmeans=True,meanline=True)
    plt.ylabel('Tempo (seg)',fontsize=14)
    ax.set_xticklabels(['10 execucoes '],fontsize=14)
    plt.grid(True)
    #ax.set_ylim([0, 30])
    # save fig
    plt.savefig(fout,format='png', bbox_inches=0)
    # remove margens brancas 
    #os.system('convert -trim ' + fout + ' ' + fout)
    #plt.show()
