#include "alphabet.h"
#include <QStringList>
#include <QList>
#include <QDebug>
Alphabet::Alphabet()
{

}
Alphabet::Alphabet(Alphabet *other){
    this->name=other->getName();
    Alphabet::ConstIterator i;
    for(i=other->constBegin();i!=other->constEnd();i++)
        insert(*i);
}

Alphabet::Alphabet(QString name)
{
    this->name=name;
}

bool Alphabet::insert(t_symbol s){
    bool r=false;
    if((s!=',')){
        QSet<QChar>::insert(s);
        r=true;
    }
    return r;
}
void Alphabet::multipleInsert(t_word s){
    clear();
    QStringList list=s.split(",");
    for(int i=0;i<list.count();i++)
        this->insert(list.value(i).at(0));
}

bool Alphabet::wordBelong(t_word w){
    const QString _lambda=QChar(955);
    int i=0;
    bool b=true;

    while(i<w.count()&&b){
        if(!((this->contains(w.at(i)))||w==""||w==_lambda)){
            b=false;
        }
        i++;
    }
    return b;
}

QString Alphabet::text(){
    const QString _sigma=QChar(931);
    QString text=name+":\n"+_sigma+"={"+elementsText()+"}";
    return text;
}

QString Alphabet::elementsText(){
    QString text,aux;
    QList<t_symbol> l(this->toList());
    qSort(l.begin(), l.end(), qLess<t_symbol>());

   QList<t_symbol>::const_iterator i;
   if(l.count()!=0){
       for(i=l.constBegin();i!=l.constEnd();i++){
           aux=QChar(*i);
           text+=aux+",";
        }
        text.chop(1);
   }
   return text;
}

QStringList Alphabet::symbolsList(){
    return elementsText().split(",");
}


Alphabet Alphabet::unite(Alphabet *other)
{
    Alphabet r;
    r.multipleInsert(this->elementsText());
    r.multipleInsert(other->elementsText());
    return r;
}
