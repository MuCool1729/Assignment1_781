# Assignment 1 - Ray Tracing

#### Mukul Kumar (2018MT10760), Yash Gohel (2018MT10773)



## Introduction

In this assignment we are implementing ray tracing using recursive ray tracing algorithm as discussed in the class.



## Models

We are working with four different models namely:

1. Triangle
2. Sphere
3. Quadric
4. Box

We are using world co-ordinate system to define all the above models.



## Lights

We have multiple light support with each light having it's own color. All lights are point-source lights.



## Camera

We are taking two inputs for camera, camera position and a point where camera is pointing to. If distance between camera position and point becomes less than some value(depends on window size) then it may result in distortion due to perspective distortion.



## Materials

We have made a class for materials where we define properties like $$K_a$$, $$K_d$$ etc. which will be later used in Phong illumination model.



## Rendering

We are rendering the matrix of RGB values we are getting after ray tracing using OpenGL and GLFW.



### Examples

![Image rendered without anti-aliasing](B:\IITD\Sem8\COL781\Assignment 1\Assigment1_781\rendered_01.png)

​																								| <b>Image rendered with anti-aliasing (16 samples)</b>|



![Without anti-aliasing](B:\IITD\Sem8\COL781\Assignment 1\Assigment1_781\rendered_02.png)

​																									| <b>Image rendered without anti-aliasing</b>|



​										![Image with refraction](B:\IITD\Sem8\COL781\Assignment 1\Assigment1_781\rendered_03.png)

​																									| <b>Image rendered with refraction(depth=3)</b>|

![Refraction](B:\IITD\Sem8\COL781\Assignment 1\Assigment1_781\rendered_033.png)

​																									| **Image rendered with refraction(depth=5)**|

![Image with reflection](B:\IITD\Sem8\COL781\Assignment 1\Assigment1_781\rendered_04.png)

​																									| <b>Image rendered with reflection</b>|

> PS. For checking working please refer to comments in the code.
>
> In the refraction we have put depth as 3 so some black dots are coming on the refracting sphere. As the depth increases we are getting better refraction and clear image but as our resources are limited and higher depth may take time around 1 hour so we have put above image for refraction.