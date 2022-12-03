#ifndef _POLY_H_
#define _POLY_H_


class Poly
{

private:

    int grau;
    double *a;

public:

    Poly();
    Poly (int g);
    Poly (const Poly &P2);
    Poly(Poly &&P2);
    Poly (const Poly && P2)=delete;
    ~Poly();
    Poly operator=(const Poly &P2);
    Poly operator=(Poly &&P2);
    void recriar(int i);
    bool empty() const;
    bool isZero() const;
    int getGrau()const;
    double getCoef(int i) const;
    double operator[](int i) const;
    double getValor(double v)const;
    double operator() (double v) const;
    void setCoef(int i, double v);
    bool salvar(const std::string &x) const;
    bool ler(const std::string &x);
    friend std::ostream &operator<<(std::ostream &X, const Poly &P);
    friend std::istream &operator>>(std::istream &X, Poly &P);
    Poly operator+(const Poly &P2) const;
    Poly operator-(const Poly &P2) const;
    Poly operator-()const;
    Poly operator*(const Poly &P2) const;
    Poly operator/(const Poly &P2)const;
    Poly operator%(const Poly &P2)const;
    Poly cutGrau();
    Poly DLT(const Poly &P2)const;//Divisão dos Termos Dominantes

};

#endif
