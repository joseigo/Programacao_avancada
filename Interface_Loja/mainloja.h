#ifndef MAINLOJA_H
#define MAINLOJA_H

#include <QMainWindow>
#include "incluircd.h"
#include "incluirdvd.h"
#include "incluirlivro.h"
#include "loja.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainLoja; }
QT_END_NAMESPACE

class MainLoja : public QMainWindow
{
    Q_OBJECT

public:
    MainLoja(QWidget *parent = nullptr);
    ~MainLoja();

    void exibir_Livros();
    void exibir_CDs();
    void exibir_DVDs();
    void exibir();
    void atualiza_totitens();


private slots:
    void on_TabLivros_cellDoubleClicked(int row);

    void on_TabCds_cellDoubleClicked(int row);

    void on_TabDVDs_cellDoubleClicked(int row);

    void on_actionLer_triggered();

    void on_actionSalvar_triggered();

    void on_actionSair_triggered();

    void on_actionIncluir_Livro_triggered();

    void on_actionIncluir_CD_triggered();

    void on_actionIncluir_DVD_triggered();

    void slotIncluirLivro(QString nome, QString preco, QString autor);

    void slotIncluirCD(QString nome, QString preco, QString numfaixas);

    void slotIncluirDVD(QString nome, QString preco, QString duracao);



private:
    Ui::MainLoja *ui;
    Loja X;
    IncluirLivro* inclLivro;
    IncluirDVD* inclDVD;
    IncluirCD*  inclCD;
    QLabel* total_itens;
};
#endif // MAINLOJA_H
