#include <vizo/package/json.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



json_value_t *json_value_new(json_type_t type) {
    json_value_t *value = malloc(sizeof(json_value_t));
    if (value == NULL) {
        return NULL;
    }

    value->type = type;
    value->error = JSON_ERROR_NONE;

    switch (type) {
        case JSON_TYPE_OBJECT:
            value->value.object = json_object_new();
            break;
        case JSON_TYPE_ARRAY:
            value->value.array = json_array_new();
            break;
        case JSON_TYPE_STRING:
            value->value.string = NULL;
            break;
        case JSON_TYPE_NUMBER:
            value->value.number = 0;
            break;
        case JSON_TYPE_BOOL:
            value->value.bool = 0;
            break;
        case JSON_TYPE_NULL:
            value->value.null = 0;
            break;
        default:
            value->error = JSON_ERROR_INVALID_TYPE;
            break;
    }

    return value;
}

int json_value_is_valid(json_value_t *value) {
    if (value == NULL || value->error != JSON_ERROR_NONE) {
        return 0;
    }

    switch (value->type) {
        case JSON_TYPE_OBJECT:
            return json_object_is_valid(value->value.object);
        case JSON_TYPE_ARRAY:
            return json_array_is_valid(value->value.array);
        case JSON_TYPE_STRING:
            return value->value.string != NULL;
        case JSON_TYPE_NUMBER:
            return 1;
        case JSON_TYPE_BOOL:
            return value->value.bool == 0 || value->value.bool == 1;
        case JSON_TYPE_NULL:
            return value->value.null == 1;
        default:
            return 0;
    }
}

void json_value_print(json_value_t *value) {
    if (value == NULL) {
        return;
    }

    switch (value->type) {
        case JSON_TYPE_OBJECT:
            json_object_print(value->value.object);
            break;
        case JSON_TYPE_ARRAY:
            json_array_print(value->value.array);
            break;
        case JSON_TYPE_STRING:
            printf("\"%s\"", value->value.string);
            break;
        case JSON_TYPE_NUMBER:
            printf("%f", value->value.number);
            break;
        case JSON_TYPE_BOOL:
            printf("%s", value->value.bool ? "true" : "false");
            break;
        case JSON_TYPE_NULL:
            printf("null");
            break;
        default:
            break;
    }
}

void json_value_free(json_value_t *value) {
    if (value == NULL) {
        return;
    }

    switch (value->type) {
        case JSON_TYPE_OBJECT:
            json_object_free(value->value.object);
            break;
        case JSON_TYPE_ARRAY:
            json_array_free(value->value.array);
            break;
        default:
            break;
    }

    free(value);
}

json_object_t *json_object_new(void) {
    json_object_t *object = malloc(sizeof(json_object_t));
    if (object == NULL) {
        return NULL;
    }

    object->keys = NULL;
    object->key_count = 0;
    object->error = JSON_ERROR_NONE;

    return object;
}

json_result_t json_object_add(json_object_t *object, const char *key, json_value_t *value) {
    if (object == NULL || key == NULL || value == NULL || !json_object_is_valid(object)) {
        return JSON_ERROR_INVALID_VALUE;
    }

    json_key_t *keys = realloc(object->keys, sizeof(json_key_t) * (object->key_count + 1));
    if (keys == NULL) {
        return JSON_ERROR_INVALID_VALUE;
    }

    object->keys = keys;
    object->keys[object->key_count].key = strdup(key);
    object->keys[object->key_count].value = value;
    object->key_count++;

    return JSON_ERROR_NONE;
}

json_value_t *json_object_get(json_object_t *object, const char *key) {
    if (object == NULL || key == NULL || !json_object_is_valid(object)) {
        return NULL;
    }

    for (int i = 0; i < object->key_count; i++) {
        if (strcmp(object->keys[i].key, key) == 0) {
            return object->keys[i].value;
        }
    }

    return NULL;
}

int json_object_is_valid(json_object_t *object) {
    if (object == NULL || object->error != JSON_ERROR_NONE) {
        return 0;
    }

    for (int i = 0; i < object->key_count; i++) {
        if (object->keys[i].key == NULL || object->keys[i].value == NULL) {
            return 0;
        }

        if (!json_value_is_valid(object->keys[i].value)) {
            return 0;
        }
    }

    return 1;

}

void json_object_print(json_object_t *object) {
    if (object == NULL) {
        return;
    }

    printf("{");
    for (int i = 0; i < object->key_count; i++) {
        printf("\"%s\": ", object->keys[i].key);
        json_value_print(object->keys[i].value);
        if (i < object->key_count - 1) {
            printf(", ");
        }
    }
    printf("}");
}

