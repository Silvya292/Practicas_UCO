from select import select
import sys
import controllerTableCalifications as controller

from PyQt5.QtWidgets import QWidget, QApplication, QLabel, QPushButton, QGridLayout, QTableWidget, QHeaderView

class TableCalificationsDlg(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        #Se crean ambas tablas
        self.table1 = QTableWidget(0, 2)
        self.table1.setHorizontalHeaderLabels(['Nombre', 'Nota'])
        self.table1.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
        self.table1.horizontalHeader().resizeSection(1, 100)
        
        self.table2 = QTableWidget(0, 2)
        self.table2.setHorizontalHeaderLabels(['Nombre', 'Nota'])
        self.table2.setEditTriggers(QTableWidget.NoEditTriggers)
        self.table2.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
        self.table2.horizontalHeader().resizeSection(1, 100)

        #Se crean los botones
        self.ordButton = QPushButton("Ordenar")
        self.selectButton = QPushButton("Seleccionar Aprobados")
        self.addButton = QPushButton("Añadir")
        self.deleteButton = QPushButton("Borrar")
        self.saveButton = QPushButton("Guardar")
        self.openButton = QPushButton("Abrir")

        #Se crea la cuadrícula de botones y se añaden
        grid = QGridLayout()
        grid.setSpacing(10)
        grid.addWidget(self.ordButton, 2, 0)
        grid.addWidget(self.selectButton, 2, 1)

        grid2 =QGridLayout()
        grid2.setSpacing(10)
        grid2.addWidget(self.addButton, 2, 2)
        grid2.addWidget(self.deleteButton, 2, 3)

        grid3 = QGridLayout()
        grid3.setSpacing(10)
        grid3.addWidget(self.saveButton, 2, 3)
        grid3.addWidget(self.openButton, 2, 4)

        #Se crea la cuadrícula principal y se añaden las tablas y la cuadrícula de botones
        layout = QGridLayout()
        layout.addWidget(QLabel("Lista de Notas"), 0, 0)
        layout.addWidget(QLabel("Lista de Aprobados"), 0, 1)
        layout.addWidget(self.table1, 1, 0)
        layout.addWidget(self.table2, 1, 1)
        layout.addLayout(grid, 2, 0)
        layout.addLayout(grid2, 3, 0)
        layout.addLayout(grid3, 2, 1)
        
        self.setLayout(layout)

        #Se establece el tamaño de la ventana y se muestra
        self.setGeometry(300, 300, 550, 400)
        self.setWindowTitle('Lista de Alumnos')
        self.show()

        #Se conectan los botones con los eventos
        self.ordButton.clicked.connect(self.ordAlumnos)
        self.selectButton.clicked.connect(self.selectAlumnos)
        self.addButton.clicked.connect(self.addAlumnos)
        self.deleteButton.clicked.connect(self.deleteAlumnos)
        self.saveButton.clicked.connect(self.saveAs)
        self.openButton.clicked.connect(self.openFile)

        #Se conecta la tabla con el evento para no permitir escrbir en la columna de notas un valor distinto de [0, 10]
        self.table1.cellChanged.connect(self.cell_changed)

    #Se definen los eventos
    def ordAlumnos(self):
        controller.eventOrdAlumnos(self)

    def selectAlumnos(self):
        controller.eventSelectAlumnos(self)

    def addAlumnos(self):
        controller.eventAddAlumnos(self)

    def deleteAlumnos(self):
        controller.eventDeleteAlumnos(self)

    def saveAs(self):
        controller.eventSaveAs(self)

    def openFile(self):
        controller.eventOpenFile(self)

    def cell_changed(self, row):
        controller.eventCellChanged(self, row, 1)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    form = TableCalificationsDlg()
    sys.exit(app.exec_())