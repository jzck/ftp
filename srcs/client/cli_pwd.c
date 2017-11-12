/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:33:09 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/12 14:19:35 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cli_pwd(t_ftp *ftp, char **av)
{
	(void)av;
	FTP_CMD(ftp, "PWD");
	ftp_code(ftp);
	return (0);
}
