/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polymer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:33:45 by chelmerd          #+#    #+#             */
/*   Updated: 2021/12/14 13:56:44 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/gnl/get_next_line.h"
#include "../utils/libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define START_POLYMER "KKOSPHCNOCHHHSPOBKVF"

static long	simulate(int fd, int steps);
static char	*apply_rules(char *polymer, int fd);
static long	calc_answer(const char *polymer);

int	main(void)
{
	FILE	*f;
	int		fd;

	f = fopen("input", "r");
	if (!f)
		return (1);
	fd = fileno(f);
	printf("The answer for part one is: %li\n", simulate(fd, 10));
	printf("The answer for part two is: %li\n", simulate(fd, 40));
	fclose(f);
	return (0);
}

static long	simulate(int fd, int steps)
{
	char	*polymer;
	char	*tmp;
	long	answer;

	polymer = ft_strdup(START_POLYMER);
	if (!polymer)
		return (-1);
	while (steps--)
	{
		tmp = apply_rules(polymer, fd);
		free(polymer);
		polymer = tmp;
	}
	answer = calc_answer(polymer);
	free(polymer);
	return (answer);
}

static char	*apply_rules(char *polymer, int fd)
{
	char	*new;
	char	*tmp;
	char	*chunk;
	char	*rule;

	new = ft_strdup("");
	while (*(polymer+1))
	{
		lseek(fd, 0L, SEEK_SET);
		rule = get_next_line(fd);
		chunk = (char *) calloc(3, sizeof (char));
		chunk[0] = polymer[0];
		while (rule && rule[0] != '\n')
		{
			if (polymer[0] == rule[0] && polymer[1] == rule[1])
				chunk[1] = rule[6];
			free(rule);
			rule = get_next_line(fd);
		}
		tmp = ft_strjoin(new, chunk);
		free(chunk); free(new);
		new = tmp;
		polymer++;
	}
	tmp = ft_strjoin(new, polymer);
	free(new);
	new = tmp;
	free(rule);
	return (new);
}

static long	calc_answer(const char *polymer)
{
	long	tab[26];
	int	i;
	long	min;
	long	max;

	i = 0;
	while (i < 26)
	{
		tab[i++] = 0;
	}
	while (*polymer)
	{
		tab[*polymer - 'A']++;
		polymer++;
	}
	min = LONG_MAX;
	i = 0;
	while (i < 26)
	{
		if (tab[i] < min && tab[i] != 0)
			min = tab[i];
		i++;
	}
	max = tab[0];
	i = 0;
	while (i < 26)
	{
		if (tab[i] > max && tab[i] != 0)
			max = tab[i];
		i++;
	}
	return (max - min);
}
