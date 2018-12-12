//=============================================================================================================== GBL.H
//
// Este módulo contiene las definiciones comunes a todos los módulos de bibliotecas
//
// ============================================================================================ 16/12/1995 - 19/09/2013
#pragma warning(disable:4267) //size_t to int

#if !defined(GBL_H)
#define GBL_H

//Macros definidas:
//_MT:       multihilo
//_DEBUG:    modo depuración
//__WXMSW__: se utiliza wxWidgets
//_WINDOWS:  compilación bajo Windows

#if defined(_MT)                                 // Código dependiente del compilador __CDC__
  #define MTAREA                                 // Definición de multitarea
#else
  #undef MTAREA
#endif

// #define USE_ASSERT

//#define MANTENER_OBSOLETO_TINIFIN

#if !defined(USE_ASSERT)
  #undef _ASSERT                                 // Posible definición anterior
  #define _ASSERT(x)
#endif  // USE_ASSERT

// ====================================================================================================================
// =========================================================================================================== INCLUDES

#include "tipos.h"
#include "smartptr.h"

#include <limits>
#include <iostream>
#include <functional>

#include <string>
#include <string.h>
#include <vector>

// ====================================================================================================================
// ============================================================================================================ DEFINES

#define NO_USE(x)

#define MIN_REAL std::numeric_limits<REAL_>::min()        // Valor mínimo representable
#define MAX_REAL std::numeric_limits<REAL_>::max()        // Valor máximo representable

#define MIN_INT std::numeric_limits<int>::min()           // Valor mínimo representable
#define MAX_INT std::numeric_limits<int>::max()           // Valor máximo representable

#if defined(_WINDOWS) || defined(_WIN32)
  #define ENDL "\r\n"
  #define LENDL 2
#else
  #define ENDL "\n"
  #define LENDL 1
#endif  // _WINDOWS
#define TAB "\t"

#if defined(_MSC_VER) && _MSC_VER<=1800
  #define __func__ __FUNCTION__
  #define noexcept _NOEXCEPT
#endif  // _MSC_VER

#define SDT_BIEN 0                               // Todo ha funcionado correctamente
#define SDT_MEMO 1                               // Error en la reserva de memoria
#define SDT_NHAY 2                               // No se encuentra el dato en memoria
#define SDT_FILE 3                               // Error en la apertura del fichero
#define SDT_ESCR 4                               // Error en escritura de fichero
#define SDT_LECT 5                               // Error en lectura de fichero
#define SDT_LERE 6                               // Error en lectura recuperable
#define SDT_DIND 7                               // Direccionamiento no definido
#define SDT_ERND 8                               // Error no definido

// ============================================================================================================= CLASES
// ================================================================= NÚMEROS SIMPLES / ESTRUCTURAS NUMÉRICAS COMPUESTAS

class TNumSmpl {};                               // Número simple
class TNumComp {};                               // Estructura numérica compuesta
class TNumPtr  {};                               // Puntero inteligente

// ····················································································································

template <class T>
class TraitsNum

{
public:
  typedef TNumComp TNum;
};

// ····················································································································

//#define TRAITS_PTR(TipoPtr)\
//template <class T>\
//class TraitsNum<TipoPtr<T>>\
//{\
//public:\
//  typedef TNumPtr TNum;\
//  typedef TipoPtr<T> TSmartPtr;\
//};
//
//TRAITS_PTR(smdel_ptr)
//
//#undef TRAITS_PTR

template <class T>
class TraitsNum<smdel_ptr<T>>
{
public:
  typedef TNumPtr TNum;
//  typedef smdel_ptr<T> TPtr;
};

// ····················································································································

//#define TRAITS_NUM(Tipo)\
//template <>\
//class TraitsNum<Tipo>\
//{\
//public:\
//  typedef TNumSmpl TNum;\
//};

// Define tipo como Write/Read SiMPLe, es decir, no tiene componentes

#define DEF_WR_SMPL(Tipo)\
template <>\
class TraitsNum<Tipo>\
{\
public:\
  typedef TNumSmpl TNum;\
};

DEF_WR_SMPL(char)                                 // Lista de números simples
DEF_WR_SMPL(INT_)
DEF_WR_SMPL(UINT_)
DEF_WR_SMPL(INT8_)
DEF_WR_SMPL(UINT8_)
DEF_WR_SMPL(bool)
DEF_WR_SMPL(INT16_)
DEF_WR_SMPL(UINT16_)
DEF_WR_SMPL(INT32_)
DEF_WR_SMPL(UINT32_)
DEF_WR_SMPL(float)
DEF_WR_SMPL(double)

