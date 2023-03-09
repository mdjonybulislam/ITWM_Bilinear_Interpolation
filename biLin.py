import numpy as np
import cv2
# from scipy.misc import imread, imshow
from scipy import ndimage
import imageio

def GetBilinearPixel(imArr, posX, posY):
	out = []

	#Get integer and fractional parts of numbers
	mod_Xi = int(posX)
	mod_Yi = int(posY)
	mod_Xf = posX - mod_Xi
	mod_Yf = posY - mod_Yi
	modXi_OneLim = min(mod_Xi+1,imArr.shape[1]-1)
	modYi_OneLim = min(mod_Yi+1,imArr.shape[0]-1)

	#Get pixels in four corners
	for chan in range(imArr.shape[2]):
		bottomLeft = imArr[mod_Yi, mod_Xi, chan]
		bottomRight = imArr[mod_Yi, modXi_OneLim, chan]
		topLeft = imArr[modYi_OneLim, mod_Xi, chan]
		topRight = imArr[modYi_OneLim, modXi_OneLim, chan]
	
		#Calculate interpolation
		bottom = mod_Xf * bottomRight + (1. - mod_Xf) * bottomLeft
		top = mod_Xf * topRight + (1. - mod_Xf) * topLeft
		pxf = mod_Yf * top + (1. - mod_Yf) * bottom
		out.append(int(pxf+0.5))

	return out

if __name__=="__main__":
	
	im = imageio.imread("1614685.jpg")
	
	
	extendedShape = list(map(int, [im.shape[0]*1.3, im.shape[1]*1.3, im.shape[2]]))
	extendedImg = np.empty(extendedShape, dtype=np.uint8)
	rowScale = float(im.shape[0]) / float(extendedImg.shape[0])
	colScale = float(im.shape[1]) / float(extendedImg.shape[1])

	for r in range(extendedImg.shape[0]):
		for c in range(extendedImg.shape[1]):
			oriRow = r * rowScale #Find position in original image
			oriCol = c * colScale
			extendedImg[r, c] = GetBilinearPixel(im, oriCol, oriRow)
   
	extendedImg = cv2.cvtColor(extendedImg, cv2.COLOR_RGB2BGR)

	cv2.imshow("bilinear_img",extendedImg)
	cv2.waitKey()
	cv2.destroyAllWindows()




