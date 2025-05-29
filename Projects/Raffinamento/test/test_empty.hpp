#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include "empty_class.hpp"

#include <gtest/gtest.h>
#include <vector>
#include <cmath>

using namespace testing;
using namespace ProjectLibrary;


TEST(TestImport, TestImportVertices)
{
    vector<int> marker1Vector;
    vector<int> marker2Vector;
    vector<int> marker3Vector;
    vector<int> marker4Vector;
    vector<int> marker5Vector;
    vector<int> marker6Vector;
    vector<int> marker7Vector;
    vector<int> marker8Vector;

    string nameFile = ".\\Dataset\\Test1\\Cell0Ds.csv";

    vector<Vertices> vertices = ImportVertices(nameFile);

    for (unsigned int i=0; i<vertices.size(); i++)
    {
        if(vertices[i].marker == 1)
        {
            marker1Vector.push_back(vertices[i].id);
        }
        else if(vertices[i].marker == 2)
        {
            marker2Vector.push_back(vertices[i].id);
        }
        else if(vertices[i].marker == 3)
        {
            marker3Vector.push_back(vertices[i].id);
        }
        else if(vertices[i].marker == 4)
        {
            marker4Vector.push_back(vertices[i].id);
        }
        else if(vertices[i].marker == 5)
        {
            marker5Vector.push_back(vertices[i].id);
        }
        else if(vertices[i].marker == 6)
        {
            marker6Vector.push_back(vertices[i].id);
        }
        else if(vertices[i].marker == 7)
        {
            marker7Vector.push_back(vertices[i].id);
        }
        else if(vertices[i].marker == 8)
        {
            marker8Vector.push_back(vertices[i].id);
        }
    }

    vector<int> exactMarker1Vector = {0};
    vector<int> exactMarker2Vector = {1};
    vector<int> exactMarker3Vector = {2};
    vector<int> exactMarker4Vector = {3};
    vector<int> exactMarker5Vector = {6, 13, 23, 24, 25, 33, 36};
    vector<int> exactMarker6Vector = {7, 14, 18, 37, 39, 77, 82};
    vector<int> exactMarker7Vector = {8, 57, 58, 69, 71, 83, 87};
    vector<int> exactMarker8Vector = {5, 30, 60, 63, 64, 75, 88};

    EXPECT_EQ(marker1Vector, exactMarker1Vector);
    EXPECT_EQ(marker2Vector, exactMarker2Vector);
    EXPECT_EQ(marker3Vector, exactMarker3Vector);
    EXPECT_EQ(marker4Vector, exactMarker4Vector);
    EXPECT_EQ(marker5Vector, exactMarker5Vector);
    EXPECT_EQ(marker6Vector, exactMarker6Vector);
    EXPECT_EQ(marker7Vector, exactMarker7Vector);
    EXPECT_EQ(marker8Vector, exactMarker8Vector);
}

TEST(TestImport, TestImportEdges)
{
    vector<int> marker5Edges;
    vector<int> marker6Edges;
    vector<int> marker7Edges;
    vector<int> marker8Edges;

    string nameFileVertices = ".\\Dataset\\Test1\\Cell0Ds.csv";
    string nameFileEdges = ".\\Dataset\\Test1\\Cell1Ds.csv";

    vector<Vertices> vertices = ImportVertices(nameFileVertices);
    vector<Edges> edges = ImportEdges(nameFileEdges, vertices);

    for (unsigned int i=0; i<edges.size(); i++)
    {
        if(edges[i].marker == 5)
        {
            marker5Edges.push_back(edges[i].id);
        }
        else if(edges[i].marker == 6)
        {
            marker6Edges.push_back(edges[i].id);
        }
        else if(edges[i].marker == 7)
        {
            marker7Edges.push_back(edges[i].id);
        }
        else if(edges[i].marker == 8)
        {
            marker8Edges.push_back(edges[i].id);
        }
    }

    vector<int> exactMarker5Edges = {57, 76, 81, 85, 89, 90, 99, 112};
    vector<int> exactMarker6Edges = {54, 55, 63, 68, 113, 115, 216, 221};
    vector<int> exactMarker7Edges = {193, 196, 198, 207, 215, 222, 225, 230};
    vector<int> exactMarker8Edges = {40, 110, 177, 182, 190, 210, 224, 231};

    EXPECT_EQ(marker5Edges, exactMarker5Edges);
    EXPECT_EQ(marker6Edges, exactMarker6Edges);
    EXPECT_EQ(marker7Edges, exactMarker7Edges);
    EXPECT_EQ(marker8Edges, exactMarker8Edges);
}

