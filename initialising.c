/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-27 11:37:54 by epolkhov          #+#    #+#             */
/*   Updated: 2024-09-27 11:37:54 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_main_struct(t_cub *cub)
{
	cub->C_array = NULL;
	cub->EA_array = NULL;
	cub->F_array = NULL;
	cub->map = NULL;
	cub->NO_array = NULL;
	cub->SO_array = NULL;
	cub->WE_array = NULL;
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
	cub->flags.C_flag = 0;
	cub->flags.EA_flag = 0;
	cub->flags.F_flag = 0;
	cub->flags.NO_flag = 0;
	cub->flags.SO_flag = 0;
	cub->flags.WE_flag = 0;
}

