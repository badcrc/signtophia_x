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

extern void DoEndPart();

//plx_texture_t *firma;//[35]; 
plx_fcxt_t * cxt;
plx_font_t * fnt;
int lado=0;
int coor=0;
int rnd[500];

float pos_x = 0;
float pos_y = 0;
float pos_txt = 0;
int viewed = 0;
int alpha=0;
int cnt_firma=0;

void init_randoms() {
    int n=0;
    for(n=0;n<500;n++) {
         rnd[n] = rand() % 5;
        // printf("N: %d - rand: %d\n",n,rnd[n]);
         }
     

    }
    /*
void load_firmas() {
    int n;
    for(n=0;n<10;n++) {
        firma[n] = plx_txr_load(data[n].nombre,0,0);
        printf("\nCargando firma %d",n);
        }
    }*/

    
void launch_sign() {
    
    switch(rnd[cnt_firma]) {
        case 0: //arriba
                lado = 0;
                break;
        case 1: //abajo
                lado = 1;
                break;
        case 2: //izqda
                lado = 2;
                break;
        case 3: //derecha
                lado = 3;
                break;
        default:
                lado=2;
        }
   /*
    printf("\nLado: %d",lado);
    printf("\nPosicion: %d",coor);*/
    //printf("\nCargando firma: %s",data[cnt_firma].nombre);
   // firma = plx_txr_load(data[cnt_firma].nombre,0,0);
    cnt_firma++;
    }

    
int done_last = 1;

void do_sign_frame() {
    /*
    printf("Viewed: %d\n",viewed);
    printf("Pos: %d",coor);
    
    */
    
    if(cnt_firma-1==32) 
         DoEndPart();

    
    plx_cxt_init();
    plx_cxt_texture(data[cnt_firma-1].firma); 
    
    //printf("\nUsuario tipo: %c",data[cnt_firma].tipo);
    switch(data[cnt_firma-1].tipo) {
        case 'A': plx_fcxt_setcolor4f(cxt,alpha,0.0f, 1.0f, 0.0f); break;
        case 'T': plx_fcxt_setcolor4f(cxt,alpha,1.0f, 0.0f, 0.0f); break;
        case 'F': plx_fcxt_setcolor4f(cxt,alpha,1.0f, 0.80f, 0.25f); break;
        case 'G': plx_fcxt_setcolor4f(cxt,alpha,1.0f, 0.0f, 1.0f); break;
        case 'W': plx_fcxt_setcolor4f(cxt,alpha,0.70f, 0.70f, 0.70f); break;
        case 'U': plx_fcxt_setcolor4f(cxt,alpha,1.0f, 1.0f, 1.0f); break;
       // default: plx_fcxt_setcolor4f(cxt,alpha,1.0f, 1.0f, 1.0f);
        }
            
    
        plx_txr_send_hdr(data[cnt_firma-1].firma,PVR_LIST_TR_POLY,1);
        if(lado == 0 ) { 
                if(viewed==0) { pos_y=0; viewed=1; pos_txt = 400; }
                pos_y+=1.5; pos_txt-=1.75f; coor=pos_y;
                alpha++;
                plx_spr_fnp(500,150,260,coor,5,alpha,1,1,1);
                PrintString(data[cnt_firma-1].autor,400.0f,pos_txt,50.0f);
                if(coor>479 || alpha>250)
                      viewed=2; 
                }
        if(lado == 1 ) { 
                if(viewed==0) { pos_y=480; viewed=1; pos_txt = 0;}
                pos_y-=1.5; pos_txt+=1.75f; coor=pos_y;
                alpha++;
                plx_spr_fnp(500,150,360,coor,5,alpha,1,1,1);
                PrintString(data[cnt_firma-1].autor,100.0f,pos_txt,400.0f);
                if(coor<1 || alpha>250)   
                      viewed=2;
                }
        if(lado == 2 ) { 
                if(viewed==0) { pos_x=0; viewed=1; pos_txt=600; }
                pos_x+=1.5; pos_txt-=1.75f; coor=pos_x;
                alpha++;
                plx_spr_fnp(500,150,coor,365,5,alpha,1,1,1);
                PrintString(data[cnt_firma-1].autor,pos_txt,100.0,90.0f);
                if(coor>639 || alpha>250)
                     viewed=2; 
                }
        if(lado == 3 ) {
                if(viewed==0) { pos_x=480; viewed=1; pos_txt=0;}
                pos_x-=1.5; pos_txt+=1.75f; coor=pos_x;
                alpha++;
                plx_spr_fnp(500,150,coor,75,5,alpha,1,1,1);
                PrintString(data[cnt_firma-1].autor,pos_txt,400.0,10.0f);
                if(coor<1 || alpha>250)
                      viewed=2; 
                }

   
   
        if(viewed==2) {
                plx_txr_destroy(data[cnt_firma-1].firma);
                launch_sign(); 
                viewed=0;
                alpha=0;
                }

                
    }
    
