#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Feb 26 19:42:28 2023

@author: Silvia Roldán
"""
import sys
from PyQt5.QtWidgets import QWidget, QLabel, QApplication


class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        lbl1 = QLabel('Posición absoluta', self)
        lbl1.move(15, 10)

        lbl2 = QLabel('de texto', self)
        lbl2.move(35, 40)

        lbl3 = QLabel('con PyQT5', self)
        lbl3.move(55, 70)

        self.setGeometry(300, 300, 400, 150)
        self.setWindowTitle('Posicionamiento absoluto')
        self.show()


def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()

