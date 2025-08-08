#include <stdio.h>

#define WIDTH 3
#define HEIGHT 3

int MAP[] = {
    //0, 8, 9, 1,
    //14, 4, 5, 10,
    //15, 7, 6, 11,
    //3, 13, 12, 2
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
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

void putsquare(int color)
{
    if (color)
        printf("\u2b1b");
    else
        printf("\u2b1c");
}

int main(int argc, char **argv)
{
	long int size = 1 << (WIDTH * HEIGHT);
	for (int i = 0; i < size; ++i)
	{
		printf("\n%d:\n", i);

		for (int h = 0; h < HEIGHT; ++h)
        {
			for (int w = 0; w < WIDTH; ++w)
			{
                putsquare(getbit(i, w, h));
            }

            if (h > 0 && h < HEIGHT - 1)
            {
                if (h == (HEIGHT - 1) / 2)
                    printf(" → ");
                else
                    printf("   ");
                
                for (int w = 1; w < WIDTH - 1; ++w)
                {
                    putsquare(life(i, w, h));
                }
            }

            printf("\n");
        }
	}
}
