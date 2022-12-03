#ifndef INCLUIRDVD_H
#define INCLUIRDVD_H

#include <QDialog>

namespace Ui {
class IncluirDVD;
}

class IncluirDVD : public QDialog
{
    Q_OBJECT

public:
    explicit IncluirDVD(QWidget *parent = nullptr);
    ~IncluirDVD();
    void clear();

public slots :

   signals: void signIncluirDVD(QString nome,QString preco,QString autor);

private slots:

    void on_buttonBox_DVD_accepted();

private:
    Ui::IncluirDVD *ui;
};

#endif // INCLUIRDVD_H
