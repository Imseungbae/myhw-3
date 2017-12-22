#include <sys/types.h>
#include <limits.h>
#include <stdio.h>
#include "run.h"
#include "util.h"
#define bf 512
void *fin =0;
void *base = 0;
p_meta find_meta(p_meta *last, size_t size) {
  p_meta index = base;
  p_meta result = base;

  if(base==last) return -1; //예외처리 base와 last같은경우

  switch(fit_flag){
  case FIRST_FIT:
   {
    //FIRST_FIT CODE
    while(index)
    {
       if(result != base) break;
       else  if(!index->next)     result = index;
       index = index->next;
    }

  }
    break;
  case BEST_FIT:
    {
      //BEST_FIT CODE
    }
     break;
   case WORST_FIT:
    {
      //WORST_FIT CODE

  }


  }

  return result;

 }
void *m_malloc(size_t size) {

 int tem1 = size + META_SIZE;
 int tem2;
 p_meta temp = find_meta(fin,size);

 if(base == 0)
  {
    base = sbrk(0);
    fin = base;
  }

  if(size%4!=0)  size = size + (4-size%4);

  if(temp==-1||(!temp->next && (!temp->free || size > temp->free && temp->size)))
  {
   p_meta tmp2 = fin;
   fin = fin + tem1;
   int flag = brk(fin);
   tmp2->size = size;
   tmp2->prev = temp;


    if(temp!=-1)  temp->next = tmp2;

   temp = tmp2;

  }



   return temp->data;

}
//일단완료오오
void m_free(void *ptr) {
  p_meta pre1 = ptr - META_SIZE;
  pre1->free = 1;

  if(pre1->prev!= -1)
   {
    pre1 = pre1->prev;
    pre1->size = pre1->size+pre1->next->size + META_SIZE;
    pre1->next = pre1->next->next;
   }

  else if(pre1->next && pre1->next->free == 1)
   {
    pre1->size= pre1->next->size+ pre1->size+pre1->next+ META_SIZE;
    pre1->next = pre1->next->next;
   }

 }
//일단완료
void* m_realloc(void* ptr, size_t size)
 {
  p_meta pre2 = ptr-META_SIZE;

  if(size >= pre2->size)
    {
    if(pre2->next && pre2->next->free && pre2->size+pre2->next->size + META_SIZE>=size)
      {
       pre2-> size = pre2->next->size+pre2->size+META_SIZE;
  pre2-> next = pre2 ->next->next;
       pre2-> next-> prev =pre2;
      }
    }
  }

