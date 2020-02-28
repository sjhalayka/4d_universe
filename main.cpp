
#include "main.h"

int main(int argc, char **argv)
{	
	get_vertices_and_tetrahedra(10);
	
	for (size_t i = 0; i < tetrahedra.size(); i++)
	{
		if (tet_neighbours[i].size() != 4)
		{
			cout << "Error: " << tet_neighbours[i].size() << endl;
			return 1;
		}

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

	}

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
