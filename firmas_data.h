#include <kos.h>
#include <math.h>
//#include <pcx/pcx.h>

#include <plx/font.h>
#include <plx/sprite.h>
#include <plx/list.h>
#include <plx/dr.h>
#include <plx/context.h>

//35 FIRMAS durante la canción.

typedef struct {
    char nombre[60];
    char autor[60];
    int tipo;
    plx_texture_t *firma;
    } firm_data;
    
firm_data data[35];


/* tipos (para el color):
- 1 A: admin (verde)
- 2 T: team (rojo)
- 3 F: fansub (naranja)
- 4 G: girl (rosa)
- 5 W: worker (gris)
- 6 U: usuario normal (blanco)
*/
