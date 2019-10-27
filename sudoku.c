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
    int puntaje;
    int sesion;
};

//Esta estructura es para guardar el estado de los menus
struct Menu{
    //Guarda la posicion del jugador en el menu
    int posicion;   
    //Es para saber si el jugador selecciono una opcion
    int enter;
};

/*Funciones de menus, impresion y sistema de usuarios*/

//Imprime un menu y regresa la opcion del jugador
int juegoMenu(char nombre[10]);            

//Imprime el menu para que el jugador inicie sesion o cree una cuenta
int sesionMenu();
//Menu para crear una cuenta
void crearCuenta();
//Esta funcion quita el \n que deja la funcion fgets al leer desde el teclado
struct Jugador _quitarDn();
//Menu para iniciar sesion
struct Jugador iniciarSesion();
//Funcion para los errores del sistema de usuarios
void _errorSistemaDeUsuarios();

//Captura el input del usuario y regresa una opcion
struct Menu mover(int posicion, int inicio, int final);

//Limpia la consola
void limpiarPantalla();
//Imprime el titulo del juego "Sudoku"
void imprimirTitulo(); 

/*Funciones y estructuras de la logica del juego sudoku*/

//Funcion que inicia el juego (void temporal)
void jugarSudoku();

//Estructura para almacenar coordenadas del tablero de juego
struct XY_tablero{
    int x;
    int y;
    int enter;
};

//Estructura para almacenar las propiedades de cada casilla
struct Casilla{
    //Almacena un valor numerico en forma de caracter del 1 al 9 de la casilla para jugar
    char valor;
    //Variable binaria que nos dice si la casilla se puede modificar 0=NO 1=SI
    int modificable;
    //Cadena de caracteres que se va a imprimir en pantalla
    char imprimir;
    //coordenadas
    int x;
    int y;
};

//funcion que permite identicar las flechas del teclado para moverse entre las casillas del tablero
struct XY_tablero moverse_en_tablero(struct XY_tablero posicion);

//Pide un numero para llenar la casilla seleccionada
char llenarCasilla();

//Estructura para almacenar las casillas del juego
struct Tablero{
    //Guarda la imformacion de las 81 casillas
    struct Casilla xy[9][9];
};

//Crea las 81 casillas
struct Tablero crearCasillas();


/*-------------------------------------------Funcion main-------------------------------------------------------------*/
int main(){
    //Variable para guardar la opcion del jugador
    int opcion;

    //Estructra para guardar los datos del jugador
    struct Jugador Jugador;
    Jugador.sesion = 0; //Variable que nos dice si el juagdor inicio sesion

    //Variable para inicializar el juego
    int juego = 1;
    
    while(juego == 1){
        //Mientras no se haya iniciado sesion y el juego siga activo
        while(Jugador.sesion == 0 && juego == 1){
            opcion = sesionMenu();

            switch(opcion){
            case 1:             //Corresponde a Iniciar sesion
                Jugador = iniciarSesion();
                break;
            case 2:             //Corresponde a Crear cuenta
                crearCuenta();
                break;
            case 3:             //Corresponde a salir
                //Termina el juego y sale
                juego = 0;
                break;
            }
        }
        //Si el jugador inicio sesion y si el juego sigue activo
        if(Jugador.sesion == 1 && juego == 1){
            opcion = juegoMenu(Jugador.nombre);
        
            //Opcion seleccionada por el jugador
            switch (opcion){
                case 1: //Corresponde a jugar
                    jugarSudoku();
                    break;
                case 2: //Corresponde a ver los puntajes
                    printf("\tLista de puntajes\n");
                    break;
                case 3: //Corresponde a ver las instrucciones
                    printf("\tInstrucciones\n");
                    break;
                case 4: //Corresponde a ver las instrucciones
                    printf("\tSesion cerrada\n");
                    //Cierra la sesion del jugador
                    Jugador.sesion = 0;
                    break;
            }
        }
    }
    
    return 0;
}
/*---------------------------------------------------------------------------------------------------------------------*/

/*Funciones para los menus*/
int juegoMenu(char nombre[10]){
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
        printf("\n\tJugador: %s\n", nombre);
        imprimirTitulo();        

        //Imprimir opciones
        switch(opcion.posicion){
            case 1:
                printf("\t>Jugar    Puntajes    %cC%cmo jugar?    Cerrar sesion\n",168,162);
                break;
            case 2:
                printf("\t Jugar   >Puntajes    %cC%cmo jugar?    Cerrar sesion\n",168,162);
                break;
            case 3:
                printf("\t Jugar    Puntajes   >%cC%cmo jugar?    Cerrar sesion\n",168,162);
                break;
            case 4:
                printf("\t Jugar    Puntajes    %cC%cmo jugar?   >Cerrar sesion\n",168,162);
                break;
        }

        //Se le pasa como paramtros la posicion actual, el inicio y el final del menu
        opcion = mover(opcion.posicion, 1, 4);

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


/*Funciones para la sesion*/
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
                printf("\t  >Iniciar Sesion      Crear cuenta      Salir\n");
                break;
            case 2: //Corresponde a crear una cuenta
                printf("\t   Iniciar Sesion     >Crear cuenta      Salir\n");
                break;
            case 3: //Corresponde a salir
                printf("\t   Iniciar Sesion      Crear cuenta     >Salir\n");
                break;
        }

        opcion = mover(opcion.posicion, 1, 3);
        limpiarPantalla();
    }

    return opcion.posicion;
}

