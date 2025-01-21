/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:06:57 by mzaian            #+#    #+#             */
/*   Updated: 2025/01/18 21:58:36 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <signal.h>

//add libft to INCLUDES and change libft.h path
# include "../../libft/INCLUDES/libft.h"
# include "../../../../usr/include/x86_64-linux-gnu/bits/sigaction.h"

typedef struct	s_server
{
	unsigned int	current_bit;
	unsigned char	mask;
	char			*msg;
	size_t			msglen;
	int				keep;
	int				amountlen;
	int				good_signature;
	int				waiting_sig_confirm;
	int				sigcount;
	int				sentback;
}	t_server;

typedef struct	s_client
{
	unsigned int	current_bit;
	unsigned char	mask;
	unsigned int	ack;
	int				amount_sent;
	int				receive_sig;
	int				good_signature;
	pid_t			pid;
}	t_client;

int	reception_ack(pid_t pid, int sig);
int	sig_sending(int sig);
int	char_sending(char c);


#endif