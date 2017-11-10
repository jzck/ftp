/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:21:10 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/10 19:48:53 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_rmd(t_ftp *ftp, char **av)
{
	if (remove(av[1]) < 0)
		return (ftp_ret(ftp, "550 remove(3) error"));
	return (ftp_ret(ftp, "257 '%s' deleted", av[1]));
}
