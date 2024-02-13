#!/bin/bash

allowed_functions=(
memset printf malloc free write fork kill
exit pthread_create pthread_detach pthread_join
usleep gettimeofday waitpid sem_open sem_close
sem_post sem_wait sem_unlink
)

found_prohibited=0
# Ejecutar nm y filtrar por símbolos indefinidos
nm philo_bonus | grep ' U ' | while read -r line; do
    # Extraer el nombre de la función removiendo el prefijo "_"
    func=$(echo "$line" | awk '{print $2}' | sed 's/^_//')

    # Verificar si la función está en la lista de permitidas
    if ! printf '%s\n' "${allowed_functions[@]}" | grep -qx "$func"; then
        # Si la función no está permitida buscar su ocurrencia en los archivos fuente
        echo "Función no permitida encontrada: $func"
        grep -rnw './src' -e "$func"
		found_prohibited=1
    fi
done
if [ "$found_prohibited" -eq 0 ]; then
    echo "Programa libre de funciones prohibidas."
fi
