#include <kos.h>
#include <math.h>
//#include <pcx/pcx.h>

#include <plx/font.h>
#include <plx/sprite.h>
#include <plx/list.h>
#include <plx/dr.h>
#include <plx/context.h>

#include "euskal_demo.h"

#define RAND_MAX 1000


int width, height;

int info, bmode, rdown, frames, font;
float alpha, rx, ry, vx, vy;
float dir[8][3];
float phi[8][3];

float pos_x_c = 0;
float pos_x_d = 0;

float pos_x2_c = 0;
float pos_x2_d = 0;

int init_data( void )
{
    int i, j;

    

    info  = 1;
    bmode = 1;
    rdown = 0;

    alpha = 0.11f;

    rx =  0.0f; ry =  0.0f;
    vx = 10.0f; vy = 48.0f;

    for( i = 0; i < 8; i++ )
    {
        for( j = 0; j < 3; j++ )
        {
            dir[i][j] = (float) ( rand() % 3 ) - 1;
            phi[i][j] = 2.0f * M_PI * (float) rand() / RAND_MAX;
        }
    }

    return( 0 );
}

void MultiCubePart(int crtl, int volta) {
    init_data();
    
    int i;
    float len, lmax, r[8], g[8], b[8], a;
    int done;
    int theta;
    plx_dr_state_t dr;
    int cnt=0;
   // pvr_set_bg_color(0.0f, 0.0f, 0.0f);
	
	//plx_dr_init(&dr);


    for( i = 0; i < 8; i++ ) {
        r[i] = ( (float) sin( phi[i][0] ) + 1.0f ) / 2.0f;
        g[i] = ( (float) sin( phi[i][1] ) + 1.0f ) / 2.0f;
        b[i] = ( (float) sin( phi[i][2] ) + 1.0f ) / 2.0f;
        }
        
    for (done = 0; !done;) {
        // Check for start
		MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)
			if (st->buttons & CONT_START)
				done = 1;
			if (st->buttons & CONT_X) {
			   // vid_screen_shot("/pc/shots/demo_hyper");
			    //printf("\nTime: %d",cnt);
                }	    
		MAPLE_FOREACH_END()


	
        // Init 3D stuff. mat3d is like KGL.
       // plx_mat3d_init();
        plx_mat3d_mode(PLX_MAT_PROJECTION);
        plx_mat3d_identity();
        plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
        plx_mat3d_mode(PLX_MAT_MODELVIEW);
       // pvr_wait_ready();
		//pvr_scene_begin();
		//pvr_list_begin(PVR_LIST_TR_POLY);
	

		// Submit the context
		plx_cxt_send(PVR_LIST_TR_POLY);
	
	    
        plx_mat3d_translate( 0.0f, 0.0f, -8.0f );
        plx_mat3d_rotate( rx, 1.0f, 0.0f, 0.0f );
        plx_mat3d_rotate( ry, 0.0f, 1.0f, 0.0f );
        plx_mat3d_translate( 0.3f, 0.0f, -2.0f );
        plx_mat3d_rotate( rx, 1.0f, 0.0f, 0.0f );
        plx_mat3d_rotate( ry, 0.0f, 1.0f, 0.0f );
       //plx_mat3d_identity();
	
        a = alpha;

        lmax = 1.4f + 0.12f * bmode;
        


        for( len = lmax; len > 0.0f; len -= 0.12f ) {
        
        
                plx_mat_identity();
		        plx_mat3d_apply(PLX_MAT_SCREENVIEW);
		        plx_mat3d_apply(PLX_MAT_PROJECTION);
		        plx_mat3d_apply(PLX_MAT_MODELVIEW);
		        
		        plx_dr_init(&dr);
                plx_cxt_init();
                plx_cxt_texture(NULL);
               	plx_cxt_culling(PLX_CULL_NONE);
                  	
                plx_vert_indm3(&dr, PLX_VERT, -len, -len, -len,plx_pack_color(a,r[0], g[0], b[0]));
                plx_vert_indm3(&dr, PLX_VERT, -len,  len, -len,plx_pack_color(a,r[1], g[1], b[1]));
                plx_vert_indm3(&dr, PLX_VERT, -len, -len,  len,plx_pack_color(a,r[2], g[2], b[2]));
                plx_vert_indm3(&dr, PLX_VERT_EOS, -len,  len,  len,plx_pack_color(a,r[3], g[3], b[3]));
      
                plx_vert_indm3(&dr, PLX_VERT, len, -len, -len,plx_pack_color(a,r[4], g[5], b[6]));
                plx_vert_indm3(&dr, PLX_VERT, len,  len, -len,plx_pack_color(a,r[5], g[5], b[6]));
                plx_vert_indm3(&dr, PLX_VERT, len, -len,  len,plx_pack_color(a,r[6], g[5], b[6]));
                plx_vert_indm3(&dr, PLX_VERT_EOS, len,  len,  len,plx_pack_color(a,r[7], g[7], b[7]));
     
                plx_vert_indm3(&dr, PLX_VERT, -len,  len, -len,plx_pack_color(a,r[0], g[0], b[0]));
                plx_vert_indm3(&dr, PLX_VERT, -len, -len, -len,plx_pack_color(a,r[1], g[1], b[1]));
                plx_vert_indm3(&dr, PLX_VERT,  len,  len, -len,plx_pack_color(a,r[5], g[5], b[5]));
                plx_vert_indm3(&dr, PLX_VERT_EOS,  len, -len, -len,plx_pack_color(a,r[4], g[4], b[4]));
        
                plx_vert_indm3(&dr, PLX_VERT, -len,  len, len,plx_pack_color(a,r[3], g[3], b[3]));
                plx_vert_indm3(&dr, PLX_VERT, -len, -len, len,plx_pack_color(a,r[2], g[2], b[2]));
                plx_vert_indm3(&dr, PLX_VERT,  len,  len, len,plx_pack_color(a,r[6], g[6], b[6]));
                plx_vert_indm3(&dr, PLX_VERT_EOS,  len, -len, len,plx_pack_color(a,r[7], g[7], b[7]));
     
                plx_vert_indm3(&dr, PLX_VERT, -len, -len, -len,plx_pack_color(a,r[0], g[0], b[0]));
                plx_vert_indm3(&dr, PLX_VERT, -len, -len,  len,plx_pack_color(a,r[3], g[3], b[3]));
                plx_vert_indm3(&dr, PLX_VERT,  len, -len, -len,plx_pack_color(a,r[7], g[7], b[7]));
                plx_vert_indm3(&dr, PLX_VERT_EOS,  len, -len,  len,plx_pack_color(a,r[4], g[4], b[4]));
    
                plx_vert_indm3(&dr, PLX_VERT, -len, len, -len,plx_pack_color(a,r[1], g[1], b[1]));
                plx_vert_indm3(&dr, PLX_VERT, -len, len,  len,plx_pack_color(a,r[2], g[2], b[2]));
                plx_vert_indm3(&dr, PLX_VERT,  len, len, -len,plx_pack_color(a,r[6], g[6], b[6]));
                plx_vert_indm3(&dr, PLX_VERT_EOS,  len, len,  len,plx_pack_color(a,r[5], g[5], b[5]));
                
                }
                switch(volta) {
                          case 1:
                              if(pos_x_c<0.0) scroll_two();
                              scroll_one();
                              break;
                          
                          case 2:
                             if(pos_x2_c<0.0) scroll_four();
                             scroll_three();
                            // printf("\nDOS");
                             break;  
                          }
              //  stars_one_frame();
               //do_sign_frame();
	 
       //pvr_scene_finish();
       rx+=5; ry+=5; theta++; cnt++;
       
       if(cnt>1600+MUSIC_TIMER_OFFSET && cnt<1602+MUSIC_TIMER_OFFSET || crtl==10)
         return;
       }
    }
    

