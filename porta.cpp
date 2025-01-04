#include "porta.h"

///
/// AS PORTAS
///

/// Porta NOT

//
// FALTA IMPLEMENTAR
//
bool PortaNOT::simular(const std::vector<bool3S>& in_port)
{
    bool3S prov = bool3S::UNDEF;
    if(in_port.size()>0 && in_port.size() == this->Nin_port)
    {
        for(int i=0; i<in_port.size(); ++i)
        {
            prov = ~(in_port[i]);
        }
        out_port = prov;
        return true;
    }
    out_port = prov;
    return false;
}

/// Porta AND

//
// FALTA IMPLEMENTAR
//
bool PortaAND::simular(const std::vector<bool3S>& in_port)
{
    bool3S prov = bool3S::UNDEF;
    if(in_port.size()>0 && in_port.size() == this->Nin_port)
    {
        for(int i=0; i<in_port.size()-1;++i)
        {
            prov = in_port[i]&in_port[i+1];
        }
        out_port = prov;
        return true;
    }
    out_port = prov;
    return false;
}

/// Porta NAND

//
// FALTA IMPLEMENTAR
//

bool PortaNAND::simular(const std::vector<bool3S> &in_port)
{
    bool3S prov = bool3S::UNDEF;
    if(in_port.size()>0 && in_port.size()== this->Nin_port)
    {
        for(int i=0; i<in_port.size()-1; ++i)
        {
            prov = ~(in_port[i]&in_port[i+1]);
        }
        out_port = prov;
        return true;
    }
    out_port = prov;
    return false;
}

/// Porta OR

//
// FALTA IMPLEMENTAR
//
bool PortaOR::simular(const std::vector<bool3S> &in_port)
{
    bool3S prov = bool3S::UNDEF;
    if(in_port.size()>0 && in_port.size() == this->Nin_port)
    {
        for(int i=0; i<in_port.size()-1; ++i)
        {
            prov = in_port[i]|in_port[i+1];
        }
        this->out_port=prov;
    }
}

/// Porta NOR

//
// FALTA IMPLEMENTAR
//
bool PortaNOR::simular(const std::vector<bool3S> &in_port)
{
    bool3S prov = bool3S::UNDEF;
    if(in_port.size()>0 && in_port.size()==Nin_port)
    {
        for(int i=0;i<in_port.size()-1; ++i)
        {
            prov = ~(in_port[i]|in_port[i+1]);
        }
        out_port=prov;
        return true;
    }
    out_port=prov;
    return false;
}

/// Porta XOR

//
// FALTA IMPLEMENTAR
//

bool PortaXOR::simular(const std::vector<bool3S> &in_port)
{
    bool3S prov = bool3S::UNDEF;
    if(in_port.size()>0 && in_port.size() == this->Nin_port)
    {
        for(int i=0;i<in_port.size()-1;++i)
        {
            prov = in_port[i]^in_port[i+1];
        }
        this->out_port=prov;
        return true;
    }
    this->out_port=prov;
    return false;
}

/// Porta NXOR

//
// FALTA IMPLEMENTAR
//
