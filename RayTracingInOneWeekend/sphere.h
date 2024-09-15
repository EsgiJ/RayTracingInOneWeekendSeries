#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "rtweekend.h"

class sphere : public hittable
{
public:
	sphere(const point3& center, double radius, shared_ptr<material> mat)
		: center(center), radius(std::max(0.0,radius)), mat(mat) {}

	bool hit(const ray& r, interval ray_t, hit_record& rec) const override
	{
		vec3 oc = r.origin() - center;
		double a = dot(r.direction(), r.direction());
		double b = 2.0 * dot(r.direction(), oc);
		double c = dot(oc, oc) - radius * radius;
		double discriminant = b * b - 4 * a * c;

		if (discriminant < 0)
		{
			return false;
		}

		double sqrtd = std::sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range.
		double root = (-b - sqrtd) / (2 * a);
		if (!ray_t.surrounds(root))
		{
			root = (-b + sqrtd) / (2 * a);
			if (!ray_t.surrounds(root))
			{
				return false;
			}
		}
		rec.t = root;
		rec.p = r.at(rec.t);
		vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);
		rec.mat = mat;

		return true;
	}
private:
	point3 center;
	double radius;
	shared_ptr<material> mat;
};
#endif
