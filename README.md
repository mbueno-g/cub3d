# cub3d

*My first raycaster with MiniLibX 💡*

🚧 WIP: Magic under development 🚧

<p align="center">
    <img src="https://user-images.githubusercontent.com/40824677/154857349-93ba911d-39b1-452e-a027-1237c97518ba.gif">
</p>

<p align="center">
    <img src="https://user-images.githubusercontent.com/40824677/154857398-332e4ebc-9793-4ff4-bbb8-fa3de5f82880.gif">
</p>

<p align="center">
    <img src="https://user-images.githubusercontent.com/40824677/154857378-54aa9625-7938-41d6-8771-249b7a8dbe0a.gif">
</p>



:books: [Introduction](#introduction)

:collision: [New concept](#new-concept): Render + Raycasting


## Introduction

The aim of the cub3D proyect is to create a 3D game using the raycasting technique which is a rendering method implemented in the world-famous Wolfenstein 3D game.
This was a group proyect and I had the honor to repeat with @madebypixel02 :)


## New concept

### Raycasting
Raycasting is a rendering technique to create a 3D perspective in a 2D map. 
The logic behind RayCasting is to throw rays in the direction of the player view. Basically, we need to check the distance between the player and the nearest wall (i.e. the point the ray hits a wall) to caculate the height of the vertical lines we draw.

<p align="center">
     <img width="200" alt="Screenshot 2022-02-15 at 23 07 13" src="https://user-images.githubusercontent.com/71781441/154158563-5b4f7641-4f3d-4cca-97f1-4cc79aac16dd.png">
    <img width="233" alt="Screenshot 2022-02-15 at 22 58 00" src="https://user-images.githubusercontent.com/71781441/154159164-667da898-a8d5-4991-a8d0-a6008f111054.png">
</p>
    
To find the wall the ray hits, we can use the following algorithm. 
1. Initialize some basic attributes needed for the projection: 

<table align="center">
    <tr aling="center">
        <th> Attribute </th>
        <th> Description </th>
        <th> Value </th>
    </tr>
    <tr align="center">
        <td>HFOV </td>
        <td> The field of view of the player</td>
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
</table>

2. From the center of the square the player is in, we move the ray forward incrementing the x's and y's coordinates of the ray.
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



<img width="333" alt="Screenshot 2022-02-20 at 22 35 23" src="https://user-images.githubusercontent.com/71781441/154865310-1b8dc0c5-0def-416f-adb6-7acf2a01c53a.png">

<img width="300" alt="Screenshot 2022-02-20 at 22 17 46" src="https://user-images.githubusercontent.com/71781441/154864710-baee6726-6f2a-4f37-8125-97a5cf52c4f7.png">








