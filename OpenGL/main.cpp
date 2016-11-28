#include <GL/glut.h>
 
void Display()
{
        glClear( GL_COLOR_BUFFER_BIT );
 
        glBegin( GL_POINTS );
 
        glColor3f( 1, 0, 0 );
        glVertex2f( 0, 0 );
       
        glEnd();
 
        glFlush();
}
 
int main( int argc, char** argv )
{
        glutInit(&argc, argv);
        glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
        glutInitWindowPosition( 200, 200 );
        glutInitWindowSize( 200, 200 );
        glutCreateWindow( "Lesson 1" );
 
        glClearColor( 0, 1, 0, 1 );
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluOrtho2D( -10, 10, -10, 10 );
 
        glutDisplayFunc( Display );
 
        glutMainLoop();
}