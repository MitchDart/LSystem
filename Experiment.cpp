#include "Experiment.h"

void Experiment::setup() {
	printf("Setting up experiment\n");

	LSystem* lsystem = new LSystem("F");
	glutPostRedisplay();
}


glm::vec3 Experiment::v4tov3(glm::vec4 v1)  {
    return glm::vec3(v1.x, v1.y, v1.z);
}

Experiment::Experiment()
{
	numObjects = 0;
	started = false;
}

Experiment::~Experiment(void)
{
}

void Experiment::initGLUT(int argc,char** argv) {
	printf("Initialising GLUT\n");
	glutInit(&argc,argv);
	
	//if(!GLEW_VERSION_4_2) {
	//	printf("Glew 4.2 not supported\n");
	//	exit(0);
	//}
	
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(888, 500);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_MULTISAMPLE);
	glutCreateWindow("Splines");

	glewInit();
	glutFullScreen();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(keyboard);
	glutKeyboardFunc(asci);
	glutKeyboardUpFunc(asciup);
	glutPassiveMotionFunc(mouseMove);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(6);
	glutMainLoop();
}

void Experiment::mouseMove(int x,int y)
{
}


void Experiment::asciup(unsigned char key, int x, int y)
{

}

void Experiment::asci(unsigned char key, int x, int y) {
	if(key == (char)27) {
		exit(0);
	}
}

void Experiment::keyboardup(int key,int x,int y) {
}
void Experiment::keyboard(int key, int x, int y) {
}
void Experiment::idle(void) {
	if(!Experiment::getInstance().started) {
		Experiment::getInstance().setup();
		Experiment::getInstance().started = true;
	} else {
		glutPostRedisplay();
	}
	
}

void Experiment::display(void) {
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(int i = 0; i < Experiment::getInstance().numObjects; i++)
		Experiment::getInstance().objectStack[i]->draw();

	glutSwapBuffers();

	glFlush();
}

void Experiment::addToObjectStack(Object* o) {
	Object** temp = new Object*[numObjects + 1];
	for(int i = 0; i < numObjects; i++)
		temp[i] = objectStack[i];
	temp[numObjects] = o;
	delete [] objectStack;
	objectStack = temp;
	numObjects++;
	
}
