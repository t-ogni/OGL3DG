#include <GL/gl.h>
#include <GL/glut.h>

void display(void)
{
/* стираем */
    glClear (GL_COLOR_BUFFER_BIT);

/* рисуем белый прямоугольник
* (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
*/
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f (0.25, 0.25, 0.0);
    glVertex3f (0.75, 0.25, 0.0);
    glVertex3f (0.75, 0.75, 0.0);
    glVertex3f (0.25, 0.75, 0.0);
    glEnd();

/* поехали ! */
    glFlush ();
}

void init (void)
{
/* установим черный фон */
    glClearColor (0.0, 0.0, 0.0, 0.0);

/* инициализация viewing values */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

/*
Определим параметры окна , display mode
* (single buffer and RGBA). Откроем окно с фразой "hello"
* в title bar.
*/
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (250, 250);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("hello");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0; /* ISO C requires main to return int. */
}