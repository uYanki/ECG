# pip install biosppy
# pip install heartpy

import numpy as np
import heartpy as hp
from biosppy.signals import ecg

fs = 50

data_ecg = np.loadtxt('./ecg_normal_50hz.txt', dtype=np.int16, delimiter=',')

data = hp.scale_data(data_ecg)
working_data, measures = hp.process(data, fs)
print(measures)

out = ecg.ecg(signal=data, sampling_rate=fs * 2, show=True)
