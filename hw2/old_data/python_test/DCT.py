import matplotlib.pyplot as plt  # plt is used to display pictures and histograms
import matplotlib.image as mpimg  # mpimg is used to load pictures
import numpy as np
import math

picName = ['TestImg/child.tif', 'TestImg/lena_small.tif',
           'TestImg/Stone.tif', 'TestImg/university.tif']
picNumber = 1  # select a picture in the picture list


# def oneDivSqrt2N(N):
#    return 1 / math.sqrt(2 * N)


def Cos(x, i, N):
    return math.cos((2*x+1)*i*math.pi/2/N)


def C(i):
    if i == 0:
        return 1/math.sqrt(2)
    return 0


def init(N):
    ods2N = 1 / math.sqrt(2 * N)
    cosList = []
    for i in range(0, N):
        row = []
        for j in range(0, N):
            row.append(math.cos((2*i+j)*i*math.pi/2/N))
        cosList.append(row)

    cList = [0]
    temp = 1/math.sqrt(2)
    for i in range(0, N):
        cList.append(temp)

    return ods2N, cosList, cList


def normalDCT(img, N):
    newImg = img
    oDS2N, cosList, cList = init(N)

    for i in range(0, N):
        print(i)
        for j in range(0, N):
            temp = 0
            for x in range(0, N):
                for y in range(0, N):
                    temp += cosList[x][i] * cosList[y][j] * (img[x][y] - 128)

            temp *= oDS2N * cList[i] * cList[j]
            newImg[i][j] = round(temp)
    return newImg


# read source image
img = np.array(mpimg.imread(picName[picNumber]))

# construct a canvas to display the results
plt.figure(figsize=(12, 6))

# set new pictures and histograms
plt.subplot(3, 2, 1)
plt.title("Image(origin)")
plt.axis('off')
plt.imshow(img, cmap='gray', vmin=0, vmax=255)

plt.subplot(3, 2, 2)
plt.title("Histogram(origin)")
plt.hist(img.ravel(), bins=256,  range=(0, 255), color='b')

row, col = img.shape
transformedImg = normalDCT(img, row)

plt.subplot(3, 2, 3)
plt.title("Image(globally histogram equalized)")
plt.axis('off')
#plt.imshow(transformedImg, cmap='gray', vmin=0, vmax=255)

plt.subplot(3, 2, 4)
plt.title("Histogram(globally histogram equalized)")
#plt.hist(transformedImg.ravel(), bins=256,  range=(0, 255), color='m')

#transformedImg2 = localHE(img, 27)

plt.subplot(3, 2, 5)
plt.title("Image(locally histogram equalized, with 27*27 windows)")
plt.axis('off')
#plt.imshow(transformedImg2, cmap='gray', vmin=0, vmax=255)

plt.subplot(3, 2, 6)
plt.title("Histogram(locally histogram equalized, with 27*27 windows)")
#plt.hist(transformedImg2.ravel(), bins=256,  range=(0, 255), color='y')

# adjust layout of canvas
plt.subplots_adjust(left=0.125,
                    bottom=0.1,
                    right=0.9,
                    top=0.9,
                    wspace=0.2,
                    hspace=0.35)

# show the canvas
plt.show()
