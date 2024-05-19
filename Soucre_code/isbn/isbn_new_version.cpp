#include "isbn_new_version.h"
#include "ui_isbn_new_version.h"
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QRegularExpression>
#include <QDebug>
#include <array>
#include <QTabWidget>
#include <QWidget>

isbn_new_version::isbn_new_version(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::isbn_new_version)
{
    ui->setupUi(this);
    connect(ui->input, &QPushButton::clicked, this, &isbn_new_version::on_input_clicked);
    connect(ui->check, &QPushButton::clicked, this, &isbn_new_version::on_checktestdigit_clicked);
    connect(ui->cleardata, &QPushButton::clicked, this, &isbn_new_version::clear_data);
    connect(ui->backtomenu, &QPushButton::clicked, this, &isbn_new_version::on_backtomenu_clicked);
}

isbn_new_version::~isbn_new_version()
{
    delete ui;
}

void isbn_new_version::on_input_clicked()
{
    QString Data_Input = ui->inputbox->text();
    if(!input_validation){
        check_invalid_input(Data_Input);
        input_validation = true;
    }
    ui->input->setEnabled(false);
}

void isbn_new_version::check_invalid_input(const QString Data){
    QString Data_Input = Data;
    static QRegularExpression regex("^(?=.*[0-9])(?:[0-9]*(?:[0-9?Xx](?![0-9?Xx]))?|[Xx][0-9]*(?![0-9?Xx])\\?)$");
    if(Data_Input.size() != 13){
        ui->Log->setPlainText("error : input must be contains 10 characters");
        qDebug() << "Panjang Data_Input:" << Data_Input.size();
        ui->check->setEnabled(false);
    }else if(!regex.match(Data_Input).hasMatch()){
        ui->Log->setPlainText("error : input must be '0-9' digit number and can contain symbol 'X' or 'x' for 10 value! or you can input ? symbol for undefine check digit value");
        qDebug() << "Jenis input : " << !regex.match(Data_Input).hasMatch();
        ui->check->setEnabled(false);
    }else if (Data_Input.contains(' ') || Data_Input.contains('-')) {
        ui->Log->setPlainText("error : input can't contains '-' or space!");
        qDebug() << "input terdapat : " << Data_Input.contains(' ') << " or " << Data_Input.contains('-');
        ui->check->setEnabled(false);
    }else if(Data_Input.isEmpty()){
        ui->Log->setPlainText("error : input is empty!");
        qDebug() << "Data input : " << Data_Input.isEmpty();
        ui->check->setEnabled(false);
    }else{
        if(regex.match(Data_Input).hasMatch()){
            ui->Log->appendPlainText(QString("info : Data %1 record").arg(Data_Input));
            ui->Log->appendPlainText("info : input complete!");
            qDebug() << Data_Input;
        }else{
            ui->Log->appendPlainText(QString("info : Data %1 record").arg(Data_Input));
            ui->Log->appendPlainText("info : input complete!");
            qDebug() << Data_Input;
        }
    }
}

void isbn_new_version::on_checktestdigit_clicked()
{
    QString Data_Input = ui->inputbox->text();
    std::array<int, 13> convert_to_int = convert(Data_Input);
    if(calculate(convert_to_int) == true){
        ui->displayvalid->setText("VALID");
    }else{
        ui->displayvalid->setText("INVALID");
    }
    ui->check->setEnabled(false);

}

std::array<int, 13> isbn_new_version::convert(QString Data) {
    std::array<int, 13> temp;

    // Konversi karakter terakhir
    if (Data.at(12) == 'X' || Data.at(12) == 'x') {
        temp[12] = 10;
    } else if (Data.at(12) == '?') {
        temp[12] = 11;
    } else {
        temp[12] = Data.at(12).digitValue();
    }

    // Konversi karakter lainnya
    for (int i = 0; i < Data.size() - 1; i++) {
        temp[i] = Data.at(i).digitValue();
    }

    return temp;
}


