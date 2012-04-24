#ifndef STATE_H
#define STATE_H

#include <QMap>
#include <QString>
#include <QStringList>

struct t_stimulus{
    QString sourceStateName;
    QChar readSymbol;
};
typedef struct t_stimulus Stimulus;
struct t_reaction{
    QChar symbolWrite;
    QChar movement;
    QString targetStateName;
};
typedef struct t_reaction Reaction;
struct t_transition{
    QString sourceStateName;
    QChar readSymbol;
    QChar symbolWrite;
    QChar movement;
    QString targetStateName;
};
typedef struct t_transition Transition;


class State
{
private:
    QString name;
    bool final;


    QMap<QChar, Reaction> transitionMap;

public:

    State();
    State(QString name, bool final);
    State(State *other);
    State(QString name);

    inline QString getName()const{return name;}
    inline void setName(QString name){this->name=name;}
    inline bool isFinal(){return final;}
    inline void setFinal(bool final){this->final=final;}

    void addTransition(QChar symbolRead,QChar symbolWrite,QChar movement,QString target);
    inline bool haveATransition(QChar symbolRead){return transitionMap.contains(symbolRead);}

    QChar transitionMovement(QChar symbolRead);
    QChar transitionWrite(QChar symbolRead);
    QString transitionTarget(QChar symbolRead);

    Reaction transition(QChar symbolRead);

    QStringList transitionStringList();


};

#endif // STATE_H
