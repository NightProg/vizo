#ifndef VIZO_JSON_H
#define VIZO_JSON_H

#define JSON_ERROR(x) { .type = JSON_TYPE_INVALID, .error = x }
#define WHITESPACE(f)     if (json_is_whitespace(json_str[*index])) {(*index)++;return f(json_str, index);}


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
    JSON_ERROR_INVALID_KEY_VALUE_SEPARATOR,

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
    json_result_t error;
} json_object_t;

typedef struct json_array {
    json_value_t **values;
    int value_count;
    json_result_t error;
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
int json_value_is_valid(json_value_t *value);
void json_value_print(json_value_t *value);
void json_value_free(json_value_t *value);

json_object_t *json_object_new(void);
json_result_t json_object_add(json_object_t *object, const char *key, json_value_t *value);
json_value_t *json_object_get(json_object_t *object, const char *key);
int json_object_is_valid(json_object_t *object);
void json_object_print(json_object_t *object);
void json_object_free(json_object_t *object);

json_array_t *json_array_new(void);
json_result_t json_array_add(json_array_t *array, json_value_t *value);
json_value_t *json_array_get(json_array_t *array, int index);
int json_array_is_valid(json_array_t *array);
void json_array_print(json_array_t *array);
void json_array_free(json_array_t *array);






json_t *json_parse(const char *json_str);
json_t *json_parse_file(const char *file_path);
json_value_t *json_parse_value(const char *json_str, json_type_t type, int *index);
json_value_t *json_parse_any_value(const char *json_str, int *index);
json_object_t *json_parse_object(const char *json_str, int *index);
json_array_t *json_parse_array(const char *json_str, int *index);
char* json_parse_string(const char *json_str, int *index);
double json_parse_number(const char *json_str, int *index);
int json_parse_bool(const char *json_str, int *index);
int json_parse_null(const char *json_str, int *index);
int json_is_whitespace(char c);
void json_free(json_t *json);


#endif
