import perspective_new
import eye_center_new
import pupil_centre_new
import eye_gestures_new
import cv2
import numpy as np
import pyautogui as gui
import requests
import threading
import time

ip_face = ''
ip_screen = ''

def make_request(req, ip):
    while True:   #just being paranoid :)
        r = requests.get('http://'+ ip + '/capture')
        if r.status_code == 200:
            req.append(r.content)
            break

def get_data(i): #i represents the point on the screen to be focussed at

    req_1 = list()
    req_2 = list()
    t1 = threading.Thread(target = make_request, args = (req_1, ip_face))
    t2 = threading.Thread(target = make_request, args = (req_2, ip_screen,))
    t1.start()
    t2.start()
    t1.join()
    t2.join()

    req_1 , req_2 = req_1[0] , req_2[0]
    img_face , img_screen = np.frombuffer(req_1, np.uint8) , np.frombuffer(req_2, np.uint8)
    img_face , img_screen = cv2.imdecode(img_face, cv2.IMREAD_COLOR) , cv2.imdecode(img_screen, cv2.IMREAD_COLOR)

    eye_center = pupil_centre_new.pupil_center(img_face)
    screen_point = perspective_new.get_perspective(img_screen)

    if not screen_point:
        return None

    screen_point = screen_point[0]

    if i < 4:
        screen_point = list(screen_point[i])
    elif i == 4: #top edge center
        screen_point = list((screen_point[0] + screen_point[2])/2)
    else:        #bottom edge center
        screen_point = list((screen_point[1] + screen_point[3])/2)

    data = eye_center + screen_point
    return data


def main():
    data = np.empty((0,4))

    print("Focus on the top left corner for the next 5 seconds")
    time.sleep(1.5)
    temp = get_data(0)
    while not temp:
        temp = get_data(0)
    np.append(data, [temp], axis = 0)
    print("Done. Relax for 5 seconds")
    time.sleep(5)

    print("Focus on the top right corner for the next 5 seconds")
    time.sleep(1.5)
    temp = get_data(2)
    while not temp:
        temp = get_data(2)
    np.append(data, [temp], axis = 0)
    print("Done. Relax for 5 seconds")
    time.sleep(5)

    print("Focus on the bottom left corner for the next 5 seconds")
    time.sleep(1.5)
    temp = get_data(1)
    while not temp:
        temp = get_data(1)
    np.append(data, [temp], axis = 0)
    print("Done. Relax for 5 seconds")
    time.sleep(5)

    print("Focus on the bottom right corner for the next 5 seconds")
    time.sleep(1.5)
    temp = get_data(3)
    while not temp:
        temp = get_data(3)
    np.append(data, [temp], axis = 0)
    print("Done. Relax for 5 seconds")
    time.sleep(5)

    print("Focus on the top edge center for the next 5 seconds")
    time.sleep(1.5)
    temp = get_data(4)
    while not temp:
        temp = get_data(4)
    np.append(data, [temp], axis = 0)
    print("Done. Relax for 5 seconds")
    time.sleep(5)

    print("Focus on the bottom edge center for the next 5 seconds")
    time.sleep(1.5)
    temp = get_data(5)
    while not temp:
        temp = get_data(5)
    np.append(data, [temp], axis = 0)
    
    print("Done. Now, let's train an ML model to estimate your gaze")

    reg_x , reg_y = eye_center_new.get_models(data)
    print("Model has been trained.")