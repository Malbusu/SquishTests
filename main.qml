import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: qsTr("Task Manager")

    property int taskSelected: -1
    property string filter: "all"

    header: ToolBar {
        GridLayout {
                id: headerBar
                columns: 5
                anchors.fill: parent
            ToolButton {
                objectName: "btnAddTask"
                text: "Add Task"
                Layout.fillWidth: true
                onClicked: newTaskDialog.open()
            }

            ToolButton {
                objectName: "btnShowAll"
                text: "All"
                Layout.fillWidth: true
                onClicked: taskFilterModel.filter = "all"
            }
            ToolButton {
                objectName: "btnShowActive"
                text: "Active"
                Layout.fillWidth: true
                onClicked: taskFilterModel.filter = "active"
            }
            ToolButton {
                objectName: "btnShowCompleted"
                text: "Completed"
                Layout.fillWidth: true
                onClicked: taskFilterModel.filter = "completed"
            }

            ToolButton {
                objectName: "btnShowStats"
                text: "Statistics"
                Layout.fillWidth: true
                onClicked: Qt.callLater(function() { backend.showStatistics() })
            }
        }
    }

    ListView {
        id: tasksList
        objectName: "listTasks"
        anchors.fill: parent
        anchors.topMargin: header
        model: taskFilterModel
        delegate: Rectangle {
            width: ListView.view ? ListView.view.width : 0
            height: 50
            color: model.completed ? "#cfc" : "#fff"

            Row {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 10

                CheckBox {
                    id: check
                    objectName: "checkCompleted"
                    checked: model.completed
                    onClicked: taskFilterModel.editTaskCompleted(index, checked)
                }
                Item {
                    width: textElement.paintedWidth
                    height: parent.height

                    Text {
                        id: textElement
                        text: model.name
                        font.pointSize: 14
                    }

                    MouseArea {
                        objectName: "areaTaskName"
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            editName.text = model.name
                            editCheck.checked = check.checked
                            taskSelected = index
                            editTaskDialog.open()
                        }
                    }
                }
            }
        }
    }

    Dialog {
        id: newTaskDialog
        modal: true
        title: "New Task"
        visible: false
        anchors.centerIn: parent
        ColumnLayout {
            spacing: 10
            TextField {
                id: nameField
                objectName: "txtAddTask"
                placeholderText: "Name of the Task"
            }
            Button {
                objectName: "btnSaveAdd"
                text: "Save"
                onClicked: {
                    if (nameField.text.length === 0){
                        newTaskDialog.close()
                        return
                    }
                    taskFilterModel.addTask(nameField.text);
                    nameField.text = ""
                    newTaskDialog.close()
                }
            }
        }
    }

    Dialog {
        id: editTaskDialog
        modal: true
        title: "Edit Task"
        visible: false
        anchors.centerIn: parent
        ColumnLayout {
            spacing: 10
            RowLayout {
                Label {
                    text: "Name:"
                    Layout.alignment: Qt.AlignLeft
                    Layout.preferredWidth: 100
                }
                TextField {
                    id: editName
                    objectName: "txtEditName"
                    placeholderText: "Name of the Task"
                }
                    }
            RowLayout {
                Label {
                    text: "Completed:"
                    Layout.alignment: Qt.AlignLeft
                    Layout.preferredWidth: 100
                }
                CheckBox {
                    id: editCheck
                    objectName: "checkEditCompleted"
                }
            }
            RowLayout {
                Layout.alignment: Qt.AlignCenter
                Button {
                    objectName: "btnSaveEdit"
                    text: "Save"
                    enabled: editName.text.length > 0
                    onClicked: {
                        taskFilterModel.editTaskName(editName.text, taskSelected)
                        taskFilterModel.editTaskCompleted(taskSelected, editCheck.checked)
                        editTaskDialog.close()
                    }
                }
                Button {
                    text: "Remove"
                    objectName: "btnRemoveTask"
                    onClicked: {
                        editTaskDialog.close()
                        Qt.callLater(function() {
                        taskFilterModel.removeTask(taskSelected)
                        })
                    }
                }
                Button {
                    objectName: "btnCancel"
                    text: "Cancel"
                    onClicked: {
                        editTaskDialog.close()
                    }
                }
            }
        }
    }
}
