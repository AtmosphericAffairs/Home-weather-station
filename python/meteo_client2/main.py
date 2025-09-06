import sys

from PyQt6 import QtCore, QtWidgets
import json
from topPanel import TopPanel as Tp
from temperature_widget import Temperature_widget as Tw
from wind_widjet import Wind_widget as Ww
from pressure_widjet import Pressure_widget as Pw
from working_comport import Working_comport as Wc

class MyWindow(QtWidgets.QTabWidget):
    def __init__(self):
        super().__init__()
        self.connect_com = True

        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.start_thread)
        self.timer.start(5000)

        self.mainGL = QtWidgets.QGridLayout(self)
        self.setLayout(self.mainGL)

        self.topFrame = QtWidgets.QFrame()
        self.btnFile = QtWidgets.QPushButton(self.topFrame)
        self.btnFile.setGeometry(QtCore.QRect(0, 0, 50, 20))
        self.btnFile.setText('Файл')

        self.layut_1 = QtWidgets.QHBoxLayout()

        self.temperature_frame = QtWidgets.QFrame()
        self.wind_frame = QtWidgets.QFrame()
        self.press_frame = QtWidgets.QFrame()
        self.temperature_frame.setObjectName('main_w_f')
        self.wind_frame.setObjectName('main_w_f')
        self.press_frame.setObjectName('main_w_f')
        self.layut_1.addWidget(self.temperature_frame)
        self.layut_1.addWidget(self.wind_frame)
        self.layut_1.addWidget(self.press_frame)


        self.layut_2 = QtWidgets.QVBoxLayout()


        self.mainGL.addWidget(self.topFrame, 0, 0, 1, 0)
        self.mainGL.addLayout(self.layut_1, 1, 0, 18, 0)
        self.mainGL.addLayout(self.layut_2, 20, 0, 20, 0)

        self.tw = Tw(self.temperature_frame)
        self.ww = Ww(self.wind_frame)
        self.pw = Pw(self.press_frame)



        self.wc = Wc()

        self.wc.connect.connect(self.go_timer)
        

        self.wc.data.connect(self.processing_data)

        self.setFixedSize(1200, 800)

    def go_timer(self, bool):
        if bool:
            print('остановлен')
            self.timer.stop()
            self.connect_com = False
        else:
            if self.connect_com == False:
                print('запущен')
                self.timer.start()
                self.connect_com = True



    def start_thread(self):
            self.wc.start()

    def decoding(self, data):
        print(data)
        try:
            data = json.loads(data)
            return data
        except:
            return {"celsius" : 0, "val" : 0, "pressure" : 0}

    def adding_to_lists(self, data):
        if len(self.tw.list_temperature) >= 180:
            self.tw.list_temperature.pop(0)
        if len(self.ww.list_wind_speed) >= 180:
            self.ww.list_wind_speed.pop(0)
        if len(self.pw.list_pressure) >= 180:
            self.pw.list_pressure.pop(0)    


        self.tw.list_temperature.append(round(float(data['celsius']), 1))
        self.ww.list_wind_speed.append(round((float(data['val']))*0.0546875, 1))
        self.pw.list_pressure.append(round(float(data["pressure"]), 1))

    def processing_data(self, data):
        self.adding_to_lists(self.decoding(data))
        self.tw.print_text()
        self.ww.print_text()
        self.pw.print_text()

    def resizeEvent(self, event):
      # Переопределяем событие resize, чтобы запретить изменение размера
      # Устанавливаем размеры в начальное значение
      self.resize(self.width(), self.height())
      super().resizeEvent(event)










if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    with open("style.qss", "r") as f:
        _style = f.read()
        app.setStyleSheet(_style)
    window = MyWindow()
    window.setWindowTitle('Meteo_client')
    window.resize(1200, 800)
    window.show()
    app.exec()