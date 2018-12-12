// =================================================================================== TIPOS.H
//
// Este módulo contiene las definiciones de los tipos
//
// =================================================================== 16/12/1995 - 06/10/2010

#if !defined(TIPOS_H)
#define TIPOS_H

#define TIPOS_STD
// #define TIPOS_64
//#define NULL_PTR                                 // Define nullptr

typedef double          REAL_;
typedef const REAL_     CREAL_;
typedef REAL_           *PREAL_;                 // Puntero a reales
typedef const REAL_     *PCREAL_;                // Puntero a reales constantes

typedef signed char     INT8_;
typedef const INT8_     CINT8_;
typedef signed char     *PINT8_;
typedef const INT8_     *PCINT8_;

typedef unsigned char   UINT8_;
typedef const UINT8_    CUINT8_;
typedef unsigned char   *PUINT8_;
typedef const UINT8_    *PCUINT8_;
#if defined(TIPOS_STD) && !defined(BYTE)
typedef UINT8_          BYTE;
#endif

#if defined(_UNICODE)
typedef wchar_t         TCHAR_;
#else
typedef char            TCHAR_;
#endif  // _UNICODE

typedef short           INT16_;                  // Entero corto
typedef const INT16_    CINT16_;
typedef short           *PINT16_;                // Puntero a entero corto
typedef const INT16_    *PCINT16_;

typedef unsigned short  UINT16_;
typedef const UINT16_   CUINT16_;
typedef unsigned short  *PUINT16_;
typedef const UINT16_   *PCUINT16_;
#if defined(TIPOS_STD) && !defined(WORD)
typedef UINT16_         WORD;
#endif  // WORD

typedef long            INT32_;
typedef const INT32_    CINT32_;
typedef long            *PINT32_;
typedef const INT32_    *PCINT32_;

typedef unsigned long   UINT32_;
typedef const UINT32_   CUINT32_;
typedef unsigned long   *PUINT32_;
typedef const UINT32_   *PCUINT32_;
#if defined(TIPOS_STD) && !defined(DWORD)
typedef UINT32_         DWORD;
#endif  // DWORD

#if defined(TIPOS_64)
typedef __int64         INT64_;
typedef const INT64_    CINT64_;
typedef __int64         *PINT64_;
typedef const INT64_    *PCINT64_;

typedef unsigned __int64 UINT64_;
typedef const UINT64_    CUINT64_;
typedef unsigned __int64 *PUINT64_;
typedef const UINT64_    *PCUINT64;
#endif  // TIPOS_64

typedef int             INT_;
typedef const INT_      CINT_;
typedef int             *PINT_;
typedef const INT_      *PCINT_;

typedef unsigned int    UINT_;
typedef const UINT_     CUINT_;
typedef unsigned int    *PUINT_;
typedef const UINT_     *PCUINT_;

typedef char            *PSTR_;                  // Puntero a caracteres
typedef const char      *PCSTR_;                 // Puntero a caracteres constantes

typedef wchar_t         *PWSTR_;                 // Puntero a caracteres unicode
typedef const wchar_t   *PCWSTR_;                // Puntero a caracteres unicode constantes

typedef TCHAR_          *PTSTR_;
typedef const TCHAR_    *PCTSTR_;

typedef void            VOID_;
typedef const void      CVOID_;
typedef void            *PVOID_;
typedef const void      *PCVOID_;

#if defined(NULL_PTR)
  #define nullptr 0
#endif  // NULL_PTR

// ========================================================= MÚLTIPLOS Y SUBMÚLTIPLOS EN EL SI

#define YOCTO 1.0E-24
#define ZEPTO 1.0E-21
#define ATTO  1.0E-18
#define FEMTO 1.0E-15
#define PICO  1.0E-12
#define NANO  1.0E-9
#define MICRO 1.0E-6
#define MILI  1.0E-3
#define CENTI 0.01
#define DECI  0.1
#define DECA  10.0
// #define DIEZ  10.0
#define HECTO 100.0
// #define CIEN  100.0
#define KILO  1000.0
#define MEGA  1.0E6
#define GIGA  1.0E9
#define TERA  1.0E12
#define PETA  1.0E15
#define EXA   1.0E18
#define ZETTA 1.0E21
#define YOTTA 1.0E24

#define KILO_i 1024
#define MEGA_i (KILO_i*KILO_i)
#define GIGA_i (KILO_i*MEGA_i)
#define TERA_i (KILO_i*GIGA_i)
#define PETA_i (KILO_i*TERA_i)

