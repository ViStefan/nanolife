#define PERMUTATION_OVERFLOW -1

typedef struct
{
    int n;
    unsigned long long size;
    unsigned long long step;
    int *value;
    int *direction;
} permutation;

permutation *init(int n);
void print(permutation *p);
char *serialize(permutation *p);
int next(permutation *p);
void free_permutation(permutation *p);
