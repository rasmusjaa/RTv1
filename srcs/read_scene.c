/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjaakonm <rjaakonm@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 11:17:04 by rjaakonm          #+#    #+#             */
/*   Updated: 2020/02/25 16:31:47 by rjaakonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rtv1.h"

void		int_array_set(int *arr, int n, int nb)
{
	int		i;

	i = 0;
	while(i < n)
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

void		read_spot_line(t_mlx *mlx, char *line)
{
	int		i;
	int		arr[8];

	int_array_set(arr, 8, 0);
	int_array_read(arr, 8, line);
	i = 0;
	while (i < 4)
	{
		if (arr[i] < -100 || arr[i] > 100)
			arr[i] = 0;
		i++;
	}
	while (i < 8)
	{
		if (arr[i] < 0 || arr[i] > 255)
			arr[i] = 0;
		i++;
	}
	mlx->spots[mlx->spot_i].p.x = arr[0];
	mlx->spots[mlx->spot_i].p.y = arr[1];
	mlx->spots[mlx->spot_i].p.z = arr[2];
	mlx->spots[mlx->spot_i].intensity = arr[3];
	mlx->spots[mlx->spot_i].type = arr[4] != 0 ? 1 : 0;
	mlx->spots[mlx->spot_i].color = arr[5]<<16 | arr[6]<<8 | arr[7];
}

void		set_plane(t_plane *plane)
{
	if (plane->p.x == plane->normal.x && plane->p.y == plane->normal.y &&
		plane->p.z == plane->normal.z)
		plane->normal.y = plane->p.y + 1;
	plane->normal = vector_minus(plane->normal, plane->p);
	plane->normal = normalized_vector(plane->normal);
}

void		read_plane_line(t_mlx *mlx, char *line)
{
	int		i;
	int		arr[9];

	int_array_set(arr, 9, 0);
	int_array_read(arr, 9, line);
	i = 0;
	while (i < 6)
	{
		if (arr[i] < -100 || arr[i] > 100)
			arr[i] = 0;
		i++;
	}
	while (i < 9)
	{
		if (arr[i] < 0 || arr[i] > 255)
			arr[i] = 0;
		i++;
	}
	mlx->planes[mlx->plane_i].p.x = arr[0];
	mlx->planes[mlx->plane_i].p.y = arr[1];
	mlx->planes[mlx->plane_i].p.z = arr[2];
	mlx->planes[mlx->plane_i].normal.x = arr[3];
	mlx->planes[mlx->plane_i].normal.y = arr[4];
	mlx->planes[mlx->plane_i].normal.z = arr[5];
	mlx->planes[mlx->plane_i].color = arr[6]<<16 | arr[7]<<8 | arr[8];
	set_plane(&mlx->planes[mlx->plane_i]);
}

void		read_sphere_line(t_mlx *mlx, char *line)
{
	int		i;
	int		arr[7];

	int_array_set(arr, 7, 0);
	int_array_read(arr, 7, line);
	i = 0;
	while (i < 4)
	{
		if (arr[i] < -100 || arr[i] > 100)
			arr[i] = 0;
		i++;
	}
	while (i < 7)
	{
		if (arr[i] < 0 || arr[i] > 255)
			arr[i] = 0;
		i++;
	}
	mlx->spheres[mlx->sphere_i].p.x = arr[0];
	mlx->spheres[mlx->sphere_i].p.y = arr[1];
	mlx->spheres[mlx->sphere_i].p.z = arr[2];
	mlx->spheres[mlx->sphere_i].radius = arr[3];
	mlx->spheres[mlx->sphere_i].color = arr[4]<<16 | arr[5]<<8 | arr[6];
}

void		set_cylinder(t_cylinder *cylinder)
{
	if (cylinder->p1.x == cylinder->p2.x && cylinder->p1.y == cylinder->p2.y &&
		cylinder->p1.z == cylinder->p2.z)
		cylinder->p2.y = cylinder->p1.y + 1;
	cylinder->axis = vector_minus(cylinder->p1, cylinder->p2);
	cylinder->axis = normalized_vector(cylinder->axis);
}

void		read_cylinder_line(t_mlx *mlx, char *line)
{
	int		i;
	int		arr[10];

	int_array_set(arr, 10, 0);
	int_array_read(arr, 10, line);
	i = 0;
	while (i < 7)
	{
		if (arr[i] < -100 || arr[i] > 100)
			arr[i] = 0;
		i++;
	}
	while (i < 10)
	{
		if (arr[i] < 0 || arr[i] > 255)
			arr[i] = 0;
		i++;
	}
	mlx->cylinders[mlx->cylinder_i].p1.x = arr[0];
	mlx->cylinders[mlx->cylinder_i].p1.y = arr[1];
	mlx->cylinders[mlx->cylinder_i].p1.z = arr[2];
	mlx->cylinders[mlx->cylinder_i].p2.x = arr[3];
	mlx->cylinders[mlx->cylinder_i].p2.y = arr[4];
	mlx->cylinders[mlx->cylinder_i].p2.z = arr[5];
	mlx->cylinders[mlx->cylinder_i].radius = arr[6];
	mlx->cylinders[mlx->cylinder_i].color = arr[7]<<16 | arr[8]<<8 | arr[9];
	set_cylinder(&mlx->cylinders[mlx->cylinder_i]);
}

void		set_cone(t_cone *cone)
{
	if (cone->p1.x == cone->p2.x && cone->p1.y == cone->p2.y &&
		cone->p1.z == cone->p2.z)
		cone->p2.y = cone->p1.y + 1;
	cone->axis = vector_minus(cone->p1, cone->p2);
	cone->axis = normalized_vector(cone->axis);
	if (cone->angle < 1)
		cone->angle = 1;
	if (cone->angle > 45)
		cone->angle = 45;
	cone->angle = cos(cone->angle * M_PI / 180.0);
	cone->angle_sqr = cone->angle * cone->angle;
}

void		read_cone_line(t_mlx *mlx, char *line)
{
	int		i;
	int		arr[10];

	int_array_set(arr, 10, 0);
	int_array_read(arr, 10, line);
	i = 0;
	while (i < 6)
	{
		if (arr[i] < -100 || arr[i] > 100)
			arr[i] = 0;
		i++;
	}
	i++;
	while (i < 10)
	{
		if (arr[i] < 0 || arr[i] > 255)
			arr[i] = 0;
		i++;
	}
	mlx->cones[mlx->cone_i].p1.x = arr[0];
	mlx->cones[mlx->cone_i].p1.y = arr[1];
	mlx->cones[mlx->cone_i].p1.z = arr[2];
	mlx->cones[mlx->cone_i].p2.x = arr[3];
	mlx->cones[mlx->cone_i].p2.y = arr[4];
	mlx->cones[mlx->cone_i].p2.z = arr[5];
	mlx->cones[mlx->cone_i].angle = arr[6];
	mlx->cones[mlx->cone_i].color = arr[7]<<16 | arr[8]<<8 | arr[9];
	set_cone(&mlx->cones[mlx->cone_i]);
}

void		read_scene_line(t_mlx *mlx, char *line)
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
	{
		ft_putendl("Invalid file");
		exit (0);
	}
	while (ft_get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp("camera", line, 6) == 0)
			read_camera_line(mlx, line);
		else if (ft_strncmp("scene", line, 5) == 0)
			read_scene_line(mlx, line);
		else if (ft_strncmp("sphere", line, 6) == 0)
		{
			read_sphere_line(mlx, line);
			mlx->sphere_i++;
		}
		else if (ft_strncmp("plane", line, 5) == 0)
		{
			read_plane_line(mlx, line);
			mlx->plane_i++;
		}
		else if (ft_strncmp("cylinder", line, 8) == 0)
		{
			read_cylinder_line(mlx, line);
			mlx->cylinder_i++;
		}
		else if (ft_strncmp("cone", line, 4) == 0)
		{
			ft_putendl("cone");
			read_cone_line(mlx, line);
			mlx->cone_i++;
		}
		else if (ft_strncmp("spot", line, 4) == 0)
		{
			read_spot_line(mlx, line);
			mlx->spot_i++;
		}
		free (line);
		line = NULL;
	}
	multi_thread(mlx);
}
