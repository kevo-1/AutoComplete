#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent, DataFetcher& df)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , service(df)
{
    ui->setupUi(this);

    // Connect buttons
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::onAddWord);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::onRemoveWord);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onFileUpload);
    connect(ui->pushButton,   &QPushButton::clicked, this, &MainWindow::onSaveFile);

    // Connect radio buttons
    connect(ui->radioButton_2, &QRadioButton::clicked, this, &MainWindow::onSortAlphabetical);
    connect(ui->radioButton_3, &QRadioButton::clicked, this, &MainWindow::onSortByLength);
    connect(ui->radioButton,   &QRadioButton::clicked, this, &MainWindow::onSortByFrequency);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddWord() {
    QString word = ui->lineEdit->text();
    this->service.addWord(word.toStdString());
}

void MainWindow::onRemoveWord() {
}

void MainWindow::onFileUpload(){

}

void MainWindow::onSaveFile() {

}

void MainWindow::onSortAlphabetical() {

}

void MainWindow::onSortByLength()
{

}

void MainWindow::onSortByFrequency()
{

}

void MainWindow::updateListDisplay() {

}
