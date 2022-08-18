#creare interfaccia grafica con bottone start, stop e un menù a tendina per selezionare la porta seriale
#https://www.tutorialspoint.com/how-to-stop-a-loop-with-a-stop-button-in-tkinter

import tkinter as tk
import serial.tools.list_ports
import serial
import threading
from datetime import datetime

file = open("mouseHandler/mouse-data.csv", "w", encoding="utf-8")
file.write("Timestamp,dX,dY,X,Y\n")
endFlag = False
ser = 0

#lettura delle porte aperte
ports = serial.tools.list_ports.comports()
portList = []
for onePort in ports:
    portList.append(str(onePort))

def end():
    global endFlag
    global ser
    print("End")
    endFlag = True
    ser.close()
    if start_thread.is_alive():
        start_thread.join()
    file.close()
    window.destroy()
    quit()

def start():
    global endFlag
    global ser
    port = selection.get()[:selection.get().index(" ")]
    print("Start with port " + port)
    ser = serial.Serial(port, 9600)
    endFlag = 0
    x = y = 0
    while not endFlag and ser.is_open:
        timestamp = str(datetime.now())[11:]
        data = ""
        data = str(ser.readline())[2:-5]
        if data != "" and "start" not in data.lower():
            x += int(data[:data.index(",")])
            y += int(data[data.index(",")+1:])
        print(timestamp + " - " + data)
        file.write(timestamp + "," + data + "," + str(x) + "," + str(y) + "\n")

start_thread = threading.Thread(target=start)
def start_thread_func():
    start_thread.start()





if __name__ == "__main__":

    #creazione della finestra
    window = tk.Tk()
    window.title("Serial Reader")
    window.geometry("600x600")
    window.resizable(False, False)

    #creazione del menù a tendina
    selection = tk.StringVar(window)
    selection.set(portList[0])
    opt = tk.OptionMenu(window, selection, *portList)
    opt.grid(row= 0, column = 1)

    #creazione del bottone start
    start_button = tk.Button(window, text="Start", command=lambda: start_thread_func())
    start_button.grid(row = 0, column = 0)

    #creazione del bottone end
    end_button = tk.Button(window, text="End", command=lambda: end())
    end_button.grid(row = 1, column = 0)

    window.mainloop()
