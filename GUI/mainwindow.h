#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../SRC/BFF/BFF.h"
#include "../Utilities/Data_Fetching/DataFetcher.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, DataFetcher& df);
    ~MainWindow();
    BFF service;
private slots:
    void onAddWord();
    void onRemoveWord();
    void onFileUpload();
    void onSaveFile();
    void onSortAlphabetical();
    void onSortByLength();
    void onSortByFrequency();

private:
    Ui::MainWindow *ui;
    void updateListDisplay();
    QMap<QString, int> wordFrequency;
};

#endif // MAINWINDOW_H
