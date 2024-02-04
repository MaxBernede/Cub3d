#include "cub3d.h"


uint32_t get_color_wall(mlx_texture_t* texture, float percentageX, float percentageY)
{
	uint32_t posX;
	uint32_t posY;
	uint32_t pixelIndex;

	if (percentageX <= 0)
		posX = 0;
	else
		posX = (uint32_t)(percentageX / 100.0 * texture->width);
	if (percentageY <= 0)
		posY = 0;
	else
    	posY = (uint32_t)(percentageY / 100.0 * texture->width);
    pixelIndex = (posY * texture->width + posX) * texture->bytes_per_pixel;
	u_int32_t r = texture->pixels[pixelIndex];
	u_int32_t g = texture->pixels[pixelIndex + 1];
	u_int32_t b = texture->pixels[pixelIndex + 2];

	uint32_t color = (r << 24) | (g << 16) | (b << 8) | 255;

	return color;
}
