/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:42:12 by gemartin          #+#    #+#             */
/*   Updated: 2022/03/02 14:36:32 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*clean_storage(char *storage)
{
	char	*new_storage;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	if (!ptr)
	{
		free(storage);
		new_storage = NULL;
		return (NULL);
	}
	else
		len = (ptr - storage) + 1;
	if (!storage[len])
	{
		free(storage);
		return (NULL);
	}
	new_storage = ft_substr(storage, len, ft_strlen(storage) - len);
	if (!new_storage)
		return(NULL);
	free(storage);
	return (new_storage);
}

char	*new_line(char *storage)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(storage, '\n');
	len = (ptr - storage) + 1;
	line = ft_substr(storage, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*readbuf(int fd, char *storage)
{
	int		rid;
	char	*buffer;

	rid = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	buffer[0] = '\0';
	while (rid > 0 && !ft_strchr(buffer, '\n'))
	{
		rid = read (fd, buffer, BUFFER_SIZE);
		if (rid == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (rid > 0)
		{
			buffer[rid] = '\0';
			storage = ft_strjoin(storage, buffer);
		}
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((storage[fd] && !ft_strchr(storage[fd], '\n')) || !storage[fd])
		storage[fd] = readbuf (fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = new_line(storage[fd]);
	if (!line)
	{
		free(storage[fd]);
		return (NULL);
	}
	storage[fd] = clean_storage(storage[fd]);
	return (line);
}
