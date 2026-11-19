/*
* Archivo: GestorDeNotas.cpp
* Autor: Juan Esteban Suarez Cardenas
* Fecha: 10/11/2026
* Curso: Técnicas de Programación
* Descripción: Gestor de notas para almacenar y manipular calificaciones.
* Compilar: g++ GestorDeNotas.cpp -o GestorDeNotas
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
void cargarNotas(vector<vector<float>>& notas, vector<string>& nombres, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "ERROR: no se pudo abrir " << nombreArchivo << " para leer" << endl;
        return;
    }
    float nota;
    string nombre;
    string linea;
    while (getline(archivo, linea)) {
        // Procesar la línea para extraer nombre y nota
        // Este es un ejemplo simplificado, ajusta según el formato de tu archivo
        istringstream iss(linea);
        if (!(iss >> nombre)) {
            continue; // Salta líneas que solo tengan espacios o caracteres \r
        }
        vector<float> notasAlumno;
        while (iss >> nota) {
            notasAlumno.push_back(nota);
        }
        nombres.push_back(nombre);
        notas.push_back(notasAlumno);
    }
    archivo.close();
}
void calcularPromedio(const vector<float>& fila, vector<float>& promedios) {
    if (fila.empty()) {
        cout << "No hay notas para calcular el promedio." << endl;
        return;
    }
    float suma = 0.0f;
    for (float n : fila) {
        suma += n;
    }
    promedios.push_back(suma / fila.size());
}