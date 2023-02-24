#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Feb 20 08:38:18 2023

@author: Silvia Roldán
"""

import sys
from PyQt5.QtWidgets import (QWidget, QToolTip,
    QPushButton, QApplication)
from PyQt5.QtGui import QFont


class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()


    def initUI(self):

        QToolTip.setFont(QFont('SansSerif', 10))

        self.setToolTip('Ayuda emergente')

        btn = QPushButton('Botón', self)
        btn.setToolTip('Ayuda emergente')
        btn.resize(btn.sizeHint())
        btn.move(50, 50)

        self.setGeometry(400, 400, 500, 200)
        self.setWindowTitle('Nueva ventana con ayudas emergentes')
        self.show()


def main():

    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
    
    