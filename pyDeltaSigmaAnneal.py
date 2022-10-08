import numpy as np
import deltaSigmaEncoder

def main():
    inSignal = 0.70710678 * np.sin(2 * np.pi * 100 * np.linspace(0, 1, 705600, endpoint = False))
    a = deltaSigmaEncoder.encoder(fSize = 3, bufSize = 2, xFilter = [0.78005, -1.27818158, 0.54848959], yFilter = [2.19333, -1.69520734, 0.45151934])
    outSignal = a.encode(705600, inSignal)[0]
    np.array(outSignal, dtype="float32").tofile("sine.raw")
if (__name__ == '__main__'):
    main()