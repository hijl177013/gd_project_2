#include "objects.hpp"
#include <ctime>
#include <climits>
#include <cfloat>
#include <windows.h>
#include <iostream>

int console_height = 165,
	console_width = 45; // console_height и console_width надо в настройках терминала ручками поставить вместе с 11 размером шрифта

int pos_to_canvas(Vec2 v) {
	return console_width * (int)(v.y) + (int)(v.x);
};

int main() {

	//std::srand(std::time(nullptr));

	int amount_hunger_muzhikov = 100;		

	Vec2 gorilla_pos{ 25,25 },
		pos_min{},
		pos_max(console_width-1, console_height-1),
		swarm_best_pos{ DBL_MAX,DBL_MAX };

	double swarm_best_dist = DBL_MAX,
		dist_low=0,
		dist_max=Vec2::dist(pos_min,pos_max);

	Particle* Swarm = new Particle[amount_hunger_muzhikov];

	char* canvas = new char[console_height * console_width + 1];
	canvas[console_height * console_width] = '\0';
	for (int i = 0;i < console_height * console_width;i++)canvas[i] = ' ';
	canvas[console_width * (int)(gorilla_pos.y) + (int)(gorilla_pos.x)] = 'G';
	for (int i = 0;i < amount_hunger_muzhikov;i++) {
		Swarm[i].pos.rand_vec(dist_low,dist_max);
		Swarm[i].best_pos = Swarm[i].pos;
		Swarm[i].best_dist = Vec2::dist(Swarm[i].best_pos, gorilla_pos);
		Swarm[i].speed.rand_vec(-(dist_max - dist_low), dist_max - dist_low);
		if (Swarm[i].best_dist < swarm_best_dist) {
			swarm_best_dist = Swarm[i].best_dist;
			swarm_best_pos = Swarm[i].best_pos;
		}

		if (canvas[pos_to_canvas(Swarm[i].pos)] == 'G') return 0;
		canvas[pos_to_canvas(Swarm[i].pos)] = 'o';

	}


	//коэффиценты
	double k1 = .5,	// инерции (влияет на значимость собственной скорости)
	k2 = 2,			// для движения в сторону своего лучшего результата
	k3 = 2;			// для движения в сторону лучшего результата мужиков


	bool running = true ? true ? true ? true ? true ? true ? true ? true ? true ? true ? true ? true ? true : false : false : false : false : false : false : false : false : false : false : false : false;
	while (running) {

		for (int i = 0;i < amount_hunger_muzhikov;i++) {

			

			if(canvas[console_width * (int)(Swarm[i].pos.y) + (int)(Swarm[i].pos.x)]=='o') canvas[console_width * (int)(Swarm[i].pos.y) + (int)(Swarm[i].pos.x)] = ' ';

			double r1 = (rand() % 100) / 100.0, r2 = (rand() % 100) / 100.0;

			Swarm[i].speed = Swarm[i].speed * k1 + (Swarm[i].best_pos - Swarm[i].pos) * k2*r1 + (swarm_best_pos - Swarm[i].pos) * k3 * r2;
			Swarm[i].pos.x = std::clamp(Swarm[i].pos.x + Swarm[i].speed.x, pos_min.x, pos_max.x);
			Swarm[i].pos.y = std::clamp(Swarm[i].pos.y + Swarm[i].speed.y, pos_min.y, pos_max.y);

			
			

			double dist = Vec2::dist(Swarm[i].pos, gorilla_pos);

			if (dist < Swarm[i].best_dist) {
				Swarm[i].best_dist = dist;
				Swarm[i].best_pos = Swarm[i].pos;
			}

			if (Swarm[i].best_dist < swarm_best_dist) {
				swarm_best_dist = Swarm[i].best_dist;
				swarm_best_pos = Swarm[i].best_pos;
			}

			if (canvas[pos_to_canvas(Swarm[i].pos)] == 'G') running = false;
			canvas[pos_to_canvas(Swarm[i].pos)] = 'o';
			if (!running)break;
			

		}


		fwrite("\33[H", 1, 3, stdout);
		fwrite(canvas, 1, console_width * console_height, stdout);
		fflush(stdout);

		if(running) Sleep(1000);

	}


}