void json_object_free(json_object_t *object) {
    if (object == NULL) {
        return;
    }

    for (int i = 0; i < object->key_count; i++) {
        free(object->keys[i].key);
        json_value_free(object->keys[i].value);
    }

    free(object->keys);
    free(object);
}

json_array_t *json_array_new(void) {
    json_array_t *array = malloc(sizeof(json_array_t));
    if (array == NULL) {
        return NULL;
    }

    array->values = NULL;
    array->value_count = 0;
    array->error = JSON_ERROR_NONE;

    return array;
}

json_result_t json_array_add(json_array_t *array, json_value_t *value) {
    if (array == NULL || value == NULL) {
        return JSON_ERROR_INVALID_VALUE;
    }

    json_value_t **values = realloc(array->values, sizeof(json_value_t*) * (array->value_count + 1));
    if (values == NULL) {
        return JSON_ERROR_INVALID_VALUE;
    }

    array->values = values;
    array->values[array->value_count] = value;
    array->value_count++;

    return JSON_ERROR_NONE;
}

json_value_t *json_array_get(json_array_t *array, int index) {
    if (array == NULL || index < 0 || index >= array->value_count) {
        return NULL;
    }

    return array->values[index];
}

int json_array_is_valid(json_array_t *array) {
    if (array == NULL || array->error != JSON_ERROR_NONE) {
        return 0;
    }

    for (int i = 0; i < array->value_count; i++) {
        if (!json_value_is_valid(array->values[i])) {
            return 0;
        }
    }

    return 1;
}

void json_array_print(json_array_t *array) {
    if (array == NULL) {
        return;
    }

    printf("[");
    for (int i = 0; i < array->value_count; i++) {
        json_value_print(array->values[i]);
        if (i < array->value_count - 1) {
            printf(", ");
        }
    }
    printf("]");
}

void json_array_free(json_array_t *array) {
    if (array == NULL) {
        return;
    }

    for (int i = 0; i < array->value_count; i++) {
        json_value_free(array->values[i]);
    }

    free(array->values);
    free(array);
}



json_t *json_parse(const char *json_str) {
    int index = 0;
    if (json_str == NULL) {
        return NULL;
    }

    json_t *json = malloc(sizeof(json_t));
    if (json == NULL) {
        return NULL;
    }

    json->value = json_parse_value(json_str, JSON_TYPE_OBJECT, &index);
    if (json->value == NULL) {
        free(json);
        return NULL;
    }

    return json;
}

json_value_t *json_parse_value(const char *json_str, json_type_t type, int *index) {
    if (json_str == NULL || index == NULL) {
        return NULL;
    }

    if (json_is_whitespace(json_str[*index])) {
        (*index)++;
        return json_parse_value(json_str, type, index);
    }

    json_value_t *value = json_value_new(type);
    if (value == NULL) {
        return NULL;
    }

    switch (type) {
        case JSON_TYPE_OBJECT:
            value->value.object = json_parse_object(json_str, index);
            if (value->value.object == NULL) {
                value->error = JSON_ERROR_INVALID_VALUE;
            } else if (value->value.object->error != JSON_ERROR_NONE) {
                value->error = value->value.object->error;
            }
            break;
        case JSON_TYPE_ARRAY:
            value->value.array = json_parse_array(json_str, index);
            if (value->value.array == NULL) {
                value->error = JSON_ERROR_INVALID_VALUE;
            } else if (value->value.array->error != JSON_ERROR_NONE) {
                value->error = value->value.array->error;
            }
            break;
        case JSON_TYPE_STRING:
            value->value.string = json_parse_string(json_str, index);
            if (value->value.string == NULL) {
                value->error = JSON_ERROR_INVALID_STRING;
            }
            break;
        case JSON_TYPE_NUMBER:
            value->value.number = json_parse_number(json_str, index);
            break;
        case JSON_TYPE_BOOL:
            value->value.bool = json_parse_bool(json_str, index);
            if (value->value.bool == -1) {
                value->error = JSON_ERROR_INVALID_BOOL;
            }
            break;
        case JSON_TYPE_NULL:
            value->value.null = json_parse_null(json_str, index);
            if (value->value.null == -1) {
                value->error = JSON_ERROR_INVALID_NULL;
            }
            break;
        default:
            value->error = JSON_ERROR_INVALID_TYPE;
            break;
    }

    return value;
}

char* json_parse_string(const char *json_str, int *index) {
    if (json_str == NULL || index == NULL) {
        return NULL;
    }

    WHITESPACE(json_parse_string)

    if (json_str[*index] != '"') {
        return NULL;
    }

    (*index)++;

    int start = *index;
    int end = start;

    while (json_str[end] != '"') {
        end++;
    }

    *index = end + 1;

    return strndup(json_str + start, end - start);
}

