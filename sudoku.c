#include <stdio.h>

//Definir teclas para jugar
#define ENTER 13
#define IZQUIERDA 75
#define DERECHA 77
#define ARRIBA 72
#define ABAJO 80

/*Funciones*/

//Imprime el menu de inicio y devuelve el input del jugador
int menu();            

//Limpia la consola
void limpiarPantalla(); 

int main(){
    int opcion; //Variable para guardar la opcion del jugador

    opcion = menu();
    printf("\n\nSalio :000  %d\n", opcion);
    
    return 0;
}

int menu(){
    //Variable para guardar la posición del menu
    int mover = 1;

    //Variable para saber si el jugador selecciono una opcion
    /*
    Se inicializa en 0 para que el jugador entre dentro del while
    y pueda seleccionar una opcion.
    */
    int enter = 0;

    //Variable para almacenar la opcion del jugador
    char opcion;

    //while para elegir la opcion
    while(enter == 0){

        //imprime un menu con ascii art
        printf("\t __           _       _       \n");   
        printf("\t/ _\\_   _  __| | ___ | | ___   _ \n");
        printf("\t\\ \\| | | |/ _` |/ _ \\| |/ / | | |\n");
        printf("\t_\\ \\ |_| | (_| | (_) |   <| |_| |\n");
        printf("\t\\__/\\__,_|\\__,_|\\___/|_|\\_\\__,_|\n\n");

        //Imprimir opciones
        switch(mover){
            case 1:
                printf("\t>Jugar      Puntajes      Iniciar sesion\n");
                break;
            case 2:
                printf("\t Jugar     >Puntajes      Iniciar sesion\n");
                break;
            case 3:
                printf("\t Jugar      Puntajes     >Iniciar sesion\n");
                break;
        }

        //Espera el input del jugador
        opcion = getch();

        //Acciones para el input del jugador
        switch (opcion){
        case IZQUIERDA:
            mover--;        //La flechita se mueve a la izquierda
            if(mover < 1){  //Si ya no puede moverse a la izquierda se va al 3
                mover = 3;
            }
            break;
        case DERECHA:
            mover++;        //La flechita se mueve a la derecha
            if(mover > 3){  //Si ya no puede moverse a la izquierda se va al 1
                mover = 1;
            }
            break;
        case ENTER:
            //Termina el menu y la funcion esta lista para retornar la opcion del usuario
            enter = 1;
            break;
        }

        limpiarPantalla();
    }

    //regresa la opcion del jugador
    return mover;
}

void limpiarPantalla(){
    system("CLS");
}
