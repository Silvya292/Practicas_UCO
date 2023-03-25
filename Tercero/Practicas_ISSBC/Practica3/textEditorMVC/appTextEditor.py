#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 16 08:55:21 2023

@author: Silvia Roldán
"""
import sys
from PyQt5.QtWidgets import QApplication
import viewTextEditor as view

app = QApplication(sys.argv)
form = view.textEditorDlg()
sys.exit(app.exec_())

