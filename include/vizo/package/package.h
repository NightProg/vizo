#ifndef VIZO_PACKAGE_H
#define VIZO_PACKAGE_H


#include <vizo/package/package_info.h>
#include <vizo/package/dependency.h>
#include <vizo/build/build.h>



typedef struct package {
    package_info_t *info;
    dependency_list_t *dependencies;
} package_t;


package_t *package_new();
package_t *package_from_json(json_t *json);
void package_free(package_t *package);



#endif //VIZO_PACKAGE_H
