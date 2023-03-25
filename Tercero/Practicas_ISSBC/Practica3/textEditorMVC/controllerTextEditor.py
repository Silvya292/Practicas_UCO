#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar 16 08:54:51 2023

@author: Silvia Roldán
"""
import modelTextEditor as model

def saveFile(self):
    data = model.saveFile(self)
    return data


def saveAsFile(self):
    data = model.saveAsFile(self)
    return data

def doubleClickedTreeView(self, index):
    data = model.doubleClickedTreeView(self, index)
    return data


def openFolder(self):
    data = model.openFolder(self)
    return data

