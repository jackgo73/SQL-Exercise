#include "Arr"

static List* new_list(NodeTag type)
{
	List	   *new_list;
	ListCell   *new_head;

	new_head = (ListCell *) palloc(sizeof(*new_head));
	new_head->next = NULL;
	/* new_head->data is left undefined! */

	new_list = (List *) palloc(sizeof(*new_list));
	new_list->type = type;
	new_list->length = 1;
	new_list->head = new_head;
	new_list->tail = new_head;

	return new_list;
}


static void new_head_cell(List *list)
{
	ListCell   *new_head;

	new_head = (ListCell *) palloc(sizeof(*new_head));
	new_head->next = list->head;

	list->head = new_head;
	list->length++;
}


static void new_tail_cell(List *list)
{
	ListCell   *new_tail;

	new_tail = (ListCell *) palloc(sizeof(*new_tail));
	new_tail->next = NULL;

	list->tail->next = new_tail;
	list->tail = new_tail;
	list->length++;
}

