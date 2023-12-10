# Convex hull generation and quadTree mesh generation
## Used technologies
* C++
* QT
## Program operation
After starting the application, a GUI window appears:  
![](/image/3.jpg )  
The user enters the number of point clouds and the number of points in each cloud - the more points, the generated polygons similar to rectangles. The polygons are elongated vertically due to the figure generation algorithm.  
After clicking the button on the left, a graphic file is generated based on the user's input. This is what the graphic file looks like for five point clouds and 30 points in each cloud:
![](/image/4.jpg )  
Note: each time you click the button, the graphic file is overwritten with other data - a new graphic file with the same name is generated.  
Clicking the button on the right causes a grid to be applied. A second file is generated next to the input file, which contains the input image with a mesh overlay:
![](/image/5.jpg )  
## Technical part:
I created the project in the QT framework, but I wrote it in C++, not Python. I chose this environment because I have more experience in creating windowed applications in QT than in any other technology, including Java. What was important was that I was offered a lot of graphics libraries and useful methods, such as drawConvexPolygon(), a lot of classes for geometry (QPoint, QLine, etc.) and operations on graphic files (QPixel, QImage), and the ease of coloring the interior of a polygon. I didn't use the forest fire algorithm, but I used the brush accordingly. This made the task easier.  
Method and class definitions in four files. Main.cpp is just an entry point in the program. Graham_algorithm.cpp contains an implementation of Graham's convex hull algorithm. Quad_tree.cpp contains a recursive method that creates a grid, and widget.cpp visualizes everything that is happening - creating the GUI and the content of graphic files.  
## Details
Content of the quad_tree.cpp file – definition of the function that generates points that are the ends of lines, creating rectangles on the graphic and saving the coordinates of these points to a .txt file
The input includes two vertices of the rectangle - the upper left one and the lower right one, and the image on which it is drawn.The function works recursively - each call calls four more...  
The bottom line of recursion is appropriately small dimensions of the slice, rigidly set in the program.
### Output
Other otput files for quad tree:  
![](/image/1.jpg )  
![](/image/2.jpg )  
