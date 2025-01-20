#ifndef SISTEMA_CONTAMINACION_H
#define SISTEMA_CONTAMINACION_H

#define MAX_ZONAS 5
#define MAX_DIAS 30
#define LIMITE_CO2 400    // Límite de CO2 (ppm)
#define LIMITE_SO2 20     // Límite de SO2 (ppm)
#define LIMITE_NO2 25     // Límite de NO2 (ppm)
#define LIMITE_PM25 10    // Límite de PM2.5 (µg/m³)

typedef struct {
    char nombre[50];
    float co2[MAX_DIAS];
    float so2[MAX_DIAS];
    float no2[MAX_DIAS];
    float pm25[MAX_DIAS];
    float promedio_co2;
    float promedio_so2;
    float promedio_no2;
    float promedio_pm25;
} Zona;

void calcularPromedios(Zona zonas[], int num_zonas);
void predecirContaminacion(Zona zonas[], int num_zonas);
void emitirAlertas(Zona zonas[], int num_zonas);
void generarRecomendaciones(Zona zonas[], int num_zonas);
void exportarDatos(Zona zonas[], int num_zonas, const char *filename);

#endif
