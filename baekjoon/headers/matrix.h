#pragma once


template <typename T>
class Matrix {
private:
    int m, n;
public:
    T** a;
    
    Matrix(int m, int n) {
        assert(m >0 && n>0);
        this->m = m;
        this->n = n;
        
        int i;
        newDoublePointer(this->a);
    }
    Matrix(int m, int n, T** a) {
        assert(m >0 && n>0);
        this->m = m;
        this->n = n;
        this->a = a;
    }
    
    //Identity Matrix
    Matrix(int n) {
        
        assert( n >0);
        this->m = m;
        this->n = n;
        
        int i,j;
        this->a = new T*[n];
        for (i=0; i<m; i++) {
            T[i] = new T[n];
            for (j=0; j<n; j++) T[i][j] = 0;
            T[i][i] = 1;
        }
    }
    ~Matrix() {
        deleteDoublePointer(this->a);
    }
    void newDoublePointer(int m, int n, T **p) {
        int i;
        p = new T*[m];
        for (i=0; i<m; i++) {
            p[i] = new T[n];
        }
    }
    void deleteDoublePointer(int m, int n, T **p) {
        int i;
        for (i=0; i<m; i++) {
            delete p[i];
        }
        delete p;
    }
    
    Matrix operator+ (const Matrix other) const {
        assert(this->m == other.m && this->n == other.n);
        Matrix ret = new Matrix(this->m, this->n);
        
        int i,j;
        for (i=0; i<m; i++) {
            for (j=0; j<n; j++) {
                ret->a[i][j] = this->a[i][j] + other.a[i][j];
            }
        }
        return ret;
    }
    Matrix operator- (const Matrix other) const {
        assert(this->m == other.m && this->n == other.n);
        Matrix ret = new Matrix(this->m, this->n);
        
        int i,j;
        for (i=0; i<m; i++) {
            for (j=0; j<n; j++) {
                ret->a[i][j] = this->a[i][j] - other.a[i][j];
            }
        }
        return ret;
    }
    Matrix operator* (const Matrix other) const {
        assert(this->n == other.m);
        Matrix ret = new Matrix(this->m, other.n);
        
        int i, j, k;
        for (i=0; i<this->m; i++) {
            for (j=0; j<other.n; j++) {
                ret->a[i][j] = 0;
                for (k=0; k<this->n; k++) {
                    a[i][j] += this->a[i][k] * other.a[k][j];
                }
            }
        }
        return ret;
    }
    Matrix Inverse() {
        
    }
    T det() {
        
    }
};