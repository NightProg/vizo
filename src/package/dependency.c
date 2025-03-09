#include <vizo/package/dependency.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


dependency_source_t *dependency_source_new(void) {
    dependency_source_t *source = malloc(sizeof(dependency_source_t));
    if (source == NULL) {
        return NULL;
    }

    source->type = DEPENDENCY_SOURCE_GIT;
    source->url = NULL;

    return source;
}

dependency_source_t *dependency_source_new_git(const char *url) {
    dependency_source_t *source = dependency_source_new();
    if (source == NULL) {
        return NULL;
    }

    source->type = DEPENDENCY_SOURCE_GIT;
    source->url = strdup(url);

    return source;
}

dependency_source_t *dependency_source_new_http(const char *url) {
    dependency_source_t *source = dependency_source_new();
    if (source == NULL) {
        return NULL;
    }

    source->type = DEPENDENCY_SOURCE_HTTP;
    source->url = strdup(url);

    return source;
}

dependency_source_t *dependency_source_new_local(const char *path) {
    dependency_source_t *source = dependency_source_new();
    if (source == NULL) {
        return NULL;
    }

    source->type = DEPENDENCY_SOURCE_LOCAL;
    source->url = strdup(path);

    return source;
}

dependency_source_t *dependency_source_new_version(const char *version) {
    dependency_source_t *source = dependency_source_new();
    if (source == NULL) {
        return NULL;
    }

    source->type = DEPENDENCY_SOURCE_VERSION;
    source->url = strdup(version);

    return source;
}

dependency_source_t *dependency_source_parse(const char *source_str) {
    if (source_str == NULL) {
        return NULL;
    }

    dependency_source_t *source = dependency_source_new();
    if (source == NULL) {
        return NULL;
    }

    if (strncmp(source_str, "git+", 4) == 0) {
        source->type = DEPENDENCY_SOURCE_GIT;
        source->url = strdup(source_str + 4);
    } else if (strncmp(source_str, "http+", 5) == 0) {
        source->type = DEPENDENCY_SOURCE_HTTP;
        source->url = strdup(source_str + 5);
    } else if (strncmp(source_str, "local+", 6) == 0) {
        source->type = DEPENDENCY_SOURCE_LOCAL;
        source->url = strdup(source_str + 6);
    } else {
        source->type = DEPENDENCY_SOURCE_VERSION;
        source->url = strdup(source_str);
    }

    return source;
}

void dependency_source_print(dependency_source_t *source) {
    if (source == NULL) {
        return;
    }

    switch (source->type) {
        case DEPENDENCY_SOURCE_GIT:
            printf("git+%s", source->url);
            break;
        case DEPENDENCY_SOURCE_HTTP:
            printf("http+%s", source->url);
            break;
        case DEPENDENCY_SOURCE_LOCAL:
            printf("local+%s", source->url);
            break;
        case DEPENDENCY_SOURCE_VERSION:
            printf("%s", source->url);
            break;
        default:
            break;
    }
}

const char *dependency_source_type_to_string(dependency_source_type_t type) {
    switch (type) {
        case DEPENDENCY_SOURCE_GIT:
            return "git";
        case DEPENDENCY_SOURCE_HTTP:
            return "http";
        case DEPENDENCY_SOURCE_LOCAL:
            return "local";
        case DEPENDENCY_SOURCE_VERSION:
            return "version";
        default:
            return "unknown";
    }
}

void dependency_source_free(dependency_source_t *source) {
    if (source == NULL) {
        return;
    }

    if (source->url != NULL) {
        free(source->url);
    }

    free(source);
}

dependency_t *dependency_new(void) {
    dependency_t *dependency = malloc(sizeof(dependency_t));
    if (dependency == NULL) {
        return NULL;
    }

    dependency->name = NULL;
    dependency->source = NULL;

    return dependency;
}

void dependency_free(dependency_t *dependency) {
    if (dependency == NULL) {
        return;
    }

    if (dependency->name != NULL) {
        free(dependency->name);
    }

    if (dependency->source != NULL) {
        dependency_source_free(dependency->source);
    }

    free(dependency);
}

dependency_list_t *dependency_list_new(void) {
    dependency_list_t *list = malloc(sizeof(dependency_list_t));
    if (list == NULL) {
        return NULL;
    }

    list->dependencies = NULL;
    list->dependency_count = 0;

    return list;
}

int dependency_list_add(dependency_list_t *list, dependency_t *dependency) {
    if (list == NULL || dependency == NULL) {
        return 0;
    }

    dependency_t **new_dependencies = realloc(list->dependencies, sizeof(dependency_t *) * (list->dependency_count + 1));
    if (new_dependencies == NULL) {
        return 0;
    }

    list->dependencies = new_dependencies;
    list->dependencies[list->dependency_count] = dependency;
    list->dependency_count++;

    return 1;
}

dependency_t *dependency_list_get(dependency_list_t *list, int index) {
    if (list == NULL || index < 0 || index >= list->dependency_count) {
        return NULL;
    }

    return list->dependencies[index];
}

dependency_t *dependency_list_get_by_name(dependency_list_t *list, const char *name) {
    if (list == NULL || name == NULL) {
        return NULL;
    }

    for (int i = 0; i < list->dependency_count; i++) {
        if (strcmp(list->dependencies[i]->name, name) == 0) {
            return list->dependencies[i];
        }
    }

    return NULL;
}

void dependency_list_free(dependency_list_t *list) {
    if (list == NULL) {
        return;
    }

    for (int i = 0; i < list->dependency_count; i++) {
        dependency_free(list->dependencies[i]);
    }

    free(list->dependencies);
    free(list);
}