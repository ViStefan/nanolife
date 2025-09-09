#define USAGE \
    { \
        usage(__ARGV__[0]); \
        exit(__ARG__ + 1); \
    }

#define ARGS_INIT(argc, argv, n) \
    int __ARG__ = 0; \
    char **__ARGV__ = argv; \
    if (argc < n + 1) \
        USAGE \
    ++__ARG__;

#define PARSE_UINT(name) \
    unsigned int name; \
    if (parse_uint(__ARGV__[__ARG__], &name)) \
        USAGE \
    ++__ARG__;

#define PARSE_PAIR(left, right) \
    unsigned int left, right; \
    if (parse_pair(__ARGV__[__ARG__], &left, &right)) \
        USAGE \
    ++__ARG__;

#define __ARG_STR(x) #x
#define __ARG_EQ(x) x

#define ENUM(NAME) \
    enum NAME \
    { \
        NAME(__ARG_EQ) \
    };

#define PARSE_ENUM(TYPE, name) \
    enum TYPE name; \
    if (parse_enum(__ARGV__[__ARG__], (int *)&name, TYPE(__ARG_STR), NULL)) \
        USAGE \
    ++__ARG__;

#define PARSE_ARRAY(name, size) \
    int name[size]; \
    if (parse_array(__ARGV__[__ARG__], size, (int *)&name)) \
        USAGE \
    ++__ARG__;
    
int parse_pair(char *arg, unsigned int *left, unsigned int *right);
int parse_uint(char *arg, unsigned int *n);
int parse_enum(char *arg, int *value, ...);
int parse_array(char *arg, int size, int *value);
