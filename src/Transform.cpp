#include <Transform.h>

Matrix Transform::Translate(const Matrix & vec)
{
	int len = vec.rows;
	Matrix res = (len==3) ? Mat::Mat4() : Mat::Mat3();
	for(int i=0; i<len; i++)
	{
		res[i][len] = vec[i][0];
	}
	return res;
}

Matrix Transform::RotateX(double angle)
{
	//angle = M_PI * angle / 180;
	Matrix res = Mat::Mat4();
	double a = cos(angle);
	double b = sin(angle);
	res[1][1] = a;
	res[1][2] = -b;
	res[2][1] = b;
	res[2][2] = a;

	return res;
}

Matrix Transform::RotateY(double angle)
{
	//angle = M_PI * angle / 180;
	Matrix res = Mat::Mat4();
	double a = cos(angle);
	double b = sin(angle);
	res[0][0] = a;
	res[0][2] = b;
	res[2][1] = -b;
	res[2][2] = a;

	return res;
}

Matrix Transform::RotateZ(double angle)
{
	//angle = M_PI * angle / 180;
	Matrix res = Mat::Mat4();
	double a = cos(angle);
	double b = sin(angle);
	res[0][0] = a;
	res[0][1] = -b;
	res[1][0] = b;
	res[1][1] = a;

	return res;
}


Matrix Transform::Scale(const Matrix & sc, const Matrix & vec)
{
	int len = vec.rows;
	Matrix res = (len==3) ? Mat::Mat4() : Mat::Mat3();
	for(int i=0; i<len; i++)
	{
		res[i][i] = sc[i][0];
		res[i][len] = (1-sc[i][0])*vec[i][0];
	}
	return res;
}

Matrix Transform::Scale(double sx, double sy, double sz, const Matrix & vec)
{
	return Scale(Mat::Vec3(sx,sy,sz), vec);
}