void PrintString(char *str,float x, float y, float z) {
	point_t w;

	w.x = x; w.y = y; w.z = z;

	plx_fcxt_begin(cxt);
		plx_fcxt_setpos_pnt(cxt, &w);
		plx_fcxt_draw(cxt,str);
	plx_fcxt_end(cxt);
	}
	
plx_fcxt_t * SetFontContext(char *fn) {
    plx_font_t * fnt;
    
    printf("\nSetting font: %s\n",fn);
    
    fnt = plx_font_load(fn);
	cxt = plx_fcxt_create(fnt, PVR_LIST_TR_POLY);
	}
    

void llenar_datos() {
    int n=0;
    cxt = SetFontContext("/rd/fonts/axaxax.txf");

    PrintString("LOADING DATA...",50.0f,50.0f,5.0f);
    
    
    strcpy(data[0].nombre,"/rd/gfx/firmas/0.png");
    strcpy(data[0].autor,"Juslibol Lord");
    data[0].tipo='U';
    data[0].firma = plx_txr_load(data[0].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[1].nombre,"/rd/gfx/firmas/1.png");
    strcpy(data[1].autor,"Poison Ivy");
    data[1].tipo='T';
    data[1].firma = plx_txr_load(data[1].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[2].nombre,"/rd/gfx/firmas/2.png");
    strcpy(data[2].autor,"Jeanne");
    data[2].tipo='G';
    data[2].firma = plx_txr_load(data[2].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[3].nombre,"/rd/gfx/firmas/3.png");
    strcpy(data[3].autor,"hal9k");
    data[3].tipo='T';
    data[3].firma = plx_txr_load(data[3].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[4].nombre,"/rd/gfx/firmas/4.png");
    strcpy(data[4].autor,"deadsunrise");
    data[4].tipo='A';
    data[4].firma = plx_txr_load(data[4].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[5].nombre,"/rd/gfx/firmas/5.png");
    strcpy(data[5].autor,"Methodman");
    data[5].tipo='T';
    data[5].firma = plx_txr_load(data[5].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[6].nombre,"/rd/gfx/firmas/6.png");
    strcpy(data[6].autor,"Neoelve");
    data[6].tipo='W';
    data[6].firma = plx_txr_load(data[6].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[7].nombre,"/rd/gfx/firmas/7.png");
    strcpy(data[7].autor,"Nida");
    data[7].tipo='F';
    data[7].firma = plx_txr_load(data[7].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[8].nombre,"/rc/gfx/firmas/8.png");
    strcpy(data[8].autor,"Makai");
    data[8].tipo='T';
    data[8].firma = plx_txr_load(data[8].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[9].nombre,"/rd/gfx/firmas/9.png");
    strcpy(data[9].autor,"Akari");
    data[9].tipo='G';
    data[9].firma = plx_txr_load(data[9].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[10].nombre,"/rd/gfx/firmas/10.png");
    strcpy(data[10].autor,"KuRWeGiO");
    data[10].tipo='F';
    data[10].firma = plx_txr_load(data[10].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[11].nombre,"/rd/gfx/firmas/11.png");
    strcpy(data[11].autor,"Reone");
    data[11].tipo='F';
    data[11].firma = plx_txr_load(data[11].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[12].nombre,"/rd/gfx/firmas/12.png");
    strcpy(data[12].autor,"Shora");
    data[12].tipo='F';
    data[12].firma = plx_txr_load(data[12].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[13].nombre,"/rd/gfx/firmas/13.png");
    strcpy(data[13].autor,"Kebrantador");
    data[13].tipo='A';
    data[13].firma = plx_txr_load(data[13].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[14].nombre,"/rd/gfx/firmas/14.png");
    strcpy(data[14].autor,"Mylenne");
    data[14].tipo='G';
    data[14].firma = plx_txr_load(data[14].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[15].nombre,"/rd/gfx/firmas/16.png");
    strcpy(data[15].autor,"Vaughamm");
    data[15].tipo='U';
    data[15].firma = plx_txr_load(data[15].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[16].nombre,"/rd/gfx/firmas/17.png");
    strcpy(data[16].autor,"Azurhialine");
    data[16].tipo='T';
    data[16].firma = plx_txr_load(data[16].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[17].nombre,"/rd/gfx/firmas/18.png");
    strcpy(data[17].autor,"Kyosuke Kasuga");
    data[17].tipo='W';
    data[17].firma = plx_txr_load(data[17].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[18].nombre,"/rd/gfx/firmas/19.png");
    strcpy(data[18].autor,"Drizzt");
    data[18].tipo='T';
    data[18].firma = plx_txr_load(data[18].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[19].nombre,"/rd/gfx/firmas/20.png");
    strcpy(data[19].autor,"Zeatanas");
    data[19].tipo='T';
    data[19].firma = plx_txr_load(data[19].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[20].nombre,"/rd/gfx/firmas/21.png");
    strcpy(data[20].autor,"Bad_CRC");
    data[20].tipo='T';
    data[20].firma = plx_txr_load(data[20].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[21].nombre,"/rd/gfx/firmas/22.png");
    strcpy(data[21].autor,"Morbiuz");
    data[21].tipo='U';
    data[21].firma = plx_txr_load(data[21].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[22].nombre,"/rd/gfx/firmas/23.png");
    strcpy(data[22].autor,"Bad_CRC");
    data[22].tipo='T';
    data[22].firma = plx_txr_load(data[22].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[23].nombre,"/rd/gfx/firmas/26.png");
    strcpy(data[23].autor,"Daftmojo");
    data[23].tipo='F';
    data[23].firma = plx_txr_load(data[23].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[24].nombre,"/rd/gfx/firmas/27.png");
    strcpy(data[24].autor,"Kebrantador");
    data[24].tipo='A';
    data[24].firma = plx_txr_load(data[24].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[25].nombre,"/rd/gfx/firmas/28.png");
    strcpy(data[25].autor,"Alesgar");
    data[25].tipo='U';
    data[25].firma = plx_txr_load(data[25].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    
    strcpy(data[26].nombre,"/rd/gfx/firmas/29.png");
    strcpy(data[26].autor,"Dexae");
    data[26].tipo='T';
    data[26].firma = plx_txr_load(data[26].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    /*
    strcpy(data[29].nombre,"/cd/gfx/firmas/30.png");
    strcpy(data[29].autor,"Maeghith");
    data[29].tipo='U';
    data[29].firma = plx_txr_load(data[29].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    strcpy(data[30].nombre,"/cd/gfx/firmas/31.png");
    strcpy(data[30].autor,"Bad_CRC");
    data[30].tipo='T';
    data[30].firma = plx_txr_load(data[30].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    strcpy(data[31].nombre,"/cd/gfx/firmas/32.png");
    strcpy(data[31].autor,"Hideyoshi");
    data[31].tipo='U';  
    data[31].firma = plx_txr_load(data[31].nombre,0,0); 
    printf("\nCargando firma: %d",n); n++;
    
    strcpy(data[32].nombre,"/cd/gfx/firmas/33.png");
    strcpy(data[32].autor,"Kujaku");
    data[32].tipo='U';
    data[32].firma = plx_txr_load(data[32].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    
    strcpy(data[33].nombre,"/cd/gfx/firmas/34.png");
    strcpy(data[33].autor,"Weemoose");
    data[33].tipo='G';
    data[33].firma = plx_txr_load(data[33].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;
    */
    /*
    strcpy(data[34].nombre,"/cd/gfx/firmas/35.png");
    strcpy(data[34].autor,"Vauhnamm");   
    data[34].tipo='U';
    data[34].firma = plx_txr_load(data[34].nombre,0,0);
    printf("\nCargando firma: %d",n); n++;*/
    
    }
    

