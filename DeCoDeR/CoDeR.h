#ifndef CODER_H
#define CODER_H
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
void TeMpLaTeS(const char* folder){ // Mostrar una imagen o texto de un Archivo en la consola.
    ifstream Archivo;
    char texto;
    Archivo.open(folder);
    if (Archivo.is_open()){
        cout << "[-> Se logro abrir el archivo" << endl;
        // Cambiar el encoding de la consola
        SetConsoleOutputCP(CP_UTF8);
        while(Archivo.good()){
            texto=Archivo.get();
            cout << texto;
        }
        Archivo.seekg(0);
    }
    else cout << "[-> No se logro abrir el archivo" << endl;
    Archivo.close();


}
char* BiNaRiO(char caracter){ // Pasar de una cadena de caracteres a binario.
    static char binario[8];
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
char* CoDiFiCaDoR_1(char* resultante, unsigned int semilla){ // Codificar una linea de bits del metodo 1.
    long int unos = 0;
    long int ceros = 0;
    long int posicion = 0;
    int contador = 1;
    bool continuar = true;
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
    while (continuar){
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
        if (resultante[posicion] == 48 || resultante[posicion] == 49){
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
        }
        else{
            continuar = false;
        }
        posicion++;
    }
    posicion -= 8;
    char* codificado = new char[posicion];
    for (long int j = 0; j < posicion; j++){
        codificado[j] = resultante[j];
    }
    return codificado;





}
char* CoDiFiCaDoR_2(char* resultante, unsigned int semilla){ // Codificar una linea de bits del metodo 2.
    long int posicion = 0;
    char intercambio = resultante[semilla-1];
    long int contador = 0;
    char antes = resultante[posicion];
    char despues;
    bool continuar = true;

    while (continuar){
        if (resultante[posicion + 1] == 48 || resultante[posicion + 1] == 49){
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
        else continuar = false;

    }
    posicion -= 6;
    char* codificado = new char[posicion];
    for (long int j = 0; j < posicion; j++){
        codificado[j] = resultante[j];
    }
    return codificado;
}
char* MeToDo_UnO(const char* documento, unsigned int semilla){ // Aplicar el metodo uno devolviendo una linea de bits codificados

    //Abrir el archivo y el arreglo a codificar.
    ifstream folder;
    char caracter;
    char* pointer;
    char* codificado;
    long int contador = 0;
    folder.open(documento);
    char* resultante = new char[80000000];

    //Obtener arreglo en binario.
    while (folder.good()){
        caracter = folder.get();
        pointer = BiNaRiO(caracter);

        for(int i = 0; i < 8; i++){
            resultante[contador] = pointer[i];
            contador++;
        }
    }

    //Codificar el archivo en binario.
    codificado = CoDiFiCaDoR_1(resultante,semilla);
    delete[] resultante;
    folder.close();

    return codificado;
}
char* MeToDo_DoS(const char* documento, unsigned int semilla){ // Aplicar el metodo dos devolviendo una linea de bits codificados
    //Abrir el archivo y el arreglo a codificar.
    ifstream folder;
    char caracter;
    char* pointer;
    char* codificado;
    long int contador = 0;
    folder.open(documento);
    char* resultante = new char[80000000];

    //Obtener arreglo en binario.
    while (folder.good()){
        caracter = folder.get();
        pointer = BiNaRiO(caracter);

        for(int i = 0; i < 8; i++){
            resultante[contador] = pointer[i];
            contador++;
        }
    }

    //Codificar el archivo en binario.
    codificado = CoDiFiCaDoR_2(resultante,semilla);
    delete[] resultante;
    folder.close();
    return codificado;
}
void DoCuMeNtO_CoDiFicAdO(char* decodificado, const char* document){ // Generar el archivo con los bits codificados
    long int posicion = 0;
    ofstream folder; folder.open(document);
    while (decodificado[posicion] == 48 || decodificado[posicion] == 49){
        folder << decodificado[posicion];
        posicion++;
    }
    folder.close();



}
void DoCuMeNtO_CoDiFicAdO_TeXtO(char* decodificado, const char* document){ // Generar el archivo con los bits codificados
    long int posicion = 0;
    ofstream folder; folder.open(document);
    while (decodificado[posicion] != NULL){
        folder << decodificado[posicion];
        posicion++;
    }
    folder.close();



}
long int BaSe2(unsigned int numero){
    long int resultado = 1;
    for (int i = 0; i < numero; i++){
        resultado *= 2;
    }
    return resultado;
}
char BiNtOtxT(char* cadena_binaria){

    long int resultado = 0;
    for (unsigned int i = 0; i < 8; i++){
        resultado += (int(cadena_binaria[7-i])-48)*BaSe2(i);
    }
    return char(resultado);

}
char* FDeCoDeR(char* resultante, unsigned int semilla){
        long int unos = 0;
        long int ceros = 0;
        long int posicion = 0;
        int contador = 1;
        bool continuar = true;
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
        while (continuar){
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
            if (resultante[posicion] == 48 || resultante[posicion] == 49){
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
            }
            else{
                continuar = false;
            }
            posicion++;
        }

        char* codificado = new char[posicion];
        for (long int j = 0; j < posicion; j++){
            codificado[j] = resultante[j];
        }
        return codificado;
}
char* FDeCoDeR2(char* resultante, unsigned int semilla){
    long int posicion = 0;
    char intercambio = resultante[0];
    bool continuar = true;

    while (continuar){
        if (resultante[posicion + 1] == 48 || resultante[posicion + 1] == 49){
            if ((posicion + 1) % semilla == 0){
                resultante[posicion] = intercambio;
                intercambio = resultante[posicion + 1];
            }
            else{
                resultante[posicion] = resultante[posicion + 1];
            }
            posicion++;
        }
        else continuar = false;

    }
    posicion += 2;
    char* codificado = new char[posicion];
    for (long int j = 0; j < posicion; j++){
        codificado[j] = resultante[j];
    }
    return codificado;
}
char* Palabras(char* codificado){
    char palabras[8];
    unsigned int contador2 = 0;
    unsigned int contador3 = 0;

    while (codificado[contador2] == 48 || codificado[contador2] == 49){
        contador2++;
    }
    long unsigned int tamaño = contador2 + 1;
    contador2 = 0;

    char* resultado = new char[tamaño];

    for (long int contador = 0; contador < tamaño; contador++){
        if (contador % 8 == 0 && contador != 0){
            resultado[contador2] = BiNtOtxT(palabras);
            contador2++;
            contador3 = 0;

        }
        palabras[contador3] = codificado[contador];
        contador3++;
    }
    resultado[contador2] = NULL;
    delete[] codificado;
    return resultado;
}
char* DeCoDe1(const char* documento, unsigned int semilla){
    ifstream folder;
    folder.open(documento);
    char* codificado;
    long int contador = 0;
    char* resultante = new char[10000000];
    while (folder.good()){
        resultante[contador] = folder.get();
        contador++;

    }
    codificado = FDeCoDeR(resultante,semilla);
    delete[] resultante;
    codificado = Palabras(codificado);

    folder.close();

    return codificado;

}
char* DeCoDe2(const char* documento, unsigned int semilla){
    ifstream folder;
    folder.open(documento);
    char* codificado;
    long int contador = 0;
    char* resultante = new char[10000000];
    while (folder.good()){
        resultante[contador] = folder.get();
        contador++;

    }
    codificado = FDeCoDeR2(resultante,semilla);
    delete[] resultante;
    codificado = Palabras(codificado);

    folder.close();

    return codificado;
}


#endif // CODER_H


