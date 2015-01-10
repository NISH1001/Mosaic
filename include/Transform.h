#pragma once

#include <Matrix.h>
#include <Mat.h>
#include <Point2D.h>
#include <cmath>
#include <iostream>

class Transform
{
public:
	static Matrix Translate(const Matrix & vec);
	static Matrix RotateX(double angle);
	static Matrix RotateY(double angle );
	static Matrix RotateZ(double angle );
	static Matrix Scale(const Matrix & sc, const Matrix & vec);
	static Matrix Scale(double sx, double sy, double sz, const Matrix & vec);
};