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
    static Vec3 camera1,camera2,camera;
    static int flag;
    static int xangle,yangle;
    static int camflag,lightflag;
    static int scalefactor;


public:
    static Object3d myobj1,myobj2,myobj3,tire1,tire2;
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
        camera1=Vec3(0,0,100);
        camera2=Vec3(100,100,100);
        camera=camera1;
        myobj1.loadObject("E:/graphics_cloned_projects/myprojects/SUSHANTE/objects/carbody.obj");
        myobj2.loadObject("E:/graphics_cloned_projects/myprojects/SUSHANTE/objects/newroad.obj");
        myobj3.loadObject("E:/graphics_cloned_projects/myprojects/SUSHANTE/objects/carbody.obj");
        tire1.loadObject("E:/graphics_cloned_projects/myprojects/SUSHANTE/objects/tirefront.obj");
        tire2.loadObject("E:/graphics_cloned_projects/myprojects/SUSHANTE/objects/tireback.obj");
        for(int i=0;i<myobj3.vertBuffer.size();i++)
        {
            RotateX(myobj3.vertBuffer[i].v,180);
            Translate(myobj3.vertBuffer[i].v,Vec3(0,-50,-0.5));
        }
        for(int i=0;i<tire1.vertBuffer.size();i++)
        {
            RotateX(tire1.vertBuffer[i].v,180);
            //RotateY(tire1.vertBuffer[i].v,90);
            Translate(tire1.vertBuffer[i].v,Vec3(0,-50,-0.5));

        }
        for(int i=0;i<tire2.vertBuffer.size();i++)
        {
            RotateX(tire2.vertBuffer[i].v,180);
            Translate(tire2.vertBuffer[i].v,Vec3(0,-50,-0.5));

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
            scalefactor*=1.05;

        }
        if (key == 'p')
        {
            flag=7;
            scalefactor*=1;

        }
        if(key=='t')
        {
            flag=8;
        }
        if(key=='1')
        {
            lightflag=0;
        }
        if(key=='2')
        {
            lightflag=1;
        }
        if(key=='3')
        {
            camflag=0;
            camera=camera1;
        }
        if(key=='4')
        {
            camflag=1;
            camera=camera2;
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
        for (int i=0;i<myobj3.vertBuffer.size();i++)
        {
            Translate(myobj3.vertBuffer[i].v,Vec3(0,0.5*scalefactor,0));
        }
        for (int i=0;i<tire1.vertBuffer.size();i++)
        {
            Translate(tire1.vertBuffer[i].v,Vec3(-tire1.xdisplacement,-tire1.ydisplacement,1.75));
            RotateX(tire1.vertBuffer[i].v,360);
            Translate(tire1.vertBuffer[i].v,Vec3(tire1.xdisplacement,tire1.ydisplacement,-1.75));
            //RotateX(tire1.vertBuffer[i].v,5);
            Translate(tire1.vertBuffer[i].v,Vec3(0,0.5*scalefactor,0));
        }
        tire1.ydisplacement+=0.5;
        for (int i=0;i<tire2.vertBuffer.size();i++)
        {
            Translate(tire2.vertBuffer[i].v,Vec3(-tire2.xdisplacement,-tire2.ydisplacement,1.75));
            RotateX(tire2.vertBuffer[i].v,360);
            Translate(tire2.vertBuffer[i].v,Vec3(tire2.xdisplacement,tire2.ydisplacement,-1.75));
            //RotateX(tire1.vertBuffer[i].v,5);
            Translate(tire2.vertBuffer[i].v,Vec3(0,0.5*scalefactor,0));
        }
        tire2.ydisplacement+=0.5;
//        for (int i=0;i<myobj1.vertBuffer.size();i++)
//        {
//                RotateZ(myobj1.vertBuffer[i].v,15);
//        }
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
        Vec3 black(1,0,0);
        Vec3 tirecolor(0,0,0);

        int wireframe = 0;
        float intensity = 100;
        int lightsource = 50;

        //Vec3 camera(-25,-25,-25);
    Vec3 LookTo(0,0,0);
        vector<Vec3> Lightposition1;
        vector<Vec3> Lightposition2;
        vector<Vec3> Lightposition;
        Lightposition1.push_back(Vec3(400,400,-400));
        Lightposition2.push_back(Vec3(-400,0,0));
        if(lightflag==0)
        {
            Lightposition=Lightposition1;
        }
        else if(lightflag==1)
        {
            Lightposition=Lightposition2;
        }
        glClearColor(1,1,1,1);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        myobj1.render(camera,LookTo,Lightposition,0.5,0.5,color1,intensity,flag);
        myobj2.render(camera,LookTo,Lightposition,0.5,0.5,color2,intensity,flag);
        myobj3.render(camera,LookTo,Lightposition,0.5,0.5,color3,intensity,flag);
        tire1.render(camera,LookTo,Lightposition,0.5,0.5,tirecolor,intensity,flag);
        tire2.render(camera,LookTo,Lightposition,0.5,0.5,tirecolor,intensity,flag);
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
Object3d myWindow::tire1= Object3d(0,0,0,0,5);
Object3d myWindow::tire2= Object3d(0,0,0,0,-5);
Vec3 myWindow::camera1= Vec3(0,0,0);
Vec3 myWindow::camera2= Vec3(0,0,0);
Vec3 myWindow::camera= Vec3(0,0,0);
int myWindow::camflag=0;
int myWindow::lightflag=0;
int myWindow::xangle=0;
int myWindow::yangle=0;
int myWindow::flag=1;
int myWindow::scalefactor=1;
;
#endif // WINDOW_H_

