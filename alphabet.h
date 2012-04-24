#ifndef ALPHABET_H
#define ALPHABET_H

#include <QSet>
typedef QChar t_symbol;
typedef QString t_word;

class Alphabet : public QSet<t_symbol>
{
public:
    //Constructores
    Alphabet();
    Alphabet(Alphabet *other);
    Alphabet(QString name);
    bool insert(t_symbol s);
    void multipleInsert(QString s);
    bool wordBelong(t_word w);
    QString text();
    QString elementsText();
    inline void setName(QString n){name=n;}
    inline QString getName()const{return name;}
    Alphabet unite(Alphabet *other);
    QStringList symbolsList();

private:
    QString name;
};

#endif // ALPHABET_H