json_array_t *json_parse_array(const char *json_str, int *index) {
    if (json_str == NULL || index == NULL) {
        return NULL;
    }

    WHITESPACE(json_parse_array)

    json_array_t *array = json_array_new();
    if (array == NULL) {
        return NULL;
    }

    if (json_str[*index] != '[') {
        array->error = JSON_ERROR_INVALID_ARRAY;
        return array;
    }

    (*index)++;

    while (json_str[*index] != ']') {
        json_value_t *value = json_parse_any_value(json_str, index);
        if (value == NULL) {
            array->error = JSON_ERROR_INVALID_VALUE;
            return array;
        } else if (value->error != JSON_ERROR_NONE) {
            array->error = value->error;
            return array;
        }

        json_array_add(array, value);

        if (json_str[*index] == ',') {
            (*index)++;
        } else if (json_str[*index] != ']') {
            array->error = JSON_ERROR_INVALID_ARRAY;
            return array;
        } else {
            break;
        }


    }

    (*index)++;

    return array;
}

json_object_t *json_parse_object(const char *json_str, int *index) {
    if (json_str == NULL || index == NULL) {
        return NULL;
    }

    WHITESPACE(json_parse_object)

    json_object_t *object = json_object_new();
    if (object == NULL) {
        return NULL;
    }

    if (json_str[*index] != '{') {
        object->error = JSON_ERROR_INVALID_OBJECT;
        return object;
    }

    (*index)++;

    while (json_str[*index] != '}') {
        char *key = json_parse_string(json_str, index);
        if (key == NULL) {
            object->error = JSON_ERROR_INVALID_KEY;
            return object;
        }

        if (json_str[*index] != ':') {
            object->error = JSON_ERROR_INVALID_KEY_VALUE_SEPARATOR;
            return object;
        }

        (*index)++;

        json_value_t *value = json_parse_any_value(json_str, index);
        if (value == NULL) {
            object->error = JSON_ERROR_INVALID_VALUE;
            return object;
        } else if (value->error != JSON_ERROR_NONE) {
            object->error = value->error;
            return object;
        }

        json_object_add(object, key, value);

        if (json_str[*index] == ',') {
            (*index)++;
        } else if (json_str[*index] != '}') {
            object->error = JSON_ERROR_INVALID_OBJECT;
            return object;
        } else {
            break;
        }
    }

    (*index)++;

    return object;
}

double json_parse_number(const char *json_str, int *index) {
    if (json_str == NULL || index == NULL) {
        return 0;
    }

    WHITESPACE(json_parse_number)

    int start = *index;
    int end = start;

    while (json_str[end] >= '0' && json_str[end] <= '9') {
        end++;
    }

    *index = end;

    return strtod(json_str + start, NULL);
}

int json_parse_bool(const char *json_str, int *index) {
    if (json_str == NULL || index == NULL) {
        return -1;
    }

    WHITESPACE(json_parse_bool)

    if (strncmp(json_str + *index, "true", 4) == 0) {
        *index += 4;
        return 1;
    } else if (strncmp(json_str + *index, "false", 5) == 0) {
        *index += 5;
        return 0;
    }

    return -1;
}

int json_parse_null(const char *json_str, int *index) {
    if (json_str == NULL || index == NULL) {
        return -1;
    }
    WHITESPACE(json_parse_null)


    if (strncmp(json_str + *index, "null", 4) == 0) {
        *index += 4;
        return 1;
    }

    return -1;
}

json_value_t *json_parse_any_value(const char *json_str, int *index) {
    if (json_str == NULL || index == NULL) {
        return NULL;
    }
    WHITESPACE(json_parse_any_value)


    if (json_str[*index] == '{') {
        return json_parse_value(json_str, JSON_TYPE_OBJECT, index);
    } else if (json_str[*index] == '[') {
        return json_parse_value(json_str, JSON_TYPE_ARRAY, index);
    } else if (json_str[*index] == '"') {
        return json_parse_value(json_str, JSON_TYPE_STRING, index);
    } else if (json_str[*index] >= '0' && json_str[*index] <= '9') {
        return json_parse_value(json_str, JSON_TYPE_NUMBER, index);
    } else if (strncmp(json_str + *index, "true", 4) == 0 || strncmp(json_str + *index, "false", 5) == 0) {
        return json_parse_value(json_str, JSON_TYPE_BOOL, index);
    } else if (strncmp(json_str + *index, "null", 4) == 0) {
        return json_parse_value(json_str, JSON_TYPE_NULL, index);
    }

    return NULL;
}

int json_is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

