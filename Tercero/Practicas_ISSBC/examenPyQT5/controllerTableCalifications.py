import modelTableCalifications as mapp

# Eventos de la tabla de calificaciones
def eventOrdAlumnos(self):
    mapp.ordAlumnos(self)

def eventSelectAlumnos(self):
    mapp.selectAlumnos(self)   

def eventAddAlumnos(self):
    mapp.addAlumnos(self)

def eventDeleteAlumnos(self):
    mapp.deleteAlumnos(self)

def eventSaveAs(self):
    mapp.saveAs(self)

def eventOpenFile(self):
    mapp.openFile(self)

def eventCellChanged(self, row, column):
    mapp.cell_changed(self, row, column)