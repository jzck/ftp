/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:05:23 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/15 13:00:38 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		console_msg(int level, char *str, ...)
{
	va_list	ap;

	va_start(ap, str);
	if (g_debug >= level)
	{
		if (level == -1)
			ft_dprintf(2, "{red}");
		else if (level == 0)
			ft_dprintf(2, "{blu}");
		else if (level == 1)
			ft_dprintf(2, "{gre}");
		else
			ft_dprintf(2, "{yel}");
		ft_vdprintf(2, str, ap);
		ft_dprintf(2, "{eoc}\n");
	}
	return (level);
}
