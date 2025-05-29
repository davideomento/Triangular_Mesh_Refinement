#include "empty_class.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;


namespace ProjectLibrary
{
    Vertices::Vertices(const int& id, const int& marker, const double& x, const double& y):
        id(id), marker(marker), x(x), y(y)
    {
    }


    Edges::Edges(const int& id, const int& marker, const int& idStart, const int& idEnd, const bool& inMesh, const vector<Vertices>& vertices):
        id(id), marker(marker), idStart(idStart), idEnd(idEnd), inMesh(inMesh)
    {
        length = sqrt(pow(vertices[idEnd].x - vertices[idStart].x, 2) + pow(vertices[idEnd].y - vertices[idStart].y, 2));
    }


    Triangles::Triangles(const int& id, const int& idV1, const int& idV2, const int& idV3, const int& idE1, const int& idE2, const int& idE3, const bool& inMesh, const vector<Vertices>& vertices):
        id(id), idV1(idV1), idV2(idV2), idV3(idV3), idE1(idE1), idE2(idE2), idE3(idE3), inMesh(inMesh)
    {
        area =  0.5 * abs(vertices[idV1].x * (vertices[idV2].y - vertices[idV3].y) + vertices[idV2].x * (vertices[idV3].y - vertices[idV1].y) + vertices[idV3].x * (vertices[idV1].y - vertices[idV2].y));
    }


    Vertices Edges::midPoint(const vector<Vertices>& vertices)
    {
        double x_midpoint = (vertices[idStart].x + vertices[idEnd].x) * 0.5;
        double y_midpoint = (vertices[idStart].y + vertices[idEnd].y) * 0.5;

        Vertices midPoint(vertices.size(), 0, x_midpoint, y_midpoint);

        return midPoint;
    }


    Edges Triangles::FindMaxEdge(const vector<Edges>& edges)
    {
        if(edges[idE1] > edges[idE2] && edges[idE1] > edges[idE3])
        {
            return edges[idE1];
        }
        else if(edges[idE2] > edges[idE1] && edges[idE2] > edges[idE3])
        {
            return edges[idE2];
        }
        else
        {
            return edges[idE3];
        }
    }


    vector<Vertices> ImportVertices(const string& nameFile)
    {
        vector<Vertices> vertices;

        ifstream file;
        file.open(nameFile);

        if(file.fail())
        {
            cerr << "Errore nell'apertura del file: " << nameFile << endl;
            return vertices;
        }

        string line;
        getline(file,line);
        while (getline(file, line))
        {
            if (file.eof())
            {
                break;
            }

            int id, marker;
            double x,y;

            istringstream convert;
            convert.str(line);
            convert >> id >> marker >> x >> y;

            Vertices vertex(id, marker, x, y);
            vertices.push_back(vertex);
        }

        file.close();

        return vertices;
    }


    vector<Edges> ImportEdges(const string& nameFile, const vector<Vertices>& vertices)
    {
        vector<Edges> edges;

        ifstream file;
        file.open(nameFile);

        if(file.fail())
        {
            cerr << "Errore nell'apertura del file: " << nameFile << endl;
            return edges;
        }

        string line;
        getline(file,line);
        while (getline(file,line))
        {
            if(file.eof())
            {
                break;
            }

            int id, marker;
            int idStartVer, idEndVer;

            istringstream convert;
            convert.str(line);
            convert >> id >> marker >> idStartVer >> idEndVer;

            Edges edge(id, marker, idStartVer, idEndVer, true, vertices);

            edges.push_back(edge);
        }

        file.close();

        return edges;
    }


    vector<Triangles> ImportTriangles(const string& nameFile, const vector<Vertices>& vertices)
    {
        vector<Triangles> triangles;

        ifstream file;
        file.open(nameFile);

        if(file.fail())
        {
            cerr << "Errore nell'apertura del file: " << nameFile << endl;
            return triangles;
        }

        string line;
        getline(file,line);
        while (getline(file,line))
        {
            if(file.eof())
            {
                break;
            }

            int id;
            int idV1, idV2, idV3;
            int idE1, idE2, idE3;

            istringstream convert;
            convert.str(line);
            convert >> id >> idV1 >> idV2 >> idV3 >> idE1 >> idE2 >> idE3;

            Triangles triangle(id, idV1, idV2, idV3, idE1, idE2, idE3, true, vertices);

            triangles.push_back(triangle);
        }

        file.close();

        return triangles;
    }


