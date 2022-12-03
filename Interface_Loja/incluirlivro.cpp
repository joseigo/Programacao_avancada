#include "incluirlivro.h"
#include "ui_incluirlivro.h"

IncluirLivro::IncluirLivro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirLivro)
{
    ui->setupUi(this);
}

IncluirLivro::~IncluirLivro()
{
    delete ui;
}

void IncluirLivro::clear()
{
    ui->nome_livro->setText("");
    ui->preco_livro->setText("");
    ui->autor_livro->setText("");
}

void IncluirLivro::on_buttonBox_livro_accepted()
{
    QString nome_prov,preco_prov,autor_prov;
    nome_prov = ui->nome_livro->text();
    preco_prov = ui->preco_livro->text();
    autor_prov = ui->autor_livro->text();
    emit signIncluirLivro(nome_prov,preco_prov,autor_prov);
}

