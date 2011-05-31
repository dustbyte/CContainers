#include <stdio.h>
#include <stdlib.h>

#include "CContainers.h"

struct		s_entry
{
  int		nb;
  CCLIST_ENTRY(struct s_entry);
};

CCLIST_PROTO(s_list, struct s_entry);

static void		ut_step(const char *msg)
{
  printf("\n==%s==\n\n", msg);
}

static void		list_infos(CCLIST_NAME(s_list) *list)
{
  printf("head is: %p :: %d\n", (void *)CCLIST_HEAD(list), CCLIST_HEAD(list)->nb);
  printf("tail is: %p :: %d\n", (void *)CCLIST_TAIL(list), CCLIST_TAIL(list)->nb);
}

static void		create_entry(CCLIST_NAME(s_list) *list, int val)
{
  struct s_entry	*nentry = malloc(sizeof(*nentry));

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
  struct s_entry	*nentry = malloc(sizeof(*nentry));

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

static void		entry_display(struct s_entry *entry)
{
  printf("%d :: %p\n", entry->nb, (void *)entry);
}

static int		entry_cmp(struct s_entry *entry1, struct s_entry* entry2)
{
  return (entry1->nb - entry2->nb);
}

static int		val_cmp(int left, int right)
{
  return (left - right);
}

static struct s_entry	*copy_entry(const struct s_entry * const ref)
{
  struct s_entry	*cpy = malloc(sizeof(*cpy));

  if (cpy != NULL)
    cpy->nb = ref->nb;
  return (cpy);
}

int			main(void)
{
  CCLIST_CREATE(s_list)	list;
  CCLIST_CREATE(s_list)	copy;
  struct s_entry	*tmp;
  struct s_entry	*tmp2;
  struct s_entry	*junk;
  struct s_entry	ref = {6, 0, 0};
  size_t		i = 0;

  CCLIST_INIT(&list);

  ut_step("Creating list (PUSH_BACK)");

  for (i = 6; i < 10; ++i)
    {
      create_entry(&list, i);
      list_infos(&list);
      puts("");
    }

  ut_step("Adding items (PUSH_FRONT)");

  for (i = 5; i > 0; --i)
    {
      create_entry_front(&list, i);
      list_infos(&list);
      puts("");
    }

  ut_step("For finding test (PUSH_BACK)");

  create_entry(&list, 6);
  list_infos(&list);

  ut_step("Show list size");

  printf("size: %d\n", CCLIST_SIZE(&list));

  ut_step("Iteration");

  CCLIST_FOREACH(&list, tmp)
    {
      entry_display(tmp);
    }

  ut_step("Reverse iteration");

  CCLIST_RFOREACH(&list, tmp)
    {
      entry_display(tmp);
    }

  ut_step("Copy");

  CCLIST_COPY(&list, &copy, struct s_entry, copy_entry, free);

  CCLIST_FOREACH(&copy, tmp)
    {
      entry_display(tmp);
    }

  ut_step("Reversion");

  CCLIST_REVERSE(&list, struct s_entry);
  CCLIST_FOREACH(&list, tmp)
    {
      entry_display(tmp);
    }

  ut_step("Find entry");

  tmp = NULL;
  CCLIST_FIND(&list, tmp, &ref, entry_cmp);
  if (tmp != NULL)
      entry_display(tmp);

  ut_step("Reverse find entry");

  tmp = NULL;
  CCLIST_RFIND(&list, tmp, &ref, entry_cmp);
  if (tmp != NULL)
      entry_display(tmp);

  ut_step("Find entry with field");

  tmp = NULL;
  CCLIST_FIND_FIELD(&list, tmp, 6, nb, val_cmp);
  if (tmp != NULL)
      entry_display(tmp);

  ut_step("Reverse find entry with field");

  tmp = NULL;
  CCLIST_RFIND_FIELD(&list, tmp, 6, nb, val_cmp);
  if (tmp != NULL)
      entry_display(tmp);

  ut_step("Deletion");

  if (tmp != NULL)
    CCLIST_REMOVE(&list, tmp);

  CCLIST_FOREACH(&list, junk)
    {
      entry_display(junk);
    }

  ut_step("Insertion");

  if (tmp != NULL)
    CCLIST_INSERT(&list, CCLIST_PREV(CCLIST_TAIL(&list)), tmp);

  CCLIST_FOREACH(&list, junk)
    {
      entry_display(junk);
    }

  ut_step("Swapping");

  tmp = CCLIST_HEAD(&list);
  tmp2 = CCLIST_TAIL(&list);
  CCLIST_SWAP(&list, tmp, tmp2, struct s_entry);

  tmp = CCLIST_HEAD(&list)->next;
  tmp2 = CCLIST_TAIL(&list)->prev;
  CCLIST_SWAP(&list, tmp, tmp2, struct s_entry);

  tmp = CCLIST_HEAD(&list);
  tmp2 = CCLIST_HEAD(&list);
  CCLIST_SWAP(&list, tmp, tmp2, struct s_entry);

  CCLIST_FOREACH(&list, junk)
    {
      entry_display(junk);
    }

  ut_step("Sorting");

  CCLIST_SORT(&list, struct s_entry, entry_cmp);

  CCLIST_FOREACH(&list, junk)
    {
      entry_display(junk);
    }

  ut_step("Concatenation");

  CCLIST_CONCAT(&list, &copy);

  CCLIST_FOREACH(&list, tmp)
    {
      entry_display(tmp);
    }

  CCLIST_FREE(&copy);

  ut_step("Deleting list from the begining");

  CCLIST_FOREACH_SAFE(&list, tmp, junk)
    {
      if (tmp->nb == 6)
	break;
      printf("%d\n", tmp->nb);
      CCLIST_REMOVE(&list, tmp);
      free(tmp);
    }

  ut_step("Deleting list from the end");

  CCLIST_RFOREACH_SAFE(&list, tmp, junk)
    {
      if (tmp->nb == 8)
	break;
      printf("%d\n", tmp->nb);
      CCLIST_REMOVE(&list, tmp);
      free(tmp);
    }

  ut_step("Deleting the rest");

  CCLIST_CLEAR(&list, free);

  ut_step("Try again");
  CCLIST_FREE(&list);

  printf("size: %d\n\n", CCLIST_SIZE(&list));

  return (0);
}
