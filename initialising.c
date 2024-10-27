/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlevinsc <dlevinsc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:37:54 by epolkhov          #+#    #+#             */
/*   Updated: 2024/10/27 19:22:08 by dlevinsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_main_struct(t_cub *cub)
{
	cub->c_array = NULL;
	cub->ea_array = NULL;
	cub->f_array = NULL;
	cub->map = NULL;
	cub->no_array = NULL;
	cub->so_array = NULL;
	cub->we_array = NULL;
	cub->height = 0;
	cub->width = 0;
	cub->player = 0;
	cub->player_h = 0;
	cub->player_w = 0;
	cub->gaze = M_PI / 2;
	cub->txt_idx = 0;
	cub->txt_w = 0;
	cub->txt = NULL;
	cub->img = NULL;
	cub->mlx = NULL;
	cub->valid = 1;
}

void	init_flag_struct(t_cub *cub)
{
	cub->flags.c_flag = 0;
	cub->flags.ea_flag = 0;
	cub->flags.f_flag = 0;
	cub->flags.no_flag = 0;
	cub->flags.so_flag = 0;
	cub->flags.we_flag = 0;
}
