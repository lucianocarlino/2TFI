#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Variables.h>

struct fechaAct
{
    int dia;
    int mes;
    int anio;
};

void MuestraOp(int &O){
    printf("Modulo del recepcionista\n");
    printf("===============\n");
    printf("1-Iniciar sesion\n");
    printf("2-Registrar cliente\n");
    printf("3-Registrar turno\n");
    printf("4-Listado de atenciones por profesional y fecha\n\n");
    printf("5-Salir\n");
    printf("Ingrese una opcion:  ");
    scanf("%d", &O);
}

void InicioSes(FILE *archi, bool &log, Recepecionistas &RecepSelec){
    char nomb[10], contr[32];
    int compU, CompC;
    Recepecionistas buff;
    rewind(archi);
    printf("Ingrese su nombre de usuario\n");
    _flushall();
    gets(nomb);
    fread(&buff, sizeof(Recepecionistas), 1, archi);
    while (!feof(archi))
    {
        compU=strcmp(nomb, buff.us.usuario);
        if (compU==0)
        {
        printf("Bienvenido %s\n", buff.Apynom);
        while (!log)
        {
            printf("Ingrese su contraseña\n");
            _flushall();
            gets(contr);
            CompC=strcmp(contr, buff.us.contr);
            if (CompC==0)
            {
                printf("Se registró con exito\n");
                log=true;
                RecepSelec=buff;
            } else
            {
                printf("La contraseña es incorrecta\n");
            }
        }
        }
        fread(&buff, sizeof(Recepecionistas), 1, archi);
    }
}

void RegistroCliente(FILE *archi){
    fseek(archi, 0, SEEK_END);
    Clientes buff;
    printf("--Nuevo cliente--");
    printf("Ingrese el Apellido y nombre\n");
    _flushall();
    gets(buff.Apynom);
    printf("Ingrese el domicilio\n");
    _flushall();
    gets(buff.Domicilio);
    printf("Ingrese el DNI\n");
    scanf("%d", &buff.DNICliente);
    printf("Ingrese la localidad\n");
    _flushall();
    gets(buff.Localidad);
    printf("Ingrese la fecha de nacimiento, con numeros\n");
    printf("Dia: \n");
    scanf("%d", &buff.FechaNac.dia);
    printf("Mes: \n");
    scanf("%d", &buff.FechaNac.mes);
    printf("Anio: \n");
    scanf("%d", &buff.FechaNac.anio);
    printf("Ingrese su peso\n");
    scanf("%f", &buff.Peso);
    printf("Ingrese su telefono celular\n");
    _flushall();
    gets(buff.Tel);
    fwrite(&buff, sizeof(Clientes), 1, archi);
    printf("Cliente registrado con exito\n");
}

void RegistroTurno(FILE *archi){
    fseek(archi, 0, SEEK_END);
    Turnos buff;
    printf("--Nuevo Turno--");
    printf("Ingrese ID del profesional requerido\n");
    scanf("%d", &buff.IdPro);
    printf("Ingrese la fecha del turno, con numeros\n");
    printf("Dia: \n");
    scanf("%d", &buff.Fecha.dia);
    printf("Mes: \n");
    scanf("%d", &buff.Fecha.mes);
    printf("Anio: \n");
    scanf("%d", &buff.Fecha.anio);
    printf("Ingrese el DNI del cliente\n");
    scanf("%d", &buff.DNICliente);
    printf("Ingrese el DNI\n");
    scanf("%d", &buff.DNICliente);
    buff.Pend=true;
    fwrite(&buff, sizeof(Turnos), 1, archi);
    printf("Turno registrado con exito\n");
}

void Informe(FILE *archi, FILE *Cliente){
    fechaAct Busq;
    Turnos buffT;
    Clientes buffC;
    int ProfId, v[500], cont=0, i;
    rewind(archi);
    rewind(Cliente);
    printf("Ingrese el ID del profesional a buscar\n");
    scanf("%d", &ProfId);
    printf("Ingrese la fecha a buscar\n");
    printf("Dia: \n");
    scanf("%d", &Busq.dia);
    printf("Mes: \n");
    scanf("%d", &Busq.mes);
    printf("Anio: \n");
    scanf("%d", &Busq.anio);
    fread(&buffT, sizeof(Turnos), 1, archi);
    while (!feof(archi))
    {
        if (Busq.dia==buffT.Fecha.dia && Busq.mes==buffT.Fecha.mes && Busq.anio==buffT.Fecha.anio)
        {
            if (ProfId==buffT.IdPro)
            {
                v[cont]=buffT.DNICliente;
                cont=cont++;
            }
        }
        fread(&buffT, sizeof(Turnos), 1, archi);
    }
    printf("El profesional vió a %d pacientes\n", cont);
    fread(&buffC, sizeof(Clientes), 1, Cliente);
    while (!feof(Cliente))
    {
        for ( i = 0; i < cont; i++)
        {
            if (v[i]==buffC.DNICliente)
            {
                printf("Paciente atendido el %d/%d/%d\n", Busq.dia, Busq.mes, Busq.anio);
                printf("Apellido y nombre: %s\n", buffC.Apynom);
                printf("Domicilio: %s\n", buffC.Domicilio);
                printf("DNI: %d\n", buffC.DNICliente);
                printf("Localidad: %s\n", buffC.Localidad);
                printf("Fecha de nacimiento: %d/%d/&d\n", buffC.FechaNac.dia, buffC.FechaNac.mes, buffC.FechaNac.anio);
                printf("Peso: %.2f\n", buffC.Peso);
                printf("Telefono celular: %s\n", buffC.Tel);
            }
        }
        fread(&buffC, sizeof(Clientes), 1, Cliente);
    }
}

main(){
    int O;
    bool log;
    fechaAct Hoy;
    Recepecionistas RecepSelec;
    FILE *Turnosa, *Clientesa, *Recep;
    Recep=fopen("Recepcionistas.dat", "r+b");
    Turnosa=fopen("Turnos.dat", "r+b");
    Clientesa=fopen("Clientes.dat", "r+b");
    while(O!=5){
        if(O==1){
            InicioSes(Recep, log, RecepSelec);
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
                RegistroCliente(Clientesa);
            } else
            {
                printf("Para realizar esta operacion debe registrarse primero\n");
            }
            MuestraOp(O);
        } else if (O==3){
            if (log)
            {
                RegistroTurno(Turnosa);
            } else
            {
                printf("Para realizar esta operacion debe registrarse primero\n");
            }
            MuestraOp(O);
        } else if (O==4){
            if (log)
            {
                Informe(Turnosa, Clientesa);
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
    fclose(Turnosa);
    fclose(Clientesa);
    fclose(Recep);
}