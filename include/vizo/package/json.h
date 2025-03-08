#ifndef VIZO_JSON_H
#define VIZO_JSON_H

#define JSON_ERROR(x) { .type = JSON_TYPE_INVALID, .error = x }


typedef struct json_value json_value_t;

typedef enum json_type {
    JSON_TYPE_OBJECT,
    JSON_TYPE_ARRAY,
    JSON_TYPE_STRING,
    JSON_TYPE_NUMBER,
    JSON_TYPE_BOOL,
    JSON_TYPE_NULL,
    JSON_TYPE_INVALID
} json_type_t;

typedef enum json_result {
    JSON_ERROR_NONE,
    JSON_ERROR_INVALID,
    JSON_ERROR_UNEXPECTED,
    JSON_ERROR_UNTERMINATED,
    JSON_ERROR_INVALID_ESCAPE,
    JSON_ERROR_INVALID_UNICODE,
    JSON_ERROR_INVALID_NUMBER,
    JSON_ERROR_INVALID_STRING,
    JSON_ERROR_INVALID_ARRAY,
    JSON_ERROR_INVALID_OBJECT,
    JSON_ERROR_INVALID_KEY,
    JSON_ERROR_INVALID_VALUE,
    JSON_ERROR_INVALID_BOOL,
    JSON_ERROR_INVALID_NULL,

    JSON_ERROR_INVALID_TYPE,
    JSON_ERROR_INVALID_INDEX,
    JSON_ERROR_INVALID_KEY_NOT_FOUND,
} json_result_t;

typedef struct json_key {
    char *key;
    json_value_t *value;
} json_key_t;

typedef struct json_object {
    json_key_t *keys;
    int key_count;
} json_object_t;

typedef struct json_array {
    json_value_t **values;
    int value_count;
} json_array_t;

struct json_value {
    json_type_t type;
    union {
        json_object_t* object;
        json_array_t* array;
        char *string;
        double number;
        int bool;
        int null;
    } value;

    json_result_t error;
};

typedef struct json {
    json_value_t *value;
} json_t;

json_value_t *json_value_new(json_type_t type);
void json_value_free(json_value_t *value);

json_object_t *json_object_new(void);
json_result_t json_object_add(json_object_t *object, const char *key, json_value_t *value);
json_value_t *json_object_get(json_object_t *object, const char *key);
void json_object_free(json_object_t *object);

json_array_t *json_array_new(void);
json_result_t json_array_add(json_array_t *array, json_value_t *value);
json_value_t *json_array_get(json_array_t *array, int index);
void json_array_free(json_array_t *array);



json_t *json_parse(const char *json_str);
void json_free(json_t *json);


#endif
