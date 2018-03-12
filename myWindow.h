#ifndef WINDOW_H_
#define WINDOW_H_
#include<windows.h>
#include<glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include <cstring>
#include <iostream>
#include "Cube.h"
#include "Object3d.h"
#include "MatVec.h"
#include "transformation.h"
using namespace std;
class myWindow
{
private:
    int height;
    int width;
    string name;
    int positionx;
    int positiony;
    int ac;
    char **av;
    static Vec3 camera;
    static int flag;
    static int xangle,yangle;

public:
    static Object3d myobj1,myobj2,myobj3;
    myWindow(int argc, char ***argv,int h=500, int w=1000, int px=0, int py=0,string wname="my window")
    {
        height=h;
        width=w;
        name=wname;
        positionx=px;
        positiony=py;
        ac=argc;
        av=*argv;
        flag=-1;
        xangle=0;
        yangle=0;
        camera=Vec3(0,0,100);
        myobj1.loadObject("E:/graphics_cloned_projects/myprojects/SUSHANTE/objects/plant.obj");
        myobj2.loadObject("E:/graphics_cloned_projects/myprojects/SUSHANTE/objects/newroad.obj");
        myobj3.loadObject("E:/graphics_cloned_projects/myprojects/SUSHANTE/objects/carexported.obj");
        for(int i=0;i<myobj3.vertBuffer.size();i++)
        {
            RotateX(myobj3.vertBuffer[i].v,-90);
        }




        show();

    }
    static void keyPressed(unsigned char key, int x, int y)
    {
        if (key == 'a')
        {
            if(yangle<=83)
            {
                yangle+=5;


            }

            flag=2;

        }
        if (key == 's')
        {

            if(xangle<=83)
            {
                xangle+=5;

            }
            flag=0;
        }
        if (key == 'd')
        {

            if(yangle>=-83)
            {
                yangle-=5;


            }
            flag=3;

        }
        if (key == 'w')
        {

            if(xangle>=-83)
            {
                xangle-=5;

            }
            flag=1;

        }
         if (key == 'x')
        {
            flag=5;

        }
         if (key == 'z')
        {
            flag=4;

        }
        if (key == 'o')
        {
            flag=6;

        }
        if (key == 'p')
        {
            flag=7;

        }
        if(key=='t')
        {
            flag=8;
        }
        glutPostRedisplay();
    }
    void show()
    {

        glutInit(&ac, av);
        glutInitWindowSize(width,height);
        glutCreateWindow("my window");

        glutDisplayFunc(display);
        glutKeyboardFunc(keyPressed);
        glutReshapeFunc(reshape);

        glutMainLoop();
    }
    static void idle()

    {
        int length=myobj3.vertBuffer.size();
        for(int i=0;i<length;i++)
        {
            Translate(myobj3.vertBuffer[i].v,Vec3(0,0.3,0));
            //glutPostRedisplay();
            //Translate(myobj3.vertBuffer[i].v,Vec3(-myobj3.xdisplacement,-myobj3.ydisplacement,0));
            //RotateZ(myobj3.vertBuffer[i].v,15);
            //myobj3.xdisplacement++;
            //myobj3.ydisplacement++;
            //Translate(myobj3.vertBuffer[i].v,Vec3(myobj3.xdisplacement,myobj3.ydisplacement,0));

        }
        glutPostRedisplay();
    }
    static void display(void)
    {

        //Vec3 fcamera(-5,0,-80);

        Vec3 color1(0,1,0);
        /** \brief
         *
         * \param 0.1
         * \param 0.1
         * \param 0.1
         * \return Vec3
         *
         */
        Vec3 color2(0.5,0.5,0.5);
        Vec3 color3(1,0,0);

        int wireframe = 0;
        float intensity = 100;
        int lightsource = 50;

        //Vec3 camera(-25,-25,-25);
        Vec3 LookTo(0,0,0);
        vector<Vec3> Lightposition1;
        vector<Vec3> Lightposition2;
        vector<Vec3> Lightposition3;
        Lightposition1.push_back(Vec3(0,0,-400));
        glClearColor(1,1,1,1);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        myobj1.render(camera,LookTo,Lightposition1,0.5,0.5,color1,intensity,flag);
        myobj2.render(camera,LookTo,Lightposition1,0.5,0.5,color2,intensity,flag);
        myobj3.render(camera,LookTo,Lightposition1,0.5,0.5,color3,intensity,flag);
        flag=-1;

       glutSwapBuffers();
       glutIdleFunc(idle);


       // model.render(camera,LookTo,Lightposition1,0.5,0.5,color,intensity);
        glFlush();  /* Single buffered, so needs a flush. */
        myobj1.Zbuffer=new float[500*1000]();
    }
    static void reshape(int w, int h)
    {
          /* Because Gil specified "screen coordinates" (presumably with an
             upper-left origin), this short bit of code sets up the coordinate
             system to correspond to actual window coodrinates.  This code
             wouldn't be required if you chose a (more typical in 3D) abstract
             coordinate system. */

          glViewport(0, 0, w, h);       /* Establish viewing area to cover entire window. */
          glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
          glLoadIdentity();             /* Reset project matrix. */
          glOrtho(0, w, 0, h, -1, 1);   /* Map abstract coords directly to window coords. */
          glScalef(1, -1, 1);           /* Invert Y axis so increasing Y goes down. */
          glTranslatef(0, -h, 0);       /* Shift origin up to upper-left corner. */
    }


};
Object3d myWindow::myobj2= Object3d(0,100);
Object3d myWindow::myobj1= Object3d(0,0,5,0,0);
Object3d myWindow::myobj3= Object3d(0,0,0,0,0,1);
Vec3 myWindow::camera= Vec3(0,0,0);
int myWindow::xangle=0;
int myWindow::yangle=0;
int myWindow::flag=1;
#endif // WINDOW_H_

