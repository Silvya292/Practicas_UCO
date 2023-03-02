#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Mar  1 11:57:25 2023

@author: Silvia Roldán
"""
import sys
from PyQt5.QtWidgets import (QMainWindow, QTextEdit, QAction, 
                             QApplication, QFileDialog, QMessageBox)
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt
from pathlib import Path

class Example(QMainWindow):

    def __init__(self):
        super().__init__()
        self.initUI()


    def initUI(self):
        self.textEdit = QTextEdit()
        self.setCentralWidget(self.textEdit)
        self.statusBar()
        
        exitAct = QAction(QIcon('exit.png'), 'Salir', self)
        exitAct.setShortcut('Ctrl+Q')
        exitAct.setStatusTip('Salir')
        exitAct.triggered.connect(self.close)
        
        openFile = QAction(QIcon('open.png'), 'Abrir archivo', self)
        openFile.setShortcut('Ctrl+O')
        openFile.setStatusTip('Abrir archivo')
        openFile.triggered.connect(self.showDialog)

        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&Archivo')
        fileMenu.addAction(openFile)
        fileMenu.addAction(exitAct)

        toolbar = self.addToolBar('Abrir')
        toolbar.addAction(openFile)
        toolbar.addAction(exitAct)

        self.setGeometry(300, 300, 500, 400)
        self.setWindowTitle('Aplicación Simple')
        self.show()
        
    def closeEvent(self, event):
        reply = QMessageBox.question(self, 'Advertencia',
                                     "¿Seguro que quieres salir?", QMessageBox.Yes |
                                     QMessageBox.No, QMessageBox.No)
        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()
        
    def keyPressEvent(self, e):
        if e.key() == Qt.Key_Escape:
            self.close()
            
    def showDialog(self):
        home_dir = str(Path.home())
        fname = QFileDialog.getOpenFileName(self, 'Abrir archivo', home_dir)

        if fname[0]:
            f = open(fname[0], 'r')
            with f:
                data = f.read()
                self.textEdit.setText(data)

def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()

