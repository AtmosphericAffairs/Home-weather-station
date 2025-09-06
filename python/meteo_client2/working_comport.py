from PyQt6 import QtCore
import serial
import serial.tools
import serial.tools.list_ports


class Working_comport(QtCore.QThread):
    connect = QtCore.pyqtSignal(bool)
    data = QtCore.pyqtSignal(str)
    def __init__(self):
        super().__init__()

    def run(self):
        ports = serial.tools.list_ports.comports()
        count = 0
        baudrate = 9600
        for port in ports:
            count += 1
            if 'USB Serial Port' in str(port):
                comports = port.device
                try:
                    ser = serial.Serial(comports, baudrate=baudrate)
                    if ser.readline().decode('utf-8') == 'i im meteo\r\n':
                        self.connect.emit(True)
                        while True:
                            line = ser.readline().decode()
                            if line:
                                self.data.emit(line)
                    else:
                        ser.close()
                except:
                    pass
            if count == len(ports):
                comports = False
                self.connect.emit(False)
        
        if comports:
            try:
                pass

            except serial.SerialException as se:
                self.connect.emit(False)

            except KeyboardInterrupt:
                pass
            finally:
                if ser.is_open:
                    ser.close()
