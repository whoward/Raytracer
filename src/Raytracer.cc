/*
 * Raytracer.cc
 *
 *  Created on: 24-Jan-2009
 *      Author: will
 */
#ifdef _WIN32
	#include <windows.h>
#endif

#include "GL/freeglut_std.h"

#include <iostream>
#include <cmath>

#include "Vector3f.hh"
#include "primitives/Primitive.hh"
#include "primitives/Sphere.hh"
#include "primitives/Plane.hh"
#include "scenemanager/BasicSceneManager.hh"

using namespace std;

#define PI_180 0.01745329252				//the value of PI/180 (conversion multiplier for degrees to radians)

#define CAM_SPEED 0.1						//velocity in GL Units per frame
#define CAM_SPEED_ANGULAR 2					//velocity for the angles in degrees per frame
#define CAM_DIST_MAX 40.0					//maximum distance between the target and camera in GL Units
#define CAM_DIST_MIN 0.2					//minimum distance between the target and camera in GL Units
#define CAM_MAXANGLE_YZ 80					//maximum angle on the YZ plane in degrees

#define TRACE_DEPTH_MIN 0
#define TRACE_DEPTH_MAX 10

// values to store camera details
GLfloat cam_angle[2]  =	{-45.0f, 45.0f};	//The camera's angle on the XY and YZ planes respectively
GLfloat cam_dist 	  =	5.0f;				//The camera's distance to its target vector

/** handle to the drawing window*/
int window = 0;

/** pixel size multiplier */
int pix_sz = 1;

/** raytrace depth */
int traceDepth = 5;

/** direction of the up vector */
Vector3f up(0.0f, 0.0f, -1.0f);

/** uvw coordinate system */
Vector3f u, v;

/** values for the screen plane */
float W = 4;
float H = 3;
float view_dist = 2.0f;

/** colour predefinitions */
Vector3f red    (0.4f, 0.0f, 0.0f);
Vector3f yellow (0.4f, 0.4f, 0.0f);
Vector3f white  (1.0f, 1.0f, 1.0f);
Vector3f blue   (0.0f, 0.0f, 0.4f);
Vector3f green  (0.0f, 0.4f, 0.0f);
Vector3f purple (1.0f, 0.0f, 1.0f);
Vector3f black  (0.0f, 0.0f, 0.0f);
Vector3f horizon(0.9843f, 0.8863f, 0.5126f);
Vector3f metal  (0.01f, 0.01f, 0.01f);

/** The Scene Manager Object */
SceneManager* scene = new BasicSceneManager( Vector3f(5.0f, 5.0f, 5.0f), Vector3f(0.0f, 0.0f, 0.0f) );

/** Some helper math functions */
inline float max(float a, float b) { return (a > b)?a:b; }
inline float min(float a, float b) { return (a < b)?a:b; }
inline float clamp(float var, float a, float b) { return min( max(var, a), b ); }

/*
 *  Display function.  This function is called each time the
 *  display screen needs to be redrawn
 */

void display() {
	// Recalculate the eye position
	Vector3f eye;
	eye.x = -cos(cam_angle[0]*PI_180) * cam_dist;
	eye.y = -sin(cam_angle[0]*PI_180) * cam_dist;
	eye.z =  sin(cam_angle[1]*PI_180) * cam_dist;

	scene->setEyePosition(eye);

	// Get the window dimensions
	int wnd_w, wnd_h;
	wnd_w = glutGet(GLUT_WINDOW_WIDTH);
	wnd_h = glutGet(GLUT_WINDOW_HEIGHT);

	// Set the matrices
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, wnd_w, 0, wnd_h);

	// Ensure that lighting is disabled as the raytracer does its own lighting
	glDisable(GL_LIGHTING);

	// The normalized vector the eye is looking at, also known as the -w vector
	Vector3f view_dir = scene->getEyeDirection();

	// Calculate the U and V vectors
	u = view_dir ^ up;
	v = view_dir ^ u;

	// Go through every pixel and ray trace
	for(int row=0; row < wnd_h; row += pix_sz) {
		for(int col=0; col < wnd_w; col += pix_sz) {
			// calculate the direction of the ray
			float Su = -W + W*((float)(2*col)/(float)wnd_w);
			float Sv = -H + H*((float)(2*row)/(float)wnd_h);

			Vector3f* point = new Vector3f();
			point->x = eye.x + Su * u.x + Sv * v.x + view_dist * view_dir.x;
			point->y = eye.y + Su * u.y + Sv * v.y + view_dist * view_dir.y;
			point->z = eye.z + Su * u.z + Sv * v.z + view_dist * view_dir.z;

			Vector3f dir = (*point - eye).normalize();

			// perform ray tracing to get a color
			Vector3f color = scene->raycolour(*point, dir);

			// set the drawing color
			glColor3f( color.x, color.y, color.z );

			// draw the pixel(s) with the color
			glRecti(col, row, col+pix_sz, row+pix_sz);
		}
	}
}

