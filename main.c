#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct object_data
{
    int age;
    char* name;
    char* description;
};


struct List {
    int item_id;
    struct object_data data;
    struct List* next;
};

//void add_first_list(struct List** item_list, int data);
void add_list(struct List** item_list, struct object_data data);
void insert_to_list(struct List** item_list, struct object_data data, int index);
void show_list(struct List** item_list);
void after_deleting(struct List** item_list, int index);
void after_inserting(struct List** item_list, int index);
struct List* get_list(struct List** item_list, int data);
struct List pop_list(struct List** item_list, int list_index);


void add_list(struct List** item_list, struct object_data data)
{   
    struct List* tmp_list = (struct List*)malloc(sizeof(struct List));
    if(*item_list)
    {
        tmp_list->item_id = (*item_list)->item_id + 1;
        tmp_list->next = *item_list;
    }
    else 
    {   
        tmp_list->item_id = 0;
        tmp_list->next = tmp_list;
    }
    tmp_list->data = data;
    *item_list=tmp_list;
}


void insert_to_list(struct List** item_list, struct object_data data, int index)
{
    struct List* tmp_list = (struct List*)malloc(sizeof(struct List));
    struct List* list_item_next = get_list(item_list, index);
    struct List* list_item_prev = get_list(item_list, index - 1);
    if(list_item_next == NULL)
    {   
        printf("Element not find!\n");
        return;
    }
    tmp_list->item_id = index;
    tmp_list->data = data;
    if(list_item_prev != NULL && list_item_next != NULL)
    {
        tmp_list->next = list_item_prev;
        list_item_next->next = tmp_list;
    }
    else if(list_item_prev == NULL)
    {
        tmp_list->next=tmp_list;
        list_item_next->next=tmp_list;
    }
    after_inserting(item_list, index);
}


void after_inserting(struct List** item_list, int index)
{
    struct List* i_list = *item_list;
    int i = i_list->item_id;
    while(i >= index )
    {
        i_list->item_id++;
        i_list = i_list->next;
        i--;
    }
}


struct List pop_list(struct List** item_list, int list_index)
{
    struct List* deleting_item = get_list(item_list, list_index);
    struct List* list_item_next = get_list(item_list, list_index + 1);
    struct List popped_item = *deleting_item;
    if(deleting_item != NULL)
    {
        if(list_index != 0 && list_item_next != NULL)
        {
            list_item_next->next = deleting_item->next;
            after_deleting(item_list, list_index);
        }
        else if(list_index == 0 && list_item_next != NULL)
        {
            list_item_next->next = list_item_next;
            after_deleting(item_list, list_index);
        }
        else if(list_index!=0 && list_item_next == NULL)
        {
            *item_list = deleting_item->next;
        }
        else if(list_index == 0 && list_item_next == NULL)
        {
            *item_list = NULL;
        }
        free(deleting_item);
    }
    return popped_item;
}


void after_deleting(struct List** item_list, int index)
{
    struct List* i_list = *item_list;
    int i = i_list->item_id;
    while(i > index && i_list != NULL && i_list->next != i_list)
    {
        i_list->item_id--;
        i_list = i_list->next;
        i--;
    }
    if(index == 0 && i_list->next == i_list)
    {
        i_list->item_id--;
    }

}


struct List* get_list(struct List** item_list, int index)
{
    bool index_finded = false;
    struct List* i_list;
    for(i_list = *item_list; i_list->next != NULL && i_list->next != i_list; i_list = i_list->next)
    {
        if(i_list->item_id == index)
        {   
            index_finded = true;
            break;
        }
    }
    if(i_list->item_id == index)
    {   
        index_finded = true;
    }    

    if(index_finded){
        return i_list;
    }
    else {
        printf("Not find list item witch id = %d\n", index);
        return NULL;
    }
}


void show_list(struct List** item_list)
{
    if(*item_list == NULL)
    {
        printf("List if empty!\n");
        return;
    }
    struct List* i_list = *item_list;
    while (i_list->next != NULL && i_list->next != i_list)
    {   
        printf("name[%d]: %s\n", i_list->item_id, i_list->data.name);
        i_list = i_list->next;
    }
    printf("name[%d]: %s\n", i_list->item_id, i_list->data.name);
}


int main ()
{   
    struct List* item_list = NULL;    
    struct object_data test_person;
    
    test_person.age = 12;
    test_person.description = "test 1";
    test_person.name = "Bob";
    add_list(&item_list, test_person);

    test_person.age = 14;
    test_person.description = "test 2";
    test_person.name = "Tim";
    add_list(&item_list, test_person);

    test_person.age = 22;
    test_person.description = "test 3";
    test_person.name = "Jack";
    add_list(&item_list, test_person);

    show_list(&item_list);

    printf("################################################\n");
    struct List* result;
    result = get_list(&item_list, 0);
    printf("name: %s\n", result->data.name);

    result = get_list(&item_list, 2);
    printf("name: %s\n", result->data.name);

    result = get_list(&item_list, 1);
    printf("name: %s\n", result->data.name);

    struct List popped_item = pop_list(&item_list, 0);
    printf("popped: %s\n", popped_item.data.name);
    show_list(&item_list);

    printf("################################################\n");
    test_person.age = 64;
    test_person.description = "test 4";
    test_person.name = "Peter";  
    insert_to_list(&item_list, test_person, 1);
    show_list(&item_list);

    test_person.age = 34;
    test_person.description = "test 5";
    test_person.name = "Joe";
    insert_to_list(&item_list, test_person, 1);
    show_list(&item_list);

    return 0;
}