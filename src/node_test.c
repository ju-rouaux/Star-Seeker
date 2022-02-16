/**
 * \file node_test.c
 * \author Guillaume
 * \brief Tests pour la liste
 */

#include "liste.h"

/**
 * \brief Fonction de tests
 * \return int 
 */
int node_tests(void)
{
    node_t *linked_list = my_add_node_next(NULL, "test1\n");

    linked_list = my_add_node_next(linked_list, "test2\n");
    linked_list = my_add_node_next(linked_list, "test3\n");
    linked_list = my_add_node_next(linked_list, "test4\n");
    linked_list = my_add_node_next(linked_list, "test5\n");
    linked_list = my_add_node_next(linked_list, "test6\n");
    linked_list = my_move_prev_node(linked_list);
    linked_list = my_move_x_next_node(linked_list, 3);
    printf("%s",(char *)linked_list->data);
    // printf("node1:%p\n", (void*)linked_list);
    // printf("node2:%p\n", (void*)linked_list->next);
    my_rm_node(&linked_list);
    // printf("node2:%p\n", (void*)linked_list);
    printf("blah1\n");
    printf("%s",(char *)linked_list->data);
    printf("%s",(char *)linked_list->prev->data);
    linked_list = my_swap_node(linked_list->prev);
    printf("blah2\n");
    printf("%s",(char *)linked_list->data);
    printf("%s",(char *)linked_list->data);
    printf("%s",(char *)linked_list->data);
    // my_putstr(linked_list->data);
    // linked_list = my_move_x_next_node(linked_list, 4);
    // my_putstr(linked_list->data);
    // linked_list = my_move_x_prev_node(linked_list, 2);
    // my_putstr(linked_list->data);
    // temp_node = linked_list->next;
    // my_rm_node(&linked_list);
    // my_putstr(linked_list->data);
    // my_putstr("aaaaaa\n");
    // linked_list = my_move_x_next_node(linked_list->next, 1);
    // my_putstr(linked_list->data);
    // my_putstr("bbbbbb\n");
    // printf("node2a:%p\n", (void*)linked_list);
    // my_putstr(linked_list->data);
    // linked_list = my_swap_node(linked_list);
    // my_putstr("cccccc\n");
    // my_putstr(linked_list->data);
    // my_putstr(linked_list->next->data);
    return 0;
}