#pragma once

#include <Point2D.h>


class Rasterizer
{
	public:
		Rasterizer();
		~Rasterizer();

		void DrawTriangle(Point2D& p1, Point2D& p2, Point2D& p3, int& w, int& h, void(*fragShader)(Point2D&), float* depthBuffer);
		{
			// first sort the points in descending order a/c y coordinate
			SortY(p1,p2,p3);

			if(p1.y == p2.y)  // the two upper points are at same y level
			{
				// make two edges, (p1,p3) and (p2,p3)
				Point2D e1[] = {p1,p3};
				Point2D e2[] = {p2,p3};
				InterpolateEdges(e1,e2,w,h,fragShader, depthbuffer);
			}
			else // the two upper points are not at same level
			{
				Point2D e1[] = {p1,p2};
				Point2D e2[] = {p1,p3};
				InterpolateEdges(e1, e2, w, h, fragShader, depthBuffer);
			}
		}
		

		void interpolateEdges(Point2D* e1, Point2D* e2, int w, int h, void(*fragShader)(Point2D&), float* depthBuffer)
		{
			float inv_m1 = (e1[1].x-e1[0].x)/(e1[1].y-e1[0].y);
			float inv_m2 = (e2[1].x-e2[0].x)/(e2[1].y-e2[0].y);

			int y = e1[0].y; // both the first point of edges have same y value
			float factorY1 = 0.f, factorY2 = 0.f;
			float factorX1, factorX2;
			int dx;
			int tempx1 = e1[0].x, tempx2 = e2[0].x; // tempx1 and tempx2 are the x values for respective edges(which may be outside x=0 and x=w).
			float x1, x2;  // x1 and x2 are the x values that are inside the window, probably visible on the surface(if they pass depth test)

			if(tempx2>=tempx1)
			{
				x1 = Max(tempx1, 0); 
				x2 = Min(tempx2, w); 
			}
			else
			{
				x1 = Min(tempx1, w);
				x2 = Max(tempx2, 0);
			}
			float dy1 = e1[0].y-e1[1].y; // subtracting from lower y to upper y
			float dy2 = e2[0].y-e2[1].y; // subtracting from lower y to upper y

			Vec3 attr1 = e1[0].attributes[0], attr2 = e2[0].attributes[0];	
			Vec3 attr;
			// do until the scan line reaches the y value of lower point of e1
			while(y-- >= e1[1].y)
			{
				if (y>h) return; // if scanline is below the screen
				if (y<0)continue;// if scanline is above the screen
				dx = tempx2 - tempx1;
				attr = attr1 +(attr2-attr1)*(x1-tempx1)/dx;						// depth buffer interpolation is remaining.

				for(int x=x1;x<=x2;x++)
				{
					attr += (attr2-attr1)*(x-x1)/dx;
				}
				//factorY1+=1/dy1;
				//factorY2+=1/dy2;
				attr1-=(e1[0].attributes[0]-e1[1].attributes[0])/dy1;
				attr2-=(e2[0].attributes[0]-e2[1].attributes[0])/dy2;
				tempx1 += 1/inv_m1;
				tempx2 += 1/inv_m2;

				if(tempx2>=tempx1)
				{
					x1 = Max(tempx1, 0); 
					x2 = Min(tempx2, w); 
				}
				else
				{
					x1 = Min(tempx1, w);
					x2 = Max(tempx2, 0);
				}

				y--;
			}
			// now do until the scan line reaches the y value of lower point of e2
			inv_m1 = (e2[1].x-e1[1].x)/(e2[1].y-e1[1].y); // now, the edge contains second point of e1 and second point of e2, other edge is the same
			dy1 = e1[1].y-e2[1].y; 
			attr1 = e1[1].attributes[0] - (e1[1].attributes[0]-e2[1].attributes[0])/dy1; // other edge is one step below
			tempx1 = e1[1].x + 1/inv_m1; // for e2, all things are the same
			// now into the loop
			while(y-- >= e1[1].y)
			{
				if (y>h) return; // if scanline is below the screen
				if (y<0)continue;// if scanline is above the screen
				dx = tempx2 - tempx1;
				attr = attr1 +(attr2-attr1)*(x1-tempx1)/dx;						// depth buffer interpolation is remaining.

				for(int x=x1;x<=x2;x++)
				{
					attr += (attr2-attr1)*(x-x1)/dx;
				}
				//factorY1+=1/dy1;
				//factorY2+=1/dy2;
				attr1-=(e1[0].attributes[0]-e1[1].attributes[0])/dy1;
				attr2-=(e2[0].attributes[0]-e2[1].attributes[0])/dy2;
				tempx1 += 1/inv_m1;
				tempx2 += 1/inv_m2;

				if(tempx2>=tempx1)
				{
					x1 = Max(tempx1, 0); 
					x2 = Min(tempx2, w); 
				}
				else
				{
					x1 = Min(tempx1, w);
					x2 = Max(tempx2, 0);
				}
			}
		}

};
