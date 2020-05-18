#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "QDebug"

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

void MainWindow::on_lineEdit_returnPressed()
{
    QString isbn_number = ui->lineEdit->text();
    std::string tempISBN = isbn_number.toStdString();

    QRegularExpression re1("^ISBN\\s(0|1)(-|\\s)[0-9]{2,7}(-|\\s)[0-9]{1,6}(-|\\s)([0-9]|X)$");

    if(isbn_number.length() == 13 && (std::count(tempISBN.begin(), tempISBN.end(), '-') == 3 || std::count(tempISBN.begin(), tempISBN.end(), ' ') == 3)){
        for(char& c : tempISBN) {
            if(c != '-' && c != ' ')
                isbn_.push_back(c);
        }
        QRegularExpressionMatch match = re1.match(isbn_number, 0, QRegularExpression::PartialPreferCompleteMatch);
        if(match.hasMatch() && check_first_digit(tempISBN)){
            ui->textBrowser->insertPlainText("Match");
        } else {
            ui->textBrowser->insertPlainText("No match");
        }
    } else {
        ui->textBrowser->insertPlainText("No match");
    }

}

bool MainWindow::check_first_digit(std::string tempISBN)
{
    int n = static_cast<int>(tempISBN.length());
        if (n != 13)
            return false;

        // Computing weighted sum
        // of first 9 digits
        int sum = 0;
        for (int i = 0; i < 9; i++)
        {
            if(isbn_[static_cast<unsigned long long>(i)] != '-' || isbn_[static_cast<unsigned long long>(i)] != ' '){
                int digit = isbn_[static_cast<unsigned long long>(i)] - '0';
                if (0 > digit || 9 < digit)
                    return false;
                sum += (digit * (10 - i));
            }
        }

        // Checking last digit.
        char last = isbn_[9];
        if (last != 'X' && (last < '0' ||
                            last > '9'))
            return false;

        // If last digit is 'X', add 10
        // to sum, else add its value.
        sum -= ((last == 'X') ? 10 :
                      (last - '0'));

        // Return true if weighted sum
        // of digits is divisible by 11.
        return (sum % 11 == 0);
}