// ============================================================================================================= CLASES
// =========================================================================================================== PolicyWR

//USO:
//Write(os,&Var);
//Read(is,&Var);

template <class T,class TNum>
class PolicyWR

{
public:
  static void Write(std::ostream &os,const T *px);
  static void Read(std::istream &os,T *px);
};

// ····················································································································

template <class T>
class PolicyWR<T,TNumSmpl>

{
public:
  static void Write(std::ostream &os,const T *px) { os.write((PCSTR_)px,sizeof(T)); }
  static void Read(std::istream &is,T *px)        { is.read((PSTR_)px,sizeof(T)); }
};

// ····················································································································

template <class T>
class PolicyWR<T,TNumComp>

{
public:
  static void Write(std::ostream &os,const T *px) { os << *px; }
  static void Read(std::istream &is,T *px)        { is >> *px; }
};

// ····················································································································

template <class T>
class PolicyWR<T,TNumPtr>

{
public:
  static void Write(std::ostream &os,const T *px) { os << **px; }
  static void Read(std::istream &is,T *px)        { is >> **px; }
};

// ====================================================================================================================

template <class T,class TNum>
class PolicyWRN

{
public:
  static void Write(std::ostream &os,const T *px,int NComp);
  static void Read(std::istream &is,T *px,int NComp);
};

// ····················································································································

template <class T>
class PolicyWRN<T,TNumSmpl>

{
public:
  static void Write(std::ostream &os,const T *px,int NComp)
    { os.write((PCSTR_)px,NComp*sizeof(T)); }
  static void Read(std::istream &is,T *px,int NComp)
    { is.read((PSTR_)px,NComp*sizeof(T)); }
};

// ····················································································································

template <class T>
class PolicyWRN<T,TNumComp>

{
public:
  static void Write(std::ostream &os,const T *px,int NComp);
  static void Read(std::istream &is,T *px,int NComp);
};

// ····················································································································

template <class T>
class PolicyWRN<T,TNumPtr>

{
public:
  static void Write(std::ostream &os,const T *px,int NComp);
  static void Read(std::istream &is,T *px,int NComp);
};

// ····································································································· Implementación

template <class T>
void PolicyWRN<T,TNumComp>::Write(std::ostream &os,const T *px,int NComp)
  { for (int i= 0;i<NComp;i++) os << px[i]; }
template <class T>
void PolicyWRN<T,TNumComp>::Read(std::istream &is,T *px,int NComp)
  { for (int i= 0;i<NComp;i++) is >> px[i]; }

template <class T>
void PolicyWRN<T,TNumPtr>::Write(std::ostream &os,const T *px,int NComp)
  { for (int i= 0;i<NComp;i++) os << *px[i]; }
template <class T>
void PolicyWRN<T,TNumPtr>::Read(std::istream &is,T *px,int NComp)
  { for (int i= 0;i<NComp;i++) { px[i].reset(new typename T::TipoDato); is >> *px[i]; }}

// ================================================================================================= Funciones de ayuda

template <class T>
void Write(std::ostream &os,const T *px)
  { PolicyWR<T,typename TraitsNum<T>::TNum>::Write(os,px); }
template <class T>
void Read(std::istream &is,T *px)
  { PolicyWR<T,typename TraitsNum<T>::TNum>::Read(is,px); }

template <class T>
void Write(std::ostream &os,const T *px,int NComp)
  { PolicyWRN<T,typename TraitsNum<T>::TNum>::Write(os,px,NComp); }
template <class T>
void Read(std::istream &is,T *px,int NComp)
  { PolicyWRN<T,typename TraitsNum<T>::TNum>::Read(is,px,NComp); }

template <>
inline void Write<std::string>(std::ostream &os,const std::string *px)
  {
  int N= px->length();
  Write(os,&N);
  if (N>0)
    { Write(os,px->data(),N); }
  }
template <>
inline void Read<std::string>(std::istream &is,std::string *px)
  {
  int N;
  Read(is,&N);
  if (N>0)
    { std::vector<char> v(N); Read(is,&v[0],N); px->assign(&v[0],N); }
  }

// ====================================================================================================================

