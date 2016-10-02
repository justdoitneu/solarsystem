//
//stars.hpp
//solarsystem
//
#ifndef star_hpp
#define star_hpp

#include<GL/glut.h>
//    颜色 color
//    公转半径 radius
//    自转速度 selfSpeed
//    公转速度 speed
//    距离太阳中心的距离 distance
//    绕行的星球 parentStar
//    当前的自转的角度 alphaSelf
//    当前的公转角度 alpha
class Star{
public:
	GLfloat radius;
	GLfloat speed,selfSpeed;
	GLfloat distance;
	GLfloat rgbaColor[4];
	//父节点星球
	Star* parentStar;
	//构造函数,星球必需参数
	Star(GLfloat radius, GLfloat distance, 
		GLfloat speed, GLfloat selfSpeed,
		Star* parent); 
	//绘制移动,旋转
	void drawStar();
	//虚函数,提供默认实现,调用drawStar()
	virtual void draw(){drawStar();}
	//参数为每次刷新画面时的时间跨度,单位天
	virtual void update(long timeSpan);
protected:
	GLfloat alphaSelf,alpha;
};
class Planet : public Star{
public:
	Planet(GLfloat radius, GLfloat distance,
                GLfloat speed,GLfloat selfSpeed,
                Star* parent,GLfloat rgbaColor[3]);
	//增加材质
	void drawPlanet();
	//继续向其子类开放重写功能
	virtual void draw(){drawPlanet(); drawStar();}
};
class LightPlanet : public Planet{
public:
	LightPlanet(GLfloat radius, GLfloat distance,
                GLfloat speed,GLfloat selfSpeed,
                Star* parent,GLfloat rgbColor[]);//有4吗？
	//增加光源
	void drawLight();
	virtual void draw(){drawLight(); drawPlanet(); drawStar();}
};
#endif //star_hpp
