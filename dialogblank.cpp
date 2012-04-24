#include "dialogblank.h"
#include "ui_dialogblank.h"
#include <QMessageBox>

DialogBlank::DialogBlank(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBlank)
{
    ui->setupUi(this);
}

DialogBlank::~DialogBlank()
{
    delete ui;
}

void DialogBlank::on_buttonBox_accepted()
{
    if(ui->le_blank->text()==","){
        QMessageBox msgBox;
        msgBox.setText("No se permite elegir la coma.");
        msgBox.exec();
    }else
        emit changeBlank(ui->le_blank->text().at(0));
}
