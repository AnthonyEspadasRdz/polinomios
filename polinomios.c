#include <stdlib.h>
#include <stdio.h>

struct _Termino // Struct que almacena el coeficiente y el grado del termino
{
    int Coeficiente;
    int Exponente;
};

typedef struct _Termino TERMINO;

struct _Polinomio
{
    TERMINO* Terminos; // Arreglo dinámico para reservar los terminos del polinomio
    int Grado; // Variable para controlar los terminos de cada polinomio
};

typedef struct _Polinomio POLINOMIO;

POLINOMIO* Crear_polinomio(); // Regresa el apuntador al polinomio creado

void Imprimir_polinomio(POLINOMIO* Polinomio); // Muestra de forma gráfica el polinomio

// Reciben las direcciones de memoria de los polinomios que se van a sumar/restar
POLINOMIO* Sumar_polinomios(POLINOMIO* Polinomio_1, POLINOMIO* Polinomio_2);
POLINOMIO* Restar_polinomios(POLINOMIO* Polinomio_1, POLINOMIO* Polinomio_2);

void Liberar_polinomio(POLINOMIO* Polinomio); // Libera la memoria reservada para el polinomio

int main()
{
    int Operacion; // Variable para controlar la decicion del usuario
    POLINOMIO* Resultado = NULL; // Apuntador para el resultado
    
    printf("Quieres sumar(0) o restar(1) polinomios?  ");
    scanf("%d", &Operacion);

    printf("\nCaptura de datos del primer polinomio:\n");

    POLINOMIO* Polinomio_1 = Crear_polinomio();
    printf("\nEl primer polinomio es:\n");
    Imprimir_polinomio(Polinomio_1);

    printf("\nCaptura de datos del segundo polinomio:\n");

    POLINOMIO* Polinomio_2 = Crear_polinomio();
    printf("\nEl segundo polinomio es:\n");
    Imprimir_polinomio(Polinomio_2);

    if (Operacion == 0)
    {
        Resultado = Sumar_polinomios(Polinomio_1, Polinomio_2);
        printf("\nY su suma es:\n");
        Imprimir_polinomio(Resultado);
    }
    else
    {
        Resultado = Restar_polinomios(Polinomio_1, Polinomio_2);
        printf("\nY su resta es:\n");
        Imprimir_polinomio(Resultado);
    }
    
    Liberar_polinomio(Polinomio_1);
    Liberar_polinomio(Polinomio_2);
    Liberar_polinomio(Resultado);

    return 0;
}

POLINOMIO* Crear_polinomio()
{
    POLINOMIO* Polinomio = NULL; // Apuntador auxiliar para la funcion
    Polinomio = (POLINOMIO*) malloc(sizeof(POLINOMIO)); // Reservamos la memoria para el apuntador
    printf("De que grado sera el polinomio? ");
    scanf("%d", &Polinomio->Grado); // Capturamos el maximo grado del polinomio
    Polinomio -> Terminos = (TERMINO*) malloc((Polinomio -> Grado + 1) * sizeof(TERMINO)); // Generamos la memoria necesaria

    for (int i = Polinomio -> Grado; i >= 0; i--, Polinomio -> Terminos++) // Capturamos los coeficientes y exponentes de cada termino
    {
        if (i == 0) 
            printf("Ingresa el termino independiente: ");
        else
            printf("Ingresa el coeficiente para el exponente %d: ", i);
        
        scanf("%d", &Polinomio -> Terminos -> Coeficiente); // Se registra el coeficiente del termino
        Polinomio -> Terminos -> Exponente = i; // Se registra el exponente que representa
    }

    Polinomio -> Terminos -= Polinomio -> Grado+1; // Devolvemoss al apuntador a la posicion inicial

    return Polinomio;
}

