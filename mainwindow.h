#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDataWidgetMapper>
#include <QStandardItemModel>
#include <QStringListModel>

#include "dialogstate.h"
#include "dialogalphabet.h"
#include "dialogblank.h"
#include "dialoginitialstate.h"
#include "dialogsimulator.h"
#include "turingmachine.h"
#include "dialogtransition.h"
#include "dialogabout.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void addState(QString nameState, bool final);
    void changeBlank(QChar c);
    void selectInitialState(QString nameState);
    void makeTransition();
    void addRowTransition(QString sourceStateName, QChar symbolRead, QChar symbolWrite, QChar movement, QString targetStateName);
    void newTuringMachine();
    void openTuringMachine();
    void saveTuringMachine();
    void updateData();
    void about();

    void on_pb_addState_clicked();
    void on_pb_addInputSymbol_clicked();
    void on_pb_addAuiliarySymbol_clicked();
    void on_pb_setBlank_clicked();
    void on_pb_setIntialState_clicked();
    void on_pb_simulate_clicked();
    void on_pb_addTransition_clicked();


public slots:
    void editInputAlphabet(QString symbols);
    void editAuxiliaryAlphabet(QString symbols);
private:
    Ui::MainWindow *ui;

    DialogState dialogState;
    DialogAlphabet dialogAlphabet;
    DialogBlank dialogBlank;
    DialogInitialState dialogInitialState;
    DialogSimulator dialogSimulator;
    DialogTransition dialogTransition;
    DialogAbout dialogAbout;
    Transition parseTransition(QString transition);
    void addRowTransition(Transition t);
    void addRowTransition(QString transition);

    TuringMachine turingMachine;

};

#endif // MAINWINDOW_H
