#include <iostream>
#include <fstream>

using namespace std;

//#pragma pack(push, 1)
//#pragma pack(pop)

#define DECL_ALIGN(x) __declspec( align( x ) )

#define GetClassName( name, align, order )                                      \
  name##_Align_##align##_Order_##order


#define DEFINE_TEST_STRUCTS( ClassName, AlignAmt )                              \
  struct DECL_ALIGN( AlignAmt ) ClassName##_Align_##AlignAmt##_Order_1 {        \
    int   i;                                                                    \
    short s;                                                                    \
    bool  b1;                                                                   \
    bool  b2;                                                                   \
  };                                                                            \
  struct DECL_ALIGN( AlignAmt ) ClassName##_Align_##AlignAmt##_Order_3 {        \
    bool  b1;                                                                   \
    bool  b2;                                                                   \
    short s;                                                                    \
    int   i;                                                                    \
  };                                                                            \
  struct DECL_ALIGN( AlignAmt ) ClassName##_Align_##AlignAmt##_Order_2 {        \
    bool  b2;                                                                   \
    int   i;                                                                    \
    bool  b1;                                                                   \
    short s;                                                                    \
  };

#define DEFINE( ClassName )      \
  DEFINE_TEST_STRUCTS( ClassName, 1 );  \
  DEFINE_TEST_STRUCTS( ClassName, 2 );  \
  DEFINE_TEST_STRUCTS( ClassName, 4 );  \
  DEFINE_TEST_STRUCTS( ClassName, 8 );  \
  DEFINE_TEST_STRUCTS( ClassName, 16 );  

DEFINE( S );

#define PRINT( X ) { cout << X << endl; };

int main(int argc, char** argv)
{
  PRINT( sizeof(GetClassName(S, 1, 1)) );
  PRINT( sizeof(GetClassName(S, 2, 1)) );
  PRINT( sizeof(GetClassName(S, 4, 1)) );
  PRINT( sizeof(GetClassName(S, 8, 1)) );
  PRINT( sizeof(GetClassName(S, 16,1)) );

  PRINT("");
  PRINT( sizeof(GetClassName(S, 1, 2)) );
  PRINT( sizeof(GetClassName(S, 2, 2)) );
  PRINT( sizeof(GetClassName(S, 4, 2)) );
  PRINT( sizeof(GetClassName(S, 8, 2)) );
  PRINT( sizeof(GetClassName(S, 16,2)) );

  PRINT("");
  PRINT( sizeof(GetClassName(S, 1, 3)) );
  PRINT( sizeof(GetClassName(S, 2, 3)) );
  PRINT( sizeof(GetClassName(S, 4, 3)) );
  PRINT( sizeof(GetClassName(S, 8, 3)) );
  PRINT( sizeof(GetClassName(S, 16,3)) );

  return 0;
}
