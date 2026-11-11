#ifndef OBJECTS

#include <cmath>
#include <random>

class Vec2 {
public:
	double x, y;

	Vec2() : x(0), y(0) {}

	Vec2(double x1, double y1) : x(x1), y(y1) {}

	Vec2(const Vec2& v) : x(v.x), y(v.y) {}

	Vec2 operator * (double n) { return Vec2(x * n, y * n); }
	void operator *= (double n) { (*this) = (*this) * n; }

	Vec2 operator / (double n) { return Vec2(x / n, y / n); }
	void operator /= (double n) { (*this) = (*this) / n; }

	Vec2 operator + (const Vec2& v) { return Vec2(x + v.x, y + v.y); }
	void operator += (const Vec2& v) { (*this) = (*this) + v; }

	Vec2 operator - (const Vec2& v) { return Vec2(x - v.x, y - v.y); }
	void operator -= (const Vec2& v) { (*this) = (*this) - v; }


	double len() { return std::sqrt(x * x + y * y); }

	double static dot (Vec2 v1, Vec2 v2) {return v1.x * v2.x + v1.y * v2.y;}
	
	Vec2 static Adamar(Vec2 v1, Vec2 v2) { return Vec2(v1.x * v2.x, v1.y * v2.y); }

	double static dist(Vec2 v1, Vec2 v2) { return std::sqrt((v2.x-v1.x)*(v2.x - v1.x) + (v2.y - v1.y)*(v2.y - v1.y)); }

	void rand_vec(int low, int up, int* seed = nullptr) { if(seed) std::srand(*seed);x = rand() % (up-low + 1); y = rand() % (up-low + 1); }
};


class Particle {
public:
	Vec2 pos, speed, best;


	Particle() : pos(Vec2()), speed(Vec2()), best(Vec2()) {}

	Particle(Vec2 pos1, Vec2 speed1, Vec2 best1) : pos(pos1), speed(speed1), best(best1) {}

	

};



#endif