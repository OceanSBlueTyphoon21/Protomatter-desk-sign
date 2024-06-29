# imports
import sys, time, serial
from PyQt6.QtWidgets import QApplication, QMainWindow
from protomattergui import Ui_main_window # Importing the Ui class from protomattergui.py



# CLASSES -------------------------------
class MyApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui=Ui_main_window()    # Instantiate a new class from protomattergui
        self.ui.setupUi(self)


    # The core interface
    # Changes the Status QLabel and sends the correct message over USB to
    # the protomatter board

        # Signals/Slots Connections
        self.ui.pushButton_0.clicked.connect(lambda: self.update_label(self.ui.pushButton_0))
        self.ui.pushButton_1.clicked.connect(lambda: self.update_label(self.ui.pushButton_1))
        self.ui.pushButton_2.clicked.connect(lambda: self.update_label(self.ui.pushButton_2))
        self.ui.pushButton_3.clicked.connect(lambda: self.update_label(self.ui.pushButton_3))
        self.ui.pushButton_4.clicked.connect(lambda: self.update_label(self.ui.pushButton_4))
        self.ui.pushButton_5.clicked.connect(lambda: self.update_label(self.ui.pushButton_5))
        self.ui.pushButton_6.clicked.connect(lambda: self.update_label(self.ui.pushButton_6))

        self.ui.pushButton.clicked.connect(self.connect2device)

    # function for USB connection
    def connect2device(self):
        com_port = self.ui.lineEdit.text()
        try:
            self.serial_connection = serial.Serial(com_port, 9600, timeout=1)
            self.ui.label_4.setText(f"Connect to {com_port}")
        except serial.SerialException: # close the GUI if no connection is found.
            quit()


    # USB Sending connection
    def send_message(self, message):
        self.serial_connection.write(message.encode())
    

    # Status QLabel updater function
    def update_label(self, button):
        if button==self.ui.pushButton_0:
            self.ui.label_2.setText("Tektronix")
            self.send_message("0")

        elif button==self.ui.pushButton_1:
            self.ui.label_2.setText("Available")
            self.send_message("1")

        elif button==self.ui.pushButton_2:
            self.ui.label_2.setText("Busy")
            self.send_message("2")

        elif button==self.ui.pushButton_3:
            self.ui.label_2.setText("Away")
            self.send_message("3")

        elif button==self.ui.pushButton_4:
            self.ui.label_2.setText("In Meeting")
            self.send_message("4")

        elif button==self.ui.pushButton_5:
            self.ui.label_2.setText("Music/Podcast")
            self.send_message("5")

        elif button==self.ui.pushButton_6:
            self.ui.label_2.setText("")
            self.send_message("6")
        

# _____________ MAIN RUN CODE ________________

if __name__=='__main__':
    testapp=QApplication(sys.argv)
    window=MyApp() # instantiate the GUI class, Forms the GUI 

    # show the GUI
    window.show()

    # close the GUI and disconnect the USB connection with protomatter board.
    sys.exit(testapp.exec())