    vector<int> findAdiacenceEdge(const Edges& edge, const vector<Triangles>& triangles)
    {
        vector<int> adiacenceVector;
        int idEdge = edge.id;
        for(unsigned int i=0; i<triangles.size(); i++)
        {
            if(triangles[i].inMesh == true)
            {
                if(triangles[i].idE1 == idEdge)
                {
                    adiacenceVector.push_back(triangles[i].id);
                }
                else if(triangles[i].idE2 == idEdge)
                {
                    adiacenceVector.push_back(triangles[i].id);
                }
                else if(triangles[i].idE3 == idEdge)
                {
                        adiacenceVector.push_back(triangles[i].id);
                }
            }
        }

        return adiacenceVector;
    }


    int findOppositeIdVertices(const Edges& edge, const Triangles& triangle)
    {
        if (triangle.idV1 != edge.idStart && triangle.idV1 != edge.idEnd)
        {
            return triangle.idV1;
        }
        else if (triangle.idV2 != edge.idStart && triangle.idV2 != edge.idEnd)
        {
            return triangle.idV2;
        }
        else if (triangle.idV3 != edge.idStart && triangle.idV3 != edge.idEnd)
        {
            return triangle.idV3;
        }
        else
        {
            cerr<<"Nella function findOppositeIdVertex non è dato un lato appartenente al triangolo";
            exit(1);
        }
    }


    int findIdEdgeBetweenVertices(const int& id1, const int& id2, const Triangles& triangle, const vector<Edges>& edges)
    {
        if((edges[triangle.idE1].idStart == id1 && edges[triangle.idE1].idEnd == id2) || (edges[triangle.idE1].idStart == id2 && edges[triangle.idE1].idEnd == id1))
        {
            return edges[triangle.idE1].id;
        }
        else if((edges[triangle.idE2].idStart == id1 && edges[triangle.idE2].idEnd == id2) || (edges[triangle.idE2].idStart == id2 && edges[triangle.idE2].idEnd == id1))
        {
            return edges[triangle.idE2].id;
        }
        else if((edges[triangle.idE3].idStart == id1 && edges[triangle.idE3].idEnd == id2) || (edges[triangle.idE3].idStart == id2 && edges[triangle.idE3].idEnd == id1))
        {
            return edges[triangle.idE3].id;
        }
        else
        {
            cerr<<"Nella function findIdEdgeBetweenVertices non sono dati vertici appartenenti al triangolo";
            exit(1);
        }
    }


    Triangles findTriangleMaxArea(const vector<Triangles>& triangles)
    {
        Triangles maxElemento = triangles[0];
        bool maxElementoTrovato = false;

        for (const Triangles& triangle : triangles) {
            if (triangle.inMesh == true && (!maxElementoTrovato || triangle.area > maxElemento.area)) {
                maxElemento = triangle;
                maxElementoTrovato = true;
            }
        }

        return maxElemento;
    }


    vector<int> divideTriangleIn2(Triangles& triangle, Edges& maxEdge, int& idPrecMidPoint, int& idPrecFirstHalf, int& idPrecSecondHalf, vector<Vertices>& vertices, vector<Edges>& edges, vector<Triangles>& triangles)
    {
        vector<int> adiacenceMaxEdge = findAdiacenceEdge(maxEdge, triangles);

        vertices.push_back(maxEdge.midPoint(vertices));
        int idMidPoint = vertices[vertices.size()-1].id;

        edges.push_back(Edges(edges.size(), 0, maxEdge.idStart, idMidPoint, true, vertices));
        int idFirstHalf = edges[edges.size()-1].id;
        edges.push_back(Edges(edges.size(), 0, idMidPoint, maxEdge.idEnd, true, vertices));
        int idSecondHalf = edges[edges.size()-1].id;

        int idOppositeVertex = findOppositeIdVertices(maxEdge, triangle);
        edges.push_back(Edges(edges.size(), 0, idMidPoint, idOppositeVertex, true, vertices));
        int idConjunction = edges[edges.size()-1].id;

        triangles.push_back(Triangles(triangles.size(), maxEdge.idStart, idMidPoint, idOppositeVertex, idFirstHalf, idConjunction, findIdEdgeBetweenVertices(maxEdge.idStart, idOppositeVertex, triangle, edges), true, vertices));        
        triangles.push_back(Triangles(triangles.size(), maxEdge.idEnd, idMidPoint, idOppositeVertex, idSecondHalf, idConjunction, findIdEdgeBetweenVertices(maxEdge.idEnd, idOppositeVertex, triangle, edges), true, vertices));

        edges[maxEdge.id].inMesh = false;
        triangles[triangle.id].inMesh = false;

        idPrecMidPoint = idMidPoint;
        idPrecFirstHalf = idFirstHalf;
        idPrecSecondHalf = idSecondHalf;

        return adiacenceMaxEdge;
    }


