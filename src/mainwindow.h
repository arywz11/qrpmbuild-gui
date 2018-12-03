#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QTableWidgetItem>
#include <QProcess>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_addFile_clicked();

    void on_pushButton_generate_clicked();

    void on_pushButton_removeFile_clicked();

    void on_pushButton_removeAll_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
