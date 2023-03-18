import matplotlib.pyplot as plt  # plt is used to display pictures and histograms
import matplotlib.image as mpimg  # mpimg is used to load pictures
import numpy as np
import sys
import dct, fdct

def checkArg(args):
    if len(args) != 3:
        return 0
    elif '--dct' in args:
        return 1
    elif '--fdct' in args:
        return 2
    elif '--wt' in args:
        return 3

def visualize(originImg, transImg, inverseImg):
    # construct a canvas to display the results
    plt.figure(figsize=(10, 3))

    # set new pictures and histograms
    plt.subplot(1, 3, 1)
    plt.title('Origin')
    plt.axis('off')
    plt.imshow(originImg, cmap='gray', vmin=0, vmax=255)

    plt.subplot(1, 3, 2)
    plt.title('Transformed')
    plt.axis('off')
    plt.imshow(transImg, cmap='gray', vmin=0, vmax=255)

    plt.subplot(1, 3, 3)
    plt.title('Inversely Transformed')
    plt.axis('off')
    plt.imshow(inverseImg, cmap='gray', vmin=0, vmax=255)

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
    flag = checkArg(sys.argv)
    if flag == 0:
        print('Usage: python3 main.py ${filename} ${method}')
        return

    # read image
    img = mpimg.imread(sys.argv[1])
    tImg = []
    itImg = []
    n, n = img.shape

    # run algorithm
    if flag == 1:
        print('running DCT...')
        tImg = dct.dct(img, n)
        print('running IDCT...')
        itImg = dct.idct(tImg, n)
    elif flag == 2:
        print('running FDCT...')
        tImg = fdct.fdct(img, n)
        print('running FIDCT...')
        itImg = fdct.fidct(tImg, n)
    
    # show canvas
    visualize(img, tImg, itImg)
    
if __name__ == '__main__':
    main()