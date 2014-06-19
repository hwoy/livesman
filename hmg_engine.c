#include <stdlib.h>
#include <time.h>
#include "hmg_engine.h"

#define UNCH '_'

/*********************************** intit random functions ********************************/
void
hmf_srandom (void)
{
  srand (time (NULL));
}

/*********************************** random functions ********************************/
int
hmf_random (int min, int max)
{
  return min <= max ? min + (rand () % (max - min + 1)) : -1;
}



assem *
hmf_init (int id)
{
  assem *asmb;
  if (!(asmb = (assem *) malloc (sizeof (assem))))
    {
      return (assem *) 0;
    }

  initx (asmb, id);
  return asmb;
}

/*********************************** free functions ********************************/
void
hmf_free (assem * asmb)
{

  freeallx (asmb);
  free (asmb);
}


int
hmf_add (assem * asmb, void *obj)
{
  linklist *list;
  if (!(list = newll ()))
    return 0;
  list->ptr = obj;
  addx (asmb, list);
  return 1;
}

/*********************************** get number of data functions ********************************/
unsigned int
hmf_getndata (assem * asmb, unsigned int gid)
{
  linklist *ptr;
  unsigned int n;

  for (n = 0, ptr = asmb->beginx; ptr; ptr = ptr->forwx)
    {

      if (gid == DPTR (ptr->ptr)->gid)
	{
	  n++;
	}

    }
  return n;
}

/*********************************** get data functions ********************************/
hms_data *
hmf_getdata (assem * asmb, unsigned int gid, unsigned int index)
{
  linklist *ptr;
  unsigned int n;

  for (n = 0, ptr = asmb->beginx; ptr; ptr = ptr->forwx)
    {


      if (gid == DPTR (ptr->ptr)->gid)
	{
	  if (index == n)
	    {
	      return DPTR (ptr->ptr);
	    }
	  n++;
	}

    }

  return (hms_data *) 0;
}

/*********************************** init game functions ********************************/
hms_game *
hmf_initgame (hms_data * data, unsigned int lives)
{
  hms_game *game;
  unsigned int i;

  if (!(game = (hms_game *) malloc (sizeof (hms_game))))
    {
      return (hms_game *) 0;
    }

  game->data = data;
  game->lives = lives;

  game->win = 0;

  for (i = 0; game->data->name[i]; i++)
    {
      game->name[i * 2] = UNCH;
      game->name[i * 2 + 1] = 0x20;
    }
  game->name[i * 2] = 0;

  return game;
}

/*********************************** get group functions ********************************/
hms_group *
hmf_getgroup (assem * asmb, unsigned int gid)
{
  linklist *ptr;

  for (ptr = asmb->beginx; ptr; ptr = ptr->forwx)
    {


      if (gid == GPTR (ptr->ptr)->gid)
	{
	  return GPTR (ptr->ptr);
	}

    }
  return (hms_group *) 0;
}

/*********************************** get number of group functions ********************************/
unsigned int
hmf_getngroup (assem * asmb)
{
  linklist *ptr;
  unsigned int n;

  for (n = 0, ptr = asmb->beginx; ptr; ptr = ptr->forwx, n++)
    {
    }

  return n;
}

/*********************************** gameplay functions ********************************/
int
hmf_gameplay (hms_game * game, char ch)
{

  int i, j;

  if (game->lives < 1)
    {
      game->win = -1;
      return -1;
    }


  for (i = 0, j = 0; game->data->name[i]; i++)
    {

      if (ch == game->data->name[i])
	{
	  game->name[i * 2] = ch;
	  j++;
	}

    }

  if (!j)
    {
      game->lives--;
    }


  for (i = 0, j = 1; game->data->name[i]; i++)
    {

      if (game->name[i * 2] != game->data->name[i])
	{
	  j = 0;
	  break;
	}

    }

  if (j)
    {
      game->win = 1;
    }

  if (!game->lives)
    {
      game->win = -1;
    }
  return game->win;
}


hms_game *
hmf_solve (hms_game * game)
{
  int i;
  for (i = 0; game->data->name[i]; i++)
    {
      game->name[i * 2] = game->data->name[i];
    }
  game->name[i * 2] = game->data->name[i];
  return game;
}

void
hmf_freegame (hms_game * game)
{
  free (game);
}