//USO:
//Tbis bis(is);
//
//bis >> NComp;
//if (NComp>0) { v.Crea(NComp); bis >> Tsetn(NComp) >> v.px; }

class Tsetn

{
private: const int NComp;
public:  Tsetn(int NComp_): NComp(NComp_) {}

friend class TsetnProxyR;
friend class TsetnProxyW;
friend class TsetnProxyWR;
};

// ====================================================================================================================

class Tbis;                                      // Declaración por adelantado

class TsetnProxyR

{
private:
  Tbis &bis;
  const int NComp;

// ·········································································································· Funciones

public:
               TsetnProxyR(Tbis &bis_,Tsetn setn): bis(bis_), NComp(setn.NComp) {}

  template <class T>
  Tbis         &operator >>(T *px);// { ::Read(bis.is,px,NComp); return bis; }
};

// ====================================================================================================================

class Tbos;                                      // Declaración por adelantado

class TsetnProxyW

{
private:
  Tbos &bos;
  const int NComp;

// ·········································································································· Funciones

public:
               TsetnProxyW(Tbos &bos_,Tsetn setn): bos(bos_), NComp(setn.NComp) {}

  template <class T>
  Tbos         &operator <<(const T *px); // { ::Write(bos.os,px,NComp); return bos; }
};

// ====================================================================================================================

class Tbios;

class TsetnProxyWR

{
private:
  Tbios &bios;
  const int NComp;

// ·········································································································· Funciones

public:
               TsetnProxyWR(Tbios &bios_,Tsetn setn): bios(bios_), NComp(setn.NComp) {}

  template <class T>
  Tbios         &operator <<(const T *px); // { ::Write(bos.os,px,NComp); return bos; }
  template <class T>
  Tbios         &operator >>(T *px);// { ::Read(bis.is,px,NComp); return bis; }
};

// ====================================================================================================================

class Tbis

{
private:
  typedef std::istream &TRef;

// ·············································································································· Datos

private:
  TRef is;

// ·········································································································· Funciones

private:
  Tbis         &operator =(const Tbis &) { return *this; }

public:
               Tbis(std::istream &is_): is(is_) {}

               operator bool() const { return !is.fail(); }
  bool         operator !() const    { return is.fail(); }

  template <class T>
  Tbis         &operator >>(T &x)      { ::Read(is,&x); return *this; }
  TsetnProxyR  operator >>(Tsetn setn) { return TsetnProxyR(*this,setn); }
  TRef         get()           { return is; }
               operator TRef() { return is; }

friend class TsetnProxyR;
};

// ====================================================================================================================

class Tbos

{
private:
  typedef std::ostream &TRef;

// ·············································································································· Datos

private:
  TRef os;

// ·········································································································· Funciones

private:
  Tbos         &operator =(const Tbos &) { return *this; }

public:
               Tbos(std::ostream &os_): os(os_) {}

               operator bool() const { return !os.fail(); }
  bool         operator !() const    { return os.fail(); }

  template <class T>
  Tbos         &operator <<(const T &x) { ::Write(os,&x); return *this; }
  TsetnProxyW  operator <<(Tsetn setn)  { return TsetnProxyW(*this,setn); }
  TRef         get()           { return os; }
               operator TRef() { return os; }

friend class TsetnProxyW;
};

// ====================================================================================================================

class Tbios

{
private:
  typedef std::iostream &TRef;

// ·············································································································· Datos

private:
  TRef ios;

// ·········································································································· Funciones

private:
  Tbios        &operator =(const Tbios &) { return *this; }

public:
               Tbios(std::iostream &ios_): ios(ios_) {}

               operator bool() const { return !ios.fail(); }
  bool         operator !() const    { return ios.fail(); }

  template <class T>
  Tbios        &operator <<(const T &x) { ::Write(ios,&x); return *this; }
  TsetnProxyWR operator <<(Tsetn setn)  { return TsetnProxyWR(*this,setn); }
  template <class T>
  Tbios        &operator >>(T &x)      { ::Read(ios,&x); return *this; }
  TsetnProxyWR operator >>(Tsetn setn) { return TsetnProxyWR(*this,setn); }
  TRef         get()           { return ios; }
               operator TRef() { return ios; }

friend class TsetnProxyWR;
};

// ====================================================================================================================

template <class T>
Tbis &TsetnProxyR::operator >>(T *px)
  { ::Read(bis.is,px,NComp); return bis; }

// ====================================================================================================================

