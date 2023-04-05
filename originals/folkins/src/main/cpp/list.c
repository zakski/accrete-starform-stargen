/*
   list.c
   Copyright Chris Croughton 1998
   Internet: chris@keris.demon.co.uk

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met (see file LICENSE for more explanation):

   1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   2. Modifications of the source code must, in addition to the above,
   include a statement that the code has been modified and by whom,
   and have relevant contact information.

   3. Redistributions in binary form must reproduce the above
   copyright notice, this list of conditions and the following
   disclaimer in the documentation and/or other materials provided
   with the distribution.  Note that this does not apply when the
   binary forms part of a completed work such as an executable
   program of which it is a minor part and from which it cannot be
   extracted in a usable form (for instance linked to form an
   executable binary image).

   4. The name of the author may not be used to endorse or promote
   products derived from this software without specific prior
   written permission.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
   IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
 */

/*
   $RCSfile: list.c,v $

   $Date: 1999/04/22 06:48:42 $
   $Revision: 1.2 $

   $Log: list.c,v $
   Revision 1.2  1999/04/22 06:48:42  ccrough
   Reformatted (indent) and protoized

   Revision 1.1  1999/04/21 13:28:56  ccrough
   Initial revision

 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "list.h"

#define printf

static int nnum;

int
listInit(List * list)
{
  list->head = NULL;
  list->tail = NULL;
  return 0;
}

int
listFree(List * list)
{
  Node   *n = list->head;

  while (n)
  {
    Node   *next = n->next;

    printf("free list %.8p node %d\n", list, n->num);
    free(n);
    n = next;
  }
  return 0;
}

int
listAddHead(List * list, Node * node)
{
  node->list = list;
  node->num = nnum++;
  printf("addH list %.8p node %d\n", list, node->num);
  if (!list->head)
  {
    list->head = node;
    list->tail = node;
    node->prev = NULL;
    node->next = NULL;
  }
  else
  {
    node->next = list->head;
    node->prev = NULL;
    list->head = node;
    node->next->prev = node;
  }
  return 0;
}

int
listAddTail(List * list, Node * node)
{
  node->list = list;
  node->num = nnum++;
  printf("addT list %.8p node %d\n", list, node->num);
  if (!list->head)
  {
    list->head = node;
    list->tail = node;
    node->prev = NULL;
    node->next = NULL;
  }
  else
  {
    node->prev = list->tail;
    node->next = NULL;
    list->tail = node;
    node->prev->next = node;
  }
  return 0;
}

int
listInsBefore(List * list, Node * curr, Node * node)
{
  node->list = list;
  node->num = nnum++;
  printf("insB list %.8p node %-5d before %d\n",
	 list, node->num, curr->num);
  node->next = curr;
  node->prev = curr->prev;
  if (curr->prev)
    curr->prev->next = node;
  else
    list->head = node;
  curr->prev = node;
  return 0;
}

int
listInsAfter(List * list, Node * curr, Node * node)
{
  node->list = list;
  node->num = nnum++;
  printf("insA list %.8p node %-5d after %d\n",
	 list, node->num, curr->num);
  node->prev = curr;
  node->next = curr->next;
  if (curr->next)
    curr->next->prev = node;
  else
    list->tail = node;
  curr->next = node;
  return 0;
}

int
listDelete(Node * node)
{
  List   *list = node->list;
  Node   *n = node->next;
  Node   *p = node->prev;

  printf("dele list %.8p node %d\n", list, node->num);
  if (n)
    n->prev = p;
  else
    list->tail = p;
  if (p)
    p->next = n;
  else
    list->head = n;
  return 0;
}

#ifdef TEST

void
dump(List * l)
{
  Node   *n;

  printf("list %.8p -> %.8p, %.8p\n", l, l->head, l->tail);
  for (n = l->head; n; n = n->next)
    printf("node %.8p -> %.8p, %.8p\n", n, n->prev, n->next);
  printf("\n");
}

int
main()
{
  List    l;
  Node   *n;
  Node   *r;
  int     i;

  listInit(&l);
  dump(&l);
  for (i = 0; i < 10; i++)
  {
    n = malloc(sizeof(Node));
    listAddHead(&l, n);
    if (i == 5)
      r = n;
  }
  dump(&l);
  n = malloc(sizeof(Node));
  printf("addb %.8p -> %.8p, %.8p\n", n, n->prev, n->next);
  listInsBefore(&l, r, n);
  dump(&l);
  n = malloc(sizeof(Node));
  printf("adda %.8p -> %.8p, %.8p\n", n, n->prev, n->next);
  listInsAfter(&l, r, n);
  dump(&l);
  while (r)
  {
    n = r->next;
    printf("rem  %.8p -> %.8p, %.8p\n", r, r->prev, r->next);
    listDelete(&l, r);
    dump(&l);
    free(r);
    r = n;
  }
  return 0;
}

#endif
