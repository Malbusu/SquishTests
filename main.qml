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
        RowLayout {
            anchors.fill: parent

            ToolButton {
                text: "+"
                onClicked: newTaskDialog.open()
            }

            ToolButton {
                text: "All"
                onClicked: taskFilterModel.filter = "all"
            }
            ToolButton {
                text: "Active"
                onClicked: taskFilterModel.filter = "active"
            }
            ToolButton {
                text: "Completed"
                onClicked: taskFilterModel.filter = "completed"
            }

            ToolButton {
                text: "WindowWidget"
                onClicked: Qt.callLater(function() { backend.mostrarVentanaWidgets() })
            }
        }
    }

    ListView {
        id: tasksList
        anchors.fill: parent
        anchors.topMargin: header
        model: taskFilterModel
        delegate: Rectangle {
            width: (parent !== null) ? parent.width : 0
            height: 50
            color: model.completed ? "#cfc" : "#fff"

            Row {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 10

                CheckBox {
                    id: check
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
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            editName.text = model.name
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
                placeholderText: "Name of the Task"
            }
            Button {
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
            TextField {
                id: editName
                placeholderText: "Name of the Task"
            }
            Button {
                text: "Save"
                onClicked: {
                    if (editName.text.length === 0){
                        editTaskDialog.close()
                        return
                    }
                    taskFilterModel.editTaskName(editName.text, taskSelected)
                    editTaskDialog.close()
                }
            }
            Button {
                text: "Remove"
                onClicked: {
                    editTaskDialog.close()
                    Qt.callLater(function() {
                    taskFilterModel.removeTask(taskSelected)
                    })
                }
            }
        }
    }
}
