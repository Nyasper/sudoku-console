#include <stdio.h>

//Definir teclas para jugar
#define ENTER 13
#define IZQUIERDA 75
#define DERECHA 77
#define ARRIBA 72
#define ABAJO 80

/*Estructuras*/
struct Jugador{
    char nombre[10];
    char usuario[10];
    char contrasena[10];
};

/*Funciones*/

//Imprime un menu y regresa la opcion del jugador
int opcionJuego();            

//Imprime el menu para que el jugador inicie sesion o cree una cuenta
int sesionMenu();
//Menu para crear una cuenta
void crearCuenta();
//Menu para iniciar sesion
struct Jugador iniciarSesion();

//Limpia la consola
void limpiarPantalla();
//Imprime el titulo del juego "Sudoku"
void imprimirTitulo(); 



/*-------------------------------------------Funcion main-------------------------------------------------------------*/
int main(){
    //Variable para saber si el jugador ya inicio sesion
    int sesion = 0;

    int opcion; //Variable para guardar la opcion del jugador

    opcion = opcionJuego();
    
    //Opcion seleccionada por el jugador
    switch (opcion){
        case 1: //Corresponde a jugar
            printf("\t   >Jugar      Puntajes      Iniciar sesion\n");
            break;
        case 2: //Corresponde a ver los puntajes
            printf("\t    Jugar     >Puntajes      Iniciar sesion\n");
            break;
        case 3: //Corresponde a ver las instrucciones
            printf("\t    Jugar      Puntajes     >Iniciar sesion\n");
            break;
    }
    
    return 0;
}
/*---------------------------------------------------------------------------------------------------------------------*/

int opcionJuego(){
    /*
    Variable para guardar la posición del menu.
    Esta tambien es igual a la opcion del jugador.
    */
    int mover = 1;

    
    /*
    Variable para saber si el jugador selecciono una opcion.
    Se inicializa en 0 para que el jugador entre dentro del while
    y pueda seleccionar una opcion.
    */
    int enter = 0;

    char input; //Variable para almacenar la opcion del jugador

    //while para elegir la opcion
    while(enter == 0){
        imprimirTitulo();        

        //Imprimir opciones
        switch(mover){
            case 1:
                printf("\t     >Jugar      Puntajes      %cC%cmo jugar?\n",168,162);
                break;
            case 2:
                printf("\t      Jugar     >Puntajes      %cC%cmo jugar?\n",168,162);
                break;
            case 3:
                printf("\t      Jugar      Puntajes     >%cC%cmo jugar?\n",168,162);
                break;
        }

        //Espera el input del jugador
        input = getch();

        //Acciones para el input del jugador
        switch(input){
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

void imprimirTitulo(){
    //imprime el titulo del juego con ascii art
    printf("\t\t __           _       _       \n");   
    printf("\t\t/ _\\_   _  __| | ___ | | ___   _ \n");
    printf("\t\t\\ \\| | | |/ _` |/ _ \\| |/ / | | |\n");
    printf("\t\t_\\ \\ |_| | (_| | (_) |   <| |_| |\n");
    printf("\t\t\\__/\\__,_|\\__,_|\\___/|_|\\_\\__,_|\n\n");
}
