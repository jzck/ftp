/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sstrfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 11:53:36 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 18:51:28 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sstrfree(char **sstr)
{
	int		i;

	i = 0;
	if (sstr)
	{
		while (sstr[i])
		{
			ft_strdel(sstr + i);
			i++;
		}
		ft_strdel(sstr + i);
		free(sstr);
	}
}
