import cv2
import numpy as np

l_b=np.array([5,60,50])
u_b=np.array([25,255,255])                                  # lower bound and upper bound for orange color
l_b1=np.array([25,40,40])                                   
u_b1=np.array([45,255,255])                #lower and upper bound of yellow fluorescent            
l_b2=np.array([0,0,0])
u_b2=np.array([255,255,20])                #for black though i havn't used it

kernal=np.ones((3,3),np.uint8)


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
    
    
def get_perspective(img):
    img1 = cv2.GaussianBlur(img,(5,5),0)
    hsv=cv2.cvtColor(img1, cv2.COLOR_BGR2HSV)

    mask=cv2.inRange(hsv,l_b,u_b)                         
                                                          
    erode=cv2.erode(mask, kernal, iterations=2)           
    dilation= cv2.dilate(erode, kernal, iterations=5)

    mask1=cv2.inRange(hsv,l_b1,u_b1)                      
    erode1=cv2.erode(mask1, kernal, iterations=2)         
    dilation1= cv2.dilate(erode1, kernal, iterations=7)

    mask2=cv2.inRange(hsv,l_b2,u_b2)                      
    result = cv2.bitwise_and(dilation1, dilation)
    #print(result)

    try:
        dontcare,contours,heirarchy = cv2.findContours(result ,cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    except:
        #print("Contours Not found")
        return None

    if(len(contours)<4):                   # skip the frame in which the number of marks detected in <4; note that there can be marks inside the frame of screen also
        #print("Not enough contours found")
        return None

    M=cv2.moments(contours[0])
    if (M['m00']==0):                      
        return None                        
    cx = int(M['m10']/M['m00'])            
    cy = int(M['m01']/M['m00'])            
    Union = [[cx,cy]]                      #  each marks is a collection of adjacent white pixels         
                                           #  Union is the set of centroids of each contour
    for contour in contours[1:]:           #
        M=cv2.moments(contour)             #
        if (M['m00']==0):                  #
            return None                    #
        cx = int(M['m10']/M['m00'])        #
        cy = int(M['m01']/M['m00'])        #
        Union= np.concatenate(([[cx,cy]],Union))
    
    pts = cv2.convexHull(np.array(Union));     #
    pts1=pts[0]                                #
    for i in range(1,len(pts)):                # convex hull function returns the vertices of the Smallest convex polygon which contains all the points in Union set 
        pts1=np.concatenate((pts1,pts[i]))     # these points are stored in pts1 variable
    
    if(len(pts1)!=4):                      # as the projection of screen is a quadilateral we skip the frames in which the convex polygon is not a quad (which may be due to noise)
        return None

    pts1 = np.float32(pts1)
    pts1 = rewrite(pts1)                  # the rewrite function orders the points in pst1 

    pts2 = np.float32([[0, 0], [0, 380], [680, 0], [680, 380]])

    M = cv2.getPerspectiveTransform(pts1, pts2)       #Transformation Matrix

    return (pts1, M)

def map_focus_point(point, M): #point can be a tuple or a list, M is the transformation matrix
    point.append(1)
    point = np.array(point).reshape(3,1)

    prod = np.dot(M, point)
    try:
        x, y = (prod[0][0] / prod[2][0]), (prod[1][0] / prod[2][0])
        return (x, y)

    except:  #just to avoid division by zero
        return None         