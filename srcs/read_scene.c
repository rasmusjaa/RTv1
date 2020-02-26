/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 11:17:04 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/26 12:42:43 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

void		int_array_set(int *arr, int n, int nb)
{
	int		i;

	i = 0;
	while (i < n)
	{
		arr[i] = nb;
		i++;
	}
}

void		int_array_read(int *arr, int n, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && j < n)
	{
		if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
		{
			arr[j] = ft_atoi(&line[i]);
			j++;
			while ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
				i++;
			i--;
		}
		i++;
	}
}

int			read_spot(t_mlx *mlx, char *line)
{
	int		arr[8];

	int_array_set(arr, 8, 0);
	int_array_read(arr, 8, line);
	arr[5] = ft_int_clamp_0(arr[5], 0, 255);
	arr[6] = ft_int_clamp_0(arr[6], 0, 255);
	arr[7] = ft_int_clamp_0(arr[7], 0, 255);
	mlx->spots[mlx->spot_i].p.x = ft_int_clamp_0(arr[0], -99, 99);
	mlx->spots[mlx->spot_i].p.y = ft_int_clamp_0(arr[1], -99, 99);
	mlx->spots[mlx->spot_i].p.z = ft_int_clamp_0(arr[2], -99, 99);
	mlx->spots[mlx->spot_i].intensity = ft_int_clamp(arr[3], 0, 100);
	mlx->spots[mlx->spot_i].type = arr[4] != 0 ? 1 : 0;
	mlx->spots[mlx->spot_i].color = arr[5] << 16 | arr[6] << 8 | arr[7];
	return (0);
}

static void	read_scene_line(t_mlx *mlx, char *line)
{
	int		arr[7];

	int_array_set(arr, 7, 0);
	int_array_read(arr, 7, line);
	mlx->scene->ambient = ft_int_clamp_0(arr[0], 0, 100);
	mlx->scene->speculars = ft_int_clamp_0(arr[1], 0, 1);
	mlx->scene->shadows = ft_int_clamp_0(arr[2], 0, 1);
	mlx->scene->shading = ft_int_clamp_0(arr[3], 0, 1);
	mlx->scene->ambient_r = ft_int_clamp_0(arr[4], 0, 255);
	mlx->scene->ambient_g = ft_int_clamp_0(arr[5], 0, 255);
	mlx->scene->ambient_b = ft_int_clamp_0(arr[6], 0, 255);
}

void		read_scene(t_mlx *mlx)
{
	int		fd;
	char	*line;

	fd = open(mlx->scene->name, O_RDONLY);
	if (fd < 0)
		exit_message("Invalid file");
	while (ft_get_next_line(fd, &line) > 0)
	{
		if (!ft_strncmp("camera", line, 6))
			read_camera(mlx, line);
		else if (!ft_strncmp("scene", line, 5))
			read_scene_line(mlx, line);
		else if (!ft_strncmp("sphere", line, 6) && !read_sphere(mlx, line))
			mlx->sphere_i++;
		else if (!ft_strncmp("plane", line, 5) && !read_plane(mlx, line))
			mlx->plane_i++;
		else if (!ft_strncmp("cylinder", line, 8) && !read_cyli(mlx, line))
			mlx->cylinder_i++;
		else if (!ft_strncmp("cone", line, 4) && !read_cone(mlx, line))
			mlx->cone_i++;
		else if (!ft_strncmp("spot", line, 4) && !read_spot(mlx, line))
			mlx->spot_i++;
		free(line);
	}
	multi_thread(mlx);
}
