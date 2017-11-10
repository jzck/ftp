/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:43:10 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 18:39:39 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cli_ls(t_ftp *ftp, char **av)
{
	char	*msg;

	(void)av;
	if (dconn_init(ftp) < 0)
		return (-1);
	ftp_cmd(ftp, "LIST -a");
	if (dconn_open(ftp) < 0)
		return (-1);
	while (1)
	{
		if (ftp_recv(ftp->d_sock, &msg))
			break ;
		write(1, msg, ft_strlen(msg));
		ft_strdel(&msg);
	}
	dconn_close(ftp);
	return (0);
}
