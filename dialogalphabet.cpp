#include "dialogalphabet.h"
#include "ui_dialogalphabet.h"

DialogAlphabet::DialogAlphabet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogAlphabet)
{
    ui->setupUi(this);
}

DialogAlphabet::~DialogAlphabet()
{
    delete ui;
}

void DialogAlphabet::on_buttonBox_accepted()
{
    if(this->windowTitle()=="Alfabeto Entrada"){
        emit editInputSymbols(ui->le_symbolsAlphabet->text());
    }
    if(this->windowTitle()=="Alfabeto Auxiliar"){
        emit editAuxiliarySymbols(ui->le_symbolsAlphabet->text());
    }

}

void DialogAlphabet::setSymbols(QString s)
{
    ui->le_symbolsAlphabet->setText(s);
}
