import cv2 
import numpy as np

def pupil_center(img):
    mroi = cv2.flip(img,0)
    roi = mroi[70:300,310:-10]
   
    gray_roi = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)   
    gray_roi = cv2.GaussianBlur(gray_roi, (7, 7), 0)
    _, threshold = cv2.threshold(gray_roi,60, 255, cv2.THRESH_BINARY_INV)

    contours,_=cv2.findContours(threshold,cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    cnt=contours[0]

    for i in contours:
        print(cv2.contourArea(i))
        if cv2.contourArea(i)>490:
            cnt=i
            break

    (x,y),radius = cv2.minEnclosingCircle(cnt)

    return [x, y]