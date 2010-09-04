Author(s)
==================
William Howard - http://william.howard.name

Description
==================
This project was a complete redo from scratch of an assignment
completed for my 3rd year computer science course titled "Scientific
Visualization and Computer Graphics" which basically required us to
create a somewhat complicated raytracer from scratch (everything but
drawing the pixels, which we used glut for).  

The reason I redid this assignment was because I utterly failed at it 
the first time (as did most the class) and because I felt I needed more 
experience developing with C++ (we focused mostly on Java through my
whole undergraduate time).

The raytracer includes the following features:
	Plane and Sphere primitives!
	Phong shading! (ambient, diffuse, specular highlighting)
	Specular Reflection!
	
For now the scene is static, composed of 6 spheres and one plane.  The
plane is black, 100% reflective, and is parallel to the XY plane.  The
six spheres are:
	the origin (yellow)
	the three primary axes X,Y, and Z (red, green and blue)
	two white lights
	
If any future work is done on this project it will likely include:
	XML based scene loading (maybe using the tinyxml library)
	Soft shadows
	Refraction
	A REAL Scene Manager
	Multithreading

Controls
==================
YES you can actually move the camera at runtime and YES it will be incredibly
slow.  The camera is rigged onto a sphere and is always pointed at the origin.
You can only move the camera between -45 deg and +45 deg to the XY plane but
have full 360 deg rotation about the Z axis.  The controls are:
	W : Increase angle on the XY plane
	S : Decrease angle on the XY plane
	A : Rotate right on the Z axis
	D : Rotate left on the Z axis

	R : Zoom In
	F : Zoom Out

	+ : increase pixel multiplication (speeds up raytracing GREATLY)
	- : decrease pixel multiplication (higher quality image but slower)

Installation
==================
I don't concern myself with installing it in a friendly location on
the target OS, building it and running the executable should be
sufficient for now.  Two makefiles are provided for Linux (tested
on Ubuntu Linux Intrepid Ibex) and Mingw32 (tested on Windows XP Home).
These makefiles are makefile.linux and makefile.mingw respectively.

To build on Linux make sure you have at least freeglut3-dev and 
libcppunit-dev installed.  Since I never got cppunit working for
mingw I haven't bothered including the unit tests in the build.

To build on Windows I've included freeglut.lib and freeglut.dll in
the zip file to hopefully make things easier.  You will need to make
sure your OpenGL and Freeglut headers are included in your mingw32
include path.

Building should be as simple as invoking:
	make -f makefile.linux
or
	mingw32-make -f makefile.mingw
assuming you have your PATH variables setup right.

License
==================
The project is licensed under the GPL v3.0 whose text is included
as gpl-3.0.txt

Libraries
==================
	freeglut 3 (http://freeglut.sourceforge.net/)
		OpenGL + freeglut is used as the frontend of the program so 
		that I don't have to know and write code for the Win32,	X11
		and OpenGL APIs.  Really all this does is just open a
		drawing window and paint pixels on it based on the result of
		the raytracing.  It also handles keyboard interaction.
		
		A precompiled freeglut.dll is included in the Windows binary
		folder alongside the precompiled exe file.  Linux users
		shouldn't have a problem installing proper shared object 
		libraries for freeglut so I haven't included them (and I don't
		intend to contribute to Linux DLL HELL).
		
	cppunit (http://cppunit.sourceforge.net/)
		I never actually got this working with mingw32 