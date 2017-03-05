#ifndef ARRAY_H
#define ARRAY_H

#include <assert.h>
#include <stdbool.h>


#define MAXSIZE 1000


typedef int Status;
typedef int ElemType;


typedef struct ListCell ListCell;

typedef struct List
{
    int         length;
    ListCell    *head;
    ListCell    *tail;
}List;


struct ListCell
{
    void        *ptr_value;
    ListCell    *next;
};




#endif
