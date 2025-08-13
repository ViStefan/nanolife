#include <stdio.h>

#define WIDTH 4
#define HEIGHT 4 

#define CHUNK_SIZE (WIDTH - 2) * (HEIGHT - 2)

int MAP[] = {
    //0, 8, 9, 1,
    //14, 4, 5, 10,
    //15, 7, 6, 11,
    //3, 13, 12, 2
    //0, 5, 3,
    //6, 4, 7,
    //2, 4, 1,
    //0, 1, 2, 3,
    //4, 5, 6, 7,
    //8, 9, 10, 11,
    //12, 13, 14, 15
    0, 1, 2, 3,
    11, 12, 13, 4,
    10, 15, 14, 5,
    9, 8, 7, 6
};

int getbit(int bits, int x, int y)
{
	if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1) return 0;
	return (bits >> MAP[x + WIDTH * y]) & 1;
}

int life(int bits, int w, int h)
{
    int neighbours = 0;

    for (int y = h - 1; y <= h + 1; ++y)
    {
        for (int x = w - 1; x <= w + 1; ++x)
        {
            neighbours += getbit(bits, x, y);
        }
    }

    int self = getbit(bits, w, h);
    neighbours -= self;

    return(neighbours == 3 || (self && neighbours == 2));
}

int life_chunk(int bits)
{	
    int out = 0;

    for (int h = 1; h < HEIGHT - 1; ++h)
    {
        for (int w = 1; w < WIDTH - 1; ++w)
        {
            out = (out << 1) | life(bits, w, h);
        }
    }
    return out;
}

void putsquare(int color)
{
    if (color)
        printf("\u2b1b");
    else
        printf("\u2b1c");
}

void pretty_print(int in, int out)
{
    for (int h = 0; h < HEIGHT; ++h)
    {
        for (int w = 0; w < WIDTH; ++w)
        {
            putsquare(getbit(in, w, h));
        }

        if (h > 0 && h < HEIGHT - 1)
        {
            if (h == (HEIGHT - 1) / 2)
                printf(" → ");
            else
                printf("   ");
            
            for (int w = 0; w < WIDTH - 2; ++w)
            {
                putsquare((out >> ((CHUNK_SIZE - 1) - (w + (h - 1) * (WIDTH - 2)))) & 1);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char **argv)
{
	long int size = 1 << (WIDTH * HEIGHT);
    int result[size];
	for (int i = 0; i < size; ++i)
	{
		printf("\n%d:\n", i);
        result[i] = life_chunk(i);
        pretty_print(i, result[i]);
	}

    int prev = result[0];
    int n = 1;
    printf("0");
    for (int i = 1; i < size; ++i)
    {
        if (result[i] != prev)
        {
            printf(", %d", i);
            prev = result[i];
            ++n;
        }
    }
    printf("\n--%d--", n);
}
