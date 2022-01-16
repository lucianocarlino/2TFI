#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Variables.h"
#include<cstdio>

struct fechaAct
{
    int dia;
    int mes;
    int anio;
};


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

void InicioSes(*FILE archi, bool &log, Profesionales &ProSelec){
    char nomb[10], contr[32];
    int compU, CompC;
    Profesionales buff;
    rewind(archi);
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
            ProSelec=buff;
        }
        }
        fread(&compId, sizeof(int), 1, archi);
    }
}

void MuestraPacientes(*FILE &archi, *FILE &Cliente, Turnos &TurSelec, Clientes &ClienteSelec){
    Turnos buffT;
    int edad;
    Clientes buffC;
    bool Muestra=false;
    fread(&buffT, sizeof(Turnos), 1, archi);
    while (!feof(archi) && !Muestra)
    {
        if (buff.Pend)
        {
            fread(&buffC, sizeof(Clientes), 1, Cliente);
            while (!feof(Cliente) && !Muestra)
            {
                if (Cliente.DNICliente==buff.DNICLiente)
                {
                    printf("Es el turno de %s\n", buffC.Apynom);
                    printf("DNI: %d\n", buffC.DNICliente);
                    printf("Domicilio: %s\n", buffC.Domicilio);
                    edad=2020-buffC.FechaNac.anio;
                    printf("Edad: %d\n", edad);
                    printf("Peso: %.2f\n", buffC.Peso);
                    printf("Para pasar al siguiente paciente pulse ENTER\n");
                    system("pause");
                    buffT.Pend=false;
                    TurSelec=buffT;
                    ClienteSelec=buffC;
                    Muestra=true;
                }
                fread(&buffC, sizeof(Clientes), 1, Cliente);
            }
        }
        fread(&buffT, sizeof(Turnos), 1, archi);
    }
}

void RegTratamiento(*FILE &archi, Clientes Cliente, Profesionales Prof, fechaAct fech){
    rewind(archi);
    Turnos buff;
    char Detalle[380], FechaChar[20];
    bool Busqueda=true;
    fread(&buff, sizeof(Turnos), 1, archi);
    while (!feof(archi) && Busqueda)
    {
        if (Cliente.DNICliente==buff.DNICliente)
        {
            printf("Ingrese el tratamiento del paciente %s\n", Cliente.Apynom);
            _flushall();
            gets(Detalle);
            strncat(Detalle, "\nProfesional: ");
            strncat(Detalle, Prof.Apynom);
            sprintf(FechaChar, "\nFecha=%d/%d/%d", fech.dia, fech.mes, fech.anio);
            strncat(Detalle, FechaChar);
            strcpy(buff.DetAt, Detalle);
            Busqueda=false;
        }
        fread(&buff, sizeof(Turnos), 1, archi);
    }
}

main(){
    int O;
    bool log;
    fechaAct Hoy;
    Profesionales ProSelec;
    Turnos TurSelec;
    Clientes ClienteSelec;
    *FILE Prof, Turnos, Clientes;
    Prof=fopen("Profesionales.dat", "r+b");
    Turnos=fopen("Turnos.dat", "r+b");
    Clientes=fopen("Clientes.dat", "rb");
    MuestraOp(O);
    while(O!=4){
        if(O==1){
            InicioSes(Prof, log, ProSelec);
            printf("Ingrese la fecha de hoy, en numeros\n");
            printf("Dia: \n");
            scanf("%d", &Hoy.dia);
            printf("Mes: \n");
            scanf("%d", &Hoy.mes);
            printf("Anio: \n");
            scanf("%d", &Hoy.anio);
            MuestraOp(O);
        } else if (O==2){
            if (log)
            {
                MuestraPacientes(Turnos, Clientes, TurSelec, ClienteSelec);
            } else
            {
                printf("Para realizar esta operacion debe registrarse primero\n");
            }
            MuestraOp(O);
        } else if (O==3){
            if (log)
            {
                RegTratamiento(Turnos, TurSelec, ClienteSelec, ProSelec, Hoy);
            } else
            {
                printf("Para realizar esta operacion debe registrarse primero\n");
            }
            MuestraOp(O);
        } else{
            printf("Ingrese una opcion valida\n");
            MuestraOp(O);
        }
    }
    fclose(Prof);
    fclose(Turnos);
}