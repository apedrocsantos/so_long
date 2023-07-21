  typedef struct  s_point
  {
    int           x;
    int           y;
  }               t_point;


#include <stdlib.h>
#include <stdio.h>

int check_map(char **tab, t_point size, t_point begin);

char** make_area(char** zone, t_point size)
{
	char** new;

	new = malloc(sizeof(char*) * size.y);
	for (int i = 0; i < size.y; ++i)
	{
		new[i] = malloc(size.x + 1);
		for (int j = 0; j < size.x; ++j)
			new[i][j] = zone[i][j];
		new[i][size.x] = '\0';
	}

	return new;
}

int main(void)
{
	t_point size = {8, 5};
	char *zone[] = {
		"11111111",
		"1PE01001",
		"1CC10001",
		"10110001",
		"11100001",
	};

	char**  area = make_area(zone, size);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	printf("\n");

	t_point begin = {1, 2};
	printf("FF return value: %d\n", check_map(area, size, begin));
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	return (0);
}
