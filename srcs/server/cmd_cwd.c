/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:36:24 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/02 15:24:00 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_cwd(t_ftp *ftp, char **av)
{
	if (chdir(av[1]))
	{
		console_msg(1, "chdir(%s) failed errno=%i", av[1], errno);
		ftp_ret(ftp, "550 file not found");
	}
	else
		ftp_ret(ftp, "200 success");
	return (1);
}
