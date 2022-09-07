#pragma once

class Vector3D {
public:
    double X;
    double Y;
    double Z;
    Vector3D();
    Vector3D(double X, double Y, double Z);
    Vector3D(const Vector3D& object);
    Vector3D& operator=(const Vector3D& object);
    const Vector3D operator-(const Vector3D& object) const;
    const Vector3D operator/(const Vector3D& object) const;
    const Vector3D operator+(const Vector3D& object) const;
    const bool operator<=(const Vector3D& object) const;
    const bool operator>=(const Vector3D& object) const;
    ~Vector3D();
};
