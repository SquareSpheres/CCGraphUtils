#pragma once
#include <string>
#include <vector>
#include <set>

typedef std::pair<int, int> Edge;

/**
 * \brief Read .mtx file and returns an edge set. Loops and multiple edges between the same two vertices are ignored.
 * \param filename file path
 * \param edgeList empty set that will be filled with edges
 * \return set with edges
 */
int ReadMtxFile(const std::string& filename, std::set<Edge>& edgeList);
/**
 * \brief Read .txt file and returns a edge set. Loops and multiple edges between the same two vertices are ignored.
 * \param filename file path
 * \param edgeList empty set that will be filled with edges
 * \return set with edges
 */
int ReadTxtFile(const std::string& filename, std::set<Edge>& edgeList);
/**
 * \brief Read .gr file and return a edge set. Loops and multiple edges between the same two vertices are ignored.
 * \param filename file path
 * \param edgeList empty set that will be filled with edges
 * \return set with edges
 */
int ReadGrFile(const std::string& filename, std::set<Edge>& edgeList);
/**
 * \brief Write edge list to file in readable format, i.e. each edge is on a seperate line with a single space splitting
 *  the e_from -> e_to. The first line is number of nodes and edges.
 * \param numVertices number of vertices in graph
 * \param edgeList a set with all the edges
 * \param filename path to where file should be saved
 */
void WriteEdgeList(int numVertices, std::set<Edge>& edgeList, const std::string& filename);