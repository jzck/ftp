/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sstrdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:04:07 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 18:51:13 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sstrdel(char **sstr, int index)
{
	int		i;

	i = index;
	ft_strdel(&sstr[index]);
	while (i == index || sstr[i])
	{
		sstr[i] = sstr[i + 1];
		++i;
	}
}
