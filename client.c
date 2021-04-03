#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "client.h"

struct AdjListNode
{
    int node_data;
    struct AdjListNode *next;
};

struct AdjList
{
    int list_capacity;
    struct AdjListNode *head;
};

struct Graph
{
    int length_of_main_list;
    struct AdjList *array;
};

struct AdjListNode *newAdjListNode(int node_data)
{
    struct AdjListNode *newNode = (struct AdjListNode *)malloc(
        sizeof(struct AdjListNode));
    newNode->node_data = node_data;
    newNode->next = NULL;
    return newNode;
}

struct Graph *createGraph(int length_of_main_list)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->length_of_main_list = length_of_main_list;
    graph->array = (struct AdjList *)malloc(length_of_main_list * sizeof(struct AdjList));
    int i;
    //creating the main list as per length
    for (i = 0; i < length_of_main_list; i++)
    {
        graph->array[i].head = NULL;
        graph->array[i].list_capacity = 1;
    }
    return graph;
}

void addEdge(struct Graph *graph, int src, int data)
{
    struct AdjListNode *newNode = newAdjListNode(data);
    if (graph->array[src].head == NULL)
    {
        graph->array[src].head = newNode;
    }
    else
    {
        struct AdjListNode *temp = graph->array[src].head;
        //adding the new node at the end of list
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        graph->array[src].list_capacity++;
    }
}

void rearrange(struct Graph *graph)
{
    //to traverse through all elements of main array
    for (int i = 0; i < (graph->length_of_main_list) - 1; i++)
    {
        if (graph->array[i].list_capacity == 2 * (i + 2))
        {
            struct AdjListNode *temp = graph->array[i].head;
            int first_value, second_value;
            int t = 0;
            //traversing throug i th element of list
            while (t < (graph->array[i].list_capacity))
            {
                //highest element of first set
                if (t == 0)
                {
                    printf("%d ", temp->node_data);
                    first_value = temp->node_data;
                    temp = temp->next;
                }
                else if (t == (i + 2))
                {
                    //highest element of second set
                    printf("X %d ", temp->node_data);
                    second_value = temp->node_data;
                    temp = temp->next;
                }
                else
                {
                    printf("%d ", temp->node_data);
                    temp = temp->next;
                }
                t++;
            }
            printf("= ");
            struct AdjListNode *temp2 = graph->array[i].head;
            if (first_value > second_value)
            {
                addEdge(graph, i + 1, first_value);
                addEdge(graph, i + 1, second_value);
                printf("%d %d ", first_value, second_value);
                int q = 0;
                // to add remaining elements of winner set
                while (temp2 != NULL)
                {
                    if (q < (i + 2) && q > 0)
                    {
                        addEdge(graph, i + 1, temp2->node_data);
                        printf("%d ", temp2->node_data);
                    }
                    q++;
                    temp2 = temp2->next;
                }
                printf("\n");
            }
            else if (second_value > first_value)
            {
                addEdge(graph, i + 1, second_value);
                addEdge(graph, i + 1, first_value);
                printf("%d %d ", second_value, first_value);
                int e = 0;
                // to add remaining elements of winner set
                while (temp2 != NULL)
                {
                    if (e > i + 2)
                    {
                        addEdge(graph, i + 1, temp2->node_data);
                        printf("%d ", temp2->node_data);
                    }
                    e++;
                    temp2 = temp2->next;
                }
                printf("\n");
            }
            graph->array[i].head = NULL;
            graph->array[i].list_capacity = 1;
            free(temp);
        }
    }
}

void tournament(struct Graph *graph, int a, int b)
{
    int c, d;
    if (a > b)
    {
        c = a;
        d = b;
    }
    else
    {
        c = b;
        d = a;
    }
    addEdge(graph, 0, c);
    addEdge(graph, 0, d);
    printf("%d X %d = %d %d\n", a, b, c, d);
    rearrange(graph);
}