TEST(TestImport, TestImportTriangles)
{
    string nameFileVertices = ".\\Dataset\\Test1\\Cell0Ds.csv";
    string nameFileEdges = ".\\Dataset\\Test1\\Cell1Ds.csv";
    string nameFileTriangles = ".\\Dataset\\Test1\\Cell2Ds.csv";

    vector<Vertices> vertices = ImportVertices(nameFileVertices);
    vector<Edges> edges = ImportEdges(nameFileEdges, vertices);
    vector<Triangles> triangles = ImportTriangles(nameFileTriangles, vertices);

    double areaTot = 0;

    for (const auto& triangle : triangles)
    {
        areaTot = areaTot + triangle.area;
    }

    double exactAreaTot = 1;

    EXPECT_DOUBLE_EQ(areaTot, exactAreaTot);
}

TEST(TestLength, TestEdgeLength)
{
    Vertices V1(0, 0, 2, 1);
    Vertices V2(1, 0, 4, 3);

    vector<Vertices> vertices = {V1, V2};

    Edges E(0, 0, 0, 1, true, vertices);

    double length = E.length;

    double exactLength = 2 * sqrt(2);

    EXPECT_EQ(length, exactLength);
}

TEST(TestMaxEdge, TestTriangleMaxEdge)
{
    Vertices V1(0, 0, 2, 1);
    Vertices V2(1, 0, 3, 4);
    Vertices V3(2, 0, 4, 3);

    vector<Vertices> vertices ={V1, V2, V3};

    Edges E1(0, 0, 1, 2, true, vertices);
    Edges E2(1, 0, 0, 1, true, vertices);
    Edges E3(2, 0, 2, 0, true, vertices);

    vector<Edges> edges = {E1, E2, E3};

    Triangles T(0, 0, 1, 2, 0, 1, 2, true, vertices);

    Edges maxEdge = T.FindMaxEdge(edges);
    int idMaxEdge = maxEdge.id;

    int exactIdMaxEdge = 1;

    EXPECT_EQ(idMaxEdge, exactIdMaxEdge);
}

TEST(TestArea, TestAreaFondamentalTriangle)
{
    Vertices V1(0, 0, 0, 0);
    Vertices V2(1, 0, 1, 0);
    Vertices V3(2, 0, 0, 1);

    vector<Vertices> vertices ={V1, V2, V3};

    Edges E1(0, 0, 0, 1, true, vertices);
    Edges E2(1, 0, 1, 2, true, vertices);
    Edges E3(2, 0, 2, 0, true, vertices);

    Triangles T(0, 0, 1, 2, 0, 1, 2, true, vertices);

    double areaT = T.area;

    double exactAreaT = 0.5;

    EXPECT_EQ(areaT, exactAreaT);
}

TEST(TestArea, TestAreaTriangle)
{
    Vertices V1(0, 0, 2, 1);
    Vertices V2(1, 0, 3, 4);
    Vertices V3(2, 0, 4, 3);

    vector<Vertices> vertices ={V1, V2, V3};

    Edges E1(0, 0, 0, 1, true, vertices);
    Edges E2(1, 0, 1, 2, true, vertices);
    Edges E3(2, 0, 2, 0, true, vertices);

    Triangles T(0, 0, 1, 2, 0, 1, 2, true, vertices);

    double areaT = T.area;

    double exactAreaT = 2;

    EXPECT_EQ(areaT, exactAreaT);
}

TEST(TestMaxArea, TestMaxArea3Triangles)
{
    Vertices V1(0, 0, 2, 1);
    Vertices V2(1, 0, 3, 4);
    Vertices V3(2, 0, 4, 3);
    Vertices V4(3, 0, 0, 4);
    Vertices V5(4, 0, 0, 0);
    Vertices V6(5, 0, 1, 0);
    Vertices V7(6, 0, 0, 1);

    vector<Vertices> vertices = {V1, V2, V3, V4, V5, V6, V7};

    Edges E1(0, 0, 0, 1, true, vertices);
    Edges E2(1, 0, 1, 2, true, vertices);
    Edges E3(2, 0, 2, 0, true, vertices);
    Edges E4(3, 0, 1, 3, true, vertices);
    Edges E5(4, 0, 3, 0, true, vertices);
    Edges E6(5, 0, 4, 5, true, vertices);
    Edges E7(6, 0, 5, 6, true, vertices);
    Edges E8(7, 0, 6, 4, true, vertices);

    Triangles T1(0, 0, 1, 3, 0, 3, 4, false, vertices);
    Triangles T2(1, 0, 1, 2, 0, 1, 2, true, vertices);
    Triangles T3(2, 4, 5, 6, 5, 6, 7, true, vertices);

    vector<Triangles> triangles = {T1, T2, T3};

    Triangles maxAreaTriangle = findTriangleMaxArea(triangles);

    Triangles exactMaxAreaTriangle = T2;

    EXPECT_EQ(maxAreaTriangle, exactMaxAreaTriangle);
}

