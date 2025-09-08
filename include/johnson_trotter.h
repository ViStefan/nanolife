#define PERMUTATION_OVERFLOW -1

typedef struct
{
    int n;
    unsigned long long size;
    unsigned long long step;
    int *value;
    int *direction;
} permutation_t;

permutation_t *permutation_init(int n);
void permutation_print(permutation_t *p);
char *permutation_serialize(permutation_t *p);
int permutation_next(permutation_t *p, int n);
void free_permutation(permutation_t *p);
