/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:26:19 by mzaian            #+#    #+#             */
/*   Updated: 2024/12/22 10:42:47 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

void	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	i = 8;
	if (argc != 3)
		return (display_error(ft_ternary("Error: missing server PID or message",
			"Error: too much arguments", argc < 3)));
	pid = ft_atoi(argv[1]);
	if (pid < 1)
		return (display_error("Error: invalid server PID"));
	while (*argv[2])
	{
		i = 8;
		while (i >= 0)
		{
			if ((*argv[2] >> i ) & 1){
				if (kill(pid, SIGUSR2) == -1)
					return (display_error("Error: message sending error"));}
			else {
				if (kill(pid, SIGUSR1) == -1)
					return (display_error("Error: message sending error"));}
			i--;
		}
		argv[2]++;
	}
}
