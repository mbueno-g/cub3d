# cub3d

*My first raycaster with MiniLibX 💡*

🚧 WIP: Magic under development 🚧

<p align="center">
    <img src="https://user-images.githubusercontent.com/40824677/153962176-0c2539c4-0c43-4a2e-9797-c67310eb6ce5.gif">
</p>

<!--

:books: [Introduction](#introduction)

:collision: [New concept](#new-concept): Render + Raycasting


## Introduction

The aim of the cub3D proyect is to create a 3D game using the raycasting technique which is a rendering method implemented in the world-famous Wolfenstein 3D game.
This was a group proyect and I had the honor to repeat with @madebypixel02 :)


## New concept

### Raycasting
Raycasting is a rendering technique to create a 3D perspective in a 2D map. 
The logic of RayCasting is to throw rays in the direction of the player view. Basically, we need to check the distance between the player and the nearest wall (i.e. the point the ray hits a wall) to caculate the height of the vertical lines we draw.

<p align="center">
     <img width="200" alt="Screenshot 2022-02-15 at 23 07 13" src="https://user-images.githubusercontent.com/71781441/154158563-5b4f7641-4f3d-4cca-97f1-4cc79aac16dd.png">
    <img width="233" alt="Screenshot 2022-02-15 at 22 58 00" src="https://user-images.githubusercontent.com/71781441/154159164-667da898-a8d5-4991-a8d0-a6008f111054.png">
</p>
    
    

## New concept

### Rendering
Rendering (= image synthesis) is the process of generating a image by means of a computer program. The resulting image is referred to as the render. 


### Raycasting
Raycasting is a rendering technique to create a 3D perspective in a 2D map.
This technique is about doing calculations for every vertical line of the screen(x axis), what makes it a fast method. However, it also has its limitations: height differences are impossible to make with this technique.
Let's see the basic idea behind raycasting. 
From the player location on the 2D map send out a ray in the direction given by the player's looking direction (N,S,W,E). The distance from the player to the nearest wall hit by the ray is used to calculare how high the wall is: the further away the wall, the smaller it's on the screen, and viceversa. The relation between this distance and the wall's height on the screen is inversely proportional. 

To find the wall the ray hits, we can use the Digital Differential Analysis algorithm. 
-->

