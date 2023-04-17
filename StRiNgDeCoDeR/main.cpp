#include <iostream>
#include <StRiNgFuNtIoNs.h>
#include <string>
using namespace std;

int main()
{
    try{
    TeMpLaTeS("Imagen.txt");
    int decodificar;
    cout << "[-> ¿Quisieras codificar ó decodificar un archivo ya en binario? [1]/[2]: "; cin >> decodificar;

    char entrada[256];
    cout << "[-> Selecciona la ruta del archivo el cual quieres codificar: "; cin >> entrada;
    char salida[256];
    cout << "[-> Selecciona la ruta del archivo de salida: "; cin >> salida;
    int metodo;
    cout << "[-> Selecciona el metodo para realizar la codificacion [1]/[2]: "; cin >> metodo;

    unsigned int semilla;
    cout << "[-> Seleccione la semilla de codificacion: "; cin >> semilla;
    //Ejecucción de los metodos;
    string resultado;
    ifstream Archivo;
    Archivo.open(entrada);

    if (!Archivo.is_open()){
        throw "Error al abrir el archivo";
    }
    else{
        Archivo.close();
    }

    if (decodificar == 1){ // Codificación de un archivo de texto a binario;
        if (metodo ==  1){
            resultado = metodo_uno(entrada,semilla);
        }
        else{
            resultado = metodo_dos(entrada,semilla);
        }

    }
    else{ // Codificación de un archivo a binario a texto;
        if (metodo ==  1){
            resultado = DeCoDe1(entrada, semilla);
        }
        else{
            resultado = DeCoDe2(entrada, semilla);
        }


    }
    documento_codificado(resultado, salida);
    cout << "[-> Se realizo correctamente la codificacion en el archivo " << salida << endl;
    }
    catch (const char* C){
        cout << C << endl;
    }
    catch (...){
        cout<<"Error no definido\n";
    }



}
