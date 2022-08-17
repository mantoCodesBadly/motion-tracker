#creare interfaccia grafica con bottone start, stop e un menù a tendina per selezionare la porta seriale
#https://www.tutorialspoint.com/how-to-stop-a-loop-with-a-stop-button-in-tkinter

import tkinter as tk
import serial.tools.list_ports
import serial

file = open("mouse-data.csv", "w")
endFlag = False

#lettura delle porte aperte
ports = serial.tools.list_ports.comports()
portList = []
for onePort in ports:
    portList.append(str(onePort))

def end():
    print("End")
    global endFlag
    endFlag = True
    window.destroy()
    file.close()

def start():
    port = variable.get()[:variable.get().index(" ")]
    print("Start with port " + port)
    ser = serial.Serial(port, 9600)
    endFlag = 0
    while not endFlag:
        data = str(ser.readline())[2:-5]
        print(data)
        file.writelines(data) 







if __name__ == "__main__":

    #creazione della finestra
    window = tk.Tk()
    window.title("Serial Reader")
    window.geometry("600x600")
    window.resizable(False, False)

    #creazione del menù a tendina
    variable = tk.StringVar(window)
    variable.set(portList[0])
    opt = tk.OptionMenu(window, variable, *portList)
    opt.grid(row= 0, column = 1)

    #creazione del bottone start
    start_button = tk.Button(window, text="Start", command=lambda: start())
    start_button.grid(row = 0, column = 0)

    #creazione del bottone end
    end_button = tk.Button(window, text="End", command=lambda: end())
    end_button.grid(row = 1, column = 0)

    window.mainloop()