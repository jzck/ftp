/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serv_do_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:07:11 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/08 12:07:55 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		serv_do_put(int sock)
{
	char	fname[MAXLINE];
	int		rep;
	int		fd;

	ft_bzero(&fname, MAXLINE);
	rep = htons(TRANSFER_START);
	if (read(sock, fname, MAXLINE) < 0)
		rep = htons(ABORT);
	else if ((fd = open_new(fname, O_WRONLY | O_TRUNC | O_APPEND)) < 0)
		rep = htons(ABORT);
	write(sock, (char*)&rep, sizeof(rep));
	if (rep != htons(TRANSFER_START))
		return (CMD_FAIL);
	net_get_large(sock, fd);
	return (CMD_SUCCESS);
}
