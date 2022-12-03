#include "incluircd.h"
#include "ui_incluircd.h"

IncluirCD::IncluirCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirCD)
{
    ui->setupUi(this);
}

IncluirCD::~IncluirCD()
{
    delete ui;
}

void IncluirCD::clear()
{
    ui->nome_CD->setText("");
    ui->preco_CD->setText("");
    ui->faixas_CD->setText("");
}

void IncluirCD::on_buttonBox_CD_accepted()
{
    QString nome_prov,preco_prov,faixas_prov;
    nome_prov = ui->nome_CD->text();
    preco_prov = ui->preco_CD->text();
    faixas_prov = ui->faixas_CD->text();
    emit signIncluirCD(nome_prov,preco_prov,faixas_prov);
}