template <class T>
Tbos &TsetnProxyW::operator <<(const T *px)
  { ::Write(bos.os,px,NComp); return bos; }

// ====================================================================================================================

template <class T>
Tbios &TsetnProxyWR::operator >>(T *px)
  { ::Read(bios.ios,px,NComp); return bios; }

// ====================================================================================================================

template <class T>
Tbios &TsetnProxyWR::operator <<(const T *px)
  { ::Write(bios.ios,px,NComp); return bios; }

// ====================================================================================================================
// ============================================================================================= CONSTANTES CIENTÍFICAS

CREAL_ cte_Faraday=  9.648456e4;                 // Constante de Faraday (C mol-1)
CREAL_ cte_KFaraday= KILO*cte_Faraday;           // Constante de Faraday (C kmol-1)
CREAL_ cte_g=        9.80665;                    // Aceleración de la gravedad (m s-2)
CREAL_ cte_G=        6.672E-11;                  // Constante de gravitación (N m2 kg-2)
CREAL_ cte_kGauss=   0.01720209895;              // Constante de gravitación de Gauss
CREAL_ cte_sgSB=     5.67032E-8;                 // Constante de Stefan-Boltzmann (W m-2 K-4)
CREAL_ cte_kB=       1.38062259e-23;             // Constante de Boltzmann (J K-1)
CREAL_ cte_NA=       6.022045E23;                // Número de Avogadro (mol-1)
CREAL_ cte_KNA=      KILO*cte_NA;                // Número de Avogadro (kmol-1)
CREAL_ cte_R=        cte_KNA*cte_kB;             // Constante de gases ideales (J kmol-1 K-1)
CREAL_ cte_c=        2.99792458e8;               // Velocidad de la luz (m s-1)
CREAL_ cte_Kelvin=   273.15;                     // Paso ºC->K
CREAL_ cte_Qe=       1.6021892e-19;              // Carga del electrón (C)
CREAL_ cte_h=        6.626176e-34;               // Constante de Planck (J s)
CREAL_ cte_eps0=     8.854187818e-12;            // Permitividad eléctrica (F m-1)
CREAL_ cte_mu0=      12.5663706144e-7;           // Permeabilidad magnética (H m-1)

// =================================================================================================== FUNCIONES INLINE

template <class T,class U> inline T fn_cast(U &u) { return static_cast<T>(u); }
template <class T> inline T Identidad(const T &x) { return x; }

std::wstring        ToWide(const std::string &str);
inline std::wstring ToWide(const std::wstring &wstr) { return wstr; }
std::string         ToANSI(const std::wstring &wstr);
inline std::string  ToANSI(const std::string &str)   { return str; }
#if defined(_UNICODE)
  typedef std::wstring tstring;
  inline tstring     ToT(const std::string &str)   { return ToWide(str); }
#else
  typedef std::string tstring;
  inline std::string ToT(const std::wstring &wstr) { return ToANSI(wstr); }
#endif // _UNICODE
inline tstring ToT(const tstring &tstr) { return tstr; }

bool FnAlwaysCont();

//template <class T> inline T Minf(T x1,T x2) { return x1<x2 ? x1 : x2; }
template <class T,class U> inline auto Minf(T x1,U x2) ->
  decltype(x1<x2 ? x1 : x2) { return x1<x2 ? x1 : x2; }
//template <class T> inline T Maxf(T x1,T x2) { return x1<x2 ? x2 : x1; }
template <class T,class U> inline auto Maxf(T x1,U x2) ->
  decltype(x1<x2 ? x2 : x1) { return x1<x2 ? x2 : x1; }

template <class T> inline T Hev(T x)              { return x<0 ? T(0) : T(1); }
template <class T> inline T Hev(T x0,T x)         { return Hev(x-x0); }
template <class T> inline T HevArg(T x)           { return x<0 ? T(0) : x; }
template <class T> inline T HevArg(T x0,T x)      { return HevArg(x-x0); }
template <class T> inline T DeltaK(T x1,T x2)     { return x1==x2; }
template <class T> inline T Limita(T x,T x1,T x2) { return x<x1 ? x1 : (x>x2 ? x2 : x); }

// template <class T> inline void Ex(T &x,T &y)  { T z= x; x= y; y= z; }// Intercambia 2 valores
template <class T> inline void Swap(T &x,T &y) { T z= x; x= y; y= z; }

