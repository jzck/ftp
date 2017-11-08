/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   console_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:05:23 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/08 19:57:41 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		console_msg(int level, char *str, ...)
{
	va_list	ap;

	va_start(ap, str);
	if (g_debug >= level)
	{
		if (level == -1)
			ft_printf("{red}");
		if (level == 0)
			ft_printf("{blu}");
		else
			ft_printf("{mag}");
		ft_vdprintf(1, str, ap);
		ft_printf("{eoc}\n");
	}
	return (level);
}
