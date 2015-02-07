#pragma once

/*
	ka = ambient reflection coefficient
	kd = diffuse ....
	ks = specular .....
	ns = shinefactor
*/

struct Material
{
	Vec3 ka;
	Vec3 kd;
	Vec3 ks;
	float ns;

	Material() : 
		ka({0.01,0.01,0.01}),
        kd({0.05,0.05,0.05}),
        ks({0.05,0.05,0.05}),
        ns(20)
    {
    	std::cout << ka << " " << kd << " " << ks << std::endl;
    }
};