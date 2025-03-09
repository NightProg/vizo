#include <vizo/package/package_info.h>
#include <stdlib.h>
#include <string.h>

package_info_t *package_info_new(void) {
    package_info_t *package_info = malloc(sizeof(package_info_t));
    if (package_info == NULL) {
        return NULL;
    }

    package_info->name = NULL;
    package_info->version = NULL;
    package_info->description = NULL;
    package_info->author = NULL;
    package_info->license = NULL;
    package_info->build_tool = PACKAGE_BUILD_TOOL_DEFAULT;

    return package_info;
}


void package_info_free(package_info_t *package_info) {
    if (package_info == NULL) {
        return;
    }

    if (package_info->name != NULL) {
        free(package_info->name);
    }

    if (package_info->version != NULL) {
        free(package_info->version);
    }

    if (package_info->description != NULL) {
        free(package_info->description);
    }

    if (package_info->author != NULL) {
        free(package_info->author);
    }

    if (package_info->license != NULL) {
        free(package_info->license);
    }

    free(package_info);
}


package_info_t *package_info_from_json(json_t *json) {
    if (json == NULL) {
        return PACKAGE_INFO_DESERIALIZE_ERROR(INVALID);
    }

    json_value_t *value = json->value;
    if (value == NULL) {
        return PACKAGE_INFO_DESERIALIZE_ERROR(INVALID);
    }

    if (value->type != JSON_TYPE_OBJECT) {
        return PACKAGE_INFO_DESERIALIZE_ERROR(EXPECTED_OBJECT);
    }

    package_info_t *package_info = package_info_new();

    json_value_t *name = json_object_get(value->value.object, "name");
    if (name != NULL && name->type == JSON_TYPE_STRING) {
        package_info->name = strdup(name->value.string);
    }

    json_value_t *version = json_object_get(value->value.object, "version");
    if (version != NULL && version->type == JSON_TYPE_STRING) {
        package_info->version = strdup(version->value.string);
    }

    json_value_t *description = json_object_get(value->value.object, "description");
    if (description != NULL && description->type == JSON_TYPE_STRING) {
        package_info->description = strdup(description->value.string);
    }

    json_value_t *author = json_object_get(value->value.object, "author");
    if (author != NULL && author->type == JSON_TYPE_STRING) {
        package_info->author = strdup(author->value.string);
    }

    json_value_t *license = json_object_get(value->value.object, "license");
    if (license != NULL && license->type == JSON_TYPE_STRING) {
        package_info->license = strdup(license->value.string);
    }

    json_value_t *build_tool = json_object_get(value->value.object, "build-tool");
    if (build_tool != NULL && build_tool->type == JSON_TYPE_STRING) {
        if (strcmp(build_tool->value.string, "cmake") == 0) {
            package_info->build_tool = BUILD_TOOL_CMAKE;
        } else if (strcmp(build_tool->value.string, "make") == 0) {
            package_info->build_tool = BUILD_TOOL_MAKE;
        } else if (strcmp(build_tool->value.string, "ninja") == 0) {
            package_info->build_tool = BUILD_TOOL_NINJA;
        }
    }

    return package_info;
}