import tkinter as tk
from tkinter import filedialog
import serial.tools.list_ports
import serial
import threading
from datetime import datetime

#lettura delle porte aperte
ports = serial.tools.list_ports.comports()
portList = []
for onePort in ports:
    portList.append(str(onePort))

end_flag = threading.Event() 
ser = serial.Serial()

def end():
    global end_flag
    global ser
    end_flag.set()#settare la variabile globale end_flag per terminare il ciclo infinito
    ser.close()
    if start_thread.is_alive():
        start_thread.join()#terminare il thread
    file.close()
    print("File saved")

def start():
    global end_flag
    global ser
    port = selection.get()[:selection.get().index(" ")]
    print("Starting with port " + port)
    ser = serial.Serial(port, 9600)
    x = y = 0
    while not end_flag.is_set() and ser.is_open:
        timestamp = datetime.now().strftime("%H:%M:%S.%f")[:-3]
        data = ""
        try:
            data = str(ser.readline())[2:-5]
        except:
            print("The port is closed")
        if data != "" and "start" not in data.lower():
            x += int(data[:data.index(",")])
            y += int(data[data.index(",")+1:])
            print(timestamp + " - " + data)
            file.write(timestamp + "," + data + "," + str(x) + "," + str(y) + "\n")

start_thread = threading.Thread(target=start)
def start_thread_func():
    start_thread.start()

def open_file():
    global file
    file_name = filedialog.asksaveasfilename(initialdir = ".",
                                          title = "Select a File",)
    file = open(file_name, "w", encoding="utf-8")
    file.write("Timestamp,dX,dY,X,Y\n")
    file.write(datetime.now().strftime("%H:%M:%S.%f")[:-3] + ",0,0,0,0\n")

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

    browse_button = tk.Button(window, text="Choose location", command=lambda: open_file())
    browse_button.grid(row = 1, column = 1)

    window.mainloop()



