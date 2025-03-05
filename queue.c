#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */

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
    if (!head || !s) {
        return false;
    }
    element_t *new_element = malloc(sizeof(element_t));
    if (!new_element) {
        return false;
    }
    new_element->value = malloc(strlen(s) + 1);
    if (!new_element->value) {
        free(new_element);
        return false;
    }
    strlcpy(new_element->value, s, strlen(s) + 1);
    list_add(&new_element->list, head);
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
    new_element->value = malloc(strlen(s) + 1);
    if (!new_element->value) {
        free(new_element);
        return false;
    }
    strlcpy(new_element->value, s, strlen(s) + 1);
    list_add_tail(&new_element->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    if (sp) {
        memset(sp, '\0', bufsize);
        strncpy(sp, container_of(head->next, element_t, list)->value,
                bufsize - 1);
    }
    element_t *remove_element = list_entry(head->next, element_t, list);
    list_del(head->next);
    return remove_element;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    if (sp) {
        memset(sp, '\0', bufsize);
        strncpy(sp, container_of(head->prev, element_t, list)->value,
                bufsize - 1);
    }
    element_t *remove_element = list_entry(head->prev, element_t, list);
    list_del(head->prev);
    return remove_element;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return 0;
    }
    int number = 0;
    struct list_head *node;
    list_for_each (node, head) {
        number++;
    }
    return number;
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
    if (!head || list_empty(head)) {
        return false;
    }
    struct list_head *node, *safe;
    bool isduplicate = false;
    list_for_each_safe (node, safe, head) {
        element_t *cur = list_entry(node, element_t, list);
        if (safe != head) {
            const element_t *nex = list_entry(safe, element_t, list);
            if (!strcmp(cur->value, nex->value)) {
                list_del(node);
                free(cur->value);
                free(cur);
                isduplicate = true;
            } else if (isduplicate) {
                list_del(node);
                free(cur->value);
                free(cur);
                isduplicate = false;
            }
        } else {
            if (isduplicate) {
                list_del(node);
                free(cur->value);
                free(cur);
                isduplicate = false;
            }
        }
    }
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    if (!head) {
        return;
    }
    if (list_empty(head) || list_is_singular(head))
        return;
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
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