//template <class T> inline std::ostream &
//  WriteGen(std::ostream &os,const T &x) { return os << x; }
//template <class T> inline std::ostream &
//  WriteGen(std::ostream &os,T * const &px) { return os << *px; }
//template <class T> inline std::istream &
//  ReadGen(std::istream &is,T &x) { return is >> x; }
//template <class T> inline std::istream &
//  ReadGen(std::istream &is, T *&px) { return is >> *px; }

// ============================================================================================================= CLASES
// ============================================================================================================== TSwap

template <class T>
class TSwap
{
private: T z;
public: void operator ()(T &x,T &y) { z= x; x= y; y= z; }
};

// ====================================================================================================================
// =========================================================================================================== TVersion

class TVersion

{
private:
  static const int NComp= 7;
  enum { idxbeta, idxsv0, idxsv1, idxsv2, idxv0, idxv1, idxv2 };
  UINT16_ Id[NComp];                             // Dato primitivo
  mutable std::string Cad;                       // Cadena versión

// ·········································································································· Funciones

public:
               TVersion();                       // Constructor
               TVersion(UINT16_ v2,UINT16_ v1,UINT16_ v0) { DefVer(v2,v1,v0); }

  void         DefSubVer(UINT16_ sv2,UINT16_ sv1,UINT16_ sv0)
                 { Id[idxsv0]= sv0; Id[idxsv1]= sv1; Id[idxsv2]= sv2; }
  void         ObtSubVer(UINT16_ &sv2,UINT16_ &sv1,UINT16_ &sv0) const
                 { sv0= Id[idxsv0]; sv1= Id[idxsv1]; sv2= Id[idxsv2]; }
  const std::string &ObtSubVer() const;

  void         DefBeta(UINT16_ beta) { Id[idxbeta]= beta; }
  void         ObtBeta(UINT16_ &beta) const { beta= Id[idxbeta]; }

  void         DefVer(UINT16_ v2,UINT16_ v1,UINT16_ v0)
                 { Id[idxv0]= v0; Id[idxv1]= v1; Id[idxv2]= v2; }
  void         ObtVer(UINT16_ &v2,UINT16_ &v1,UINT16_ &v0) const
                 { v0= Id[idxv0]; v1= Id[idxv1]; v2= Id[idxv2]; }
  const std::string &ObtVer() const;
  const std::string &operator ()() const { return ObtVer(); }
  const std::string &ObtVerEx() const;

  bool         operator <(const TVersion &Version) const;
  bool         operator <=(const TVersion &Version) const;
  bool         operator >(const TVersion &Version) const  { return !operator <=(Version); }
  bool         operator >=(const TVersion &Version) const { return !operator <(Version); }
  bool         operator ==(const TVersion &Version) const;
  bool         operator !=(const TVersion &Version) const { return !operator ==(Version); }

friend std::ostream &operator <<(std::ostream &os,const TVersion &Version);
friend std::istream &operator >>(std::istream &is,TVersion &Version);
};

// ····················································································································

inline std::ostream &operator <<(std::ostream &os,const TVersion &Version)
  { ::Write(os,Version.Id,Version.NComp); return os; }
inline std::istream &operator >>(std::istream &is,TVersion &Version)
  { ::Read(is,Version.Id,Version.NComp); return is; }

// ====================================================================================================================
// =========================================================================================================== TMiembro

template <class T>
class TMiembro

{
private:
  T Dato;

// ·········································································································· Funciones

public:
               operator T() const { return Dato; }
  void         Def(const T &Dato_) { Dato= Dato_; }
};

// ====================================================================================================================
// ============================================================================================================= TXBase

class TXBase

{
protected:
  char MsgDonde[LG_CAD];

public:
  UINT16_ E;                                     // Error

// ·········································································································· Funciones

public:
#if defined(_WINDOWS) || defined(_WIN32)
               TXBase(UINT16_ E_,PCSTR_ MsgDonde_): E(E_) { strcpy_s(MsgDonde,LG_CAD,MsgDonde_); }
               TXBase(const TXBase &XBase): E(XBase.E)    { strcpy_s(MsgDonde,LG_CAD,XBase.MsgDonde); }
#else
               TXBase(UINT16_ E_,PCSTR_ MsgDonde_): E(E_) { strcpy(MsgDonde,MsgDonde_); }
               TXBase(const TXBase &XBase): E(XBase.E)    { strcpy(MsgDonde,XBase.MsgDonde); }
#endif

