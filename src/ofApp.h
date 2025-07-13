#pragma once

#include "ofMain.h"
#include "Particle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void resetParticles();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		particleMode currentMode;
		string currentModeStr; 

		vector <Particle> p;
		vector <glm::vec3> attractPoints;
		vector <glm::vec3> attractPointsWithMovement;

		/**/
		float currentMoveX;
		float currentMoveY;
		float endMoveX;
		float endMoveY;
		float dragX;
		float dragY;
		bool drag = false;
		bool madeRect = false;
		bool finishDrag = false;
		float newX;
		float newY;
		float newWidth;
		float newHeight;
		/**/

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**/
		bool pause = false;
		double particleSpeed = 1;
		/**/
		bool record = false;
		vector<int> recordMemory;
		string showMessageRecord = "Recording";

		bool replay = false;
		int count = 0;
		int i = 0;
		string showMessageReplay = "Replay";

		string press;
		/**/
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
};
