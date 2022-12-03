#include "mainloja.h"
#include "loja.h"
#include "ui_mainloja.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QDialog>
#include "incluirlivro.h"



MainLoja::MainLoja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLoja)
    ,X()
    ,inclLivro(nullptr)
    ,inclDVD(nullptr)
    ,inclCD(nullptr)
    ,total_itens(nullptr)


{
    ui->setupUi(this);

    inclCD = new IncluirCD (this);
    inclDVD = new IncluirDVD (this);
    inclLivro = new IncluirLivro (this);


    //Alinhando e ajustando os cabeçalhos
    ui->CabecCD->setAlignment(Qt::AlignCenter);
    ui->CabecCD->setStyleSheet("background-color:lightgray");
    ui->CabecCD->setMaximumHeight(16);

    ui->CabecDVD->setAlignment(Qt::AlignCenter);
    ui->CabecDVD->setStyleSheet("background-color:lightgray");
    ui->CabecDVD->setMaximumHeight(16);


    ui->CabecLIV->setAlignment(Qt::AlignCenter);
    ui->CabecLIV->setStyleSheet("background-color:lightgray");
    ui->CabecLIV->setMaximumHeight(16);


    //Ajustando os cabeçalhos das Qtables
    ui->TabLivros->setHorizontalHeaderLabels(QStringList() << "NOME" << "PREÇO" << "AUTOR");
    ui->TabCds->setHorizontalHeaderLabels(QStringList() << "NOME" << "PREÇO" << "Nº FAIXAS");
    ui->TabDVDs->setHorizontalHeaderLabels(QStringList() << "NOME" << "PREÇO" << "DURAÇÃO");
    ui->TabCds->setStyleSheet( "QHeaderView::section { text-align:center }" "QHeaderView::section { font: bold }" "QHeaderView::section { background-color:lightgray }" );
    ui->TabDVDs->setStyleSheet( "QHeaderView::section { text-align:center }" "QHeaderView::section { font: bold }" "QHeaderView::section { background-color:lightgray }" );
    ui->TabLivros->setStyleSheet( "QHeaderView::section { text-align:center }" "QHeaderView::section { font: bold }" "QHeaderView::section { background-color:lightgray }" );

    //Desativando a navegacao por tab das Qtables
    ui->TabLivros->setTabKeyNavigation(false);
    ui->TabCds->setTabKeyNavigation(false);
    ui->TabDVDs->setTabKeyNavigation(false);

    //Definindo ajustes para as colunas
    ui->TabCds->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->TabCds->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->TabCds->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    ui->TabDVDs->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->TabDVDs->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->TabDVDs->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    ui->TabLivros->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->TabLivros->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->TabLivros->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);


    //inserindo informações na barra de status
    ui->statusbar->insertWidget(0,new QLabel("Total de itens: "));
    total_itens= new QLabel(this) ;
    total_itens->setNum( X.getNumCD() + X.getNumDVD()+ X.getNumLivro());
    ui->statusbar->insertWidget(1,total_itens);
    ui->statusbar->setEnabled(true);

    //conectando os sinais de inclusão ao devidos slots
    connect(inclCD,&IncluirCD::signIncluirCD,this,&MainLoja::slotIncluirCD);
    connect(inclDVD,&IncluirDVD::signIncluirDVD,this,&MainLoja::slotIncluirDVD);
    connect(inclLivro,&IncluirLivro::signIncluirLivro,this,&MainLoja::slotIncluirLivro);

    //exibindo todas as tabelas
    exibir();


 }

MainLoja::~MainLoja()
{
    delete ui;
}


void MainLoja::on_TabLivros_cellDoubleClicked(int row)
{
    QMessageBox::StandardButton resp;
    Livro L = X.getLivro(row);
    QString name = QString::fromStdString(L.getNome());

    resp = QMessageBox::question(this, tr("Excluir Livro"),tr("Deseja realmente excluir o item?\nNome: "+name.toLatin1()));
    if(resp==QMessageBox::Yes)
    {
       X.excluirLivro(row);
       exibir_Livros();
       atualiza_totitens();
    }
}

void MainLoja::on_TabCds_cellDoubleClicked(int row)
{
   QMessageBox::StandardButton resp;
   CD C = X.getCD(row);
   QString name = QString::fromStdString(C.getNome());

   resp = QMessageBox::question(this, tr("Excluir CD"),tr("Deseja realmente excluir o item?\nNome: "+name.toLatin1()));
   if(resp==QMessageBox::Yes)
   {
       X.excluirCD(row);
       exibir_CDs();
       atualiza_totitens();
   }
}

void MainLoja::on_TabDVDs_cellDoubleClicked(int row)
{
    QMessageBox::StandardButton resp;
    DVD D = X.getDVD(row);
    QString name = QString::fromStdString(D.getNome());

    resp = QMessageBox::question(this, tr("Excluir DVD"),tr("Deseja realmente excluir o item?\nNome: "+name.toLatin1()));
    if(resp==QMessageBox::Yes)
    {
        X.excluirDVD(row);
        exibir_DVDs();
        atualiza_totitens();
    }
}

void MainLoja::on_actionLer_triggered()
{
   QString fileName = QFileDialog::getOpenFileName(this,"Ler estoque",QString(),"Estoques (*.txt)");
   std::string str = fileName.toStdString();
   if(!X.ler(str))
   {
      QMessageBox::critical(this, tr("Erro!"), tr("Não foi possivel ler o arquivo!"));
      return;
   }

   exibir();

}

