#include "incluirdvd.h"
#include "ui_incluirdvd.h"

IncluirDVD::IncluirDVD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirDVD)
{
    ui->setupUi(this);
}

IncluirDVD::~IncluirDVD()
{
    delete ui;
}

void IncluirDVD::clear()
{
    ui->nome_DVD->setText("");
    ui->preco_DVD->setText("");
    ui->durac_DVD->setText("");
}

void IncluirDVD::on_buttonBox_DVD_accepted()
{
    QString nome_prov,preco_prov,durac_prov;
    nome_prov = ui->nome_DVD->text();
    preco_prov = ui->preco_DVD->text();
    durac_prov = ui->durac_DVD->text();
    emit signIncluirDVD(nome_prov,preco_prov,durac_prov);
}