void modifyRaytraceDepth(int delta) {
	traceDepth = clamp ( traceDepth + delta, TRACE_DEPTH_MIN, TRACE_DEPTH_MAX );
	scene->setRaytraceDepth(traceDepth);
	cout << "updated raytrace depth: " << traceDepth << endl;
}

void modifyPixelSize(int delta) {
	pix_sz = max( pix_sz + delta, 1 );
	cout << "updated pixel size: " << pix_sz << endl;
}

/**
 * Called when a key is pressed
 */
void keyhandler(unsigned char key, int x, int y) {
	if(key == 'a')
		cam_angle[0] += CAM_SPEED_ANGULAR;
	else if(key == 'd')
		cam_angle[0] -= CAM_SPEED_ANGULAR;
	else if(key == 'w')
		cam_angle[1] = clamp( cam_angle[1]+CAM_SPEED_ANGULAR, -CAM_MAXANGLE_YZ, CAM_MAXANGLE_YZ);
	else if(key == 's')
		cam_angle[1] = clamp( cam_angle[1]-CAM_SPEED_ANGULAR, -CAM_MAXANGLE_YZ, CAM_MAXANGLE_YZ);
	else if(key == 'r')
		cam_dist = clamp( cam_dist-CAM_SPEED, CAM_DIST_MIN, CAM_DIST_MAX );
	else if(key == 'f')
		cam_dist = clamp( cam_dist+CAM_SPEED, CAM_DIST_MIN, CAM_DIST_MAX );
	else if(key == '-')
		modifyPixelSize(-1);
	else if(key == '=')
		modifyPixelSize(1);
	else if(key == '[')
		modifyRaytraceDepth(-1);
	else if(key == ']')
		modifyRaytraceDepth(1);

	glutPostRedisplay();
}

/*
 * The main function
 */
int main(int argc, char **argv) {
	cout << "Creating Scene." << endl;

	Primitive* sphere = new Sphere(Vector3f(2.0f, 0.0f, 0.0f), 1.0f);
	sphere->setMaterial(Material(red, 0.2f, 1.0f, 0.0f, 64.0f));
	scene->addPrimitive(sphere);

	Primitive* sphere2 = new Sphere(Vector3f(0.0f, 0.0f, 2.0f), 1.0f);
	sphere2->setMaterial(Material(blue, 0.2f, 1.0f, 0.0f, 64.0f));
	scene->addPrimitive(sphere2);

	Primitive* sphere3 = new Sphere(Vector3f(0.0f, 2.0f, 0.0f), 1.0f);
	sphere3->setMaterial(Material(green, 0.2f, 1.0f, 0.0f, 64.0f));
	scene->addPrimitive(sphere3);

	Primitive* sphere4 = new Sphere(Vector3f(0.0f, 0.0f, 0.0f), 1.0f);
	sphere4->setMaterial(Material(yellow, 0.2f, 1.0f, 0.0f, 64.0f));
	scene->addPrimitive(sphere4);

	Primitive* plane = new Plane(Vector3f(0.0f, 0.0f, 1.0f), 3.0f);
	plane->setMaterial(Material(black, 0.6f, 0.5f, 1.0f, 64.0f));
	scene->addPrimitive(plane);

	Primitive* light = new Sphere(Vector3f(0.0f,6.0f,6.0f), 1.0f);
	light->setMaterial(Material(white, 0.0f, 0.0f, 0.0f, 50.0f));
	light->setLight(true);
	scene->addPrimitive(light);

	Primitive* light2 = new Sphere(Vector3f(2.0f,-6.0f,2.0f), 1.0f);
	light2->setMaterial(Material(white, 0.0f, 0.0f, 0.0f, 50.0f));
	light2->setLight(true);
	scene->addPrimitive(light2);

	cout << "Scene created, contains " << scene->primitiveCount() << " objects." << endl;

	scene->setRaytraceDepth(traceDepth);

	// Ensure the window is an appropriate 4:3 size
	glutInitWindowSize( 640, 480 );

	// Initialize GLUT and process its command line arguments
	glutInit(&argc,argv);

	// Set the display mode, double buffered, RGB colour and depth buffer
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

	// Create the display window
	window = glutCreateWindow("Ray Tracer");

	// set the function pointers
	glutDisplayFunc(display);

	// a keyboard handling function so we can move the camera in the raytracer and modify other values
	glutKeyboardFunc(keyhandler);

	// Pass control to GLUT to run the application
	glutMainLoop();
}
