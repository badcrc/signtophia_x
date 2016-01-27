#include <kos.h>
#include <math.h>
//#include <pcx/pcx.h>

#include <plx/font.h>
#include <plx/sprite.h>
#include <plx/list.h>
#include <plx/dr.h>
#include <plx/context.h>

#include "euskal_demo.h"

//#define CUBE_ALPHA 130

typedef struct {
    float x;
    float y;
    float z;
    } cube;

float CUBE_ALPHA = 0;

float tb=240.0;
float rf=0.0f, gf=0.0f,bf=0.0f;
void drawwave(int theta, int time) {
	uint32 color = 0xffa0a0a0;
	int i, divs = 320;
	float x, y, t;
	plx_dr_state_t dr;
	if(tb>0.0)
        tb-=2.8;	
    if(rf<0.9) {
       rf+=0.015;  gf+=0.015;  bf+=0.015; 
        //pvr_set_bg_color(0+rf,0+gf,0+bf);
        }
    if(time+MUSIC_TIMER_OFFSET>2100 && time+MUSIC_TIMER_OFFSET<2223 ) {
        tb-=2.8;
         rf+=0.015;  gf+=0.015;  bf+=0.015; 
       // pvr_set_bg_color(0+rf,0+gf,0+bf);
        color = plx_pack_color(1,254,254,254); 
        if(time<2223) {
                 tb=240.0; rf=0.0f, gf=0.0f,bf=0.0f;
                 }
        }

	plx_dr_init(&dr);

	// Convert to radians for sin/cos
	t = theta * 2*M_PI / 360.0f;

	for (i=0; i<=divs; i++) {
		x = i*640.0f/divs;
	 
		// These are more or less magic numbers I played with until
		// it looked neat.
		y = tb+260.0f + fsin(t + i*M_PI/64.0f)*30.0f*fsin(t*4);
  		y += fcos(t + i*M_PI/36.0f)*40.0f*fcos(t*6);
		y += fcos(t + i*M_PI/32.0f)*24.0f*fcos(t*8);

		plx_vert_ind(&dr, PLX_VERT, x, y, 0.0001f, color);
		plx_vert_ind(&dr, i == divs ? PLX_VERT_EOS : PLX_VERT, x, 480.0f, 0.0001f, color);
	}
}
plx_texture_t *tex;
static float tz;

void cubeInit() {
	tex= plx_txr_load("/rd/gfx/text_wire.png",1,0);
	tz = -300.0f;

}


#define vert_ifdm3(st, flg, x, y, z, color, u, v) do { \
	float tx = x, ty = y, tz = z; \
	plx_mat_tfip_3d(tx, ty, tz); \
	if (tz <= 0.0f) { \
		tx = lx; ty = ly; tz = lz; \
	} else { \
		lx = tx; ly = ty; lz = tz; \
	} \
	plx_vert_ifd(st, flg, tx, ty, tz, color, u, v); \
} while (0)

static inline float tabs_a(float a) { return a < 0.0f ? -a : a; }

