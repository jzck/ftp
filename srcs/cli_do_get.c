/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_do_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:02:48 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/08 12:03:12 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		cli_do_get(int sock, char **av)
{
	int		rep;
	int		fd;

	if (!av[1] || av[2])
		return (console_msg(-1, "usage: get <file>"));
	if (req_init(sock, REQUEST_FILE))
		return (1);
	write(sock, av[1], ft_strlen(av[1]));
	rep = read_req(sock);
	if (rep != FILENAME_OK)
		return (1);
	rep = htons(TRANSFER_START);
	if ((fd = open_new(av[1], O_WRONLY | O_TRUNC | O_APPEND)) < 0)
		rep = htons(ABORT);
	write(sock, (char*)&rep, sizeof(rep));
	if (rep != htons(TRANSFER_START))
		return (1);
	console_msg(1, "TRANSFER_START");
	net_get_large(sock, fd);
	console_msg(1, "TRANSFER DONE");
	return (0);
}
