#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include "VG/openvg.h"
#include "VG/vgu.h"
#include "shapes.h"

// ~55 seems to be the limit before jankiness kicks in
#define NUM_PARTICLES 50

typedef struct particle {
	int x, y;
	double vx, vy;
	int r, g, b;
	int radius;
} particle_t;

particle_t particles[NUM_PARTICLES];

int showTrails = 0;
int directionRTL = 0;
int alternate = 1;
double gravity = 0.5;

// Initialize _all_ the particles
void initParticles(int w, int h) {
	int i;
	for (i = 0; i < NUM_PARTICLES; i++) {
		particle_t *p = &particles[i];

		p->x = 0;
		p->y = 0;
		p->vx = (rand() % 30) + 30;
		p->vy = (rand() % 20) + 40;
		p->g = rand() % 256;
		p->r = p->g / 2 + rand() % 128;
		p->b = 0;
		p->radius = (rand() % 100) + 200;

		if (directionRTL) {
			p->vx *= -1;
			p->x = w;
		}
	}
}

void paintBG(int w, int h) {
	if (!showTrails)
		return Background(255, 255, 0);

	Fill(0, 0, 0, 0.1);
	Rect(0, 0, w, h);
}

void draw(int w, int h) {
	int i;
	particle_t *p;

	paintBG(w, h);

	for (i = 0; i < NUM_PARTICLES; i++) {
		p = &particles[i];

		Stroke(p->r, p->g, p->b, 0.5);
        Line(p->x,p->y, w/2, h/2);
		// Circle(p->x, p->y, p->radius);

		// Apply the velocity
		p->x += p->vx;
		p->y += p->vy;

		p->vx *= 0.98;
		if (p->vy > 0)
			p->vy *= 0.97;

		// Gravity
		p->vy -= gravity;

		// Stop particles leaving the canvas  
		if (p->x < -50)
			p->x = w + 50;
		if (p->x > w + 50)
			p->x = -50;

		// When particle reaches the bottom of screen reset velocity & start posn
		if (p->y < -50) {
			p->x = 0;
			p->y = 0;
			p->vx = (rand() % 30) + 30;
			p->vy = (rand() % 20) + 40;

			if (directionRTL) {
				p->vx *= -1;
				p->x = w;
			}
		}

		if (p->y > h + 50)
			p->y = -50;
	}

	End();
}

void setOptions(int argc, char **argv) {
	int i = argc;
	while (i--) {
		char option = argv[i][1];

		if (option == 't') {
			showTrails = 1;
			printf("Displaying trails\n");
		}
		// If r or l is set, disable alternation
		if (option == 'r' || option == 'l')
			alternate = 0;

		// Set direction
		if (option == 'r') {
			directionRTL = 1;
			printf("Displaying in right-to-left mode\n");
		}

		if (option == 'l') {
			directionRTL = 0;
			printf("Displaying in left-to-right mode\n");
		}
		if (option == 'g' && i+1 < argc) {
			gravity = atof(argv[i+1]);
			printf("Gravity set to %.2f\n", gravity);
		}
	}
}

// Display Options
// -t  show trails
// -g[value] gravity
//
// Direction (alternates by default)
// -r  right-to-left
// -l  left-to-right
int main(int argc, char **argv) {
	srand(time(NULL));

	setOptions(argc, argv);

	int w, h;
	init(&w, &h);
	initParticles(w, h);

	Start(w, h);
    StrokeWidth(20);
	int i = 0;
	while (1) {
		draw(w, h);

		// NOTE: Consider a `usleep()` in here to not tie up the CPU if you intend serious use

		// Change launch direction every 100 draws
		i++;
		if (alternate && i == 100) {
			directionRTL = directionRTL ? 0 : 1;
			i = 0;
		}
	}
}

