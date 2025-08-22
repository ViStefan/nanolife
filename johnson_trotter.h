struct permutation
{
    int size;
    int step;
    int *value;
    int *direction;
} typedef permutation;

permutation *init(int size);
void print(permutation *p);
void next(permutation *p);
void free_permutation(permutation *p);
int factorial(int n);
