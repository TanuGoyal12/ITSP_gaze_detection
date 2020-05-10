import cv2
import numpy as np

def rewrite(l):
    l1=l.copy()
    a=[]
    for i in range(4):
       a.append(l[i][0]+l[i][1])
    a=np.float32(a).reshape(4,1)
    l=np.hstack([l,a])
    l2=l.copy()
    p=l[:,2]
    p2=np.argsort(p)
    for i in range(4):
        j=p2[i]
        l[i]=l2[j]
    for i in range(2):
        l1[:,i]=l[:,i]
    return l1

kernal=np.ones((5,5),np.uint8)
img = cv2.imread('laptop1.jpg')
imgray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
ret, mask = cv2.threshold(imgray, 130, 255, cv2.THRESH_BINARY)
closing=cv2.morphologyEx(mask,cv2.MORPH_CLOSE,kernal,iterations=3)
contours,heirarchy=cv2.findContours(closing,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

a = []
for x in contours:
    a.append(len(x))
t = 0
for x in a:
    t = max(t, x)
for i in range(len(a)):
    if t == a[i]:
        break

cnt = contours[i]

epsilon = 0.1 * cv2.arcLength(cnt, True)
approx = cv2.approxPolyDP(cnt, epsilon, True)

img = cv2.drawContours(img,[approx],0,(0,0,255),2)

pts1 = np.float32(approx).reshape(4,2)

pts1 = rewrite(pts1)

pts2 = np.float32([[0, 0], [0, 380], [680, 0], [680, 380]])

M = cv2.getPerspectiveTransform(pts1, pts2)
dst = cv2.warpPerspective(img, M, (680, 380))

cv2.imshow('image', img)
cv2.imshow('output', dst)

cv2.waitKey(1000000)
cv2.destroyAllWindows()


