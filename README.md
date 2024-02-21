# Proyecto Philosophers

## Resumen

El problema de la cena de los filósofos es un dilema clásico de las ciencias de la computación que representa la sincronización de procesos en un sistema operativo. Inspirado en pensadores que utilizan palillos para comer, este proyecto modela un sistema donde la cooperación y competencia por recursos compartidos deben ser cuidadosamente balanceadas.

## Características

- **Concurrencia:** Ejecución en paralelo de procesos filosóficos como hilos.
- **Sincronización:** Control meticuloso de los recursos mediante mutex para evitar condiciones de carrera.
- **Rendimiento:** Tiempos de ejecución reales que influyen directamente en el resultado de la simulación.

## Compilación y Ejecución

Para compilar el proyecto, utiliza:

```
PPR$ make
Philosophers compiled successfully!
```

Para ejecutar la simulación:

```
PPR$ ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

## Bonus

En la parte bonus del proyecto Philosophers, el enfoque se desplaza de los hilos y mutex a los procesos y semáforos, ofreciendo una dimensión adicional de complejidad y realismo al problema de la sincronización:

- **Procesos:** Cada filósofo es representado por un proceso independiente, en lugar de un hilo, para imitar de manera más realista entidades separadas que compiten por recursos limitados.
- **Semaforos:** Los tenedores, que ahora son recursos limitados, están representados por semáforos en lugar de mutex. Esto significa que un semáforo gestiona la disponibilidad de los tenedores, lo que permite que solo un número limitado de filósofos acceda a ellos al mismo tiempo.
- **Independencia del proceso principal:** A diferencia de los hilos, los procesos tienen su propia memoria y estado, y el proceso principal actúa como coordinador en lugar de participar directamente en la simulación.
