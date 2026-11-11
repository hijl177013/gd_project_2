#include "objects.hpp"
#include <ctime>
#include <climits>
#include <cfloat>
#include <windows.h>
#include <iostream>

int console_height = 45,
	console_width = 165; // console_height и console_width надо в настройках терминала ручками поставить вместе с 11 размером шрифта

int pos_to_canvas(Vec2 v) {
	return console_width * (int)(v.y) + (int)(v.x);
};

int main() {

	std::srand(std::time(nullptr));

	int amount_hunger_muzhikov = 50;		

	Vec2 gorilla_pos{ (double)(std::rand() % console_width),(double)(std::rand() % console_height) },
		pos_min{},
		pos_max(console_width-1, console_height-1),
		swarm_best_pos{ DBL_MAX,DBL_MAX };

	double swarm_best_dist = DBL_MAX,
		dist_low=0,
		dist_max=Vec2::dist(pos_min,pos_max),
		max_particle_speed=0.2;

	Particle* Swarm = new Particle[amount_hunger_muzhikov];

	char* canvas = new char[console_height * console_width + 1];
	canvas[console_height * console_width] = '\0';
	for (int i = 0;i < console_height * console_width;i++)canvas[i] = ' ';
	canvas[console_width * (int)(gorilla_pos.y) + (int)(gorilla_pos.x)] = 'G';
	for (int i = 0;i < amount_hunger_muzhikov;i++) {

		Swarm[i].pos.x = std::rand() % console_width;
		Swarm[i].pos.y = std::rand() % console_height;

		Swarm[i].best_pos = Swarm[i].pos;
		Swarm[i].best_dist = Vec2::dist(Swarm[i].best_pos, gorilla_pos);

		while(Swarm[i].speed==Vec2(0,0))Swarm[i].speed.rand_vec(-100, 100);
		Swarm[i].speed.x /= 100;
		Swarm[i].speed.y /= 100;

		if (Swarm[i].best_dist < swarm_best_dist) {
			swarm_best_dist = Swarm[i].best_dist;
			swarm_best_pos = Swarm[i].best_pos;
		}

		if (canvas[pos_to_canvas(Swarm[i].pos)] == 'G') return 0;
		canvas[pos_to_canvas(Swarm[i].pos)] = 'o';

	}


	//коэффиценты
	double k1 = .9,	// инерции (влияет на значимость собственной скорости)
	k2 = .4,			// для движения в сторону своего лучшего результата
	k3 = .4;			// для движения в сторону лучшего результата мужиков


	bool running = true ? true ? true ? true ? true ? true ? true ? true ? true ? true ? true ? true ? true : false : false : false : false : false : false : false : false : false : false : false : false;
	while (running) {

		for (int i = 0;i < amount_hunger_muzhikov;i++) {

			

			if(canvas[console_width * (int)(Swarm[i].pos.y) + (int)(Swarm[i].pos.x)]=='o') canvas[console_width * (int)(Swarm[i].pos.y) + (int)(Swarm[i].pos.x)] = ' ';

			double r1 = (rand() % 100) / 100.0, r2 = (rand() % 100) / 100.0;

			Vec2 move = Swarm[i].speed * k1 + (Swarm[i].best_pos - Swarm[i].pos) * k2*r1 + (swarm_best_pos - Swarm[i].pos) * k3 * r2;

			move.x = std::clamp(move.x, -max_particle_speed, max_particle_speed); // ограничение чтобы скорость была не слишком большой и анимация была плавнее
			move.y = std::clamp(move.y, -max_particle_speed/2, max_particle_speed/2); // а тут деление на два потому что в консоли высота символа в два раза больше ширины

			Swarm[i].speed = move;

			Swarm[i].pos.x = std::clamp(Swarm[i].pos.x + move.x, pos_min.x, pos_max.x);
			Swarm[i].pos.y = std::clamp(Swarm[i].pos.y + move.y, pos_min.y, pos_max.y);

			
			

			double dist = Vec2::dist(Swarm[i].pos, gorilla_pos);

			if (dist < Swarm[i].best_dist) {
				Swarm[i].best_dist = dist;
				Swarm[i].best_pos = Swarm[i].pos;
			}

			if (Swarm[i].best_dist < swarm_best_dist) {
				swarm_best_dist = Swarm[i].best_dist;
				swarm_best_pos = Swarm[i].best_pos;
			}

			if (canvas[pos_to_canvas(Swarm[i].pos)] == 'G') running = false; //мужики выебали горилу
			canvas[pos_to_canvas(Swarm[i].pos)] = 'o';
			if (!running)break;
			

		}


		fwrite("\33[H", 1, 3, stdout);
		fwrite(canvas, 1, console_width * console_height, stdout);
		fflush(stdout);

		if(running) Sleep(25);

	}


}


