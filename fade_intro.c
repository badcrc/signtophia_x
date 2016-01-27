#include <kos.h>
#include <math.h>
//#include <pcx/pcx.h>

#include <plx/font.h>
#include <plx/sprite.h>
#include <plx/list.h>
#include <plx/dr.h>
#include <plx/context.h>

#include "euskal_demo.h"
#include "firmas_data.h"

extern plx_fcxt_t * cxt;

void ShowDisclaimer() {
    plx_texture_t *logo     = plx_txr_load("/rd/gfx/logo.png",0,0);
    plx_texture_t *crash    = plx_txr_load("/rd/gfx/crash.png",0,0);
    float y,xoffs = ((640 - 512)/2)-70;
    int cnt=0,j=0;
    
    int n=250,i=50;
    
    
 //   printf("\nCargando firma: %d",n); n++;
    
   // PlayOGG("/pc/dcdev/euskal_demo/pruebas/driver.ogg",0);
   PlayOGG("/rd/music/driver.ogg",0);
   printf("\nCargando el sonido...");
    plx_cxt_init();
    plx_cxt_texture(logo);

    for(;n>60;n--,i++) {
        plx_scene_begin();
        plx_list_begin(PVR_LIST_TR_POLY);
        
        plx_txr_send_hdr(logo,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(640,160,320,240,5,n,1,1,1);
        
        //plx_scene_end();
        sndoggvorbis_volume(i);
        cnt++;
        
        }
    timer_spin_sleep(500);
    //vid_screen_shot("/pc/shots/demo1");
    plx_txr_destroy(logo);
            
    plx_cxt_init();
	plx_cxt_texture(crash);
    plx_cxt_culling(PLX_CULL_NONE);
    
    

    
    for(n=0,y = 0.0f;n<250;n++) {
    	
        plx_scene_begin();
      // pvr_list_begin(PVR_LIST_OP_POLY);

		// Submit the context
		plx_cxt_send(PVR_LIST_OP_POLY);
		
        plx_vert_ifp(PLX_VERT, xoffs, y, 1.0f, 0xffffffff, 0.0f, y/480.0f);
		plx_vert_ifp(PLX_VERT, xoffs, 0.0f, 1.0f, 0xffffffff, 0.0f, 0.0f);
		plx_vert_ifp(PLX_VERT, 640.0f-xoffs, y, 1.0f, 0xffffffff, 1.0f, y/480.0f);
		plx_vert_ifp(PLX_VERT_EOS, 640.0f-xoffs, 0.0f, 1.0f, 0xffffffff, 1.0f, 0.0f);
		
		plx_vert_ifp(PLX_VERT, xoffs, 480.0f, 1.0f, 0xffffffff, 0.0f, y/480.0f);
		plx_vert_ifp(PLX_VERT, xoffs, y, 1.0f, 0xffffffff, 0.0f, y/480.0f);
		plx_vert_ifp(PLX_VERT, 640.0f-xoffs, 480.0f, 1.0f, 0xffffffff, 1.0f, y/480.0f);
		plx_vert_ifp(PLX_VERT_EOS, 640.0f-xoffs, y, 1.0f, 0xffffffff, 1.0f, y/480.0f);
		

		
		//pvr_list_begin(PVR_LIST_TR_POLY);
    
        //plx_txr_send_hdr(logo,PVR_LIST_TR_POLY,1);
       // plx_spr_fnp(640,160,320,240,5,n,1,1,1);
        
        //plx_txr_send_hdr(crash,f_LIST_TR_POLY,1);
        //plx_spr_fnp(640,480,320,240,1,n,1,1,1);
        
  
        
        if (y < 480.0f)
			y += 2.3f;
		cnt++;
	//	if(n==125)
	//	   vid_screen_shot("/pc/shots/demo2");
		
	//	printf("\n%d",n);
			
        //plx_scene_end();
      //  sndoggvorbis_volume(i);
        }
        
   
  // vid_screen_shot("/pc/shots/demo3");
    do { 
        MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)
			if (st->buttons & CONT_X) {
			    //vid_screen_shot("/pc/shots/demo_hyper");
			  
                }	    
		MAPLE_FOREACH_END()
		
        cnt++; 
        j=foo(cnt); 
        #ifdef PC50
        timer_spin_sleep(10);
        #endif
        #ifdef PC60
        timer_spin_sleep(14);
        #endif
        #ifdef VGA
        timer_spin_sleep(10);
        #endif
     } while(j!=1);
        

    plx_txr_destroy(crash);
       
    strcpy(data[27].nombre,"/rd/gfx/firmas/30.png");
    strcpy(data[27].autor,"Maeghith");
    data[27].tipo='U';
    data[27].firma = plx_txr_load(data[27].nombre,0,0);
   // printf("\nCargando firma: %d",n); n++;
    
    strcpy(data[28].nombre,"/rd/gfx/firmas/31.png");
    strcpy(data[28].autor,"Bad_CRC");
    data[28].tipo='T';
    data[28].firma = plx_txr_load(data[28].nombre,0,0);
   // printf("\nCargando firma: %d",n); n++;
    
    strcpy(data[29].nombre,"/rd/gfx/firmas/32.png");
    strcpy(data[29].autor,"Hideyoshi");
    data[29].tipo='U';  
    data[29].firma = plx_txr_load(data[29].nombre,0,0); 
   // printf("\nCargando firma: %d",n); n++;
    
    strcpy(data[30].nombre,"/rd/gfx/firmas/33.png");
    strcpy(data[30].autor,"Kujaku");
    data[30].tipo='U';
    data[30].firma = plx_txr_load(data[30].nombre,0,0);
 //   printf("\nCargando firma: %d",n); n++;
    
    strcpy(data[31].nombre,"/rd/gfx/firmas/34.png");
    strcpy(data[31].autor,"Weemoose");
    data[31].tipo='G';
    data[31].firma = plx_txr_load(data[31].nombre,0,0);
    
    
    }
    
int foo(int n) { 
     if(n<1573+MUSIC_TIMER_OFFSET)
          return 0;
     else 
          return 1;

     }


