#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addingmenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_autoservice_btn_clicked()
{
    addingmenu window(this); // создаём на стеке (не через new — так безопаснее для exec)

    // запускаем диалог в модальном режиме
    if (window.exec() == QDialog::Accepted) {
        // обработка данных после "Принять"
    }
}

