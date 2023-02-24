#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Feb 23 10:21:52 2023

@author: Silvia Roldán
"""
import sys
from PyQt5.QtWidgets import (QWidget, QDesktopWidget, QApplication, 
                             QPushButton, QToolTip, QMessageBox)
from PyQt5.QtGui import QFont


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):

        self.resize(400, 200)
        self.center()
        
        QToolTip.setFont(QFont('SansSerif', 10))
        self.setToolTip('Botón para cerrar la ventana')
        
        qbtn = QPushButton('Salir', self)
        qbtn.clicked.connect(QApplication.instance().quit)
        qbtn.resize(qbtn.sizeHint())
        qbtn.move(160, 80)

        self.setWindowTitle('Ejemplo')
        self.show()
        

    def center(self):

        qr = self.frameGeometry()
        cp = QDesktopWidget().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())
        
    def closeEvent(self, event):

        reply = QMessageBox.question(self, 'Mensaje',
                                     "Estás seguro de que deseas salir?", QMessageBox.Yes |
                                     QMessageBox.No, QMessageBox.No)
        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()


def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
