import cv2
import numpy as np
from keras.models import load_model

model = load_model('eye_gestures.h5')

def is_open(img):  #returns True for open, False for closed
    img = img.transpose((1,0,2))
    img = cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
    img = cv2.resize(img,(100,100),cv2.INTER_AREA)
    img = img/255
    img = np.expand_dims(img,axis=0)

    p = model.predict(img)
    #print(p)
    if p<0.5:
        return True
    else:
        return False