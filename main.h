
// This code and data are in the public domain.


#ifndef main_H
#define main_H


#include "custom_math.h"
using namespace custom_math;




#include <fstream>
#include <ios>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;



vector<vector_4> vertices;
vector<indexed_tetrahedron> tetrahedra;
map<size_t, vector<size_t> > tet_neighbours;









vector_4 get_tri_centre(const indexed_triangle& it)
{
	vector_4 ret;

	vector_4 a = vertices[it.vertex_indices[0]];
	vector_4 b = vertices[it.vertex_indices[1]];
	vector_4 c = vertices[it.vertex_indices[2]];

	ret = a + b + c;

	ret = ret / 3.0;

	return ret;
}

vector_4 get_tet_centre(const indexed_tetrahedron& it)
{
	vector_4 ret;

	vector_4 a = vertices[it.vertex_indices[0]];
	vector_4 b = vertices[it.vertex_indices[1]];
	vector_4 c = vertices[it.vertex_indices[2]];
	vector_4 d = vertices[it.vertex_indices[3]];

	ret = a + b + c + d;

	ret = ret / 4.0;

	return ret;
}

vector<float> get_tet_edge_lengths(const indexed_tetrahedron& it)
{
	vector<float> ret;

	vector_4 v0 = vertices[it.vertex_indices[0]];
	vector_4 v1 = vertices[it.vertex_indices[1]];
	vector_4 v2 = vertices[it.vertex_indices[2]];
	vector_4 v3 = vertices[it.vertex_indices[3]];

	ret.push_back(static_cast<float>(d_4(v0, v1)));
	ret.push_back(static_cast<float>(d_4(v0, v2)));
	ret.push_back(static_cast<float>(d_4(v0, v3)));
	ret.push_back(static_cast<float>(d_4(v1, v3)));
	ret.push_back(static_cast<float>(d_4(v3, v2)));
	ret.push_back(static_cast<float>(d_4(v2, v1)));

	return ret;
}

void get_sorted_tris_from_tetrahedron(size_t tet_index, vector<indexed_triangle>& tris)
{
	tris.clear();

	indexed_triangle it;
	vector<size_t> sorted_vertex_indices;

	// do tri 0
	it.vertex_indices[0] = tetrahedra[tet_index].vertex_indices[0];
	it.vertex_indices[1] = tetrahedra[tet_index].vertex_indices[1];
	it.vertex_indices[2] = tetrahedra[tet_index].vertex_indices[3];

	sorted_vertex_indices.clear();
	sorted_vertex_indices.push_back(it.vertex_indices[0]);
	sorted_vertex_indices.push_back(it.vertex_indices[1]);
	sorted_vertex_indices.push_back(it.vertex_indices[2]);

	sort(sorted_vertex_indices.begin(), sorted_vertex_indices.end());

	it.vertex_indices[0] = sorted_vertex_indices[0];
	it.vertex_indices[1] = sorted_vertex_indices[1];
	it.vertex_indices[2] = sorted_vertex_indices[2];

	tris.push_back(it);

	// do tri 1
	it.vertex_indices[0] = tetrahedra[tet_index].vertex_indices[0];
	it.vertex_indices[1] = tetrahedra[tet_index].vertex_indices[2];
	it.vertex_indices[2] = tetrahedra[tet_index].vertex_indices[3];

	sorted_vertex_indices.clear();
	sorted_vertex_indices.push_back(it.vertex_indices[0]);
	sorted_vertex_indices.push_back(it.vertex_indices[1]);
	sorted_vertex_indices.push_back(it.vertex_indices[2]);

	sort(sorted_vertex_indices.begin(), sorted_vertex_indices.end());

	it.vertex_indices[0] = sorted_vertex_indices[0];
	it.vertex_indices[1] = sorted_vertex_indices[1];
	it.vertex_indices[2] = sorted_vertex_indices[2];

	tris.push_back(it);

	// do tri 2
	it.vertex_indices[0] = tetrahedra[tet_index].vertex_indices[0];
	it.vertex_indices[1] = tetrahedra[tet_index].vertex_indices[1];
	it.vertex_indices[2] = tetrahedra[tet_index].vertex_indices[2];

	sorted_vertex_indices.clear();
	sorted_vertex_indices.push_back(it.vertex_indices[0]);
	sorted_vertex_indices.push_back(it.vertex_indices[1]);
	sorted_vertex_indices.push_back(it.vertex_indices[2]);

	sort(sorted_vertex_indices.begin(), sorted_vertex_indices.end());

	it.vertex_indices[0] = sorted_vertex_indices[0];
	it.vertex_indices[1] = sorted_vertex_indices[1];
	it.vertex_indices[2] = sorted_vertex_indices[2];

	tris.push_back(it);

	// do tri 3
	it.vertex_indices[0] = tetrahedra[tet_index].vertex_indices[1];
	it.vertex_indices[1] = tetrahedra[tet_index].vertex_indices[2];
	it.vertex_indices[2] = tetrahedra[tet_index].vertex_indices[3];

	sorted_vertex_indices.clear();
	sorted_vertex_indices.push_back(it.vertex_indices[0]);
	sorted_vertex_indices.push_back(it.vertex_indices[1]);
	sorted_vertex_indices.push_back(it.vertex_indices[2]);

	sort(sorted_vertex_indices.begin(), sorted_vertex_indices.end());

	it.vertex_indices[0] = sorted_vertex_indices[0];
	it.vertex_indices[1] = sorted_vertex_indices[1];
	it.vertex_indices[2] = sorted_vertex_indices[2];

	tris.push_back(it);
}


