/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sonar_sweep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:55:23 by chelmerd          #+#    #+#             */
/*   Updated: 2021/12/03 10:41:49 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/gnl/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

int			ft_atoi(const char *s);

static int	part1(int fd);
static int	part2(int fd);

int	main(void)
{
	FILE	*f;
	int		fd;

	f = fopen("input", "r");
	if (!f)
		return (1);
	fd = fileno(f);
	printf("The answer for part one is:%i\n", part1(fd));
	fclose(f);
	f = fopen("input", "r");
	if (!f)
		return (1);
	fd = fileno(f);
	printf("The answer for part two is:%i\n", part2(fd));
	fclose(f);
	return (0);
}

static int	part1(int fd)
{
	int		answer;
	char	*measurement;
	int		previous;

	answer = 0;
	previous = -1;
	measurement = get_next_line(fd);
	while (measurement)
	{
		if (previous != -1 && ft_atoi(measurement) > previous)
				answer++;
		previous = ft_atoi(measurement);
		measurement = get_next_line(fd);
	}
	free(measurement);
	return (answer);
}

static void	add_m(int g[], int m, int i)
{
	int	j;

	j = 0;
	while (j <= 3)
	{
		if (i < 3 || (i + 1) % 4 != j)
			g[j] += m;
		j++;
	}
}

/* TODO: fix me */
static int	part2(int fd)
{
	int		answer;
	int		i;
	char	*measurement;
	int		m;
	int		groups[4];

	answer = 0;
	i = 0;
	measurement = get_next_line(fd);
	while (measurement)
	{
		m = ft_atoi(measurement);
		if (3 < i && i <= 2000)
		{
			if ((i % 4 < 3 && groups[(i % 4) + 1] > groups[i % 4])
				|| (i % 4 == 3 && groups[0] > groups[3]))
				answer++;
		}
		groups[i % 4] = 0;
		add_m(groups, m, i);
		i++;
		measurement = get_next_line(fd);
	}
	free(measurement);
	return (answer);
}