void BuildCube(int r, int g,int b, int a) {
     float lx = -50.0f, ly = -50.0f, lz = -50.0f;
	
	if (tabs_a( -12.0f - tz ) > 0.1f) {
		tz += ((-12.0f) - tz) / 64.0f;
	} else {
		tz = -12.0f;
	}
    
	uint32 color = plx_pack_color(a,r,g,b); //0xffff00a0;
	
	plx_dr_state_t dr;
	
	
	//plx_cxt_init();
	plx_cxt_texture(tex);
    plx_cxt_culling(PLX_CULL_NONE);
    
    plx_cxt_send(PLX_LIST_TR_POLY);
    plx_mat3d_apply_all();
    
    plx_dr_init(&dr);

    /* Front Face */
	vert_ifdm3(&dr, PLX_VERT,      3.0f, -3.0f,  3.0f, color, 1.0f, 1.0f);
	vert_ifdm3(&dr, PLX_VERT,     -3.0f, -3.0f,  3.0f, color, 0.0f, 1.0f);
	vert_ifdm3(&dr, PLX_VERT,      3.0f,  3.0f,  3.0f, color, 1.0f, 0.0f);
	vert_ifdm3(&dr, PLX_VERT_EOS, -3.0f,  3.0f,  3.0f, color, 0.0f, 0.0f);

	/* Back Face */
	vert_ifdm3(&dr, PLX_VERT,     -3.0f,  3.0f, -3.0f, color, 1.0f, 0.0f);
	vert_ifdm3(&dr, PLX_VERT,     -3.0f, -3.0f, -3.0f, color, 1.0f, 1.0f);
	vert_ifdm3(&dr, PLX_VERT,      3.0f,  3.0f, -3.0f, color, 0.0f, 0.0f);
	vert_ifdm3(&dr, PLX_VERT_EOS,  3.0f, -3.0f, -3.0f, color, 0.0f, 1.0f);

	/* Top Face */
	vert_ifdm3(&dr, PLX_VERT,     -3.0f,  3.0f,  3.0f, color, 0.0f, 1.0f);
	vert_ifdm3(&dr, PLX_VERT,     -3.0f,  3.0f, -3.0f, color, 0.0f, 0.0f);
	vert_ifdm3(&dr, PLX_VERT,      3.0f,  3.0f,  3.0f, color, 1.0f, 1.0f);
	vert_ifdm3(&dr, PLX_VERT_EOS,  3.0f,  3.0f, -3.0f, color, 1.0f, 0.0f);

	/* Bottom Face */
	vert_ifdm3(&dr, PLX_VERT,      3.0f, -3.0f, -3.0f, color, 0.0f, 0.0f);
	vert_ifdm3(&dr, PLX_VERT,     -3.0f, -3.0f, -3.0f, color, 1.0f, 0.0f);
	vert_ifdm3(&dr, PLX_VERT,      3.0f, -3.0f,  3.0f, color, 0.0f, 1.0f);
	vert_ifdm3(&dr, PLX_VERT_EOS, -3.0f, -3.0f,  3.0f, color, 1.0f, 1.0f);

	/* Right face */
	vert_ifdm3(&dr, PLX_VERT,      3.0f,  3.0f, -3.0f, color, 1.0f, 0.0f);
	vert_ifdm3(&dr, PLX_VERT,      3.0f, -3.0f, -3.0f, color, 1.0f, 1.0f);
	vert_ifdm3(&dr, PLX_VERT,      3.0f,  3.0f,  3.0f, color, 0.0f, 0.0f);
	vert_ifdm3(&dr, PLX_VERT_EOS,  3.0f, -3.0f,  3.0f, color, 0.0f, 1.0f);

	/* Left Face */
	vert_ifdm3(&dr, PLX_VERT,     -3.0f, -3.0f,  3.0f, color, 1.0f, 1.0f);
	vert_ifdm3(&dr, PLX_VERT,     -3.0f, -3.0f, -3.0f, color, 0.0f, 1.0f);
	vert_ifdm3(&dr, PLX_VERT,     -3.0f,  3.0f,  3.0f, color, 1.0f, 0.0f);
	vert_ifdm3(&dr, PLX_VERT_EOS, -3.0f,  3.0f, -3.0f, color, 0.0f, 0.0f);

}

