/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:18:46 by mzaian            #+#    #+#             */
/*   Updated: 2024/12/22 11:05:28 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"


void	handle_sigusr1(int sig, t_server serv)
{
	if (serv.current_bit != 8)
	{
		(serv.bit_received << (8 - serv.current_bit)) & serv.bit_received;
		serv.current_bit++;
	}
	else
		while (serv.current_bit != 0)
		{
			write()
		}
}

void	handle_sigusr2(int sig, t_server serv)
{
	
}

int	init_server(void)
{
	t_server	serv;

	return ((signal(SIGUSR1, handle_sigusr1), signal(SIGUSR2, handle_sigusr2)),
	ft_printf("\e[31;1m\n\
   +---------------------------------------------+\n\
   | __  __ ___ _   _ ___ _____  _    _     _  __|\n\
   ||  \\/  |_ _| \\ | |_ _|_   _|/ \\  | |   | |/ /|\n\
   || |\\/| || ||  \\| || |  | | / _ \\ | |   | ' / |\n\
   || |  | || || |\\  || |  | |/ ___ \\| |___| . \\ |\n\
   ||_|  |_|___|_| \\_|___| |_/_/   \\_\\_____|_|\\_\\|\n\
   |                                             |\n\
   |            SO WE CAN COMMUNICATE            |\n\
   +---------------------------------------------+\n\n\
	\e[32;1mServer's PID : %d\e[0m\n", getpid()));
}

int main(void)
{
	init_server(); //this just retrieves program's PID
	while (1)
		pause();
	return (0);
}
