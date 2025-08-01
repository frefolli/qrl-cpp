import pandas
import matplotlib.pyplot
import numpy

def moving_average(x, w):
  y = numpy.convolve(x, numpy.ones(w), 'valid') / w
  x = list(range(len(y)))
  return x, y

df = pandas.read_csv('./builddir/training.csv')
Xs, Ys = moving_average(df['CumulativeReward'], 100)
matplotlib.pyplot.plot(Xs, Ys)
matplotlib.pyplot.savefig('./builddir/training.png')
matplotlib.pyplot.close()

df = pandas.read_csv('./builddir/evaluation.csv')
Xs, Ys = moving_average(df['CumulativeReward'], 1)
matplotlib.pyplot.plot(Xs, Ys)
matplotlib.pyplot.savefig('./builddir/evaluation.png')
matplotlib.pyplot.close()
