

#include <stdio.h>
#include <stdlib.h>

typedef struct Array {
    int *data;
    size_t len;
} Array;

void print(Array arr) {
    printf("[ ");
    for (size_t i = 0; i < arr.len; i++) {
        if (i == arr.len - 1) {
            printf("%d ]\n", arr.data[i]);
            return;
        }
        printf("%d, ", arr.data[i]);        
    }
}

void prepopulate(Array arr, int start, int step) {
    arr.data[0] = start;
    for (size_t i = 1; i < arr.len; i++) {
        arr.data[i] = arr.data[i - 1] + step;
    }
}

int _bsearch(int val, Array arr, size_t start, size_t end) {
    const int m = (start + end) / 2;
    if (start > end) {
        return -1;    
    }

    if (arr.data[m] > val) {
        return _bsearch(val, arr, start, m - 1);
    } else if (arr.data[m] < val) {
        return _bsearch(val, arr, m + 1, end);
    } else {
        return m;
    }
}

int binarysearch(int val, Array arr) {
    return _bsearch(val, arr, 0, arr.len - 1);    
}

int main(int argc, char *argv[argc + 1]) {
    int len = atoi(argv[1]);
    int val = atoi(argv[2]);
    Array arr = { .len = len };
    arr.data = malloc(arr.len * sizeof (int));
    prepopulate(arr, 3, 2);
    
    print(arr);

    printf("Index: %d\n", binarysearch(val, arr));
    return EXIT_SUCCESS;
}

