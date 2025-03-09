#ifndef VIZO_DEPENDENCY_H
#define VIZO_DEPENDENCY_H


typedef enum dependency_source_type {
    DEPENDENCY_SOURCE_GIT,
    DEPENDENCY_SOURCE_HTTP,
    DEPENDENCY_SOURCE_LOCAL,
    DEPENDENCY_SOURCE_VERSION
} dependency_source_type_t;

typedef struct dependency_source {
    dependency_source_type_t type;
    char *url;
} dependency_source_t;


typedef struct dependency {
    char *name;
    dependency_source_t *source;
} dependency_t;


typedef struct dependency_list {
    dependency_t **dependencies;
    int dependency_count;
} dependency_list_t;

dependency_source_t *dependency_source_new(void);
dependency_source_t *dependency_source_new_git(const char *url);
dependency_source_t *dependency_source_new_http(const char *url);
dependency_source_t *dependency_source_new_local(const char *path);
dependency_source_t *dependency_source_new_version(const char *version);

dependency_source_t *dependency_source_parse(const char *source_str);
void dependency_source_print(dependency_source_t *source);
const char *dependency_source_type_to_string(dependency_source_type_t type);

void dependency_source_free(dependency_source_t *source);

dependency_t *dependency_new(void);
void dependency_free(dependency_t *dependency);

dependency_list_t *dependency_list_new(void);
int dependency_list_add(dependency_list_t *list, dependency_t *dependency);
dependency_t *dependency_list_get(dependency_list_t *list, int index);
dependency_t *dependency_list_get_by_name(dependency_list_t *list, const char *name);
void dependency_list_free(dependency_list_t *list);



#endif //VIZO_DEPENDENCY_H
