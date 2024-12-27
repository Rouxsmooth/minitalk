/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaian <mzaian@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:06:57 by mzaian            #+#    #+#             */
/*   Updated: 2024/12/25 17:18:51 by mzaian           ###   ########.fr       */
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
} t_server;

#endif