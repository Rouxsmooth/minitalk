/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:06:57 by mzaian            #+#    #+#             */
/*   Updated: 2025/03/01 09:29:35 by mzaian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <signal.h>

//add libft to INCLUDES and change libft.h path
# include "../../libft/INCLUDES/libft.h"
# include "../../../../usr/include/x86_64-linux-gnu/bits/sigaction.h"

typedef struct s_server
{
	unsigned int	current_bit;
	unsigned char	mask;
	char			*msg;
	size_t			msglen;
	int				maxbits;
	int				has_signature;
	int				sigcount;
	unsigned int	len;
}	t_server;

typedef struct s_client
{
	unsigned int	current_bit;
	unsigned char	mask;
	unsigned int	ack;
	int				amount_sent;
	int				receive_sig;
	pid_t			pid;
	unsigned int	msglen;
}	t_client;

extern t_server	g_serv;
extern t_client	g_client;

int		reception_ack(pid_t pid, int sig);
int		sig_sending(int sig);
int		char_sending(char c);
int		msg_sending(char *msg);
void	init_g_serv(void);
void	get_signature(void);

#endif