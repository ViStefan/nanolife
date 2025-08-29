#define PERMUTATION_OVERFLOW -1

typedef struct
{
    int n;
    int size;
    int step;
    int *value;
    int *direction;
} permutation;

permutation *init(int n);
void print(permutation *p);
char *serialize(permutation *p);
int next(permutation *p);
void free_permutation(permutation *p);
int factorial(int n);
