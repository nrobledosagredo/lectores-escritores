# Lectores y escritores

![C](https://img.shields.io/badge/language-C-blue)
![POSIX Semaphores](https://img.shields.io/badge/sync-POSIX--Semaphores-green)
![Shared Memory](https://img.shields.io/badge/memory-Shared-yellow)
![Concurrency](https://img.shields.io/badge/topic-Concurrency-orange)

Este script implementa una simulación de procesos concurrentes en C, donde múltiples lectores y escritores acceden de forma controlada a un recurso compartido.

## Descripción

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

## Ejecución

Compila el código con el siguiente comando:

```bash
gcc -o lectores_escritores lectores_escritores.c -lpthread
