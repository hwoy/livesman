#include "linklist/linklist.h"
#include "grap/grap.h"
#define GPTR(x) ((hms_group *)(x))
#define DPTR(x) ((hms_data *)(x))

#define NEWGROUP() (hms_group *)malloc(sizeof(hms_group))
#define NEWDATA() (hms_data *)malloc(sizeof(hms_data))
/* above 2 macros requires stdlib.h*/

#define HMC_NAMELEN 25
#define HMC_HINTLEN 50*2

#define HMC_ENGINE_VERSION_STR "1.23"
#define HMC_ENGINE_VERSION_MAJOR 1
#define HMC_ENGINE_VERSION_MINOR 23

typedef struct
{
unsigned int gid;
char name[HMC_NAMELEN+1];
char hint[HMC_HINTLEN+1];
}hms_data;


typedef struct
{
unsigned int gid;
char name[HMC_NAMELEN+1];
}hms_group;

typedef struct
{
hms_group *group;
hms_data *data;
char name[(HMC_NAMELEN+1)*2];
int win;
unsigned int lives;
}hms_game;


/*********** All function do not check NULL parameters. So that you could check them yourself ******************/

void hmf_srandom(void); /*init seed random*/
int hmf_random(int min,int max); /*generate number*/

unsigned int  hmf_getndata(assem *asmb,unsigned int  gid); /*return numbers of data*/
hms_data *hmf_getdata(assem *asmb,unsigned int  gid,unsigned int  index); /*return a pointer of data*/

hms_group *hmf_getgroup(assem *asmb,unsigned int  gid);   /*return a pointer of group*/
unsigned int  hmf_getngroup(assem *asmb);       /*return numbers of group*/

void hmf_free(assem *asmb);  /*free allocated space of assem and lnklist*/
void hmf_freegame(hms_game *); /*free allocated space of assem and game*/
assem *hmf_init(int id); /*init assem*/
int hmf_add(assem *asmb,void *obj); /*add linklist*/

hms_game * hmf_initgame(hms_data *data,unsigned int lives); /*set up a game*/
int hmf_gameplay(hms_game *game,char ch); /*Play a game*/

hms_game *hmf_solve(hms_game *game); /*solve a puzzle*/


