#include "welcome_user.h"
#include "ui_welcome_user.h"

#include <QWidget>

Welcome_User::Welcome_User(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Welcome_User)
{
    ui->setupUi(this);
    connect(ui->NextButtonv10, &QPushButton::clicked, this, &Welcome_User::on_NextButton_clicked);

}

Welcome_User::~Welcome_User()
{
    delete ui;
}

void Welcome_User::on_NextButton_clicked()
{
    // Buat instansi isbn_old_version hanya jika belum ada
    if (!oldVersionWidget) {
        oldVersionWidget = new isbn_old_version(this); // Ganti "this" dengan parent widget jika perlu
        oldVersionWidget->setWindowTitle("ISBN-10");
    }

    // Tampilkan isbn_old_version
    oldVersionWidget->show();
}


void Welcome_User::on_NextButtonv13_clicked()
{
    if(!newVersionWidget){
        newVersionWidget = new isbn_new_version(this);
        newVersionWidget->setWindowTitle("ISBN-13");
    }
    newVersionWidget->show();
}

