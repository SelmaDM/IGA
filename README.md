# IGA

## BEZIER CURVES AND SURFACES 

### COMPILE  
```
g++ -o BezierSurface  BezierSurface.cpp  -lglut -lGL -lGLU
NB : The compilation  output is already present in the directory  and can be directly run with  ./BezierCurve  ./BezierSurface
```




### HOW TO RUN  
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

 #### Draw the curve 

```c++
glMap1f(GL_MAP1_VERTEX_3, umin, umax, stride, polynomialdegree, controlepoints);
```

#### Draw the polygone
              
			  
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
### RESULTS 

[![Bezier curve with 200 segments](https://github.com/SelmaDM/IGA/blob/b758b34f005c8bc9d56c6cc0c45b860387e1583c/Bezier_Curve_seg_200.png)
[![Bezier curve with 10 segments ](https://github.com/SelmaDM/IGA/blob/master/Bezier_curve_seg_10.png)



			  

####  Implement evenely spaced points using segment number

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
  	rather, it is "stretched" toward them as though each were an attractive force [Wikipedia](https://en.wikipedia.org/wiki/B%C3%A9zier_surface)
   

### Main functions
> To handle surfaces, we just convert the OpenGL functions from the earlier section above to 2D
```c++  
glMap2f(type, u_min, u_max, u_stride, u_order, v_min, v_max, v_stride, v_order, point_array);
```

> glMapGrid2 specifies two such linear mappings. One maps integer grid coordinate i = 0 exactly to u1, and integer 
> grid coordinate i = un exactly to u2
> 
```c++  
glMapGrid2f(u_steps,u_min,u_max,v_steps,v_min,v_max)
```
> In glEvalMesh2, specifies whether to compute a two-dimensional mesh of points, lines, or polygons. Symbolic 
> constants GL_POINT, GL_LINE, and GL_FILL are accepted
```c++  
glEvalMesh2(GL_FILL,u_start,u_stop,v_start,v_stop)
```
## RESULTS 

[![Bezier Surface ](https://github.com/SelmaDM/IGA/blob/master/Surface1.png)
[![Bezier Surface ](https://github.com/SelmaDM/IGA/blob/master/surface2.png)
[![Bezier Surface ](https://github.com/SelmaDM/IGA/blob/master/Surface3.png)




### Sources :

1. [W3 cs](https://w3.cs.jmu.edu/bernstdh/web/common/lectures)
2. [educatech](https://educatech.in/opengl-bezier-spline-curve-functions/ )
3. [GitHub](https://github.com/Hanbiubiu/Bezier-curve-surface)
4. [khronos](https://www.khronos.org/opengl/wiki/Code_Resources)
			
	

			
			
