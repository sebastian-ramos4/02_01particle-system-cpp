#pragma once
#include "ofMain.h"

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE
};

class Particle{

	public:
		Particle();
		
		void setMode(particleMode newMode);	
		void setAttractPoints( vector <glm::vec3> * attract );
		void attractToPoint(int, int);
		void repelFromPoint(int, int);
		void reset();
		void update();
		void draw();		
		
		glm::vec3 pos;
		glm::vec3 vel;
		glm::vec3 frc;
		
		float drag; 
		float uniqueVal;
		float scale;
		
		particleMode mode;
		
		vector <glm::vec3> * attractPoints; 

		

        /**/
        void changeColor();
        ofColor checkColor;
        ofColor defaultColor;
		int r,g,b;
		bool defColor =true;
        bool tKeyPressed;
        bool tKeyJustPressed;
		/**/


		/**/
		double particleSpeed = 1;
		/**/
};
