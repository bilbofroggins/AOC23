#include <stdio.h>
#include <string.h>
#include "dictionary.h"

int main() {
    FILE *file = fopen("/users/pcunniff/projects/c/aoc23/day02/data.txt", "r");
    if (file == NULL) {
        perror("error opening file");
        return 1;
    }

    dict_t *maxes = dict_init();
    dict_set(maxes, "red", 12);
    dict_set(maxes, "green", 13);
    dict_set(maxes, "blue", 14);

    dict_t *power_maxes = dict_init();

    int total = 0;
    int sumpower = 0;
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        int valid = 1;
        char *token;
        char *rest = line;
        char *inner_rest;
        char *inner_token;
        int gameIndex;
        int number;
        char color[10];
        int power = 0;
        int max_so_far = 0;

        dict_set(power_maxes, "blue", 0);
        dict_set(power_maxes, "green", 0);
        dict_set(power_maxes, "red", 0);

        token = strtok_r(rest, ":", &rest);
        if (token != NULL && sscanf(token, "Game %d", &gameIndex) == 1) {
            printf("Game index: %d\n", gameIndex);
        } else {
            printf("Game index not found.\n");
            return 1;
        }

        token = strtok_r(rest, ";", &rest);
        while (token != NULL) {
            inner_rest = token;
            inner_token = strtok_r(inner_rest, ",", &inner_rest);
            while (inner_token != NULL) {
                if (sscanf(inner_token, "%d %s", &number, color) == 2) {
                    max_so_far = dict_get(power_maxes, color);
                    if (number > max_so_far) {
                        dict_set(power_maxes, color, number);
                    }
                    if (number > dict_get(maxes, color)) {
                        valid = 0;
                    }
                }
                inner_token = strtok_r(inner_rest, ",", &inner_rest);
            }
            token = strtok_r(rest, ";", &rest);
        }
        if (valid) {
            total += gameIndex;
        }
        power = dict_get(power_maxes, "blue") *
                dict_get(power_maxes, "green") *
                dict_get(power_maxes, "red");
//        printf("powers: %d, %d, %d, %d", dict_get(power_maxes, "blue"), dict_get(power_maxes, "green"), dict_get(power_maxes, "red"), power);
        sumpower += power;
    }

    printf("Ans: %d", total);
    printf("Sum Power: %d", sumpower);

    return 0;
}