/**
 * \file liste.c
 * \author Guillaume
 * \brief Gestion des listes
 */

#include "liste.h"
#include <stdio.h>

node_t *my_add_node_next(node_t *node, void *data);
node_t *my_add_node_prev(node_t *node, void *data);
node_t *my_move_next_node(node_t *node);
node_t *my_move_prev_node(node_t *node);

node_t *my_insert_node_next(node_t *node, void *data)
{
    node_t *temp_node = malloc(sizeof(node_t));

    temp_node->next = NULL;
    temp_node->prev = NULL;
    temp_node->data = data;
    if (node == NULL || node->next == NULL) {
        free(temp_node);
        node = my_add_node_next(node, data);
        return (node);
    } else if (node->prev == NULL) {
        free(temp_node);
        node = my_add_node_prev(node, data);
        return (node);
    } else {
        temp_node->prev = node;
        temp_node->next = node->next;
        node->next = temp_node;
        temp_node->next->prev = temp_node;
    }
    return temp_node;
}


node_t *my_move_x_next_node(node_t *node, int nb)
{
    if (node == NULL)
        return NULL;
    for (int i = 0; node->next != NULL && i != nb; node = node->next, i++);
    return node;
}

node_t *my_move_x_prev_node(node_t *node, int nb)
{
    if (node == NULL)
        return NULL;
    for (int i = 0; node->prev != NULL && i != nb; node = node->prev, i++);
    return node;
}


void my_rm_move_ptr(node_t **node)
{
    if ((*node)->prev == NULL) {
        (*node)->next->prev = NULL;
        *node = (*node)->next;
    } else if ((*node)->next == NULL) {
        (*node)->prev->next = NULL;
        *node = (*node)->prev;
    } else {
        (*node)->prev->next = (*node)->next;
        (*node)->next->prev = (*node)->prev;
        *node = (*node)->next;
    }
}

void *my_rm_node(node_t **node)
{
    node_t *temp_node = *node;
    void *temp_data;

    if (node == NULL)
        return NULL;
    temp_data = (*node)->data;
    if ((*node)->prev == NULL && (*node)->next == NULL) {
        free(*node);
        *node = NULL;
        return temp_data;
    }
    my_rm_move_ptr(node);
    free(temp_node);
    return (temp_data);
}


node_t *my_swap_node(node_t *node1)
{
    node_t *node0 = node1->prev;
    node_t *node2 = node1->next;
    node_t *node3 = NULL;

    if (node1 == NULL || node1->next == NULL)
        return NULL;
    node3 = node2->next;
    node2->next = node1;
    node2->prev = node0;
    node1->next = node3;
    node1->prev = node2;
    if (node0 != NULL)
        node0->next = node2;
    if (node3 != NULL)
        node3->prev = node1;
    return (node2);
}

// A ne pas appeler pour une liste cyclique


node_t *my_add_node_next(node_t *node, void *data)
{
    node_t *temp_node = malloc(sizeof(node_t));
    printf("%s",(char *)data);
    temp_node->next = NULL;
    temp_node->data = data;
    node = my_move_next_node(node);
    if (node == NULL) {
        node = temp_node;
        node->prev = NULL;
    } else {
        temp_node->prev = node;
        node->next = temp_node;
    }
    return node;
}


node_t *my_add_node_prev(node_t *node, void *data)
{
    node_t *temp_node = malloc(sizeof(node_t));

    temp_node->prev = NULL;
    temp_node->data = data;
    node = my_move_prev_node(node);
    if (node == NULL) {
        node = temp_node;
        node->next = NULL;
    } else {
        temp_node->next = node;
        node->prev = temp_node;
    }
    return temp_node;
}

node_t *my_move_next_node(node_t *node)
{
    if (node == NULL)
        return NULL;
    for (; node->next != NULL; node = node->next);

    return node;
}

node_t *my_move_prev_node(node_t *node)
{
    if (node == NULL)
        return NULL;
    for (; node->prev != NULL; node = node->prev);

    return node;
}