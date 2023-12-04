#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

int isnum(dict_t* d, char *ptr, int size) {
    int three_size = 3;
    if (size < three_size) {
        return 0;
    }
    char* threes[3] = {"one", "two", "six"};
    char *compare_three = malloc(three_size + 1);
    strncpy(compare_three, ptr - three_size, three_size);
    for (int i = 0; i < three_size; i++) {
        if (strcmp(compare_three, threes[i]) == 0) {
            return dict_get(d, threes[i]);
        }
    }

    int four_size = 4;
    if (size < four_size) {
        return 0;
    }
    char* fours[3] = {"four", "five", "nine"};
    char *compare_four = malloc(four_size + 1);
    strncpy(compare_four, ptr - four_size, four_size);
    for (int i = 0; i < 3; i++) {
        if (strcmp(compare_four, fours[i]) == 0) {
            return dict_get(d, fours[i]);
        }
    }

    int five_size = 5;
    if (size < five_size) {
        return 0;
    }
    char* fives[3] = {"three", "seven", "eight"};
    char *compare = malloc(five_size + 1);
    strncpy(compare, ptr - five_size, five_size);
    for (int i = 0; i < 3; i++) {
        if (strcmp(compare, fives[i]) == 0) {
            return dict_get(d, fives[i]);
        }
    }
    return 0;
}

int isnum_back(dict_t* d, char *ptr, int size) {
    int three_size = 3;
    if (size < three_size) {
        return 0;
    }
    char* threes[3] = {"one", "two", "six"};
    char *compare_three = malloc(three_size + 1);
    strncpy(compare_three, ptr, three_size);
    for (int i = 0; i < three_size; i++) {
        if (strcmp(compare_three, threes[i]) == 0) {
            return dict_get(d, threes[i]);
        }
    }

    int four_size = 4;
    if (size < four_size) {
        return 0;
    }
    char* fours[3] = {"four", "five", "nine"};
    char *compare_four = malloc(four_size + 1);
    strncpy(compare_four, ptr, four_size);
    for (int i = 0; i < 3; i++) {
        if (strcmp(compare_four, fours[i]) == 0) {
            return dict_get(d, fours[i]);
        }
    }

    int five_size = 5;
    if (size < five_size) {
        return 0;
    }
    char* fives[3] = {"three", "seven", "eight"};
    char *compare = malloc(five_size + 1);
    strncpy(compare, ptr, five_size);
    for (int i = 0; i < 3; i++) {
        if (strcmp(compare, fives[i]) == 0) {
            return dict_get(d, fives[i]);
        }
    }
    return 0;
}

int main() {
    FILE *file = fopen("/users/pcunniff/projects/c/aoc23/day01/data.txt", "r");
    if (file == NULL) {
        perror("error opening file");
        return 1;
    }
    int total = 0;
    dict_t* d = dict_init();
    dict_set(d, "one", 1);
    dict_set(d, "two", 2);
    dict_set(d, "three", 3);
    dict_set(d, "four", 4);
    dict_set(d, "five", 5);
    dict_set(d, "six", 6);
    dict_set(d, "seven", 7);
    dict_set(d, "eight", 8);
    dict_set(d, "nine", 9);

    int leftval = 0;
    int rightval = 0;

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        // Check if the last character is a newline
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';  // Replace newline with null terminator
        }

        char *leftPtr = line;
        char *rightPtr = line + strlen(line) - 1;

        // Traversing from left to right
        while (*leftPtr && (!isdigit(*(unsigned char*)leftPtr) && !isnum(d, leftPtr, (int) (leftPtr - line)))) {
            leftPtr++;
        }
        if (isnum(d, leftPtr, (int) (leftPtr - line))) {
            leftval = isnum(d, leftPtr, (int) (leftPtr - line));
        } else {
            leftval = (*leftPtr - '0');
        }

        // Traversing from right to left
        while (rightPtr >= line &&
            (!isdigit(*(unsigned char*)rightPtr) && !isnum_back(d, rightPtr, (int) (line + strlen(line) - rightPtr)))
            ) {
            rightPtr--;
        }
        if (isnum_back(d, rightPtr, (int) (line + strlen(line) - rightPtr))) {
            rightval = isnum_back(d, rightPtr, (int) (line + strlen(line) - rightPtr));
        } else {
            rightval = (*rightPtr - '0');
        }
        printf("leftval: %d, rightval: %d\n", leftval, rightval);
        total += leftval * 10 + rightval;
    }

    printf("Total: %d", total);
    fclose(file);
    return 0;
}
