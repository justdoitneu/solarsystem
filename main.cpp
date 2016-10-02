//
//main.cpp
//solarsystem
//
//头文件
#include <GL/glut.h>
#include "solarsystem.hpp"

#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 600

SolarSystem solarsystem;
//注册窗口回调函数
void onDisplay(void){
	solarsystem .onDisplay();
}
void onUpdate(void){
	solarsystem.onUpdate();
}
void onKeyboard(unsigned char key,int x,int y){
	solarsystem.onKeyboard(key,x,y);
}

int main(int argc, char* argv[]){
	//初始化glut
	glutInit(&argc, argv);
	//rgba颜色模式 双缓存窗口
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	//窗口左上角在屏幕的位置
	glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
	glutInitWindowSize(WIDTH,HEIGHT);
	//程序名称
	glutCreateWindow("solarsystem at sky");
	// glutDisplayFunc 的函数原型为 glutDisplayFunc(void (*func)(void))
 	// 这是一个回调函数，每当 GLUT 确定一个窗口的内容需要更新显示的时候,
 	// glutDisplayFunc 注册的回调函数就会被执行.
	//
 	// glutIdleFunc(void (*func)(void)) 将指定一个函数，用于处理当事件循环
 	// 处于空闲的时候，就执行这个函数。这个回调函数接受一个函数指针作为它的唯一参数
	//
 	// glutKeyboardFunc(void (*func)(unsigned char key, int x, int y))
 	// 会将键盘上的键与一个函数关联，当这个键被按下或者释放时，函数就会调用
 	//
 	// 因此下面的三行实际上是在向 GLUT 注册关键的三个回调函数
	glutDisplayFunc(onDisplay);
	glutIdleFunc(onUpdate);
	glutKeyboardFunc(onKeyboard);
	
	glutMainLoop();
	return 0;
}
