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
		m_pos = pos;
		m_target = target;

		Vec3 up(0,1,0);
		Vec3 n = pos-target;
		Vec3 u = Vec3::Cross(up,n);
		n.NormalizeToUnit();
		u.NormalizeToUnit();
		Vec3 v = Vec3::Cross(n,u);
		v.NormalizeToUnit();

		m_n = n;
		m_up = v;

		m_view =  Mat4(
					Vec4(u, Vec3::Dot(pos * (-1),u)),
					Vec4(v, Vec3::Dot(pos * (-1),v)),
					Vec4(n, Vec3::Dot(pos * (-1),n)),
					Vec4(0,0,0,1)
				);
	}

	void SetView(Mat4 view)
	{
		m_view = view;
	}

	void MoveForward(float deltastep)	
	{
		m_pos -= m_n * deltastep;
        m_target -= m_n * deltastep;
		SetView(m_pos, m_target);
	}

	void MoveSideway(float deltastep)
	{
		
		Vec3 side = Vec3::Cross(m_n, m_up);
		side.NormalizeToUnit();
		side = side * deltastep;
		m_pos += side;
		m_target += side;
		SetView(m_pos, m_target);
		
	}

	void MoveVertically(float deltastep)
	{
		m_pos += m_up * deltastep;
		m_target += m_up * deltastep;
		SetView(m_pos, m_target);
	}

	void RotateView(float deltastep)
	{
		Vec4 vec = Transform::Rotate(deltastep, m_up, m_pos) * Vec4(m_target,1);
		Vec3 target = vec.ToVec3();
		SetView(m_pos, target);
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
