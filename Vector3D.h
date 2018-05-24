#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Matrix3D;

template <class T>
class Vector3D
{
    T x = 0;
    T y = 0;
    T z = 0;
public:
    Vector3D() = default;
    Vector3D(T x, T y, T z);

    T getX() const { return this->x; }
    T getY() const { return this->y; }
    T getZ() const { return this->z; }

    void setX(T x){
        this->x = x;
        return;
    }
    void setY(T y){
        this->y = y;
        return;
    }
    void setZ(T z){
        this->z = z;
        return;
    }

    friend ostream& operator<<(ostream& os, const Vector3D<T>& v) {
        os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
        return  os;
    }

    friend istream& operator>>(istream& is, Vector3D<T>& v){
        T x, y, z;
        is >> x >> y >> z;
        v.setX(x);
        v.setY(y);
        v.setZ(z);
        return is;
    }

    bool operator== (const Vector3D<T>& v2);

    bool operator!= (const Vector3D<T>& v2);

    Vector3D<T> operator+ (const Vector3D<T>& v2);

    Vector3D<T> operator- (const Vector3D<T>& v2);

    T operator* (const Vector3D<T>& v1);

    Vector3D<T> vect_mult (Vector3D<T>& v1, Vector3D<T>& v2);

    Vector3D<T> operator* (T a);

    Vector3D<T> operator* (Matrix3D<T>& m);

    friend Vector3D<T> operator* (T a, const Vector3D<T>& v){
        Vector3D<T> res;
        res.setX(v.getX() * a);
        res.setY(v.getY() * a);
        res.setZ(v.getZ() * a);
        return res;
    }
};

template <class T>
class Matrix3D{
public:
    vector< vector<T> > elem;
    Matrix3D() {
        elem.resize(3);
        for (int i = 0; i < 3; i++){
            elem[i].resize(3);
        }
    }

    Matrix3D(vector< vector<T> > args){
        elem.resize(3);
        for (int i = 0; i < 3; i++){
            elem[i].resize(3);
        }
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                elem[i][j] = args[i][j];
            }
        }
    }

    Matrix3D<T> operator* (T a);

    Vector3D<T> operator* (Vector3D<T>& v);

    Matrix3D<T> operator* (Matrix3D<T>& m);

    Matrix3D<T> operator+ (Matrix3D<T>& m);

    Matrix3D<T> operator- (Matrix3D<T>& m);

    friend Matrix3D<T> operator*(T arg, Matrix3D<T>& m){
        return m * arg;
    }

    bool operator== (Matrix3D<T>& m);
    bool operator!= (Matrix3D<T>& m);

    T determinant();

    friend ostream& operator<<(ostream& os, const Matrix3D<T>& m){
        os << m.elem[0][0] << ' ' << m.elem[0][1] << ' ' << m.elem[0][2] << '\n' << m.elem[1][0] << ' ' << m.elem[1][1] << ' ' << m.elem[1][2] << '\n' << m.elem[2][0] << ' ' << m.elem[2][1] << ' ' << m.elem[2][2] << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Matrix3D<T>& m){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                is >> m.elem[i][j];
            }
        }
        return is;
    }
};

template <class T>
Matrix3D<T> Matrix3D<T>::operator* (T arg) {
    Matrix3D<T>* matrix3D = new Matrix3D<T>();
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            matrix3D->elem[i][j] = this->elem[i][j] * arg;
        }
    }
    return *matrix3D;
}

template <class T>
Vector3D<T> Matrix3D<T>::operator*(Vector3D<T> &v) {
    return Vector3D(elem[0][0] * v.getX() + elem[0][1] * v.getY() + elem[0][2] * v.getZ(), elem[1][0] * v.getX() + elem[1][1] * v.getY() + elem[1][2] * v.getZ(), elem[2][0] * v.getX() + elem[2][1] * v.getY() + elem[2][2] * v.getZ());
}

template <class T>
T Matrix3D<T>::determinant() {
    return elem[0][0] * (elem[1][1] * elem[2][2] - elem[1][2] * elem[2][1]) -
            elem[0][1] * (elem[1][0] * elem[2][2] - elem[1][2] * elem[2][0]) +
            elem[0][2] * (elem[1][0] * elem[2][1] - elem[1][1] * elem[2][0]);
}

template <class T>
Matrix3D<T> Matrix3D<T>::operator*(Matrix3D<T>& m) {
    Matrix3D<T> ans;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            ans.elem[i][j] = elem[i][0] * m.elem[0][j] + elem[i][1] * m.elem[1][j] + elem[i][2] * m.elem[2][j];
        }
    }
    return ans;
}

template <class T>
Matrix3D<T> Matrix3D<T>::operator+(Matrix3D<T> &m) {
    Matrix3D<T> ans;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            ans.elem[i][j] = elem[i][j] + m.elem[i][j];
        }
    }
    return ans;
}

template <class T>
Matrix3D<T> Matrix3D<T>::operator-(Matrix3D<T> &m) {
    Matrix3D<T> ans;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            ans.elem[i][j] = elem[i][j] - m.elem[i][j];
        }
    }
    return ans;
}

template<class T>
bool Matrix3D<T>::operator==(Matrix3D<T> &m) {
    return this->elem == m.elem;
}

template<class T>
bool Matrix3D<T>::operator!=(Matrix3D<T> &m) {
    return !(this->elem == m.elem);
}


//------------------------------------------

template <class T>
Vector3D<T> Vector3D<T>::operator*(Matrix3D<T>& m) {
    Vector3D* vector3D = new Vector3D<T>(m.elem[0][0] * x + m.elem[1][0] * y + m.elem[2][0] * z, m.elem[0][1] * x + m.elem[1][1] * y + m.elem[2][1] * z, m.elem[0][2] * x + m.elem[1][2] * y + m.elem[2][2] * z);
    return *vector3D;
}

template<class T>
Vector3D<T>::Vector3D(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class T>
bool Vector3D<T>::operator==(const Vector3D<T> &v2) {
    return this->getX() == v2.getX() && this->getY() == v2.getY() && this->getZ() == v2.getZ();
}

template <class T>
bool Vector3D<T>::operator!=(const Vector3D<T> &v2) {
    return !(*this == v2);
}

template <class T>
Vector3D<T> Vector3D<T>::operator+(const Vector3D<T> &v2) {
    Vector3D<T> res;
    res.setX(this->getX() + v2.getX());
    res.setY(this->getY() + v2.getY());
    res.setZ(this->getZ() + v2.getZ());
    return res;
}

template <class T>
Vector3D<T> Vector3D<T>::operator*(const T a) {
    Vector3D<T> res;
    res.setX(x * a);
    res.setY(y * a);
    res.setZ(z * a);
    return  res;
}

template <class T>
Vector3D<T> Vector3D<T>::operator-(const Vector3D<T> &v2) {
    Vector3D<T> res;
    res.setX(this->getX() - v2.getX());
    res.setY(this->getY() - v2.getY());
    res.setZ(this->getZ() - v2.getZ());
    return res;
}

template<class T>
T Vector3D<T>::operator*(const Vector3D<T> &v1) {
    return v1.getX() * this->x + v1.getY() * this->y + v1.getZ() * this->z;
}

template <class T>
Vector3D<T> Vector3D<T>::vect_mult(Vector3D<T> &a, Vector3D<T> &b) {
    return Vector3D(a.getY() * b.getZ() - a.getZ() * b.getY(), a.getZ() * b.getX() - a.getX() * b.getZ(), a.getX() * b.getY() - a.getY() * b.getX());
}
