import matplotlib.pyplot as plt  # plt is used to display pictures and histograms
import matplotlib.image as mpimg  # mpimg is used to load pictures
import numpy as np
import sys
from HistogramEqualization import histogramEqualization

def heWrapper(img):
    npImg = np.array(img)
    row, col = npImg.shape
    return np.array(histogramEqualization(npImg, row, col))

def visualize(originImg, heImg):
    # construct a canvas to display the results
    plt.figure(figsize=(10, 6))

    # set new pictures and histograms
    plt.subplot(2, 2, 1)
    plt.title('Origin')
    plt.axis('off')
    plt.imshow(originImg, cmap='gray', vmin=0, vmax=255)

    plt.subplot(2, 2, 2)
    plt.title('Origin')
    plt.hist(originImg.ravel(), bins=256,  range=(0, 255), color='r')

    plt.subplot(2, 2, 3)
    plt.title('Global')
    plt.axis('off')
    plt.imshow(heImg, cmap='gray', vmin=0, vmax=255)

    plt.subplot(2, 2, 4)
    plt.title('Global')
    plt.hist(heImg.ravel(), bins=256,  range=(0, 255), color='b')

    # adjust layout of canvas
    plt.subplots_adjust(left=0.125,
                        bottom=0.1,
                        right=0.9,
                        top=0.9,
                        wspace=0.2,
                        hspace=0.35)

    # show the canvas
    plt.show()

def main():
    # check command line arguments correctness
    if len(sys.argv) != 2:
        print('Usage: python3 ${filename}')
    
    img = mpimg.imread(sys.argv[1])
    visualize(img, heWrapper(img))
    
if __name__ == '__main__':
    main()