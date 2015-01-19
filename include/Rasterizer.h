#pragma once

#include <Point2D.h>


class Rasterizer
{
	public:
		Rasterizer(){}
		~Rasterizer(){}

		// helper functions
		template <class t>
		t Max(t a, t b)
		{
			if (a>b) return a;
			else return b;
		}
		
		template <class t>
		t Min(t a, t b)
		{
			if (a<b) return a;
			else return b;
		}

	void SortY(Point2D& p1, Point2D& p2, Point2D& p3)
	{
		if (p1.y < p2.y) 
		{
			std::swap(p1.x, p2.x);
			std::swap(p1.y, p2.y);
		}
		if (p2.y < p3.y) 
		{
			std::swap(p2.x, p3.x);
			std::swap(p2.y, p3.y);
		} ///largest yvalue coord is at 1
		if (p1.y < p2.y) 
		{
			std::swap(p1.x, p2.x);
			std::swap(p1.y, p2.y);
		}
	}
	// helper functions end.

		void DrawTriangle(Point2D& p1, Point2D& p2, Point2D& p3, int& w, int& h, void(*fragShader)(Point2D&), float* depthBuffer)
		{
			// check if depth clipping fails or not
			if((p1.depth<0 or p1.depth>1) and (p2.depth<0 or p2.depth>1) and (p2.depth<0 or p2.depth>1)) return; 

			// first sort the points in descending order a/c y coordinate
			SortY(p1,p2,p3);

			if(p1.y == p2.y)  // the two upper points are at same y level
			{
				// make two edges, (p1,p3) and (p2,p3)
				Point2D e1[] = {p1,p3};
				Point2D e2[] = {p2,p3};
				InterpolateEdges(e1,e2,w,h,fragShader, depthBuffer);
			}
			else // the two upper points are not at same level
			{
				Point2D e1[] = {p1,p2};
				Point2D e2[] = {p1,p3};
				InterpolateEdges(e1, e2, w, h, fragShader, depthBuffer);
			}
		}
		

		void InterpolateEdges(Point2D* e1, Point2D* e2, int& w, int& h, void(*fragShader)(Point2D&), float* depthBuffer)
		{
			float inv_m1 = (e1[1].x-e1[0].x)/(e1[1].y-e1[0].y);
			float inv_m2 = (e2[1].x-e2[0].x)/(e2[1].y-e2[0].y);

			int inc=1;
			// check direction of x increment, if e1 has x values smaller
			// than that of e2, x in increment positively,else -vely
			if(e1[0].x<e2[0].x or e1[1].x<e2[1].x) inc = 1;
			//else inc = -1;
			if(e1[0].x>e2[0].x or e1[1].x>e2[1].x) inc = -1;

			int y = e1[0].y; // both the first point of edges have same y value
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
			float depth1 =e1[0].depth, depth2 = e2[0].depth;
			float depth;
			// do until the scan line reaches the y value of lower point of e1
			std::cout << "y and e1[1].y >> " << y << " " << e1[1].y << std::endl;
			while(y-- > e1[1].y)
			{
				if (y>h) return; // if scanline is below the screen
				if (y<0)continue;// if scanline is above the screen
				dx = tempx2 - tempx1;
				if (dx==0)
				{
					attr = attr1;
					depth = depth1;
				}
				else 
				{
					attr = attr1 +(attr2-attr1)*(x1-tempx1)/dx;		
					depth = depth1 + (depth2-depth1)*(x1-tempx1)/dx;
				}

				int tot = inc*(x2-x1);// making positive tot
				std::cout << "tot " << tot << std::endl;
				for(int c=0;c<=tot;c++)
				{
					attr += (attr2-attr1)*(inc)/dx;
					depth += (depth2-depth1)*(inc)/dx;
					std::cout << y << " &&" << attr<< std::endl;
				}
				// update attributes and depth for two edges points in next scan line
				attr1-=(e1[0].attributes[0]-e1[1].attributes[0])/dy1;
				attr2-=(e2[0].attributes[0]-e2[1].attributes[0])/dy2;
				depth1-=(e1[0].depth-e1[1].depth)/dy1;
				depth2-=(e2[0].depth-e2[1].depth)/dy2;

				tempx1 += 1/inv_m1;
				tempx2 += 1/inv_m2;
				std::cout << "tempx1 :" << tempx1 << " tempx2 :" << tempx2 << std::endl;

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
				std::cout << "x1 :" << x1 << " x2 :" << x2 << std::endl;
			}
			// now do until the scan line reaches the y value of lower point of e2
			if (e2[1].y == e1[1].y)return;
			inv_m1 = (e2[1].x-e1[1].x)/(e2[1].y-e1[1].y); // now, the edge e1 contains second point of e1 and second point of e2, other edge is the same
			dy1 = e1[1].y-e2[1].y; // it is a new dy1 because the edge is changed now, for end point of previous e1 is already reached

			attr1 = e1[1].attributes[0] - (e1[1].attributes[0]-e2[1].attributes[0])/dy1; // other edge is one step below
			depth1 = e1[1].depth - (e1[1].depth - e2[1].depth)/dy1; // other edge is one step below

			tempx1 = e1[1].x + 1/inv_m1; // for e2, all things are the same
			// now into the loop
			while(y-- >= e2[1].y)
			{
				if (y>h) return; // if scanline is below the screen
				if (y<0)continue;// if scanline is above the screen
				dx = tempx2 - tempx1;
				attr = attr1 +(attr2-attr1)*(x1-tempx1)/dx;						// depth buffer interpolation is remaining.
				depth = depth1 +(depth2-depth1)*(x1-tempx1)/dx;

				int tot = inc*(x2-x1);// making positive tot
				for(int c=0;c<=tot;c++)
				{
					attr += (attr2-attr1)*(inc)/dx;
					depth += (depth2-depth1)*(inc)/dx;
					std::cout << y << "  " << attr<< std::endl;
				}
				// update attributes and depth for two edges points in next scan line
				attr1-=(e1[1].attributes[0]-e2[1].attributes[0])/dy1;
				attr2-=(e2[0].attributes[0]-e2[1].attributes[0])/dy2;
				depth1-=(e1[0].depth-e1[1].depth)/dy1;
				depth2-=(e2[0].depth-e2[1].depth)/dy2;

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
