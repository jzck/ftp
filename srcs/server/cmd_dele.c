/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_dele.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:38:40 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 19:39:34 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_dele(t_ftp *ftp, char **av)
{
	(void)av;
	if (unlink(av[1]) < 0)
		return (ftp_ret(ftp, "550 unlink error"));
	else
		return (ftp_ret(ftp, "250 file '%s' deleted", av[1]));
	return (0);
}
