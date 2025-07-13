#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 

	resetParticles();

}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the fourth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( glm::vec3( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) , 0) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
	/**/
	if (pause){return;}
	/**/
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].update();
		p[i].particleSpeed = particleSpeed;
	}
	
	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}	

	/**/  //Replay Code
	if(replay == true){
		record = false;
		if(count == 120){
			keyPressed(recordMemory[i]);
			i++;
			count = 0;
		}
		if(i == recordMemory.size()){ 
			i = 0;
			replay = false;
			record = false;

			recordMemory.erase(recordMemory.begin() , recordMemory.end());
		}

		if(count < 120){
			count++;
		}
		else{
			count = 0;
		}
	}
	/**/
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw();
	}
	
	ofSetColor(190);
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}
	
	if (drag == true){
		ofSetColor(255,255,255,25);
		ofDrawRectangle(dragX, dragY, currentMoveX - dragX, currentMoveY - dragY); // Rectangle dimensioned while dragging and holding left click
	} else if (drag == false && finishDrag == true){
		ofSetColor(255,255,255,25);
		ofDrawRectangle (dragX, dragY, endMoveX - dragX, endMoveY - dragY); //Rectangle drawed when
		newX =dragX;
		newY = dragY;
		newWidth = endMoveX - dragX;
		newHeight = endMoveY - dragY;
		madeRect = true;
		finishDrag=false;
	}

	if(madeRect == true){
		ofSetColor(255,255,255,25);
		ofDrawRectangle (newX,newY,newWidth,newHeight);
	}

		
	ofSetColor(230);	
	//ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**/
	ofDrawBitmapString(currentModeStr + "\n" , 10 , 20);
	ofDrawBitmapString("Spacebar to reset\n" , 10 , 40);
	ofDrawBitmapString("Key 1-4 to change mode\n" , 10 , 60);
	ofDrawBitmapString("Press 't' to change particle color\n" , 10 , 80);
	ofDrawBitmapString("Press 's' to pause\n" , 10 , 100);
	ofDrawBitmapString("Press 'd' duplicate particle speed\n" , 10 , 120);
	ofDrawBitmapString("Press 'a' halves particle speed\n" , 10 , 140);
	ofDrawBitmapString("Press 'r' to start record\n" , 10 , 160);
	ofDrawBitmapString("Press 'p' to start replay\n" , 10 , 180);
	ofDrawBitmapString("Press 'c' to cancel replay\n" , 10 , 200);

	if(record == true){
		ofDrawBitmapString(showMessageRecord + "\n" , 500 , 80);
	}
	if(replay == true){
		ofDrawBitmapString(showMessageReplay + "\n" , 600 , 80);

		ofDrawBitmapString(press + " is pressed\n" , 600 , 100);
	}
	/**/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	/**/
	if(record == true){
		recordMemory.push_back(key);
	}
	/**/

	
	
	if( key == '1'){
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";

		/**/
		press = "Key 1";
		/**/ 		
	}
	if( key == '2'){
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse"; 	

		/**/
		press = "Key 2";
		/**/			
	}
	if( key == '3'){
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force"; 

		/**/
		press = "Key 3";
		/**/						
	}
	if( key == '4'){
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 						
		resetParticles();

		/**/
		press = "Key 4";
		/**/
	}	
		
	if( key == ' ' ){
		resetParticles();
		/**/
		press = "Space Bar";
		/**/
	}

	if (key == 's'){
		pause = !pause;
	}

	if (key == 'd'){
		particleSpeed *= 2;
	}

	if (key == 'a'){
		particleSpeed *= 0.5;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/**/
	if(key == 'r'){
		record = !record;
	}

	if(key == 'p'){
		replay = true;
	}

	if(key == 'c'){
		replay = false;
	}
	/**/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
		currentMoveX = x;
		currentMoveY = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	if(button == 0){
		madeRect=false;
		drag = true;
		dragX = x;
		dragY = y;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
 if(button == 0 && madeRect == false){
		endMoveX = currentMoveX;
		endMoveY = currentMoveY;
		drag = false;
		finishDrag = true;
	}


	if(button == 2 && madeRect == true  && x <= max(newX , endMoveX)  &&  x >= min(newX , endMoveX)  &&  y <= max(newY , endMoveY)  && y >= min(newY , endMoveY)){
		madeRect = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
