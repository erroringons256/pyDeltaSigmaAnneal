import circBuf
import random
class encoder:
    def __init__(self, fSize = 1, bufSize = 1, xFilter = [1.0], yFilter = [0.0], xState = None, yState = None): # xFilter and yFilter are arrays, xState and yState are circBufs
        if(xState is None):
            xState = circBuf.circBuf(bufSize)
        if(yState is None):
            yState = circBuf.circBuf(bufSize)
        self.xFilter = xFilter
        self.yFilter = yFilter
        self.xState = xState
        self.yState = yState
        self.fSize = fSize

    def encode(self, n, inSignal): # n = amount of iterations, input = input sample list
        outSignal = n * [1]
        i = 0
        while(i < n):
            q = inSignal[i] - self.yState.get(0)
            outSignal[i] = 2 * int((q + 0.1 * (2 * random.random() - 1.0))> 0) - 1
            self.xState.set(0, outSignal[i] - q)
            self.xState.roll(1)
            self.yState.roll(1)
            j = 1
            buf = 0.0
            while(j < self.fSize + 1):
                buf += self.xFilter[j - 1] * self.xState.get(j) + self.yFilter[j - 1] * self.yState.get(j)
                j += 1
            #buf += 1.5 * self.xState.get(1) - 1.0 * self.xState.get(2) + 0.5 * self.yState.get(1)
            self.yState.set(0, buf)
            i += 1

        return (outSignal, self)