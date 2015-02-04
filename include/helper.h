#pragma once

#include <algorithm>
#include <cctype>
#include <locale>

// it contains other helper functions like converting to degree, radian, sorting, etc

namespace Helper
{
	inline int ROUND(float x)
	{
		return x>0 ? int(x+0.5) : int(x-0.5);
	}
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
	inline float GetC(t& p1, t& p2, t& p3)
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
		return (a.x*b.y)-(b.x*a.y);;
	}

	inline float ToRadian(float degree)
	{
		return degree*3.1415/180.f;
	}

	//remove trailing  whitespaces
	inline std::string &RightTrim(std::string & str)
	{
		 str.erase(find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
		 return str;
	}

	//remove lieading whitespaces
	inline std::string &LeftTrim(std::string &str) 
	{
		 str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return str;
	}

	inline std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) 
	{
    	size_t start_pos = 0;
    	while((start_pos = str.find(from, start_pos)) != std::string::npos) 
    	{
        	str.replace(start_pos, from.length(), to);
        	start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    	}
    	return str;
	}

}