struct Jugador iniciarSesion(){
    //Estructura que va a almacenar al jugador
    struct Jugador Jugador;

    //Estructura que va a almacenar los datos que ingrese el usuario para iniciar sesion
    struct Jugador Login;

    //Variable para abrir el archhivo de usuarios en modo lectura
    FILE * usuarios = fopen(".usuarios.txt", "r");

    //Comprobar si el archivo se abrio correctamente
    if(usuarios == NULL){
        _errorSistemaDeUsuarios();
    }else{
        //Variable para saber si el juagdor quiere poner de nuevo el usuario y contrasena
        int deNuevo = 1;

        while(deNuevo == 1){
            limpiarPantalla();
            printf("\n\t\tIniciar sesion\n\n");

            //Ingresa datos del usuario y limpia el buffer con fflush
            fflush(stdin);
            printf("\tUsuario: ");
            fgets(Login.usuario, 10, stdin);
            fflush(stdin);

            printf("\tContrase%ca: ", 164);
            fgets(Login.contrasena, 10, stdin);
            fflush(stdin);

            //Quitar los \n
            Login = _quitarDn(Login);

            //Variable para saber si los usuarios coninciden
            int encontrado = 0;
            //while para iterar entre todos los usuarios de la base de datos para saber si alguno conincide
            while(feof(usuarios) == 0 && encontrado == 0){
                fscanf(usuarios, "%s %s %s %d %d", Jugador.nombre, Jugador.usuario, Jugador.contrasena, &Jugador.puntaje, &Jugador.sesion);

                //Si el usuario y contrasena coincide con alguno de la base de datos .txt
                if(strcmp(Jugador.usuario, Login.usuario) == 0 && strcmp(Jugador.contrasena, Login.contrasena) == 0){
                    //El usuario ha iniciado sesion
                    Jugador.sesion = 1;
                    encontrado = 1;
                    deNuevo = 0;
                }
            }
            
            //Si el jugador inicio sesion
            if(Jugador.sesion == 1){
                limpiarPantalla();
                printf("\n\tHola %s Bienvenido a Sudoku\n", Jugador.nombre);
                printf("\n\n\t Pulsa ENTER para empezar!");
                char enter;
                enter = getch();
                limpiarPantalla();
            }else{
                //Estructura para moverse en el menu de usuario y contrasena incorrecto
                struct Menu opcion;
                opcion.posicion = 1;
                opcion.enter = 0;

                //Menu para intentar otra vez o regresar al menu de inicio
                while(opcion.enter == 0){
                    limpiarPantalla();
                    printf("\n\n\tUsuario o contrase%ca incorrecto.\n", 164);
                    switch (opcion.posicion){
                    case 1:
                        printf("\n  >Intentar de nuevo    Regresar");
                        break;
                    
                    case 2:
                        printf("\n   Intentar de nuevo   >Regresar");
                        break;
                    }
                    opcion = mover(opcion.posicion, 1, 2);
                }   
            }
        }////fin while
	}

    return Jugador;
}

