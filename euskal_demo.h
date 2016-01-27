#define PC50


//Leer el ogg desde el pc a50hz, en cada frame hay un pequeño parón, se soluciona 
//leyendo la musica del rd
#ifdef PC50
#define MUSIC_TIMER_OFFSET 0
#endif

#ifdef RD50
#define MUSIC_TIMER_OFFSET +20
#endif

#ifdef PC60
#define MUSIC_TIMER_OFFSET -200
#endif

#ifdef RD60
#define MUSIC_TIMER_OFFSET +299
#endif

#ifdef VGA
#define MUSIC_TIMER_OFFSET +20
#endif


