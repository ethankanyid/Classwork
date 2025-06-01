#include <stdio.h>
#include <stdlib.h>
#include "double_stack.h"

typedef struct DoubleStack
{
  struct DoubleStack *next_p;
  double d;
}doublestack;

doublestack *doubleStackBase_p = NULL;

static doublestack *doubleStack_new(double d)
{
  doublestack *doubleStack_p=(doublestack*)malloc(sizeof(doublestack));

  doubleStack_p->next_p=NULL;
  doubleStack_p->d=d;

  return doubleStack_p;
}

void doubleStack_push(double d)
{
  doublestack *doublestack_p = doubleStack_new(d);

  doublestack_p->next_p = doubleStackBase_p;
  doubleStackBase_p = doublestack_p;
}

int doubleStack_pop(double *val)
{
  if (doubleStackBase_p != NULL)
  {
      (*val) = doubleStackBase_p->d;
      doubleStackBase_p=doubleStackBase_p->next_p;
      return 1;
  } 

  return 0;
}

void doubleStack_print(void)
{
  int result;
  double d;
  result = doubleStack_pop(&d);
  if (result == 1)
  {
      printf("%20.14g\n", d);
      doubleStack_print();
      doubleStack_push(d);
  }
}


