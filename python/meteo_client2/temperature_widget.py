from PyQt6 import QtCore, QtWidgets, QtGui
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter

class Temperature_widget(QtWidgets.QTableWidget):
    def __init__(self, frame):
        super().__init__()
        self.list_temperature = []

        font_temp = QtGui.QFont()
        font_temp.setPointSize(24)
        font_temp_min_and_max = QtGui.QFont()
        font_temp_min_and_max.setPointSize(20)
        font_name = QtGui.QFont()
        font_name.setPointSize(22)

        self.vertLayot = QtWidgets.QVBoxLayout(frame)
        self.vertLayot2 = QtWidgets.QVBoxLayout()
        self.horLayot = QtWidgets.QHBoxLayout()
        self.horLayot_2 = QtWidgets.QHBoxLayout()

        self.name_block_lbl = QtWidgets.QLabel()
        self.name_block_lbl.setText('Температура воздуха:')
        self.name_block_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.name_block_lbl.setFont(font_name)

        self.temperature_lbl = QtWidgets.QLabel()
        self.temperature_lbl.setFont(font_temp)

        self.name_min_temp_lbl = QtWidgets.QLabel()
        self.name_max_temp_lbl = QtWidgets.QLabel()
        self.name_min_temp_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.name_max_temp_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)

        self.min_temperature_lbl = QtWidgets.QLabel()
        self.min_temperature_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.min_temperature_lbl.setFont(font_temp_min_and_max)

        self.max_temperature_lbl = QtWidgets.QLabel()
        self.max_temperature_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.max_temperature_lbl.setFont(font_temp_min_and_max)

        self.temperature_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)

        self.horLayot_2.addWidget(self.name_min_temp_lbl)
        self.horLayot_2.addWidget(self.name_max_temp_lbl)

        self.horLayot.addWidget(self.min_temperature_lbl)
        self.horLayot.addWidget(self.max_temperature_lbl)

        self.vertLayot2.addWidget(self.name_block_lbl)
        self.vertLayot2.addWidget(self.temperature_lbl)
        self.vertLayot2.addLayout(self.horLayot_2)
        self.vertLayot2.addLayout(self.horLayot)
        self.vertLayot.addLayout(self.vertLayot2)

        self.name_min_temp_lbl.setText('Минимальная за 3ч')
        self.name_max_temp_lbl.setText('Максимальная за 3ч')

        self.figure, self.ax = plt.subplots(figsize=(1.8, 1.85))
        self.drawing_graphics()
        self.temperature_lbl.setText('C°')
        self.min_temperature_lbl.setText('C°')
        self.max_temperature_lbl.setText('C°')
        
    def print_text(self):
        self.temperature_lbl.setText(str(self.list_temperature[-1]) + 'C°')
        self.min_temperature_lbl.setText(str(min(self.list_temperature)) + 'C°')
        self.max_temperature_lbl.setText(str(max(self.list_temperature)) + 'C°')
        self.drawing_graphics()
    def drawing_graphics(self):
        self.ax.clear()
        self.ax.plot(self.list_temperature, color='red')
        self.ax.yaxis.set_major_formatter(FormatStrFormatter('%.1f'))
        self.ax.set_xticks([0, 60, 120, 180])  

        self.ax.set_xticklabels(['0ч', '1ч', '2ч', '3ч']) 
        self.canvas = self.figure.canvas
        self.canvas.draw()

        self.vertLayot.addWidget(self.canvas, alignment=QtCore.Qt.AlignmentFlag.AlignTop)

    


        



