#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 16 08:51:01 2023

@author: Silvia Roldán
"""
import sys
import controllerTextEditor as controller
from PyQt5.QtWidgets import QWidget, QApplication, QLabel, QLineEdit, QPushButton, QTextEdit, QMessageBox, QVBoxLayout, QHBoxLayout, QGridLayout, QFileSystemModel, QTreeView

class textEditorDlg(QWidget):
    def __init__(self):
        super().__init__()
        self.fileName = ["Editor de texto", ".txt"]
        self.initUI()

    def initUI(self):
        folderSectionTitle = QLabel("Carpeta")
        self.fileFolder = QLineEdit()
        self.fileFolder.setReadOnly(True)
        self.selectButton = QPushButton("Seleccionar")

        filesSectionTitle = QLabel("Archivos")
        self.fileTree = QTreeView()
        self.fileSystemModel = QFileSystemModel(self.fileTree)
        self.fileSystemModel.setReadOnly(True)
        modelRoot = self.fileSystemModel.setRootPath("/home")
        self.fileTree.setModel(self.fileSystemModel)
        self.fileTree.setRootIndex(modelRoot)
        self.fileTree.hideColumn(1)
        self.fileTree.hideColumn(2)
        self.fileTree.hideColumn(3)
        self.fileTree.setHeaderHidden(True)

        self.textEdit = QTextEdit()

        self.saveButton = QPushButton("Guardar")
        self.saveAsButton = QPushButton("Guardar como")
        
        hbox = QHBoxLayout()
        hbox.addWidget(folderSectionTitle)
        hbox.addWidget(self.fileFolder)
        hbox.addWidget(self.selectButton)
        
        vbox = QVBoxLayout()
        vbox.setSpacing(30)
        vbox.addLayout(hbox)

        grid = QGridLayout()
        grid.setSpacing(10)
        grid.addWidget(filesSectionTitle, 0, 0)
        grid.addWidget(self.fileTree, 1, 0, 1, 3)
        grid.addWidget(self.textEdit, 1, 3, 1, 5)
        vbox.addLayout(grid)

        self.buttomsLayout = QHBoxLayout()
        self.buttomsLayout.addWidget(self.saveButton)
        self.buttomsLayout.addWidget(self.saveAsButton)
        self.buttomsLayout.addStretch()
        vbox.addLayout(self.buttomsLayout)

        self.setLayout(vbox)
        self.setWindowTitle("Editor de texto")
        self.setGeometry(300, 150, 1000, 700)
        self.show()

        self.selectButton.clicked.connect(self.openFolders)
        self.fileTree.doubleClicked.connect(self.doubleClickedTreeView)
        self.saveButton.clicked.connect(self.saveFiles)
        self.saveAsButton.clicked.connect(self.saveAsFiles)

    def openFolders(self):
        directory = controller.openFolder(self)
        modelRoot = self.fileSystemModel.setRootPath(directory)
        self.fileTree.setRootIndex(modelRoot)
        self.fileFolder.setText(directory)

    def doubleClickedTreeView(self, index):
        filedata = controller.doubleClickedTreeView(self, index)
        self.textEdit.setText(filedata)

    def saveFiles(self):
        controller.saveFile(self)

    def saveAsFiles(self):
        controller.saveAsFile(self)

    def closeEvent(self, event):
        reply = QMessageBox.question(self, "Mensaje", "¿Estás seguro que deseas salir?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        if reply == QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = textEditorDlg()
    sys.exit(app.exec_())