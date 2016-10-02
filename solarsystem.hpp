//
//solarsystem.hpp
//solarsystem
//
#include<GL/glut.h>

#include"stars.hpp"

#define STARS_NUM 10

class SolarSystem {

public:
	SolarSystem();
	~SolarSystem();
	
	void onDisplay();
	void onUpdate();
	void onKeyboard(unsigned char key, int x, int y);

private:
	//存储星星资料
	Star* stars[STARS_NUM];
	
	//定义观察视角的参数
	GLdouble viewX, viewY, viewZ;
	GLdouble centerX, centerY, centerZ;
	GLdouble upX, upY, upZ;
};
//注意，类定义后面有；号