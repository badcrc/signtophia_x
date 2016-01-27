#include <kos.h>
#include <math.h>
//#include <pcx/pcx.h>

#include <plx/font.h>
#include <plx/sprite.h>
#include <plx/list.h>
#include <plx/dr.h>
#include <plx/context.h>

#include "euskal_demo.h"

#define	MAX_PARTICLES	250

typedef struct	{					// Create A Structure For Particle
	int	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed

	float	r;					// Red Value
	float	g;					// Green Value
	float	b;					// Blue Value

	float	x;					// X Position
	float	y;					// Y Position
	float	z;					// Z Position

	float	xi;					// X Direction
	float	yi;					// Y Direction
	float	zi;					// Z Direction

	float	xg;					// X Gravity
	float	yg;					// Y Gravity
	float	zg;					// Z Gravity
    } particles;						// Particles Structure



int rainbow=1;	

float	slowdown=0.1f;			// Slow Down Particles
float	xspeed;				// Base X Speed (To Allow Keyboard Direction Of Tail)
float	yspeed;				// Base Y Speed (To Allow Keyboard Direction Of Tail)
float	zoom=-40.0f;			// Used To Zoom Out

int	loop;				// Misc Loop Variable
int	col;				// Current Color Selection
int	delay;				// Rainbow Effect Delay
int	texture[1];			// Storage For Our Particle Texture
plx_texture_t *tex;// = plx_txr_load("/rd/gfx/particle.png",0,0);

particles particle[MAX_PARTICLES];

