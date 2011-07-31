#include <stdlib.h>
#include <stdio.h>

#include "CContainers/CCStack.h"
#include "unit_test.h"

/* C++ compilable */
#undef CC_CAST
#define CC_CAST int

static int	stack_append(ccstack_t *stack, int val)
{
  int		*tmp;

  ccstack_malloc(sizeof(*tmp), tmp);
  if (tmp != NULL)
    {
      *tmp = val;
      ccstack_push(stack, tmp);
      printf("top: %d\n", *(int *)ccstack_top(stack));
      return (1);
    }
  return (0);
}

int		main()
{
  ccstack_t	stack;
  int		i;

  ccstack_init(&stack);

  ut_log("push");
  for (i = 0; i < 10; ++i)
    if (stack_append(&stack, i) == 0)
      break;

  ut_log("pop");
  while (!ccstack_empty(&stack))
    {
      printf("top: %d\n", *(int *)ccstack_top(&stack));
      ccstack_pop(&stack);
    }
  
  return (0);
}
