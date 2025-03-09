#include <vizo/package/json.h>
#include <stdio.h>

int main(void) {
    json_t *json = json_parse("{\"name\": \"Vizo\", \"version\": \"1.0.0\"}");
    if (json == NULL) {
        printf("Failed to parse JSON (json is null)\n");
        return 1;
    }

    json_value_t *value = json->value;
    if (value == NULL) {
        printf("Failed to parse JSON (value is null)\n");
        return 1;
    }

    json_object_t *object = value->value.object;
    if (object == NULL) {
        printf("Failed to parse JSON (object is null)\n");
        return 1;
    }
    json_value_t *name_key = json_object_get(object, "name");
    if (name_key == NULL) {
        printf("Failed to get name key\n");
        return 1;
    }

    json_value_t *version_key = json_object_get(object, "version");
    if (version_key == NULL) {
        printf("Failed to get version key\n");
        return 1;
    }

    printf("Name: %s\n", name_key->value.string);
    printf("Version: %s\n", version_key->value.string);


    return 0;
}