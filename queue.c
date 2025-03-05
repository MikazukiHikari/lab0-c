#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"



/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head) {
        return NULL;
    }
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head) {
        return;
    }
    if (list_empty(head)) {
        free(head);
        return;
    }
    struct list_head *node, *safe;
    list_for_each_safe (node, safe, head) {
        element_t *current_element = list_entry(node, element_t, list);
        q_release_element(current_element);
    }
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head || !s) {
        return false;
    }
    element_t *new_element = malloc(sizeof(element_t));
    if (!new_element) {
        return false;
    }
    new_element->value = strdup(s);
    if (!new_element->value) {
        free(new_element);
        return false;
    }
    list_add(&new_element->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head || !s) {
        return false;
    }
    element_t *new_element = (element_t *) malloc(sizeof(element_t));
    if (!new_element) {
        return false;
    }
    new_element->value = strdup(s);
    if (!new_element->value) {
        free(new_element);
        return false;
    }
    list_add_tail(&new_element->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *remove_element = list_entry(head->next, element_t, list);
    if (sp) {
        memset(sp, '\0', bufsize);
        strncpy(sp, container_of(head->next, element_t, list)->value,
                bufsize - 1);
    }
    list_del(head->next);
    return remove_element;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *remove_element = list_entry(head->prev, element_t, list);
    if (sp) {
        memset(sp, '\0', bufsize);
        strncpy(sp, container_of(head->prev, element_t, list)->value,
                bufsize - 1);
    }
    list_del(head->prev);
    return remove_element;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    return -1;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head || list_empty(head))
        return false;
    struct list_head *forward = head->next;
    struct list_head *backward = head->prev;
    while (forward != backward && forward->next != backward) {
        forward = forward->next;
        backward = backward->prev;
    }
    list_del(backward);
    free(list_entry(backward, element_t, list)->value);
    free(list_entry(backward, element_t, list));
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head) {}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (q_size(head) == 0 || q_size(head) == 1) {
        return;
    }
    struct list_head *node, *safe;
    list_for_each_safe (node, safe, head) {
        if (safe != head) {
            list_move(node, safe);
            safe = node->next;
        }
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend)
{
    if (!head || q_size(head) == 0 || q_size(head) == 1) {
        return;
    }
    struct list_head *tmp = head;
    head->prev->next = NULL;
    head->next = merge_sort_list(head->next, descend);
    struct list_head *cur = head->next;
    while (cur->next != NULL) {
        cur->prev = tmp;
        tmp = cur;
        cur = cur->next;
    }
    cur->prev = tmp;
    cur->next = head;
    head->prev = cur;
}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    if (!head || q_size(head) == 0) {
        return 0;
    } else if (q_size(head) == 1) {
        return 1;
    }
    const char *last = list_entry(head->prev, element_t, list)->value;
    struct list_head *node, *safe;
    for (node = (head)->prev, safe = node->prev; node != head;
         node = safe, safe = node->prev) {
        element_t *node_entry = list_entry(node, element_t, list);
        if (strcmp(node_entry->value, last) > 0) {
            list_del(node);
            free(node_entry->value);
            free(node_entry);
        } else if (strcmp(node_entry->value, last) < 0) {
            last = node_entry->value;
        }
    }
    return q_size(head);
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    if (!head || q_size(head) == 0) {
        return 0;
    } else if (q_size(head) == 1) {
        return 1;
    }
    const char *last = list_entry(head->prev, element_t, list)->value;
    struct list_head *node, *safe;
    for (node = (head)->prev, safe = node->prev; node != head;
         node = safe, safe = node->prev) {
        element_t *node_entry = list_entry(node, element_t, list);
        if (strcmp(node_entry->value, last) < 0) {
            list_del(node);
            free(node_entry->value);
            free(node_entry);
        } else if (strcmp(node_entry->value, last) > 0) {
            last = node_entry->value;
        }
    }
    return q_size(head);
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    if (!head || q_size(head) == 0) {
        return 0;
    } else if (q_size(head) == 1) {
        return q_size(list_entry(head->next, queue_contex_t, chain)->q);
    }
    queue_contex_t *node = list_entry(head->next, queue_contex_t, chain);
    node->q->prev->next = NULL;
    struct list_head *nex = node->chain.next;
    for (int i = 0; i < ((node->size) - 1); i++) {
        queue_contex_t *next_node = list_entry(nex, queue_contex_t, chain);
        next_node->q->prev->next = NULL;
        node->q->next =
            merge_two_list(node->q->next, next_node->q->next, descend);
        INIT_LIST_HEAD(next_node->q);
        nex = nex->next;
    }
    struct list_head *cur = node->q->next;
    struct list_head *tmp = node->q;
    while (cur->next != NULL) {
        cur->prev = tmp;
        tmp = cur;
        cur = cur->next;
    }
    cur->prev = tmp;
    cur->next = node->q;
    node->q->prev = cur;

    return q_size(node->q);
}

bool q_shuffle(struct list_head *head)
{
    int len = q_size(head);
    if (len <= 1) {
        return true;
    }
    // Fisher-Yates shuffle algorithm
    for (int j = len - 1; j > 0; j--) {
        int rand_idx = rand() % (j + 1);
        struct list_head *node;
        list_for_each(node, head) {
            if (rand_idx == 0) {
                break;
            }
            rand_idx--;
        }
        list_del(node);
        list_add_tail(node, head);
    }
    return true;
}
