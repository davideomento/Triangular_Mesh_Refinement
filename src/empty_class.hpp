#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <Eigen/Eigen>

using namespace std;
using namespace Eigen;

namespace ProjectLibrary
{
    constexpr double max_tolerance(const double& x, const double& y)
    {
        return x > y ? x : y;
    }


    class Vertices
    {
        public:
            int id;
            int marker;
            double x;
            double y;

            Vertices(const int& id,
                     const int& marker,
                     const double& x,
                     const double& y);

    };


    class Edges
    {
        public:
            int id;
            int marker;
            int idStart;
            int idEnd;
            double length;
            bool inMesh;

            static constexpr double geometricTol = 1.0e-12;

            Edges(const int& id,
                  const int& marker,
                  const int& idStart,
                  const int& idEnd,
                  const bool& inMesh,
                  const vector<Vertices>& vertices);

            Vertices midPoint(const vector<Vertices>& vertices);

    };


    class Triangles
    {
        public:
            int id;
            int idV1;
            int idV2;
            int idV3;
            int idE1;
            int idE2;
            int idE3;
            double area;
            bool inMesh;


            static constexpr double geometricTol = 1.0e-12;
            static constexpr double geometricTol_Squared = max_tolerance(Triangles::geometricTol * Triangles::geometricTol,
                                                                         numeric_limits<double>::epsilon());
            Triangles(const int& id,
                      const int& idV1,
                      const int& idV2,
                      const int& idV3,
                      const int& idE1,
                      const int& idE2,
                      const int& idE3,
                      const bool& inMesh,
                      const vector<Vertices>& vertices);

            Edges FindMaxEdge(const vector<Edges>& edges);

    };



    //operatori necessari

    inline bool operator==(const Vertices& v1, const Vertices& v2)
    {
      return (v1.x == v2.x && v1.y == v2.y) ;
    }


    inline bool operator==(const Edges& e1, const Edges& e2)
    {
      return (e1.id == e2.id);
    }


    inline bool operator>(const Edges& e1, const Edges& e2)
    {
        return e1.length > e2.length + Edges::geometricTol * max(e1.length, e2.length);
    }


    inline bool operator<=(const Edges& e1, const Edges& e2)
    {
        return !(e1 > e2);
    }


    inline ostream& operator<<(ostream& os, const Edges& e1)
    {
        os << e1.id;
        return os;
    }


    inline bool operator==(const Triangles& t1, const Triangles& t2)
    {
      return (t1.id == t2.id);
    }


    inline bool operator>(const Triangles& t1, const Triangles& t2)
    {
        return t1.area > t2.area + Triangles::geometricTol_Squared * max(t1.area, t2.area);
    }


    inline bool operator<=(const Triangles& t1, const Triangles& t2)
    {
        return !(t1 > t2);
    }


    inline ostream& operator<<(ostream& os, const Triangles& t1)
    {
        os << t1.id;
        return os;
    }



    //funzioni utilizzate per l'import del dataset

    vector<Vertices> ImportVertices(const string& nameFile);


    vector<Edges> ImportEdges(const string& nameFile,
                              const vector<Vertices>& vertices);


    vector<Triangles> ImportTriangles(const string& nameFile,
                                      const vector<Vertices>& vertices);



    // funzioni utilizzate per il raffinamento

    Triangles findTriangleMaxArea(const vector<Triangles>& triangles);


    vector<int> findAdiacenceEdge(const Edges& edge,
                                  const vector<Triangles>& triangles);


    int findOppositeIdVertices(const Edges& edge,
                               const Triangles& triangle);


    int findIdEdgeBetweenVertices(const int& id1,
                                  const int& id2,
                                  const Triangles& triangle,
                                  const vector<Edges>& edges);


    vector<int> divideTriangleIn2(Triangles& triangle,
                                  Edges& maxEdge,
                                  int& idPrecMidPoint,
                                  int& idPrecFirstHalf,
                                  int& idPrecSecondHalf,
                                  vector<Vertices>& vertices,
                                  vector<Edges>& edges,
                                  vector<Triangles>& triangles);


    vector<int> divideTriangleIn3(Triangles& triangle,
                                  Edges& maxEdge,
                                  Edges& precMaxEdge,
                                  int& idPrecMidPoint,
                                  int& idPrecFirstHalf,
                                  int& idPrecSecondHalf,
                                  vector<Vertices>& vertices,
                                  vector<Edges>& edges,
                                  vector<Triangles>& triangles);


    void raffinamentoComplesso(const int& theta,
                               vector<Vertices>& vertices,
                               vector<Edges>& edges,
                               vector<Triangles>& triangles);


}

#endif // __EMPTY_H
