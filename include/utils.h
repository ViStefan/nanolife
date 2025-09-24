#ifndef UTILS_H
#define UTILS_H

long long factorial(int n);
int sequence_string_length(int n);
char *serialize_sequence(int *sequence, int size);
char *serialize_array(int *array, int size, int chunk_size, int newline,
                      int tabs);

#endif /* UTILS_H */
