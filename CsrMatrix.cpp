#include "CsrMatrix.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <execution>
#include <fstream>

CsrMatrix::CsrMatrix(std::set<std::pair<int, int>>& edgeSet, const int numVertices) : numVertices(numVertices), numEdges(edgeSet.size())
{
    nindex.resize(numVertices + 1);
    nlist.reserve(edgeSet.size());
    const int maxVertex = edgeSet.rbegin()->first;

    // for c++17 use for_each with parallel execution
    for (auto& edge : edgeSet)
    {
        nindex[edge.first + 1]++;
        nlist.push_back(edge.second);
    }

    // maxVertex + 2 is because nindex starts with a 0, and we want inclusive maxVertex
    std::partial_sum(nindex.begin(), nindex.begin() + maxVertex + 2, nindex.begin());
    // Use this for c++17
    //std::inclusive_scan(std::execution::par, nindex.begin(), nindex.begin() + maxVertex + 2, nindex.begin());

    for (auto i = maxVertex + 2; i < numVertices + 1; ++i)
    {
        nindex[i] = nindex[maxVertex + 1];
    }
}

CsrMatrix::CsrMatrix(std::istream& fstream)
{
    //TODO
}


CsrMatrix::~CsrMatrix()
= default;


//ECL-CC License
//Copyright © 2017, Texas State University. All rights reserved.
//
//Redistribution and use in source and binary forms, with or without modification, are permitted for academic, research, experimental, or personal use provided that the following conditions are met:
//
//Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//Neither the name of Texas State University nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//For all other uses, please contact the Office for Commercialization and Industry Relations at Texas State University http://www.txstate.edu/ocir/.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
//TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
void CsrMatrix::toEgrFile(const std::string& filename)
{
    if ((numVertices < 1) || (numEdges < 0)) { fprintf(stderr, "ERROR: node or edge count too low\n\n");  exit(-1); }
    int cnt;
    FILE* f = fopen(filename.c_str(), "wb");  if (f == NULL) { fprintf(stderr, "ERROR: could not open file %s\n\n", filename.c_str());  exit(-1); }
    cnt = fwrite(&numVertices, sizeof(numVertices), 1, f);  if (cnt != 1) { fprintf(stderr, "ERROR: failed to write nodes\n\n");  exit(-1); }
    cnt = fwrite(&numEdges, sizeof(numEdges), 1, f);  if (cnt != 1) { fprintf(stderr, "ERROR: failed to write edges\n\n");  exit(-1); }

    cnt = fwrite(&nindex[0], sizeof(nindex[0]), numVertices + 1, f);  if (cnt != numVertices + 1) { fprintf(stderr, "ERROR: failed to write neighbor index list\n\n");  exit(-1); }
    cnt = fwrite(&nlist[0], sizeof(nlist[0]), numEdges, f);  if (cnt != numEdges) { fprintf(stderr, "ERROR: failed to write neighbor list\n\n");  exit(-1); }

    fclose(f);
}

void CsrMatrix::toTextFile(const std::string& filename)
{

    std::ofstream ofstream(filename);
    if (ofstream.is_open())
    {
        ofstream << numVertices << " " << numEdges << std::endl;


        for (auto i = 0; i < nlist.size(); ++i)
        {
            if (i == nlist.size() - 1) { ofstream << nlist[i] << std::endl; }
            else { ofstream << nlist[i] << " "; }
        }
        for (auto i = 0; i < nindex.size(); ++i)
        {
            if (i == nindex.size() - 1) { ofstream << nindex[i]; }
            else { ofstream << nindex[i] << " "; }
        }
        ofstream.close();
    }
}


std::ostream& operator<<(std::ostream& ostream, const CsrMatrix& csr)
{
    const size_t maxPrint = 20;

    ostream << "Number of nodes = " << csr.get_num_vertices() << std::endl;
    ostream << "Number of edges = " << csr.get_num_edges() << std::endl;

    ostream << "nlist : [ ";
    int length = std::min(maxPrint, csr.nlist.size());

    for (int i = 0; i < length; ++i)
    {
        ostream << csr.nlist[i] << " ";
    }

    if (csr.nlist.size() > maxPrint) { ostream << "...]" << std::endl; }
    else { ostream << "]" << std::endl; }

    ostream << "nindex : [ ";
    length = std::min(maxPrint, csr.nindex.size());

    for (int i = 0; i < length; ++i)
    {
        ostream << csr.nindex[i] << " ";
    }

    if (csr.nindex.size() > maxPrint) { ostream << "...]" << std::endl; }
    else { ostream << "]" << std::endl; }

    return ostream;
}
