#include "mythread.h"
#include "list.h"
#include "string.h"
#define SZ 4096

struct hashmap_element_s 
{
    char *key;
    void *data;
};

struct hashmap_s 
{
    struct list* table[SZ];
    struct lock* lk[SZ];
};

int hash_code_map(const char* key)
{
    int val=0;
    int i=0;
    while(*(key+i)!='\0')
    {
        int ascii=*(key+i);
        val=26*val+(ascii-96);
        i++;
        val=val%(SZ);
    }
    return val%(SZ);
}

int hashmap_create(struct hashmap_s *const out_hashmap)  // Initialize a hashmap
{
        for(int i=0;i<SZ;i++)
        {
            out_hashmap->table[i]=list_new();
            out_hashmap->lk[i]=lock_new();
        }
}
int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data)  // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function
{
    int key_map=hash_code_map(key);
    struct list* get_list=hashmap->table[key_map];
    struct listentry* head=get_list->head;
    struct listentry* tail=get_list->tail;
    while (head!=NULL && strcmp(((struct hashmap_element_s*)(head->data))->key,key)!=0)
    { 
        head=head->next;
    }
    if(head==NULL)
    {
        struct listentry* new_entry=(struct listentry*) malloc(sizeof(struct listentry));
        struct hashmap_element_s* key_data=(struct hashmap_element_s*) malloc(sizeof(struct hashmap_element_s));
        new_entry->data=key_data;
        key_data->key=(char*)malloc(strlen(key)+1);
        strcpy(key_data->key,key);
        key_data->data=data;
        new_entry->next=NULL;
        new_entry->prev=NULL;
        if(get_list->head==NULL && get_list->tail==NULL)
        {
            get_list->head=new_entry;
            get_list->tail=new_entry;
        }
        else
        {
            new_entry->prev=tail;
            tail->next=new_entry;
            get_list->tail=new_entry;
        }
    }
    else
    {
        ((struct hashmap_element_s*)(head->data))->data=data;
    }
}
void* hashmap_get(struct hashmap_s *const hashmap, const char* key)    // Fetch value of a key from hashmap
{
    int code_key=hash_code_map(key);
    struct list* get_list=hashmap->table[code_key];
    struct listentry* head=get_list->head;
    while (head!=NULL && strcmp((((struct hashmap_element_s*)(head->data))->key),key)!=0)
    {
        head=head->next;
    }
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        return ((struct hashmap_element_s*)(head->data))->data;

    }

}
void hashmap_iterator(struct hashmap_s* const hashmap,int (*f)(struct hashmap_element_s *const))  // Execute argument function on each key-value pair in hashmap
{
    for(int i=0;i<SZ;i++)
    {
        struct listentry* head=hashmap->table[i]->head;
        struct listentry* tail=hashmap->table[i]->tail;

        while(head!=NULL)
        {
            f((struct hashmap_element_s*)(head->data));
        }        
    }
}

int acquire_bucket(struct hashmap_s *const hashmap, const char* key) // Acquire lock on a hashmap slot
{
    int hash_value=hash_code_map(key);
    struct lock* lock_add=lock_new();
    lock_add->ctx=(ucontext_t *)curr->data;
    hashmap->lk[hash_value]=lock_add;
}
int release_bucket(struct hashmap_s *const hashmap, const char* key)   // Release acquired lock
{
    int hash_value=hash_code_map(key);
    hashmap->lk[hash_value]=lock_new();
}
