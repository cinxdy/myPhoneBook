#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pbInputBtn, SIGNAL(clicked()),this, SLOT(slotInsertBtnClicked()));
    connect(ui->pbClearBtn, SIGNAL(clicked()),this, SLOT(slotClearBtnClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotInsertBtnClicked(void)
{
    int retv;
    QMessageBox msgInputBox;

    msgInputBox.setStyleSheet("QLabel{width: 600px; min-width: 600px; max-width: 600px;height: 100px; min-height: 100px; max-height: 100px;}");
    retv=msgInputBox.warning(this, "Confirm","Data Input",QMessageBox::Cancel|QMessageBox::Ok);

    if(retv==QMessageBox::Ok)
    {
        if(ui->leName->text().length()==0)
        {
            msgInputBox.warning(this, "Field Check", "Name Field Empty!!", QMessageBox::Ok);
            ui->leName->setFocus();
            return ;
        }
        if(ui->leSex->text().length()==0)
        {
            msgInputBox.warning(this, "Field Check", "Sex Field Empty!!", QMessageBox::Ok);
            ui->leSex->setFocus();
            return ;
        }
        if(ui->leTelNo->text().length()==0)
        {
            msgInputBox.warning(this, "Field Check", "TelNo Field Empty!!", QMessageBox::Ok);
            ui->leTelNo->setFocus();
            return ;
        }


        QString strMsg;
//        strMsg.QString("%1(%2)\n%3 $4\n %5").arg(ui->leName->text()).arg(ui->leSex->text()).arg(ui->lePersonType->text()).arg(ui->leMemo->text());
        strMsg = ui->leName->text() + "(" + ui->leSex->text() + ")\n" + ui->leTelNo->text() + "\n" + ui->leMemo->text();

        msgInputBox.warning(this, "Success", strMsg ,QMessageBox::Ok);
        ui->leSex->setText("");
        ui->leMemo->setText("");
        ui->leName->setText("");
        ui->leTelNo->setText("");
        ui->lePersonType->setText("");
    }
}
void MainWindow::slotClearBtnClicked(void)
{
    int retv;
    QMessageBox msgClearBox;
//    msgClearBox.warning(this, "Confirm","Data Clear",QMessageBox::Cancel|QMessageBox::Ok);
    retv = msgClearBox.warning(this, "Confirm", "Data Clear", QMessageBox::Cancel|QMessageBox::Ok);
    if(retv==QMessageBox::Ok)
    {
        ui->leSex->setText("");
        ui->leMemo->setText("");
        ui->leName->setText("");
        ui->leTelNo->setText("");
        ui->lePersonType->setText("");
    }
}

//void MainWindow::on_pbInputBtn_clicked()
//{
//    QMessageBox msgInputBox;
//    msgInputBox.warning(this, "Input","Data Input",QMessageBox::Cancel|QMessageBox::Ok);
//}

//void MainWindow::on_pbClearBtn_clicked()
//{
//    QMessageBox msgClearBox;
//    msgClearBox.warning(this, "Clear","Data Clear",QMessageBox::Cancel|QMessageBox::Ok);
//}
