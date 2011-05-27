#include <stdio.h>
#include <stdlib.h>

#include "CCQueue.h"

typedef struct s_entry
{
  int		nb;
  CCQUEUE_ENTRY(struct s_entry);
} t_entry;

typedef CCQUEUE_PROTO(s_queue, t_entry) t_queue;

/* Don't do that this is evil ! */
static void	display_queue(const t_queue *queue)
{
  const t_entry	*tmp;

  CCLIST_FOREACH(queue, tmp)
    {
      printf("%d\n", tmp->nb);
    }
}

static void	create_entry(t_queue *queue, int val)
{
  t_entry	*nentry = malloc(sizeof(*nentry));

  if (nentry != NULL)
    {
      nentry->nb = val;
      CCQUEUE_PUSH(queue, nentry);
    }
}

void		ut_step(const char *str)
{
  printf("\n==%s==\n\n", str);
}

int		main(void)
{
  t_queue	queue;
  t_queue	cpy;
  t_entry	*tmp;
  size_t	i;

  CCQUEUE_INIT(&queue);

  ut_step("Creation");

  for (i = 0; i < 10; ++i)
    create_entry(&queue, i);

  display_queue(&queue);

  ut_step("Copy");

  CCQUEUE_DUP(&queue, &cpy, t_entry);

  display_queue(&cpy);

  ut_step("Pop");

  while (!CCQUEUE_EMTPY(&queue))
    {
      CCQUEUE_POP(&queue, tmp);
      printf("%d\n", tmp->nb);
      free(tmp);
    }

  ut_step("Refence");

  CCQUEUE_REF(&cpy, &queue);

  CCQUEUE_INIT(&cpy);

  display_queue(&queue);

  ut_step("Deletion");

  CCQUEUE_FREE(&queue);

  printf("%d\n\n", CCQUEUE_SIZE(&queue));

  return (0);
}
