#include <Vector.h>
#include <Matrix.h>
#include <Transform.h>

class Camera
{
public:

	Camera(){}

	Camera(Vec3 pos, Vec3 target)
	{
		SetView(pos, target);
	}

	void SetView(Vec3 pos, Vec3 target)
	{
		//pos.x = target.x;
		m_pos = pos;
		m_target = target;

		Mat4 translate = Transform::Translate(m_pos * (-1));

		Vec3 v(0,1,0); 
		Vec3 n = m_pos - m_target;
		n.NormalizeToUnit();
		m_n = n;

		Vec3 u = Vec3::Cross(v,n);
		u.NormalizeToUnit();
		
		v = Vec3::Cross(n,u);
		v.NormalizeToUnit();
		m_up = v;

		Mat4 rotate = Mat4(Vec4(u,0), Vec4(v,0), Vec4(n,0), Vec4(0,0,0,1));

		m_view = rotate * translate;
	}

	void SetView(Mat4 view)
	{
		m_view = view;
	}

	void MoveForward(float deltastep)	
	{
		//Vec3 n = m_target- m_pos;
		m_pos -= m_n * deltastep;
		SetView(m_pos, m_target);
	}

	void MoveSideway(float deltastep)
	{
		/*
		Vec3 side = Vec3::Cross(m_n, m_up);
		side.NormalizeToUnit();
		side = side * deltastep;
		m_pos += side;
		m_target.x = m_pos.x;
		std::cout << m_pos << ", " << m_target << std::endl;
		SetView(m_pos, m_target);
		*/
	}

	void RotateView(float deltastep)
	{
		/*
		Vec4 vec = Transform::Rotate(deltastep, m_up, m_pos) * Vec4(m_target,1);
		Vec3 target = vec.ToVec3();
		m_pos.x = target.x;
		std::cout << m_pos << ", " << m_target << std::endl;
		SetView(m_pos, target);
		*/
	}

	inline Mat4 GetView(void) const { return m_view; }

	inline Vec3 GetPos(void) const { return m_pos; }

	inline Vec3 GetTarget(void) const { return m_target; }

private:
	Vec3 m_pos;
	Vec3 m_target;

	Vec3 m_up;
	Vec3 m_n;

	Mat4 m_view;
};