void Imprimir_polinomio(POLINOMIO* Polinomio)
{
    int Ceros = 0; // Variable para controlar el numero de ceros en el polinomio

    for (int i = 0; i <= Polinomio -> Grado; i++, Polinomio -> Terminos++)
    {
        if (Polinomio -> Terminos -> Coeficiente == 0)
        {
            Ceros++; // Se incrementa el contador de ceros
            if (Ceros > Polinomio -> Grado) // Si todos los terminos del polinomio son ceros
                printf("0"); // Se imprime solo un cero
            continue; // Si el coeficiente es 0 no se imprime y el ciclo sigue
        }
        else if (Polinomio -> Terminos -> Exponente == 1) // Cuando se imprime un exponente 1
            if (Polinomio -> Terminos -> Coeficiente == 1) // Si el coeficiente es 1, no se muestra
                printf("+ x ");
            else if (Polinomio -> Terminos -> Coeficiente == -1) // Si es coeficiene es -1, se muestra el signo
                printf("- x ");
            else if (Polinomio -> Terminos -> Coeficiente < 0) // Para casos con coeficientes negativos
                printf("- %dx ", (-1) * Polinomio -> Terminos -> Coeficiente);
            else // Para los coeficientes positivos
                printf("+ %dx ", Polinomio -> Terminos -> Coeficiente);
        else if(i == 0) // Cuando se imprime el primer termino
            if (Polinomio -> Terminos -> Coeficiente == 1) // Si el coeficiente es 1 no es necesario escribrilo
                printf("x^%d ", Polinomio -> Terminos -> Exponente);
            else if (Polinomio -> Terminos -> Coeficiente == -1) // Si es negativo hay que expresar el signo
                printf("-x^%d ", Polinomio -> Terminos -> Exponente);
            else
                printf("%dx^%d ", Polinomio -> Terminos -> Coeficiente, Polinomio -> Terminos -> Exponente);
        else if (i == Polinomio -> Grado) // Para la impresion del termino independiente
            if (Polinomio -> Terminos -> Coeficiente < 0) // Para los casos donde es negativo
                printf("- %d", (-1) * Polinomio -> Terminos -> Coeficiente);
            else // En caso de que sea positivo
                printf("+ %d", Polinomio -> Terminos -> Coeficiente);
        else
            if (Polinomio -> Terminos -> Coeficiente < 0) // Para los terminos negativos
                if (Polinomio -> Terminos -> Coeficiente == -1) // Si el coeficiente es 1 no es necesario escribirlo
                    printf("- x^%d ", Polinomio -> Terminos -> Exponente);
                else
                    printf("- %dx^%d ", (-1) * Polinomio -> Terminos -> Coeficiente, Polinomio -> Terminos -> Exponente);
            else // Para los positivos
                if (Polinomio -> Terminos -> Coeficiente == 1) // Si el coeficiente es 1 no es necesario escribirlo
                    printf("+ x^%d ", Polinomio -> Terminos -> Exponente);
                else
                    printf("+ %dx^%d ", Polinomio -> Terminos -> Coeficiente, Polinomio -> Terminos -> Exponente);
    }

    printf("\n"); // Espacio para cuando se termina el polinomio

    Polinomio -> Terminos -= Polinomio -> Grado + 1; // Devolvemos al apuntador a su posision original
}

POLINOMIO* Sumar_polinomios(POLINOMIO* Polinomio_1, POLINOMIO* Polinomio_2)
{
    POLINOMIO* Resultado = (POLINOMIO*) malloc(sizeof(POLINOMIO)); // Reservamos memoria para el resultado
    
    // Reservamos memoria para el resultado segun el polinomio de mayor grado
    if (Polinomio_1 -> Grado >= Polinomio_2 -> Grado) // Casos donde el uno es mayor o son iguales
    {
        Resultado -> Grado = Polinomio_1 -> Grado;
        Resultado -> Terminos = (TERMINO*) malloc ((Polinomio_1 -> Grado + 1)*(sizeof(TERMINO)));

        // Realizamos las operaciones de asignacion
        for (int i = Resultado -> Grado; i >= 0; i--, Polinomio_1 -> Terminos++, Resultado -> Terminos++)
        {
            if (i > Polinomio_2 -> Grado) // Para las asignaciones de exponente donde el Polonomio 2 no tiene termino
                Resultado -> Terminos -> Coeficiente = Polinomio_1 -> Terminos -> Coeficiente;
            else 
            {
                Resultado -> Terminos -> Coeficiente = Polinomio_1 -> Terminos -> Coeficiente + Polinomio_2 -> Terminos -> Coeficiente;
                Polinomio_2 -> Terminos++;
            }

            Resultado -> Terminos ->Exponente = i;
        }
    }
    else // Casos para cuando el 2 es mayor
    {
        Resultado -> Grado = Polinomio_2 -> Grado;
        Resultado -> Terminos = (TERMINO*) malloc ((Polinomio_2 -> Grado + 1)*(sizeof(TERMINO)));

        for (int i = Resultado -> Grado; i >= 0; i--, Polinomio_2 -> Terminos++, Resultado -> Terminos++)
        {
            if (i > Polinomio_1 -> Grado) // Para las asignaciones de exponente donde el Polonomio 1 no tiene termino
                Resultado -> Terminos -> Coeficiente = Polinomio_2 -> Terminos -> Coeficiente;
            else
            {
                Resultado -> Terminos -> Coeficiente = Polinomio_2 -> Terminos -> Coeficiente + Polinomio_1 -> Terminos -> Coeficiente;
                Polinomio_1 -> Terminos++;
            }

            Resultado -> Terminos -> Exponente = i;
        }
    }

    // Devolvemos los apuntadores de cada polinomio a la posicion inicial
    Polinomio_1 -> Terminos -= Polinomio_1 -> Grado + 1;
    Polinomio_2 -> Terminos -= Polinomio_2 -> Grado + 1;
    Resultado -> Terminos -= Resultado -> Grado + 1;

    return Resultado;
}