TEST(TestMidPoint, TestEdgeMidPoint)
{
    Vertices V1(0, 0, 2, 1);
    Vertices V2(1, 0, 4, 3);

    vector<Vertices> vertices = {V1, V2};

    Edges E(0, 0, 0, 1, true, vertices);

    Vertices midPoint = E.midPoint(vertices);
    int idMidPoint = midPoint.id;
    int XMidPoint = midPoint.x;
    int YMidPoint = midPoint.y;

    int exactIdMidPoint = 2;
    int exactXMidPoint = 3;
    int exactYMidPoint = 2;

    EXPECT_EQ(idMidPoint, exactIdMidPoint);
    EXPECT_EQ(XMidPoint, exactXMidPoint);
    EXPECT_EQ(YMidPoint, exactYMidPoint);
}

TEST(TestAdiacence, TestAdiacenceEdge)
{
    Vertices V1(0, 0, 2, 1);
    Vertices V2(1, 0, 3, 4);
    Vertices V3(2, 0, 4, 3);
    Vertices V4(3, 0, 0, 4);

    vector<Vertices> vertices = {V1, V2, V3, V4};

    Edges E1(0, 0, 0, 1, true, vertices);
    Edges E2(1, 0, 1, 2, true, vertices);
    Edges E3(2, 0, 2, 0, true, vertices);
    Edges E4(3, 0, 1, 3, true, vertices);
    Edges E5(4, 0, 3, 0, true, vertices);

    Triangles T1(0, 0, 1, 3, 0, 3, 4, true, vertices);
    Triangles T2(1, 0, 1, 2, 0, 1, 2, true, vertices);

    vector<Triangles> triangles = {T1, T2};

    vector<int> adiacenceVector = findAdiacenceEdge(E1, triangles);

    vector<int> exactVec = {0, 1};

    EXPECT_EQ(adiacenceVector, exactVec);
}

TEST(TestOppositeVertex, TestOppositeVertexToEdge)
{
    Vertices V1(0, 0, 2, 1);
    Vertices V2(1, 0, 3, 4);
    Vertices V3(2, 0, 4, 3);

    vector<Vertices> vertices = {V1, V2, V3};

    Edges E1(0, 0, 1, 2, true, vertices);
    Edges E2(1, 0, 0, 1, true, vertices);
    Edges E3(2, 0, 2, 0, true, vertices);

    vector<Edges> edges = {E1, E2, E3};

    Triangles T(0, 0, 1, 2, 0, 1, 2, true, vertices);

    Edges maxEdge = T.FindMaxEdge(edges);

    int oppositeIdVertex = findOppositeIdVertices(maxEdge, T);

    int exactOppositeIdVertex = V3.id;

    EXPECT_EQ(oppositeIdVertex, exactOppositeIdVertex);
}

TEST(TestEdgeBetweenVertices, TestEdgeBetweenVertices)
{
    Vertices V1(0, 0, 2, 1);
    Vertices V2(1, 0, 3, 4);
    Vertices V3(2, 0, 4, 3);

    vector<Vertices> vertices = {V1, V2, V3};

    Edges E1(0, 0, 1, 2, true, vertices);
    Edges E2(1, 0, 0, 1, true, vertices);
    Edges E3(2, 0, 2, 0, true, vertices);

    vector<Edges> edges = {E1, E2, E3};

    Triangles T(0, 0, 1, 2, 0, 1, 2, true, vertices);

    int IdEdgeBetweenVertices = findIdEdgeBetweenVertices(V2.id, V1.id, T, edges);

    int exactIdEdgeBetweenVertices = E2.id;

    EXPECT_EQ(IdEdgeBetweenVertices, exactIdEdgeBetweenVertices);
}

