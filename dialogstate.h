#ifndef DIALOGSTATE_H
#define DIALOGSTATE_H

#include <QDialog>

namespace Ui {
    class DialogState;
}

class DialogState : public QDialog
{
    Q_OBJECT

public:

    explicit DialogState(QWidget *parent = 0);
    ~DialogState();
    int exec();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogState *ui;

signals:
    void newState(QString nameState,bool final);



};

#endif // DIALOGSTATE_H
