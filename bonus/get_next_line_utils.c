/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khouten <khouten@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 16:19:56 by khouten           #+#    #+#             */
/*   Updated: 2020/12/03 16:19:57 by khouten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clear(t_list **all_data, int fd, char *buf, int return_value)
{
	t_list	*tmp;
	t_list	*pmt;

	if (*all_data)
	{
		tmp = *all_data;
		if (tmp->fd == fd)
			*all_data = tmp->next;
		else
		{
			while (tmp->next->fd != fd)
				tmp = tmp->next;
			pmt = tmp->next;
			tmp->next = pmt->next;
			tmp = pmt;
		}
		free(tmp->ostatok);
		free(tmp);
	}
	free(buf);
	if (return_value == -1)
		return (-1);
	return (0);
}

t_list	*ft_lstnew(int content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->fd = content;
	new->next = NULL;
	new->ostatok = NULL;
	return (new);
}

char	*ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (s[0] == '\0' && s[0] == c)
		return (&s[0]);
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*b;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
		i++;
	b = (char *)malloc(sizeof(char) * (i + 1));
	if (!b)
		return (0);
	i = 0;
	while (s[i])
	{
		b[i] = s[i];
		i++;
	}
	b[i] = '\0';
	return (b);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	new = (char *)malloc((i + j) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}