TEST(TestDivideIn2, TestDivideTriangleIn2)
{
    Vertices V0(0, 0, 2, 1);
    Vertices V1(1, 0, 3, 4);
    Vertices V2(2, 0, 4, 3);
    Vertices V3(3, 0, 0, 4);
    Vertices V4(4, 0, 4, 0);

    vector<Vertices> vertices = {V0, V1, V2, V3, V4};

    Edges E0(0, 0, 0, 1, true, vertices);
    Edges E1(1, 0, 1, 2, true, vertices);
    Edges E2(2, 0, 2, 0, true, vertices);
    Edges E3(3, 0, 1, 3, true, vertices);
    Edges E4(4, 0, 3, 0, true, vertices);
    Edges E5(5, 0, 2, 4, true, vertices);
    Edges E6(6, 0, 0, 4, true, vertices);

    vector<Edges> edges = {E0, E1, E2, E3, E4, E5, E6};

    Triangles T0(0, 0, 1, 3, 0, 3, 4, false, vertices);
    Triangles T1(1, 0, 1, 2, 0, 1, 2, true, vertices);
    Triangles T2(2, 0, 2, 4, 5, 6, 2, true, vertices);

    vector<Triangles> triangles = {T0, T1, T2};

    int idPrecMidPoint;
    int idPrecFirstHalf;
    int idPrecSecondHalf;

    vector<int> adiacence = divideTriangleIn2(T1, E2, idPrecMidPoint, idPrecFirstHalf, idPrecSecondHalf, vertices, edges, triangles);

    Vertices midPoint(5, 0, 3, 2);
    Edges firstHalf(7, 0, 2, 5, true, vertices);
    Edges secondHalf(8, 0, 5, 0, true, vertices);
    Edges conjunction(9, 0, 5, 1, true, vertices);
    Triangles firstTriangle(3, 2, 5, 1, 7, 9, 1, true, vertices);
    Triangles secondTriangle(4, 0, 5, 1, 8, 9, 0, true, vertices);

    vector<int> exactAdiacence = {1, 2};

    EXPECT_EQ(adiacence, exactAdiacence);

    EXPECT_EQ(idPrecMidPoint, midPoint.id);
    EXPECT_EQ(vertices[idPrecMidPoint].x, midPoint.x);
    EXPECT_EQ(vertices[idPrecMidPoint].y, midPoint.y);

    EXPECT_EQ(idPrecFirstHalf, firstHalf.id);
    EXPECT_EQ(edges[idPrecFirstHalf].idStart, firstHalf.idStart);
    EXPECT_EQ(edges[idPrecFirstHalf].idEnd, firstHalf.idEnd);

    EXPECT_EQ(idPrecSecondHalf, secondHalf.id);
    EXPECT_EQ(edges[idPrecSecondHalf].idStart, secondHalf.idStart);
    EXPECT_EQ(edges[idPrecSecondHalf].idEnd, secondHalf.idEnd);

    EXPECT_EQ(edges[edges.size()-1].id, conjunction.id);
    EXPECT_EQ(edges[edges.size()-1].idStart, conjunction.idStart);
    EXPECT_EQ(edges[edges.size()-1].idEnd, conjunction.idEnd);

    EXPECT_EQ(triangles[triangles.size()-2].id, firstTriangle.id);
    EXPECT_EQ(triangles[triangles.size()-2].idV1, firstTriangle.idV1);
    EXPECT_EQ(triangles[triangles.size()-2].idV2, firstTriangle.idV2);
    EXPECT_EQ(triangles[triangles.size()-2].idV3, firstTriangle.idV3);
    EXPECT_EQ(triangles[triangles.size()-2].idE1, firstTriangle.idE1);
    EXPECT_EQ(triangles[triangles.size()-2].idE2, firstTriangle.idE2);
    EXPECT_EQ(triangles[triangles.size()-2].idE3, firstTriangle.idE3);

    EXPECT_EQ(triangles[triangles.size()-1].id, secondTriangle.id);
    EXPECT_EQ(triangles[triangles.size()-1].idV1, secondTriangle.idV1);
    EXPECT_EQ(triangles[triangles.size()-1].idV2, secondTriangle.idV2);
    EXPECT_EQ(triangles[triangles.size()-1].idV3, secondTriangle.idV3);
    EXPECT_EQ(triangles[triangles.size()-1].idE1, secondTriangle.idE1);
    EXPECT_EQ(triangles[triangles.size()-1].idE2, secondTriangle.idE2);
    EXPECT_EQ(triangles[triangles.size()-1].idE3, secondTriangle.idE3);

    EXPECT_EQ(edges[2].inMesh, false);
    EXPECT_EQ(triangles[1].inMesh, false);
}

