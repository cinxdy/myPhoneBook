#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QButtonGroup>

#include <QItemSelectionModel>
#include <QItemSelection>
#include <QTableWidgetItem>

#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QTextStream>

static QStringList qStrListOptionTable_Headers = {"Name","Sex","Phone","Type"};
int m_listCount;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QButtonGroup *btnGrp = new QButtonGroup(this);
    btnGrp->addButton(ui->rbM);
    btnGrp->addButton(ui->rbW);
    ui->rbM->setChecked(true);

    ui->cbPersonType->addItem("Family");
    ui->cbPersonType->addItem("Best Friend");
    ui->cbPersonType->addItem("Class Mate");
    ui->cbPersonType->addItem("Project Mate");
    ui->cbPersonType->addItem("Church Community");
    ui->cbPersonType->addItem("Other");

    ui->cbTelNo->addItem("02");
    ui->cbTelNo->addItem("054");
    ui->cbTelNo->addItem("010");
    ui->cbTelNo->setCurrentIndex(0);

    ui->tblPhoneList->setRowCount(10);
    ui->tblPhoneList->setColumnCount(4);
    ui->tblPhoneList->setColumnWidth(0,80);
    ui->tblPhoneList->setColumnWidth(1,30);
    ui->tblPhoneList->setColumnWidth(2,140);
    ui->tblPhoneList->setColumnWidth(3,100);

    ui->tblPhoneList->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tblPhoneList->setHorizontalHeaderLabels(qStrListOptionTable_Headers);
    ui->tblPhoneList->setStyleSheet("QTableWidget QTableCornerButton::section {"
                               "background-color:rgb(187,187,187);"
                               "border-image: url(:/transparent.png);"
                               "image: url(:/qt-logo.ico);"
                               "}");
    m_listCount = 0;


    connect(ui->pbInputBtn, SIGNAL(clicked()),this, SLOT(slotInsertBtnClicked()));
    connect(ui->pbClearBtn, SIGNAL(clicked()),this, SLOT(slotClearBtnClicked()));
    connect(ui->pbSaveBtn, SIGNAL(clicked()),this, SLOT(slotSaveBtnClicked()));
    connect(ui->pbDelBtn, SIGNAL(clicked()),this, SLOT(slotDeleteBtnClicked()));
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
        if(ui->leTelNo->text().length()==0)
        {
            msgInputBox.warning(this, "Field Check", "TelNo Field Empty!!", QMessageBox::Ok);
            ui->leTelNo->setFocus();
            return ;
        }


        QString strMsg;
        QString strRdo;

        if(ui->rbM->isChecked()) strRdo.append("Male");
        else strRdo.append("Female");

//        strMsg.QString("%1(%2)\n%3 $4\n %5").arg(ui->leName->text()).arg(ui->leSex->text()).arg(ui->lePersonType->text()).arg(ui->leMemo->text());
        strMsg = ui->leName->text() + "(" + strRdo + ")\n" + ui->cbPersonType->currentText() + " " + ui->cbTelNo->currentText()+" "+ui->leTelNo->text() + "\n" + ui->leMemo->text();

        QString temp;
        ui->tblPhoneList->setItem(m_listCount ,0, new QTableWidgetItem(ui->leName->text()));
        ui->tblPhoneList->setItem(m_listCount ,1, new QTableWidgetItem(strRdo));
        temp= ui->cbTelNo->currentText() + " " + ui->leTelNo->text();
        ui->tblPhoneList->setItem(m_listCount, 2, new QTableWidgetItem(temp));
        ui->tblPhoneList->setItem(m_listCount, 3, new QTableWidgetItem(ui->cbPersonType->currentText()));

        msgInputBox.warning(this, "Success", strMsg ,QMessageBox::Ok);
//        ui->leSex->setText("");
        ui->rbM->setChecked(true);
        ui->leMemo->setText("");
        ui->leName->setText("");
        ui->leTelNo->setText("");
        ui->cbPersonType->setCurrentIndex(0);
        ui->cbTelNo->setCurrentIndex(0);
//        ui->lePersonType->setText("");

        m_listCount++;
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
//        ui->leSex->setText("");
        ui->rbM->setChecked(true);
        ui->leMemo->setText("");
        ui->leName->setText("");
        ui->leTelNo->setText("");
        ui->cbPersonType->setCurrentIndex(0);
        ui->cbTelNo->setCurrentIndex(0);
//        ui->lePersonType->setText("");
    }
}

void MainWindow::slotSaveBtnClicked(void)
{
    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save    Data"), nullptr, \
                                                                 tr("Text    File(*.txt);;All Files (*)"));
    QFile saveFile(saveFileName);

    if(!saveFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Cannot write";
        return;
    }

    QTextStream strOut(&saveFile);
    for(int repi=0;repi<m_listCount;repi++)
    {
        for(int repj=0;repj<m_listCount;repj++)
        {
            QString temp = \
                    ui->tblPhoneList->model()->data(ui->tblPhoneList->model()->index(repi,repj)) \
                    .toString().simplified();

            if(repj!=3) strOut << temp << ",";
            else strOut << temp << "\n";
        }
    }

    saveFile.flush();
    saveFile.close();
}

void MainWindow::slotDeleteBtnClicked(void)
{
    int retv;
    QMessageBox msgClearBox;
    retv = msgClearBox.warning(this, "Confirm", "Delete all data!", QMessageBox::Cancel | QMessageBox::Ok);

    if(retv==QMessageBox::Ok)
    {
        ui->tblPhoneList->model()->removeRows(0, ui->tblPhoneList->rowCount());
        ui->tblPhoneList->setRowCount(10);
    }
}

