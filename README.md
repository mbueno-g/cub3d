# cub3d

:books: [Introduction](#introduction)

:mega: [Rules](#rules)

:collision: [New concept](#new-concept): Raycasting

:rainbow: [Textures](#textures)



:joystick: [Time to play](#time-to-play)


## Introduction

The aim of the cub3D proyect is to create a 3D game using the raycasting technique which is a rendering method implemented in the world-famous Wolfenstein 3D game.
This was a group proyect and I had the honor to repeat with @madebypixel02 :)


## Rules

This 3D game must follow the following rules:

#### Files rules
- [x] The executable cub3D must receive at least one argument, a map.
- [x] The map is a .cub file
- [x] The first few lines must contain a direction, written as `NO`,`SO`,`WE`,`EA`, followed by a path to an .xpm image. If one of these directions appears more than once, the image or texture is updated if the new path is valid. 
- [x] After the textures and an empty line,  the RGB color for the floor and ceiling is shown as `F` or `C` followed by the RGB coordinates separated by commas.
- [x] Finally, the map is display.

#### Maps rules
- [x] These are the possible characters: ` ` (empty), `0` (floor), `1` (wall) and `N`,`S`, `W`, `E` (player's view direction). Additionally, for the bonus we have `c` (close door) and `o` (open door).
- [x] The map must be surrounded by walls, even the empty spaces.

So a valid map would be seen as this one:

```
NO textures/wall_1.xpm
NO textures/wall_1.xpm
SO textures/wall_2.xpm
WE textures/wall_3.xpm
EA textures/wall_3.xpm

F 255,113,39
C 51,198,227

11111111111111111111111111111
11111111110000000000000000011111
        10110000011100000000000111111
        100000000110000011111111111
11111111111111011100000010001
11111111000001111100000010001
       1000001 100000001100011111111
    11110000111101000N00000011111
11111111111111111111111111111

11111111111111111111111111111
10000000111100010000000001001
100000001  100110101110000001
10000000111110000001 10100001
11111111111111111111 11111111
```

#### Game rules
- [x] The `W`, `A`, `S` and `D` keys move up, down, left and right the player's point of view.
- [x] The `left` and `right` arrow keys rotate the field of view of the player. 
- [x] Pressing `ESC` or the red cross on the window's frame must close the window and quit the program cleanly. 


## New concept

### Raycasting
Raycasting is a rendering technique to create a 3D perspective in a 2D map. 
The logic behind RayCasting is to throw rays in the direction of the player view. Basically, we need to check the distance between the player and the nearest wall (i.e. the point the ray hits a wall) to caculate the height of the vertical lines we draw.

<p align="center">
     <img width="200" alt="Screenshot 2022-02-15 at 23 07 13" src="https://user-images.githubusercontent.com/71781441/154158563-5b4f7641-4f3d-4cca-97f1-4cc79aac16dd.png">
    <img width="233" alt="Screenshot 2022-02-15 at 22 58 00" src="https://user-images.githubusercontent.com/71781441/154159164-667da898-a8d5-4991-a8d0-a6008f111054.png">
</p>
    
To calculate the **distance between the player and the nearest wall**, we can use the following algorithm:
1. Initialize some basic attributes needed for the projection: 

<table align="center">
    <tr aling="center">
        <th> Attribute </th>
        <th> Description </th>
        <th> Value </th>
    </tr>
    <tr align="center">
        <td>FOV </td>
        <td> The field of view of the player <img width="150" align="center" alt="Screenshot 2022-02-20 at 22 17 46" src="https://user-images.githubusercontent.com/71781441/154864710-baee6726-6f2a-4f37-8125-97a5cf52c4f7.png"></td>
        <td> 30º </td>
    </tr>
    <tr align="center">
        <td>Ray angle </td>
        <td> Angle of the player view's direction</td>
        <td> N (270º), S (90º), W (180º), E (0º)</td>
    </tr>
    <tr align="center">
        <td>Ray increment angle </td>
        <td> Angle difference between one ray and the next one </td>
        <td> 2 * HFOV / window_width </td>
    </tr>
    <tr align="center">
        <td>Precision </td>
        <td> </td>
        <td>70 </td>
    </tr>
    <tr align="center">
        <td>Limit </td>
        <td> Limit of the distance the player can view </td>
        <td> 11</td>
    </tr>
    <tr align="center">
        <td>Player's position</td>
        <td> Center of the square where the player is </td>
        <td> pl.x += 0.5 ; pl.y += 0.5 </td>
    </tr>
</table>


2. From the the player's position, we move the ray forward incrementing the x's and y's coordinates of the ray.

<img align="right" width="333" alt="Screenshot 2022-02-20 at 22 35 23" src="https://user-images.githubusercontent.com/71781441/154865310-1b8dc0c5-0def-416f-adb6-7acf2a01c53a.png">

```c
ray.x += ray_cos;
ray.y += ray_sin;
```

where `ray_cos` and `ray_sin` are of the form:
```c
ray_cos = cos(degree_to_radians(ray_angle)) / g->ray.precision;
ray_sin = sin(degree_to_radians(ray_angle)) / g->ray.precision;
```

3. Repeat step 2 until we reach the limit or we hit a wall.

4. Calculate the distance between the player's and the ray's position using the euclidean distance:
```c
distance = sqrt(powf(x - pl.x - 0.5, 2.) + powf(y - pl.y - 0.5, 2.));
```

5. Fix fisheye
```c
distance = distance * cos(degree_to_radians(ray_angle - g->ray.angle))
```

This algorith is repeated window_width times, i.e. in every iteration we increment the angle until we have been through all the field of view. 
This distance is really helpful to calculate the height of the wall height:
```c
wall_height = (window_height / (1.5 * distance));
```

## Textures

One last thing we need to do is to read pixels `(x,y)` from a texture image `i` to get the colors of the wall. 

```c
x = (int)(i->width * (g->x + g->y)) % i->width;
// y = image height
color = my_mlx_pixel_get(i, x, y);
```
Once we know the wall height and all the colors, we have everything we need to draw the ceiling, the wall and the floor.
- Ceiling: from screen top to screen half height minus wall height
- Wall: from half height minus wall height to half height plus wall height
- Floor: from half height plus wall height to screen botton


## Time to play

Here are a few samples of how our maps look

<p align="center">
    <img src="https://user-images.githubusercontent.com/40824677/155116913-80e549a9-1080-4eaf-bf44-0c0940998119.gif">
</p>

- ``1.cub``

<p align="center">
    <img src="https://user-images.githubusercontent.com/40824677/155116616-824e5a4e-7dc2-4e6b-8d00-5d22e57d7c2c.gif">
</p>

- ``2.cub``

<p align="center">
    <img src="https://user-images.githubusercontent.com/40824677/155116751-58a1f0d4-8500-480d-bf47-c93073933fbb.gif">
</p>

- ``pac.cub``

<p align="center">
    <img src="https://user-images.githubusercontent.com/40824677/155117235-bd8e392a-d856-4201-9f56-13a72f7ef3ca.gif">
</p>


- ``pac2.cub``

<p align="center">
    <img src="https://user-images.githubusercontent.com/40824677/155117526-38191be8-94d7-43e5-bca0-aca7a0efeb00.gif">
</p>

To check some of our favorite layouts, see [MAPS.md](https://github.com/mbueno-g/cub3d/blob/main/maps/MAPS.md)
