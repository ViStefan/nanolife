#define PERMUTATION_OVERFLOW -1

typedef struct
{
    int n;
    unsigned long long size;
    unsigned long long step;
    int *value;
    int *direction;
} permutation_t;

permutation_t *init(int n);
void print(permutation_t *p);
char *serialize(permutation_t *p);
int next(permutation_t *p);
void free_permutation(permutation_t *p);
