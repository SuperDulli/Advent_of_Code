/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fish.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chelmerd <chelmerd@student.wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:06:35 by chelmerd          #+#    #+#             */
/*   Updated: 2021/12/10 11:11:04 by chelmerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/gnl/get_next_line.h"
#include "../utils/libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

static t_list	*create_list(char *str);
static t_list	*copy_list(t_list *l);
static int		part1(t_list *start);

int	main(void)
{
	FILE	*f;
	int		fd;
	char	*line;
	t_list	*list;

	f = fopen("input", "r");
	if (!f)
		return (1);
	fd = fileno(f);
	line = get_next_line(fd);
	while (line)
	{
		list = create_list(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	fclose(f);
	printf("list len=%i\n", ft_lstsize(list));
	printf("Answer part1= %i", part1(list));
	ft_lstclear(&list, free);
	free(list);
	return (0);
}

static t_list	*create_list(char *str)
{
	t_list	*l;
	char	**tab;
	char	**tab_start;
	char	*nbr;

	l = NULL;
	str[ft_strlen(str) - 1] = '\0';
	tab = ft_split(str, ',');
	if (!tab)
		return (NULL);
	tab_start = tab;
	nbr = *tab;
	while (nbr)
	{
		ft_lstadd_back(&l, ft_lstnew(nbr));
		nbr = *(++tab);
	}
	free(tab_start);
	return (l);
}

static int	part1(t_list *start)
{
	int		days;
	t_list	*list;
	t_list	*list_start;
	int		size;

	days = 80;
	list = copy_list(start);
	list_start = list;
	while (days)
	{
		size = ft_lstsize(list);
		while (size)
		{
			if (!ft_strncmp((char *) list->content, "0", 1))
				ft_lstadd_back(&list, ft_lstnew(ft_strdup("8")));
			else
				((char *) list->content)[0]--;
			list = list->next;
			size--;
		}
		list = list_start;
		days--;
	}
	return (ft_lstsize(list));
}

static t_list	*copy_list(t_list *l)
{
	t_list	*copy;

	copy = NULL;
	while (l->next)
	{
		ft_lstadd_back(&copy, ft_lstnew(ft_strdup(l->content)));
		l = l->next;
	}
	return (copy);
}
