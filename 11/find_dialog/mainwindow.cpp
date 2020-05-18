#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <fstream>
#include <algorithm>
#include <QDebug>

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

namespace {
    bool findWord(std::multimap<std::string, std::string> words_, bool matchChecked, QString keyWords){
        std::string stringKeyWords = keyWords.toStdString();
        std::string tempKeyWords = stringKeyWords;
        transform(stringKeyWords.begin(), stringKeyWords.end(), stringKeyWords.begin(), ::toupper);
        auto search = words_.find(stringKeyWords);
        if (search != words_.end()) {
            if(matchChecked){
                if(search->second == tempKeyWords){
                    return true;
                }
                return false;
            }
            return true;
        }
        return false;
    }
}

void MainWindow::on_findPushButton_clicked()
{
    QString keyWord = ui->keyLineEdit->text();
    if(keyWord != ""){
        bool matchChecked = ui->matchCheckBox->isChecked();
        if(findWord(words_, matchChecked, keyWord)){
            ui->textBrowser->append("Word found");
        } else {
            ui->textBrowser->append("Word not found");
        }
    }
}

void MainWindow::on_fileLineEdit_editingFinished()
{
    QString fileName = ui->fileLineEdit->text();
    std::string tempFileName = fileName.toStdString();
    std::ifstream file_object(tempFileName);
    std::string word;
    if ( not file_object ) {
        ui->textBrowser->setText("File not found");
    } else {
        qDebug() << QString::fromStdString(tempFileName);
        ui->textBrowser->setText("File found");
        while ( getline(file_object, word, ' ') ) {
            std::string temp_word = word;
            temp_word.erase(std::remove_if(temp_word.begin(), temp_word.end(),
                [](char c) { return std::isspace(c) || !std::isalpha(c); } ),
                temp_word.end());
            if(temp_word != ""){
                std::string value_word = temp_word;
                transform(temp_word.begin(), temp_word.end(), temp_word.begin(), ::toupper);
                words_.insert({temp_word, value_word});
            }
        }
    }
}

void MainWindow::on_keyLineEdit_editingFinished()
{
    QString keyWord = ui->keyLineEdit->text();
    if(keyWord != ""){
        std::string stringKeyWords = keyWord.toStdString();
        qDebug() << QString::fromStdString(stringKeyWords);
    }
}
