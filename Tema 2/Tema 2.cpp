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
        else if (!ob.real)
            output << ob.imaginar << 'i';
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

    Complex operator+(const Complex& ob) {
        Complex res;
        res.real = real + ob.real;
        res.imaginar = imaginar + ob.imaginar;
        return res;
    }

    Complex operator*(const Complex& ob) {
        Complex res;
        res.real = real * ob.real - imaginar * ob.imaginar;
        res.imaginar = real * ob.imaginar + imaginar * ob.real;
        return res;
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
        v = nullptr;
    }

    //Parametrizat
    Matrice(int n, int m) {
        v = nullptr;
    }

    //De copiere
    Matrice(const Matrice& mat) {
        v = nullptr;
    }

    void setElement(int n, int m , Complex val) {
        v[n][m] = val;
    }

    virtual void print() = 0;

    virtual void alloc() = 0;

    virtual ~Matrice() {}

};

class Matrice_patratica : public Matrice {
    int dim;
public:
    //Constructor Default
    Matrice_patratica() {
        dim = 1;
        alloc();
        v[0][0] = Complex(0, 0);
    }
    
    //Constructor Parametrizat
    Matrice_patratica(int size) : dim(size) {
        alloc();
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                v[i][j] = Complex(0, 0);
    }

    //Constructor De Copiere
    Matrice_patratica(const Matrice_patratica& mat) {
        dim = mat.dim;
        alloc();
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                v[i][j] = mat.v[i][j];
    }

    void print() {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++)
                cout << v[i][j] << "  ";
            cout << endl;
        }
        cout << "Determinant: ";
        Complex Det;
        Det = deter(*this, dim);
        cout << Det;
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
    }

    void getCofactor(Matrice_patratica mat, Matrice_patratica &temp, int p, int q, int n) {
        int i = 0, j = 0;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (row != p && col != q) {
                    temp.v[i][j] = mat.v[row][col];
                    j++;
                    if (j == n - 1) {
                        j = 0;
                        i++;
                    }
                }
            }

        }
    }

    Complex deter(Matrice_patratica mat, int n) {
        Complex D;
        if (n == 1)
            return mat.v[0][0];
        Matrice_patratica temp(n);
        Complex sign(1, 0);
        for (int f = 0; f < n; f++) {
            getCofactor(mat, temp, 0, f, n);
            D = D + (sign * mat.v[0][f] * deter(temp, n - 1));
            Complex neg(-1, 0);
            sign = sign * neg;  
        }
        return D;
    }

    //Supraincarcare >>
    friend istream& operator>>(istream& input, Matrice_patratica& mat) {
        int n = mat.dim;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                input >> mat.v[i][j];

        return input;
    }

    ~Matrice_patratica() {
        for (int i = 0; i < dim; i++)
            delete[] v[i];
        delete[] v;

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
    }

    //Supraincarcare >>
    friend istream& operator>>(istream& input, Matrice_oarecare& mat) {
        int n = mat.lin;
        int m = mat.col;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                input >> mat.v[i][j];

        return input;
    }

    ~Matrice_oarecare() {
        for (int i = 0; i < lin; i++)
            delete[] v[i];
        delete[] v;
    }

};

int main()
{
   
    Matrice_patratica mat(3);
    mat.setElement(0, 0, Complex(3, 0));
    mat.setElement(0, 1, Complex(3, 3));
    mat.setElement(1, 0, Complex(2, 0));
    mat.setElement(1, 1, Complex(5, 0));

    mat.setElement(1, 2, Complex(5, 0));
    mat.setElement(2, 0, Complex(5, 6));
    mat.setElement(2, 1, Complex(6, 0));
    mat.setElement(2, 2, Complex(2, -8));

    mat.print();
    

    /*
    Matrice_patratica mat3(2);
    cin >> mat3;
    mat3.print();
    */
    return 0;
}