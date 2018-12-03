#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_addFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      QDir::homePath(),
                                                      tr("* (*)"));

    if (fileName.length() > 0) {
        QTableWidgetItem* item = new QTableWidgetItem(fileName);
        ui->tableWidget_files->setRowCount(ui->tableWidget_files->rowCount()+1);
        ui->tableWidget_files->setItem(ui->tableWidget_files->rowCount()-1, 0, item);
    }
}

void MainWindow::on_pushButton_generate_clicked()
{
    QDir pwd = QDir::homePath();
    bool ok;
    ok = pwd.mkpath("qrpmbuilds");
    QDir::setCurrent(pwd.path()+"/qrpmbuilds");
    QProcess::execute("rm -rf rpmbuild");
    ok = pwd.mkpath(QDir::currentPath()+"/rpmbuild/BUILD");
    ok = pwd.mkpath(QDir::currentPath()+"/rpmbuild/BUILDROOT");
    ok = pwd.mkpath(QDir::currentPath()+"/rpmbuild/RPMS");
    ok = pwd.mkpath(QDir::currentPath()+"/rpmbuild/SOURCES");
    ok = pwd.mkpath(QDir::currentPath()+"/rpmbuild/SPECS");
    ok = pwd.mkpath(QDir::currentPath()+"/rpmbuild/SRPMS");
    QFile file(":/template/rpmbuild-spec.template");
    if (!file.open(QFile::ReadOnly))
        qDebug()<<"open qrc file failed"<<file.errorString();
    QString spec_template = file.readAll();
    file.close();

    QString installPaths;
    for (int row=0; row<ui->tableWidget_files->rowCount(); row++){
        installPaths.append(ui->tableWidget_files->item(row, 1)->text()+"\n");

        ;
        QString rpmInstallPath = "rpmbuild/BUILDROOT/"+ui->lineEdit_name->text()
                                +"-"
                                +ui->lineEdit_version->text()
                                +"-"
                                +ui->lineEdit_release->text()
                                +"."
                                +QSysInfo::buildCpuArchitecture()
                                +ui->tableWidget_files->item(row, 1)->text();
        QFileInfo fileInfo(rpmInstallPath);
        pwd.mkpath(fileInfo.absolutePath());
        if (!QFile::copy(ui->tableWidget_files->item(row, 0)->text(),rpmInstallPath)){
            qDebug()<<"QFile::error";
        };
    }


    file.setFileName(QDir::currentPath()+"/rpmbuild/SPECS/rpmbuild.spec");
    if (file.open(QFile::WriteOnly)){
        QString spec_content = spec_template
                .arg(ui->lineEdit_summary->text())
                .arg(ui->lineEdit_name->text())
                .arg(ui->lineEdit_version->text())
                .arg(ui->lineEdit_release->text())
                .arg(ui->comboBox_license->currentText())
                .arg(ui->comboBox_group->currentText())
                .arg(ui->lineEdit_source->text())
                .arg(ui->lineEdit_url->text())
                .arg(ui->lineEdit_Distribution->text())
                .arg(ui->lineEdit_packager->text())
                .arg(QSysInfo::buildCpuArchitecture())
                .arg(ui->textEdit_description->toPlainText())
                .arg(installPaths);
        file.write(spec_content.toLocal8Bit());
    }
    else {
        QMessageBox::warning(this, "create "+file.fileName()+"failed", file.errorString());
        return;
    }
    file.close();

    QProcess* cmd = new QProcess(this);
    cmd->setWorkingDirectory(QDir::currentPath());
    QString def("--define=_topdir "+QDir::currentPath()+"/rpmbuild");
    ui->statusBar->showMessage("Run command:rpmbuild "+def+" -bb"+" rpmbuild/SPECS/rpmbuild.spec");
    cmd->start("rpmbuild", QStringList()<<def <<"-bb"<<"rpmbuild/SPECS/rpmbuild.spec");
    cmd->waitForStarted();
    cmd->waitForFinished();
    QString rpmBuildMsg = cmd->readAll();
    if (rpmBuildMsg.length() == 0){
        rpmBuildMsg = "rpmbuild seems not work";
        QMessageBox::information(this,"rpmbuild", rpmBuildMsg, QMessageBox::Ok);
    }
    else {
        if (QMessageBox::information(this,"rpmbuild", rpmBuildMsg+"\nopen folder?", QMessageBox::Open, QMessageBox::No)==QMessageBox::Open) {
            QProcess::execute("xdg-open "+QDir::currentPath()+"/rpmbuild/RPMS/"+QSysInfo::buildCpuArchitecture());
        }
    }
}

void MainWindow::on_pushButton_removeFile_clicked()
{
    ui->tableWidget_files->removeRow(ui->tableWidget_files->currentRow());
}

void MainWindow::on_pushButton_removeAll_clicked()
{
    while (ui->tableWidget_files->rowCount() > 0)
        ui->tableWidget_files->removeRow(0);
}