    vector<int> divideTriangleIn3(Triangles& triangle, Edges& maxEdge, Edges& precMaxEdge, int& idPrecMidPoint, int& idPrecFirstHalf, int& idPrecSecondHalf, vector<Vertices>& vertices, vector<Edges>& edges, vector<Triangles>& triangles)
    {
        vector<int> adiacenceMaxEdge = findAdiacenceEdge(maxEdge, triangles);

        vertices.push_back(maxEdge.midPoint(vertices));
        int idMidPoint = vertices[vertices.size()-1].id;

        edges.push_back(Edges(edges.size(), 0, maxEdge.idStart, idMidPoint, true, vertices));
        int idFirstHalf = edges[edges.size()-1].id;
        edges.push_back(Edges(edges.size(), 0, idMidPoint, maxEdge.idEnd, true, vertices));
        int idSecondHalf = edges[edges.size()-1].id;

        int idOppositeVertex = findOppositeIdVertices(maxEdge, triangle);
        edges.push_back(Edges(edges.size(), 0, idMidPoint, idOppositeVertex, true, vertices));
        int idSecondConjunction = edges[edges.size()-1].id;

        edges[maxEdge.id].inMesh = false;
        triangles[triangle.id].inMesh = false;

        edges.push_back(Edges(edges.size(), 0, idPrecMidPoint, idMidPoint, true, vertices));
        int idConjunctionMidPoint = edges[edges.size()-1].id;

        if(idOppositeVertex == precMaxEdge.idStart)
        {
            if(maxEdge.idStart == precMaxEdge.idEnd)
            {
                triangles.push_back(Triangles(triangles.size(), maxEdge.idEnd, idMidPoint, precMaxEdge.idStart, idSecondHalf, idSecondConjunction, findIdEdgeBetweenVertices(maxEdge.idEnd, precMaxEdge.idStart, triangle, edges), true, vertices));
                triangles.push_back(Triangles(triangles.size(), idMidPoint, idPrecMidPoint, maxEdge.idStart, idFirstHalf, idConjunctionMidPoint, idPrecSecondHalf, true, vertices));
                triangles.push_back(Triangles(triangles.size(), idMidPoint, idPrecMidPoint, precMaxEdge.idStart, idSecondConjunction, idConjunctionMidPoint, idPrecFirstHalf, true, vertices));
            }
            else if(maxEdge.idEnd == precMaxEdge.idEnd)
            {
                triangles.push_back(Triangles(triangles.size(), maxEdge.idStart, idMidPoint, precMaxEdge.idStart, idFirstHalf, idSecondConjunction, findIdEdgeBetweenVertices(maxEdge.idStart, precMaxEdge.idStart, triangle, edges), true, vertices));
                triangles.push_back(Triangles(triangles.size(), idMidPoint, idPrecMidPoint, maxEdge.idEnd, idSecondHalf, idConjunctionMidPoint, idPrecSecondHalf, true, vertices));
                triangles.push_back(Triangles(triangles.size(), idMidPoint, idPrecMidPoint, precMaxEdge.idStart, idSecondConjunction, idConjunctionMidPoint, idPrecFirstHalf, true, vertices));
            }
            else
            {
                exit(1);
            }
        }
        else if(idOppositeVertex == precMaxEdge.idEnd)
        {
            if(maxEdge.idStart == precMaxEdge.idStart)
            {
                triangles.push_back(Triangles(triangles.size(), maxEdge.idEnd, idMidPoint, precMaxEdge.idEnd, idSecondHalf, idSecondConjunction, findIdEdgeBetweenVertices(maxEdge.idEnd, precMaxEdge.idEnd, triangle, edges), true, vertices));
                triangles.push_back(Triangles(triangles.size(), idMidPoint, idPrecMidPoint, maxEdge.idStart, idFirstHalf, idConjunctionMidPoint, idPrecFirstHalf, true, vertices));
                triangles.push_back(Triangles(triangles.size(), idMidPoint, idPrecMidPoint, precMaxEdge.idEnd, idSecondConjunction, idConjunctionMidPoint, idPrecSecondHalf, true, vertices));
            }
            else if(maxEdge.idEnd == precMaxEdge.idStart)
            {
                triangles.push_back(Triangles(triangles.size(), maxEdge.idStart, idMidPoint, precMaxEdge.idEnd, idFirstHalf, idSecondConjunction, findIdEdgeBetweenVertices(maxEdge.idStart, precMaxEdge.idEnd, triangle, edges), true, vertices));
                triangles.push_back(Triangles(triangles.size(), idMidPoint, idPrecMidPoint, maxEdge.idEnd, idSecondHalf, idConjunctionMidPoint, idPrecFirstHalf, true, vertices));
                triangles.push_back(Triangles(triangles.size(), idMidPoint, idPrecMidPoint, precMaxEdge.idEnd, idSecondConjunction, idConjunctionMidPoint, idPrecSecondHalf, true, vertices));
            }
            else
            {
                exit(1);
            }
        }
        else
        {
            exit(2);
        }

        idPrecMidPoint = idMidPoint;
        idPrecFirstHalf = idFirstHalf;
        idPrecSecondHalf = idSecondHalf;

        return adiacenceMaxEdge;
    }


