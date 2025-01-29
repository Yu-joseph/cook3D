/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouhail <ysouhail@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:01:10 by ysouhail          #+#    #+#             */
/*   Updated: 2025/01/28 15:25:35 by ysouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	load_color(t_game *game, t_path *l)
{
	game->c_b = l->c_b;
	game->c_g = l->c_g;
	game->c_r = l->c_r;
	game->f_b = l->f_b;
	game->f_g = l->f_g;
	game->f_r = l->f_r;
}
void load_img(t_game *game, t_path *l)
{
	// printf("%s\n", l->SO);
	
	game->so = mlx_load_png(l->SO);	
	game->no = mlx_load_png(l->NO);	
	game->we = mlx_load_png(l->WE);	
	game->ea = mlx_load_png(l->EA);	
	if (!game->so || !game->no || !game->ea || !game->we)
	{
		exit(write(2, "ERROR\nbad images1\n", 18));
	}
	game->i_no = mlx_texture_to_image(game->mlx , game->no);
	game->i_so = mlx_texture_to_image(game->mlx , game->so);
	game->i_we = mlx_texture_to_image(game->mlx , game->we);
	game->i_ea = mlx_texture_to_image(game->mlx , game->ea);
	if (!game->i_so || !game->i_no || !game->i_ea || !game->i_we)
	{
		exit(write(2, "ERROR\nbad images\n", 17));
	}
	game->clr.ea = get_pixels(game->i_ea);
	game->clr.so = get_pixels(game->i_so);
	game->clr.no = get_pixels(game->i_no);
	game->clr.we = get_pixels(game->i_we);
	load_color(game, l);
}
// int get_texture_pixel_color(mlx_texture_t *txt, int img_x, int img_y)
// {
//     // Ensure img_x and img_y are within the bounds of the texture
//     if (img_x < 0 || (uint32_t)img_x >= txt->width || (uint32_t)img_y < 0 || (uint32_t)img_y >= txt->height)
//     {
//         return 0;  // Return 0 (black) if the coordinates are out of bounds
//     }

//     // Get the pixel data from the texture (assuming it's an array of integers)
//     int *texture_data = (int *)txt->pixels;  // Assuming 'pixels' holds the texture data

//     // Calculate the offset to access the pixel data at (img_x, img_y)
//     int pixel_index = img_y * txt->width + img_x;  // The index in the 1D array

//     // Return the color of the pixel
//     return texture_data[pixel_index];
// }


int	**get_pixels(mlx_image_t *img)
{
	int **pixels;
	int	i;
	int	j;
	int count;
	int	*pixel;

	i = 0;
	count = 0;
	if (!img)
		return(NULL);
	pixels = malloc(sizeof(int *) * img->height);
	while (i < (int) img->height)
	{
		j = 0;
		pixel = malloc(sizeof(int) * img->width);
		while (j < (int)img->width)
		{
			pixel[j++] = rgb(img->pixels[count], img->pixels[count + 1], img->pixels[count + 2], img->pixels[count + 3]);
			count += 4;
		}
		pixels[i++] = pixel;
	}
	return(pixels);
}


mlx_image_t	*get_texture(t_game *data, int ***clr, int i)
{
    if (data->rays[i].vertical)
	{
        if (data->rays[i].right) 
		{
            *clr = data->clr.ea;
            return(data->i_ea);
        } 
		else 
		{
            *clr = data->clr.we;
            return(data->i_we);
        }
    } 
	else
	{ 
        if (data->rays[i].up)
		{
            *clr = data->clr.no;
            return(data->i_no);
        } 
		else 
		{
            *clr = data->clr.so;
            return(data->i_so);
        }
    }
}
	// if (data->rays[i].up == true && data->rays[i].vertical == true)
	// {	
	// 	*clr = data->clr.no;
	// 	return(data->i_no);
	// }
	// else if (data->rays[i].down == true && data->rays[i].vertical == false)
	// {	
	// 	*clr = data->clr.so;
	// 	return(data->i_so);
	// }
	// else if (data->rays[i].up == true && data->rays[i].vertical == true)
	// {	
	// 	*clr = data->clr.we;
	// 	return(data->i_we);
	// }
	// else if (data->rays[i].up == true && data->rays[i].vertical == true)
	// {	
	// 	*clr = data->clr.ea;
	// 	return(data->i_ea);
	// }

// }
// void draw_wall(t_game *data, double t_pix, double wall_h, int i)
// {
//     mlx_image_t *txt;
//     int j = 0;
//     int **color;
//     int img_x, img_y;
//     double tex_pos;
//     double step;
    
//     txt = get_texture(data, &color);
    
//     // Calculate the x-coordinate on texture
//     if (data->rays[i].vertical == true)
//         img_x = ((data->rays[i].y / CELL) - floor(data->rays[i].y / CELL)) * txt->height;
//     else
//         img_x = ((data->rays[i].x / CELL) - floor(data->rays[i].x / CELL)) * txt->height;
    
//     // Calculate texture step based on wall height vs window height
//     step = txt->height / wall_h;
    
//     // If wall_h > window height, adjust starting texture position
//     if (wall_h > H) {
//         tex_pos = (wall_h - H) / 2.0 * step;
//     } else {
//         tex_pos = 0;
//     }
    
//     while (j < H) // Draw only within window height
//     {
//         if (t_pix + j >= H)
//             break;

//         if (t_pix + j >= 0) // Only draw visible pixels
//         {
//             img_y = (int)tex_pos % txt->height;
//             mlx_put_pixel(data->game, i * WALL_STRIP_WIDTH, (t_pix + j), color[img_y][img_x]);
//         }
        
//         tex_pos += step;
//         j++;
//     }
// }


void draw_wall(t_game *data, double t_pix, double b_pix, double wall_h, int i)
{
    mlx_image_t *txt;
    int j = 0;
	int **color;
	double texture_step;
	double texture_pos;
    int img_x, img_y = 0;
	img_y = 0;
    txt = get_texture(data, &color, i);
	if (!txt)
		exit(write(2, "ERROR\nNo Imgaes", 15));
    if (data->rays[i].vertical == true)
        img_x = ((data->rays[i].y / CELL) - floor(data->rays[i].y / CELL)) * txt->height;
    else
        img_x = ((data->rays[i].x / CELL) - floor(data->rays[i].x / CELL)) * txt->height;
	texture_step = txt->height / wall_h;
    if (wall_h > H)
        texture_pos = texture_step * ((wall_h - H) / 2);
	else
        texture_pos = 0;
    while (j < wall_h)
    {
        if (t_pix + j >= H)
            break;
		if (t_pix + j >= 0)
        {
            img_y = (int)texture_pos % txt->height;
            mlx_put_pixel(data->game, b_pix, (t_pix + j), color[img_y][img_x]);
        }
        texture_pos += texture_step;
        j++;
    }
}

void draw_texture(t_game *data)
{
    int i = 0;
    double t_pix = 0;
	double b_pix = 0;
    while (i < NUM_RAYS)
    {
        t_pix = (H / 2) - (data->rays[i].wall_height / 2);
        if (t_pix < 0)
            t_pix = 0;
        draw_wall(data, t_pix, b_pix, data->rays[i].wall_height, i);
		b_pix += WALL_STRIP_WIDTH;
        i++;
    }
}
void free_int(int **arry, int size)
{
	int i;

	i = -1;
	while (++i < size)
	{
		free(arry[i]);
	}
	free(arry);
}
void    free_path(t_path *p, t_game *g)
{
    free(p->EA);
    free(p->SO);
    free(p->WE);
    free(p->NO);
	
	free_int(g->clr.ea, g->i_ea->height);
    mlx_delete_image(g->mlx, g->i_ea);
    mlx_delete_texture(g->ea);
	
	free_int(g->clr.so, g->i_so->height);
    mlx_delete_image(g->mlx, g->i_so);
    mlx_delete_texture(g->so);
	
	free_int(g->clr.no, g->i_no->height);
    mlx_delete_image(g->mlx, g->i_no);
    mlx_delete_texture(g->no);
	
	free_int(g->clr.we, g->i_we->height);
    mlx_delete_image(g->mlx, g->i_we);
    mlx_delete_texture(g->we);
}
void aa(void)
{
	system("leaks cub3D");
}
int	main(int ac, char **av)
{
	atexit(aa);
	t_path l;
	char **map;
	t_game game;

	if(ac  != 2)
		return (1);
	(void) ac;
	if(check_name(av[1]) == false)
		return (1);
	map = check_map(av[1], &game);
	parse_map(map, &game, &l);
	game.path = &l;
	printf("ccc= %d, %d, %d\n",game.path->c_r, game.path->c_g, game.path->c_b);
	printf("ffff= %d, %d, %d\n",game.path->f_r, game.path->f_g, game.path->f_b);
	game.ply = init_ply();
	ft_mlx_init(&game);
	load_img(&game, &l);
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	clean_img(&game);
	free_path(&l, &game);
	free_d(map);
	free(game.ls);
	return (0);
}
