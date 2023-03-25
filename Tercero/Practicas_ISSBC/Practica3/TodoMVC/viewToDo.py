from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QListWidget, QLineEdit, QPushButton
from PyQt5.QtCore import Qt

class TodoView(QWidget):
    def __init__(self):
        super().__init__()
        self.tasks_list = QListWidget()
        self.tasks_list.setMaximumWidth(300)
        self.task_input = QLineEdit()
        self.add_button = QPushButton('Añadir')
        self.remove_button = QPushButton('Borrar')
        self.init_ui()

        self.setWindowTitle("MVC TODO list")
        self.show()

    def init_ui(self):
        vlayout = QVBoxLayout()
        hlayout = QHBoxLayout()
        hlayout.addWidget(self.task_input)
        hlayout.addWidget(self.add_button)
        vlayout.addWidget(self.tasks_list)
        vlayout.addLayout(hlayout)
        vlayout.addWidget(self.remove_button)
        self.setLayout(vlayout)

    def get_task(self):
        return self.task_input.text()

    def clear_task_input(self):
        self.task_input.clear()

    def get_selected_task(self):
        selected = self.tasks_list.currentItem()
        if selected:
            return selected.text()

    def set_tasks(self, tasks):
        self.tasks_list.clear()
        for task in tasks:
            self.tasks_list.addItem(task)
