#include <iostream>
#include <string>
#include <Funciones.h>

using namespace std;

int main()
{
    // Datos organizados en arreglo multidimensional;

    // Toda la información de los usuarios esta encriptada en un archivo;

    // Encriptación realizada:
        // Metodo: 1;
        // Semilla: 3;

    string password = DeCoDe1("Administrator.txt",3); // Extración contraseña del administrador;
    string usuarios = DeCoDe1("Users.txt",3); // Extración información de los usuarios;

    // Datos en archivos:  Usuario,Document,Password,Money;

    long unsigned int users = 0;   // Obtener el numero de usuarios registrados;

    for(long unsigned int H = 0; H < usuarios.length(); H++){
        if (usuarios[H] == 59){
            users++;
        }
    }

    // Información almacenada para su uso;

    string temporal; string temporal2;
    string data[256][4];

    for (long int j = 0; j < users; j++){
        temporal = usuarios.substr(0,usuarios.find(";"));
        usuarios.erase(0,usuarios.find(";")+2);
        for(long int k = 0; k < 4; k++){
            temporal2 = temporal.substr(0,temporal.find(","));
            temporal.erase(0,temporal.find(",")+1);
            data[j][k] = temporal2;

        }
    }

    Welcomeship("Welcomeship.txt"); // [-> Bienvenida con imagen de un documento;

    bool continuar = true; bool acceso = false; unsigned int seleccion; string saldo; string comparado;
    string usuario; string contraseña; long int monto; long int posicion; long int saldo_resultado;

    string Nombre;
    string Newpass;
    string cedula;
    string COP;
    try{
    while(continuar){

        cout << "[-> Bienvenido a su cajero CASH LOADER" << endl << "[-> [1] Iniciar sesión." << endl << "[-> [2] Administrador." << endl << "[-> [3] Salir" << endl;
        cin >> seleccion;

        if (seleccion == 1){
            cout << "[-> Escriba su nombre de usuario: ";
            cin >> usuario;
            cout << "[-> Escriba su contraseña: ";
            cin >> contraseña;

            for (long int K = 0; K < users; K++){
                comparado = data[K][0];
                if ((usuario.compare(comparado)) == 0){
                    comparado = data[K][2];
                    if ((contraseña.compare(comparado)) == 0){
                        acceso = true;
                        posicion = K;
                    }
                }
            }

            if(acceso){
                 cout << "[-> Acceso concedido, ¡Bienvenido " << usuario << "!" << endl;
                 while(acceso){
                    cout << "[-> ¿Qué deseas realizar el dia de hoy?" << endl << "[-> [1] Consultar saldo; Costo: 1000$" << endl << "[-> [2] Retirar dinero; Costo: 1000$" << endl << "[-> [3] Salir" << endl;
                    cin >> seleccion;

                    if (seleccion == 1){
                        saldo = data[posicion][3];
                        saldo_resultado = stoi(saldo) - 1000;
                        cout << "Su saldo actualmente es: " << saldo_resultado << endl;
                        saldo = to_string(saldo_resultado);
                        data[posicion][3] = saldo;

                    }
                    else if(seleccion == 2){
                        cout << "[-> Seleccione su monto:";
                        cin >> monto;
                        saldo = data[posicion][3];
                        saldo_resultado = stoi(saldo) - monto - 1000;
                        cout << "Su saldo actualmente es: " << saldo_resultado << endl;
                        saldo = to_string(saldo_resultado);
                        data[posicion][3] = saldo;
                    }
                    else if(seleccion == 3){
                        acceso = false;
                         cout << "[-> Sesión finalizada";
                    }
                    else{
                        cout << "[-> Seleccione una opción valida.";
                    }
                 }
            }
            else{
                cout << "[-> Acceso denegado, intente nuevamente." << endl;
            }
        }
        else if (seleccion == 2){
            cout << "[-> Escriba la contraseña de administrador: "; cin >> contraseña;
            if (contraseña.compare(password) ==  0){
                acceso = true;
                if (acceso){
                    cout << "[-> Acceso concedido, ¡Bienvenido Administrador!" << endl << "[-> ¿Qué desea hacer el dia de hoy?" << endl;
                    while(acceso){
                        cout << "[-> [1] Agregar nuevo usuario." << endl << "[-> [2] Salir.";
                        cin >> seleccion;
                        if (seleccion == 1){
                            cout << "[-> RECUERDE QUE TODO USUARIO CON NOMBRE REPETIDO SERA DESCARTADO.";
                            cout << "[-> Ingrese el nombre del usuario:"; cin >> Nombre;
                            cout << "[-> Ingrese la cedula del usuario:"; cin >> cedula;
                            cout << "[-> Ingrese la contraseña del usuario:"; cin >> Newpass;
                            cout << "[-> Ingrese el monto inicial del usuario:"; cin >> COP;

                            data[users][0] = Nombre;
                            data[users][1] = cedula;
                            data[users][2] = Newpass;
                            data[users][3] = COP;

                            users++;
                        }
                        else if (seleccion == 2){
                            acceso = false;
                            cout << "[-> Sesión finalizada";
                        }
                        else{
                            cout << "[-> Seleccione una opción valida.";
                        }
                    }
                }
                else{
                    cout << "[-> Acceso denegado, intente nuevamente." << endl;
                }
            }

        }
        else if(seleccion == 3){
            cout << "¡Vuelva pronto!" << endl;
            continuar = false;
        }
        else{
            cout << "[-> Seleccione una opción valida.";
        }
    }

    comparado = "";

    for (long unsigned int T = 0; T < users; T++){
        for (unsigned int P = 0; P < 4; P++){
            if (P == 3){
                comparado += data[T][P] + ";\n";
            }
            else{
                comparado += data[T][P] + ",";
            }
        }
    }
    usuario = "";
    for (long unsigned int L = 0; L < comparado.length(); L++){
        usuario += binario(comparado[L]);

    }
    usuario = codificador1(usuario, 3);
    documento_codificado(usuario, "Users.txt");
    }
    catch(...){
        cout << "Tenemos problemas tecnicos\n Sí este error sucedio al realizar una transación o consulta de dinere es posible que tu usuario este fuera de servicio";
    }


    return 0;
}
