
#include "main.h"

int main(int argc, char **argv)
{	
	get_vertices_and_tetrahedra(1000);

	double K = 0;

	vector<float> edge_lengths;

	for (size_t i = 0; i < tetrahedra.size(); i++)
	{
		if (tet_neighbours[i].size() != 4)
		{
			cout << "Error" << endl;
			return 1;
		}

		vector<float> e = get_tet_edge_lengths(tetrahedra[i]);

		for (size_t j = 0; j < e.size(); j++)
			edge_lengths.push_back(e[j]);


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

		vector_4 o_0 = tet_0_centre - tri_0_centre;
		o_0.normalize();
		o_0 = -o_0;

		vector_4 n_1 = this_tet_centre - tri_1_centre;
		n_1.normalize();

		vector_4 o_1 = tet_1_centre - tri_1_centre;
		o_1.normalize();
		o_1 = -o_1;

		vector_4 n_2 = this_tet_centre - tri_2_centre;
		n_2.normalize();

		vector_4 o_2 = tet_2_centre - tri_2_centre;
		o_2.normalize();
		o_2 = -o_2;

		vector_4 n_3 = this_tet_centre - tri_3_centre;
		n_3.normalize();

		vector_4 o_3 = tet_3_centre - tri_3_centre;
		o_3.normalize();
		o_3 = -o_3;

		double d_i = (n_0.dot(o_0) + n_1.dot(o_1) + n_2.dot(o_2) + n_3.dot(o_3)) / 4.0;
		double k_i = (1.0 - d_i) / 2.0;

		K += k_i;
	}

	K /= static_cast<double>(tetrahedra.size());

	cout << 3.0 + K << endl;



	write_histogram(edge_lengths, "histogram.png");


	return 0;


	glutInit(&argc, argv);
	init_opengl(win_x, win_y);
	glutReshapeFunc(reshape_func);
	glutIdleFunc(idle_func);
	glutDisplayFunc(display_func);
	glutKeyboardFunc(keyboard_func);
	glutMouseFunc(mouse_func);
	glutMotionFunc(motion_func);
	glutPassiveMotionFunc(passive_motion_func);
	//glutIgnoreKeyRepeat(1);

	glutMainLoop();

	glutDestroyWindow(win_id);

	return 0;
}
