#pragma once
#include <string>
#include <vector>
#include <set>

typedef std::pair<int, int> Edge;


/**
 * \brief Read .egr file into memory
 * \param nodes number of nodes
 * \param edges number of edges
 * \param nindex nindex
 * \param nlist nlist
 * \param filename file path
 *
 * //ECL-CC License
 * Copyright © 2017, Texas State University. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted for academic, research, experimental, or personal use provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * Neither the name of Texas State University nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * For all other uses, please contact the Office for Commercialization and Industry Relations at Texas State University http://www.txstate.edu/ocir/.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
void ReadEgrFile(int& nodes, int& edges, int** nindex, int** nlist, const std::string& filename);

/**
 * \brief Read .mtx file and returns an edge set. Loops and multiple edges between the same two vertices are ignored.
 * \param filename file path
 * \param edgeList empty set that will be filled with edges
 * \return number of nodes in graph
 */
int ReadMtxFile(const std::string& filename, std::set<Edge>& edgeList);
/**
 * \brief Read .txt file and returns a edge set. Loops and multiple edges between the same two vertices are ignored.
 * \param filename file path
 * \param edgeList empty set that will be filled with edges
 * \return number of nodes in graph
 */
int ReadTxtFile(const std::string& filename, std::set<Edge>& edgeList);
/**
 * \brief Read .gr file and return a edge set. Loops and multiple edges between the same two vertices are ignored.
 * \param filename file path
 * \param edgeList empty set that will be filled with edges
 * \return number of nodes in graph
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