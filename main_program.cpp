#include "empty_class.hpp"
#include <vector>
#include <ostream>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace ProjectLibrary;
using namespace std;

int main()
{
    int theta = 0;

    // import di vertici, lati e triangoli che compongono la mesh
    string nameFileVertices = ".\\Dataset\\Test1\\Cell0Ds.csv";
    string nameFileEdges = ".\\Dataset\\Test1\\Cell1Ds.csv";
    string nameFileTriangles = ".\\Dataset\\Test1\\Cell2Ds.csv";
    vector<Vertices> vertices = ImportVertices(nameFileVertices);
    vector<Edges> edges = ImportEdges(nameFileEdges, vertices);
    vector<Triangles> triangles = ImportTriangles(nameFileTriangles, vertices);


    auto start = chrono::high_resolution_clock::now();

    raffinamentoComplesso(theta, vertices, edges, triangles);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo_trascorso = end - start;
    cout << "Tempo di esecuzione: " << tempo_trascorso.count() << " secondi." << "\n";
    cout << "Numero triangoli finali: " << triangles.size() << "\n";


    //stampa del file di output dei vertici
    ofstream outputFileVertices("C:\\Users\\Asus\\OneDrive\\Desktop\\outputVertices.csv");
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        outputFileVertices<<vertices[i].x<<";"<<vertices[i].y<<"\n";
    }
    outputFileVertices.close();


    //stampa del file di output dei lati
    ofstream outputFileEdges("C:\\Users\\Asus\\OneDrive\\Desktop\\outputEdges.csv");
    for(unsigned int i=0; i<edges.size(); i++)
    {
        outputFileEdges<<vertices[edges[i].idStart].x<<";"<<vertices[edges[i].idStart].y<<";"<<vertices[edges[i].idEnd].x<<";"<<vertices[edges[i].idEnd].y<<"\n";
    }
    outputFileEdges.close();


    return 0;
}
