#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include "Poly.h"

using namespace std;

Poly::Poly (): grau(-1),a(nullptr)
{
}
Poly::Poly(int g): grau(g)
{
    if(grau<0) a=nullptr;

    else if(grau==0)
    {
        a =new double [1];
        a[0]=0.0;
    }
    else
    {
        a=new double [grau+1];
        for( int i=0; i<=grau; i++)
        {
            a[i] = (i==grau) ? (1.0) : (0.0);
        }
    }
}
Poly::Poly(const  Poly &P2): grau(P2.grau), a(nullptr)
{
    if (grau>=0)
    {
        a=new double [grau+1];
        for (int i=0; i<=P2.grau; i++)
        {
            a[i]=P2.a[i];
        }
    }
}

Poly::Poly(Poly &&P2): grau(P2.grau), a(P2.a)
{
    P2.grau=-1;
    P2.a=nullptr;
}
Poly::~Poly()
{
    delete []a;
    a=nullptr;
}

Poly Poly::operator=(const Poly &P2)
{
    if (this != &P2)
    {
        delete[]a;
        grau=P2.grau;
        a=nullptr;

        if (grau>=0)
        {
            a=new double [grau+1];
            for (int i=0; i<=P2.grau; i++)
            {
                a[i]=P2.a[i];
            }
        }
        return *this;
    }
}
Poly Poly::operator=(Poly &&P2)
{
    delete []a;
    grau = P2.grau;
    a = P2.a;
    P2.grau=-1;
    P2.a=nullptr;
    return *this;
}

void Poly::recriar(int g)
{
    if(grau==g)
    {
        for( int i=0; i<=grau; i++)
        {
            a[i] = (i==grau) ? (1.0) : (0.0);
        }
        return;
    }

    *this = Poly(g);
}

bool Poly::empty() const
{
    return (grau<0);
}

bool Poly::isZero() const
{
    return (grau==0 && a[0]==0.0);
}

int Poly::getGrau() const
{
    return grau;
}

double Poly::getCoef(int i) const
{
    return (i<0 || i>grau)? 0.0 : a[i];
}

double Poly::operator[](int i) const
{
    return getCoef(i);
}

double Poly::getValor(double v) const
{
    if (empty()) return 0;

    double sum = 0.0;
    for (int i=0; i<grau+1; i++)
    {
        sum +=(a[i] * pow(v,i));
    }
    return sum;
}

double Poly::operator()(double v) const
{
    return getValor(v);
}

void Poly::setCoef(int i, double v)
{
    if(i<0 || i>grau)
    {
        cerr<<"Valor de indice invalido"<<endl;;
    }

    if (i==grau && v==0.0 && !isZero())
    {
        cerr<<"Valor de coeficiente invalido"<<endl;
    }
    else
    {
        a[i]=v;
    }
}
bool Poly::ler(const string &x)
{
    ifstream arquivo;
    arquivo.open(x);
    if(!arquivo.is_open()) return false;

    string palav_reserv;
    arquivo >> palav_reserv;

    if(!arquivo.good()|| palav_reserv!="POLY")
    {
        arquivo.close();
        return false;
    }
    int g;
    arquivo >> g;
    if(!arquivo.good())
    {
        arquivo.close();
        return false;
    }
    if(g<0)
    {
        arquivo.close();
        *this=Poly();
        return true;
    }

    Poly aux(g);
    for (int i=0; i<=aux.grau; i++)
    {
        arquivo >> aux.a[i];
        if (!arquivo.good())
        {
            arquivo.close();
            return false;
        }
    }
    if(aux[aux.grau]==0 && aux.grau>0)
    {
        arquivo.close();
        return false;
    }

    *this=aux;
    arquivo.close();
    return true;
}

bool Poly::salvar(const string &x) const
{
    ofstream arquivo;
    arquivo.open(x,ios::trunc);
    if(arquivo.fail()) return false;

    arquivo << "POLY"<<' '<<grau<<endl;;
    for( int i=0; i<=grau; i++)
    {
        arquivo <<a[i]<<' ';
    }
    arquivo <<endl;
    arquivo.close();
    return true;
}

ostream& operator<<(ostream& X, const Poly & P)
{
    if (P.grau<0)
    {
    }
    else
    {
        for (int i=P.grau; i>=0; i--)
        {
            if (P.a[i]==0.0)
            {
                if(i==0 && P.grau==0)
                {
                    X<<P.a[i];
                }
            }
            else
            {
                if(P.a[i]<0.0)
                {
                    X<<'-';
                }
                else
                {
                    if(i!=P.grau)
                    {
                        X<<'+';
                    }
                }

                if( abs(P.a[i])!=1.0 || i==0 )
                {
                    X<<abs(P.a[i]);
                }
                if (i!=0)
                {
                    if(abs(P.a[i])!=1.0)
                    {
                        X<<'*';
                    }
                    X<<'x';

                    if(i>1)
                    {
                        X<<'^';
                        X<<i;
                    }
                }
            }
        }
    }
    return X;
}

