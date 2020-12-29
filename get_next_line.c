/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquordle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:51:59 by dquordle          #+#    #+#             */
/*   Updated: 2020/11/18 13:58:53 by dquordle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinf(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	j = ft_strlen(s2);
	i = ft_strlen(s1);
	if (!(res = (char *)malloc(i + j + 1)))
		return (NULL);
	res[0] = '\0';
	ft_strlcat(res, s1, i + 1);
	ft_strlcat(res, s2, i + j + 1);
	free(s1);
	return (res);
}

void	ft_trimstart(char *dst, char *src)
{
	int i;

	if (src == NULL)
		return ;
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

int		ft_reading(char **rem, char **line, int fd)
{
	char	*buf;
	int		check;

	while (!(buf = ft_strchr(*rem, '\n')))
	{
		if (!(*line = ft_strjoinf(*line, *rem)))
		{
			free(*rem);
			return (-1);
		}
		if(!(check = read(fd, *rem, 9999)))
		{
			free(*rem);
			return (0);
		}
		(*rem)[check] = 0;
	}
	*buf = 0;
	if (!(*line = ft_strjoinf(*line, *rem)))
		return (-1);
	ft_trimstart(*rem, buf + 1);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*rem = NULL;
	char		*buf;
	int			check;

	if (!line || (read(fd, buf, 0) == -1) || !(*line = ft_strdup("")))
		return (-1);
	if (!rem)
	{
		if(!(rem = (char *)malloc(10000)))
			return (-1);
		check = read(fd, rem, 9999);
		rem[check] = 0;
	}
	return (ft_reading(&rem, line, fd));
}
