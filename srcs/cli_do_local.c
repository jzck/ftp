/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_do_local.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 12:02:12 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/08 12:02:35 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		cli_do_local(int sock, char **av)
{
	char	*command;

	(void)sock;
	command = ft_strsepjoin(av + 1, ' ');
	system(command);
	return (-1);
}
