#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	std::ofstream outfile("water.obj");
	float y = 0.f; // water level at y=0.f

	int breadth=21, length=31;

	std::vector<int> indices;
	// we have 31x21 points each at distance of 0.5
	// first write vertices
	int count=0;
	for(int i=0;i<breadth;i++)
		for(int j=0;j<length;j++)
		{
			outfile << "v " << j/float(length-1) << " "<<j<<" "<<i/float(breadth-1)<<"\n";
		}
	// write the only one vertex normal, that is 0,1,0
	outfile << "\nvn " << "0.0 1.0 0.0\n\n";
	
	// now faces
	for(int i=0;i<breadth-1;i++)
		for(int j=0;j<length-1;j++)
		{
			outfile <<"f "<< j+i*length+1<< "//1 "<<j+(i+1)*length+1<<"//1 "<<j+1+i*length+1<<"//1\n";
			outfile<<"f "<<j+1+i*length+1<<"//1 "<<j+(i+1)*length+1<<"//1 "<<j+1+(i+1)*length+1<<"//1\n";
		}

	return 0;
}

