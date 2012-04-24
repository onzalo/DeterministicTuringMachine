#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QString>
#include <QChar>
#include <QObject>
#include <QList>
#include <QMap>
#include "alphabet.h"
#include "state.h"

const QString _transformationSign=QString(QChar(9500))+QString(QChar(9472));

class TuringMachine : public QObject
{
    Q_OBJECT
private:
    Alphabet inputAlphabet;
    Alphabet auxiliaryAlphabet;
    QChar blank;
    QString initialStateName;
    QMap<QString, State*> states;
    QMap<QString, State*> finalStates();
    QMap<QString, QMap<QChar, Reaction> > transitionsMap;
    Reaction transitionFunction(QString state,QChar symbolRead);

public:
    explicit TuringMachine(QObject *parent = 0);

///Input alphabet
    void addInputSymbol(QChar c);
    void addInputSymbols(QString s);
    void removeInputSymbol(QChar c);
    inline void clearInputAlphabet(){inputAlphabet.clear();}
    inline Alphabet getInputAlphabet()const{return inputAlphabet;}
    inline QStringList inputAlphabetSymbols(){return inputAlphabet.symbolsList();}

///Auxiliar alphabet
    void addAxiliarySymbol(QChar c);
    void addAuxiliarySymbols(QString s);
    void removeAuxiliarySymbol(QChar c);
    inline void clearAuxiliaryAlphabet(){auxiliaryAlphabet.clear();}
    inline Alphabet getAxiliaryAlphabet()const{return auxiliaryAlphabet;}


    inline QStringList auxiliaryAlphabetSymbols(){return auxiliaryAlphabet.symbolsList();}

///Blank simbol
    void setBlank(QChar c);
    inline QChar getBlank()const{return blank;}

///States
    State *addState(QString name,bool final);
    State *addState(QString name);
    State *addFinalState(QString name);
    State *addState(State *state);
    void addStates(QString statesText);

    inline QStringList statesList(){return states.keys();}
    inline QStringList finalStatesList(){return finalStates().keys();}

    inline void setInitialState(QString initial){this->initialStateName=initial;}
    inline QString getInitialStateName()const{return initialStateName;}


 ////
///Simulation

    QString currentStateName;
    int headPosition;
    QString tape;


    inline void setInput(QString input){tape=input;}
    QString makeTransition();
    void moveHead(QChar movement);
    inline QChar symbolRead(){return tape[headPosition];}
    inline void writeSymbol(QChar symbol){tape[headPosition]=symbol;}
    inline State *currentState(){return states[currentStateName];}

//Configurations
    QString alpha1();
    QString alpha2();

    bool haveTransition(QString state, QChar symbolRead);

    QString initializeSimulator(QString input);
    QStringList transitionStringList();
    QString statesText();
    Transition parseTransition(QString transition);
    QStringList tapeAlphabetSymbols();

public slots:
    void addTransition(QString source, QChar symbolRead,QChar symbolWrite, QChar movement, QString target);
    void addTransition(Transition transition);
    void addTransitions(QString transitions);
    void clear();
signals:
    void accepted(QString r);
    void blocked(QString r);
};


#endif // TURINGMACHINE_H