void MainLoja::on_actionSalvar_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Salvar estoque", "estoque","Estoques (*.txt)");
    std::string str = fileName.toStdString();
    if(!X.salvar(str))
    {
       QMessageBox::critical(this, tr("Erro!"), tr("Não foi possivel salvar o arquivo!"));
       return;
    }
}

void MainLoja::on_actionSair_triggered()
{
    QCoreApplication::quit();
}


void MainLoja::on_actionIncluir_Livro_triggered()
{
    inclLivro->clear();
    inclLivro->show();
}


void MainLoja::on_actionIncluir_CD_triggered()
{
    inclCD->clear();
    inclCD->show();
}


void MainLoja::on_actionIncluir_DVD_triggered()
{
    inclDVD->clear();
    inclDVD->show();
}

void MainLoja::slotIncluirLivro(QString nome, QString preco, QString autor)
{
    std::string name = nome.toStdString();
    float valor = preco.toFloat();
    valor = round(valor * 100);
    std::string aut = autor.toStdString();

    if(name==""||valor<=0.||aut==""){
         QMessageBox::critical(this, tr("Livro Invalido!"), tr("Não foi possivel incluir o livro!\nNome= "+ nome.toLatin1()+"\nPreco="+preco.toLatin1()+"\nAutor="+autor.toLatin1()));
         return;
    }
    X.incluirLivro(Livro(name,valor,aut));
    exibir_Livros();
    atualiza_totitens();
}

void MainLoja::slotIncluirCD(QString nome, QString preco, QString numfaixas)
{
    std::string name = nome.toStdString();
    float valor = preco.toFloat();
    valor =  round(valor * 100);
    int faixas = numfaixas.toFloat();
    if(name==""||valor<=0.||faixas<=0){
         QMessageBox::critical(this, tr("CD Invalido!"), tr("Não foi possivel incluir o CD!\nNome= "+ nome.toLatin1()+"\nPreco="+preco.toLatin1()+"\nAutor="+numfaixas.toLatin1()));
         return;
    }
    X.incluirCD(CD(name,valor,faixas));
    exibir_CDs();
   atualiza_totitens();
}

void MainLoja::slotIncluirDVD(QString nome, QString preco, QString duracao)
{
    std::string name = nome.toStdString();
    float valor = preco.toFloat();
    valor = round(valor * 100);
    int dur = duracao.toFloat();
    if(name==""||valor<=0.||dur<=0){
         QMessageBox::critical(this, tr("DVD Invalido!"), tr("Não foi possivel incluir o DVD!\nNome= "+ nome.toLatin1()+"\nPreco="+preco.toLatin1()+"\nAutor="+duracao.toLatin1() ));
         return;
    }
    X.incluirDVD(DVD(name,valor,dur));
    exibir_DVDs();
    atualiza_totitens();

}

void MainLoja::exibir_Livros()
{
   ui->TabLivros->clearContents();
   ui->TabLivros->setRowCount(X.getNumLivro());

   for(int i=0;i<X.getNumLivro();i++)
   {
       Livro L=X.getLivro(i);
       QLabel* prov(nullptr);

       prov = new QLabel(L.getNome().c_str());
       prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
       ui->TabLivros->setCellWidget(i,0,prov);

       prov = new QLabel(QString::number(L.getPreco(),'f',2));
       prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
       ui->TabLivros->setCellWidget(i,1,prov);

       prov = new QLabel(L.getAutor().c_str());
       prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
       ui->TabLivros->setCellWidget(i,2,prov);

   }

}

void MainLoja::exibir_CDs()
{
    ui->TabCds->clearContents();
    ui->TabCds->setRowCount(X.getNumCD());

    for(int i=0;i<X.getNumCD();i++)
    {
        CD C=X.getCD(i);
        QLabel* prov(nullptr);

        prov = new QLabel(C.getNome().c_str());
        prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        ui->TabCds->setCellWidget(i,0,prov);

        prov = new QLabel(QString::number(C.getPreco(),'f',2));
        prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        ui->TabCds->setCellWidget(i,1,prov);

        prov = new QLabel(QString::number(C.getNumFaixas()));
        prov->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->TabCds->setCellWidget(i,2,prov);
    }
}

void MainLoja::exibir_DVDs()
{
    ui->TabDVDs->clearContents();
    ui->TabDVDs->setRowCount(X.getNumDVD());

    for(int i=0;i<X.getNumDVD();i++)
    {
        DVD D=X.getDVD(i);
        QLabel* prov(nullptr);

        prov = new QLabel(D.getNome().c_str());
        prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        ui->TabDVDs->setCellWidget(i,0,prov);

        prov = new QLabel(QString::number(D.getPreco(),'f',2));
        prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        ui->TabDVDs->setCellWidget(i,1,prov);

        prov = new QLabel(QString::number(D.getDuracao()));
        prov->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->TabDVDs->setCellWidget(i,2,prov);
    }
}

void MainLoja::exibir()
{
    exibir_Livros();
    exibir_CDs();
    exibir_DVDs();
    atualiza_totitens();
}

void MainLoja::atualiza_totitens()
{
    total_itens->setNum( X.getNumCD() + X.getNumDVD()+ X.getNumLivro());
}
