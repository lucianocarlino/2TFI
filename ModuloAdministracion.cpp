#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Variables.h>
#include<cstdio>

struct fechaAct
{
    int dia;
    int mes;
    int anio;
};


void MuestraOp(int &O){
    printf("Modulo administracion\n");
    printf("===============\n");
    printf("1-Registrar profesional\n");
    printf("2-Registrar usuario recepcionista\n");
    printf("3-Atenciones por profesional\n");
    printf("4-Ranking de profesionales por atenciones\n\n");
    printf("5-Salir\n");
    printf("Ingrese una opcion:  ");
    scanf("%d", &O);
}


bool VerificacionUs(char cadena[10]){
    bool r=true;
    int i, contM=0, contD=0;
    int v[]={33, 42, 43, 45, 47, 63, 168, 173};
    if (strlen(cadena)<6 or strlen(cadena)>10)
    {
        r=false;
    }
    if (cadena[0]<97 and cadena[0]>122)
    {
        r=false;
    }
    for ( i = 0; i < strlen(cadena); i++)
    {
        if (cadena[i]<48 and cadena[i]>57)
        {
            if (cadena[i]<65 and cadena[i]>90)
            {
                if (cadena[i]<97 and cadena[i]>122)
                {
                    for ( i = 0; i < 8; i++)
                    {
                        if (cadena[i]!=v[i])
                        {
                            r=false;
                        } else
                        {
                            r=true;
                        }
                    }
                }
            } else
            {
                contM++;
            }
            
        } else
        {
            contD++;
        }
        
    }
    if (contD>3)
    {
        r=false;
    }
    if (contM<2)
    {
        r=false;
    }
    return r;
}

bool VerificacionContr(char cadena[32]){
    bool r=true;
    int i, contmin=0, contmay=0, contnum=0, j, k;
    if (strlen(cadena)<6 or strlen(cadena)>32)
    {
        r=false;
    }
    for ( i = 0; i < strlen(cadena); i++)
    {
        if (cadena[i]<48 and cadena[i]>57)
        {
            if (cadena[i]<65 and cadena[i]>90)
            {
                if (cadena[i]<97 and cadena[i]>122)
                {
                    r=false;
                } else
                {
                    contmin=1;
                    if (cadena[i]==cadena[i+1]-1)
                    {
                        r=false;
                    }
                    if (cadena[1]==cadena[i+1]-33)
                    {
                        r=false;
                    }
                }
            } else
            {
                contmay=1;
                if (cadena[i]==cadena[i+1]-1)
                {
                    r=false;
                }
                if (cadena[1]==cadena[i+1]-33)
                {
                    r=false;
                }
            }
        } else
        {
            contnum=1;
            if (cadena[i]==cadena[i+1]-1 and cadena[i+1]==cadena[i+2]-1)
            {
                r=false;
            }
            if (cadena[i]==cadena[i+1]+1 and cadena[i+1]==cadena[i+2]+1)
            {
                r=false;
            }
        }
    }
    if (contmin<1 or contmay<1 or contnum<1)
    {
        r=false;
    }
    return r;
}

