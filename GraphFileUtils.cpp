
#include "GraphFileUtils.h"
#include <fstream>
#include <set>
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;


void ReadEgrFile(int & nodes, int & edges, int ** nindex, int ** nlist, const std::string & filename)
{
    FILE* f = fopen(filename.c_str(), "rb");  if (f == NULL) { fprintf(stderr, "ERROR: could not open file %s\n\n", filename.c_str());  exit(-1); }
    int cnt = fread(&nodes, sizeof(nodes), 1, f);  if (cnt != 1) { fprintf(stderr, "ERROR: failed to read nodes\n\n");  exit(-1); }
    cnt = fread(&edges, sizeof(edges), 1, f);  if (cnt != 1) { fprintf(stderr, "ERROR: failed to read edges\n\n");  exit(-1); }
    if ((nodes < 1) || (edges < 0)) { fprintf(stderr, "ERROR: node or edge count too low\n\n");  exit(-1); }

    *nindex = (int*)malloc((nodes + 1) * sizeof(nindex[0]));
    *nlist = (int*)malloc(edges * sizeof(nlist[0]));
    if ((nindex == NULL) || (nlist == NULL)) { fprintf(stderr, "ERROR: memory allocation failed\n\n");  exit(-1); }

    cnt = fread(*nindex, sizeof(*nindex[0]), nodes + 1, f);  if (cnt != nodes + 1) { fprintf(stderr, "ERROR: failed to read neighbor index list\n\n");  exit(-1); }
    cnt = fread(*nlist, sizeof(*nlist[0]), edges, f);  if (cnt != edges) { fprintf(stderr, "ERROR: failed to read neighbor list\n\n");  exit(-1); }

    fclose(f);
}

int ReadMtxFile(const std::string& filename, std::set<Edge>& edgeList)
{
    fs::path filePath = filename;
    if (!fs::is_regular_file(filePath)) { throw std::invalid_argument("File does not exist"); }
    if (!(filePath.extension() == ".mtx")) { throw std::invalid_argument("Wrong file format, expected : \".mtx\" was : " + filePath.extension().string() + "\""); }

    std::ifstream ifs(filePath, std::ifstream::in);
    std::string nextLine;

    bool firstLine = true;
    int numVert = 0;


    while (std::getline(ifs, nextLine))
    {
        if (nextLine[0] == '%') continue; // skip comments

        if (firstLine) // read number of vertices
        {
            firstLine = false;
            numVert = std::stoi(nextLine.substr(0, nextLine.find_first_of(' ')));
            continue;
        }

        const std::size_t found = nextLine.find_first_of(' ');
        const int numDigitsToRead = nextLine.find_first_of(' ', found + 1) - (found + 1);

        int edgeFrom = std::stoi(nextLine.substr(0, found)) - 1;
        int edgeTo = std::stoi(nextLine.substr(found + 1, numDigitsToRead)) - 1;

        if (edgeFrom == edgeTo) continue; // loops not allowed
        const Edge edge = { edgeFrom,edgeTo };
        const Edge edgeO = { edgeTo,edgeFrom };
        edgeList.insert(edge);
        edgeList.insert(edgeO);
    }

    return numVert;
}

int ReadTxtFile(const std::string& filename, std::set<Edge>& edgeList)
{
    fs::path filePath = filename;
    if (!fs::is_regular_file(filePath)) { throw std::invalid_argument("File does not exist"); }
    if (!(filePath.extension() == ".txt")) { throw std::invalid_argument("Wrong file format, expected : \".txt\" was : " + filePath.extension().string() + "\""); }

    std::ifstream ifs(filePath, std::ifstream::in);
    std::string nextLine;

    int numVert = 0;


    while (std::getline(ifs, nextLine))
    {
        if (nextLine[0] == '#')
        {
            if (nextLine.find("Nodes:") != std::string::npos && nextLine.find("Edges:") != std::string::npos)
            {
                const auto cutFrom = nextLine.find_first_of(':') + 1;
                const auto cutTo = nextLine.find(' ', cutFrom + 2);
                const auto numDigitsToRead = cutTo - cutFrom;
                numVert = std::stoi(nextLine.substr(cutFrom, numDigitsToRead));
            }

            continue;
        }

        const std::size_t found = nextLine.find_first_of('\t');


        int edgeFrom = std::stoi(nextLine.substr(0, found));
        int edgeTo = std::stoi(nextLine.substr(found + 1));

        if (edgeFrom == edgeTo) continue; // loops not allowed
        const Edge edge = { edgeFrom,edgeTo };
        const Edge edgeO = { edgeTo,edgeFrom };
        edgeList.insert(edge);
        edgeList.insert(edgeO);
    }

    return numVert;
}

int ReadGrFile(const std::string& filename, std::set<Edge>& edgeList)
{
    fs::path filePath = filename;
    if (!fs::is_regular_file(filePath)) { throw std::invalid_argument("File does not exist"); }
    if (!(filePath.extension() == ".gr")) { throw std::invalid_argument("Wrong file format, expected : \".txt\" was : " + filePath.extension().string() + "\""); }

    std::ifstream ifs(filePath, std::ifstream::in);
    std::string nextLine;

    int numVert = 0;


    while (std::getline(ifs, nextLine))
    {
        if (nextLine[0] == 'p' && nextLine.find("sp") != std::string::npos)
        {
            const auto cutFrom = 5;
            const auto cutTo = nextLine.find(' ', cutFrom);
            const auto numDigitsToRead = cutTo - cutFrom;
            numVert = std::stoi(nextLine.substr(cutFrom, numDigitsToRead));
            continue;
        }

        if (nextLine[0] == 'a')
        {
            const std::size_t found = nextLine.find_first_of(' ');
            const std::size_t found2 = nextLine.find_first_of(' ', found + 1);

            int edgeFrom = std::stoi(nextLine.substr(found, found2 - found)) - 1;
            int edgeTo = std::stoi(nextLine.substr(found2 + 1)) - 1;

            if (edgeFrom == edgeTo) continue; // loops not allowed
            const Edge edge = { edgeFrom,edgeTo };
            const Edge edgeO = { edgeTo,edgeFrom };
            edgeList.insert(edge);
            edgeList.insert(edgeO);
        }

    }

    return numVert;
}

void WriteEdgeList(const int numVertices, std::set<Edge>& edgeList, const std::string& filename)
{
    std::ofstream ofstream(filename);
    if (ofstream.is_open())
    {
        ofstream << numVertices << " " << edgeList.size() << std::endl;
        for (auto && edge : edgeList)
        {
            ofstream << edge.first << " " << edge.second << std::endl;
        }

        ofstream.close();
    }
}




