

#include <kos.h>
#include <oggvorbis/sndoggvorbis.h>

int PlayOGG(char *song,int rep) {
   // if(song==NULL) { printf("\n%s not found",song); return 1; }

    sndoggvorbis_stop();
    sndoggvorbis_start(song,rep);
        
    return 0;
    }

void StopOGG() {
    sndoggvorbis_stop();
    }
    

