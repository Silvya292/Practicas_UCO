import sys
from PyQt5 import QtWidgets
import viewTableCalifications as view

app = QtWidgets.QApplication(sys.argv) #Crea una aplicación
form = view.TableCalificationsDlg()   #Crea una instancia del formulario
sys.exit(app.exec_())   #Se inicia la aplicación y se espera eventos