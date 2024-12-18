/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:37:27 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/14 21:06:01 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(char arg)
{
	if (arg >= '0' && arg <= '9')
		return (1);
	else
		return (0);
}