void crearCuenta(){
    //Contador para los for
    int i;
    //Estructura para guardar los datos del jugador
    struct Jugador Nuevo;
    //Inicializamos su puntaje del nuevo juagdor en 0
    Nuevo.puntaje = 0;
    //Dejamos su sesion del nuevo jugador cerrada
    Nuevo.sesion = 0;
    //input para confirmar
    char confirmar;

    //variable para confirmar si el usuario ingreso los datos correctamente
    int datosOK = 0;

    //Abrimos el archivo de usuarios en "a" para agregar
    FILE * users = fopen(".usuarios.txt", "a");

    //Comprobamos si el archivo se abrio correctamente
    if(users == NULL){
        _errorSistemaDeUsuarios();
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
        fprintf(users, "%s %s %s %d %d\n", Nuevo.nombre, Nuevo.usuario, Nuevo.contrasena, Nuevo.puntaje, Nuevo.sesion);

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

void _errorSistemaDeUsuarios(){
    //input para confirmar
    char confirmar;

    printf("\nERROR: No se pudo acceder a al sistema de usuarios");
    printf("\n\t ENTER para continuar");
    confirmar = getch();
        
    //Se sale del programa
     exit (-1);
}

/*Funciones para imprimir*/
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


/*Funciones para la logica del juego*/

void jugarSudoku(){
    //Estructura que almacena la posicion del jugador en el tablero del suidoku (x, y)
    struct XY_tablero posicionJugador;
    //Se inicializan la posicion del jugador en (0, 0) y con enter = 0
    posicionJugador.x = 0;
    posicionJugador.y = 0;
    posicionJugador.enter = 0;

    //Se crea el tablero
    struct Tablero TABLERO;

    //Se crea el tablero
    TABLERO = crearCasillas();

    //Variable para saber si el jugador continua jugando
    int juego = 1;

    //Contadores para el for
    int x, y;

    //Variable donde se almacena el numero que va a poner el jugador
    int n;

    //Mientras quiera continuar con el juego
    while(juego == 1){
        printf("\n\n\t\t\tSudoku\n\n\t");
        //Imprimir tablero
        //for para iterar en las coordenadas x, y
        for(y=0; y<9; y++){
            for(x=0; x<9; x++){
                if(x == posicionJugador.x && y == posicionJugador.y){
                    //Imprime el caracter correspondiente a la coordenada x, y
                    printf(" %c %c", 254, TABLERO.xy[x][y].imprimir);
                }else{
                    //Imprime el caracter correspondiente a la coordenada x, y
                    printf(" %c %c",TABLERO.xy[x][y].valor ,TABLERO.xy[x][y].imprimir);
                }
                

                /*Estos casos son para toma en cuenta las peculiaridades del tablero*/
                if((x+1)%3 == 0 && x < 8){
                    printf("%c", TABLERO.xy[x][y].imprimir);
                }
                
                if(x == 8 && y != 8 && (y+1)%3 != 0){
                    printf("        -------------------------------------\n\t");
                }
                if((y+1)%3 == 0 && y < 8 && x == 8){
                        printf("        =====================================\n\t");
                    }
            }
        }

        //Boton de salir
        if(posicionJugador.y == 9){
            printf("\n\n\t\t\t>Salir\n\n");
        }else{
            printf("\n\n\t\t\t Salir\n\n");
        }
        posicionJugador = moverse_en_tablero(posicionJugador);

        //Si se presiono enter
        if(posicionJugador.enter == 1){
            switch (posicionJugador.y){
            case 9:         //Corresponde a terminar el juego
                juego = 0;
                break;

            default:        //Corresponde a llenar casilla
                //Llena la casilla seleccionada con un numero que va a dijitar el usuario
                TABLERO.xy[posicionJugador.x][posicionJugador.y].valor = llenarCasilla();
                break;
            }
        }
        
        //Enter valor a falso para seguir llenando mas casillas
        posicionJugador.enter = 0;
        system("CLS"); 
    }
}

struct XY_tablero moverse_en_tablero(struct XY_tablero posicion){
    //Input del teclado del usuario
    char input;

    //Leer input
    input = getch();

    //Se suman o se restan posiciones dependiendo la tecla que se presione
    switch (input){
    case ARRIBA:           
        posicion.y--; 

        if(posicion.y < 0){
            posicion.y = 8;
        }
        break;
    case ABAJO:
        posicion.y++;

        if(posicion.y > 9){
            posicion.y = 0;
        }
        break;
    case DERECHA:
        posicion.x++;

        if(posicion.x > 8){
            posicion.x = 0;
        }
        break;
    case IZQUIERDA:
        posicion.x--;

        if(posicion.x < 0){
            posicion.x = 8;
        }
        break;

    case ENTER:
        posicion.enter = 1;
        break;
    }

    return posicion;
}

struct Tablero crearCasillas(){
    //Contadores para el for
    int x, y;

    //Valor para la casilla

    //Tablero al que se le van a dar valores
    struct Tablero TABLERO;

    //for para darle los valores a las casillas en y
    for(y=0; y<9; y++){
        //for para darle valores a x
        for(x=0; x<9; x++){
            //Le da un valor vacio a la casilla
            TABLERO.xy[x][y].valor = ' ';
            if(x < 8){
                TABLERO.xy[x][y].imprimir = '|';
            }else{
                TABLERO.xy[x][y].imprimir = '\n';
            }
        }
    }

    return TABLERO;
}

char llenarCasilla(){
    //Va a recibir un numero y lo va a trasformar a char para regresarlo para que entre en una casilla
    char numero;

    //Numero que va a digitar el jugador
    int n;

    do{
        //Llenamos la casilla seleccionadfa con un numero del 1 al 9 que dijite el usuario
        printf("\n\t\tNumero (1 al 9): ");
        //Si el usuario digita una letra se convierte a entero para evitar bugs
        if (scanf("%d", &n) != 1) {
        n = 0;
        /* Limpia el buffer del stdin (Evita el ciclo infinito) */
        while (getchar() != '\n');
        }

        if(n < 1 || n > 9){
            printf("\tERROR: Solo se permiten numeros del 1 al 9");
        }

    }while(n < 1 || n > 9);

    //Convertimos el numero a caracter
    numero = (char) (n + '0');

    return numero;
}