void NuevoProf(FILE *archi){
    Profesionales buff, buffR;
    int comp;
    bool val=false;
    char usuario[10], contr[32];
    printf("--Nuevo Profesional--");
    printf("Ingrese el apellido y nombre\n");
    _flushall();
    gets(buff.Apynom);
    printf("Ingrese el Id de profesional\n");
    scanf("%d", buff.IdPro);
    printf("Ingrese el DNI\n");
    scanf("%d", &buff.DNI);
    printf("Ingrese el telefono\n");
    _flushall();
    gets(buff.Tel);
    strcpy(buff.us.Apynom, buff.Apynom);
    printf("Ingrese su nombre de usuario, debe cumplir:\n");
    printf("Minimo 6 caracteres, maximo 10 caracteres\n");
    printf("Se aceptan letras, digitos (como maximo 3) y simbolos del conjunto: +, -, /, ?, ¿, !, ¡\n");
    printf("Comenzar con una letra minuscula\n");
    printf("Contener al menos dos letras mayusculas\n");
    _flushall();
    gets(usuario);
    val=VerificacionUs(usuario);
    while (!val)
    {
        printf("El nombre de usuario no cumple uno de los requisitos\n");
        printf("Ingrese su nombre de usuario, debe cumplir:\n");
        printf("Minimo 6 caracteres, maximo 10 caracteres\n");
        printf("Se aceptan lestras, digitos (como maximo 3) y simbolos del conjunto: +, -, /, ?, ¿, !, ¡\n");
        printf("Comenzar con una letra minuscula\n");
        printf("Contener al menos dos letras mayusculas\n");
        _flushall();
        gets(usuario);
        val=VerificacionUs(usuario);
        fseek(archi, 0, SEEK_SET);
        fread(&buffR, sizeof(Profesionales), 1, archi);
        while (!feof(archi))
        {
            comp=strcmp(usuario, buffR.us.usuario);
            fread(&buffR, sizeof(Profesionales), 1, archi);
        }
        if (comp==0)
        {
            printf("Su nombre de usuario no es unico\n");
            val=false;
        }
    }
    strcpy(buff.us.usuario, usuario);
    printf("Ingrese su contraseña, debe cumplir:\n");
    printf("Minimo 6 caracteres, maximo 32 caracteres\n");
    printf("Solo se aceptan letras y digitos, al menos una minuscula, una mayuscula y un digito\n");
    printf("No debe tener mas de tres digitos consecutivos\n");
    printf("No debe tener mas de dos letras consecutivas ascendentes, tanto mayusculas o minusculas\n");
    _flushall();
    gets(contr);
    val=false;
    val=VerificacionContr(contr);
    while (!val)
    {
        printf("La contraseña no cumple uno de los requisitos\n");
        printf("Ingrese su contraseña, debe cumplir:\n");
        printf("Minimo 6 caracteres, maximo 32 caracteres\n");
        printf("Solo se aceptan letras y digitos, al menos una minuscula, una mayuscula y un digito\n");
        printf("No debe tener mas de tres digitos consecutivos\n");
        printf("No debe tener mas de dos letras consecutivas ascendentes, tanto mayusculas o minusculas\n");
        _flushall();
        gets(contr);
        val=VerificacionContr(contr);
    }
    strcpy(buff.us.contr, contr);
    fseek(archi, 0, SEEK_END);
    fwrite(&buff, sizeof(Profesionales), 1, archi);
    printf("Profesional registrado con exito\n");
}

void NuevoRecep(FILE *archi){
    Recepecionistas buff, buffR;
    int comp;
    bool val=false;
    char usuario[10], contr[32];
    printf("--Nuevo Profesional--");
    printf("Ingrese el apellido y nombre\n");
    _flushall();
    gets(buff.Apynom);
    printf("Ingrese el Id de profesional\n");
    scanf("%d", buff.IdRecep);
    printf("Ingrese el DNI\n");
    scanf("%d", &buff.DNI);
    printf("Ingrese el telefono\n");
    _flushall();
    gets(buff.Tel);
    strcpy(buff.us.Apynom, buff.Apynom);
    printf("Ingrese su nombre de usuario, debe cumplir:\n");
    printf("Minimo 6 caracteres, maximo 10 caracteres\n");
    printf("Se aceptan letras, digitos (como maximo 3) y simbolos del conjunto: +, -, /, ?, ¿, !, ¡\n");
    printf("Comenzar con una letra minuscula\n");
    printf("Contener al menos dos letras mayusculas\n");
    _flushall();
    gets(usuario);
    val=VerificacionUs(usuario);
    while (!val)
    {
        printf("El nombre de usuario no cumple uno de los requisitos\n");
        printf("Ingrese su nombre de usuario, debe cumplir:\n");
        printf("Minimo 6 caracteres, maximo 10 caracteres\n");
        printf("Se aceptan lestras, digitos (como maximo 3) y simbolos del conjunto: +, -, /, ?, ¿, !, ¡\n");
        printf("Comenzar con una letra minuscula\n");
        printf("Contener al menos dos letras mayusculas\n");
        _flushall();
        gets(usuario);
        val=VerificacionUs(usuario);
        fseek(archi, 0, SEEK_SET);
        fread(&buffR, sizeof(Recepecionistas), 1, archi);
        while (!feof(archi))
        {
            comp=strcmp(usuario, buffR.us.usuario);
            fread(&buffR, sizeof(Recepecionistas), 1, archi);
        }
        if (comp==0)
        {
            printf("Su nombre de usuario no es unico\n");
            val=false;
        }
    }
    strcpy(buff.us.usuario, usuario);
    printf("Ingrese su contraseña, debe cumplir:\n");
    printf("Minimo 6 caracteres, maximo 32 caracteres\n");
    printf("Solo se aceptan letras y digitos, al menos una minuscula, una mayuscula y un digito\n");
    printf("No debe tener mas de tres digitos consecutivos\n");
    printf("No debe tener mas de dos letras consecutivas ascendentes, tanto mayusculas o minusculas\n");
    _flushall();
    gets(contr);
    val=false;
    val=VerificacionContr(contr);
    while (!val)
    {
        printf("La contraseña no cumple uno de los requisitos\n");
        printf("Ingrese su contraseña, debe cumplir:\n");
        printf("Minimo 6 caracteres, maximo 32 caracteres\n");
        printf("Solo se aceptan letras y digitos, al menos una minuscula, una mayuscula y un digito\n");
        printf("No debe tener mas de tres digitos consecutivos\n");
        printf("No debe tener mas de dos letras consecutivas ascendentes, tanto mayusculas o minusculas\n");
        _flushall();
        gets(contr);
        val=VerificacionContr(contr);
    }
    strcpy(buff.us.contr, contr);
    fseek(archi, 0, SEEK_END);
    fwrite(&buff, sizeof(Recepecionistas), 1, archi);
    printf("Recepcionista registrado con exito\n");
}

