/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 17:44:35 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/17 02:49:15 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/INCLUDES/libft.h"
#include "fcntl.h"

int	error_loop(char *line, int serv)
{
	int		i;
	int		len_without_nl;
	char	*serv_tofind;
	int		errorcount;

	i = 1;
	while (line)
	{
		if (i != 1)
			ft_del(serv_tofind);
		serv_tofind = ft_itoa(i);
		ft_insert_str(&serv_tofind, "test", 0);
		len_without_nl = ft_strlen(line) - 1;
		if (ft_strncmp(serv_tofind, line, len_without_nl))
		{
			errorcount++;
			ft_printf("issue at line %d | '%s' : '", i, serv_tofind);
			write(1, line, len_without_nl);
			write(1, "'\n", 3);
		}
		i++;
		ft_del(line);
		line = get_next_line(serv);
	}
	return (close(serv), ft_del(serv_tofind), ft_del(line), errorcount);
}

int	main(void)
{
	char	*line;
	int		i;
	int		serv;
	int		errorcount;

	serv = open("test.txt", O_RDONLY);
	line = get_next_line(serv);
	i = 0;
	while (i++ < 12)
	{
		ft_del(line);
		line = get_next_line(serv);
	}
	errorcount = error_loop(line, serv);
	if (!errorcount)
		return (ft_printf("No errors in receiving."), 0);
	return (ft_printf("There are %d errors\n", errorcount), 0);
}
	/* error output */
// issue at line 29 | 'test29' : 'test29a'
// issue at line 47 | 'test47' : 'test42'
// issue at line 98 | 'test98' : 'test94'
// There are 3 errors