/*#include <bits/stdc++.h>*/
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <string>

using namespace std;


/*
La primera línea consta de un número v, el cual corresponde a la vida del héroe mechón.
La segunda línea consta de un número n, el cual corresponde al número total de esbirros generados por PEPE.
La tercera línea consta de n números separados por espacios, indicando la vida de los esbirros, en el mismo orden en el que atacarán la ciudad.
La cuarta línea consta de n números separados por espacios, indicando el ataque de cada esbirro, en el mismo orden en el que atacarán la ciudad.
La quinta línea consta de n valores binarios separados por espacios, indicando con un 1 si el i-ésimo esbirro es un CANO o 0 en caso contrario. Para efectos del trabajo, asumiremos que todos los CANO se dividirán luego del segundo ataque recibido.
*/


/*
los CANO se dividirán luego del segundo ataque recibido.
*/

vector<int> read_file(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << archivo << endl;
        exit(1);
    }

    vector<int> data;
    int valor;

    // Leer todos los valores del archivo y almacenarlos en el vector
    while (file >> valor) {
        data.push_back(valor);
    }

    // Verificar si se leyeron los valores correctamente
    if (data.size() < 5) {
        cerr << "Error: El archivo no contiene suficientes datos." << endl;
        exit(1);
    }

    file.close();
    return data;
}

class Entidad{
    public:
    
        int get_vida() {return vida;}
        int get_ataque() {return ataque;}
        int set_vida(int val) {vida = val;}
        int set_ataque(int val) {ataque = val;}
    private:
        int vida;
        int ataque;
};

class Esbirro: public Entidad{
    public:
        Esbirro(int vida, int ataque, bool is_cano ){
            this->set_vida(vida);
            this->set_ataque(ataque);
            this->cano = is_cano;
        };
        bool get_cano(){return cano;}
    private:
        bool cano;
};


void get_input(string* nombre_archivo, Entidad* mechon, deque<Esbirro>* deq_esbirros){

    vector<int> data = read_file(*nombre_archivo);

    // Verificar que los valores sean válidos
    if (data[0] <= 0 || data[1] <= 0){
        cerr << "Error: La vida del héroe y la cantidad de esbirros deben ser mayores a cero." << endl;
        exit(1);
    }
    // Leer valores de vida del héroe y cantidad de esbirros
    int vida_heroe = data[0];
    int cant_esbirros = data[1];

    // Inicializar el héroe
    mechon->set_vida(vida_heroe);
    mechon->set_ataque(2);

    // Leer valores de esbirros
    for (int i = 0; i < cant_esbirros; i++){

        // Verificar que lo valores sean válidos
        if (data[2 + i] <= 0 || data[2 + cant_esbirros + i] <= 0 || (data[2 + 2*cant_esbirros + i] != 0 && data[2 + 2*cant_esbirros + i] != 1)){
            cerr << "Error: La vida y el ataque de los esbirros deben ser mayores a cero, y el valor de cano debe ser 0 o 1." << endl;
            exit(1);
        }

        // Leer los valores de vida, ataque y cano
        int vida = data[2 + i];
        int ataque = data[2 + cant_esbirros + i];
        bool cano = data[2 + 2*cant_esbirros + i] == 1;

        Esbirro esb(vida, ataque, cano);
        deq_esbirros->push_back(esb);
    }
}

int main() {

    int daño_realizado = 0, contador = 0, esbirros_derrotados = 0;
    Entidad mechon;
    deque<Esbirro> deq_esbirros;
    string nombre_archivo = "Ejemplo.txt"; // Luego se puede poner un cin

    get_input(&nombre_archivo, &mechon, &deq_esbirros);

    // Simulación de ataques
    while (!deq_esbirros.empty()) {

        // Si el mechón no tiene vida, se termina el juego
        if (mechon.get_vida() <= 0) {
            cout << daño_realizado << endl << "RIP mechón" << endl;
            return 0;
        }

        // Si el mechón derrota a 5 esbirros, aumenta su ataque
        if (esbirros_derrotados == 5) {
            mechon.set_ataque(mechon.get_ataque() + 1);
            esbirros_derrotados = 0;
        }
        
        // El mechón ataca al esbirro
        deq_esbirros[0].set_vida(deq_esbirros[0].get_vida() - mechon.get_ataque());
        daño_realizado += mechon.get_ataque();
        if (deq_esbirros.front().get_cano()) {
            contador++;
        }
        
        // El esbirro ataca al mechón
        mechon.set_vida(mechon.get_vida() - deq_esbirros[0].get_ataque());
        
        // Si el esbirro es CANO, se divide luego de la segunda vez que recibe daño
        if (deq_esbirros[0].get_cano() && deq_esbirros[0].get_vida() > 1 && contador == 2) {
            Esbirro division(deq_esbirros.front().get_vida() - 1, deq_esbirros.front().get_ataque() - 1, false);
            deq_esbirros.pop_front();
            deq_esbirros.push_front(division);
            deq_esbirros.push_front(division);
            contador = 0;
            continue;
        }

        // Si el esbirro es derrotado, se elimina
        if (deq_esbirros[0].get_vida() <= 0) {
            daño_realizado += deq_esbirros[0].get_vida();
            deq_esbirros.pop_front();
            esbirros_derrotados++;
        }
    }
    
    // Si el mechón sobrevive
    if (mechon.get_vida() > 0) {
        cout << daño_realizado << endl << "EZ pizi" << endl;
    } 

    return 0;
}