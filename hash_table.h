#include <stdlib.h>
#include <string.h>

typedef void (*VoidFunc)(void);
typedef int (*IntFunc)(void);

typedef enum {
    VOID_FUNC,
    INT_FUNC
} FuncType;

typedef struct {
    char* key;
    FuncType type;
    union {
        VoidFunc voidFunc;    // Function pointer for void functions
        IntFunc intFunc;      // Function pointer for int-returning functions
    };
} FunctionItem;

FunctionItem* create_void_func_item(char* key, VoidFunc func) {
    FunctionItem* item = malloc(sizeof(FunctionItem));
    item->type = VOID_FUNC;
    item->voidFunc = func;
    return item;
}

FunctionItem* create_int_func_item(char* key, IntFunc func) {
    FunctionItem* item = malloc(sizeof(FunctionItem));
    item->type = INT_FUNC;
    item->intFunc = func;
    return item;
}

typedef struct {
    FunctionItem* entries;
    size_t capacity; // capacity
    size_t length; // length
} FuncHashTable;

