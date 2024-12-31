/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:26:19 by mzaian            #+#    #+#             */
/*   Updated: 2024/12/31 15:46:37 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

float get_usleep(size_t messlen)
{
	//float divisor;
	//int lowerbound;
	//int upperbound;

	if (messlen < 100)
		return (300);
	//lowerbound = get_lower_bound(messlen, 10);
	//upperbound = get_upper_bound(messlen, 10);
	//if (messlen - lowerbound < upperbound - messlen)
	//	divisor = 5 * lowerbound - 20;
	//else
	//	divisor = 2 * upperbound;
	return (4 * messlen);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;
	float	usleep_time;

	i = 8;
	if (argc != 3)
		return (display_error(ft_ternary("Error: missing server PID or message",
			"Error: too much arguments", argc < 3)));
	pid = ft_atoi(argv[1]);
	if (pid < 1)
		return (display_error("Error: invalid server PID"));
	usleep_time = get_usleep(ft_strlen(argv[2]));
	ft_printf("usleep time = %d pour messlen de %d\n", (int) usleep_time, (int) ft_strlen(argv[2]));
	while (*argv[2])
	{
		//ft_printf("binletter : ");
		i = 7;
		while (i >= 0)
		{
			//ft_printf("h bit would be: %d\n", (104 >> i) & 1);
			//ft_printf("%d", (*argv[2] >> i) & 1);
			if ((*argv[2] >> i ) & 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					return (display_error("Error: message sending error"));
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					return (display_error("Error: message sending error"));
			}
			i--;
			usleep(usleep_time);
		}
		//ft_printf("\n");
		argv[2]++;
	}
	return (0);
}
