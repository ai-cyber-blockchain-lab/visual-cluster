#include <stdio.h>
#include "cJSON.h"

int parse_json(const char *input, size_t length) {
    fprintf(stderr, "got json '%s'\n", input);
    fflush(stderr);
 
    cJSON *json = cJSON_Parse(input);
    if (NULL == json) {
        fprintf(stderr, "json is invalid\n");
        fflush(stderr);

        return 0;
    }
    cJSON_Delete(json);

    fprintf(stderr, "json is valid\n");
    fflush(stderr);

    return 1;
}