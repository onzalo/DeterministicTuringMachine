#ifndef DIALOGINITIALSTATE_H
#define DIALOGINITIALSTATE_H

#include <QDialog>

namespace Ui {
    class DialogInitialState;
}

class DialogInitialState : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInitialState(QWidget *parent = 0);
    ~DialogInitialState();
    void setStates(QStringList states);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogInitialState *ui;
signals:
    void initialStateSelected(QString stateName);
};


#endif // DIALOGINITIALSTATE_H
s
