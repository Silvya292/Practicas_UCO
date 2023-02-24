#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Feb 23 10:41:58 2023

@author: Silvia Roldán
"""
import sys
from PyQt5.QtWidgets import (QMainWindow, QTextEdit, QAction, 
                             QApplication, QMenu, qApp)
from PyQt5.QtGui import QIcon


class Example(QMainWindow):

    def __init__(self):
        super().__init__()
        self.initUI()


    def initUI(self):
        exitAct = QAction(QIcon('exit.png'), 'Salir', self)
        exitAct.setShortcut('Ctrl+Q')
        exitAct.setStatusTip('Salir')
        exitAct.triggered.connect(self.close)

        self.statusBar()

        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&Archivo')
        impMenu = QMenu('Nuevo', self)
        impAct = QAction('Archivo', self)
        impMenu.addAction(impAct)
        fileMenu.addMenu(impMenu)
        fileMenu.addAction(exitAct)

        toolbar = self.addToolBar('Salir')
        toolbar.addAction(exitAct)

        self.setGeometry(300, 300, 350, 250)
        self.setWindowTitle('Ventana principal')
        self.show()

    def contextMenuEvent(self, event):
        cmenu = QMenu(self)
        newAct = cmenu.addAction("Nuevo")
        openAct = cmenu.addAction("Abrir")
        quitAct = cmenu.addAction("Salir")
        action = cmenu.exec_(self.mapToGlobal(event.pos()))
        if action == quitAct:
            qApp.quit()

def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
