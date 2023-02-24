#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Feb 20 08:19:46 2023

@author: Silvia Roldán
"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget


def main():

    app = QApplication(sys.argv)

    w = QWidget()
    w.resize(250, 150)
    w.move(300, 300)
    w.setWindowTitle('Nueva ventana')
    w.show()

    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
    
    
    