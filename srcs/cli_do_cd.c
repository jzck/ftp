/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_do_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:02:04 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/08 12:02:04 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		cli_do_cd(int sock, char **av)
{
	if (!av[1] || av[2])
		return (console_msg(-1, "usage: cd <path>"));
	if (req_init(sock, REQUEST_CD))
		return (1);
	console_msg(0, "sending %s", av[1]);
	write(sock, av[1], ft_strlen(av[1]));
	return (0);
}
