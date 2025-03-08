#ifndef VIZO_PACKAGE_INFO_H
#define VIZO_PACKAGE_INFO_H

#include <vizo/package/json.h>

#define PACKAGE_BUILD_TOOL_DEFAULT BUILD_TOOL_MAKE
#define PACKAGE_BUILD_TYPE_DEFAULT BUILD_TYPE_DEBUG

#define PACKAGE_INFO_DESERIALIZE_ERROR(x) (void*) -PACKAGE_INFO_DESERIALIZE_ERROR_##x


typedef enum package_info_deserialize_error {
    PACKAGE_INFO_DESERIALIZE_ERROR_INVALID,
    PACKAGE_INFO_DESERIALIZE_ERROR_EXPECTED_OBJECT,
    PACKAGE_INFO_DESERIALIZE_ERROR_EXPECTED_STRING,

} package_info_deserialize_error_t;

typedef enum package_build_type {
    BUILD_TYPE_DEBUG,
    BUILD_TYPE_RELEASE
} package_build_type_t;

typedef enum package_build_tool {
    BUILD_TOOL_CMAKE,
    BUILD_TOOL_MAKE,
    BUILD_TOOL_NINJA
} package_build_tool_t;

typedef struct package_info {
    char *name;
    char *version;
    char *description;
    char *author;
    char *license;
    package_build_tool_t build_tool;
} package_info_t;

package_info_t *package_info_new(void);
void package_info_free(package_info_t *package_info);

package_info_t *package_info_from_json(json_t *json);




#endif //VIZO_PACKAGE_INFO_H
