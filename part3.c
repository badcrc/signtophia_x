#include <stdio.h>
#include <math.h>


#define M_PI 3.14159265358979f
#define RAND_MAX 2


/* application window title */

char *AppTitle = "Spinning Quark";

/* external OS-dependant functions */

struct htime
{
    unsigned char blob[16];
};



/* global data */

int width, height;

int info;
int frames;
int font;
float fps;
int texture;
float dir[2][3];
float phi[2][3];
float rx[2], ry[2];
float vx[2], vy[2];
struct htime tv;

/* data initialization function */

int gl_data( void )
{
    int i, j;

    srand( time( NULL ) );

    info = 1;

    for( i = 0; i < 2; i++ )
    {
        for( j = 0; j < 3; j++ )
        {
            dir[i][j] = (float) ( 2 * ( rand() % 2 ) - 1 );
            phi[i][j] = 2.0f * M_PI * (float) rand() / RAND_MAX;
        }

        rx[i] = 360.0f * (float) rand() / RAND_MAX;
        ry[i] = 360.0f * (float) rand() / RAND_MAX;

        vx[i] = 20.0f * (float) ( 2 * ( rand() % 2 ) - 1 );
        vy[i] = 20.0f * (float) ( 2 * ( rand() % 2 ) - 1 );
    }

    return( 0 );
}

/* gl initialization function */

int gl_init( void )
{
    int i, j, k;
    double dx, alpha;
    unsigned char *map;
/*
    qobj = gluNewQuadric();
    gluQuadricTexture( qobj, GL_TRUE );
*/
    if( ! ( map = (unsigned char *) malloc( 128 * 128 * 3 ) ) )
    {
      //  perror( "malloc" );
        return( 1 );
    }

    k = 0;

    for( i = 0; i < 128; i++ )
    {

        dx = (double) ( i - 64 ) / 64.0;

        for( j = 0; j < 128; j++ )
        {
            alpha = 0.2f * ( cos( 8 * M_PI * ( dx        ) ) + 1.0f );
            map[k++] = (unsigned char) ( alpha * 255.0 );

            alpha = 0.2f * ( cos( 8 * M_PI * ( dx + 0.05 ) ) + 1.0f );
            map[k++] = (unsigned char) ( alpha * 255.0 );

            alpha = 0.2f * ( cos( 8 * M_PI * ( dx + 0.10 ) ) + 1.0f );
            map[k++] = (unsigned char) ( alpha * 255.0 );
        }
    }
/*
    glTexImage2D( GL_TEXTURE_2D, 0, 3, 128, 128, 0,
                  GL_RGB, GL_UNSIGNED_BYTE, map );
*/
    free( map );
/*
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
*/
    return( 0 );
}

/* window drawing function */

void gl_draw( void )
{
    int i, j;
    float r, g, b;

 //   glClear( GL_COLOR_BUFFER_BIT );

    if( fps )
    {
        for( i = 0; i < 2; i++ )
        {
            for( j = 0; j < 3; j++ )
            {
                if( ! ( rand() % ( (int) ( fps * 8.0f ) ) ) )
                {
                    dir[i][j] = (float) ( rand() % 3 - 1 );
                }
        //      phi[i][j] += dir[i][j] / fps;
            }

         // rx[i] += vx[i] / fps;
        //  ry[i] += vy[i] / fps;
        }
    }

  //  glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0.0f, 0.0f, -16.0f );

 //   glEnable( GL_TEXTURE_2D );

    for( i = 0; i < 2; i++ )

    {
        r = (float) ( ( sin( phi[i][0] ) + 1.0f ) *
                        ( sin( phi[i][0] ) + 1.0f ) ) / 2.0f;

        g = (float) ( ( sin( phi[i][1] ) + 1.0f ) *
                        ( sin( phi[i][1] ) + 1.0f ) ) / 2.0f;

        b = (float) ( ( sin( phi[i][2] ) + 1.0f ) *
                        ( sin( phi[i][2] ) + 1.0f ) ) / 2.0f;

        glColor3f( r, g, b );

        glPushMatrix();
        glRotatef( rx[i], 1.0f, 0.0f, 0.0f );
        glRotatef( ry[i], 0.0f, 1.0f, 0.0f );
   //     gluSphere( qobj, 4.0f, 32, 32 );
        glPopMatrix();
    }

   // glDisable( GL_TEXTURE_2D );

    
    glFinish();

    frames++;
}


