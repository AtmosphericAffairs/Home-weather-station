from PyQt6 import QtCore, QtWidgets, QtGui
import numpy as np
import matplotlib.pyplot as plt

class Wind_widget(QtWidgets.QTableWidget):
    def __init__(self, frame):
        super().__init__()
        self.list_wind_speed = []

        font_wind = QtGui.QFont()
        font_wind.setPointSize(24)
        font_wind_max = QtGui.QFont()
        font_wind_max.setPointSize(20)
        font_name = QtGui.QFont()
        font_name.setPointSize(22)

        self.frame_1 = QtWidgets.QFrame()
        self.frame_2 = QtWidgets.QFrame()
        self.frame_3 = QtWidgets.QFrame()
        self.frame_4 = QtWidgets.QFrame()

        self.vertLayot = QtWidgets.QVBoxLayout(frame)
        self.vertLayot2 = QtWidgets.QVBoxLayout()
        self.horLayot = QtWidgets.QHBoxLayout()
        self.horLayot_2 = QtWidgets.QHBoxLayout()

        self.name_block_lbl = QtWidgets.QLabel()
        self.name_block_lbl.setText('Скорость ветра:')
        self.name_block_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.name_block_lbl.setFont(font_name)

        self.wind_lbl = QtWidgets.QLabel()
        self.wind_lbl.setFont(font_wind)

        self.name_max_wind_lbl = QtWidgets.QLabel()
        self.name_max_wind_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)

        self.max_wind_lbl = QtWidgets.QLabel()
        self.max_wind_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.max_wind_lbl.setFont(font_wind_max)

        self.wind_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)

        self.horLayot_2.addWidget(self.name_max_wind_lbl)

        self.horLayot.addWidget(self.max_wind_lbl)

        self.vertLayot2.addWidget(self.name_block_lbl)
        self.vertLayot2.addWidget(self.wind_lbl)
        self.vertLayot2.addLayout(self.horLayot_2)
        self.vertLayot2.addLayout(self.horLayot)
        self.vertLayot2.addWidget(self.frame_1)
        self.vertLayot2.addWidget(self.frame_2)
        self.vertLayot2.addWidget(self.frame_3)
        self.vertLayot2.addWidget(self.frame_4)
        self.vertLayot.addLayout(self.vertLayot2)

        self.name_max_wind_lbl.setText('Максимальный порыв за 3ч')

        self.wind_lbl.setText('м/с')
        self.max_wind_lbl.setText('м/с')
        
    def print_text(self):
        self.wind_lbl.setText(str(round(sum(self.list_wind_speed[-10:])/len(self.list_wind_speed[-10:]), 1)) + 'м/с')
        self.max_wind_lbl.setText(str(max(self.list_wind_speed)) + 'м/с')