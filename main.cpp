#include <bits/stdc++.h>
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
        bool is_cano(){return cano;}
    private:
        bool cano;
};

void get_input(int* vida_heroe, int* cant_esbirros, int* vida_esbirros, int* esbirro_cano){

    
    cin >> *vida_heroe;
    while(vida_heroe <= 0){
        cin >> *vida_heroe;
    };

    
    cin >> *cant_esbirros;
    while(*cant_esbirros <= 0){
        cin >> *cant_esbirros;
    };


    // CREAR CLASSES EN EL LOOP
    vida_esbirros = new int[*cant_esbirros];
    esbirro_cano = new int[*cant_esbirros];
    
    for(int i = 0; i < *cant_esbirros; i++){
        cin >> esbirro_cano[i];
    }
}

int main(){
    int vida_heroe = 0;
    int cant_esbirros = 0;
    int* vida_esbirros;
    int* esbirro_cano;

    get_input(&vida_heroe, &cant_esbirros, vida_esbirros,esbirro_cano);

    
    return 0;
}