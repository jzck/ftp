/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mkd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:17:53 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 19:35:39 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_mkd(t_ftp *ftp, char **av)
{
	(void)av;
	if (mkdir(av[1], 0755) < 0)
		return (ftp_ret(ftp, "550 mkdir() error"));
	else
		return (ftp_ret(ftp, "257 '%s' created", av[1]));
	return (0);
}
