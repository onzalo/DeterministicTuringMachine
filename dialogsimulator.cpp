#include "dialogsimulator.h"
#include "ui_dialogsimulator.h"

DialogSimulator::DialogSimulator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSimulator)
{
    ui->setupUi(this);
}

DialogSimulator::~DialogSimulator()
{
    delete ui;
}

void DialogSimulator::on_pb_makeTransition_clicked()
{
    emit makeTransition();
}

void DialogSimulator::setTape(QString tape)
{
    ui->la_tape->setText(tape);
}


void DialogSimulator::initializeSimulator(QString input){
    QString tape=input;
    tape.insert(0,"<u>");
    tape.insert(4,"</u>");
    ui->le_input->setText(input);
    ui->la_tape->setText(tape);
    ui->la_accepted->setText("");
    ui->tb_configurations->clear();
    ui->pb_makeTransition->setEnabled(true);

}

void DialogSimulator::addConfiguration(QString configuration)
{
    ui->tb_configurations->setText(ui->tb_configurations->toPlainText()+configuration);

}

void DialogSimulator::accepted(QString configuration)
{
    ui->la_accepted->setText("<span style=\" color:#55aa00;\">Entrada aceptada.</span><p> Configuraci&oacute;n final:"+configuration+"</p>");
    ui->pb_makeTransition->setEnabled(false);
}

void DialogSimulator::blocked(QString configuration)
{
    ui->la_accepted->setText("<span style=\" color:#aa0000;\">Entrada rechazada.</span>" + configuration);
    ui->pb_makeTransition->setEnabled(false);
}


