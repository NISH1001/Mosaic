#pragma once
#include <Point2D.h>
#include <helper.h>

using namespace Helper; // mainly for ROUND function, other functions are SortY, Min, Max, Swap

class Rasterizer
{
	public:
		Rasterizer(){}
		~Rasterizer(){}

		// helper functions
			// helper functions end.

	static void DrawTriangle(Point2D& p1, Point2D& p2, Point2D& p3, int& w, int& h, void(*fragShader)(Point2D&), float* depthBuffer)
		{
			// first sort the points in descending order a/c y coordinate
			SortY(p1,p2,p3);

			if(p1.y == p2.y)  // the two upper points are at same y level
			{
				//std::cout << "upper base";
				// make two edges, (p1,p3) and (p2,p3)
				Point2D e1[] = {p1,p3};
				Point2D e2[] = {p2,p3};
				Interpolate(e1,e2,w, h,fragShader, depthBuffer);
			}
			else if (p2.y == p3.y) // the two lower points are at same y level
			{
				//std::cout << "lower base";
				Point2D e1[] = {p1, p2};
				Point2D e2[] = {p1, p3};
				Interpolate(e1,e2,w, h,fragShader, depthBuffer);
			}
			else // all the vertices are at different y level
			{
				// find a point with interpolated depth and attributes in edge (p1, p3)
				int dy = p3.y - p1.y;
				float inv_m = (p3.x-p1.x)/float(dy);
				int x = p1.x + inv_m*(p2.y-p1.y)+0.5;
				//std::cout << "x : " << x<<std::endl;
				// interpolated values
				float depth = p1.depth + (p3.depth-p1.depth)*(p2.y-p1.y)/dy;
				Vec3 attribute = p1.attributes[0] + (p3.attributes[0]-p1.attributes[0])*(p2.y-p1.y)/dy;
				Vec3 attrNormal = p1.attributes[1] + (p3.attributes[1]-p1.attributes[1]) * (p2.y-p1.y)/dy;
				attrNormal.NormalizeToUnit();
				// new point
				Point2D p(x, p2.y);
				// assign attributes and depth
				p.depth = depth;
				p.attributes[0] = attribute;
				p.attributes[1] = attrNormal;

				// now form two pairs of edges and send to interpolate each
				Point2D e1[] = {p1,p2};
				Point2D e2[] = {p1, p};
				Interpolate(e1, e2,w,h,fragShader, depthBuffer);
				// reassign other points to the edges
				e1[0] = p; e1[1] = p3;
				e2[0] = p2; e2[1] = p3;
				Interpolate(e1, e2,w,h,fragShader, depthBuffer);
			}
		}

		static void Interpolate(Point2D* e1, Point2D* e2, int& w, int& h, void(*fragShader)(Point2D&), float* depthBuffer)
		{
			// function receives flat top or flat bottom triangle
			// make sure that e1 is left edge
			if(e1[0].x > e2[0].x or e1[1].x > e2[1].x) // if e1 is on right, swap the edges
				Swap(e1, e2);

			int l1x0 = e1[0].x, l1x1 = e1[1].x;
			int l2x0 = e2[0].x, l2x1 = e2[1].x;
			int l1y0 = e1[0].y, l1y1 = e1[1].y;
			int l2y0 = e2[0].y, l2y1 = e2[1].y;

			int dx1 = l1x0 - l1x1;
			int dx2 = l2x0 - l2x1;

			int dy = l1y0 - l1y1; // dy is same for both lines

			// inverse slopes
			float inv_m1 = float(dx1)/dy;
			float inv_m2 = float(dx2)/dy;

			// attributes
			Vec3 attr1, attr2, attr, dAttr1, dAttr2;
			attr1 = e1[0].attributes[0];
			attr2 = e2[0].attributes[0];
			
			// values of attribute to be increased at each scan line
			dAttr1 = (e1[0].attributes[0] - e1[1].attributes[0])/dy;
			dAttr2 = (e2[0].attributes[0] - e2[1].attributes[0])/dy;
			
			// depths and values to be increased at each scan line
			float depth1, depth2, depth, dDepth1, dDepth2;
			dDepth1 = (e1[0].depth - e1[1].depth)/dy;
			dDepth2 = (e2[0].depth - e2[1].depth)/dy;
			depth1 = e1[0].depth;
			depth2 = e2[0].depth;
			
			int y = l1y0;
			float x1 = l1x0, x2 = l2x0;

			int clippedx1, clippedx2;
			// begin loop
			while( y >= l1y1) // both edges have lower y value same, so no matter we take l1y1 or l2y1
			{
				if(y < 0) break; // as we move from top to bottom
				
				if(!(x2 < 0 or x1 > w or y > h)) // scan line is not outside the screen
				{

					clippedx1 = Max(ROUND(x1), 0); // clipped x1 value
					clippedx2 = Min(ROUND(x2), w); // clipped x2 value
	
					int dx = ROUND(x2)-ROUND(x1);

					attr = attr1;
					depth = depth1;
	
					if (clippedx1 != ROUND(x1)) // means x-clipping has occured and thus attribute at clipped value is different than attr1
					{
						attr = attr1+(attr2-attr1)*(clippedx1-ROUND(x1))/dx;
						depth = depth1+(depth2-depth1)*(clippedx1-ROUND(x1))/dx;
					}
	
					// plot the first point
					if( depth < depthBuffer[y*w + clippedx1] and depth > -1)
						{
							Point2D p(clippedx1, y);
							p.attributes[0] = attr;
							depthBuffer[y*w + clippedx1] = depth;
							fragShader(p);
						}
					// plot other points	
					for(int x=clippedx1+1;x<=clippedx2;x++)
					{
						attr+= (attr2-attr1)/dx;
						depth+= (depth2-depth1)/dx;
						if( depth < depthBuffer[y*w + x] and depth >= -1)
						{
							Point2D p(x, y);
							p.attributes[0] = attr;
							depthBuffer[y*w+x] = depth;
							fragShader(p);
						}
				}
			}
			attr1 -= dAttr1;
			attr2 -= dAttr2;
			depth1 -= dDepth1;
			depth2 -= dDepth2;

			x1-=inv_m1;
			x2-=inv_m2;

			y--;
		}
	}
};

		
