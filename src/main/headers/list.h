#ifndef _LIST_H
#define _LIST_H

/*
  list.h
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
  $RCSfile: list.h,v $
    
  $Date: 1999/04/21 13:28:56 $
  $Revision: 1.1 $
          
  $Log: list.h,v $
  Revision 1.1  1999/04/21 13:28:56  ccrough
  Initial revision

*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct List List;
typedef struct Node Node;

struct Node
{
  List *list;
  Node *prev;
  Node *next;
  int   num;
};

struct List
{
  Node *head;
  Node *tail;
};

int listInit(List *list);
int listFree(List *list);
int listAddHead(List *list, Node *node);
int listAddTail(List *list, Node *node);
int listInsBefore(List *list, Node *curr, Node *node);
int listInsAfter(List *list, Node *curr, Node *node);
int listDelete(Node *node);

#endif
