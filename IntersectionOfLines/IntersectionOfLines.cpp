#include <cmath>
#include <iostream>

#include "Segment3D.h"
#include "Vector3D.h"

using namespace std;

const double epsilon = 0.000001;

Vector3D* Intersect(Segment3D firstSegment, Segment3D secondSegment);

bool canLieInSamePlane(Segment3D firstSegment, Segment3D secondSegment);
bool isCollinear(Vector3D firstDirect, Vector3D secondDirect, double epsilon);
bool isCoplanar(Vector3D differenceVector, Vector3D firstDirect,
    Vector3D secondDirect, double epsilon);

void calculateLinearSystem(double** linearSystem, Segment3D firstSegment, Segment3D secondSegment);
void calculatePlaneEquation(double* PlaneEquation, Vector3D first,
    Vector3D second, Vector3D third);

Vector3D* CramersMethod(double** linearSystem);
double matrixDeterminant(double** linearSystem, int first, int second,
    int third);

bool isOnSegments(Segment3D firstSegment, Segment3D secondSegment, Vector3D pointToCheck);




int main() {
    //Segment3D firstSegment(Vector3D(3, -3, 2), Vector3D(2, -2, 4));
    //Segment3D secondSegment(Vector3D(-1, 4, -26), Vector3D(2, 0, -20));
    //Segment3D firstSegment(Vector3D(4, 4, 4), Vector3D(-2, -2, -2));
    //Segment3D secondSegment(Vector3D(6, 7, -1), Vector3D(-2, -3, 5));
    Segment3D firstSegment(Vector3D(-2, -2, -2), Vector3D(2, 2, 2));
    Segment3D secondSegment(Vector3D(6, 7, -1), Vector3D(2, 2, 2));
    Vector3D* result = Intersect(firstSegment, secondSegment);

    if (result) {
        cout << "intersection in point: ";
        cout << result->X << " " << result->Y << " " << result->Z << endl;
        delete result;
    }
    else {
        cout << "no intersections!" << endl;
    }

}

Vector3D* Intersect(Segment3D firstSegment, Segment3D secondSegment) {
    Vector3D* result = NULL;
    if (canLieInSamePlane(firstSegment, secondSegment)) {
        double** linearSystem = new double* [3];
        for (int i = 0; i < 3; i++) {
            linearSystem[i] = new double[4];
        }

        calculateLinearSystem(linearSystem, firstSegment, secondSegment);
        result = CramersMethod(linearSystem);
        if (!isOnSegments(firstSegment, secondSegment, *result)) {
            delete result;
            result = NULL;
        }

        for (int i = 0; i < 3; i++) {
            delete[] linearSystem[i];
        }
        delete[] linearSystem;
    }
    return result;
}

bool canLieInSamePlane(Segment3D firstSegment, Segment3D secondSegment) {
    bool conclusion = false;
    Vector3D firstDirect = firstSegment.end - firstSegment.start;
    Vector3D secondDirect = secondSegment.end - secondSegment.start;
    if (!isCollinear(firstDirect, secondDirect, epsilon)) {
        if (isCoplanar(firstSegment.end - secondSegment.end, firstDirect, secondDirect, epsilon)) {
            conclusion = true;
        }
    }
    return conclusion;
}

bool isCollinear(Vector3D firstDirect, Vector3D secondDirect, double epsilon) {
    bool conclusion = false;

    double firstMinor = firstDirect.Y * secondDirect.Z -
        firstDirect.Z * secondDirect.Y;
    double secondMinor = firstDirect.X * secondDirect.Z -
        firstDirect.Z * secondDirect.X;
    double thirdMinor = firstDirect.X * secondDirect.Y -
        firstDirect.Y * secondDirect.X;

    if (fabs(firstMinor) < epsilon && fabs(secondMinor) < epsilon && fabs(thirdMinor) < epsilon) {
        conclusion = true;
    }

    return conclusion;
}

bool isCoplanar(Vector3D differenceVector, Vector3D firstDirect,
    Vector3D secondDirect, double epsilon) {
    bool conclusion = false;

    double firstMinor = firstDirect.Y * secondDirect.Z -
        firstDirect.Z * secondDirect.Y;
    double secondMinor = firstDirect.X * secondDirect.Z -
        firstDirect.Z * secondDirect.X;
    double thirdMinor = firstDirect.X * secondDirect.Y -
        firstDirect.Y * secondDirect.X;
    double calculationResult = differenceVector.X * firstMinor -
        differenceVector.Y * secondMinor +
        differenceVector.Z * thirdMinor;

    if (fabs(calculationResult) < epsilon) {
        conclusion = true;
    }

    return conclusion;
}

void calculateLinearSystem(double** linearSystem, Segment3D firstSegment, Segment3D secondSegment) {

    calculatePlaneEquation(linearSystem[0], firstSegment.end,
        firstSegment.end - firstSegment.start,
        secondSegment.end - secondSegment.start);

    Vector3D additionalPoint((firstSegment.end - secondSegment.end) /
        Vector3D(2, 2, 2) + Vector3D(linearSystem[0][0], linearSystem[0][1], linearSystem[0][2]));

    calculatePlaneEquation(linearSystem[1], additionalPoint,
        firstSegment.end - additionalPoint,
        firstSegment.start - additionalPoint);

    calculatePlaneEquation(linearSystem[2], additionalPoint,
        secondSegment.end - additionalPoint,
        secondSegment.start - additionalPoint);
}

void calculatePlaneEquation(double* PlaneEquation, Vector3D first,
    Vector3D second, Vector3D third) {
    double firstMinor = second.Y * third.Z - second.Z * third.Y;
    double secondMinor = second.X * third.Z - second.Z * third.X;
    double thirdMinor = second.X * third.Y - second.Y * third.X;

    PlaneEquation[0] = firstMinor;
    PlaneEquation[1] = -secondMinor;
    PlaneEquation[2] = thirdMinor;

    PlaneEquation[3] = first.X * firstMinor - first.Y * secondMinor + first.Z * thirdMinor;
}

Vector3D* CramersMethod(double** linearSystem) {
    double mainDeterminant = matrixDeterminant(linearSystem, 0, 1, 2);
    double X = matrixDeterminant(linearSystem, 3, 1, 2) / mainDeterminant;
    double Y = matrixDeterminant(linearSystem, 0, 3, 2) / mainDeterminant;
    double Z = matrixDeterminant(linearSystem, 0, 1, 3) / mainDeterminant;
    return new Vector3D(X, Y, Z);
}

double matrixDeterminant(double** linearSystem, int first, int second, int third) {
    double result = 0;

    double firstMinor = linearSystem[1][second] * linearSystem[2][third] -
        linearSystem[1][third] * linearSystem[2][second];
    double secondMinor = linearSystem[1][first] * linearSystem[2][third] -
        linearSystem[1][third] * linearSystem[2][first];
    double thirdMinor = linearSystem[1][first] * linearSystem[2][second] -
        linearSystem[1][second] * linearSystem[2][first];

    result = linearSystem[0][first] * firstMinor -
        linearSystem[0][second] * secondMinor +
        linearSystem[0][third] * thirdMinor;

    return result;
}

bool isOnSegments(Segment3D firstSegment, Segment3D secondSegment, Vector3D pointToCheck) {
    bool conclusion = true;
    conclusion = conclusion && (firstSegment == pointToCheck);
    conclusion = conclusion && (secondSegment == pointToCheck);
    return conclusion;
}

