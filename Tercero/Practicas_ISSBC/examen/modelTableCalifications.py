from pathlib import Path
from PyQt5.QtCore import QFile, QTextStream
from PyQt5.QtWidgets import QFileDialog, QTableWidgetItem

#Ordena la tabla de alumnos por nombre
def ordAlumnos(self):
    self.table1.sortItems(0, 0)

#Selecciona los alumnos aprobados y los añade a la tabla de aprobados
def selectAlumnos(self):
    for row in range(self.table2.rowCount()-1, -1, -1):
        self.table2.removeRow(row)

    for row in range(self.table1.rowCount()):
        nota = int(self.table1.item(row, 1).text())
        if nota >= 5:
            fila = []
            for column in range(self.table1.columnCount()):
                fila.append(self.table1.item(row, column).clone())
            self.table2.insertRow(self.table2.rowCount())
            for column, item in enumerate(fila):
                self.table2.setItem(self.table2.rowCount()-1, column, item)

#Añade un alumno a la tabla de alumnos
def addAlumnos(self):
    row_count = self.table1.rowCount()
    self.table1.insertRow(row_count)

#Elimina un alumno seleccionado de la tabla de alumnos
def deleteAlumnos(self):
    row = self.table1.currentRow()
    self.table1.removeRow(row)

#Guarda la tabla de alumnos en un fichero de texto
def saveAs(self):
    home = str(Path.home())
    newFileName, _ = QFileDialog.getSaveFileName(self, "Save File", home, "Text Files (*.txt)")
    
    if newFileName:
        file = QFile(newFileName)
        file.open(QFile.WriteOnly | QFile.Text)
        stream = QTextStream(file)
        for row in range(self.table1.rowCount()):
            for column in range(self.table1.columnCount()):
                item = self.table1.item(row, column)
                if item is not None:
                    stream << item.text() << "\t"
            stream << "\n"
        file.close()

#Abre un fichero de texto y lo carga en la tabla de alumnos
def openFile(self):
    home = str(Path.home())
    filename, _ = QFileDialog.getOpenFileName(self, "Open File", home, "Text Files (*.txt)")
    
    if filename:
        with open(filename, 'r') as file:
            lines = file.readlines()
            data = [line.strip().split("\t") for line in lines]
            nRows = len(data)
            nColums = len(data[0])
            self.table1.setRowCount(nRows)
            self.table1.setColumnCount(nColums)
            for row in range(nRows):
                for colum in range(nColums):
                    cell = QTableWidgetItem(data[row][colum])
                    self.table1.setItem(row, colum, cell)

#Controla que los valores introducidos en la tabla de alumnos sean correctos
def cell_changed(self, row, column):
    item = self.table1.item(row, column)
    if item is None:
        return
    value = item.text()
    try:
        value = int(value)
    except ValueError:
        self.table1.setItem(row, column, QTableWidgetItem("0"))
        return
    if value < 0 or value > 10:
        self.table1.setItem(row, column, QTableWidgetItem("0"))
        return
    item.setText(str(value))