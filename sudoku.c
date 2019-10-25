#include <stdio.h>
#include <windows.h>

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
    int puntaje;
};

//Esta estructura es para guardar el estado de los menus
struct Menu{
    int posicion;   //Guarda la posicion del jugador en el menu
    int enter;
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

//Captura el input del usuario y regresa una opcion
struct Menu mover(int posicion, int inicio, int final);


//Limpia la consola
void limpiarPantalla();
//Imprime el titulo del juego "Sudoku"
void imprimirTitulo(); 



/*-------------------------------------------Funcion main-------------------------------------------------------------*/
int main(){
    //Variable para saber si el jugador ya inicio sesion
    int sesion = 0;
    //Variable para guardar la opcion del jugador
    int opcion;

    //Mientras no se haya iniciado sesion
    while(sesion == 0){
        sesion = sesionMenu();

        crearCuenta();
    }


    opcion = opcionJuego();
    
    //Opcion seleccionada por el jugador
    switch (opcion){
        case 1: //Corresponde a jugar
            printf("\t1   >Jugar      Puntajes      Iniciar sesion\n");
            break;
        case 2: //Corresponde a ver los puntajes
            printf("\t2    Jugar     >Puntajes      Iniciar sesion\n");
            break;
        case 3: //Corresponde a ver las instrucciones
            printf("\t3    Jugar      Puntajes     >Iniciar sesion\n");
            break;
    }
    
    return 0;
}
/*---------------------------------------------------------------------------------------------------------------------*/

//Funciones para los menus
int opcionJuego(){
    /*
    Estructura para saber el estado en que posicion  del menu esta el jugador y para saber si selecciono una opcion.
    El enter se iguala a 0 para entrar en el while y elegir una opcion.
    La poscicion se iguala a 1 para iniciar en la primera opcion del menu.
    */
    struct Menu opcion;
    opcion.enter = 0;
    opcion.posicion = 1;

    //while para elegir la opcion
    while(opcion.enter == 0){
        imprimirTitulo();        

        //Imprimir opciones
        switch(opcion.posicion){
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

        //Se le pasa como paramtros la posicion actual, el inicio y el final del menu
        opcion = mover(opcion.posicion, 1, 3);

        limpiarPantalla();
    }

    //regresa la opcion del jugador
    return opcion.posicion;
}

int sesionMenu(){
    int sesion = 0;

    /*
    Estructura para saber el estado en que posicion  del menu esta el jugador y para saber si selecciono una opcion.
    El enter se iguala a 0 para entrar en el while y elegir una opcion.
    La poscicion se iguala a 1 para iniciar en la primera opcion del menu.
    */
    struct Menu opcion;
    opcion.enter = 0;
    opcion.posicion = 1;

    while(opcion.enter == 0){
        imprimirTitulo();
        //Opcion seleccionada por el jugador
        switch (opcion.posicion){
            case 1: //Corresponde iniciar sesion
                printf("\t\t>Iniciar Sesion      Crear cuenta\n");
                break;
            case 2: //Corresponde a crear una cuenta
                printf("\t\t Iniciar Sesion     >Crear cuenta\n");
                break;
        }

        opcion = mover(opcion.posicion, 1, 2);
        limpiarPantalla();
    }
    
    sesion = 1;

    return sesion;
}

struct Menu mover(int posicion, int inicio, int final){
    //Es lo que teclea el usuario
    char input;

    //Estrcura que contiene la posicion y el estado del enter
    struct Menu estado;
    estado.posicion = posicion;
    estado.enter = 0;

    
    //Espera el input del jugador
    input = getch();

    //Acciones para el input del jugador
    //Los if se usan para darle continuidad a las flechitas
    switch(input){
    case IZQUIERDA:
        estado.posicion--;        //La flechita se mueve a la izquierda
        if(estado.posicion < inicio){  //Si ya no puede moverse a la izquierda se va al fnial
            estado.posicion = final;
        }
        break;
    case DERECHA:
        estado.posicion++;        //La flechita se mueve a la derecha
        if(estado.posicion > final){  //Si ya no puede moverse a la izquierda se va al inicio
            estado.posicion = inicio;
        }
        break;

    case ENTER:
        estado.enter = 1;
        break;
    }

    return estado;
}

//Funciones para la sesion
void crearCuenta(){
    int i;
    //Estructura para guardar los datos del jugador
    struct Jugador Nuevo;

    //input para confirmar
    char confirmar;

    printf("\t\tHola bienvenido a Sudoku\n\n");
    printf("\tIngresa tus datos:\n\n");
    printf("\tNombre: ");
    gets(Nuevo.nombre);
    printf("\tUsuario: ");
    gets(Nuevo.usuario);
    printf("\tContrase%ca: ", 164);
    gets(Nuevo.contrasena);

    //Animacion para procesar
    limpiarPantalla();
    //254
    printf("\n\t\tProcesando...\n\t\t");
    for(i=0; i<13; i++){
        printf("%c",254);
        Sleep(50);
    }   
    printf("\n\n");

    printf("\t\tListo!\n\tCuenta creada exitosamente.");

    printf("\n\n\tENTER para continuar");
    confirmar = getch();

    limpiarPantalla();
}

//Funciones para imprimir
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
