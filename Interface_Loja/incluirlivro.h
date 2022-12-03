#ifndef INCLUIRLIVRO_H
#define INCLUIRLIVRO_H

#include <QDialog>

namespace Ui {
class IncluirLivro;
}

class IncluirLivro : public QDialog
{
    Q_OBJECT

public:
    explicit IncluirLivro(QWidget *parent = nullptr);
    ~IncluirLivro();
    void clear();

public slots :

   signals: void signIncluirLivro(QString nome,QString preco,QString autor);

private slots:

    void on_buttonBox_livro_accepted();

private:
    Ui::IncluirLivro *ui;

};

#endif // INCLUIRLIVRO_H
