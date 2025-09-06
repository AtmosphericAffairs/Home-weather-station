from PyQt6 import QtCore, QtWidgets

class TopPanel(QtWidgets.QTabWidget):
    def __init__(self, mainwindow):
        super().__init__()
        self.mainVlayot = QtWidgets.QBoxLayout(mainwindow)
        self.btnFile = QtWidgets.QPushButton('Файл')

        