#include <kos.h>
#include <math.h>
#include <plx/matrix.h>
#include <plx/prim.h>
#include <plx/list.h>
/*

This is a Parallax version of the "bubbles" KGL demo. The speed is about
the same, but it uses the Parallax functions instead of KGL.

*/


static float phase = 0.0f;
//static pvr_poly_cxt_t cxt_b;
//static pvr_poly_hdr_t hdr;
static void sphere( float radius, int slices, int stacks ) {
	int	i, j;
	float	pitch, pitch2;
	float	x, y, z, g, b;
	float	yaw, yaw2;
	plx_dr_state_t	dr_state;

	/* Setup our Direct Render state: pick a store queue and setup QACR0/1 */
	//pvr_dr_init(dr_state);

	/* Initialize xmtrx with the values from KGL */
	plx_mat_identity();
	plx_mat3d_apply(PLX_MAT_SCREENVIEW);
	plx_mat3d_apply(PLX_MAT_PROJECTION);
	plx_mat3d_apply(PLX_MAT_MODELVIEW);

	/* Put our own polygon header */
	//pvr_prim(&hdr, sizeof(hdr));

	/* Iterate over stacks */
	for ( i=0; i<stacks; i++ ) {
		pitch = 2*M_PI * ( (float)i/(float)stacks );
		pitch2 = 2*M_PI * ( (float)(i+1)/(float)stacks );

		/* Iterate over slices: each entire stack will be one
		   long triangle strip. */
		for ( j=0; j<=slices/2; j++ ) {
			yaw = 2*M_PI * ( (float)j/(float)slices );
			yaw2 = 2*M_PI * ( (float)(j+1)/(float)slices );

			/* x, y+1 */
			x = radius * fcos( yaw ) * fcos( pitch2 );
			y = radius * fsin( pitch2 );
			z = radius * fsin( yaw ) * fcos( pitch2 );
			mat_trans_single(x, y, z);			/* Use ftrv to transform */
			g = fcos( yaw*2 ) / 2.0f + 0.5f;
			b = fsin( phase + pitch2 ) / 2.0f + 0.5f;
			plx_vert_fnd(&dr_state, PLX_VERT,
				x, y, z, 0.5f,
				0.0f, g, b);
                
			/* x, y */
			x = radius * fcos( yaw ) * fcos( pitch );
			y = radius * fsin( pitch );
			z = radius * fsin( yaw ) * fcos( pitch );
			mat_trans_single(x, y, z);
			g = fcos( yaw*2 ) / 2.0f + 0.5f;
			b = fsin( phase + pitch ) / 2.0f + 0.5f;

			if (j == (slices/2)) {
				plx_vert_fnd(&dr_state, PLX_VERT_EOS,
					x, y, z, 0.5f,
					0.0f, g, b);
			} else {
				plx_vert_fnd(&dr_state, PLX_VERT,
					x, y, z, 0.5f,
					0.0f, g, b);
			}
		}
	}
}

#define SPHERE_CNT 12
static float r = 0;
static void sphere_frame_trans() {
	int i;


	//pvr_wait_ready();


	//pvr_scene_begin();
	//pvr_list_begin(PVR_LIST_TR_POLY);

	plx_mat3d_identity();
	plx_mat3d_translate(0.0f, 0.0f, -12.0f);
	plx_mat3d_rotate(r * 2, 0.75f, 1.0f, 0.5f);
	plx_mat3d_push();

	for (i=0; i<SPHERE_CNT; i++) {
		plx_mat3d_translate(4.0f * fcos(i * 2*M_PI / SPHERE_CNT), 0.0f, 4.0f * fsin(i * 2*M_PI / SPHERE_CNT));
		plx_mat3d_rotate(r, 1.0f, 1.0f, 1.0f);
		sphere(1.0f, 20, 20);
		if (i < (SPHERE_CNT-1))
			plx_mat3d_peek();
	}

	plx_mat3d_pop();

	
	//pvr_scene_finish();

	r++;
	phase += 2*M_PI / 240.0f;
}



void do_sphere_frame() {
/*
	pvr_poly_cxt_col(&cxt, PVR_LIST_TR_POLY);
	cxt.gen.culling = PVR_CULLING_NONE;
	pvr_poly_compile(&hdr, &cxt);
*/
    sphere_frame_trans();
  /*
	pvr_poly_cxt_col(&cxt, PVR_LIST_TR_POLY);
	cxt.gen.culling = PVR_CULLING_NONE;
	pvr_poly_compile(&hdr, &cxt);
	*/
}
