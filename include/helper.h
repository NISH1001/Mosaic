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
}
