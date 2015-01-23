#pragma once

#define ROUND(x) x>0 ? int(x+0.5) : int(x-0.5)
// it contains other helper functions like converting to degree, radian, sorting, etc

namespace Helper
{
	template <class t>
	inline t Max(t a, t b)
	{
		if (a>b) return a;
		else return b;
	}

	template <class t>
	inline t Min(t a, t b)
	{
		if (a<b) return a;
		else return b;
	}

	template <class t>
	inline void Swap(t&a, t&b)
	{
		t temp = a;
		a = b;
		b = temp;
	}
	
	template <class t> // t is point like thing having y as a member
	inline void SortY(t& m_p1, t& m_p2, t& m_p3)
	{
		if (m_p1.y < m_p2.y) Swap(m_p1, m_p2);

		if (m_p2.y < m_p3.y) Swap(m_p2, m_p3);

		 ///largest yvalue coord is at 1
		if (m_p1.y < m_p2.y) Swap(m_p1, m_p2);
	}

	// function to find C of a plane, input must be something having x, y, z attributes
	// and input must be in anticlockwise order
	template <class t>
	float GetC(t& p1, t& p2, t& p3)
	{
		// here we have 3 points in some order
		// to find the C component of normal, we need to do
		// (p3-p2)X(p1-p2) and find its z component
		t a = p3-p2;
		t b = p1-p2;
		/*float C = p1.x * (p2.y - p3.y) +
			  p2.x * (p3.y - p1.y) +
			  p3.x * (p1.y - p2.y);
		*/
		float C = (a.x*b.y)-(b.x*a.y);
		return C;
	}

	inline float ToRadian(float degree)
	{
		return degree*3.141592/180.f;
	}

}