istream &operator>>(istream &X, Poly &P)
{
    if(P.empty())
    {
        cerr<<"Polinimio invalido(Empty)!"<<endl;
    }
    for( int i=P.grau; i>=0; i--)
    {
        do
        {
            cout<<"Digite o Coeficiente de x^"<<i<<": ";
            X>>P.a[i];
        }
        while(i==P.grau && P.grau>0 && P.a[P.grau]==0.0);
    }
    return X ;
}

Poly Poly::operator+(const Poly &P2) const
{
    if(P2.empty()) return *this;
    if(empty())return P2;
    if(P2.isZero()) return *this;
    if(isZero()) return P2;

    Poly sum(max(getGrau(),P2.getGrau()));
    for(int i=0; i<=sum.grau; i++)
    {
        sum.a[i]=getCoef(i)+P2[i];
    }
    return sum.cutGrau();
}

Poly Poly::operator -(const Poly &P2) const
{
    if(P2.empty()) return *this;
    if(empty())return -P2;
    if(P2.isZero()) return *this;
    if(isZero()) return -P2;

    Poly sub(max(getGrau(),P2.getGrau()));
    for(int i=0; i<=sub.grau; i++)
    {
        sub.a[i] = getCoef(i)- P2[i];
    }

    return sub.cutGrau();
}

Poly Poly::operator-()const
{
    if (empty()) return Poly();
    if(isZero()) return Poly(0);
    Poly aux(grau);

    for(int i=0; i<=aux.grau; i++)
    {
        aux.a[i]=getCoef(i)*(-1);
    }
    return aux;
}

Poly Poly::operator*(const Poly &P2) const
{
    if(empty()) return Poly();
    if(P2.empty())return Poly();
    if(isZero()) return Poly(0);
    if(P2.isZero()) return Poly(0);

    Poly aux(grau+P2.grau);
    aux.a[aux.grau]=0.0;

    for(int i=0; i<=grau; i++)
    {
        for(int j=0; j<=P2.grau; j++)
        {
            aux.a[i+j]+=(getCoef(i)*P2[j]);
        }
    }
    return aux;
}
Poly Poly::operator/(const Poly &P2)const
{
    if(P2.isZero())
    {
        cerr<<"Divisao impossivel!!"<<endl;
        return Poly();
    }
    if(P2.grau>grau) return Poly();//Pois gera um polinomio de grau negativo
    if(empty()) return Poly();
    if(P2.empty())
    {
        cerr<<"Divisao impossivel!!"<<endl;
        return Poly();
    }
    if(isZero()) return Poly(0);

    Poly q(grau-P2.grau);
    q.a[q.grau]=0.0;
    Poly r(*this);
    Poly aux(r.DLT(P2));

    while(!r.isZero() && aux.grau>=0)
    {
        aux= r.DLT(P2);
        q = (q + aux) ;
        r = r -(aux*P2);
    }
    return q;
}
Poly Poly::operator%(const Poly &P2)const
{
    if(P2.isZero())
    {
        cerr<<"Divisao impossivel!!"<<endl;
        return Poly();
    }
    if(P2.grau>grau) return Poly();//Pois gera um polinomio de grau negativo
    if(empty()) return Poly();
    if(P2.empty())
    {
        cerr<<"Divisao impossivel!!"<<endl;
        return Poly();
    }
    if(isZero()) return Poly(0);

    Poly r(*this);
    Poly aux(r.DLT(P2));

    while(!r.isZero() && aux.grau>=0)
    {
        aux= r.DLT(P2);
        r = r - (aux*P2);
    }
    return r;
}
Poly Poly::DLT(const Poly &P2)const
{
    if(P2.isZero()) return Poly();
    if(P2.grau>grau) return Poly();
    if(isZero()) return Poly(0);

    Poly aux(grau-P2.grau);
    aux.a[aux.grau]= a[grau]/P2[P2.grau];
    return aux;
}

Poly Poly::cutGrau()
{
    while (a[grau]==0.0 && grau>0)
    {
        grau--;
    }

    Poly aux(grau);
    for (int i=0; i<=aux.grau; i++)
    {
        aux.a[i]=a[i];
    }
    *this=aux;

    return *this;
}
