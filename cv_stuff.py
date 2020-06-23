import cv2
import pyautogui as gui
import numpy as np

def imshow_fullscreen (winname, img):
    cv2.namedWindow (winname, cv2.WINDOW_NORMAL)
    cv2.setWindowProperty (winname, cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
    cv2.imshow (winname, img)
    cv2.waitKey(3000)

for i in range(10):
    img = 255 * np.ones((gui.size())[::-1] + (3,), np.uint8)
    cv2.circle(img, ((100 + (200 * i)), (100 + (50 * i))), 50, (255, 255, 0), -1)
    imshow_fullscreen(str(i), img)