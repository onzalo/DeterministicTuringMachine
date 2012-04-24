#ifndef DIALOGALPHABET_H
#define DIALOGALPHABET_H

#include <QDialog>

namespace Ui {
    class dialogAlphabet;
}

class DialogAlphabet : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAlphabet(QWidget *parent = 0);
    ~DialogAlphabet();
    void setSymbols(QString s);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::dialogAlphabet *ui;
signals:
    void editInputSymbols(QString symbols);
    void editAuxiliarySymbols(QString symbols);
};

#endif // DIALOGALPHABET_H
