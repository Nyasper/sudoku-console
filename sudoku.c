#include <stdio.h>


//Funciones
int imprimirMenu();

main(){
    imprimirMenu();

    return 0;
}

int imprimirMenu(){
    int op = 0;

    //imprime un menu con ascii art
    printf("\t __           _       _       \n");   
    printf("\t/ _\\_   _  __| | ___ | | ___   _ \n");
    printf("\t\\ \\| | | |/ _` |/ _ \\| |/ / | | |\n");
    printf("\t_\\ \\ |_| | (_| | (_) |   <| |_| |\n");
    printf("\t\\__/\\__,_|\\__,_|\\___/|_|\\_\\__,_|\n\n");

    //Imprimir opciones
    printf("\t1.Jugar      2.Puntajes     3.Iniciar sesion\n");
    
    //Bucle que no deja salir al usuario hasta que ponga una opcion correcta
    do{
        //Lee la opcion del usuario
        printf("\n\t\tOpcion: ");
        scanf("%d", &op);

        //Imprimir mensaje de error si el jugador no pone una opcion correcta
        if(op<1 || op>3){
            printf("\t\tERROR: Opcion no valida. :00\n");
        }
    }while(op<1 || op>3);
    
    

    return op;
}
