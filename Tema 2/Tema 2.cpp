#include <iostream>
using namespace std;


class Complex {
    float real;
    float imaginar;

public:
    //Constructori
    //Default
    Complex() {
        real = 0;
        imaginar = 0;
    }

    //Parametrizat
    Complex(float a, float b) {
        real = a;
        imaginar = b;
    }

    //De copiere
    Complex(const Complex &ob) {
        real = ob.real;
        imaginar = ob.imaginar;
    }

    void setReal(float x) {
        real = x;
    }

    void setImaginar(float x) {
        imaginar = x;
    }

    float getReal() {
        return real;
    }

    float getImaginar() {
        return imaginar;
    }

    //Supraincarcarea >>
    friend istream& operator>>(istream& input, Complex& ob) {
        input >> ob.real >> ob.imaginar;
        return input;
    }

    //Supraincarcarea <<
    friend ostream& operator<<(ostream& output, Complex& ob) {
        if (!ob.imaginar) 
            output << ob.real;
        else 
            output << ob.real << " + " << ob.imaginar << 'i';
        return output;
    }

    //Supraincarcarea =
    Complex& operator=(const Complex& ob) {
        real = ob.real;
        imaginar = ob.imaginar;
        return *this;
    }

    //Destructor
    ~Complex() {
    }

};

class Matrice {
protected:
    Complex** v;
public:
    //Constructori
    //Default
    Matrice() {
        cout << "Constructor Matrice Default" << endl;
    }

    //Parametrizat
    Matrice(int n, int m) {
        cout << "Constructor Matrice Parametrizat" << endl;

    }

    //De copiere
    Matrice(const Matrice& mat) {
        cout << "Constructor Matrice De Copiere" << endl;
    }

    void setElement(int n, int m , Complex val) {
        v[n][m] = val;
    }

    virtual void print() = 0;

    virtual void alloc() = 0;

    //Supraincarcare >>
   /* friend istream& operator>>(istream& input, Matrice& mat) {
        int n = mat.lin;
        int m = mat.col;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                input >> mat.v[i][j];

        return input;
    }*/


    virtual ~Matrice() {
        cout << "tadammmm" << '\n';
    }

};

class Matrice_patratica : public Matrice {
    int dim;
public:
    //Constructor Default
    Matrice_patratica() {
        dim = 1;
        alloc();
        v[0][0] = Complex(0, 0);
        cout << "Constructor Matrice Patratica Default" << endl;
    }
    
    //Constructor Parametrizat
    Matrice_patratica(int size) : dim(size) {
        alloc();
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                v[i][j] = Complex(0, 0);
        cout << "Constructor Matrice Patratica Parametrizat" << endl;
    }

    //Constructor De Copiere
    Matrice_patratica(const Matrice_patratica& mat) {
        dim = mat.dim;
        alloc();
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                v[i][j] = mat.v[i][j];

        cout << "Constructor Matrice Patratica De Copiere" << endl;
    }

    void print() {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++)
                cout << v[i][j] << "  ";
            cout << endl;
        }
    }

    bool triunghiulara() {
        if (t_sup() || t_inf())
            return true;
        return false;
    }

    bool t_sup() {
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                if ((v[i][j].getImaginar() != 0 || v[i][j].getReal() != 0) && i > j)
                    return false;
        return true;
    }

    bool t_inf() {
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                if ((v[i][j].getImaginar() != 0 || v[i][j].getReal() != 0) && i < j)
                    return false;
        return true;
    }

    bool diagonala() {
        if (t_sup() && t_inf()) {
            for (int i = 0; i < dim; i++)
                if (v[i][i].getImaginar() == 0 && v[i][i].getReal() == 0)
                    return false;
            return true;
        }
        return false;
    }

    void alloc() {
        v = new Complex*[dim];
        for (int i = 0; i < dim; i++) {
            v[i] = new Complex[dim];
        }
        cout << "Matrice patrata alocata" << '\n';
    }

    ~Matrice_patratica() {
        for (int i = 0; i < dim; i++)
            delete[] v[i];
        delete[] v;
        cout << "Destructor Matrice patratica" << '\n';

    }

};

class Matrice_oarecare : public Matrice {
    int lin;
    int col;
public:
    //Constructori
    //Default
    Matrice_oarecare() {
        lin = 1;
        col = 1;
        alloc();
        v[0][0] = Complex(0, 0);
    }

    //Parametrizat
    Matrice_oarecare(int n, int m) {
        lin = n;
        col = m;
        alloc();
        for (int i = 0; i < lin; i++)
            for (int j = 0; j < col; j++)
                v[i][j] = Complex(0, 0);
        cout << "-----" << '\n';
    }

    //De copiere
    Matrice_oarecare(const Matrice_oarecare& mat) {
        lin = mat.lin;
        col = mat.col;
        alloc();
        for (int i = 0; i < lin; i++)
            for (int j = 0; j < col; j++)
                this->v[i][j] = mat.v[i][j];

    }

    void print() {
        for (int i = 0; i < lin; i++) {
            for (int j = 0; j < col; j++)
                cout << v[i][j] << "  ";
            cout << endl;
        }
    }

    void alloc() {
        v = new Complex * [lin];
        for (int i = 0; i < lin; i++) {
            v[i] = new Complex[col];
        }
        cout << "Matrice oarecare alocata" << '\n';
    }

    ~Matrice_oarecare() {
        for (int i = 0; i < lin; i++)
            delete[] v[i];
        delete[] v;
        cout << "Destructor Matrice oarecare" << '\n';
    }

};

int main()
{
    Matrice_patratica mat(3);
    mat.setElement(0, 0, Complex(3, 1));
    mat.setElement(1, 1, Complex(3, 2));
    mat.setElement(2, 2, Complex(3, 3));
    mat.setElement(1, 2, Complex(3, 3));
    mat.setElement(2, 1, Complex(3, 3));
    mat.print();
    return 0;
}