#include "state.h"
#include <QDebug>

State::State()
{

}

State::State(QString name, bool final){
    this->name=name;
    this->final=final;

}
State::State(QString name){
   State(name, true);
}

State::State(State *other){
    State(other->getName(),other->isFinal());
}

void State::addTransition(QChar symbolRead,QChar symbolWrite,QChar movement,QString target)
{
    transitionMap[symbolRead].symbolWrite=symbolWrite;
    transitionMap[symbolRead].movement=movement;
    transitionMap[symbolRead].targetStateName=target;
}



QChar State::transitionMovement(QChar symbolRead)
{
    return transitionMap[symbolRead].movement;
}

QChar State::transitionWrite(QChar symbolRead)
{
    return transitionMap[symbolRead].symbolWrite;
}

QString State::transitionTarget(QChar symbolRead)
{
    return transitionMap[symbolRead].targetStateName;
}

QStringList State::transitionStringList(){
     qDebug()<<"f";
    QStringList transitions;
    QList<QChar> keys= transitionMap.keys();

    qDebug()<<transitionMap.count();
    for(int i=0;i<keys.count();i++){
        Reaction r=transitionMap.value(keys.at(i));
        transitions.append("f("+this->name+","+keys.at(i)+")=("+r.targetStateName+","+r.symbolWrite+","+r.movement+")");
        qDebug()<<"f("+this->name+","+keys.at(i)+")=("+r.targetStateName+","+r.symbolWrite+","+r.movement+")";
    }
    /*
    QMap<QChar, Reaction>::iterator i;

    for(i=transitionMap.begin();i!=transitionMap.end();i++){
        Reaction r=i.value();
        transitions.append("f("+this->name+","+i.key()+")=("+r.targetStateName+","+r.symbolWrite+","+r.movement+")");

        qDebug()<<"f("+this->name+","+i.key()+")=("+r.targetStateName+","+r.symbolWrite+","+r.movement+")";
    }*/

    return transitions;
}

Reaction State::transition(QChar symbolRead)
{
    return transitionMap[symbolRead];
}

