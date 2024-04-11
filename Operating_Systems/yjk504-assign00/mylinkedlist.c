#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylinkedlist.h"

/*
 * Function: NewStudentCell
 * Usage: student_cell_T *element;
 *        element = NewStudentCell(int id, double gpa, char *name);
 * --------------------------
 * This function allocates space for a student cell and initializes its fields.
 */
student_cell_T *NewStudentCell(int id, double gpa, char *name) {
    student_cell_T *element = (student_cell_T *)malloc(sizeof(student_cell_T));
    if (!element) {
        fprintf(stderr, "NewStudentCell cannot allocate memory\n");
        return NULL;
    }

    element->id = id;
    element->gpa = gpa;

    // Allocate memory for the name and copy it
    element->name = (char *)malloc(strlen(name) + 1);
    if (!element->name) {
        fprintf(stderr, "NewStudentCell cannot allocate memory for name\n");
        free(element); // Free the previously allocated memory
        return NULL;
    }
    strcpy(element->name, name);

    element->next = NULL;

    return element;
}

/*
 * Function: NewLinkedList
 * Usage: linked_list_T *list;
 *        list = NewLinkedList();
 * --------------------------
 * This function allocates and returns an empty linked list.
 */
linked_list_T *NewLinkedList(void) {
    linked_list_T *list = (linked_list_T *)malloc(sizeof(linked_list_T));
    if (!list) {
        fprintf(stderr, "NewLinkedList cannot allocate memory\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}

/*
 * Function: FreeLinkedList
 * Usage: FreeLinkedList(list);
 * ------------------------
 * This function frees the storage associated with list.
 */
void FreeLinkedList(linked_list_T *list) {
    if (!list) {
        return;
    }

    student_cell_T *current = list->head;
    while (current) {
        student_cell_T *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }

    free(list);
}

/*
 * Function: Enlist
 * Usage: Enlist(list, element);
 * -------------------------------
 * This function adds a student cell pointed to by element to the end of the list.
 */
void Enlist(linked_list_T *list, student_cell_T *element) {
    if (!list || !element) {
        return;
    }

    if (!list->head) {
        list->head = element;
        list->tail = element;
    } else {
        list->tail->next = element;
        list->tail = element;
    }
}

/*
 * Function: Delist
 * Usage: element = Delist(list);
 * --------------------------------
 * This function removes the student cell at the head of the list
 * and returns its address to the caller (client).  If the list is empty, Delist
 * prints an Error with an appropriate message and returns NULL.
 */
student_cell_T *Delist(linked_list_T *list) {
    if (!list || !list->head) {
        fprintf(stderr, "Delist: List is empty\n");
        return NULL;
    }

    student_cell_T *element = list->head;
    list->head = element->next;

    if (!list->head) {
        list->tail = NULL;
    }

    return element;
}

/*
 * Function: LinkedListIsEmpty, LinkedListIsFull
 * Usage: if (LinkedListIsEmpty(list)) . . .
 *        if (LinkedListIsFull(list)) . . .
 * -------------------------------------
 * These functions test whether the list is empty or full.
 */
int LinkedListIsEmpty(linked_list_T *list) {
    return list == NULL || list->head == NULL;
}

int LinkedListIsFull(linked_list_T *list) {
    return 0; // because we have a linked list
}

/*
 * Function: LinkedListLength
 * Usage: n = LinkedListLength(list);
 * ------------------------------
 * This function returns the number of elements in the list.
 */
int LinkedListLength(linked_list_T *list) {
    int length = 0;
    student_cell_T *current = list->head;

    while (current) {
        length++;
        current = current->next;
    }

    return length;
}

/*
 * Function: GetLinkedListElement
 * Usage: element = GetLinkedListElement(list, index);
 * -----------------------------------------------
 * This function returns the element at the specified index in the
 * list, where the head of the list is defined as index 0. For
 * example, calling GetLinkedListElement(list, 0) returns the initial
 * element from the list without removing it.  If the caller tries
 * to select an element that is out of range, GetLinkedListElement prints
 * Error and returns NULL.  Note: This function is not a fundamental list operation
 * and is instead provided mainly to facilitate debugging.
 */
student_cell_T *GetLinkedListElement(linked_list_T *list, int index) {
    if (!list || index < 0) {
        fprintf(stderr, "GetLinkedListElement: Invalid input\n");
        return NULL;
    }

    student_cell_T *current = list->head;
    int i = 0;

    while (current) {
        if (i == index) {
            return current;
        }
        i++;
        current = current->next;
    }

    fprintf(stderr, "GetLinkedListElement: Index out of range\n");
    return NULL;
}
