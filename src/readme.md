## BEZIER CURVES AND SURFACES 

### COMPILE  
g++ -o BezierSurface  BezierSurface.cpp  -lglut -lGL -lGLU
### NB : The compilation  output is already present in the directory ./BezierCurve  ./BezierSurface


### RUN  
### Bezier Curve
		1. run  ./BezierCurve    
		2. Specify the number of segments 
		3. Left-Click: To add a point
		4. Right-Click-and-Drag: To select a point and move it

### Bezier Surface
		1. ./BezierSurface
		2. Right-Click to display the surface from different perspectives



### FEATURES

### Bezier Curve 
  
  > Cubic bezier curves are generated with glMap1f evaluator,
  > which computes the values for bernstein polynomials of any order

### Main functions

           - Draw the curve 


			```c++
						glMap1f(GL_MAP1_VERTEX_3, umin, umax, stride, polynomialdegree, controlepoints);
			```

           - Draw the polygone
              
			  
			```c++
						// Connect the points (using a piecewise linear curve)
						if (numPoints >= 2) {
							glColor3f(0.8, 0.2, 0.3);
							glBegin(GL_LINE_STRIP);
							{
							for (int i = 0; i < numPoints; i++) {
								glVertex3f(points[i][0], points[i][1], points[i][2]);
							}
							}
							glEnd();
						}

			```

			  

           -  Implement evenely spaced points using segment number

         			   	```c++
							glBegin(GL_LINE_STRIP);  // GL_POINTS can also be used
							{
							for (int i = 0; i < nbSegments; i++) {
							glEvalCoord1f(((float) i) / nbSegments);
							}
							}
							glEnd();
							} 
					```
			
### Bezier Surface 
>   As with Bézier curves, a Bézier surface is defined by a set of control points. Similar to interpolation in many 	respects, a key difference is that the surface does not, in general, pass through the central control points;
  	rather, it is "stretched" toward them as though each were an attractive force [Wikipedia]
	(https://en.wikipedia.org/wiki/B%C3%A9zier_surface)
   

### Main functions
  






### Sources :
			[W3 cs]    (https://w3.cs.jmu.edu/bernstdh/web/common/lectures)
			[educatech](https://educatech.in/opengl-bezier-spline-curve-functions/ )
			[GitHub]   (https://github.com/Hanbiubiu/Bezier-curve-surface)
			[khronos]  (https://www.khronos.org/opengl/wiki/Code_Resources)
			
	

			
			