//
//stars.cpp
//solarsystom
//
#include "stars.hpp"
//sin,cos中需要cmath头文件
#include "cmath"

#define PI 3.1415926536

Star::Star(GLfloat radius, GLfloat distance,
           GLfloat speed,GLfloat selfSpeed,      
           Star* parent){
//
	this->radius = radius;
	this->distance = distance;
	this->selfSpeed = selfSpeed;
	this->alphaSelf = this->alpha =0;

	for(int i=0; i<4; i++){
		this->rgbaColor[i] = 1.0f;
	}

	this->parentStar = parent;

	if(speed > 0){
		this->speed = 360.0f/speed;
	}else{
		this->speed = 0.0f;
	}

} 
void Star::drawStar(){
//
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	int n = 1440;
	
	//保存opengl当前矩阵环境
	glPushMatrix();
	{	
		//公转
		//如为行星，且距离不为0，就向原点平移一个半径
		//这部分处理卫星，本例中指月球
		if(parentStar != 0 && parentStar->distance > 0){
			//将绘制的图形沿 z 轴旋转 alpha
			glRotatef(parentStar->alpha,0,0,1);
			// x 轴方向上平移 distance , y,z 方向不变
			glTranslatef(parentStar->distance,0.0,0.0);
		}
		
		// 绘制运行轨道
		//图形绘制开始和结束要调用glBegin和glEnd.GL_POLYGON 则是绘制一个从第一个点到第 n 个点的多边形
		glBegin(GL_LINES);
		for(int i=0; i<n; ++i){
			glVertex2f(distance*cos(2*PI*i/n),
						distance*sin(2*PI*i/n));
		}
		glEnd();

		glRotatef(alpha, 0, 0, 1);
		glTranslatef(distance, 0.0, 0.0);
		
		//自传
		glRotatef(alphaSelf, 0, 0, 1);
		
		//绘制星星颜色
		glColor3f(rgbaColor[0], rgbaColor[1], rgbaColor[2]);
		//绘制星星半径，经纬线条数		
		glutSolidSphere(radius, 40, 32);
	}
	// 恢复绘制前的矩阵环境
	glPopMatrix();
}
void Star::update(long timeSpan){
	//更新公转角度，自传角度
	alpha += timeSpan * speed;
	alphaSelf += timeSpan * selfSpeed;
}

Planet::Planet(GLfloat radius, GLfloat distance,
                GLfloat speed,GLfloat selfSpeed,
                Star* parent,GLfloat rgbaColor[3]) :
Star(radius, distance, speed, selfSpeed, parent){
//
	this->rgbaColor[0] = rgbaColor[0];
	this->rgbaColor[1] = rgbaColor[1];
	this->rgbaColor[2] = rgbaColor[2];
	this->rgbaColor[3] = 1.0f;	
}

void Planet::drawPlanet(){
	//不发光星球，绘制光照效果
	GLfloat mat_ambient[]   = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat mat_diffuse[]   = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat mat_specular[]  = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat mat_emission[]  = {rgbaColor[0], rgbaColor[1],rgbaColor[2], rgbaColor[3]};
	GLfloat mat_shininess   = 90.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);//传入数组参数
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION,  mat_emission);
	glMaterialf (GL_FRONT, GL_SHININESS, mat_shininess);//仅传入单个参数
}

LightPlanet::LightPlanet(GLfloat radius, GLfloat distance, 
			GLfloat speed,GLfloat selfSpeed,
             		Star* parent,GLfloat rgbaColor[]) :
Planet(radius, distance, speed, selfSpeed, parent, rgbaColor){
//
}
void LightPlanet::drawLight(){
	//发光的星球，所以我们不但要设置其光照材质，还要设置其光源位置
	GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat light_ambient[]  = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat light_diffuse[]  = {0.0f, 0.0f, 0.5f, 1.0f};
	GLfloat light_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};

	glMaterialfv(GL_LIGHT0, GL_EMISSION, light_position);// 指定零号光源的位置
	glMaterialfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);// 表示各种光线照射到该材质上，经过很多次反射后追踪遗留在环境中的光线强度
	glMaterialfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);// 漫反射后的光照强度
	glMaterialfv(GL_LIGHT0, GL_SPECULAR, light_specular);// 镜面反射后的光照强度
}

