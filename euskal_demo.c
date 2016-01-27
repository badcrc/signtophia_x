/* KallistiOS ##version##

   rotocube.c
   Copyright (C)2003 Dan Potter
*/

#include <kos.h>
#include <math.h>
#include <plx/font.h>
#include <plx/texture.h>
#include <plx/context.h>
#include <plx/prim.h>

#include "euskal_demo.h" 
//#include "stars.c"

//plx_fcxt_t * cxt;

/*KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);
*/
int plx_main(int argc, char **argv) {
	int done, i=0;
	//pvr_stats_t stats;

	//vid_set_mode(DM_640x480_PAL_IL,PM_RGB565);
	
	//pvr_init_defaults();
	//pvr_set_bg_color(0.0f, 0.0f, 0.0f);
//	cxt = SetFontContext("/cd/fonts/axaxax.txf");
	//stars_init();
    sndoggvorbis_init();
   // llenar_datos();
   // launch_sign();
    printf("\nRandomizing...");
	//init_randoms();
//	load_firmas();
	
	//load_mod("/rd/bgm.it");


	
	
    ShowDisclaimer();
   // DoEndPart();
	/// Until the user hits start...
	for (done = 0; !done; ) {
		// Check for start
		MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)
			if (st->buttons & CONT_START)
				done = 1;
		MAPLE_FOREACH_END()


//	do {
		ParticlePart(i);
        CubePart(i); 
        MultiCubePart(i,1);
        CubePart(i);
        MultiCubePart(i,2);
 //       i++;
   //     done=1;
 //    }while(sndoggvorbis_isplaying());
  //   done=1;
	}
	//pvr_get_stats(&stats);
//	dbglog(DBG_DEBUG, "3D Stats: %ld vblanks, frame rate ~%f fps, max vertex used %d bytes\n",
//		stats.vbl_count, (double)stats.frame_rate, stats.vtx_buffer_used_max);
	
	return 0;
}


