/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:33:09 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 12:42:11 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cli_pwd(t_ftp *ftp, char **av)
{
	char	*msg;

	(void)av;
	ftp_cmd(ftp, "PWD");
	ftp_recv(ftp->cmd_sock, &msg);
	ft_strdel(&msg);
	return (0);
}
