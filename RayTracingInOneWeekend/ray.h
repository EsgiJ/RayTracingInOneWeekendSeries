#ifndef RAY_H
#define RAY_H

#include "vec3.h"
class ray
{
public:
	ray() {};

	ray(const point3& origin, const vec3& direction)
		: m_Origin(origin), m_Direction(direction) {}

	const point3& origin() const { return m_Origin; }
	const point3& direction() const { return m_Direction; }

	point3 at(double t) const
	{
		return origin + t * m_Direction;
	}

private:
	point3 m_Origin;
	point3 m_Direction;
};

#endif
