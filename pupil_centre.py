
import cv2 
import numpy as np 
cap=cv2.VideoCapture('v1.webm')
fourcc=cv2.VideoWriter_fourcc(*'XVID')
out=cv2.VideoWriter('pupil_centre_final.avi',fourcc,20.0,(640,480))
while(True):
	ret,frame=cap.read()
	if ret==True:
		mroi = cv2.flip(frame,0)
		roi=mroi[70:300,310:-10]
		gray_roi = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
		# gray_roi=gray_roi[:150,:250]
		gray_roi = cv2.GaussianBlur(gray_roi, (7, 7), 0)
		_, threshold = cv2.threshold(gray_roi,60, 255, cv2.THRESH_BINARY_INV)
		gray_roi2 = cv2.cvtColor(threshold, cv2.COLOR_GRAY2BGR)
		contours,_=cv2.findContours(threshold,cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
		cnt=contours[0]

		for i in contours:
			print(cv2.contourArea(i))
			if cv2.contourArea(i)>490:
				cnt=i
				break

		(x,y),radius = cv2.minEnclosingCircle(cnt)
		center = (int(x),int(y))
		radius = int(radius)
		# cv2.circle(gray_roi2,center,radius,(0,255,0),2)
		# cv2.circle(gray_roi2,center,1,(255,255,0),2)
		# cv2.imshow("roi",roi)
		# cv2.imshow("threshlod",threshold)

		center2=(int(x)+310,int(y)+70)
		cv2.circle(roi,center,radius,(0,255,0),2)
		cv2.circle(roi,center,1,(255,255,0),2)
		cv2.circle(mroi,center2,radius,(0,255,0),2)
		cv2.circle(mroi,center2,1,(255,255,0),2)
		# cv2.circle(gray_roi,center,radius,(0,255,0),2)
		# cv2.circle(gray_roi,center,1,(255,255,0),2)

		# print(center)

		cv2.imshow("roic",mroi)
		out.write(mroi)

	if cv2.waitKey(1) & 0xFF==ord('q'):
		break
cap.release()
cv2.destroyAllWindows()
