#ifndef LIST_H
#define LIST_H

struct list 
{
	struct listentry* head;
	struct listentry* tail;
};

struct listentry {
	void *data;
	struct listentry *prev;
	struct listentry *next;
};

void list_rm(struct list* l, struct listentry* e)    // Remove an item from the list
{
	struct listentry* head=l->head;
	while(head!=NULL || head!=e)
	{
		head=head->next;
	}
	if(head!=NULL)
	{
		if(l->head==e && l->tail==e)
		{
			l->head=NULL;
			l->tail=NULL;
		}
		else if(l->head==e)
		{
			l->head=head->next;
			l->head->prev=NULL;
		}
		else if(l->tail==e)
		{
			l->tail=l->tail->prev;
			l->tail->next=NULL;
		}
		else
		{
			(head->prev)->next=head->next;
			(head->next)->prev=head->prev;
		}
	}
	free(e);
}
struct listentry* list_add(struct list* l, void* data)  // Add an item to the list
{
	struct listentry* new_block=(struct listentry* )(malloc(sizeof(struct listentry)));
	new_block->data=data;
	new_block->next=NULL;
	if(l->head==NULL && l->tail==NULL)
	{
		l->head=new_block;
		l->tail=new_block;
	}
	else
	{
		l->tail->next=new_block;
		new_block->prev=l->tail;
		l->tail=new_block;
	}
	return new_block;

}
struct list* list_new()  // Return an initialized list
{
	struct list* new_list=(struct list*)(malloc(sizeof(struct list)));
	new_list->head=NULL;
	new_list->tail=NULL;
	
	return new_list;
}
int is_empty(struct list* l)  // Check if list is empty or not
{
	if(l->head==NULL && l->tail==NULL)
	{
		return true;
	}
	return false;
}
#endif
