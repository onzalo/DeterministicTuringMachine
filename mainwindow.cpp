#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&dialogState,
            SIGNAL(newState(QString,bool)),
            this,
            SLOT(addState(QString,bool))
            );
    connect(&dialogAlphabet,
            SIGNAL(editInputSymbols(QString)),
            this,
            SLOT(editInputAlphabet(QString))
            );
    connect(&dialogAlphabet,
            SIGNAL(editAuxiliarySymbols(QString)),
            this,
            SLOT(editAuxiliaryAlphabet(QString))
            );
    connect(&dialogBlank,
            SIGNAL(changeBlank(QChar)),
            this,
            SLOT(changeBlank(QChar))
            );
    connect(&dialogInitialState,
            SIGNAL(initialStateSelected(QString)),
            this,
            SLOT(selectInitialState(QString))
            );
    connect(&dialogSimulator,
            SIGNAL(makeTransition()),
            this,
            SLOT(makeTransition())
            );
    connect(&turingMachine,
            SIGNAL(accepted(QString)),
            &dialogSimulator,
            SLOT(accepted(QString))
            );
    connect(&turingMachine,
            SIGNAL(blocked(QString)),
            &dialogSimulator,
            SLOT(blocked(QString))
            );
    connect(&dialogTransition,
            SIGNAL(addTransition(QString,QChar,QChar,QChar,QString)),
            &turingMachine,
            SLOT(addTransition(QString,QChar,QChar,QChar,QString))
            );
    connect(&dialogTransition,
            SIGNAL(addTransition(QString,QChar,QChar,QChar,QString)),
            this,
            SLOT(updateData())
            );

    updateData();


    /***********/
    /** Test**/
    //turingMachine.addInputSymbol('a');
    //turingMachine.addAxiliarySymbol('b');
    //turingMachine.addAxiliarySymbol('c');
    //turingMachine.addState("q0",false);
    //turingMachine.addState("q1",true);
    //turingMachine.setInitialState("q0");
    //turingMachine.addTransition("q0",'a','b','R',"q1");
    //turingMachine.addTransition("q1",'a','c','R',"q0");
    /** Fin**/
    /***********/

    updateData();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateData()
{

    ui->tb_States->setText("Q={"+turingMachine.statesList().join(",")+"}");

    ui->tb_inputAlphabet->setHtml(QString(QChar(931))+"<span style=\" vertical-align:sub;\">E</span>={"
                                  +turingMachine.inputAlphabetSymbols().join(",")+"}");
    ui->tb_auxiliaryAlphabet->setHtml(QString(QChar(931))+"<span style=\" vertical-align:sub;\">A</span>={"
                                  +turingMachine.auxiliaryAlphabetSymbols().join(",")+"}");
    ui->tb_blank->setText("b="+QString(turingMachine.getBlank()));
    ui->tb_initialState->setHtml("q<span style=\" vertical-align:sub;\">0</span>="+turingMachine.getInitialStateName());
    ui->tb_finalStates->setText("F={"+turingMachine.finalStatesList().join(",")+"}");

    QStringList transitionStringList=turingMachine.transitionStringList();
    QStringListModel *transitionListModel=new QStringListModel(transitionStringList);
    //transitionListModel->setStringList(turingMachine.transitionStringList());
    ui->lv_transitions->setModel(transitionListModel);


    ui->tw_transitions->setRowCount(0);

    for(int i=0;i<transitionStringList.count();i++){
        addRowTransition(transitionStringList[i]);
    }

}

void MainWindow::on_pb_addState_clicked()
{
    dialogState.exec();
}

void MainWindow::on_pb_addInputSymbol_clicked()
{
    dialogAlphabet.setWindowTitle("Alfabeto Entrada");
    dialogAlphabet.setSymbols(turingMachine.inputAlphabetSymbols().join(","));
    dialogAlphabet.exec();
}
void MainWindow::on_pb_addAuiliarySymbol_clicked()
{
    dialogAlphabet.setWindowTitle("Alfabeto Auxiliar");
    dialogAlphabet.setSymbols(turingMachine.auxiliaryAlphabetSymbols().join(","));
    dialogAlphabet.exec();
}

void MainWindow::addState(QString nameState, bool final)
{
    turingMachine.addState(nameState,final);
    updateData();
}

void MainWindow::editInputAlphabet(QString symbols)
{
    turingMachine.clearInputAlphabet();
    turingMachine.addInputSymbols(symbols);
    updateData();

}

void MainWindow::editAuxiliaryAlphabet(QString symbols)
{
    turingMachine.clearAuxiliaryAlphabet();
    turingMachine.addAuxiliarySymbols(symbols);
    updateData();
}



void MainWindow::on_pb_setBlank_clicked()
{
    dialogBlank.exec();
}

void MainWindow::changeBlank(QChar c)
{
    turingMachine.setBlank(c);
    updateData();
}

void MainWindow::on_pb_setIntialState_clicked()
{
    dialogInitialState.setStates(turingMachine.statesList());
    dialogInitialState.exec();
}

