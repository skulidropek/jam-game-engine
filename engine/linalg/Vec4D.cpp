//
// Created by Иван Ильин on 12.01.2021.
//

#include <cmath>
#include <stdexcept>
#include <cassert>

#include <linalg/Vec4D.h>
#include <Consts.h>

Vec4D::Vec4D(double x, double y, double z, double w) {
    _arr_point[0] = x;
    _arr_point[1] = y;
    _arr_point[2] = z;
    _arr_point[3] = w;
}

Vec4D::Vec4D(const Vec4D &point4D) {
    _arr_point[0] = point4D.x();
    _arr_point[1] = point4D.y();
    _arr_point[2] = point4D.z();
    _arr_point[3] = point4D.w();
}

[[nodiscard]] Vec4D Vec4D::operator-() const {
    return Vec4D(-x(), -y(), -z(), -w());
}

bool Vec4D::operator==(const Vec4D &point4D) const {
    const Vec4D diff = *this - point4D;
    return diff.sqrAbs() < Consts::EPS;
}

bool Vec4D::operator!=(const Vec4D &point4D) const {
    return !(*this == point4D);
}

// Operations with Vec4D
Vec4D Vec4D::operator+(const Vec4D &point4D) const {
    return Vec4D(x() + point4D.x(), y() + point4D.y(), z() + point4D.z(), w() + point4D.w());
}

Vec4D Vec4D::operator-(const Vec4D &point4D) const {
    return Vec4D(x() - point4D.x(), y() - point4D.y(), z() - point4D.z(), w() - point4D.z());
}

Vec4D Vec4D::operator*(double number) const {
    return Vec4D(x() * number, y() * number, z() * number, w() * number);
}

Vec4D Vec4D::operator/(double number) const {
    if (std::abs(number) > Consts::EPS) {
        return Vec4D(x() / number, y() / number, z() / number, w() / number);
    }
    throw std::domain_error("Vec4D::operator/(double number): division by zero");
}

// Other useful methods
double Vec4D::sqrAbs() const {
    return x() * x() + y() * y() + z() * z() + w() * w(); // TODO dot(*this);
}

double Vec4D::abs() const {
    return std::sqrt(sqrAbs());
}

Vec4D Vec4D::normalized() const {
    if (const double vec = abs(); vec > Consts::EPS) {
        return Vec4D(*this) / vec;
    }
    return Vec4D(0);
}

bool Vec4D::isNear(double a, double b) {
    return std::abs(a - b) < Consts::EPS;
}

void Vec4D::test() {
    Vec4D a(1, 2, 3, 4);
    Vec4D b(3, 4, 5, 6);

    // testing copy constructor:
    Vec4D c(a);
    assert(isNear(c.x(), 1) && isNear(c.y(), 2) && isNear(c.z(), 3) && isNear(c.w(), 4));

    // testing assigment operator (=):
    c = b;
    assert(isNear(c.x(), 3) && isNear(c.y(), 4) && isNear(c.z(), 5)  && isNear(c.w(), 6));

    // testing .x() & .y() & .z() & .w() methods:
    assert(isNear(a.x(), 1) && isNear(a.y(), 2) && isNear(a.z(), 3) && isNear(a.w(), 4));
    assert(isNear(b.x(), 3) && isNear(b.y(), 4) && isNear(b.z(), 5) && isNear(b.w(), 6));

    // testing operator -Vec:
    Vec4D neg = -a;
    assert(isNear(neg.x(), -a.x()) && isNear(neg.y(), -a.y()) && isNear(neg.z(), -a.z()) && isNear(neg.w(), -a.w()));

    // testing == & != operators:
    assert(c != a && c == b);

    // testing operators +, -:
    Vec4D summ = a + b;
    assert(isNear(summ.x(), 4) && isNear(summ.y(), 6) && isNear(summ.z(), 8) && isNear(summ.w(), 10));
    Vec4D diff = a - b;
    assert(isNear(diff.x(), -2) && isNear(diff.y(), -2)  && isNear(diff.z(), -2) && isNear(diff.w(), -2));

    // testing scaling operators:
    Vec4D scale1 = a * 2;
    assert(isNear(scale1.x(), 2) && isNear(scale1.y(), 4) && isNear(scale1.z(), 6) && isNear(scale1.w(), 8));
    Vec4D scale2 = a / 2;
    assert(isNear(scale2.x(), 0.5) && isNear(scale2.y(), 1) && isNear(scale2.z(), 1.5) && isNear(scale2.w(), 2));

    // testing .abs() & .normalized() methods:
    assert(isNear(b.abs(), std::sqrt(86)));
    assert(isNear(b.normalized().abs(), 1));
}

