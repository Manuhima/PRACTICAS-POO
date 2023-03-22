

#include "fecha.hpp"

/////////////////// MÉTODOS PRIVADOS ///////////////////
void Fecha::comprueba() const
{
    if(dia_>ultimo_dia() || dia_<1){
        Invalida d_inval{"Dia Incorrecto"};
        throw d_inval;
    }

    if(anno_<Fecha::AnnoMinimo || anno_>Fecha::AnnoMaximo){
        Invalida a_inval{"Año Incorrecto"};
        throw a_inval;
    }
}

int Fecha::ultimo_dia() const {
    if(mes_==1 || mes_==3 || mes_==5 || mes_==7 || mes_==8 || mes_==10 || mes_==12) 
        return 31;

    else{
        if(mes_==4 || mes_==6 || mes_==9 || mes_==11)
            return 30;

        else{
            if(mes_==2){ //¿Es bisiesto?
                if(anno_%4==0 && (anno_%400==0 || anno_%100!=0))
                    return 29;
                else
                    return 28;

            }else{
                Invalida inval{"Mes Incorrecto"};
                throw inval;
            }
        } 
    } 
}

/////////////////// CONSTRUCTORES ///////////////////
Fecha::Fecha(int d, int m, int a): dia_{d}, mes_{m}, anno_{a}
{
    std::time_t tiempo_calendario=std::time(nullptr);
    std::tm* tiempo_descompuesto=std::localtime(&tiempo_calendario);
    //Si es 0 lo pone al actual
    if(anno_==0)
        anno_=tiempo_descompuesto->tm_year+1900;
    if(mes_==0)
        mes_=tiempo_descompuesto->tm_mon+1;
    if (dia_==0)
        dia_=tiempo_descompuesto->tm_mday;
    comprueba();
}

Fecha::Fecha (const char* c)
{
    if(sscanf(c,"%d/%d/%d",&dia_,&mes_,&anno_)!=3){
    //sscanf debe devolver 3, uno por dia, otro por mes y otro por año
        Invalida format{"Formato de la cadena incorrecto."};
        throw format;
    }

    //Llamo al constructor de 3 parámetros (en vez de volver a copiarlo)
    *this=Fecha(dia_,mes_,anno_);
}

/////////////////// CONVERSOR FECHA -> CONST CHAR* ///////////////////
Fecha::operator const char*() const
{
    std::locale::global(std::locale("")); //Por defecto ("") pilla la del sistema -> "es_ES.utf8"
    char *buffer=new char[50]; //50 por ejemplo

    std::time_t tiempo_calendario=std::time(nullptr);                  
    std::tm* tiempo_descompuesto=std::localtime(&tiempo_calendario);    

    tiempo_descompuesto->tm_mday=dia_;
    tiempo_descompuesto->tm_mon=mes_-1;
    tiempo_descompuesto->tm_year=anno_-1900;

    mktime(tiempo_descompuesto); //Rellena el struct tm y normaliza la fecha. Ej: 30 Febrero 2023 -> 2 Marzo 2023
    strftime(buffer,50,"%A %e de %B de %Y",tiempo_descompuesto); //De struct tm a formato cadena

    return buffer;
}

/////////////////// OPERADORES ///////////////////
Fecha& Fecha::operator +=(int n)
{
    std::tm fe{};
    fe.tm_mday=dia_+n;
    fe.tm_mon=mes_-1;
    fe.tm_year=anno_-1900;
    mktime(&fe);
    //Sumamos días, normalizamos, comprobamos, devolvemos
    dia_=fe.tm_mday;
    mes_=fe.tm_mon+1;
    anno_=fe.tm_year+1900;
    comprueba();

    return *this;
}

Fecha& Fecha::operator -=(int n)
{
    *this+= -n;
    return *this;
}

Fecha& Fecha::operator ++() //++f
{
    *this+=1;
    return *this;
}

Fecha& Fecha::operator ++(int) //f++
{
    Fecha *f=new Fecha{*this};
    *this+=1;
    return *f;
}

Fecha& Fecha::operator --() //--f
{
    *this+= -1;
    return *this;
}

Fecha& Fecha::operator --(int) //f--
{
    Fecha *f=new Fecha{*this};
    *this+= -1;
    return *f;
}

/////////////////// OPERADORES ARITMÉTICOS ///////////////////
Fecha Fecha::operator +(int n) const
{
    Fecha f{*this};
    return f+=n;
}

Fecha Fecha::operator -(int n) const
{
    Fecha f{*this};
    return f+= -n;
}
