/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-27 19:06:09 by epolkhov          #+#    #+#             */
/*   Updated: 2024-10-27 19:06:09 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// Determine the direction of the view
void	view_direction(t_cub *cub)
{
	int		x;
	float	dv;
	float	v;

	v = cub->gaze - FOV / 2;
	dv = FOV / (WINDOW_W - 1);
	x = -1;
	while (++x < WINDOW_W)
	{
		line(cub, x, view(cub, v) * cos(cub->gaze - v));
		v += dv;
	}
}

// Check for collisions in the view
float	check_view_collision(t_cub *cub, t_view *view)
{
	if (view->v_dist < view->h_dist)
	{
		if (cub->map[(int)view->v_y][(int)view->v_x
			+ (view->sx - 1) / 2] == '1')
		{
			cub->txt_idx = view->sx + 1;
			cub->txt_w = view->v_w;
			return (view->v_dist);
		}
		view->v_x += view->sx;
	}
	else
	{
		if (cub->map[(int)view->h_y + (view->sy - 1)
				/ 2][(int)view->h_x] == '1')
		{
			cub->txt_idx = view->sy + 2;
			cub->txt_w = view->h_w;
			return (view->h_dist);
		}
		view->h_y += view->sy;
	}
	return (-1);
}

// Calculate the view distance
float	view(t_cub *cub, float v)
{
	t_view	view;
	float	result;

	view_start(cub, &view, v);
	while (1)
	{
		view_next(cub, &view);
		result = check_view_collision(cub, &view);
		if (result != -1)
			return (result);
	}
}

// Initialize view settings
void	view_start(t_cub *cub, t_view *view, float angle)
{
	view->dx = cos(angle);
	view->dy = -sin(angle);
	view->sx = check_sign(view->dx);
	view->sy = check_sign(view->dy);
	view->v_x = (int)cub->p_x;
	if (view->sx > 0)
		view->v_x += 1.0f;
	view->h_y = (int)cub->p_y;
	if (view->sy > 0)
		view->h_y += 1.0f;
}

// Move to the next view position
void	view_next(t_cub *cub, t_view *view)
{
	if (view->sx != 0)
	{
		view->v_y = cub->p_y + view->dy / view->dx * (view->v_x - cub->p_x);
		view->v_dist = sqrt(pow(cub->p_x - view->v_x, 2.0)
				+ pow(cub->p_y - view->v_y, 2.0));
		if (view->sx > 0)
			view->v_w = 1 - view->v_w;
	}
	else
		view->v_dist = INFINITY;
	if (view->sy != 0)
	{
		view->h_x = cub->p_x + view->dx / view->dy * (view->h_y - cub->p_y);
		view->h_dist = sqrt(pow(cub->p_x - view->h_x, 2.0)
				+ pow(cub->p_y - view->h_y, 2.0));
		view->h_w = view->h_x - (int)view->h_x;
		if (view->sy < 0)
			view->h_w = 1 - view->h_w;
	}
	else
		view->h_dist = INFINITY;
}