// ==================================================================== CONSTANTES MATEMÁTICAS
#if !defined(_GLIBCXX_CMATH)
#define M_E         2.71828182845904523536
#define M_LOG2E     1.44269504088896340736
#define M_LOG10E    0.434294481903251827651
#define M_LN2       0.693147180559945309417
#define M_LN10      2.30258509299404568402
#define M_PI        3.14159265358979323846
#define M_PI_2      1.57079632679489661923
#define M_PI_4      0.785398163397448309616
#define M_1_PI      0.318309886183790671538
#define M_2_PI      0.636619772367581343076
#define M_1_SQRTPI  0.564189583547756286948
#define M_2_SQRTPI  1.12837916709551257390
#define M_SQRT2     1.41421356237309504880
#define M_SQRT_2    0.707106781186547524401
#endif  // _GLIBCXX_CMATH

// ================================================================== CONSTANTES DE CONVERSIÓN

#define M_24    24
#define M_I24   (1.0/M_24)
#define M_60    60
#define M_I60   (1.0/M_60)
#define M_3600  3600
#define M_I3600 (1.0/M_3600)

#define M_360 360.0
#define M_180 180.0

#define DEG_TO_RAD  (M_PI/M_180)
#define RAD_TO_DEG  (M_180/M_PI)
#define MIN_TO_SEG  M_60
#define SEG_TO_MIN  M_I60
#define HRS_TO_SEG  M_3600
#define SEG_TO_HRS  M_I3600
#define DIA_TO_SEG  (M_24*HRS_TO_SEG)
#define SEG_TO_DIA  (SEG_TO_HRS*M_I24)
#define DIA_TO_HRS  M_24
#define HRS_TO_DIA  M_I24
#define M_DOSPI     (2.0*M_PI)

#define HRS_TO_RAD  (M_PI/12.0)
#define RAD_TO_HRS  (12.0/M_PI)

#define CAL_TO_J 4.1868
#define J_TO_CAL (1.0/CAL_TO_J)

#define EPS0  1.0E-6                             // Error estándar en variables (1.0E-6)
#define FEPS0 1.0E-10                            // Error estándar en función

#define EPS1P (1.0+EPS0)
#define EPS1N (1.0-EPS0)

// =================================================================================== DEFINES

#define LG_INT       8                           // Longitud (en caracteres) de un entero
#define LG_REAL      12                          // Longitud (en caracteres) de un número real
#define LG_REALEXT   25                          // Longitud real extendido (en caracteres)
#define LG_NOMID     20                          // Nombre de identificador
#define LG_IP        17                          // Longitud cadena IP
#define LG_SCAD      80                          // Longitud cadena corta
#define LG_CAD       225                         // Longitud cadena
#define LG_CADK      1023                        // Cadena de 1k

#define LG_INT_1     (LG_INT+1)                  // Longitud (en caracteres) de un entero
#define LG_REAL_1    (LG_REAL+1)                 // Longitud (en caracteres) de un número real
#define LG_REALEXT_1 (LG_REALEXT+1)              // Longitud real extendido (en caracteres)
#define LG_NOMID_1   (LG_NOMID+1)                // Nombre de identificador+1
#define LG_SCAD_1    (LG_SCAD+1)                 // Longitud cadena corta
#define LG_CAD_1     (LG_CAD+1)                  // Longitud cadena
#define LG_CADK_1    (LG_CADK+1)                 // Cadena de 1k

#define DEFBIT(n,x) ((x) << (n))
#define OBTBIT(n,x) (((x) & (1<<(n))) >> (n))

#define OBTBYTE0(x) ((x) & 0x000000FF)
#define OBTBYTE1(x) (((x) & 0x0000FF00) >>  8)
#define OBTBYTE2(x) (((x) & 0x00FF0000) >> 16)
#define OBTBYTE3(x) (((x) & 0xFF000000) >> 24)

#define DEFBYTE0(x) (x)
#define DEFBYTE1(x) ((x) <<  8)
#define DEFBYTE2(x) ((x) << 16)
#define DEFBYTE3(x) ((x) << 24)

#define OBTWORD0(x) ((x) & 0x0000FFFF)
#define OBTWORD1(x) (((x) & 0xFFFF0000) >> 16)

#define DEFWORD0(x) (x)
#define DEFWORD1(x) ((x) << 16)

#endif  // TIPOS_H
