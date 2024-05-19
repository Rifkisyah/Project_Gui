#ifndef ISBN_NEW_VERSION_H
#define ISBN_NEW_VERSION_H

#include <QDialog>

namespace Ui {
class isbn_new_version;
}

class isbn_new_version : public QDialog
{
    Q_OBJECT

public:
    explicit isbn_new_version(QWidget *parent = nullptr);
    ~isbn_new_version();

    bool input_validation = false;

private slots:
    void on_input_clicked();

    void check_invalid_input(const QString Data_Input);

    void on_checktestdigit_clicked();
    std::array<int, 13> convert(QString Data);
    bool calculate(std::array<int, 13> data);
    void clear_data();

    void on_backtomenu_clicked();

private:
    Ui::isbn_new_version *ui;
};

#endif // ISBN_NEW_VERSION_H