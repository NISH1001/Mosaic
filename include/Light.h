#pragma once

#include <Vector.h>

/*
	A directed light source
*/

struct DirectedLight
{
	//light direction given  in world space usually
	Vec3 direction;

	//light intensity -> r, g, b -> 0 to 1 range
	Vec3 intensity;

	DirectedLight(const Vec3 & dir, const Vec3 & intense) : direction(dir), intensity(intense)
	{
		direction.NormalizeToUnit();
	}

	DirectedLight() : direction(Vec3(-1,-1,-1)), intensity(Vec3(1,1,1))
	{
		direction.NormalizeToUnit();
	}
};

/*
	Ambient light it is 
	has only color intensity
*/
struct AmbientLight
{
	Vec3 intensity;
};