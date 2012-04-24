#include "dialogstate.h"
#include "ui_dialogstate.h"
#include <QDebug>

DialogState::DialogState(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogState)
{
    ui->setupUi(this);

}


DialogState::~DialogState()
{

    delete ui;
}
int DialogState::exec(){

    ui->le_nameState->clear();
    ui->cb_final->setChecked(false);
    ui->le_nameState->setFocus();
    return QDialog::exec();
}
void DialogState::on_buttonBox_accepted()
{
    if(ui->le_nameState->text()!=""){
        //qDebug()<<ui->le_nameState->text();
        emit newState(ui->le_nameState->text(),ui->cb_final->isChecked());
    }
}