void Informe(FILE *archi){
    fechaAct Busq;
    Turnos buffT;
    int ProfId, cont=0;
    rewind(archi);
    printf("Ingrese el ID del profesional a buscar\n");
    scanf("%d", &ProfId);
    printf("Ingrese el mes y año a buscar\n");
    printf("Mes: \n");
    scanf("%d", &Busq.mes);
    printf("Anio: \n");
    scanf("%d", &Busq.anio);
    fread(&buffT, sizeof(Turnos), 1, archi);
    while (!feof(archi))
    {
        if (Busq.mes==buffT.Fecha.mes && Busq.anio==buffT.Fecha.anio)
        {
            if (ProfId==buffT.IdPro)
            {
                cont=cont++;
            }
        }
        fread(&buffT, sizeof(Turnos), 1, archi);
    }
    printf("El profesional vió a %d pacientes\n", cont);
}

void Ranking(FILE *archi, FILE *Prof){
    fechaAct Busq;
    Turnos buffT;
    Profesionales buffP, MejProf;
    int v[500], contPac=0, MayPac=0;
    rewind(archi);
    rewind(Prof);
    printf("Ingrese el mes y año a buscar\n");
    printf("Mes: \n");
    scanf("%d", &Busq.mes);
    printf("Anio: \n");
    scanf("%d", &Busq.anio);
    fread(&buffP, sizeof(Profesionales), 1, Prof);
    while (!feof(Prof))
    {   
        fread(&buffT, sizeof(Turnos), 1, archi);
        while (!feof(archi))
        {
            if (Busq.mes==buffT.Fecha.mes && Busq.anio==buffT.Fecha.anio)
            {
                if (buffP.IdPro==buffT.IdPro)
                {
                    contPac=contPac++;
                }
            }
            fread(&buffT, sizeof(Turnos), 1, archi);
        }
        if (contPac>MayPac)
        {
            MejProf=buffP;
            MayPac=contPac;
        }
        contPac=0;
        fread(&buffP, sizeof(Profesionales), 1, Prof);
    }
    printf("El profesional que mas pacientes atendió este mes es: %s, con ID %d\n", MejProf.Apynom, MejProf.IdPro);
}

main(){
    int O;
    FILE *Recep, *Prof, *Turnosa;
    Recep=fopen("Recepcionistas.dat", "r+b");
    Prof=fopen("Profesionales.dat", "r+b");
    Turnosa=fopen("Turnos.dat", "r+b");
    while(O!=5){
        if(O==1){
            NuevoProf(Prof);
            MuestraOp(O);
        } else if (O==2){
            NuevoRecep(Recep);
            MuestraOp(O);
        } else if (O==3){
            Informe(Turnosa);
            MuestraOp(O);
        } else if (O==4){
            Ranking(Turnosa, Prof);
            MuestraOp(O);
        } else{
            printf("Ingrese una opcion valida\n");
            MuestraOp(O);
        }
    }
    fclose(Recep);
    fclose(Prof);
    fclose(Turnosa);
}