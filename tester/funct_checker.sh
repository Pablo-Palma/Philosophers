#!/bin/bash

allowed_functions=(
memset printf malloc free write
usleep gettimeofday pthread_create
pthread_detach pthread_join pthread_mutex_init
pthread_mutex_destroy pthread_mutex_lock pthread_mutex_unlock
)

# Ejecutar nm y filtrar por símbolos indefinidos
nm philo | grep ' U ' | while read -r line; do
    # Extraer el nombre de la función removiendo el prefijo "_"
    func=$(echo "$line" | awk '{print $2}' | sed 's/^_//')

    # Verificar si la función está en la lista de permitidas
    if ! printf '%s\n' "${allowed_functions[@]}" | grep -qx "$func"; then
        # Si la función no está permitida buscar su ocurrencia en los archivos fuente
        echo "Función no permitida encontrada: $func"
        grep -rnw './src' -e "$func"
    fi
done
