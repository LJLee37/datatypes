#include <stdlib.h>

struct int_node
{
    int data;
    struct int_node * next;
};

struct int_single_linked_list
{
    struct int_node * head;
    struct int_node * current;
    struct int_node * previous;
};

typedef struct int_node inode_t;
typedef struct int_single_linked_list isll_t;

inode_t * init_inode_t(int data)
{
    inode_t * retval = malloc (sizeof(inode_t));
    if (retval == NULL)
        return NULL;
    retval->next = NULL;
    retval->data = data;
    return retval;
}

int is_rear(isll_t * list)
{
    return list == NULL || list->current == NULL || list->current->next == NULL;
}

isll_t * init_isll_t(int data)
{
    isll_t * retval = malloc (sizeof(isll_t));
    if (retval == NULL)
        return NULL;
    retval->head = init_inode_t(data);
    if (retval->head == NULL)
    {
        free(retval);
        return NULL;
    }
    retval->current = retval->head;
    retval->previous = NULL;
    return retval;
}

int delete_inode_t(isll_t * list)
{
    if (list == NULL)
        return 1;
    inode_t * target = list->current;
    if (target == NULL)
        return 1;
    if (list->head == target)
    {
        if (target->next == NULL)
            return 1;
        list->head = target->next;
    }
    else
        list->previous->next = target->next;
    list->current = target->next;
    free(target);
    return 0;
}

int goto_head(isll_t * list)
{
    if (list == NULL)
        return 1;
    list->current = list->head;
    list->previous = NULL;
    return 0;
}

int goto_next(isll_t * list)
{
    if(list == NULL)
        return 1;
    if(list->current->next == NULL)
        return 1;
    list->previous = list->current;
    list->current = list->current->next;
    if (list->previous->next == list->current)
        return 0;
    return 1;
}

int delete_isll_t(isll_t ** list)
{
    isll_t * target = *list;
    if (target == NULL)
        return 1;
    goto_head(target);
    while(target->head->next != NULL)
        delete_inode_t(target);
    free(target->head);
    free(target);
    *list = NULL;
    return 0;
}

int insert_inode(isll_t * list, int data)
{
    if (list == NULL)
        return 1;
    inode_t * new_inode = malloc(sizeof(inode_t));
    if (new_inode == NULL)
        return 1;
    new_inode->data = data;
    new_inode->next = list->current;
    if (list->current == list->head)
        list->head = new_inode;
    else
        list->previous->next = new_inode;
    list->current = new_inode;
    return 0;
}

int append_inode(isll_t * list, int data)
{
    if (list == NULL)
        return 1;
    inode_t * new_inode = malloc(sizeof(inode_t));
    if (new_inode == NULL)
        return 1;
    new_inode->data = data;
    new_inode->next = list->current->next;
    list->current->next = new_inode;
    list->previous = list->current;
    list->current = new_inode;
    return 0;
}

#include <stdio.h>
int main()
{
    printf("int type single linked list\n");
    printf("init number : ");
    int data;
    scanf("%d", &data);
    fflush(stdin);
    isll_t * list = init_isll_t(data);
    while(list != NULL)
    {
        char sw;
        printf("1. insert_inode 2. append_inode\n");
        printf("3. delete_inode 4. print current\n");
        printf("5. is_head 6. is_rear\n");
        printf("7. goto_head 8. goto_next\n");
        printf("9. delete_list\n");
        printf("choice : ");
        scanf("%c", &sw);
        fflush(stdin);
        switch(sw)
        {
        case '1':
            printf("insert data : ");
            scanf("%d", &data);
            fflush(stdin);
            printf("run int insert_inode()\n");
            if(insert_inode(list, data))
            {
                printf("Error occurred!\n");
                printf("trying to exit...");
                if(delete_isll_t(&list))
                {
                    printf("deleting list failed!\n");
                    printf("For performence and safety of your computer, rebooting is recommended.\n");
                    printf("Aborting...");
                    abort();
                }
                break;
            }
            break;
        case '2':
            printf("append data : ");
            scanf("%d", &data);
            fflush(stdin);
            printf("run int append_inode()\n");
            if(append_inode(list, data))
            {
                printf("Error occurred!\n");
                printf("trying to exit...");
                if(delete_isll_t(&list))
                {
                    printf("deleting list failed!\n");
                    printf("For performence and safety of your computer, rebooting is recommended.\n");
                    printf("Aborting...");
                    abort();
                }
                break;
            }
            break;
        case '3':
            printf("run int delete_inode_t()\n");
            if(delete_inode_t(list))
            {
                printf("Error occurred!\n");
                printf("isn't it the last element?\n");
            }
            break;
        case '4':
            printf("currernt data : %d\n",list->current->data);
            break;
        case '5':
            printf("int is_head() does not exist.\nis_head = %d\n", list->previous == NULL);
            break;
        case '6':
            printf("int is_rear() = %d\n", is_rear(list));
            break;
        case '9':
            printf("run int delete_isll_t()\n");
            if(delete_isll_t(&list))
            {
                printf("Error occurred!\n");
                printf("For performence and safety of your computer, rebooting is recommended.\n");
                printf("Aborting...");
                abort();
            }
            break;
        case '7':
            printf("int goto_head() = %d\n", goto_head(list));
            break;
        case '8':
            printf("int goto_next() = %d\n", goto_next(list));
            break;
        default:
            printf("wrong choice.\n\n");
            break;
        }
    }
    printf("list is empty. exiting....");
    return 0;
}
