#ifndef DIALOGTRANSITION_H
#define DIALOGTRANSITION_H

#include <QDialog>
#include <QStringList>

namespace Ui {
    class DialogTransition;
}

class DialogTransition : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTransition(QWidget *parent = 0);
    ~DialogTransition();

private:
    Ui::DialogTransition *ui;
public slots:
    void initialize(QStringList states,QStringList tapeAlphabet);
    void on_buttonBox_accepted();
signals:
    void addTransition(QString sourceStateName, QChar symbolRead,QChar symbolWrite, QChar movement, QString targetStateName);
};

#endif // DIALOGTRANSITION_H
