#pragma once
#include <math.h>

class vec2
{
public:
	float x = 0;
	float y = 0;

	vec2() {};
	vec2(unsigned int xIn, unsigned int yIn) : x(float(xIn)), y(float(yIn)) {}
	vec2(int xIn, int yIn) : x(xIn), y(yIn) {}
	vec2(float xIn, float yIn) : x(xIn), y(yIn) {}

	inline vec2 operator + (const vec2& vec) const
	{
		return vec2(x + vec.x, y + vec.y);
	}

	inline vec2 operator - (const vec2& vec) const
	{
		return vec2(x - vec.x, y - vec.y);
	}

	inline vec2 operator / (float val) const
	{
		return vec2(x / val, y / val);
	}

	inline vec2 operator * (float val) const
	{
		return vec2(x * val, y * val);
	}

	inline vec2 operator * (const vec2& vec) const
	{
		return vec2(x * vec.x, y * vec.y);
	}

	inline bool operator == (const vec2& vec) const
	{
		return bool(x == vec.x && y == vec.y);
	}

	inline bool operator != (const vec2& vec) const
	{
		/*return bool(x != vec.x && y != vec.y);*/
		return (*this == vec);
	}

	inline void operator += (const vec2& vec)
	{
		x += vec.x;
		y += vec.y;
	}

	inline void operator -= (const vec2& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}

	inline void operator *= (float val)
	{
		x *= val;
		y *= val;
	}

	inline void operator /= (float val)
	{
		x /= val;
		y /= val;
	}

	inline float distSq(const vec2& vec) const
	{
		return (x - vec.x) * (x - vec.x) + (y - vec.y) * (y - vec.y);
	}

	inline float dist(const vec2& vec) const
	{
		return sqrt(distSq(vec));
	}

	inline float length() const
	{
		return sqrt(x * x + y * y);
	}

	inline vec2 normalize() const
	{
		float l = length();
		return vec2(x / l, y / l);
	}

	inline vec2 abs() const
	{
		return vec2(x < 0 ? -x : x, y < 0 ? -y : y);
	}
};

