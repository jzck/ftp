#include "ft_p.h"

int		g_debug;

int		cli_do_debug(int sock, char **av)
{
	(void)sock;
	if (av[1] && av[2])
		return (console_msg(-1, "usage: debug [ on | off | level ]"));
	if (!av[1])
		g_debug = !g_debug;
	else if (ft_strcmp(av[1], "on") == 0)
		g_debug = 1;
	else if (ft_strcmp(av[1], "off") == 0)
		g_debug = 0;
	else if (ft_stris(av[1], ft_isdigit))
		g_debug = ft_atoi(av[1]);
	else
	{
		console_msg(-1, "%s: bad debugging value", av[1]);
		return (-1);
	}
	console_msg(0, "Debugging %s (g_debug = %i)",
			g_debug ? "on" : "off", g_debug);
	return (-1);
}
