#ifndef VIZO_PACKAGE_H
#define VIZO_PACKAGE_H


#include <vizo/package/package_info.h>
#include <vizo/package/dependency.h>



typedef struct package {
    package_info_t *info;
    dependency_list_t *dependencies;

} package_t;


#endif //VIZO_PACKAGE_H
