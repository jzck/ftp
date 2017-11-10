/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:53:38 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 16:01:43 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	locate multiple characters in a string
*/
char	*ft_strpbrk(const char *s1, const char *s2)
{
	char	*str;

	str = (char *)s1;
	while (*str)
		if (ft_strchr(s2, *str))
			return (str);
		else
			str++;
	return (NULL);
}