void CubePart(int crtl) {
    int done;
	int theta,thetac,thetab;
	int r=0,g=0,b=0;
	int r1=0,g1=0,b1=0;
	//int r2=0,g2=0,b2=0;
    int s=0,t=0;    
    float time=0;

    
    //pvr_set_bg_color(1.0f,1.0f,1.0f);

    /*r=255; g=255; b=255*/ s=0;  
    cubeInit();
   	// Setup the context
	plx_cxt_init();
	
	plx_cxt_culling(PLX_CULL_NONE);
	
	// Init 3D stuff. mat3d is like KGL.
//	plx_mat3d_init();
	plx_mat3d_mode(PLX_MAT_PROJECTION);
	plx_mat3d_identity();
	plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	plx_mat3d_mode(PLX_MAT_MODELVIEW);
	
    for (done = 0,thetac = 0, theta = 0, thetab = 0; !done;) {
		// Check for start
		MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)
			if (st->buttons & CONT_START)
				done = 1;
			//if (st->buttons & CONT_X) 
			   // printf("\nTime: %f",time);    
		        /*vid_screen_shot("/pc/shots/demo_cube_f");*/
				
		MAPLE_FOREACH_END()
  
        if(CUBE_ALPHA<130)
	        CUBE_ALPHA+=0.05f;
     
    	// Setup the frame
		//pvr_wait_ready();
		//pvr_scene_begin();
		//pvr_list_begin(PVR_LIST_TR_POLY);
	


        /****************CUBO1****************/
        plx_mat3d_identity();
		plx_mat3d_translate(0.0f, 0.0f, -30.0f);
		plx_mat3d_rotate(theta*0.3f, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(theta*1.5f, 0.0f, 1.0f, 0.0f);
		plx_mat3d_translate(10.0f, 0.0f, 0.1f);
		plx_mat3d_rotate(theta, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(theta*0.5f, 0.0f, 0.1f, 0.0f);
		plx_mat3d_rotate(theta*0.3f, 0.0f, 0.0f, 0.1f);
          
        plx_mat_identity();
		plx_mat3d_apply(PLX_MAT_SCREENVIEW);
		plx_mat3d_apply(PLX_MAT_PROJECTION);
		plx_mat3d_apply(PLX_MAT_MODELVIEW);
	
		
        BuildCube(!r^g,g|b,b&r,CUBE_ALPHA);
       //BuildCube(r,g,b,CUBE_ALPHA);
        
        /****************CUBO2****************/
        plx_mat3d_identity();
		plx_mat3d_translate(0.0f, 0.0f, -30.0f);
		plx_mat3d_rotate(theta*0.3f, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(theta*1.5f, 0.0f, 1.0f, 0.0f);
		plx_mat3d_translate(-10.0f, 0.0f, 0.1f);
		plx_mat3d_rotate(theta, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(theta*0.5f, 0.0f, 0.1f, 0.0f);
		plx_mat3d_rotate(theta*0.3f, 0.0f, 0.0f, 0.1f);
		       
        plx_mat_identity();
		plx_mat3d_apply(PLX_MAT_SCREENVIEW);
		plx_mat3d_apply(PLX_MAT_PROJECTION);
		plx_mat3d_apply(PLX_MAT_MODELVIEW);
        
        BuildCube(!r1^g1,!g1|b1,!b1&r1,CUBE_ALPHA);
        //BuildCube(r,g,b,CUBE_ALPHA);
        /****************CUBO3 CENTRAL****************/
        plx_mat3d_identity();
		plx_mat3d_translate(0.0f, 0.0f, -30.0f);
		plx_mat3d_rotate(thetab*0.3f, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(thetab*1.5f, 0.0f, 1.0f, 0.0f);
		plx_mat3d_translate(-2.0f, 1.0f, 0.0f);
		plx_mat3d_rotate(thetab, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(thetab*0.5f, 0.0f, 0.1f, 0.0f);
		plx_mat3d_rotate(thetab+1*0.3f, 0.1f, 0.0f, 0.1f);
        
        plx_mat_identity();
		plx_mat3d_apply(PLX_MAT_SCREENVIEW);
		plx_mat3d_apply(PLX_MAT_PROJECTION);
		plx_mat3d_apply(PLX_MAT_MODELVIEW);
	
		
        BuildCube(!r+r,g|g,!b^b,100);
        
        
        plx_mat3d_identity();
		plx_mat3d_translate(0.0f, 0.0f, -30.0f);
		plx_mat3d_rotate(theta*0.3f, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(theta*1.5f, 0.0f, 1.0f, 0.0f);
		plx_mat3d_translate(-2.0f, 1.0f, 0.0f);
		plx_mat3d_rotate(theta, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(theta*0.5f, 0.0f, 0.1f, 0.0f);
		plx_mat3d_rotate(theta+1*0.3f, 0.1f, 0.0f, 0.1f);
        
        plx_mat_identity();
		plx_mat3d_apply(PLX_MAT_SCREENVIEW);
		plx_mat3d_apply(PLX_MAT_PROJECTION);
		plx_mat3d_apply(PLX_MAT_MODELVIEW);
	
		
        BuildCube(!r+r,g|g,!b^b,CUBE_ALPHA);
        //BuildCube(r,g,b,CUBE_ALPHA);
        /*********************************************/
        
        /****************CUBO1****************/
        plx_mat3d_identity();
		plx_mat3d_translate(0.0f, 0.0f, -30.0f);
		plx_mat3d_rotate(theta*0.3f, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(theta*1.5f, 0.0f, 1.0f, 0.0f);
		plx_mat3d_translate(10.0f,10.0f, 0.1f);
		plx_mat3d_rotate(theta, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(theta*0.5f, 0.0f, 0.1f, 0.0f);
		plx_mat3d_rotate(theta*0.3f, 0.0f, 0.0f, 0.1f);
          
        plx_mat_identity();
		plx_mat3d_apply(PLX_MAT_SCREENVIEW);
		plx_mat3d_apply(PLX_MAT_PROJECTION);
		plx_mat3d_apply(PLX_MAT_MODELVIEW);
	
		
        BuildCube(!r^g,g|b,b&r,CUBE_ALPHA);
        //BuildCube(r,g,b,CUBE_ALPHA);
        /****************CUBO1****************/
        plx_mat3d_identity();
		plx_mat3d_translate(0.0f, 0.0f, -30.0f);
		plx_mat3d_rotate(theta*0.3f, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(theta*1.5f, 0.0f, 1.0f, 0.0f);
		plx_mat3d_translate(-10.0f, -10.0f, 0.1f);
		plx_mat3d_rotate(theta, 1.0f, 0.0f, 0.0f);
		plx_mat3d_rotate(theta*0.5f, 0.0f, 0.1f, 0.0f);
		plx_mat3d_rotate(theta*0.3f, 0.0f, 0.0f, 0.1f);
       
        plx_mat_identity();
		plx_mat3d_apply(PLX_MAT_SCREENVIEW);
		plx_mat3d_apply(PLX_MAT_PROJECTION);
		plx_mat3d_apply(PLX_MAT_MODELVIEW);
	
		
       BuildCube(!r1^g1,!g1|b1,!b1&r1,CUBE_ALPHA);
        //BuildCube(r,g,b,CUBE_ALPHA);
        /*************************************************/
       // drawwave(thetac,time);
       // stars_one_frame();
       // do_sign_frame();
        //pvr_scene_finish();
               /*
        if(s==0) 
        { r--; g--; b--; }
        if(s==1)
        { r++; g++; b++; }
        
        if(s==1) 
        { r1--; g1--; b1--; }
        if(s==0)
        { r1++; g1++; b1++; }
        
        if(s==0) 
        { r2--; g2--; b2--; }
        if(s==1)
        { r2--; g2++; b2++; }
        
        */
    
        //printf("%d ",r);
        if(time+MUSIC_TIMER_OFFSET>2100 && time+MUSIC_TIMER_OFFSET<2223 ) {
                if(r>255) s=1; if(g>255) s=1; if(b>255) s=1; 
                }
        else {
                if(r>255) s=0; if(g>255) s=0; if(b>255) s=0; 
                if(r<2)   s=1; if(g<2)   s=1; if(b<2)   s=1; 
             }
		

		// Move our counters
		thetab=theta;
		theta+=5;
		thetac+=5;
		t++;
		time++;
		
		if(time+MUSIC_TIMER_OFFSET>2220 && time+MUSIC_TIMER_OFFSET < 2222)
		  //printf("\nSALTO DE ESCENA");
		  return;
		/*
		if(t==650) {
            vid_screen_shot("/pc/shots/demo5");
            done=1;
            }
        else if(t==268)
            vid_screen_shot("/pc/shots/demo4");*/
         
        }
       	plx_txr_destroy(tex);
  }
    

