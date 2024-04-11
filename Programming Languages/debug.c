#include <stdio.h>
#include <stdlib.h>

// Describe our data
typedef struct Obj {
    int count;
    char *name;
    struct Obj *next;
} Obj_t;

// Function prototypes
Obj_t *makeObj(char *name);
void freeObj(Obj_t *obj);
void setNext(Obj_t *obj, Obj_t *nxt);
static void showInfo(Obj_t *obj);

int main(int argc, char *argv[]) {
    // Create some Objs to work with
    Obj_t *one = makeObj("First");
    Obj_t *two = makeObj("Second");
    Obj_t *three = makeObj("Third");
    Obj_t *four = makeObj("Fourth");
    Obj_t *five = makeObj("Fifth");

    // Link Objs together
    setNext(one, three);
    setNext(one, two);
    setNext(three, two);
    setNext(four, two);
    setNext(five, four);

    // Free three and see what the others have
    freeObj(three);

    showInfo(one);
    showInfo(two);
    showInfo(four);
    showInfo(five);

    return 0;
}

// Create a new instance of the obj
Obj_t *makeObj(char *name) {
    Obj_t *obj = (Obj_t *)malloc(sizeof(Obj_t));
    obj->count = 1;  // Initialize count to 1
    obj->name = name;
    obj->next = NULL;
    return obj;
}

// We're done with this Obj. Careful: recursive
void freeObj(Obj_t *obj) {
    if (obj) {
        obj->count -= 1;  // Decrement count
        if (obj->count == 0) {
            if (obj->next != NULL) {
                freeObj(obj->next);
            }
            free(obj);
        }
    }
}

// Set its next pointer to another Obj
void setNext(Obj_t *obj, Obj_t *nxt) {
    if (obj) {
        if (obj->next != NULL) {
            freeObj(obj->next);  // Free the existing next Obj
        }
        obj->next = nxt;
        if (nxt) {
            nxt->count += 1;  // Increment count of the next Obj
        }
    }
}

// Print information about an obj
static void showInfo(Obj_t *obj) {
    if (obj) {
        printf("%s count = %d\n", obj->name, obj->count);
    }
}

