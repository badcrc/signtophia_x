/* 3D star code, written a long time ago =) */
#include <math.h>
#include <kos.h>


#define NS 1024
int	*star_x = NULL, *star_y, *star_z;

/* init stars so that they will be anywhere on the screen, but will start out
   as a single dot in the middle because of the Z coord.

   This routine has been mathmatically optimized to produce the best possible
   spread of stars on the given starfield parameters by solving the
   perspective equation for X and Y. */

#define zk 64
#define MAXX ((640*(zk+640))/zk)
#define MAXY ((480*(zk+480))/zk)

pvr_poly_hdr_t stars_header;

void stars_init() {
	int i;
	pvr_poly_cxt_t tmp;

	if (star_x == NULL) {
		star_x = malloc(NS*sizeof(int));
		star_y = malloc(NS*sizeof(int));
		star_z = malloc(NS*sizeof(int));
	}

	for (i=0; i<NS; i++) {
		star_x[i]=randnum(MAXX)-(MAXX/2);
		star_y[i]=randnum(MAXY)-(MAXY/2);
		star_z[i]=randnum(640);
	}

	pvr_poly_cxt_col(&tmp, PVR_LIST_OP_POLY);
	pvr_poly_compile(&stars_header, &tmp);
}

/* Draws a point using a triangle strip */
void poly_pnt(int x, int y, float z, float size, int color) {
	pvr_vertex_t vert;
	
	vert.flags = PVR_CMD_VERTEX;
	vert.x = x;
	vert.y = y + size;
	vert.z = z;
	vert.u = vert.v = 0.0f;
	vert.argb = PVR_PACK_COLOR(1.0f, color / 256.0f, color / 256.0f, color / 256.0f);
	vert.oargb = 0;
	pvr_prim(&vert, sizeof(vert));
	
	vert.y = y;
	pvr_prim(&vert, sizeof(vert));
	
	vert.flags = PVR_CMD_VERTEX_EOL;
	vert.x = x + size;
	vert.y = y + size;
	pvr_prim(&vert, sizeof(vert));
}

void stars_one_frame() {
	int i, x1, y1, xn, yn, zn, c;


	/* Send polygon header to the TA using store queues */
	pvr_prim(&stars_header, sizeof(stars_header));

	/* Calculate each star's position and plot it on screen */
	for (i=0; i<NS; i++) {
		/* Calculate star perspective */
		xn = star_x[i]; yn = star_y[i]; zn = star_z[i];
		x1 = xn*zk / (zn + zk);
		y1 = yn*zk / (zn + zk);

		if (x1>-320 && y1>-240 && x1<320 && y1<240) {
			c = (zn * 256/640) & 0xff;
			poly_pnt(x1+320, y1+240, 1.0f, 4.0f, 255-c);
		} else {
			star_z[i] = 640;
		}

		/* Move star's Z coord to show motion inward */
		star_z[i]-=28;
	}
}

/********************************************************************/

