#include "dialogtransition.h"
#include "ui_dialogtransition.h"
#include <QDebug>

DialogTransition::DialogTransition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTransition)
{
    ui->setupUi(this);
}

DialogTransition::~DialogTransition()
{
    delete ui;
}

void DialogTransition::initialize(QStringList states, QStringList tapeAlphabet)
{
    ui->cb_State->clear();
    ui->cb_targetState->clear();
    ui->cb_readSymbol->clear();
    ui->cb_writeSymbol->clear();

    ui->cb_State->addItems(states);
    ui->cb_targetState->addItems(states);
    ui->cb_readSymbol->addItems(tapeAlphabet);
    ui->cb_writeSymbol->addItems(tapeAlphabet);
}


void DialogTransition::on_buttonBox_accepted()
{
    QString sourceStateName=ui->cb_State->currentText();
    QChar symbolRead=ui->cb_readSymbol->currentText().at(0);
    QChar symbolWrite=ui->cb_writeSymbol->currentText().at(0);
    QString targetStateName=ui->cb_targetState->currentText();
    QChar movement;
    QString mov=ui->cb_movement->currentText();

    if(mov=="I")
        movement='L';
    else if(mov=="D")
        movement='R';
    else
        movement='S';

 emit addTransition(sourceStateName,symbolRead,symbolWrite,movement, targetStateName);
}
