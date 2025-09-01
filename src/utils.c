unsigned long long factorial(int n)
{
    int r = 1;
    do
    {
        r *= n;
    } while (--n);
    return r;
}

// how many chars you need to store "1, 2, 3, ..., n"?
int sequence_string_length(int n)
{
	if (n < 10)
		return n * 3 * sizeof(char);
	return 30 + (4 * (n - 10)) * sizeof(char);
}
