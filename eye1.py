import numpy as np
from numpy import genfromtxt
import cv2
import requests

i = 0


def click_event(event, x, y, flags, param):        #called when mouse is clicked on scene image 
	if event == cv2.EVENT_LBUTTONDOWN:
		data = param[0]
		img = param[1]
		img1 = param[2]

		global i 
		cv2.imwrite(str(i)+".jpg", img)      #clicks the image of eye
		i = i+1
		                                     # use getreflectioncenter function if using reflection instead of pupil, ignore otherwise
		ScreenCoordinates = (x,y)
		data.append( ScreenCoordinates)
	

def getreflectionCenter(img):                                #returns the center of brightest and largest contour                                               
	imggray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	ret, thresh = cv2.threshold(imggray, 235,255, cv2.THRESH_BINARY)
	dontcare, contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	if len(contours)>0:
		maxi = contours[0]
		for contour in contours[1:]:
			if cv2.contourArea(contour)>cv2.contourArea(maxi):
				maxi = contour
	#cv2.drawContours(img, [maxi], -1, (0, 255, 0), 2)
	if len(contours)>0:
		M=cv2.moments(maxi)  
		if M['m00'] != 0:                                  
			cx = int(M['m10']/M['m00'])
			cy = int(M['m01']/M['m00'])
			return(cx, cy)
	return None



cap = cv2.VideoCapture(1)           # use 1 for external webcam and 0 for embedded webcam
ret, img = cap.read()
img = cv2.GaussianBlur(img,(5,5),0)        # I have used external webcam as eye camera
data = []

img1 = requests.get("http://192.168.43.1:8080/shot.jpg")         #
img1 = np.array(bytearray(img1.content), dtype = np.uint8)		 # use such code to use smartphone as webcam
img1 = cv2.imdecode(img1, -1)									 # you will need to install IP webcam app on your phone
img1 = cv2.resize(img1,(500,300))								 #
																 # I have used smartphone camera as perspective/ scene camera
#cap1 = cv2.VideoCapture(0)										 # both cameras were fixed wrt head
#ret, img1 = cap1.read()
cv2.namedWindow('img1')
#cv2.setMouseCallback('img1', click_event, [data, img, img1])

EyeCenter = None
while(True):

	ret, img = cap.read()
	img = cv2.GaussianBlur(img,(5,5),0)
	img = cv2.getRectSubPix(img, (300,200), (500,310))
	img = cv2.rotate(img, cv2.ROTATE_90_COUNTERCLOCKWISE)
	img = cv2.rotate(img, cv2.ROTATE_90_COUNTERCLOCKWISE)
	
	#ret, img1 = cap1.read()
	img1 = requests.get("http://192.168.43.1:8080/shot.jpg")
	img1 = np.array(bytearray(img1.content), dtype = np.uint8)
	img1 = cv2.imdecode(img1, -1)
	img1 = cv2.resize(img1,(700,420))
	img1 = cv2.rotate(img1, cv2.ROTATE_90_COUNTERCLOCKWISE)
	center = getEyeCenter(img)
	if center is not None:
		EyeCenter = center
	
	imggray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	ret, thresh = cv2.threshold(imggray, 235,255, cv2.THRESH_BINARY)
	dontcare, contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	if len(contours)>0:
		maxi = contours[0]
		for contour in contours[1:]:
			if cv2.contourArea(contour)>cv2.contourArea(maxi):
				maxi = contour

	cv2.imshow("thresh",thresh)
	cv2.imshow("img",img)
	cv2.imshow("img1", img1)
	cv2.setMouseCallback('img1', click_event, [data, img, img1,EyeCenter])
	key = cv2.waitKey(10)    
	if key==ord('q'):                        #press "q" key on keyboard to stop videocapture
		break

print (data)


cap.release()
cv2.destroyAllWindows()