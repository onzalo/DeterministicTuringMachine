#ifndef DIALOGBLANK_H
#define DIALOGBLANK_H
//
//Diálogo para elegir el símbolo blanco
//
#include <QDialog>

namespace Ui {
    class DialogBlank;
}

class DialogBlank : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBlank(QWidget *parent = 0);
    ~DialogBlank();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogBlank *ui;
signals:
    void changeBlank(QChar c);
};

#endif // DIALOGBLANK_H
