#pragma once
#define ROUND(x) x>0 ? int(x+0.5) : int(x-0.5)
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

	void SortY(Point2D& m_p1, Point2D& m_p2, Point2D& m_p3)
	{
		if (m_p1.y < m_p2.y) 
		{
			Point2D temp = m_p1;
			m_p1 = m_p2;
			m_p2 = temp;
		}
		if (m_p2.y < m_p3.y) 
		{
			Point2D temp = m_p2;
			m_p2 = m_p3;
			m_p3 = temp;

		} ///largest yvalue coord is at 1
		if (m_p1.y < m_p2.y) 
		{
			Point2D temp = m_p1;
			m_p1 = m_p2;
			m_p2 = temp;
		}
	}
	// helper functions end.

		void DrawTriangle(Point2D& p1, Point2D& p2, Point2D& p3, int& w, int& h, void(*fragShader)(Point2D&), float* depthBuffer)
		{
			// first sort the points in descending order a/c y coordinate
			SortY(p1,p2,p3);

			if(p1.y == p2.y)  // the two upper points are at same y level
			{
				//std::cout << "upper base";
				// make two edges, (p1,p3) and (p2,p3)
				Point2D e1[] = {p1,p3};
				Point2D e2[] = {p2,p3};
				Interpolate(e1,e2,w,h,fragShader, depthBuffer);
			}
			else if (p2.y == p3.y) // the two lower points are at same y level
			{
				//std::cout << "lower base";
				Point2D e1[] = {p1, p2};
				Point2D e2[] = {p1, p3};
				Interpolate(e1,e2,w,h,fragShader, depthBuffer);
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
				// new point
				Point2D p(x, p2.y);
				// assign attributes and depth
				p.depth = depth;
				p.attributes[0] = attribute;

				// now form two pairs of edges and send to interpolate each
				Point2D e1[] = {p1,p2};
				Point2D e2[] = {p1, p};
				Interpolate(e1, e2, w,h,fragShader, depthBuffer);
				// reassign other points to the edges
				e1[0] = p; e1[1] = p3;
				e2[0] = p2; e2[1] = p3;
				Interpolate(e1, e2, w,h,fragShader, depthBuffer);
				
			}
		}
		
		void Interpolate(Point2D* e1, Point2D* e2, int& w, int& h, void(*fragShader)(Point2D&), float* depthBuffer)
		{
			// this function assumes flat bottom or top
			// make sure that e1 is left edge
			if(e1[0].x > e2[0].x or e1[1].x > e2[1].x) // means if e1 is on the right
			{
				// swap the edges
				Point2D* temp = e1;
				e1 = e2;
				e2 = temp;
			}
			// now we have e1 on the left of e2

			int dx1 = e1[0].x-e1[1].x; // dx for first edge
			int dx2 = e2[0].x-e2[1].x; // dx for second edge
			int dy = e1[0].y - e1[1].y;
			int cnt1 = 0, cnt2 = 0;    // counter for increment of x value(but this works only when dy>dx)
			float inv_m1 = float(dx1)/dy;
			float inv_m2 = float(dx2)/dy;
			int xinc1=1, xinc2=1;

			if(dx1<0) 
				xinc1 = -1;
			if(dx2<0)
				xinc2 = -1;

			int absdx1 = abs(dx1);
			int absdx2 = abs(dx2);
			//std::cout << "inv_m1 : " << inv_m1 << "  inv_m2 : " << inv_m2 << std::endl;

			int yScan = e1[0].y; // both the first point of edges have same y value
			// starting from topmost y

			float x1 = e1[0].x, x2 = e2[0].x; // x1 and x2 are the x values for respective edges(which may be outside x=0 and x=w).
			float clipx1, clipx2; // clipped x values
			int dx;
			// attributes
			Vec3 attr1, attr2, attr, dAttr1, dAttr2;
			attr1 = e1[0].attributes[0]; // attribute on the starting point of scan line
			attr2 = e2[0].attributes[0]; // attribute on the end point of scan line
			dAttr1 = (e1[0].attributes[0]-e1[1].attributes[0])/dy; // value of attribure to be increased at each scan line
			dAttr2 = (e2[0].attributes[0]-e2[1].attributes[0])/dy;
			// depths
			float depth1, depth2, depth, dDepth1, dDepth2;
			dDepth1 = (e1[0].depth - e1[1].depth)/dy;
			dDepth2 = (e2[0].depth - e2[1].depth)/dy;
			depth1 = e1[0].depth;
			depth2 = e2[0].depth;
//			std::cout << "test\n";
			while(yScan >= e1[1].y) 	// both edges have lower y value same, we can take any y
			{
				dx = x2-x1;
				clipx1 = Max(Min(ROUND(x1),w), 0);
				clipx2 = Min(Max(ROUND(x2),0), w); 
				if (dx !=0)
				{
					attr = attr1 + (attr2-attr1)*(clipx1-x1)/dx; // attribute of the first point of clipped scan line
					depth = depth1 + (depth2-depth1)*(clipx1-x1)/dx;
				}
				else 
				{
					attr = attr1;
					depth = depth1;
				}
				int x = clipx1;
				do 
				{
//					std::cout << "x: " << x << " y: " << yScan <<std::endl;
					if (/*depth<0 and depth > 1*/0/* 0 for testing only*/) // discard the point
						continue;
					else
					{
						if(1 /*depth > depthBuffer[yScan*w + x]*/) // write to FB
							{
							// update depthBuffer value
							//depthBuffer[yScan*w + x] = depth;
							Point2D temp(x, yScan);
							temp.attributes[0] = attr;
				//			temp.depth = depth;
							fragShader(temp);
						}
					}
//					std::cout << "( " << yScan << " , " << x<< ") \n ";
					x++;
					attr += (attr2-attr1)/dx;
					depth += (depth2-depth1)/dx;
				}while(x <= clipx2);
				//std::cout << std::endl;

				attr1 -= dAttr1;
				attr2 -= dAttr2;
				depth1 -= dDepth1;
				depth2 -= dDepth2;

				if(absdx1>dy)
				{
					x1-=inv_m1;
				}
				else 
				{
					cnt1+=2*absdx1;
					if(cnt1>=dy)
					{
						cnt1 -= 2*dy;
						x1-=xinc1;
					}
				}

				if(absdx2>dy)
				{
					x2-=inv_m2;
				}
				else 
				{
					cnt2+=2*absdx2;
					if(cnt2>=dy)
					{
						cnt2 -= 2*dy;
						x2-=xinc2;
					}
				}
				yScan--;
			}
		}
};
