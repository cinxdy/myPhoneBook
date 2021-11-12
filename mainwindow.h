#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotInsertBtnClicked(void);
    void slotClearBtnClicked(void);

//private slots:
//    void on_pbInputBtn_clicked();
//    void on_pbClearBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
