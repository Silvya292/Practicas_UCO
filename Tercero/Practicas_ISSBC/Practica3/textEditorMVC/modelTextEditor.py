#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 16 08:56:09 2023

@author: Silvia Roldán
"""
from PyQt5.QtWidgets import QFileDialog
from pathlib import Path
import os.path

def saveFile(self):
    if self.fileName == ["Editor de texto", ".txt"]:
        saveAsFile(self)
    else:
        f = open(self.fileName[0], "w")
        filedata = self.textEdit.toPlainText()
        f.write(filedata)
        f.close()

def saveAsFile(self):
    home = str(Path.home())
    newFileName = QFileDialog.getSaveFileName(self, "Save File", home)
    if newFileName[0]:
        self.fileName = newFileName
        f = open(self.fileName[0], "w")
        filedata = self.textEdit.toPlainText()
        f.write(filedata)
        f.close()

def doubleClickedTreeView(self, index):
    item = self.fileSystemModel.index(index.row(), 0, index.parent())
    self.fileName[0] = self.fileSystemModel.filePath(item)

    if os.path.isdir(self.fileName[0]) == False:
        f = open(self.fileName[0], "r")
        with f:
            data = f.read()
            return data

def openFolder(self):
    folder = str(QFileDialog.getExistingDirectory(self, "Select Directory"))
    return folder

