from PyQt5.QtWidgets import QApplication
from modelToDo import TodoModel
from viewToDo import TodoView
from controllerToDo import TodoController

if __name__ == '__main__':
    app = QApplication([])
    model = TodoModel()
    view = TodoView()
    controller = TodoController(model, view)
    view.show()
    app.exec_()

