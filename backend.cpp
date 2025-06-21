#include "Backend.h"
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

Backend::Backend(QObject* parent) : QObject(parent) {
}

void Backend::mostrarVentanaWidgets() {
    QWidget* ventana = new QWidget;
    ventana->setWindowTitle("Ventana QtWidgets");
    ventana->resize(300, 100);

    QVBoxLayout* layout = new QVBoxLayout(ventana);
    QLabel* label = new QLabel("Esta es una ventana usando QtWidgets", ventana);
    layout->addWidget(label);

    ventana->setLayout(layout);
    ventana->show();
}
