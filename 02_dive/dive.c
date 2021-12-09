/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dive.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:42:26 by chelmerd          #+#    #+#             */
/*   Updated: 2021/12/03 11:34:16 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/gnl/get_next_line.h"
#include "../utils/libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

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
	printf("The answer for part one is: %i\n", part1(fd));
	fclose(f);
	f = fopen("input", "r");
	if (!f)
		return (1);
	fd = fileno(f);
	printf("The answer for part two is: %i\n", part2(fd));
	fclose(f);
	return (0);
}

static int	part1(int fd)
{
	int		pos_h;
	int		pos_d;
	char	*cmd;
	char	**inst;

	pos_h = 0;
	pos_d = 0;
	cmd = get_next_line(fd);
	while (cmd)
	{
		inst = ft_split(cmd, ' ');
		if (!ft_strncmp(inst[0], "forward", ft_strlen(inst[0])))
			pos_h += ft_atoi(inst[1]);
		else if (!ft_strncmp(inst[0], "down", ft_strlen(inst[0])))
			pos_d += ft_atoi(inst[1]);
		else if (!ft_strncmp(inst[0], "up", ft_strlen(inst[0])))
			pos_d -= ft_atoi(inst[1]);
		cmd = get_next_line(fd);
	}
	return (pos_h * pos_d);
}

static int	part2(int fd)
{
	int		pos_h;
	int		pos_d;
	int		aim;
	char	*cmd;
	char	**inst;

	pos_h = 0;
	pos_d = 0;
	aim = 0;
	cmd = get_next_line(fd);
	while (cmd)
	{
		inst = ft_split(cmd, ' ');
		if (!ft_strncmp(inst[0], "forward", ft_strlen(inst[0])))
		{
			pos_h += ft_atoi(inst[1]);
			pos_d += aim * ft_atoi(inst[1]);
		}
		else if (!ft_strncmp(inst[0], "down", ft_strlen(inst[0])))
			aim += ft_atoi(inst[1]);
		else if (!ft_strncmp(inst[0], "up", ft_strlen(inst[0])))
			aim -= ft_atoi(inst[1]);
		cmd = get_next_line(fd);
	}
	return (pos_h * pos_d);
}
