intern u64
hash_str(const char* str) {
    u64 hash = 14695981039346656037ULL; // FNV offset basis
    i32 c;
    while ((c = *str++)) {
        hash ^= (u64)c;
        hash *= 1099511628211ULL; // FNV prime
    }
    return hash;
}

// Macros
#define __HASH_NEW_CONTAINER(T) \
    struct __Hash_##T##_Container {\
        u64 key;\
        T data;\
        struct __Hash_##T##_Container* next;\
    };

#define __HASH_GET_FUNC(T, n) \
    intern T hash_get_##n(const char* key) {\
        u64 hash = hash_str(key);\
        struct __Hash_##T##_Container* curr = &__##n##_bucket_root;\
        while(curr != NULL){\
            if(hash == curr->key)\
                return curr->data;\
            curr = curr->next;\
        }\
        return (T){0};\
    }

#define __HASH_INSERT_FUNC(T, n) \
    intern void hash_insert_##n(const char* key, T data) {\
        u64 hash = hash_str(key);\
        struct __Hash_##T##_Container* curr = &__##n##_bucket_root;\
        while (curr != NULL) {\
            if (curr->key == hash) {\
                curr->data = data;\
                return;\
            }\
            if (curr->next == NULL) {\
                curr->next = (struct __Hash_##T##_Container*)malloc(sizeof(struct __Hash_##T##_Container));\
                curr = curr->next;\
                curr->key = hash;\
                curr->data = data;\
                curr->next = NULL;\
                return;\
            }\
            curr = curr->next;\
        }\
    }

#define __HASH_DELETE_FUNC(T, n) \
    intern void hash_delete_##n(const char* key) {\
        u64 hash = hash_str(key);\
        struct __Hash_##T##_Container* curr = &__##n##_bucket_root;\
        struct __Hash_##T##_Container* last = NULL;\
        while (curr != NULL) {\
            if (curr->key == hash) {\
                if (last != NULL)\
                    last->next = curr->next;\
                free((void*)curr);\
                return;\
            }\
            last = curr;\
            curr = curr->next;\
        }\
    }

#define HASHMAP(T, name) \
    __HASH_NEW_CONTAINER(T)\
    global struct __Hash_##T##_Container __##name##_bucket_root = {0, 0, NULL};\
    __HASH_GET_FUNC(T, name)\
    __HASH_INSERT_FUNC(T, name)\
    __HASH_DELETE_FUNC(T, name)