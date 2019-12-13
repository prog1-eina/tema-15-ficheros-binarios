#include <fstream>
#include <iostream>
#include "calculos.h"
using namespace std;

const int MAX_PRIMOS = 5000000;
const char NOMBRE_FICHERO_PRIMOS[] = "../primos.dat";

/*
 * Pre:  El vector «primos» tiene al menos «n» componentes.
 * Post: Si existe un fichero binario denominado «NOMBRE_FICHERO_PRIMOS» que
 *       contiene al menos los primeros «n» números primos almacenados en orden
 *       creciente, ha copiado los primeros «n» datos del fichero en las
 *       primeras «n» componentes del vector «primos», de forma que almacenan, en
 *       orden creciente, los primeros «n» números primos y ha devuelto «true». 
 *       En caso contrario (si el fichero no existe o si contiene menos de «n»
 *       números primos), ha devuelto «false».
 */
bool leerFicheroPrimos(int primos[], const int n) {
    ifstream f;
    f.open(NOMBRE_FICHERO_PRIMOS, ios::binary);
    if (f.is_open()) {
        f.read(reinterpret_cast<char*>(&primos), n * sizeof(int));
        bool ok = !f.eof();
        f.close();
        return ok;
    }
    else {
        return false;
    }
}

/*
 * Pre:  El vector «primos» tiene al menos «n» componentes.
 * Post: Las primeras «n» componentes del vector «primos» almacenan, en orden
 *       creciente, los primeros «n» números primos, que han sido calculados por
 *       esta función.
 */
void calcular(int primos[], const int n) {
    primos[0] = 2;
    int i = 1;
    int p = 3;
    while (i < n) {
        if (esPrimo(p)) {
            primos[i] = p;
            i++;
        }
        p += 2;
    }    
}

/*
 * Pre:  El vector «primos» tiene al menos «n» componentes que almacenan, en orden
 *       creciente, los primeros «n» números primos.
 * Post: Ha escrito en un fichero binario denominado «NOMBRE_FICHERO_PRIMOS» los
 *       primeros «n» números primos en orden creciente, tal y como aparecen en
 *       el vector «primos».
 */
void guardar(const int primos[], const int n) {
    ofstream f;
    f.open(NOMBRE_FICHERO_PRIMOS, ios::binary);
    if (f.is_open()) {
        f.write(reinterpret_cast<const char*>(primos), n * sizeof(int));                
        f.close();
    }
    else {
        cerr << "Error creando el fichero \"" << NOMBRE_FICHERO_PRIMOS 
             << "\"." << endl;
    }
}


/*
 * Pre:  El vector «primos» tiene al menos «n» componentes.
 * Post: Las primeras «n» componentes del vector «primos» almacenan, en orden
 *       creciente, los primeros «n» números primos. 
 *       Existe ahora también un fichero binario denominado
 *       «NOMBRE_FICHERO_PRIMOS» que almacena al menos los primeros «n» números
 *       primos en orden creciente.
 */
void inicializar(int primos[], const int n) {
    bool ok = leerFicheroPrimos(primos, n);
    if (!ok) {
        calcular(primos, n);
        guardar(primos, n);
    }
}

/*
 * Primeras instrucciones de una supuesta aplicación criptográfica que necesita
 * trabajar con un vector que contenga los primeros 5 000 000 números primos.
 * En el estado actual, se limita a cargar en memoria un vector de 5 000 000
 * componentes con los primeros números primos.
 */
int main() {
    // El vector «primos» que se declara a continuación es demasiado grande para
    // ser almacenado en la pila (el segmento de memoria donde se ubican
    // habitualmente las variables locales de una función). Con el modificador
    // «static», se indica al compilador que la ubique en el segmento de datos.
    // Os darán más detalles en la asignatura de Arquitectura de Computadores.
    static int primos[MAX_PRIMOS];
    
    inicializar(primos, MAX_PRIMOS);
   
    cout << "Vector con los primeros " << MAX_PRIMOS << " cargado." << endl;
    return 0;
}