extern plx_fcxt_t * cxt;

void scroll_one() {
   // pos_y_c-=2.0f;
   plx_fcxt_setcolor4f(cxt,0.5f,0.0f, 1.0f, 0.0f);
   plx_fcxt_setsize(cxt,20.0f);
    PrintString("Demo echa con KOS para el Euskal Encounter '04",640.0f+pos_x_c,30.0f,5.0f);
    pos_x_c-=1.0f;
  //  pos_y_c+=2.0f;

    }

void scroll_two() {
   // pos_y_c-=2.0f;
   plx_fcxt_setcolor4f(cxt,0.5f,0.0f, 1.0f, 0.0f);
   plx_fcxt_setsize(cxt,20.0f);
    PrintString("Se hizo usando las firmas de los miembros del foro de Frozen-Layer",640.0f+pos_x_d,60.0f,5.0f);
    pos_x_d-=1.5f;
  //  pos_y_c+=2.0f;

    }
    
void scroll_three() {
   // pos_y_c-=2.0f;
   plx_fcxt_setcolor4f(cxt,0.5f,1.0f, 0.0f, 0.0f);plx_fcxt_setsize(cxt,20.0f);
   
    PrintString("www.frozen-layer.net",640.0f+pos_x2_c,30.0f,5.0f);
    pos_x2_c-=1.0f;
  //  pos_y_c+=2.0f;

    }
    
void scroll_four() {
   // pos_y_c-=2.0f;
   plx_fcxt_setcolor4f(cxt,0.5f,2.0f, 0.0f, 0.0f);plx_fcxt_setsize(cxt,20.0f);
    PrintString("La cancion que suena es el primer opening de la serie \"Great Teacher Onizuka\"",640.0f+pos_x2_d,60.0f,5.0f);
    pos_x2_d-=1.5f;
  //  pos_y_c+=2.0f;

    }
