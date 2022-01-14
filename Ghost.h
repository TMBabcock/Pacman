#include <stdlib.h>
#include <vector>
#include <deque>
#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

class Ghost
{
	private:
		char name;
		bool isSick = true;
		float position [2];
		float rgb [3];
		const int squareSize = 50;
		int direction;

	public:
		//Responsible for the "Drawing" of the ghost.
		void spawn()
		{
			if (isSick)
			{
				int x, y;
				glBegin(GL_LINES);
				glColor3f(rgb[0], rgb[1], rgb[2]);
				//draw the head
				for (int k = 0; k < 32; k++) {
					x = (float)k / 2.0 * cos(360 * M_PI / 180.0) + (position[0] * squareSize);
					y = (float)k / 2.0 * sin(360 * M_PI / 180.0) + (position[1] * squareSize);
					for (int i = 180; i <= 360; i++) {
						glVertex2f(x, y);
						x = (float)k / 2.0 * cos(i * M_PI / 180.0) + (position[0] * squareSize);
						y = (float)k / 2.0 * sin(i * M_PI / 180.0) + (position[1] * squareSize);
						glVertex2f(x, y);
					}
				}
				glEnd();
				//draw body
				glRectf((position[0] * squareSize) - 17, position[1] * squareSize, (position[0] * squareSize) + 15, (position[1] * squareSize) + 15);
				glBegin(GL_POINTS);
				glColor3f(0, 0.2, 0.4);
				//draw eyes and legs
				glVertex2f((position[0] * squareSize) - 11, (position[1] * squareSize) + 14); //legs
				glVertex2f((position[0] * squareSize) - 1, (position[1] * squareSize) + 14); //legs
				glVertex2f((position[0] * squareSize) + 8, (position[1] * squareSize) + 14); //legs
				glVertex2f((position[0] * squareSize) + 4, (position[1] * squareSize) - 3); //eyes
				glVertex2f((position[0] * squareSize) - 7, (position[1] * squareSize) - 3); //eyes 
				glEnd();
			}
		}
		//Responsible for moving the ghost.
		void move(vector<vector<bool>> bitmap)
		{
			//find the current position of the monster
			int x1Quadrant = (int)((position[0] - (2 / squareSize)) - (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
			int x2Quadrant = (int)((position[0] + (2 / squareSize)) + (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
			int y1Quadrant = (int)((position[1] - (2 / squareSize)) - (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
			int y2Quadrant = (int)((position[1] + (2 / squareSize)) + (16.0 * cos(360 * M_PI / 180.0)) / squareSize);
			//move him acording to its direction until he hits an obstacle
			switch (direction) 
			{
			case 1:
				if (!bitmap.at(x1Quadrant).at(position[1])) {
					position[0] -= 2 / squareSize;
				}
				else {
					int current = direction;
					do {
						direction = (rand() % 4) + 1;
					} while (current == (int)direction);
				}
				break;
			case 2:
				if (!bitmap.at(x2Quadrant).at((int)position[1])) {
					position[0] += 2 / squareSize;
				}
				else {
					int current = direction;
					do {
						direction = (rand() % 4) + 1;
					} while (current == (int)direction);
				}
				break;
			case 3:
				if (!bitmap.at((int)position[0]).at(y1Quadrant)) {
					position[1] -= 2 / squareSize;
				}
				else {
					int current = direction;
					do {
						direction = (rand() % 4) + 1;
					} while (current == (int)direction);
				}
				break;
			case 4:
				if (!bitmap.at((int)position[0]).at(y2Quadrant)) {
					position[1] += 2 / squareSize;
				}
				else {
					int current = direction;
					do {
						direction = (rand() % 4) + 1;
					} while (current == (int)direction);
				}
				break;
			default:
				break;
			}
		}

	public:
		//Constructor
		Ghost(char name, float x, float y, int direction, float r, float g, float b)
		{
			this->name = name;
			this->position[0] = x;
			this->position[1] = y;
			this->direction = direction;
			this->rgb[0] = r;
			this->rgb[1] = g;
			this->rgb[2] = b;
		}
};