bool get_shared_triangle(size_t tet_index_0, size_t tet_index_1, indexed_triangle &it)
{
	it.vertex_indices[0] = 0;
	it.vertex_indices[1] = 0;
	it.vertex_indices[2] = 0;

	vector<indexed_triangle> tris;
	get_sorted_tris_from_tetrahedron(tet_index_0, tris);

	vector<indexed_triangle> neighbour_tris;
	get_sorted_tris_from_tetrahedron(tet_index_1, neighbour_tris);

	for (size_t i = 0; i < tris.size(); i++)
	{
		for (size_t j = 0; j < neighbour_tris.size(); j++)
		{
			if (tris[i] == neighbour_tris[j])
			{
				it = tris[i];
				return true;
			}
		}
	}

	return false;
}


void get_all_tet_neighbours(void)
{
	tet_neighbours.clear();

	vector<size_t> default_lookup;

	for (size_t i = 0; i < tetrahedra.size(); i++)
		tet_neighbours[i] = default_lookup;

	cout << "Enumerating shared faces" << endl;

	map<indexed_triangle, vector<size_t> > neighbours;

	for (size_t i = 0; i < tetrahedra.size(); i++)
	{
		if(i % 100 == 0)
		cout << i + 1 << " of " << tetrahedra.size() << endl;

		vector<indexed_triangle> tris;

		get_sorted_tris_from_tetrahedron(i, tris);

		for (size_t j = 0; j < tris.size(); j++)
			neighbours[tris[j]].push_back(i);
	}

	cout << "Processing shared faces" << endl;

	size_t count = 0;

	for (map<indexed_triangle, vector<size_t> >::const_iterator ci = neighbours.begin(); ci != neighbours.end(); ci++)
	{
		if (count % 100 == 0)
			cout << count + 1 << " of " << neighbours.size() << endl;

		count++;

		tet_neighbours[ci->second[0]].push_back(ci->second[1]);
		tet_neighbours[ci->second[1]].push_back(ci->second[0]);
	}
}



void get_vertices_and_tetrahedra(const size_t num_vertices)
{
	vertices.clear();
	tetrahedra.clear();

	ostringstream oss;
	oss << num_vertices;

	// rbox s 10 D4 | qconvex i Qt

	string rbox_cmdline = "rbox s ";
	rbox_cmdline += oss.str();
	rbox_cmdline += " D4 > vertices.txt";

	system(rbox_cmdline.c_str());

	ifstream rbox_file("vertices.txt");

	string rbox_cmdline_short;

	string line;
	getline(rbox_file, rbox_cmdline_short);
	getline(rbox_file, line);

	for (size_t i = 0; i < num_vertices; i++)
	{
		getline(rbox_file, line);

		istringstream iss(line);

		vector_4 v;
		iss >> v.x;
		iss >> v.y;
		iss >> v.z;
		iss >> v.w;

		vertices.push_back(v);
	}
	
	rbox_file.close();


	//ofstream rbox_file_out("vertices.txt");

	//rbox_file_out << rbox_cmdline_short << endl;
	//rbox_file_out << vertices.size() << endl;


	//// Process vertices here...
	//// e.g. gravitational attraction


	//for (size_t i = 0; i < vertices.size(); i++)
	//	rbox_file_out << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << " " << vertices[i].w << endl;

	//rbox_file_out.close();

	
	
	string qconvex_cmdline = "\"qconvex i Qt < vertices.txt\" > tetrahedra.txt";

	system(qconvex_cmdline.c_str());

	ifstream qconvex_file("tetrahedra.txt");

	getline(qconvex_file, line);
	
	istringstream iss_tetrahedron_count(line);

	size_t num_tetrahedra = 0;
	iss_tetrahedron_count >> num_tetrahedra;

	for (size_t i = 0; i < num_tetrahedra; i++)
	{
		getline(qconvex_file, line);

		istringstream iss(line);

		indexed_tetrahedron t;
		iss >> t.vertex_indices[0];
		iss >> t.vertex_indices[1];
		iss >> t.vertex_indices[2];
		iss >> t.vertex_indices[3];

		tetrahedra.push_back(t);
	}

	cout << "Vertex count:      " << vertices.size() << endl;
	cout << "Tetrahedron count: " << tetrahedra.size() << endl;

	get_all_tet_neighbours();
}


double standard_deviation(const vector<double>& src)
{
	double mean = 0;
	double size = static_cast<double>(src.size());

	for (size_t i = 0; i < src.size(); i++)
		mean += src[i];

	mean /= size;

	double sq_diff = 0;

	for (size_t i = 0; i < src.size(); i++)
	{
		double diff = src[i] - mean;
		sq_diff += diff * diff;
	}

	sq_diff /= size;
	
	return sqrt(sq_diff);
}



#endif
