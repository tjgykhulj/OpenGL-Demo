#include "TVector.h"

TVector::TVector() { x = y = z = 0; }
TVector::TVector(GLfloat X, GLfloat Y, GLfloat Z)
	: x(X), y(Y), z(Z) {
}
TVector::TVector(TVector &v1, TVector &v2)
	: x(v2.x - v1.x), y(v2.y - v1.y), z(v2.z - v1.z) {
}
void TVector::set(GLfloat X, GLfloat Y, GLfloat Z) { x = X, y = Y, z = Z; }

GLfloat TVector::length() { return sqrt(x*x + y*y + z*z); }

GLfloat TVector::operator *(TVector &sth){ return x*sth.x + y*sth.y + z*sth.z; }
TVector TVector::operator +(TVector &sth){ return TVector(x + sth.x, y + sth.y, z + sth.z); }
TVector TVector::operator -(TVector &sth){ return TVector(x - sth.x, y - sth.y, z - sth.z); }
TVector TVector::operator *(GLfloat k)	{ return TVector(x*k, y*k, z*k); }
TVector TVector::operator /(GLfloat k)	{ return TVector(x / k, y / k, z / k); }

GLfloat & TVector::operator [](GLint k) {
	switch (k) {
	case 0: return x;
	case 1: return y;
	default: return z;
	}
}