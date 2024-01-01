# Generated Vines 

## What I Intend To Make

<p> I plan on creating a system which adds three dimensional vines climbing up the side of preexisting models. The general steps that will be taken to create this effect will be: to use an L-system to generate a 2D vine-like structure of lines, wrapping this structure around the surface of the chosen model, generating a mesh for the vine, and instantiating leaves on chosen vertices. My hope is that the outcome will be visually interesting as well as show my understanding of the topic of computer graphics.

<p>One reason that I was interested in this project was due to the plethora of prior examples of systems which generate ivy and vines. Which I've found tend to be highly praised by 3D artists as a huge time save when it comes to the modeling process. 

## Existing Reference

<p> An example of a similar effect to what I intend to make is, "An Ivy Generator" by Thomas Luft.[1] Similarly to my idea Thomas' ivy grows from a single root point and extends upwards from there. Where his project differs from mine, however, is in the approach he used to create natural paths of ivy stems. Thomas' ivy grows following five forces: a growth direction based on previous directions, a random influence, an adhesion force, an up vector and gravity.[1] My project will instead be using an implementation of the L system in order to make generic vine shapes which can be wrapped onto a model. This will lead to a less realistic outcome, especially around overhangs, however should also make the implementation much easier which will be necessary given the deadline of my project.
</p>

![Generated Ivy By Thomas Luft](/Images/ImageOfGeneratedIvyByThomasLuft.png)<br>[fig.1 Generated Ivy By Thomas Luft [1]]

<p> Another example of a similar project to mine was developed by Aidan Mcinerny. In this project he used C++ and OpenGL to create 3D trees built with a modified implementation of the L-system.[2] This is a particularly good project to look into as Mcinerny was in university when he was working on it. So the goal of recreating his quality seems less aspirational.
</p>

![3D L-system Trees By Aidan Mcinerny](/Images/3DL-systemTreesByAidanMcinerny.png)<br>[fig.2 3D L-system Trees By Aidan Mcinerny [2]]

## Systems In Use

<p> In Order to generate the structure of my vines I am planning on using the L-system. I chose this algorithm because it is particularly good for creating natural and complex plant-like structures whilst staying logically simple relative to some other options.

<p> The L-system uses a set of rules and grammar to create branches and leaves iteratively.[3] This allows the user to have strong control over the output, by editing the input string. This high level of control can also lead to some results that deviate strongly from the intended outcome.

<p> To wrap the L-System onto the face of the shape I will draw the constructing lines one at a time starting at the origin point of the system. At each occurrence of a line intersecting the edge of a face I will cut the line there and wrap the rest over by using the angle between the normal of the face of the shape that is being left, and the normal of the face being entered, about the cross product of these two normals.

<p> In order to make the knitting of vertices as simple as possible, I plan on visualizing the stems of the vine as a series of cylinders, where each ring of vertices has an equal number as the previous. This will allow me to handle knitting the vertices by creating two lists of vertices and creating a rule which can repeat around the circumference of the cylinder. This technique also allows for varying thickness of stem across the plant if that is something that I choose to create.

![Vertex Knitting Visualised](/Images/VertexknittingVisualised.PNG)<br>[fig.4 Vertex Knitting Visualised]

## Agile Workflow

<p> I will be using an agile workflow to complete this project. This will be achieved by having minimum viable products for each of the algorithms that I intend to add. I will work on them first then use extra time to iterate on these and extend the scope of my work.

## References

[1]
"An Ivy Generator," Uni-konstanz.de, 2023. http://graphics.uni-konstanz.de/~luft/ivy_generator/ (accessed Feb. 07, 2023). <br>

[2]
"3D L-System," Rit.edu, 2015. https://www.csh.rit.edu/~aidan/portfolio/3DLSystems.shtml (accessed Feb. 07, 2023). <br>

‌[3]
Ruoxi Sun, Jinyuan Jia, and M. Jaeger, "Intelligent tree modeling based on L-system," 2009 IEEE 10th International Conference on Computer-Aided Industrial Design & Conceptual Design, Nov. 2009, doi: https://doi.org/10.1109/caidcd.2009.5375256.
