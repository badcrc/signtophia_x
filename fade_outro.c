#include <kos.h>
#include <math.h>
//#include <pcx/pcx.h>

#include <plx/font.h>
#include <plx/sprite.h>
#include <plx/list.h>
#include <plx/dr.h>
#include <plx/context.h>

#include "euskal_demo.h"

/*ORDEN:
 - fade-in de coded.
 - fade in de music
 - fade in de artwork y rapidamente otro faede in de fl
 - fade out de eso y fae in de fin en japo
 
 TAMAÑOS
coded: 275*50
fin: 415*120
music: 512*60
art: 300*60
fl: 630*50

             tamaño - posicion
 plx_spr_fnp(640,480,320,240,5,0,1,1,1);
*/


extern plx_fcxt_t * cxt;

void DoEndPart() {
    plx_texture_t *coded     = plx_txr_load("/rd/gfx/coded.png",0,0);
    plx_texture_t *fin    = plx_txr_load("/rd/gfx/fin.png",0,0);
    plx_texture_t *music    = plx_txr_load("/rd/gfx/music.png",0,0);
    plx_texture_t *art    = plx_txr_load("/rd/gfx/art.png",0,0);
    plx_texture_t *fl    = plx_txr_load("/rd/gfx/fl.png",0,0);
    /*
    float y,xoffs = ((640 - 512)/2)-70;
    int cnt=0,j=0;
    */
    int m=0,n=250,i=250;
    //pvr_stats_t stats;
    
    //CODED
    plx_cxt_init();
    plx_cxt_texture(coded);
    printf("\nDoing coded...");

    for(n=250,m=0;n>60;n--,i--,m++) {
        plx_scene_begin();
        plx_list_begin(PVR_LIST_TR_POLY);
        
        plx_txr_send_hdr(coded,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(275,50,320,30,5,n,1,1,1);
        
        //plx_scene_end();
        sndoggvorbis_volume(i);
     
        }
        
 //   timer_spin_sleep(500);
    //vid_screen_shot("/pc/shots/demo1");
            
    //MUSIC
    //plx_cxt_init();
    plx_cxt_texture(music);
    printf("\nDoing music...");

    for(n=250,m=0;n>60;n--,i++,m++) {
        plx_scene_begin();
        plx_list_begin(PVR_LIST_TR_POLY);
        
        plx_txr_send_hdr(coded,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(275,50,320,30,5,m,1,1,1);
        plx_txr_send_hdr(music,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(512,60,320,320,5,n,1,1,1);
        m=0;
        //plx_scene_end();
        sndoggvorbis_volume(i);
       
        }
  //  timer_spin_sleep(500);
    
    //ARTWORK
   // plx_cxt_init();
    plx_cxt_texture(art);
    printf("\nDoing artwork...");

    for(n=250,m=0;n>60;n--,i++,m++) {
        plx_scene_begin();
        plx_list_begin(PVR_LIST_TR_POLY);
        
        plx_txr_send_hdr(coded,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(275,50,320,30,5,m,1,1,1);
        plx_txr_send_hdr(music,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(512,60,320,320,5,m,1,1,1);
        plx_txr_send_hdr(art,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(300,60,320,396,5,n,1,1,1);
        m=0;
        //plx_scene_end();
      //  sndoggvorbis_volume(i);
      
        }
    //timer_spin_sleep(500);
    
    //FROZEN LAYER
   // plx_cxt_init();
    plx_cxt_texture(fl);
    printf("\nDoing frozen...");

    for(n=250,m=0;n>60;n--,i++,m++) {
        plx_scene_begin();
        plx_list_begin(PVR_LIST_TR_POLY);
        
        plx_txr_send_hdr(coded,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(275,50,320,30,5,m,1,1,1);
        plx_txr_send_hdr(music,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(512,60,320,320,5,m,1,1,1);
        plx_txr_send_hdr(art,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(300,60,320,396,5,m,1,1,1);
        plx_txr_send_hdr(fl,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(630,50,320,454,5,n,1,1,1);
        m=0;
        //plx_scene_end();
     //   sndoggvorbis_volume(i);
       
        }
  //  timer_spin_sleep(300);
    
    //FIN
   // plx_cxt_init();
    plx_cxt_texture(fin);
    printf("\nDoing end...\n");

    for(n=250,m=0;n>1;n--,i++,m++) {
        plx_scene_begin();
        plx_list_begin(PVR_LIST_TR_POLY);
        
        
        plx_txr_send_hdr(coded,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(275,50,320,30,5,m,1,1,1);
        plx_txr_send_hdr(music,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(512,60,320,320,5,m,1,1,1);
        plx_txr_send_hdr(art,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(300,60,320,396,5,m,1,1,1);
        plx_txr_send_hdr(fl,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(630,50,320,454,5,m,1,1,1);
        plx_txr_send_hdr(fin,PVR_LIST_TR_POLY,1);
        plx_spr_fnp(415,120,320,190,5,n,1,1,1);
        
        //plx_scene_end();
        //sndoggvorbis_volume(i);
        }
    timer_spin_sleep(500);

  // vid_screen_shot("/pc/shots/demo3");


    plx_txr_destroy(fl);
    plx_txr_destroy(fin);
    plx_txr_destroy(coded);
    plx_txr_destroy(music);
    plx_txr_destroy(art);
    
    /*pvr_get_stats(&stats);
	dbglog(DBG_DEBUG, "3D Stats: %ld vblanks, frame rate ~%f fps, max vertex used %d bytes\n",
		stats.vbl_count, (double)stats.frame_rate, stats.vtx_buffer_used_max);
    */
    exit(0);
    
    }


