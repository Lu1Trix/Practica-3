#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <fstream>
#include <string>
#include <iostream>
#include <windows.h> // Esta libreria es opcional; Función y uso: decoración del cajero electrónico;

using namespace std;

void Welcomeship( const char* str ){ // Mostrar una imagen decorativa;

    SetConsoleOutputCP(CP_UTF8);
    ifstream folder; char caracter;

    folder.open(str);
    while (folder.good()){
        caracter = folder.get();
        cout << caracter;
    }
    folder.seekg(0);
    folder.close();
}


// Funciones para decodificación de la informacion provenientes de programas anteriores.

long int base2(unsigned int numero){ // Obtener potencias de dos;
    long int resultado = 1;
    for (int i = 0; i < numero; i++){
        resultado *= 2;
    }
    return resultado;
}
string binario(char caracter){ // Convertir caracter a binario;

    string binario = "00000000";
    int number = int(caracter);
    int contador = 7;

    while (number / 2 >= 2){
        binario[contador] = ((number % 2)+48);
        contador--;
        number /= 2;
    }
    binario[contador] = ((number % 2)+48);
    contador--;
    binario[contador] = ((number / 2)+48);
    while (contador > 0){
        contador--;
        binario[contador] = 48;
    }
    return binario;



}
string codificador1(string resultante, unsigned int semilla){
    long int unos = 0;
    long int ceros = 0;
    long int posicion = 0;
    int contador = 1;
    bool invertir = false;
    bool dos = false;
    bool tres = false;

    // Invertir las primeras semilla posiciones
    while (posicion < semilla){
        if (resultante[posicion] == 48){
            ceros++;
            resultante[posicion] = 49;
        }
        else if (resultante[posicion] == 49){
            unos++;
            resultante[posicion] = 48;
        }
        posicion++;
    }
    // Codificación de los bits

    while (posicion < (int(resultante.size())-8)){
        if (posicion % semilla == 0){
            // Estalecer el criterio de comparación
            if (ceros == unos){
                invertir = true;
                dos = false;
                tres = false;
            }
            if (ceros > unos){
                invertir = false;
                dos = true;
                tres = false;
            }
            if (ceros < unos){
                tres = true;
                dos = false;
                invertir = false;
            }
            ceros = 0;
            unos = 0;
        }
        if (invertir){
            if (resultante[posicion] == 48){
                resultante[posicion] = 49;
                ceros++;
            }
            else if (resultante[posicion] == 49){
                resultante[posicion] = 48;
                unos++;
            }
        }
        if (dos){
            if (contador == 2){
                contador = 1;
                if (resultante[posicion] == 48){
                    resultante[posicion] = 49;
                    ceros++;
                }
                else if (resultante[posicion] == 49){
                    resultante[posicion] = 48;
                    unos++;
                }
            }
            else{
                contador++;
                if (resultante[posicion] == 48){
                    ceros++;
                }
                else if (resultante[posicion] == 49){
                    unos++;
                }
            }
        }
        if (tres){
            if (contador == 3){
                contador = 1;
                if (resultante[posicion] == 48){
                    resultante[posicion] = 49;
                    ceros++;
                }
                else if (resultante[posicion] == 49){
                    resultante[posicion] = 48;
                    unos++;
                }
            }
            else{
                contador++;
                if (resultante[posicion] == 48){
                    ceros++;
                }
                else if (resultante[posicion] == 49){
                    unos++;
                }
            }

        }
        posicion++;
    }
    return resultante.substr(0,(int(resultante.size())-8));

}
string metodo_uno(const char* documento, unsigned int semilla){ // Aplicar codificación metodo # 1;
    //Abrir el archivo y el arreglo a codificar.
    ifstream folder;
    char caracter;
    string pointer;
    string codificado = "";
    long int contador = 0;
    folder.open(documento);

    //Obtener arreglo en binario.
    while (folder.good()){
        caracter = folder.get();
        pointer = binario(caracter);

        codificado += pointer;
    }

    //Codificar el archivo en binario.
    codificado = codificador1(codificado,semilla);
    folder.close();

    return codificado;
}
string codificador2(string resultante, unsigned int semilla){
    long int posicion = 0;
    char intercambio = resultante[semilla-1];
    long int contador = 0;
    char antes = resultante[posicion];
    char despues;

    while (posicion < resultante.size()){
        if ((posicion + 1) % semilla == 0){
            resultante[contador] = intercambio;
            intercambio = resultante[posicion + semilla];
            contador = posicion + 1;
            antes = resultante[posicion + 1];
        }
        else{
            despues = resultante[posicion + 1];
            resultante[posicion + 1] = antes;
            antes = despues;
        }
        posicion++;

    }
    return resultante.substr(0,(int(resultante.size())-8));

}
string metodo_dos(const char* documento, unsigned int semilla){ // Aplicar codificación metodo # 2;
    //Abrir el archivo y el arreglo a codificar.
    ifstream folder;
    char caracter;
    string pointer;
    string codificado = "";
    long int contador = 0;
    folder.open(documento);

    //Obtener arreglo en binario.
    while (folder.good()){
        caracter = folder.get();
        pointer = binario(caracter);

        codificado += pointer;
    }

    //Codificar el archivo en binario.
    codificado = codificador2(codificado,semilla);
    folder.close();

    return codificado;
}
void documento_codificado(string decodificado, const char* document){ // Generar el archivo con los bits codificados
    long int posicion = 0;
    ofstream folder; folder.open(document);
    while (posicion < decodificado.size()){
        folder << decodificado[posicion];
        posicion++;
    }
    folder.close();



}
char bintotxt(string cadena_binaria){

    long int resultado = 0;
    for (unsigned int i = 0; i < 8; i++){
        resultado += (int(cadena_binaria[7-i])-48)*base2(i);
    }
    return char(resultado);

}
string decodificador1(string resultante, unsigned int semilla){
    long int unos = 0;
    long int ceros = 0;
    long int posicion = 0;
    int contador = 1;
    bool invertir = false;
    bool dos = false;
    bool tres = false;

    // Invertir las primeras semilla posiciones
    while (posicion < semilla){
        if (resultante[posicion] == 48){
            unos++;
            resultante[posicion] = 49;
        }
        else if (resultante[posicion] == 49){
            ceros++;
            resultante[posicion] = 48;
        }
        posicion++;
    }
    // Codificación de los bits

    while (posicion < (int(resultante.size()))){
        if (posicion % semilla == 0){
            // Estalecer el criterio de comparación
            if (ceros == unos){
                invertir = true;
                dos = false;
                tres = false;
            }
            if (ceros > unos){
                invertir = false;
                dos = true;
                tres = false;
            }
            if (ceros < unos){
                tres = true;
                dos = false;
                invertir = false;
            }
            ceros = 0;
            unos = 0;
        }
        if (invertir){
            if (resultante[posicion] == 48){
                resultante[posicion] = 49;
                unos++;
            }
            else if (resultante[posicion] == 49){
                resultante[posicion] = 48;
                ceros++;
            }
        }
        if (dos){
            if (contador == 2){
                contador = 1;
                if (resultante[posicion] == 48){
                    resultante[posicion] = 49;
                    unos++;
                }
                else if (resultante[posicion] == 49){
                    resultante[posicion] = 48;
                    ceros++;
                }
            }
            else{
                contador++;
                if (resultante[posicion] == 48){
                    ceros++;
                }
                else if (resultante[posicion] == 49){
                    unos++;
                }
            }
        }
        if (tres){
            if (contador == 3){
                contador = 1;
                if (resultante[posicion] == 48){
                    resultante[posicion] = 49;
                    unos++;
                }
                else if (resultante[posicion] == 49){
                    resultante[posicion] = 48;
                    ceros++;
                }
            }
            else{
                contador++;
                if (resultante[posicion] == 48){
                    ceros++;
                }
                else if (resultante[posicion] == 49){
                    unos++;
                }
            }

        }
        posicion++;
    }
    return resultante;
}
string decodificador2(string resultante, unsigned int semilla){
    long int posicion = 0;
    char intercambio = resultante[semilla-1];
    long int contador = 0;

    while (posicion < resultante.size()){
        if ((posicion + 1) % semilla == 0){
            resultante[posicion] = intercambio;
            intercambio = resultante[posicion + 1];
        }
        else{
            resultante[posicion] = resultante[posicion + 1];
        }
        posicion++;

    }
    return resultante;
}
string DeCoDe1(const char* documento, unsigned int semilla){
    ifstream folder;
    string codificado = "";
    string resultante = "";
    long int max = 8;
    long int min = 0;
    long int contador = 0;
    folder.open(documento);

    //Obtener arreglo en binario.
    while (folder.good()){
        codificado += folder.get();
    }
    codificado = codificado.substr(0,codificado.size()-1);
    //Codificar el archivo en binario.
    codificado = decodificador1(codificado,semilla);
    while(max <= codificado.size()){
        resultante += bintotxt(codificado.substr(min,max));
        max += 8;
        min += 8;
    }
    folder.close();

    return resultante;

}
string DeCoDe2(const char* documento, unsigned int semilla){
    ifstream folder;
    string codificado = "";
    string resultante = "";
    long int max = 8;
    long int min = 0;
    long int contador = 0;
    folder.open(documento);

    //Obtener arreglo en binario.
    while (folder.good()){
        codificado += folder.get();
    }
    codificado = codificado.substr(0,codificado.size()-1);
    //Codificar el archivo en binario.
    codificado = decodificador2(codificado,semilla);
    while(max <= codificado.size()){
        resultante += bintotxt(codificado.substr(min,max));
        max += 8;
        min += 8;
    }
    folder.close();

    return resultante;

}

#endif // FUNCIONES_H
