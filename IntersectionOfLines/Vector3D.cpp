#include "Vector3D.h"

Vector3D::Vector3D() {
    this->X = 0;
    this->Y = 0;
    this->Z = 0;
}

Vector3D::Vector3D(double X, double Y, double Z) {
    this->X = X;
    this->Y = Y;
    this->Z = Z;
}

Vector3D::Vector3D(const Vector3D& object) {
    this->X = object.X;
    this->Y = object.Y;
    this->Z = object.Z;
}

Vector3D& Vector3D::operator=(const Vector3D& object) {
    if (this == &object) {
        return *this;
    }
    this->X = object.X;
    this->Y = object.Y;
    this->Z = object.Z;
    return *this;
}

const Vector3D Vector3D::operator-(const Vector3D& object) const {
    return Vector3D(X - object.X, Y - object.Y, Z - object.Z);
}

const Vector3D Vector3D::operator/(const Vector3D& object) const {
    return Vector3D(X / object.X, Y / object.Y, Z / object.Z);
}

const Vector3D Vector3D::operator+(const Vector3D& object) const {
    return Vector3D(X + object.X, Y + object.Y, Z + object.Z);
}

const bool Vector3D::operator<=(const Vector3D& object) const {
    bool conclusion;
    if (X <= object.X && Y <= object.Y && Z <= object.Z) {
        conclusion = true;
    }
    else {
        conclusion = false;
    }
    return conclusion;
}

const bool Vector3D::operator>=(const Vector3D& object) const {
    bool conclusion;
    if (X >= object.X && Y >= object.Y && Z >= object.Z) {
        conclusion = true;
    }
    else {
        conclusion = false;
    }
    return conclusion;
}

Vector3D::~Vector3D() {}
