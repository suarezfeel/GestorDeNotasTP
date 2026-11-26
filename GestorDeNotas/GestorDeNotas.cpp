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
#include <chrono>
#include <thread>
using namespace std;

void limpiarPantalla() {
for(int i = 5; i > 0; i--) {
cout << "\nLa pantalla se limpiara en " << i << "..." << endl;
this_thread::sleep_for(chrono::seconds(1));
}
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif
}

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
int buscarEstudiante(const vector<string>& nombres, const string& buscado, int indice = 0) {

    if(indice >= static_cast<int>(nombres.size())){
        return -1;
    }
    if (nombres[indice] == buscado){
        return indice;
    }
    return buscarEstudiante(nombres, buscado, indice +1);

}
float consultarEstudiante(const vector<float> &promedios, int indiceEstudiante) {
    return promedios[indiceEstudiante];
}

 int main () { 

    vector<vector<float>> notas;
    vector<string> nombres;
    vector<float> promedios;
    string buscado; 

    cargarNotas(notas,nombres, "notas.txt");

    for (int i=0; i< notas.size(); i++) {
        calcularPromedio(notas[i],promedios);
    }
    int eleccion; 
    do { 
        cout<<"1.Consultar estudiante"<<endl; 
        cout<<"2.Ranking"<<endl; 
        cout<<"3.EStadisticas"<<endl;
        cout<<"4.Agregar estudiante"<<endl; 

        cin>>eleccion; 

        if (nombres.empty() && eleccion >= 1 && eleccion <= 3) {
            cout << "No hay datos" << endl;
        }
        else {
            switch (eleccion) {
                case 1: {
                    cout<<"Ingrese el nombre del estudiante a buscar: ";
                    cin>>buscado;
                    cout << "El estudiante " << buscado << " se encuenta en la posicion " << buscarEstudiante(nombres,buscado) << " y tiene un promedio de " << consultarEstudiante(promedios, buscarEstudiante(nombres, buscado));
                    break;
                }
                case 2: {
                    mergeSort(notas, nombres, promedios, 0, nombres.size() - 1);
                    for (size_t i = 0; i < nombres.size(); i++) {
                        cout << i + 1 << "  " << nombres[i] << "  " << promedios[i] << endl;
                    }
                    break;
                }
        
            }
        }
    } while (eleccion!=0); //Esta llave es la del do 
    return 0; 
}