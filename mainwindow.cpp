#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Conectar el explorador de archivos local al QTreeView
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(QDir::homePath());
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files);

    ui->treeView->setModel(fileModel);
    ui->treeView->setRootIndex(fileModel->index(QDir::currentPath()));

    // Ocultar columnas de peso, tipo y fecha
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    // Proporciones de los paneles
    ui->splitter_2->setSizes({220, 780});
    ui->splitter->setSizes({450, 150});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Compilar_triggered()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("=== Compilando con g++ ===");

    // Obtener texto del editor activo
    QString codigo = ui->plainTextEdit_2->toPlainText();

    QString archivoFuente = "temp_run.cpp";
    QFile file(archivoFuente);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << codigo;
        file.close();
    }

    compileProcess = new QProcess(this);

    connect(compileProcess, &QProcess::readyReadStandardError, [this]() {
        ui->plainTextEdit->appendPlainText(compileProcess->readAllStandardError());
    });

    connect(compileProcess, &QProcess::readyReadStandardOutput, [this]() {
        ui->plainTextEdit->appendPlainText(compileProcess->readAllStandardOutput());
    });

    compileProcess->start("g++", QStringList() << archivoFuente << "-o" << "temp_run");
}
