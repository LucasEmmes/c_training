#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char a;
} element;

void print_list(element * * list, char length) {
    printf("List: ");
    for (char i = 0; i < length; i++)
    {
        printf("%d,", list[i]->a);
    }
    printf("\n");
}

// Pass list as argument so that we can skip allocating memory
element * * merge(element * * list, element * * list1, char list1_length, element * * list2, char list2_length) {

    // Counter for number of elements consumed
    char l1_index = 0;
    char l2_index = 0;
    
    // While both still have elements left, copy smallest and increment counter
    while (l1_index < list1_length && l2_index < list2_length) {
        
        if (list1[l1_index]->a < list2[l2_index]->a) {
            list[l1_index + l2_index] = list1[l1_index];
            l1_index++;
        } else {
            list[l1_index + l2_index] = list2[l2_index];
            l2_index++;
        }

    }

    // Once we're done one of them must still have at least 1 element left
    // If list1 has some left
    while (l1_index < list1_length) {
        list[l1_index + l2_index] = list1[l1_index];
        l1_index++;
    }
    // If list2 has some left
    while (l2_index < list2_length) {
        list[l1_index + l2_index] = list2[l2_index];
        l2_index++;
    }

    return list;
}

element * * merge_sort(element * * list, char length) {

    // If we have only 1 element, we return it
    if (length == 1) {
        return list;
    } else {
        // Split up lengths
        char list1_length = (char) length/2;
        char list2_length = length - list1_length;

        // Allocate enough memory for both lists
        element ** list1 = (element * *) malloc(sizeof(element *) * list1_length);
        element ** list2 = (element * *) malloc(sizeof(element *) * list2_length);

        // Transfer pointers
        for (char i = 0; i < list1_length; i++)
        {
            list1[i] = list[i];
        }
        for (char i = 0; i < list2_length; i++)
        {
            list2[i] = list[i + list1_length];
        }

        // Recursively sort list partitions
        list1 = merge_sort(list1, list1_length);
        list2 = merge_sort(list2, list2_length);
        // Merge together in correct order
        merge(list, list1, list1_length, list2, list2_length);

        // Don't forget to free them
        free(list1);
        free(list2);

        return list;        
    }
}


int main(int argc, char const *argv[])
{

    element a,b,c,d,e,f,g;
    
    a.a = 6;
    b.a = 2;
    c.a = 3;
    d.a = 8;
    e.a = 4;
    f.a = 10;
    g.a = 0;

    element * L[7] = {&a,&b,&c,&d,&e,&f,&g};
    char length = 7;

    element * * sorted = L;
    
    printf("BEFORE:\n");
    print_list(sorted, length);
    
    sorted = merge_sort(sorted, length);
    
    printf("AFTER:\n");
    print_list(sorted, length);
    
    return 0;
}
