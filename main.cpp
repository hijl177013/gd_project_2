#include "objects.hpp"
#include <ctime>
#include <climits>
#include <cfloat>

int main() {

	Vec2 gorilla_pos{},
		pos_min{},
		pos_max(100,100);
	
	int amount_hunger_muzhikov = 100,
		seed = 0;
	double swarm_best = DBL_MAX,
		dist_low=0,
		dist_max=Vec2::dist(pos_min,pos_max);

	Particle* Swarm = new Particle[amount_hunger_muzhikov];


	
	for (int i = 0;i < amount_hunger_muzhikov;i++) {
		Swarm[i].pos.rand_vec(dist_low,dist_max,&seed);
		Swarm[i].best = Swarm[i].pos;
		Swarm[i].speed.rand_vec(-(dist_max - dist_low), dist_max - dist_low);
	}

//goida


}