
#include "main.h"

int main(int argc, char **argv)
{	
	get_vertices_and_tetrahedra(10);
	
	for (size_t i = 0; i < tetrahedra.size(); i++)
	{
		if (tet_neighbours[i].size() != 4)
		{
			cout << tet_neighbours[i].size() << endl;
			return 1;
		}

		indexed_triangle it;

		get_shared_triangle(i, tet_neighbours[i][0], it);




		//cout << it.vertex_indices[0] << " ";
		//cout << it.vertex_indices[1] << " ";
		//cout << it.vertex_indices[2] << endl;

		//has_shared_triangle(i, tet_neighbours[i][1], it);

		//cout << it.vertex_indices[0] << " ";
		//cout << it.vertex_indices[1] << " ";
		//cout << it.vertex_indices[2] << endl;

		//has_shared_triangle(i, tet_neighbours[i][2], it);

		//cout << it.vertex_indices[0] << " ";
		//cout << it.vertex_indices[1] << " ";
		//cout << it.vertex_indices[2] << endl;
		//
		//has_shared_triangle(i, tet_neighbours[i][3], it);

		//cout << it.vertex_indices[0] << " ";
		//cout << it.vertex_indices[1] << " ";
		//cout << it.vertex_indices[2] << endl;




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
