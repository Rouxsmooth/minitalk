/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:18:46 by mzaian            #+#    #+#             */
/*   Updated: 2025/01/07 03:37:56 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/minitalk.h"

t_server serv;
/*
void printmaskbin(unsigned int mask)
{
	int i;

	i = 7;
	ft_printf("Binary mask: ");
	while (i >= 0)
	{
		ft_printf("%d", (mask >> i) & 1);
		i--;
	}
	ft_printf("\n");
}
*/
void handle_sigusr(int sig)
{
	int bit;

	bit = (sig == SIGUSR2);
	//ft_printf("Received bit: %d\n", bit);
	if (serv.current_bit < 8)
	{
		serv.mask |= (bit << (7 - serv.current_bit));
		serv.current_bit++;
	}
	if (serv.current_bit == 8)
	{
		ft_printf("%c", serv.mask);
		serv.current_bit = 0;
		serv.mask = 0;
	}
	//printmaskbin(serv.mask);
}

int init_server(void)
{
	struct sigaction sa;

	serv.current_bit = 0;
	serv.mask = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_sigusr;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		return (ft_printf("Failed to set up signal handlers.\n"), -1);
	return (ft_printf("\e[31;1m\n\
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
	if (init_server() == -1)
		return (display_error("Error: signal assignation error."), 1);
	while (1)
		pause();
	return (0);
}
