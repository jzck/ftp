#include "ft_p.h"

int		g_debug;

int		console_msg(int level, char *str, ...)
{
	va_list	ap;

	va_start(ap, str);
	if (g_debug >= level)
	{
		if (level == -1)
			ft_printf("{red}");
		if (level == 0)
			ft_printf("{blu}");
		else
			ft_printf("{mag}");
		ft_vdprintf(1, str, ap);
		ft_printf("{eoc}\n");
	}
	return (level);
}
