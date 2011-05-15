#include <stdio.h>
#include <stdlib.h>

#include "CContainers.h"

struct		s_test
{
  int		nb;
  CCLIST_ENTRY(s_test);
};

CCLIST_PROTO(s_list, s_test);

static void		inspect(struct s_test* entry)
{
  printf("val is: %d\n", entry->nb);
  printf("entry is: %p\n", (void *)entry);
  printf("prev is: %p\n", (void *)entry->prev);
  printf("next is: %p\n", (void *)entry->next);
  puts("");
}

static void		list_infos(CCLIST_NAME(s_list) *list)
{
  printf("head is: %p :: %d\n", (void *)CCLIST_HEAD(list), CCLIST_HEAD(list)->nb);
  printf("tail is: %p :: %d\n", (void *)CCLIST_TAIL(list), CCLIST_TAIL(list)->nb);
}

static void		create_entry(CCLIST_NAME(s_list) *list, int val)
{
  struct s_test	*nentry = malloc(sizeof(*nentry));

  if (nentry != NULL)
    {
      CCLIST_PUSH_BACK(list, nentry);
      nentry->nb = val;
    }
  else
    {
      fprintf(stderr, "Couldn't create entry\n");
    }
}

static void		create_entry_front(CCLIST_NAME(s_list) *list, int val)
{
  struct s_test	*nentry = malloc(sizeof(*nentry));

  if (nentry != NULL)
    {
      CCLIST_PUSH_FRONT(list, nentry);
      nentry->nb = val;
    }
  else
    {
      fprintf(stderr, "Couldn't create entry\n");
    }
}

static void		entry_display(struct s_test *entry)
{
  printf("%d :: %p\n", entry->nb, (void *)entry);
}

static int		item_cmp(struct s_test *entry1, struct s_test* entry2)
{
  return (entry1->nb == entry2->nb);
}

static int		val_cmp(int left, int right)
{
  return (left == right);
}

int			main(void)
{
  CCLIST_CREATE(s_list)	list;
  CCLIST_CREATE(s_list)	tmplist;
  struct s_test		*tmp;
  struct s_test		*tmp2;
  struct s_test		*junk;
  struct s_test		ref = {6, 0, 0};
  size_t		i = 0;

  CCLIST_INIT(&list);
  CCLIST_INIT(&tmplist);

  puts("\n==Creating list (PUSH_BACK)==\n");

  for (i = 6; i < 10; ++i)
    {
      create_entry(&list, i);
      list_infos(&list);
      puts("");
    }

  puts("\n==Adding items (PUSH_FRONT)==\n");

  for (i = 5; i > 0; --i)
    {
      create_entry_front(&list, i);
      list_infos(&list);
      puts("");
    }

  puts("\n==For finding test (PUSH_BACK)==\n");

  create_entry(&list, 6);
  list_infos(&list);

  puts("\n==Iteration==\n");

  CCLIST_FOREACH(&list, tmp)
    {
      entry_display(tmp);
    }

  puts("\n==Reverse iteration==\n");

  CCLIST_RFOREACH(&list, tmp)
    {
      entry_display(tmp);
    }

  puts("\n==Reversion==\n");

  CCLIST_REVERSE(&list, &tmplist, s_test);
  CCLIST_FOREACH(&list, tmp)
    {
      entry_display(tmp);
    }


  puts("\n==Find entry==\n");

  tmp = NULL;
  CCLIST_FIND(&list, tmp, &ref, item_cmp);
  if (tmp != NULL)
      entry_display(tmp);

  puts("\n==Reverse find entry==\n");

  tmp = NULL;
  CCLIST_RFIND(&list, tmp, &ref, item_cmp);
  if (tmp != NULL)
      entry_display(tmp);

  puts("\n==Find entry with field==\n");

  tmp = NULL;
  CCLIST_FIND_FIELD(&list, tmp, 6, nb, val_cmp);
  if (tmp != NULL)
      entry_display(tmp);

  puts("\n==Reverse find entry with field==\n");

  tmp = NULL;
  CCLIST_RFIND_FIELD(&list, tmp, 6, nb, val_cmp);
  if (tmp != NULL)
      entry_display(tmp);

  puts("\n==Deletion==\n");

  if (tmp != NULL)
    CCLIST_REMOVE(&list, tmp);

  CCLIST_FOREACH(&list, junk)
    {
      entry_display(junk);
    }

  puts("\n==Insertion==\n");

  if (tmp != NULL)
    CCLIST_INSERT(&list, CCLIST_PREV(CCLIST_TAIL(&list)), tmp);

  CCLIST_FOREACH(&list, junk)
    {
      entry_display(junk);
    }

  puts("\n==Swapping==\n");

  tmp = CCLIST_HEAD(&list);
  tmp2 = CCLIST_TAIL(&list);
  CCLIST_SWAP(&list, tmp, tmp2, s_test);
  tmp = CCLIST_HEAD(&list)->next;
  tmp2 = CCLIST_TAIL(&list)->prev;
  CCLIST_SWAP(&list, tmp, tmp2, s_test);
  tmp = CCLIST_HEAD(&list);
  tmp2 = CCLIST_HEAD(&list);
  CCLIST_SWAP(&list, tmp, tmp2, s_test);

  CCLIST_FOREACH(&list, junk)
    {
      entry_display(junk);
    }

  puts("\n==Deleting list from the begining==\n");

  CCLIST_FOREACH_SAFE(&list, tmp, junk)
    {
      if (tmp->nb == 6)
	break;
      printf("%d\n", tmp->nb);
      CCLIST_REMOVE(&list, tmp);
      free(tmp);
    }

  puts("\n==Deleting list from the end==\n");

  CCLIST_RFOREACH_SAFE(&list, tmp, junk)
    {
      if (tmp->nb == 8)
	break;
      printf("%d\n", tmp->nb);
      CCLIST_REMOVE(&list, tmp);
      free(tmp);
    }

  puts("\n==Deleting the rest==\n");

  CCLIST_CLEAR(&list, tmp, free);

  puts("\n==Try again==\n");
  CCLIST_FREE(&list, tmp);
  return (0);
}
