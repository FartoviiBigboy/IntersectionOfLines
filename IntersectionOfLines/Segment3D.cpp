#include "Segment3D.h"

Segment3D::Segment3D(Vector3D start, Vector3D end) {
    this->start = start;
    this->end = end;
}

Segment3D::Segment3D(const Segment3D& object) {
    this->start = object.start;
    this->end = object.end;
}

Segment3D& Segment3D::operator=(const Segment3D& object) {
    if (this == &object) {
        return *this;
    }
    this->start = object.start;
    this->end = object.end;
    return *this;
}

const bool Segment3D::operator==(const Vector3D& object) const {
    bool conclusion = true;
    conclusion = conclusion && ((object.X >= start.X && object.X <= end.X) || (object.X >= end.X && object.X <= start.X));
    conclusion = conclusion && ((object.Y >= start.Y && object.Y <= end.Y) || (object.Y >= end.Y && object.Y <= start.Y));
    conclusion = conclusion && ((object.Z >= start.Z && object.Z <= end.Z) || (object.Z >= end.Z && object.Z <= start.Z));
    return conclusion;
}

Segment3D::~Segment3D() {}
