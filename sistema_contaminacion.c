c: #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema_contaminacion.h"

void calcularPromedios(Zona zonas[], int num_zonas) {
    for (int i = 0; i < num_zonas; i++) {
        float suma_co2 = 0, suma_so2 = 0, suma_no2 = 0, suma_pm25 = 0;
        for (int j = 0; j < MAX_DIAS; j++) {
            suma_co2 += zonas[i].co2[j];
            suma_so2 += zonas[i].so2[j];
            suma_no2 += zonas[i].no2[j];
            suma_pm25 += zonas[i].pm25[j];
        }
        zonas[i].promedio_co2 = suma_co2 / MAX_DIAS;
        zonas[i].promedio_so2 = suma_so2 / MAX_DIAS;
        zonas[i].promedio_no2 = suma_no2 / MAX_DIAS;
        zonas[i].promedio_pm25 = suma_pm25 / MAX_DIAS;
    }
}

void predecirContaminacion(Zona zonas[], int num_zonas) {
    for (int i = 0; i < num_zonas; i++) {
        zonas[i].promedio_co2 *= 1.1; // Ejemplo: incrementar en 10%
        zonas[i].promedio_so2 *= 1.1;
        zonas[i].promedio_no2 *= 1.1;
        zonas[i].promedio_pm25 *= 1.1;
    }
}

void emitirAlertas(Zona zonas[], int num_zonas) {
    for (int i = 0; i < num_zonas; i++) {
        if (zonas[i].promedio_co2 > LIMITE_CO2 ||
            zonas[i].promedio_so2 > LIMITE_SO2 ||
            zonas[i].promedio_no2 > LIMITE_NO2 ||
            zonas[i].promedio_pm25 > LIMITE_PM25) {
            printf("Alerta en la zona %s: niveles de contaminacion exceden los limites.\n", zonas[i].nombre);
        }
    }
}

void generarRecomendaciones(Zona zonas[], int num_zonas) {
    for (int i = 0; i < num_zonas; i++) {
        if (zonas[i].promedio_pm25 > LIMITE_PM25) {
            printf("Recomendaciones para la zona %s:\n", zonas[i].nombre);
            printf("- Reducir el trafico vehicular.\n");
            printf("- Considerar el cierre temporal de industrias.\n");
            printf("- Suspender actividades al aire libre.\n");
        }
    }
}

void exportarDatos(Zona zonas[], int num_zonas, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error al abrir el archivo");
        return;
    }

    fprintf(file, "Zona,CO2 promedio,SO2 promedio,NO2 promedio,PM2.5 promedio\n");
    for (int i = 0; i < num_zonas; i++) {
        fprintf(file, "%s,%.2f,%.2f,%.2f,%.2f\n",
                zonas[i].nombre,
                zonas[i].promedio_co2,
                zonas[i].promedio_so2,
                zonas[i].promedio_no2,
                zonas[i].promedio_pm25);
    }
    fclose(file);
    printf("Datos exportados a %s\n", filename);
}

int main() {
    Zona zonas[MAX_ZONAS] = {
        {"Zona 1", {390, 395}, {15, 18}, {20, 22}, {9, 11}},
        {"Zona 2", {405, 400}, {21, 19}, {25, 24}, {11, 12}},
        {"Zona 3", {380, 390}, {18, 20}, {19, 21}, {8, 10}},
        {"Zona 4", {400, 410}, {22, 20}, {26, 23}, {12, 14}},
        {"Zona 5", {395, 398}, {20, 21}, {23, 22}, {10, 13}}
    };

    calcularPromedios(zonas, MAX_ZONAS);
    predecirContaminacion(zonas, MAX_ZONAS);
    emitirAlertas(zonas, MAX_ZONAS);
    generarRecomendaciones(zonas, MAX_ZONAS);
    exportarDatos(zonas, MAX_ZONAS, "reporte_contaminacion.csv");

    return 0;
}
