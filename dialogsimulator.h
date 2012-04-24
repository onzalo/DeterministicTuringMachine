#ifndef DIALOGSIMULATOR_H
#define DIALOGSIMULATOR_H

#include <QDialog>
#include <QString>

namespace Ui {
    class DialogSimulator;
}

class DialogSimulator : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSimulator(QWidget *parent = 0);
    ~DialogSimulator();
    QString input;
    void initializeSimulator(QString input);
    void setTape(QString tape);
    void setInputTitle(QString input);
    void addConfiguration(QString configurtion);


private:
    Ui::DialogSimulator *ui;
public slots:
    void accepted(QString configuration);
    void blocked(QString configuration);

private slots:
    void on_pb_makeTransition_clicked();

signals:
    void makeTransition();
};

#endif // DIALOGSIMULATOR_H
