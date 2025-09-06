from PyQt6 import QtCore, QtWidgets, QtGui
import matplotlib.pyplot as plt
from matplotlib.ticker import FormatStrFormatter

class Pressure_widget(QtWidgets.QTableWidget):
    def __init__(self, frame):
        super().__init__()
        self.list_pressure = []

        font_press = QtGui.QFont()
        font_press.setPointSize(24)
        font_name = QtGui.QFont()
        font_name.setPointSize(22)

        self.vertLayot = QtWidgets.QVBoxLayout(frame)
        self.vertLayot2 = QtWidgets.QVBoxLayout()
        self.horLayot = QtWidgets.QHBoxLayout()
        self.horLayot_2 = QtWidgets.QHBoxLayout()

        self.name_block_lbl = QtWidgets.QLabel()
        self.name_block_lbl.setText('Атмосферное давление:')
        self.name_block_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
        self.name_block_lbl.setFont(font_name)

        self.pressure_lbl = QtWidgets.QLabel()
        self.pressure_lbl.setFont(font_press)

        self.pressure_lbl.setAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)

        self.vertLayot2.addWidget(self.name_block_lbl)
        self.vertLayot2.addWidget(self.pressure_lbl)
        self.vertLayot2.addLayout(self.horLayot_2)
        self.vertLayot2.addLayout(self.horLayot)
        self.vertLayot.addLayout(self.vertLayot2)

        self.figure, self.ax = plt.subplots(figsize=(0.1, 1.85))
        self.drawing_graphics()
        self.pressure_lbl.setText('гПа')
        
    def print_text(self):
        self.pressure_lbl.setText(str(self.list_pressure[-1]) + 'гПа')
        self.drawing_graphics()
    def drawing_graphics(self):
        self.ax.clear()
        self.ax.plot(self.list_pressure, color='red')
        self.ax.yaxis.set_major_formatter(FormatStrFormatter('%.0f'))
        self.ax.set_xticks([0, 60, 120, 180])  

        self.ax.set_xticklabels(['0ч', '1ч', '2ч', '3ч']) 
        self.canvas = self.figure.canvas
        self.canvas.draw()

        self.vertLayot.addWidget(self.canvas, alignment=QtCore.Qt.AlignmentFlag.AlignTop)

    