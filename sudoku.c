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
    int sesion;
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
//Esta funcion quita el \n que deja la funcion fgets al leer desde el teclado(Es exclusiva de crearCuenta)
struct Jugador _quitarDn();
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
    //Variable para guardar la opcion del jugador
    int opcion;

    //Estructra para guardar los datos del jugador
    struct Jugador Jugador;
    Jugador.sesion = 0; //Variable que nos dice si el juagdor inicio sesion
    

    //Mientras no se haya iniciado sesion
    while(Jugador.sesion == 0){
        opcion = sesionMenu();

        switch(opcion){
        case 1:             //Corresponde a Iniciar sesion
            //Jugador = iniciarSesion();
            break;
        case 2:             //Corresponde a Crear cuenta
            crearCuenta();
            break;
        }
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
int sesionMenu(){
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

    return opcion.posicion;
}

void crearCuenta(){
    //Contador para los for
    int i;
    //Estructura para guardar los datos del jugador
    struct Jugador Nuevo;
    //Inicializamos su puntaje del nuevo juagdor en 0
    Nuevo.puntaje = 0;
    //input para confirmar
    char confirmar;

    //variable para confirmar si el usuario ingreso los datos correctamente
    int datosOK = 0;

    //Abrimos el archivo de usuarios en "a" para agregar
    FILE * users = fopen(".usuarios.txt", "a");

    //Comprobamos si el archivo se abrio correctamente
    if(users == NULL){
        printf("\nHubo un error ):");
        printf("\n\t ENTER para continuar");
        confirmar = getch();
        
        //Se sale del programa
        exit (-1);
    }else{
        //Mientras los datos no se hayan ingresado correctamente
        while(datosOK == 0){
            fflush(stdin);
            printf("\tIngresa tus datos:\n\n");


            printf("\tNombre: ");
            fgets(Nuevo.nombre, 10, stdin);
            fflush(stdin);

            printf("\tUsuario: ");
            fgets(Nuevo.usuario, 10, stdin);
            fflush(stdin);

            printf("\tContrase%ca: ", 164);
            fgets(Nuevo.contrasena, 10, stdin);
            fflush(stdin);

            //Comprueba si el jugador dejo un espacio vacio
            if(Nuevo.nombre[0] != '\n' && Nuevo.usuario[0] != '\n' && Nuevo.contrasena[0] != '\n'){
                datosOK = 1;
            }else{
                printf("\n\tERROR: Dejaste algun espacio vacio\n");
            }
        }
        //Quitar los \n
        Nuevo = _quitarDn(Nuevo);

        //Animacion para procesar
        limpiarPantalla();
        //254
        printf("\n\t\tProcesando...\n\t\t");
        //Escrbir en el archivo
        fprintf(users, "%s %s %s %d \n", Nuevo.nombre, Nuevo.usuario, Nuevo.contrasena, Nuevo.puntaje);

        for(i=0; i<13; i++){
            printf("%c",254);
            Sleep(20);
        }   
        printf("\n\n");

        printf("\t\t Listo!\n\t Cuenta creada exitosamente.");

        //Cerrar el archivo
        fclose(users);

        printf("\n\n\t ENTER para continuar");
        confirmar = getch();

        limpiarPantalla();
    }
}

struct Jugador _quitarDn(struct Jugador Nuevo){
    int i;

    //Quita el \n en el nombre
    for(i=0; i<10; i++){
        if(Nuevo.nombre[i] == '\n'){
            Nuevo.nombre[i] = NULL;
        }
    }

    //Quita el \n en el usuario
    for(i=0; i<10; i++){
        if(Nuevo.usuario[i] == '\n'){
            Nuevo.usuario[i] = NULL;
        }
    }
    
    //Quita el \n en la contrasena
    for(i=0; i<10; i++){
        if(Nuevo.contrasena[i] == '\n'){
            Nuevo.contrasena[i] = NULL;
        }
    }

    return Nuevo;
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
