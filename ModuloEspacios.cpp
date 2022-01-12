#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Variables.h>

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

void InicioSes(bool &log, profesionales &selec){
    char nomb[10], contr[32];
    int compU, CompC;
    Profesionales buff;
    *FILE archi;
    archi=fopen("Profesionales.dat", "r+b");
    printf("Ingrese su nombre de usuario\n");
    _flushall();
    gets(nomb);
    fread(&buff, sizeof(Profesionales), 1, archi);
    while (!feof(archi))
    {
        compU=strcmp(nomb, buff.us.usuario);
        if (compU==0)
        {
        printf("Bienvenido %s\n", buff.ApyNom);
        printf("Ingrese su contraseña\n");
        _flushall();
        gets(contr);
        CompC=strcmp(contr, buff.us.contr);
        if (CompC==0)
        {
            printf("Se registró con exito\n");
            log=true;
            selec=buff;
        }
        }
        fread(&compId, sizeof(int), 1, archi);
    }
}

main(){
    int O;
    bool log;
    Profesionales selec;
    MuestraOp(O);
    while(O!=4){
        if(O==1){
            InicioSes();
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