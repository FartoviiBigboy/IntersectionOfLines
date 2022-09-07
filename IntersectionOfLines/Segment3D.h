#pragma once
#include "Vector3D.h"

class Segment3D {
public:
    Vector3D start;
    Vector3D end;

    Segment3D(Vector3D start, Vector3D end);
    Segment3D(const Segment3D& object);
    Segment3D& operator=(const Segment3D& object);
    const bool operator==(const Vector3D& object) const;
    ~Segment3D();
};
