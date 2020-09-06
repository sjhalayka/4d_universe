// This code and data are in the public domain.

#include "main.h"

int main(void)
{	
	get_vertices_and_tetrahedra(10000);

	vector<double> curvatures;

	double total_volume = 0;

	for (size_t i = 0; i < tetrahedra.size(); i++)
	{
		if (tet_neighbours[i].size() != 4)
		{
			cout << "Error" << endl;
			return 1;
		}

		// Get volume
		vector_4 a = vertices[tetrahedra[i].vertex_indices[0]];
		vector_4 b = vertices[tetrahedra[i].vertex_indices[1]];
		vector_4 c = vertices[tetrahedra[i].vertex_indices[2]];
		vector_4 d = vertices[tetrahedra[i].vertex_indices[3]];

		total_volume += tetrahedra[i].volume(
			d_4(a, b),
			d_4(a, c), 
			d_4(a, d), 
			d_4(c, d),
			d_4(b, d),
			d_4(b, c));


		// Get curvature
		vector_4 this_tet_centre = get_tet_centre(tetrahedra[i]);

		vector_4 tet_0_centre = get_tet_centre(tetrahedra[tet_neighbours[i][0]]);
		vector_4 tet_1_centre = get_tet_centre(tetrahedra[tet_neighbours[i][1]]);
		vector_4 tet_2_centre = get_tet_centre(tetrahedra[tet_neighbours[i][2]]);
		vector_4 tet_3_centre = get_tet_centre(tetrahedra[tet_neighbours[i][3]]);

		indexed_triangle it;

		vector_4 tri_0_centre;
		vector_4 tri_1_centre;
		vector_4 tri_2_centre;
		vector_4 tri_3_centre;

		get_shared_triangle(i, tet_neighbours[i][0], it);
		tri_0_centre = get_tri_centre(it);
		
		get_shared_triangle(i, tet_neighbours[i][1], it);
		tri_1_centre = get_tri_centre(it);

		get_shared_triangle(i, tet_neighbours[i][2], it);
		tri_2_centre = get_tri_centre(it);

		get_shared_triangle(i, tet_neighbours[i][3], it);
		tri_3_centre = get_tri_centre(it);

		vector_4 n_0 = this_tet_centre - tri_0_centre;
		n_0.normalize();

		vector_4 o_0 = tri_0_centre - tet_0_centre;
		o_0.normalize();

		vector_4 n_1 = this_tet_centre - tri_1_centre;
		n_1.normalize();

		vector_4 o_1 = tri_1_centre - tet_1_centre;
		o_1.normalize();

		vector_4 n_2 = this_tet_centre - tri_2_centre;
		n_2.normalize();

		vector_4 o_2 = tri_2_centre - tet_2_centre;
		o_2.normalize();

		vector_4 n_3 = this_tet_centre - tri_3_centre;
		n_3.normalize();

		vector_4 o_3 = tri_3_centre - tet_3_centre;
		o_3.normalize();

		double d_i = (n_0.dot(o_0) + n_1.dot(o_1) + n_2.dot(o_2) + n_3.dot(o_3)) / 4.0;
		double k_i = (1.0 - d_i) / 2.0;

		curvatures.push_back(k_i);
	}

	// Print total volume
	double r3 = 0.5 * 0.5 * 0.5;
	double pi2 = pi * pi;

	cout << total_volume << " " << 2 * pi2 * r3 << endl;

	// Print average curvature
	double K = 0;

	for (size_t i = 0; i < curvatures.size(); i++)
		K += curvatures[i];

	K /= curvatures.size();

	cout << K << " +/- " << standard_deviation(curvatures) << endl;

	return 0;
}
 
