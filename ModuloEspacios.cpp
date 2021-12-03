#include<stdio.h>
#include<stdlib.h>

void MuestraOp(int &O){
    printf("Modulo espacios\n");
    printf("===============\n");
    printf("1-Iniciar sesion\n");
    printf("2-Visualizar lista de espera\n");
    printf("3-Registrar evolucion de tratamiento\n\n");
    printf("4-Salir\n");
    printf("Ingrese una opcion:  ");
    scanf("%d", &O);
}

void InicioSes(){

}

main(){
    int O;
    MuestraOp(O);
    while(O!=4){
        if(O==1){

            MuestraOp(O);
        } else if (O==2){
            MuestraOp(O);
        } else if (O==3){
            MuestraOp(O);
        } else{
            printf("No pude encontrar el codigo deseado\n");
            MuestraOp(O);
        }
    }
    
}