TEST(TestDivideIn2, TestDivideTriangleIn2OnFrontier)
{
    Vertices V0(0, 0, 2, 1);
    Vertices V1(1, 0, 3, 4);
    Vertices V2(2, 0, 4, 3);
    Vertices V3(3, 0, 0, 4);
    Vertices V4(4, 0, 4, 0);

    vector<Vertices> vertices = {V0, V1, V2, V3, V4};

    Edges E0(0, 0, 0, 1, true, vertices);
    Edges E1(1, 0, 1, 2, true, vertices);
    Edges E2(2, 0, 2, 0, true, vertices);
    Edges E3(3, 0, 1, 3, true, vertices);
    Edges E4(4, 0, 3, 0, true, vertices);
    Edges E5(5, 0, 2, 4, true, vertices);
    Edges E6(6, 0, 0, 4, true, vertices);

    vector<Edges> edges = {E0, E1, E2, E3, E4, E5, E6};

    Triangles T0(0, 0, 1, 3, 0, 3, 4, false, vertices);
    Triangles T1(1, 0, 1, 2, 0, 1, 2, true, vertices);
    Triangles T2(2, 0, 2, 4, 5, 6, 2, true, vertices);

    vector<Triangles> triangles = {T0, T1, T2};

    int idPrecMidPoint;
    int idPrecFirstHalf;
    int idPrecSecondHalf;

    vector<int> adiacence = divideTriangleIn2(T2, E5, idPrecMidPoint, idPrecFirstHalf, idPrecSecondHalf, vertices, edges, triangles);

    vector<int> exactAdiacence = {2};

    EXPECT_EQ(adiacence, exactAdiacence);
}

