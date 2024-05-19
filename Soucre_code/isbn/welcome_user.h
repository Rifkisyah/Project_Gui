#ifndef WELCOME_USER_H
#define WELCOME_USER_H

#include <QMainWindow>
#include "isbn_old_version.h"
#include "isbn_new_version.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Welcome_User;
}
QT_END_NAMESPACE

class Welcome_User : public QMainWindow
{
    Q_OBJECT

public:
    Welcome_User(QWidget *parent = nullptr);
    ~Welcome_User();

private slots:
    void on_NextButton_clicked();

    void on_NextButtonv13_clicked();

private:
    Ui::Welcome_User *ui;
    isbn_old_version *oldVersionWidget = nullptr;
    isbn_new_version *newVersionWidget = nullptr;
};
#endif // WELCOME_USER_H
