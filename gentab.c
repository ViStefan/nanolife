#include <stdio.h>

#define WIDTH 3
#define HEIGHT 3

int MAP[] = {0, 1, 2, 3, 4, 5, 6, 7};

int getbit(int bits, int n)
{
	if (n < 0 || n > WIDTH * HEIGHT) return 0;
	return (bits >> MAP[n]) & 1;
}

int main(int argc, char **argv)
{
	long int size = 1 << (WIDTH * HEIGHT);
	for (int i = 0; i < size - 1; ++i)
	{
		printf("\n%d:\n", i);

		for (int h = 0; h < HEIGHT; ++h)
			for (int w = 0; w < WIDTH; ++w)
			{
				printf("\n(%d, %d):\n", w, h);

				for (int y = h - 1; y <= h + 1; ++y)
				{
					for (int x = w - 1; x <= w + 1; ++x)
					{
						int n = (w - x) + ((h + y) * WIDTH);
						if (getbit(i, n))
							printf("⬛");
						else
							printf("⬜");

					}
					printf("\n");
				}
			}
	}
}
