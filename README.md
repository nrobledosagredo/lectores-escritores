# Lectores y escritores

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

Este script implementa una simulación de procesos concurrentes en C, donde múltiples lectores y escritores acceden de forma controlada a un recurso compartido.

El programa permite que varios procesos lectores accedan simultáneamente al recurso compartido, mientras que los escritores requieren acceso exclusivo. La coordinación entre lectores y escritores se realiza mediante el uso de semáforos y memoria compartida, asegurando la correcta sincronización y consistencia de los datos.

## Detalles

- **Procesos involucrados:**
  - Lectores: Pueden leer el recurso al mismo tiempo.
  - Escritores: Modifican el recurso con acceso exclusivo.
- **Sincronización:** 
  - Se utilizan semáforos POSIX (`sem_open`, `sem_wait`, `sem_post`) para evitar conflictos entre procesos.
- **Memoria compartida:**
  - `dato`: Variable compartida que es leída y escrita.
  - `n_lectores`: Contador del número de lectores activos.

## Parámetros configurables

- `ITERACION`: Número de iteraciones para cada lector/escritor.
- `MAX_LECTORES`: Cantidad máxima de lectores.
- `MAX_ESCRITORES`: Cantidad máxima de escritores.

## Compilación y ejecución

1. Compila el programa:  
   ```bash
   gcc -o lectores_escritores lectores_escritores.c -lpthread
2. Ejecuta el binario generado:
   ```bash
   ./lectores_escritores
