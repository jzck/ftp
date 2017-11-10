/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 18:08:31 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 15:56:57 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	token generator
*/
char	*ft_strtok(char *s, const char *delim)
{
	static char	*lasts;
	int			ch;

	if (s == 0)
		s = lasts;
	if ((ch = *s++) == 0)
		return (0);
	while (ft_strchr(delim, ch))
	{
		if ((ch = *s++) == 0)
			return (0);
	}
	--s;
	lasts = s + ft_strcspn(s, delim);
	if (*lasts != 0)
		*lasts++ = 0;
	return (s);
}

/*
**	also returns empty strings in the case of multiple delimiters
*/
char	*ft_strtok_single(char *str, char const *delims)
{
	static char	*src = NULL;
	char		*p;
	char		*ret = 0;

	if (str != NULL)
		src = str;
	if (src == NULL)
		return NULL;
	if ((p = strpbrk (src, delims)) != NULL) {
		*p  = 0;
		ret = src;
		src = ++p;
	}
	else if (*src)
	{
		ret = src;
		src = NULL;
	}
	return ret;
}