void MainWindow::selectInitialState(QString nameState)
{
    turingMachine.setInitialState(nameState);
    updateData();
}

void MainWindow::makeTransition()
{
    dialogSimulator.addConfiguration(turingMachine.makeTransition());
    int i = turingMachine.headPosition;
    QString tape=turingMachine.tape;
    tape.insert(i,"<u>");
    tape.insert(i+4,"</u>");
    dialogSimulator.setTape(tape);
}


void MainWindow::on_pb_simulate_clicked()
{
    dialogSimulator.initializeSimulator(ui->le_input->text());
    dialogSimulator.addConfiguration(turingMachine.initializeSimulator(ui->le_input->text()));
    dialogSimulator.exec();
}



void MainWindow::on_pb_addTransition_clicked()
{
    dialogTransition.initialize(turingMachine.statesList(),turingMachine.tapeAlphabetSymbols());
    dialogTransition.exec();
}

void MainWindow::addRowTransition(QString sourceStateName, QChar symbolRead,QChar symbolWrite, QChar movement, QString targetStateName){

    QString prefix;
    if(sourceStateName==turingMachine.getInitialStateName())
        prefix.append(QString(8594));
    if(turingMachine.finalStatesList().contains(sourceStateName))
        prefix.append("*");

    sourceStateName.prepend(prefix);


    QString mov;
    if(movement=='L')
        mov="I";
    else if(movement=='R')
        mov="D";
    else if(movement=='S')
        mov="N";
    else
        mov=movement;



    QTableWidgetItem *sourceItem,*readItem,*targetItem,*writeItem,*movementItem;
    sourceItem=new QTableWidgetItem(sourceStateName);
    readItem=new QTableWidgetItem(QString(symbolRead));
    targetItem=new QTableWidgetItem(targetStateName);
    writeItem=new QTableWidgetItem(QString(symbolWrite));
    movementItem=new QTableWidgetItem(mov);

    int numberRow=ui->tw_transitions->rowCount();
    ui->tw_transitions->insertRow(numberRow);
    ui->tw_transitions->setItem(numberRow,0,sourceItem);
    ui->tw_transitions->setItem(numberRow,1,readItem);
    ui->tw_transitions->setItem(numberRow,2,targetItem);
    ui->tw_transitions->setItem(numberRow,3,writeItem);
    ui->tw_transitions->setItem(numberRow,4,movementItem);
}
void MainWindow::addRowTransition(Transition t){
    addRowTransition(t.sourceStateName,t.readSymbol,t.symbolWrite,t.movement,t.targetStateName);
}
void MainWindow::addRowTransition(QString transition){
    addRowTransition(parseTransition(transition));
}



Transition MainWindow::parseTransition(QString transition)
{
    QStringList members=transition.split(")=(");
    QString stimulus=members.at(0).mid(2);
    QString reaction=members.at(1);
    reaction.chop(1);

    QStringList stimulusPart=stimulus.split(",");
    QStringList reactionPart=reaction.split(",");

    Transition r;
    r.sourceStateName=stimulusPart[0];
    r.readSymbol=stimulusPart.at(1).at(0);
    r.targetStateName=reactionPart[0];
    r.symbolWrite=reactionPart.at(1).at(0);
    r.movement=reactionPart.at(2).at(0);

    return r;
}
void MainWindow::saveTuringMachine()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                        tr("Guardar Maquina de Turing"),
                                                    "MT",
                                        tr("Archivo de Texto (*.txt)"));

        fileName+=".txt";
        QFile data(fileName);
        if (data.open(QFile::WriteOnly | QFile::Truncate)) {

            QTextStream out(&data);

             out<< turingMachine.statesText()+"\n"
                    +turingMachine.inputAlphabetSymbols().join(",")+"\n"
                    +turingMachine.auxiliaryAlphabetSymbols().join(",")+"\n"
                    +turingMachine.getBlank()+"\n"
                    +turingMachine.getInitialStateName()+"\n"
                    +turingMachine.transitionStringList().join(";");


            data.close();
        }

}

void MainWindow::openTuringMachine()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir MT"), "",
            tr("Archivos de Texto (*.txt)"));

    if (fileName != "") {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Truncate)) {
            QString outString;
            QTextStream in(&file);
            turingMachine.clear();
            QStringList lines;
            for(int i=0;i<6;i++){
                QString line=QString(in.readLine());
                lines.append(line);
            }
            turingMachine.addStates(lines.at(0));
            turingMachine.addInputSymbols(lines.at(1));
            turingMachine.addAuxiliarySymbols(lines.at(2));
            turingMachine.setBlank(lines.at(3).at(0));
            turingMachine.setInitialState(lines.at(4));
            turingMachine.addTransitions(lines.at(5));
            file.close();

        }

    }
    updateData();
}

void MainWindow::newTuringMachine(){
    turingMachine.clear();
    updateData();
}
void MainWindow::about(){
    dialogAbout.exec();
}


