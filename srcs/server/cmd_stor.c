/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_stor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 16:01:54 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/09 15:15:02 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_stor(t_ftp *ftp, char **av)
{
	int		fd;
	char	*msg;

	if (dconn_open(ftp) < 0)
		return (-1);
	if ((fd = open(av[1], O_WRONLY | O_TRUNC | O_CREAT, 0644)) < 0)
		return (ftp_ret(ftp, "550 couldn't open/create file"));
	while (1)
	{
		if (ftp_recv(ftp->d_sock, &msg))
			break ;
		write(fd, msg, ft_strlen(msg));
		ft_strdel(&msg);
	}
	dconn_close(ftp);
	return (0);
}
