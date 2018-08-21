#pragma once

#include <set>
#include <vector>
#include <istream>

/**
 * \brief The compressed sparse row (CSR) or compressed row storage (CRS) format represents
 *  a matrix M by three (one-dimensional) arrays, that respectively contain nonzero values,
 *  the extents of rows, and column indices. It is similar to COO, but compresses the row indices,
 *  hence the name. This format allows fast row access and matrix-vector multiplications (Mx).
 *  [https://en.wikipedia.org/wiki/Sparse_matrix]
 *
 *  Data matrix is excluded because it is not relevant in Connected component algorithms.
 */
class CsrMatrix
{

public:
    /**
     * \brief Create a CSR matrix from a sorted edgeset.
     * \param edgeSet sorted set of edges
     * \param numVertices number of vertices in graph
     */
    CsrMatrix(std::set<std::pair<int, int>>& edgeSet, int numVertices);

    /**
     * \brief Create a CSR matrix from an input stream. Edges must be read in order.
     * \param fstream a filestream
     */
    CsrMatrix(std::istream& fstream);
    ~CsrMatrix();

    friend std::ostream& operator<< (std::ostream& ostream, const CsrMatrix& csr);

    /**
     * \brief Write CSR matrix to a binary file
     * \param filename file path
     */
    void toEgrFile(const std::string& filename);
    /**
     * \brief Write CSR matrix to a text file
     * \param filename file path
     */
    void toTextFile(const std::string& filename);

    std::vector<int> getNlist() const { return nlist; }
    std::vector<int> getNindex() const { return nindex; }
    std::vector<int> getData() const { return data; }
    int get_num_vertices() const { return numVertices; }
    int get_num_edges() const { return numEdges; }

private:
    std::vector<int> nlist;
    std::vector<int> nindex;
    std::vector<int> data;
    int numVertices{};
    int numEdges{};
};

