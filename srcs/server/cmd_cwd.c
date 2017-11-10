/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 13:36:24 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 13:00:01 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_cwd(t_ftp *ftp, char **av)
{
	char	old[1024];
	char	buf[1024];

	getcwd(old, 1024);
	if (chdir(av[1]))
	{
		console_msg(1, "chdir(%s) failed errno=%i", av[1], errno);
		ftp_ret(ftp, "550 directory not found");
	}
	else
	{
		getcwd(buf, 1024);
		if (!ft_strstr(buf, old))
		{
			console_msg(0, "%s -> %s", buf, old);
			chdir(old);
			ftp_ret(ftp, "550 unauthorized directory");
		}
		else
			ftp_ret(ftp, "200 success");
	}
	return (0);
}
