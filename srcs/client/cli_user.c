/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:17:03 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/09 10:21:45 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cli_user(t_ftp *ftp, char **av)
{
	int		code;

	if (av[1] == NULL || av[2] != NULL)
	{
		console_msg(-1, "usage: user <username>");
		return (-1);
	}
	ftp_cmd(ftp, "USER %s", av[1]);
	code = ftp_code(ftp);
	return (0);
}
