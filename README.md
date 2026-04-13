# Sistema de Liga de Fútbol

## Autor
Juan  Andres Perez Rojas

## Descripción
Aplicación en C++ que permite gestionar una liga de fútbol desde consola.  
El programa permite registrar partidos, calcular la tabla de posiciones, manejar jornadas y consultar historial de enfrentamientos entre equipos.

## Funcionalidades
- Registro de resultados de partidos
- Cálculo automático de la tabla de posiciones
- Ordenamiento por puntos, diferencia de goles y goles a favor
- Visualización de jornadas
- Consulta de partidos jugados
- Historial de enfrentamientos entre equipos
- Exportación de la tabla a archivo
- Validación de datos de entrada

## Archivos del sistema

### config.txt
Contiene la configuración de la liga:

nombreLiga=La Liga  
puntosGanar=3  
puntosEmpate=1  
puntosPerder=0  
equipo=Real Madrid  
equipo=Barcelona  

### partidos.txt
Contiene los partidos jugados:

Real Madrid,Barcelona,2,1  

### fechas.txt
Contiene las jornadas registradas:

JORNADA=1  
Real Madrid,Barcelona,2,1  
FIN_JORNADA  

### tabla.txt
Archivo generado automáticamente con la tabla de posiciones.

## Decisiones de diseño
- Uso de struct para representar equipos
- Uso de vector para almacenamiento dinámico
- Uso de archivos para persistencia de datos
- Uso de funciones para modularizar el código
- Uso de punteros para actualizar estadísticas
- Uso de sort para ordenar la tabla

## Compilación
g++ src/main.cpp -o programa

## Ejecución
 en powershell:./programa
 en cmd :programa