    void raffinamentoComplesso(const int& theta, vector<Vertices>& vertices, vector<Edges>& edges, vector<Triangles>& triangles)
    {
        for(unsigned int i=0; i<theta; i++)
        {
            Triangles triangleToRefine = findTriangleMaxArea(triangles);
            int idTriangleToRefine = triangleToRefine.id;

            Edges maxLengthEdge = triangleToRefine.FindMaxEdge(edges);
            int idMaxLengthEdge = maxLengthEdge.id;

            int idPrecMidPoint;
            int idPrecFirstHalf;
            int idPrecSecondHalf;

            vector<int> adiacenceMaxEdge = divideTriangleIn2(triangleToRefine, maxLengthEdge, idPrecMidPoint, idPrecFirstHalf, idPrecSecondHalf, vertices, edges, triangles);

            while(adiacenceMaxEdge.size() == 2)
            {
                Triangles secondTriangleToRefine(0, 0, 0, 0, 0, 0, 0, true, vertices);
                if(adiacenceMaxEdge[0] == idTriangleToRefine)
                {
                    secondTriangleToRefine = triangles[adiacenceMaxEdge[1]];
                }
                else if(adiacenceMaxEdge[1] == idTriangleToRefine)
                {
                    secondTriangleToRefine = triangles[adiacenceMaxEdge[0]];
                }

                int idSecondTriangleToRefine = secondTriangleToRefine.id;

                Edges secondMaxLengthEdge = secondTriangleToRefine.FindMaxEdge(edges);
                int idSecondMaxLengthEdge = secondMaxLengthEdge.id;

                if(idSecondMaxLengthEdge == idMaxLengthEdge)
                {
                    int idOppositeVertex = findOppositeIdVertices(secondMaxLengthEdge, secondTriangleToRefine);
                    edges.push_back(Edges(edges.size(), 0, idPrecMidPoint, idOppositeVertex, true, vertices));
                    int idConjunction = edges[edges.size()-1].id;

                    triangles.push_back(Triangles(triangles.size(), maxLengthEdge.idStart, idPrecMidPoint, idOppositeVertex, idPrecFirstHalf, idConjunction, findIdEdgeBetweenVertices(maxLengthEdge.idStart, idOppositeVertex, secondTriangleToRefine, edges), true, vertices));                    
                    triangles.push_back(Triangles(triangles.size(), maxLengthEdge.idEnd, idPrecMidPoint, idOppositeVertex, idPrecSecondHalf, idConjunction, findIdEdgeBetweenVertices(maxLengthEdge.idEnd, idOppositeVertex, secondTriangleToRefine, edges), true, vertices));

                    triangles[idSecondTriangleToRefine].inMesh = false;

                    break;
                }
                else
                {
                    adiacenceMaxEdge = divideTriangleIn3(secondTriangleToRefine, secondMaxLengthEdge, maxLengthEdge, idPrecMidPoint, idPrecFirstHalf, idPrecSecondHalf, vertices, edges, triangles);
                }

                triangleToRefine = secondTriangleToRefine;
                idTriangleToRefine = idSecondTriangleToRefine;
                maxLengthEdge = secondMaxLengthEdge;
                idMaxLengthEdge = idSecondMaxLengthEdge;
            }
        }
    }

}
