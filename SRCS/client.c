/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:26:19 by mzaian            #+#    #+#             */
/*   Updated: 2025/01/13 10:34:44 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

/*int get_usleep(size_t messlen)
{
	//float divisor;
	//int lowerbound;
	//int upperbound;

	//if (messlen < 125)
	//	return (500);
	//lowerbound = get_lower_bound(messlen, 10);
	//upperbound = get_upper_bound(messlen, 10);
	//if (messlen - lowerbound < upperbound - messlen)
	//	divisor = 5 * lowerbound - 20;
	//else
	//	divisor = 2 * upperbound;
	return (4 * messlen);
}*/

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;
	//int		usleep_time;
	size_t	messlen;

	i = 8;
	if (argc != 3)
		return (display_error(ft_ternary("input should be \
./client <PID> <MESSAGE>", "too much arguments", argc < 3)));
	pid = ft_atoi(argv[1]);
	if (pid < 1)
		return (display_error("invalid server PID"));
	//usleep_time = get_usleep(ft_strlen(argv[2]));
	messlen = ft_strlen(argv[2]);
	#include <stdio.h>
	//printf("usleep time = %f pour messlen de %d\n", (double) (3.5 * messlen), (int) messlen);
	while (*argv[2])
	{
		//ft_printf("binletter : ");
		i = 7;
		while (i >= 0)
		{
			//ft_printf("h bit would be: %d\n", (104 >> i) & 1);
			//ft_printf("%d", (*argv[2] >> i) & 1);
			if ((*argv[2] >> i) & 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					return (display_error("message sending error"));
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					return (display_error("message sending error"));
			}
			i--;
			usleep(10 * messlen);
		}
		//ft_printf("\n");
		argv[2]++;
	}
	return (0);
}