TEST(TestDivideIn3, TestDivideTriangleIn3)
{
    Vertices V0(0, 0, 2, 1);
    Vertices V1(1, 0, 3, 4);
    Vertices V2(2, 0, 4, 3);
    Vertices V3(3, 0, 0, 4);
    Vertices V4(4, 0, 4, 0);

    vector<Vertices> vertices = {V0, V1, V2, V3, V4};

    Edges E0(0, 0, 0, 1, true, vertices);
    Edges E1(1, 0, 1, 2, true, vertices);
    Edges E2(2, 0, 2, 0, true, vertices);
    Edges E3(3, 0, 1, 3, true, vertices);
    Edges E4(4, 0, 3, 0, true, vertices);
    Edges E5(5, 0, 2, 4, true, vertices);
    Edges E6(6, 0, 0, 4, true, vertices);

    vector<Edges> edges = {E0, E1, E2, E3, E4, E5, E6};

    Triangles T0(0, 0, 1, 3, 0, 3, 4, false, vertices);
    Triangles T1(1, 0, 1, 2, 0, 1, 2, true, vertices);
    Triangles T2(2, 0, 2, 4, 5, 6, 2, true, vertices);

    vector<Triangles> triangles = {T0, T1, T2};

    int idPrecMidPoint;
    int idPrecFirstHalf;
    int idPrecSecondHalf;

    vector<int> adiacenceAfter2 = divideTriangleIn2(T0, E0, idPrecMidPoint, idPrecFirstHalf, idPrecSecondHalf, vertices, edges, triangles);

    vector<int> adiacenceAfter3 = divideTriangleIn3(T1, E2, E0, idPrecMidPoint, idPrecFirstHalf, idPrecSecondHalf, vertices, edges, triangles);

    Vertices midPoint(5, 0, 2.5, 2.5);
    Edges firstHalf(7, 0, 0, 5, true, vertices);
    Edges secondHalf(8, 0, 5, 1, true, vertices);
    Edges conjunction(9, 0, 5, 3, true, vertices);
    Triangles firstTriangle(3, 0, 5, 3, 7, 9, 4, true, vertices);
    Triangles secondTriangle(4, 1, 5, 3, 8, 9, 3, true, vertices);

    Vertices secondMidPoint(6, 0, 3, 2);
    Edges secondFirstHalf(10, 0, 2, 6, true, vertices);
    Edges secondSecondHalf(11, 0, 6, 0, true, vertices);
    Edges secondConjunction(12, 0, 6, 1, true, vertices);
    Edges conjunctionMidPoint(13, 0, 5, 6, true, vertices);
    Triangles triangleNew1(5, 2, 6, 1, 10, 12, 1, true, vertices);
    Triangles triangleNew2(6, 6, 5, 0, 11, 13, 7, true, vertices);
    Triangles triangleNew3(7, 6, 5, 1, 12, 13, 8, true, vertices);

    vector<int> exactAdiacenceAfter3 = {1, 2};

    EXPECT_EQ(adiacenceAfter3, exactAdiacenceAfter3);

    EXPECT_EQ(idPrecMidPoint, secondMidPoint.id);
    EXPECT_EQ(vertices[idPrecMidPoint].x, secondMidPoint.x);
    EXPECT_EQ(vertices[idPrecMidPoint].y, secondMidPoint.y);

    EXPECT_EQ(idPrecFirstHalf, secondFirstHalf.id);
    EXPECT_EQ(edges[idPrecFirstHalf].idStart, secondFirstHalf.idStart);
    EXPECT_EQ(edges[idPrecFirstHalf].idEnd, secondFirstHalf.idEnd);

    EXPECT_EQ(idPrecSecondHalf, secondSecondHalf.id);
    EXPECT_EQ(edges[idPrecSecondHalf].idStart, secondSecondHalf.idStart);
    EXPECT_EQ(edges[idPrecSecondHalf].idEnd, secondSecondHalf.idEnd);

    EXPECT_EQ(edges[edges.size()-2].id, secondConjunction.id);
    EXPECT_EQ(edges[edges.size()-2].idStart, secondConjunction.idStart);
    EXPECT_EQ(edges[edges.size()-2].idEnd, secondConjunction.idEnd);

    EXPECT_EQ(edges[2].inMesh, false);
    EXPECT_EQ(triangles[1].inMesh, false);

    EXPECT_EQ(edges[edges.size()-1].id, conjunctionMidPoint.id);
    EXPECT_EQ(edges[edges.size()-1].idStart, conjunctionMidPoint.idStart);
    EXPECT_EQ(edges[edges.size()-1].idEnd, conjunctionMidPoint.idEnd);

    EXPECT_EQ(triangles[triangles.size()-3].id, triangleNew1.id);
    EXPECT_EQ(triangles[triangles.size()-3].idV1, triangleNew1.idV1);
    EXPECT_EQ(triangles[triangles.size()-3].idV2, triangleNew1.idV2);
    EXPECT_EQ(triangles[triangles.size()-3].idV3, triangleNew1.idV3);
    EXPECT_EQ(triangles[triangles.size()-3].idE1, triangleNew1.idE1);
    EXPECT_EQ(triangles[triangles.size()-3].idE2, triangleNew1.idE2);
    EXPECT_EQ(triangles[triangles.size()-3].idE3, triangleNew1.idE3);

    EXPECT_EQ(triangles[triangles.size()-2].id, triangleNew2.id);
    EXPECT_EQ(triangles[triangles.size()-2].idV1, triangleNew2.idV1);
    EXPECT_EQ(triangles[triangles.size()-2].idV2, triangleNew2.idV2);
    EXPECT_EQ(triangles[triangles.size()-2].idV3, triangleNew2.idV3);
    EXPECT_EQ(triangles[triangles.size()-2].idE1, triangleNew2.idE1);
    EXPECT_EQ(triangles[triangles.size()-2].idE2, triangleNew2.idE2);
    EXPECT_EQ(triangles[triangles.size()-2].idE3, triangleNew2.idE3);

    EXPECT_EQ(triangles[triangles.size()-1].id, triangleNew3.id);
    EXPECT_EQ(triangles[triangles.size()-1].idV1, triangleNew3.idV1);
    EXPECT_EQ(triangles[triangles.size()-1].idV2, triangleNew3.idV2);
    EXPECT_EQ(triangles[triangles.size()-1].idV3, triangleNew3.idV3);
    EXPECT_EQ(triangles[triangles.size()-1].idE1, triangleNew3.idE1);
    EXPECT_EQ(triangles[triangles.size()-1].idE2, triangleNew3.idE2);
    EXPECT_EQ(triangles[triangles.size()-1].idE3, triangleNew3.idE3);
}


#endif // __TEST_EMPTY_H