void find_second_greatest(int *numbers, int length)
{
    if (length == 0)
    {
        printf("Array does not contain any elements\n");
    }
    else if (length == 1)
    {
        printf("Array has only one element\n");
    }
    else if (length > 1)
    {
        //detemining the length of list
        int length_of_main_list = (int)(ceil(log(length) / log(2))) + 1;
        struct Graph *graph = createGraph(length_of_main_list);
        //traversing through the list
        for (int i = 0; i < (length); i = i + 2)
        {
            if (i != (length - 1))
            {
                tournament(graph, *(numbers + i), *(numbers + i + 1));
            }
            else
            {
                addEdge(graph, 0, *(numbers + i));
            }
        }
        //Handling end condition of odd/not power of 2 and final calculation
        for (int i = 0; i < (graph->length_of_main_list) - 1; i++)
        {
            struct AdjListNode *temp = graph->array[i].head;
            if ((graph->array[i].list_capacity) <= 2 * (i + 2) && (graph->array[i].head != NULL))
            {
                //if list contains only one set
                if (graph->array[i].list_capacity <= (i + 2) && (graph->array[i].list_capacity) >= 1)
                {
                    for (int t = 0; t < graph->array[i].list_capacity; t++)
                    {
                        addEdge(graph, i + 1, temp->node_data);
                        temp = temp->next;
                    }
                    graph->array[i].head = NULL;
                    graph->array[i].list_capacity = 1;
                    free(temp);
                }
                // if the list contains 2 sets
                else if (graph->array[i].list_capacity >= (i + 3))
                {
                    int first_value, second_value;
                    int t = 0;
                    while (t < (graph->array[i].list_capacity))
                    {
                        //highest element of first set
                        if (t == 0)
                        {
                            printf("%d ", temp->node_data);
                            first_value = temp->node_data;
                            temp = temp->next;
                        }
                        //highest element of second set
                        else if (t == (i + 2))
                        {
                            printf("X %d ", temp->node_data);
                            second_value = temp->node_data;
                            temp = temp->next;
                        }
                        else
                        {
                            printf("%d ", temp->node_data);
                            temp = temp->next;
                        }
                        t++;
                    }
                    printf("= ");
                    struct AdjListNode *temp2 = graph->array[i].head;
                    if (first_value > second_value)
                    {
                        addEdge(graph, i + 1, first_value);
                        addEdge(graph, i + 1, second_value);
                        printf("%d %d ", first_value, second_value);
                        int q = 0;
                        while (temp2 != NULL)
                        {
                            if (q < (i + 2) && q > 0)
                            {
                                addEdge(graph, i + 1, temp2->node_data);
                                printf("%d ", temp2->node_data);
                            }
                            q++;
                            temp2 = temp2->next;
                        }
                        printf("\n");
                    }
                    else if (second_value > first_value)
                    {
                        addEdge(graph, i + 1, second_value);
                        addEdge(graph, i + 1, first_value);
                        printf("%d %d ", second_value, first_value);

                        int e = 0;
                        while (temp2 != NULL)
                        {
                            if (e > i + 2)
                            {
                                addEdge(graph, i + 1, temp2->node_data);
                                printf("%d ", temp2->node_data);
                            }
                            e++;
                            temp2 = temp2->next;
                        }
                        printf("\n");
                    }

                    graph->array[i].head = NULL;
                    graph->array[i].list_capacity = 1;
                    free(temp);
                }
            }
            rearrange(graph);
        }
        // calculatind second highest from final
        struct AdjListNode *temp4 = graph->array[(graph->length_of_main_list) - 1].head;
        temp4 = temp4->next;
        int high, low;
        high = temp4->node_data;
        temp4 = temp4->next;
        while (temp4 != NULL)
        {
            low = temp4->node_data;
            if (low > high)
            {
                high = low;
            }
            temp4 = temp4->next;
        }
        printf("\n%d\n", high);
    }
}
