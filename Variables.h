#inlcude<string.h>

struct fecha
{
    int dia;
    int mes;
    int anio;
};

struct usuarios
{
    char usuario[10];
    char contr[32];
    char Apynom [60];
};

struct Profesionales
{
    char Apynom [60];
    int IdPro;
    int DNI;
    char Tel[25];
    usuarios us;
};

struct Recepecionistas
{
    char Apynom [60];
    int IdRecep;
    int DNI;
    char Tel[25];
    usuarios us;
};

struct Turnos
{
    int IdPro;
    fecha Fecha;
    int DNICliente;
    char DetAt[380];
    bool Pend;
};

struct Clientes
{
    char Apynom [60];
    char Domicilio [60];
    int DNICliente;
    char Localidad [60];
    fecha FechaNac;
    float Peso;
    char Tel[25];
};
