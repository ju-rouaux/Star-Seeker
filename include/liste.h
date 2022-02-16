
//Equivalent ifdef
#pragma once

#include <stdlib.h>
#include <stdio.h>


typedef struct my_node {
    struct my_node *next;
    struct my_node *prev;
    void *data;
} node_t;


node_t *my_move_next_node(node_t *node);

node_t *my_move_x_next_node(node_t *node, int nb);

node_t *my_move_prev_node(node_t *node);

node_t *my_move_x_prev_node(node_t *node, int nb);

void *my_rm_node(node_t **node);

node_t *my_add_node_next(node_t *node, void *data);

node_t *my_insert_node_next(node_t *node, void *data);

node_t *my_add_node_prev(node_t *node, void *data);

node_t *my_swap_node(node_t *node);

//tests

int node_tests(void);
