#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Mar  1 13:25:25 2023

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
        self.path = None
        self.txt = QTextEdit()
        self.setCentralWidget(self.txt)
        self.statusBar()
        
        newFile = QAction(QIcon('new.png'), 'Nuevo archivo', self)
        newFile.setShortcut('Ctrl+N')
        newFile.setStatusTip('Nuevo archivo')
        newFile.triggered.connect(self.newFile)
        
        openFile = QAction(QIcon('open.png'), 'Abrir archivo', self)
        openFile.setShortcut('Ctrl+O')
        openFile.setStatusTip('Abrir archivo')
        openFile.triggered.connect(self.openFile)
        
        saveFile = QAction(QIcon('save.png'),'Guardar', self)
        saveFile.setShortcut('Ctrl+G')
        saveFile.setStatusTip('Guardar archivo')
        saveFile.triggered.connect(self.saveFile)
        
        saveFileAs = QAction(QIcon('saveAs.png'),'Guardar como', self)
        saveFileAs.setShortcut('Ctrl+S')
        saveFileAs.setStatusTip('Guardar archivo como')
        saveFileAs.triggered.connect(self.saveFileAs)
        
        exitAct = QAction(QIcon('exit.png'), 'Salir', self)
        exitAct.setShortcut('Ctrl+Q')
        exitAct.setStatusTip('Salir')
        exitAct.triggered.connect(self.close)
        
        menubar = self.menuBar()
        fileMenu = menubar.addMenu("&Archivo")
        fileMenu.addAction(newFile)
        fileMenu.addAction(openFile)
        fileMenu.addAction(saveFile)
        fileMenu.addAction(saveFileAs)
        fileMenu.addAction(exitAct)

        self.setGeometry(300, 300, 500, 400)
        self.setWindowTitle("Editor de textos")
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
            
    def newFile(self):
        self.txt.clear()
    
    def openFile(self):
        home_dir = str(Path.home())
        fname = QFileDialog.getOpenFileName(self, 'Abrir archivo', home_dir)

        if fname[0]:
            f = open(fname[0], 'r')
            with f:
                data = f.read()
                self.txt.setText(data)
                self.path = fname
                self.setWindowTitle(fname[0])
                
    def saveFile(self):
        if self.path is None:
            return self.saveFileAs()
        self.save_path()
        
    def saveFileAs(self):
        fname = QFileDialog.getSaveFileName(self, "Guardar archivo")
        if fname[0]:
            f = open(fname[0], "w")
            with f:
                data = self.txt.toPlainText()
                f.write(data)
                f.close()
                self.path = fname
                self.setWindowTitle(fname[0])
    
    def save_path(self):
        text = self.txt.toPlainText()
        with open(self.path[0], "w") as f:
            f.write(text)

def main():
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()

