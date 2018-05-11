#include <iostream>
#include <vector>

using namespace std;

class Matrix3D;

template <class T>
class Vector3D
{
    T x;
    T y;
    T z;
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

    friend ostream& operator<<(ostream& os, Vector3D& v);

    friend istream& operator>>(istream& is, Vector3D& v);

    bool operator== (const Vector3D& v2);

    bool operator!= (const Vector3D& v2);

    Vector3D operator+ (const Vector3D& v2);

    Vector3D operator- (const Vector3D& v2);

    friend T scal_mult (Vector3D& v1, Vector3D& v2);

    friend Vector3D vect_mult (Vector3D& v1, Vector3D& v2);

    Vector3D operator* (const int a);

    Vector3D operator* (Matrix3D& m);
};

template <class T>
class Matrix3D{
public:
    vector< vector < T > > elem;
    Matrix3D() {
        elem.resize(3);
        for (int i = 0; i < 3; i++){
            elem[i].resize(3);
        }
    }
    template <class T>
    Matrix3D(vector< vector<T> > args){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                elem[i][j] = args[i][j];
            }
        }
    }

    Matrix3D operator* (T a);
    Vector3D operator* (Vector3D& v);
    Matrix3D operator* (Matrix3D& m);
    Matrix3D operator+ (Matrix3D& m);
    Matrix3D operator- (Matrix3D& m);
    bool operator== (Matrix3D& m);
    bool operator!= (Matrix3D& m);
    T determinant();

    friend ostream& operator<<(ostream& os, Matrix3D& m);
    friend istream& operator>>(istream& is, Matrix3D& m);
};

template <class T>
Matrix3D Matrix3D::operator* (T arg) {
    Matrix3D* matrix3D = new Matrix3D();
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            matrix3D->elem[i][j] = matrix3D->elem[i][j] * arg;
        }
    }
    return *matrix3D;
}

Vector3D Matrix3D::operator*(Vector3D &v) {
    return Vector3D(elem[0][0] * v.getX() + elem[0][1] * v.getY() + elem[0][2] * v.getZ(), elem[1][0] * v.getX() + elem[1][1] * v.getY() + elem[1][2] * v.getZ(), elem[2][0] * v.getX() + elem[2][1] * v.getY() + elem[2][2] * v.getZ(),);
}

template <class T>
T Matrix3D::determinant() {
    return elem[0][0] * (elem[1][1] * elem[2][2] - elem[1][2] * elem[2][1]) - elem[0][1] * (elem[1][0] * elem[2][2] - elem[1][2] * elem[2][0]) + elem[0][2] * (elem[1][0] * elem[2][1] - elem[1][1] * elem[2][0]);
}

template <class T>
Matrix3D Matrix3D::operator*(Matrix3D& m) {
    Matrix3D ans;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            ans.elem[i][j] = elem[i][0] * m.elem[0][j] + elem[i][1] * m.elem[1][j] + elem[i][2] * m.elem[2][j];
        }
    }
    return ans;
}

Matrix3D Matrix3D::operator+(Matrix3D &m) {
    Matrix3D ans;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            ans.elem[i][j] = elem[i][j] + m.elem[i][j];
        }
    }
    return ans;
}

Matrix3D Matrix3D::operator-(Matrix3D &m) {
    Matrix3D ans;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            ans.elem[i][j] = elem[i][j] - m.elem[i][j];
        }
    }
    return ans;
}

ostream& operator<<(ostream& os, Matrix3D& m) {
    os << m.elem[0][0] << ' ' << m.elem[0][1] << m.elem[0][2] << '\n' << m.elem[1][0] << ' ' << m.elem[1][1] << ' ' << m.elem[1][2] << '\n' << m.elem[2][0] << ' ' << m.elem[2][1] << ' ' << m.elem[2][2] << endl;
    return os;
}

istream& operator>>(istream& is, Matrix3D& m){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            is >> m.elem[i][j];
        }
    }
    return is;
}

template<class T>
bool Matrix3D<T>::operator==(Matrix3D &m) {
    return this->elem == m.elem;
}

template<class T>
bool Matrix3D<T>::operator!=(Matrix3D &m) {
    return !(this->elem == m.elem);
}


//------------------------------------------

Vector3D Vector3D::operator*(Matrix3D& m) {
    Vector3D* vector3D = new Vector3D(m.elem[0][0] * x + m.elem[1][0] * y + m.elem[2][0] * z, m.elem[0][1] * x + m.elem[1][1] * y + m.elem[2][1] * z, m.elem[0][2] * x + m.elem[1][2] * y + m.elem[2][2] * z);
    return *vector3D;
}

template<class T>
Vector3D::Vector3D(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

ostream& operator<<(ostream &os, Vector3D &v) {
    os << '(' << v.getX() << ", " << v.getY() << ", " << v.getZ() << ')';
    return  os;
}

bool Vector3D::operator==(const Vector3D &v2) {
    return this->getX() == v2.getX() && this->getY() == v2.getY() && this->getZ() == v2.getZ();
}

bool Vector3D::operator!=(const Vector3D &v2) {
    return !(*this == v2);
}

Vector3D Vector3D::operator+(const Vector3D &v2) {
    Vector3D res;
    res.setX(this->getX() + v2.getX());
    res.setY(this->getY() + v2.getY());
    res.setY(this->getZ() + v2.getZ());
    return res;
}

Vector3D Vector3D::operator*(const int a) {
    Vector3D res;
    res.setX(x * a);
    res.setY(y * a);
    res.setY(z * a);
    return  res;
}

Vector3D operator* (int a, const Vector3D& v) {
    Vector3D res;
    res.setX(v.getX() * a);
    res.setY(v.getY() * a);
    res.setY(v.getZ() * a);
    return res;
}
template<class T>
istream& operator>>(std::istream &is, Vector3D &v) {
    T x, y, z;
    is >> x >> y >> z;
    v.setX(x);
    v.setY(y);
    v.setZ(z);
    return is;
}

Vector3D Vector3D::operator-(const Vector3D &v2) {
    Vector3D res;
    res.setX(this->getX() - v2.getX());
    res.setY(this->getY() - v2.getY());
    res.setY(this->getZ() - v2.getZ());
    return res;
}

template<class T>
T scal_mult(Vector3D &v1, Vector3D &v2) {
    return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
}

Vector3D vect_mult(Vector3D &a, Vector3D &b) {
    return Vector3D(a.getY() * b.getZ() - a.getZ() * b.getY(), a.getZ() * b.getX() - a.getX() * b.getZ(), a.getX() * b.getY() - a.getY() * b.getX());
}