POLINOMIO* Restar_polinomios(POLINOMIO* Polinomio_1, POLINOMIO* Polinomio_2) // El polinomio 2 siempre es el que se va a restar
{
    POLINOMIO* Resultado = (POLINOMIO*) malloc(sizeof(POLINOMIO)); // Reservamos memoria para el resultado
    
    // Reservamos memoria para el resultado segun el polinomio de mayor grado
    if (Polinomio_1 -> Grado >= Polinomio_2 -> Grado) // Casos donde el uno es mayor o son iguales
    {
        Resultado -> Grado = Polinomio_1 -> Grado;
        Resultado -> Terminos = (TERMINO*) malloc ((Polinomio_1 -> Grado + 1)*(sizeof(TERMINO)));

        // Realizamos las operaciones de asignacion
        for (int i = Resultado -> Grado; i >= 0; i--, Polinomio_1 -> Terminos++, Resultado -> Terminos++)
        {
            if (i > Polinomio_2 -> Grado) // Para las asignaciones de exponente donde el Polonomio 2 no tiene termino
                Resultado -> Terminos -> Coeficiente = Polinomio_1 -> Terminos -> Coeficiente;
            else 
            {
                Resultado -> Terminos -> Coeficiente = Polinomio_1 -> Terminos -> Coeficiente - Polinomio_2 -> Terminos -> Coeficiente;
                Polinomio_2 -> Terminos++;
            }

            Resultado -> Terminos ->Exponente = i;
        }
    }
    else // Casos para cuando el 2 es mayor
    {
        Resultado -> Grado = Polinomio_2 -> Grado;
        Resultado -> Terminos = (TERMINO*) malloc ((Polinomio_2 -> Grado + 1)*(sizeof(TERMINO)));

        for (int i = Resultado -> Grado; i >= 0; i--, Polinomio_2 -> Terminos++, Resultado -> Terminos++)
        {
            if (i > Polinomio_1 -> Grado) // Para las asignaciones de exponente donde el Polonomio 1 no tiene termino
                Resultado -> Terminos -> Coeficiente = (-1) * Polinomio_2 -> Terminos -> Coeficiente; // Se invierte su valor al ser una resta
            else
            {
                Resultado -> Terminos -> Coeficiente = Polinomio_1 -> Terminos -> Coeficiente - Polinomio_2 -> Terminos -> Coeficiente;
                Polinomio_1 -> Terminos++;
            }

            Resultado -> Terminos -> Exponente = i;
        }
    }

    // Devolvemos los apuntadores de cada polinomio a la posicion inicial
    Polinomio_1 -> Terminos -= Polinomio_1 -> Grado + 1;
    Polinomio_2 -> Terminos -= Polinomio_2 -> Grado + 1;
    Resultado -> Terminos -= Resultado -> Grado + 1;

    return Resultado;
}

void Liberar_polinomio(POLINOMIO* Polinomio)
{
    free(Polinomio -> Terminos); // Liberamos el espacio de los terminos
    free(Polinomio); // Liberamos el espacio del polinomio
}