  virtual PCSTR_ Que() const= 0;
  PCSTR_       Donde() const { return MsgDonde; }

#if defined(_WINDOWS) || defined(_WIN32)
  TXBase       &operator =(const TXBase &XBase)
                 { strcpy_s(MsgDonde,LG_CAD,XBase.MsgDonde); E= XBase.E; return *this; }
#else
  TXBase       &operator =(const TXBase &XBase)
                 { strcpy(MsgDonde,XBase.MsgDonde); E= XBase.E; return *this; }
#endif

  virtual      ~TXBase() {}                      // Destructor
};

// ====================================================================================================================
// ============================================================================================================== TXGen

class TXGen: public TXBase

{
protected:
  char         MsgQue[LG_CAD];

// ·········································································································· Funciones

public:
               TXGen(): TXBase(0,"") {}
               TXGen(UINT16_ E_,PCSTR_ MsgDonde_): TXBase(E_,MsgDonde_) {}

#if defined(_WINDOWS) || defined(_WIN32)
               TXGen(UINT16_ E_,PCSTR_ MsgQue_,PCSTR_ MsgDonde_): TXBase(E_,MsgDonde_)
                 { strcpy_s(MsgQue,LG_CAD,MsgQue_); }
               TXGen(PCSTR_ MsgQue_,PCSTR_ MsgDonde_): TXBase(INT16_(0),MsgDonde_)
                 { strcpy_s(MsgQue,LG_CAD,MsgQue_); }
               TXGen(const TXGen &XGen): TXBase(XGen)
                 { strcpy_s(MsgQue,LG_CAD,XGen.MsgQue); }
#else
               TXGen(UINT16_ E_,PCSTR_ MsgQue_,PCSTR_ MsgDonde_): TXBase(E_,MsgDonde_)
                 { strcpy(MsgQue,MsgQue_); }
               TXGen(PCSTR_ MsgQue_,PCSTR_ MsgDonde_): TXBase(INT16_(0),MsgDonde_)
                 { strcpy(MsgQue,MsgQue_); }
               TXGen(const TXGen &XGen): TXBase(XGen)
                 { strcpy(MsgQue,XGen.MsgQue); }
#endif

  virtual PCSTR_ Que() const { return MsgQue; }

  TXGen        &operator =(const TXGen &XGen)
#if defined(_WINDOWS) || defined(_WIN32)
                 { TXBase::operator =(XGen); strcpy_s(MsgQue,LG_CAD,XGen.MsgQue); return *this; }
#else
                 { TXBase::operator =(XGen); strcpy(MsgQue,XGen.MsgQue); return *this; }
#endif
};

// ====================================================================================================================
// =========================================================================================================== TXSDatos

class TXSDatos: public TXBase

{
private:                                         // Excepción generada por lista
  static PCSTR_ MsgQue[];                        // Mensajes

// ·········································································································· Funciones

public:
               TXSDatos(INT16_ E_,PSTR_ MsgDonde_): TXBase(E_,MsgDonde_) {}
               TXSDatos(INT16_ E_,const std::string &MsgDonde_):
                 TXBase(E_,MsgDonde_.c_str()) {}
               TXSDatos(const TXSDatos &XSDatos): TXBase(XSDatos) {}

  virtual PCSTR_ Que() const { return MsgQue[E]; }

//             ~TXSDatos() {}
};

// ====================================================================================================================
// ============================================================================================================= TDirIP

class TDirIP

{
private:
  UINT32_ IP;
  mutable std::string CadIP;

public:
  void         Def(UINT8_ x3,UINT8_ x2,UINT8_ x1,UINT8_ x0)
                 { IP= DEFBYTE0(x0) | DEFBYTE1(x1) | DEFBYTE2(x2) | DEFBYTE3(x3); }
  void         Def(std::string IPStr);           // Define IP a partir de cadena
  UINT32_      Obt() const { return IP; }        // Obtiene IP
  std::string  ObtStr() const;                   // Obtiene IP en forma de cadena
  std::string  Str() const { return ObtStr(); }  // Obtiene IP en forma de cadena
  PCSTR_       c_str() const;

  TDirIP       &operator =(std::string IPStr)         { Def(IPStr); return *this; }
  bool         operator <(const TDirIP &DirIP) const  { return IP<DirIP.IP; }
  bool         operator ==(const TDirIP &DirIP) const { return IP==DirIP.IP; }
};

#endif  // GBL_H
