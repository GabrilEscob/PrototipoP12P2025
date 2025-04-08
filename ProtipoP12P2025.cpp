#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NUM_INDUSTRIAS = 3;
const int NUM_EMPRESAS = 5;
const int NUM_ANIOS = 4;
const double VENTA_MIN = 950000.0;
const double VENTA_MAX = 1000000.0;

// Lista de nombres base para las empresas
string nombresBase[] = {
    "LogiCorp", "TechNova", "AgriFoods", "TransExpress", "DataLink",
    "GreenMove", "ByteForce", "EcoFoods", "UrbanDrive", "CloudMax",
    "FastFleet", "AgroPlus", "SmartTrans", "NetWorld", "FreshLine"
};

struct Empresa {
    string nombre;
    double ventas[NUM_ANIOS];
    double promedio = 0;
    string industria;
};

struct Industria {
    string nombre;
    Empresa empresas[NUM_EMPRESAS];
    double promedio = 0;
};

double generarVentaAleatoria() {
    return VENTA_MIN + (rand() % int(VENTA_MAX - VENTA_MIN + 1));
}

int main() {
    srand(time(0));
    int nombreIndex = 0;

    Industria industrias[NUM_INDUSTRIAS] = {
        {"Transportistas"},
        {"Tecnología"},
        {"Alimentos"}
    };

    Empresa* empresaTop = nullptr;

    // Llenar datos con nombres random
    for (int i = 0; i < NUM_INDUSTRIAS; i++) {
        double sumaIndustria = 0;
        for (int j = 0; j < NUM_EMPRESAS; j++) {
            Empresa& e = industrias[i].empresas[j];
            e.nombre = nombresBase[nombreIndex++ % (sizeof(nombresBase) / sizeof(string))] + "_" + to_string(j + 1);
            e.industria = industrias[i].nombre;

            double sumaEmpresa = 0;
            for (int k = 0; k < NUM_ANIOS; k++) {
                e.ventas[k] = generarVentaAleatoria();
                sumaEmpresa += e.ventas[k];
            }
            e.promedio = sumaEmpresa / NUM_ANIOS;
            sumaIndustria += e.promedio;

            if (!empresaTop || e.promedio > empresaTop->promedio) {
                empresaTop = &e;
            }
        }
        industrias[i].promedio = sumaIndustria / NUM_EMPRESAS;
    }

    // Mostrar resultados
    cout << fixed << setprecision(2);
    for (int i = 0; i < NUM_INDUSTRIAS; i++) {
        cout << "\nIndustria: " << industrias[i].nombre << endl;
        for (int j = 0; j < NUM_EMPRESAS; j++) {
            Empresa& e = industrias[i].empresas[j];
            cout << "  " << e.nombre << " - Promedio ventas: $" << e.promedio << endl;
        }
        cout << ">> Promedio de la industria: $" << industrias[i].promedio << endl;
    }

    // Empresa con mayor promedio
    if (empresaTop) {
        cout << "\nEMPRESA CON MAYOR PROMEDIO: " << empresaTop->nombre
             << " (Industria: " << empresaTop->industria << ")"
             << " - $" << empresaTop->promedio << endl;
    }

    return 0;
}
