#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

int main(){

    ifstream binFile("ethernet_1.bin", ios::binary);

    if(!binFile){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    cout << setw(50) << "ANALISIS DE TRAMA ETHERNET" << endl << endl;

    binFile.seekg(0, ios::end);
    int size = binFile.tellg();

    binFile.seekg(0, ios::beg);

    char buffer[size];

    binFile.read(buffer, size);

    cout << "MAC Destino: ";
    for(int i = 0; i < 6; i++){
        printf("%02x:", (unsigned char)buffer[i]);
    }
    cout << endl;

    cout << "MAC Origen: ";
    for(int i = 6; i < 12; i++){
        printf("%02x:", (unsigned char)buffer[i]);
    }
    cout << endl;

    int tipo;
    for(int i = 12; i < 14; i++){
        tipo = (unsigned char)buffer[i];
    }

    switch (tipo){
        case 0:
            cout << "Tipo: IPv4" << endl;
            break;
        case 6:
            cout << "Tipo: ARP" << endl;
            break;
        case 53:
            cout << "Tipo: RARP" << endl;
            break;
        case 221:
            cout << "Tipo: IPv6" << endl;
            break;
        default:
            cout << "Tipo: Desconocido" << endl;
            break;        
    }

    cout << "Datos: ";
    for(int i = 14; i < size; i++){
        printf("%02x:", (unsigned char)buffer[i]);
    }
    cout << endl;

    binFile.close();
    return 0;
}