bool isbn_new_version::calculate(std::array<int, 13> data){
    int sum_condition_1 = 0;
    ui->Log->appendPlainText("process : ");
    int multiply = 1;

    for(int i = 0; i < 12; i++){
        sum_condition_1 += data[i] * multiply;                   // menambahkan nilai isbn yang dikalikan 1-9

        ui->Log->appendPlainText(QString::number(data[i]) + " X " + QString::number(multiply)+ " = " + QString::number(sum_condition_1));
        multiply = (multiply == 1) ? 3 : 1;
    }

    int mod = sum_condition_1 % 10;                             // modular hasil pertambahan dengan 11
    ui->Log->appendPlainText(QString::number(sum_condition_1) + " mod 10 = " + QString::number(mod));

    int check_digit = 10 - mod;
    ui->displaydigitvalue->setText(QString::number(check_digit));
    ui->Log->appendPlainText("10 - " + QString::number(mod) + " = " + QString::number(check_digit));

    if(data[12] == 11){                                    // kondisi jika test digit di index terakhir sama seperti nilai insialisasi yaitu 11
        ui->Log->appendPlainText(" ");
        bool isValid = false; // Inisialisasi variabel boolean untuk menandakan validitas ISBN

        for (int i = 0; i < 12; i++) {
            data[12] = i;
            int sum_condition_2 = 0; // Inisialisasi ulang sum_condition_2 untuk setiap iterasi
            ui->Log->appendPlainText("Valid Process of check digit : ");
            ui->Log->appendPlainText("if '?' is " + QString::number(data[12]));
            for(int j = 0; j <= 12; j++){
                sum_condition_2 += data[j] * multiply;
                ui->Log->appendPlainText(QString::number(data[j]) + "X" + QString::number(multiply) + " = " + QString::number(sum_condition_2));
                multiply = (multiply == 1) ? 3 : 1;
            }

            int mod_2 = sum_condition_2 % 10;
            ui->Log->appendPlainText(QString::number(sum_condition_2) + " mod 10 = " + QString::number(mod_2));


            if(mod_2 == 0){
                ui->Log->appendPlainText("Test Digit " + QString::number(mod_2) + " same as 0 = VALID");
                ui->Log->appendPlainText("This isbn value is VALID when check digit is " + QString::number(data[12]));
                isValid = true; // Set isValid menjadi true karena ISBN valid
                break; // Keluar dari loop for karena ISBN sudah dinyatakan valid
            }else{
                ui->Log->appendPlainText("Test Digit " + QString::number(mod_2) + " is not same as " + QString::number(mod));
                int test_digit = 10 - mod_2;
                ui->Log->appendPlainText("Test digit = 11 - " + QString::number(mod_2) + " = " + QString::number(test_digit));


                if(test_digit == mod){
                    ui->Log->appendPlainText("Test Digit " + QString::number(test_digit) + " same as " + QString::number(mod) + " = VALID");
                    isValid = true; // Set isValid menjadi true karena ISBN valid
                    break; // Keluar dari loop for karena ISBN sudah dinyatakan valid
                }else{
                    ui->Log->appendPlainText("Test Digit " + QString::number(test_digit) + " is not same as " + QString::number(mod) + " = INVALID");
                    ui->Log->appendPlainText(" ");
                    isValid = false; // Tetapkan isValid menjadi false karena ISBN tidak valid
                }
            }
        }

        if (!isValid) {
            // Tambahkan log atau kode lainnya untuk menangani kasus di mana ISBN tidak valid
        }

        return isValid;


    }else if(data[12] == check_digit){                                        // kondisi jika hasil modular sama seperti test digit di index terakhir
        ui->Log->appendPlainText("Test Digit " + QString::number(check_digit) + " same as " + QString::number(data[12]) + " = VALID");
        return true;

    }else{
        ui->Log->appendPlainText("Test Digit " + QString::number(check_digit) + " is not same as " + QString::number(data[12]) + " = INVALID");
        return false;                                           // kondisi jika semua kondisi tidak terpenuhi
    }
}

void isbn_new_version::clear_data(){
    ui->Log->clear();
    ui->inputbox->clear();
    ui->displaydigitvalue->clear();
    ui->displayvalid->clear();
    input_validation = false;

    ui->input->setEnabled(true);
    ui->check->setEnabled(true);
}


void isbn_new_version::on_backtomenu_clicked()
{
    this->hide();
    QWidget *toMainWindow = this->parentWidget();
    if(toMainWindow){
        toMainWindow->show();
    }
    clear_data();
}

