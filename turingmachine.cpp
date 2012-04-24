#include "turingmachine.h"
#include <QDebug>


TuringMachine::TuringMachine(QObject *parent) :
    QObject(parent)
{
    blank=QChar(916);
    auxiliaryAlphabet.insert(blank);
}


State *TuringMachine::addState(QString name,bool final){
    states[name]=new State(name);
    states[name]->setFinal(final);
    return states[name];
}
State *TuringMachine::addState(State* state){
    return addState(state->getName(),state->isFinal());
}
State *TuringMachine::addState(QString name)
{
    return addState(name,false);
}

State * TuringMachine::addFinalState(QString name)
{
    return addState(name,true);
}

void TuringMachine::addTransition(QString sourceStateName, QChar symbolRead,QChar symbolWrite, QChar movement, QString targetStateName)
{   if(states.contains(sourceStateName)&&states.contains(targetStateName)){
        states[sourceStateName]->addTransition(symbolRead,symbolWrite,movement,targetStateName);
        Reaction r;
        r.symbolWrite=symbolWrite;
        r.targetStateName=targetStateName;
        r.movement=movement;
        transitionsMap[sourceStateName][symbolRead]=r;
    }

}

QString TuringMachine::initializeSimulator(QString input){
    currentStateName=initialStateName;
    headPosition=0;
    tape=input;
    return QString(blank)+alpha1()+currentStateName+alpha2()+QString(blank);
}

QString TuringMachine::makeTransition()
{
    if(haveTransition(currentStateName,symbolRead())){
        Reaction reaction=transitionFunction(currentStateName,symbolRead());

        writeSymbol(reaction.symbolWrite);
        moveHead(reaction.movement);
        currentStateName = reaction.targetStateName;


        if(currentState()->isFinal())
            emit accepted(_transformationSign+"*"+QString(blank)+alpha1()+currentStateName+alpha2()+QString(blank));

        return _transformationSign+QString(blank)+alpha1()+currentStateName+alpha2()+QString(blank);
    }
    else{
        emit blocked("<p>El estado "+currentStateName+" no posee una transici&oacute;n para "+symbolRead()+".</p>");
        return " Bloqueo.";
    }

}

void TuringMachine::moveHead(QChar movement)
{
    if(movement=='L')
        if(headPosition==0)
            tape.prepend(blank);
        else
            headPosition--;

    else if(movement=='R'){
        if(headPosition==tape.count()-1)
            tape.append(blank);
        headPosition++;

    }
}

QString TuringMachine::alpha1()
{
    return tape.left(headPosition);
}

QString TuringMachine::alpha2()
{
    return tape.mid(headPosition);
}

void TuringMachine::setBlank(QChar c)
{
    removeAuxiliarySymbol(blank);
    addAxiliarySymbol(c);
    blank=c;
}

void TuringMachine::addInputSymbol(QChar c)
{
    inputAlphabet.insert(c);
}

void TuringMachine::addAxiliarySymbol(QChar c)
{
    auxiliaryAlphabet.insert(c);
}

void TuringMachine::removeInputSymbol(QChar c)
{
    inputAlphabet.remove(c);
}

void TuringMachine::removeAuxiliarySymbol(QChar c)
{
    auxiliaryAlphabet.remove(c);
}

bool TuringMachine::haveTransition(QString state, QChar symbolRead){
    bool r=false;
    if(states.contains(state))
        if(states[state]->haveATransition(symbolRead))
            r=true;
    return r;
}

Reaction TuringMachine::transitionFunction(QString state, QChar symbolRead)
{
    return states[state]->transition(symbolRead);
}

void TuringMachine::addInputSymbols(QString s)
{
    inputAlphabet.multipleInsert(s);
}

void TuringMachine::addAuxiliarySymbols(QString s)
{
    auxiliaryAlphabet.multipleInsert(s);
}

QMap<QString, State *> TuringMachine::finalStates()
{   State *s;
    QMap<QString, State *> r=states;
    QMap<QString, State *>::ConstIterator i;
    for(i=states.constBegin();i!=states.constEnd();i++){
        s=(*i);
        if(!(s->isFinal()))
            r.remove(i.key());
    }
    return r;
}

QStringList TuringMachine::transitionStringList()
{
    QStringList transitions;
    QStringList statesNames=states.keys();
    for(int i=0;i<statesNames.count();i++)
    {
        QMap <QChar, Reaction> m= transitionsMap[statesNames[i]];
        QMap <QChar, Reaction>::iterator j;

        for(j=m.begin();j!=m.end();j++)
        {
            Reaction r=j.value();
            QString mov=r.movement;

            /*if(r.movement=='L')
                mov="I";
            else if(r.movement=='R')
                mov="D";
            else
                mov="N";*/

            transitions.append("f("+statesNames[i]+","+j.key()+")=("+r.targetStateName+","+r.symbolWrite+","+mov+")");

        }

    }


    return transitions;
}

QString TuringMachine::statesText()
{
    QString r;
    QMap<QString, State*>::iterator i;
    for(i=states.begin();i!=states.end();i++){
        QString final;
        if(states[i.key()]->isFinal()){
            final="1";
        }else{
            final="0";
        }

        r+=i.key()+","+final+";";
    }
    r.chop(1);
    return r;
}

void TuringMachine::addStates(QString statesText)
{
    QStringList statesList=statesText.split(";");

    for(int i=0;i<statesList.count();i++){
        QStringList statePart=statesList.at(i).split(",");
        bool final=false;
        if(statePart.at(1)=="1")
            final=true;
        addState(statePart[0],final);
    }
}

Transition TuringMachine::parseTransition(QString transition)
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
void TuringMachine::addTransition(Transition t)
{
    addTransition(t.sourceStateName,t.readSymbol,t.symbolWrite,t.movement,t.targetStateName);
}

void TuringMachine::addTransitions(QString transitions)
{
    QStringList transitionList = transitions.split(";");
    for(int i=0;i<transitionList.count();i++)
    {
        Transition t= parseTransition(transitionList.at(i));
        addTransition(t);
    }

}

void TuringMachine::clear()
{
    states.clear();
    inputAlphabet.clear();
    auxiliaryAlphabet.clear();
    blank=QChar(916);
    addAxiliarySymbol(blank);
    initialStateName="";
    transitionsMap.clear();
}

QStringList TuringMachine::tapeAlphabetSymbols()
{
    Alphabet tapeAlphabet;
    tapeAlphabet.multipleInsert(inputAlphabet.elementsText()+","+auxiliaryAlphabet.elementsText());

    Alphabet::ConstIterator i;
    QStringList r;
    for(i=tapeAlphabet.constBegin();i!=tapeAlphabet.constEnd();i++){
        r.append(QString(QChar(*i)));
    }

    return r;
}

