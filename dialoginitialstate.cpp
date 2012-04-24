#include "dialoginitialstate.h"
#include "ui_dialoginitialstate.h"

DialogInitialState::DialogInitialState(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInitialState)
{
    ui->setupUi(this);
}

DialogInitialState::~DialogInitialState()
{
    delete ui;
}

void DialogInitialState::on_buttonBox_accepted()
{
    emit initialStateSelected(ui->cb_states->itemText(ui->cb_states->currentIndex()));
}

void DialogInitialState::setStates(QStringList states)
{
    ui->cb_states->clear();
    ui->cb_states->addItems(states);
}
