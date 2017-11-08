/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 18:14:51 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/02 15:49:12 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_type(t_ftp *ftp, char **av)
{
	if (!av[1])
		ftp_ret(ftp, "501 syntax error in parameter");
	if (av[1][0] == 'A')
	{
		ftp_ret(ftp, "200 type A ok");
	}
	else if (av[1][0] == 'I')
	{
		ftp_ret(ftp, "200 type A ok");
	}
	else
		ftp_ret(ftp, "500 parameter unrecognized");
	return (1);
}
