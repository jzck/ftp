/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:20:26 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/09 14:03:52 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cli_debug(t_ftp *ftp, char **av)
{
	(void)ftp;
	if (av[1] != NULL && av[2] != NULL)
	{
		console_msg(-1, "usage: debug <level>");
		return (1);
	}
	if (av[1])
		g_debug = FT_ABS(ft_atoi(av[1]));
	console_msg(0, "debug_level is set to %i", g_debug);
	return (0);
}
