import tkinter as tk
import pyautogui as gui
import time

root = tk.Tk()
root.attributes('-fullscreen', True)
root.bind('<F11>', lambda event : root.attributes('-fullscreen', not root.attributes('-fullscreen')))  #F1 to toggle fullscreen
root.bind('<Escape>', lambda event : root.attributes('-fullscreen', False))   #Escape key to escape fullscreen

def draw_circle(canvas, i):
    canvas.create_oval(100 + (200 * (i + 1)), 100 + (10 * (i + 1)), 150 + (200 * (i + 1)), 150 + (10 * (i + 1)), fill = 'red')

width , height = gui.size()
canvas = tk.Canvas(root, width = width, height = height, bg = 'white')
canvas.pack(fill = tk.BOTH)
canvas.create_oval(450, 450, 550, 550, fill = 'red')
root.after(5000, canvas.delete, 'all')
for i in range(5):
    root.after(7000 * (i + 1), draw_circle, canvas, i)
    root.after(((7000 * (i + 1)) + 5000), canvas.delete, 'all')    

root.after(41000, root.destroy)
root.mainloop()