static float colors[12][3]=				// Rainbow Of Colors
{
	{1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
	{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
	{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

int init_particle() {
    int loop;
    
    for (loop=0;loop<MAX_PARTICLES;loop++)					// Initials All The Textures
	{
		particle[loop].active=1;					// Make All The Particles Active
		particle[loop].life=1.0f;	
		particle[loop].fade=(float)(rand()%100)/1000.0f+0.003f;	
		particle[loop].r=colors[loop*(12/MAX_PARTICLES)][0];		// Select Red Rainbow Color
		particle[loop].g=colors[loop*(12/MAX_PARTICLES)][1];		// Select Red Rainbow Color
		particle[loop].b=colors[loop*(12/MAX_PARTICLES)][2];		// Select Red Rainbow Color
     	particle[loop].xi=(float)((rand()%50)-26.0f)*10.0f;		// Random Speed On X Axis
		particle[loop].yi=(float)((rand()%50)-25.0f)*10.0f;		// Random Speed On Y Axis
		particle[loop].zi=(float)((rand()%50)-25.0f)*10.0f;		// Random Speed On Z Axis
        particle[loop].xg=0.0f;						// Set Horizontal Pull To Zero
		particle[loop].yg=-0.8f;					// Set Vertical Pull Downward
		particle[loop].zg=0.0f;						// Set Pull On Z Axis To Zero
	}
	
	return 0;
}


void ParticlePart(int crtl) {
    tex= plx_txr_load("/rd/gfx/particle.png",1,0);
    
    init_particle();
   // float theta = 0;
    int done, loop, cnt=0;
    uint32 color;  
    plx_dr_state_t dr;
	float x,y,z;


	
    // Setup the context

	
	//pvr_set_bg_color(0.0f,0.0f,0.0f);
	
	// Init 3D stuff. mat3d is like KGL.
	//plx_mat3d_init();
	plx_mat3d_mode(PLX_MAT_PROJECTION);
	plx_mat3d_identity();
	plx_mat3d_perspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);
	plx_mat3d_mode(PLX_MAT_MODELVIEW);
	
	    
    for (done = 0; !done;) {
		// Check for start
		MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)
			if (st->buttons & CONT_START)
				done = 1;
			if (st->buttons & CONT_X) {
			    printf("\nTime: %d",cnt);
			   /* vid_screen_shot("/pc/shots/demo_part_f");*/ }
		MAPLE_FOREACH_END()
		if(col<12)
          col++;
        else
          col=0;
    	// Setup the frame
    	
		plx_cxt_texture(tex);
    		
		//pvr_wait_ready();
		//pvr_scene_begin();
		//pvr_list_begin(PLX_LIST_TR_POLY);

		// Submit the context
		plx_cxt_send(PLX_LIST_TR_POLY);
		
	   // plx_fcxt_setcolor4f(cxt,particle[loop].life,particle[loop].r, particle[loop].g, particle[loop].r);
        //PrintString("Driver's High - L'Arc-en-Ciel",80.0f,22.0,30.0f);
		
		
		plx_mat3d_identity();
		
		for (loop=0;loop<MAX_PARTICLES;loop++)	{				// Loop Through All The Particl
		  if (particle[loop].active) {					// If The Particle Is Active
				  x=particle[loop].x;				// Grab Our Particle X Position
			      y=particle[loop].y;				// Grab Our Particle Y Position
			      z=particle[loop].z+zoom;				// Particle Z Pos + Zoom
			      
			      //printf("\nR: %f - G: %f - B: %f",particle[loop].r,particle[loop].g,particle[loop].b);
			      color = plx_pack_color(particle[loop].life,particle[loop].r,particle[loop].g,particle[loop].b);
                 // printf("\nColor: %d",color); //0xff0a0a0a;
                  	
                  	
                  	plx_mat3d_identity();
                    plx_mat3d_translate(x, y, z);
                  	
                  	 plx_mat_identity();
                  	 plx_mat3d_apply(PLX_MAT_SCREENVIEW);
                  	 plx_mat3d_apply(PLX_MAT_PROJECTION);
                  	 plx_mat3d_apply(PLX_MAT_MODELVIEW);
	
                   	 plx_dr_init(&dr);
                  	plx_cxt_init();
                  
                  	plx_cxt_culling(PLX_CULL_NONE);
                   plx_txr_send_hdr(tex,PLX_LIST_TR_POLY,1);
                 
                  plx_spr_fnp(32,32,320.0+particle[loop].x,240.0+particle[loop].y,particle[loop].z,particle[loop].life,particle[loop].r,particle[loop].g,particle[loop].b);
                  /*
                  plx_vert_indm3(&dr, PLX_VERT,-0.5,0.5,-0.5,color);
	              plx_vert_indm3(&dr, PLX_VERT,-0.5,-0.5,-0.5, color);
	              plx_vert_indm3(&dr, PLX_VERT,0.5,0.5,-0.5, color);
	              plx_vert_indm3(&dr, PLX_VERT_EOS,0.5,-0.5,-0.5, color);
	                
	                    */
                 
                 
	              particle[loop].x+=particle[loop].xi/(slowdown*250);	// Move On The X Axis By X Speed
		          particle[loop].y+=particle[loop].yi/(slowdown*250);	// Move On The Y Axis By Y Speed
			      particle[loop].z+=particle[loop].zi/(slowdown*250);	// Move On The Z Axis By Z Speed
			      
			      particle[loop].xi+=particle[loop].xg;			// Take Pull On X Axis Into Account
			      particle[loop].yi+=particle[loop].yg;			// Take Pull On Y Axis Into Account
			      particle[loop].zi+=particle[loop].zg;			// Take Pull On Z Axis Into Account
			      
			      particle[loop].life-=particle[loop].fade;		// Reduce Particles Life By 'Fade'

			      if (particle[loop].life<0.0f)	{				// If Particle Is Burned Out
						      particle[loop].life=1.0f;				// Give It New Life
				              particle[loop].fade=(float)(rand()%100)/1000.0f+0.003f;	// Random Fade Value
				              
				              particle[loop].x=0.0f;					// Center On X Axis
				              particle[loop].y=0.0f;					// Center On Y Axis
				              particle[loop].z=0.0f;					// Center On Z Axis
				              
				              particle[loop].xi=xspeed+(float)((rand()%60)-32.0f);	// X Axis Speed And Direction
				              particle[loop].yi=yspeed+(float)((rand()%60)-30.0f);	// Y Axis Speed And Direction
				              particle[loop].zi=(float)((rand()%60)-30.0f);		// Z Axis Speed And Direction

				              particle[loop].r=colors[col][0];			// Select Red From Color Table
				              particle[loop].g=colors[col][1];			// Select Green From Color Table
				              particle[loop].b=colors[col][2];			// Select Blue From Color Table
				              }
				    #ifdef PC50            
                    if ((cnt>402+(MUSIC_TIMER_OFFSET) && cnt <405+(MUSIC_TIMER_OFFSET)) || (cnt>467+(MUSIC_TIMER_OFFSET) && cnt<469+(MUSIC_TIMER_OFFSET)) ||
                        (cnt>528+(MUSIC_TIMER_OFFSET) && cnt <530+(MUSIC_TIMER_OFFSET)) || (cnt>594+(MUSIC_TIMER_OFFSET) && cnt<596+(MUSIC_TIMER_OFFSET)) ||
                        (cnt>649+(MUSIC_TIMER_OFFSET) && cnt <651+(MUSIC_TIMER_OFFSET)) || (cnt>712+(MUSIC_TIMER_OFFSET) && cnt<714+(MUSIC_TIMER_OFFSET)) || 
                        (cnt>778+(MUSIC_TIMER_OFFSET) && cnt <780+(MUSIC_TIMER_OFFSET))) {
                          particle[loop].x=0.0f;					// Center On X Axis
				          particle[loop].y=0.0f;					// Center On Y Axis
				          particle[loop].z=0.0f;					// Center On Z Axis
				          particle[loop].xi=(float)((rand()%50)-26.0f)*10.0f;	// Random Speed On X Axis
				          particle[loop].yi=(float)((rand()%50)-25.0f)*10.0f;	// Random Speed On Y Axis
				          particle[loop].zi=(float)((rand()%50)-25.0f)*10.0f;	// Random Speed On Z Axis
				          }
                     #endif 
                     
				     #ifdef VGA     
                     if ((cnt>402+(MUSIC_TIMER_OFFSET) && cnt <405+(MUSIC_TIMER_OFFSET)) || (cnt>467+(MUSIC_TIMER_OFFSET) && cnt<469+(MUSIC_TIMER_OFFSET)) ||
                        (cnt>528+(MUSIC_TIMER_OFFSET) && cnt <530+(MUSIC_TIMER_OFFSET)) || (cnt>594+(MUSIC_TIMER_OFFSET) && cnt<596+(MUSIC_TIMER_OFFSET)) ||
                        (cnt>649+(MUSIC_TIMER_OFFSET) && cnt <651+(MUSIC_TIMER_OFFSET)) || (cnt>712+(MUSIC_TIMER_OFFSET) && cnt<714+(MUSIC_TIMER_OFFSET)) || 
                        (cnt>778+(MUSIC_TIMER_OFFSET) && cnt <780+(MUSIC_TIMER_OFFSET))) {
                          particle[loop].x=0.0f;					// Center On X Axis
				          particle[loop].y=0.0f;					// Center On Y Axis
				          particle[loop].z=0.0f;					// Center On Z Axis
				          particle[loop].xi=(float)((rand()%50)-26.0f)*10.0f;	// Random Speed On X Axis
				          particle[loop].yi=(float)((rand()%50)-25.0f)*10.0f;	// Random Speed On Y Axis
				          particle[loop].zi=(float)((rand()%50)-25.0f)*10.0f;	// Random Speed On Z Axis
				          }
                      #endif
                   }
                   
             }
            // stars_one_frame();
             //do_sign_frame();
         //pvr_scene_finish();
             cnt++;
             if(cnt>846+MUSIC_TIMER_OFFSET)
               return;

        }
    }
