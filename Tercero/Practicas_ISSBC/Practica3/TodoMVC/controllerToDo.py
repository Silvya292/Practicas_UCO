from PyQt5.QtCore import QObject, pyqtSlot
from modelToDo import TodoModel
from viewToDo import TodoView

class TodoController(QObject):
    def __init__(self, model, view):
        super().__init__()
        self.model = model
        self.view = view
        self.connect_signals()

    def connect_signals(self):
        self.view.add_button.clicked.connect(self.add_task)
        self.view.remove_button.clicked.connect(self.remove_task)
        self.view.tasks_list.itemDoubleClicked.connect(self.remove_task)

    @pyqtSlot()
    def add_task(self):
        task = self.view.get_task()
        if task:
            self.model.add_task(task)
            self.view.clear_task_input()
            self.view.set_tasks(self.model.tasks)

    @pyqtSlot()
    def remove_task(self):
        task = self.view.get_selected_task()
        if task:
            self.model.remove_task(task)
            self.view.set_tasks(self.model.tasks)

