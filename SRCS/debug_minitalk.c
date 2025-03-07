/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_minitalk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:44:35 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/02 17:55:29 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/INCLUDES/libft.h"
#include "fcntl.h"

int	main(void)
{
	char	*line;
	int		i;
	int		serv;
	char	*serv_tofind;
	int		errorcount;

	serv = open("test.txt", O_WRONLY);
	line = get_next_line(serv);
	errorcount = 0;
	while (line)
	{
		i = 0;
		ft_del(serv_tofind);
		serv_tofind = ft_itoa(i);
		if (ft_strcmp(serv_tofind, line))
		{
			errorcount++;
			ft_printf("issue at line %d | '%s' : '%s'\n", i, serv_tofind, line);
		}
		i++;
		ft_del(line);
	}
	ft_printf("There are %d errors\n", errorcount);
	return (close(serv), ft_del(serv_tofind), ft_del(line), 0);
}
