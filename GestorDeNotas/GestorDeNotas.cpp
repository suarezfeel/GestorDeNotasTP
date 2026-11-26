/*
* Archivo: GestorDeNotas.cpp
* Autor: Juan Esteban Suarez Cardenas
* Autor 2: Jordan Alejandro Martinez Soto 
* Autor 3: Julian Andres Tunjano Bermudez 
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
#include <algorithm> 

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
        promedios.push_back(0.0f); // Agregar un promedio de 0 si no hay notas
        return;
    }
    float suma = 0.0f;
    for (float n : fila) {
        suma += n;
    }
    promedios.push_back(suma / fila.size());
}
void mezclar(vector<vector<float>>& notas, vector<string>& nombres, vector<float>& promedios, int ini, int mitad, int fin) {
    vector<vector<float>> auxNotas;
    vector<string> auxNombres;
    vector<float> auxPromedios;

    int i = ini;
    int j = mitad + 1;

    while (i <= mitad && j <= fin) {
        // Ordenar de mayor a menor promedio; si son iguales, mantiene el orden original
        if (promedios[i] >= promedios[j]) {
            auxNotas.push_back(notas[i]);
            auxNombres.push_back(nombres[i]);
            auxPromedios.push_back(promedios[i]);
            i++;
        } else {
            auxNotas.push_back(notas[j]);
            auxNombres.push_back(nombres[j]);
            auxPromedios.push_back(promedios[j]);
            j++;
        }
    }

    // Copiar sobrantes de la mitad izquierda
    while (i <= mitad) {
        auxNotas.push_back(notas[i]);
        auxNombres.push_back(nombres[i]);
        auxPromedios.push_back(promedios[i]);
        i++;
    }

    // Copiar sobrantes de la mitad derecha
    while (j <= fin) {
        auxNotas.push_back(notas[j]);
        auxNombres.push_back(nombres[j]);
        auxPromedios.push_back(promedios[j]);
        j++;
    }

    // Devolver los tres resultados sincronizados a los vectores originales
    for (size_t k = 0; k < auxNotas.size(); k++) {
        notas[ini + k] = auxNotas[k];
        nombres[ini + k] = auxNombres[k];
        promedios[ini + k] = auxPromedios[k];
    }
}

void mergeSort(vector<vector<float>>& notas, vector<string>& nombres, vector<float>& promedios, int ini, int fin) {
    if (ini >= fin) return; // Caso base: 0 o 1 estudiante ya está ordenado

    int mitad = (ini + fin) / 2;
    mergeSort(notas, nombres, promedios, ini, mitad);
    mergeSort(notas, nombres, promedios, mitad + 1, fin);
    mezclar(notas, nombres, promedios, ini, mitad, fin);
}

float mayor(const vector<float>& v, int inicio, int final) {
    if (inicio==final) return v[inicio];
    int mitad=(inicio + final )/ 2;
    float izq= mayor(v,inicio,mitad); 
    float dere=mayor (v, mitad + 1,final );
    return max(izq,dere); 

}
float menor(const vector<float>& v, int inicio, int final) {
    if (inicio==final) return v[inicio];
    int mitad=(inicio + final )/ 2;
    float izq= menor(v,inicio,mitad); 
    float dere=menor (v, mitad + 1,final );
    return min(izq,dere); 
}

float sumatotal(const vector<float>& v, int inicio, int final) {
    if (inicio== final) return v[inicio];
    int mitad = (inicio +final) / 2; 
    return sumatotal(v,inicio,mitad)+ sumatotal(v,mitad + 1,final);
}
//que sueno colega, suficiente por hoy, voy a dejar que neko se me acueste en el teclado, Suarez ven te invito a subir mira en el free fire. 
int buscarEstudiante(const vector<string>& nombres, const string& buscado, int indice = 0) {

    if(indice >= static_cast<int>(nombres.size())){
        return -1;
    }
    if (nombres[indice] == buscado){
        return indice;
    }
    return buscarEstudiante(nombres, buscado, indice +1);

}

