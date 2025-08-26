struct permutation
{
    int size;
    int step;
    int *value;
    int *direction;
} typedef permutation;

struct permutation_threaded
{
    permutation *perm;
    int threads;
    void (*callback)(permutation *p);
} typedef permutation_threaded;

void permutate(int number, int threads, void (*callback)(permutation *p));
permutation *init(int size);
void print(permutation *p);
void next(permutation *p);
void free_permutation(permutation *p);
int factorial(int n);
