// An attempt to write some assembler support code in C preprocessor MACROS

// Fix endianess of triwords
#define TRIWORD( A, B, C) C;B;A

#define TRYTE( A ) A

#define NOP 000 000 000; 000 000 000; 000 000 000

#define R2MODFORMAT( MOD ) TOP##MOD BOT##MOD

#define INST2( OPCODE, R1, R2, R2MOD, IMM ) \
  TRIWORD( IMM TOP_IMS(IMM), BOT_IMS(IMM) R2 R2MODFORMAT(R2MOD), R1 OPCODE )

#define INST3( OPCODE, R1, R2, R2MOD, R3, R3MOD ) \
  TRIWORD( R3 TOP##R3MOD, BOT##R3MOD R2 R2MODFORMAT(R2MOD), R1 OPCODE )

#define INST1_2IMM( OPCODE, R1, IMM1, IMM2 ) \
  TRIWORD( IMM2 TOP_IMS(IMM2) BOT_IMS(IMM2), IMM1 TOP_IMS(IMM1) BOT_IMS(IMM1), R1 OPCODE )

#define N13    ---
#define N12    --0
#define N11    --+
#define N10    -0-
#define N09    -00
#define N08    -0+
#define N07    -+-
#define N06    -+0
#define N05    -++
#define N04    0--
#define N03    0-0
#define N02    0-+
#define N01    00-
#define ZERO   000
#define P01    00+
#define P02    0+-
#define P03    0+0
#define P04    0++
#define P05    +--
#define P06    +-0
#define P07    +-+
#define P08    +0-
#define P09    +00
#define P10    +0+
#define P11    ++-
#define P12    ++0
#define P13    +++

#define CLOCK  N03
#define FLAGS  N02
#define PC     N01

#define TOP_NEG --
#define TOP_INC --
#define TOP_DEC --
#define TOP_ABN --
#define TOP_ABS --
#define TOP_FLT --
#define TOP_SHR --
#define TOP_NOP 00
#define TOP_SHL --

#define BOT_NEG --
#define BOT_INC -0
#define BOT_DEC -+
#define BOT_ABN 0-
#define BOT_ABS 00
#define BOT_FLT 0+
#define BOT_SHR --
#define BOT_NOP 00
#define BOT_SHL --

// MACRO chicanery to detect Immediate value of 0, this is why Immediate values
// can't contain + or -
#define _CAT( A, B ) A ## B
#define CAT( A, B ) _CAT(A, B)
#define SECOND(a, b, ...) b

#define _POP_(...) SECOND(__VA_ARGS__, 1)

#define _PUSH_0 ~, 0

#define BOOL(A) _POP_( _PUSH_##A )

#define TOP_IMS_0 0
#define BOT_IMS_0 00
#define TOP_IMS_1 n
#define BOT_IMS_1 nn

#define TOP_IMS(A) CAT(TOP_IMS_,BOOL(A))
#define BOT_IMS(A) CAT(BOT_IMS_,BOOL(A))

#define LD1( DST, SRC, MOD,  IMM ) \
  INST2( ------, DST, SRC, MOD, IMM )

#define LD2( DST, SRC, MOD,  IMM ) \
  INST2( -----0, DST, SRC, MOD, IMM )

#define LD3( DST, SRC, MOD,  IMM ) \
  INST2( -----+, DST, SRC, MOD, IMM )

#define ST1( DST, SRC, MOD,  IMM ) \
  INST2( ----0-, DST, SRC, MOD, IMM )

#define ST2( DST, SRC, MOD,  IMM ) \
  INST2( ----00, DST, SRC, MOD, IMM )

#define ST3( DST, SRC, MOD,  IMM ) \
  INST2( ----0+, DST, SRC, MOD, IMM )

#define POP( DST, SRC, MOD,  IMM ) \
  INST2( ----+-, DST, SRC, MOD, IMM )

#define PSH( DST, SRC, MOD,  IMM ) \
  INST2( ----+0, DST, SRC, MOD, IMM )

#define ADC( R1, R2, R2MOD, R3, R3MOD ) \
  INST3( ---0--, R1, R2, R2MOD, R3, R3MOD )

#define ADD( R1, R2, R2MOD, R3, R3MOD ) \
  INST3( ---0-0, R1, R2, R2MOD, R3, R3MOD )

#define ADS( R1, R2, R2MOD, R3, R3MOD ) \
  INST3( ---0-+, R1, R2, R2MOD, R3, R3MOD )

#define ADCI( DST, SRC, MOD,  IMM ) \
  INST2( ---00-, DST, SRC, MOD, IMM )

#define ADDI( DST, SRC, MOD,  IMM ) \
  INST2( ---000, DST, SRC, MOD, IMM )

#define ADSI( R1, IMM1, IMM2 ) \
  INST1_2IMM( ---00+, R1, IMM1, IMM2 )

#define RTL( R1, R2, R2MOD, R3, R3MOD ) \
  INST3( ---+--, R1, R2, R2MOD, R3, R3MOD )

#define TAND( R1, R2, R2MOD, R3, R3MOD ) \
  INST3( ---+-+, R1, R2, R2MOD, R3, R3MOD )

#define TOR TORR
#define TORR( R1, R2, R2MOD, R3, R3MOD ) \
  INST3( ---+0-, R1, R2, R2MOD, R3, R3MOD )

#define TMAJ( R1, R2, R2MOD, R3, R3MOD ) \
  INST3( ---+00, R1, R2, R2MOD, R3, R3MOD )

#define TADD( R1, R2, R2MOD, R3, R3MOD ) \
  INST3( ---+0+, R1, R2, R2MOD, R3, R3MOD )

#define TMUL( R1, R2, R2MOD, R3, R3MOD ) \
  INST3( ---0+-, R1, R2, R2MOD, R3, R3MOD )

#define TMIN( R1, R2, R2MOD, R3, R3MOD ) \
  INST3( ---0+0, R1, R2, R2MOD, R3, R3MOD )

#define TMAX( R1, R2, R2MOD, R3, R3MOD ) \
  INST3( ---0++, R1, R2, R2MOD, R3, R3MOD )

#define RTLI( DST, SRC, MOD,  IMM ) \
  INST2( --0---, DST, SRC, MOD, IMM )

#define TANDI( DST, SRC, MOD,  IMM ) \
  INST2( --0--+, DST, SRC, MOD, IMM )

#define TORI TORRI
#define TORRI( DST, SRC, MOD,  IMM ) \
  INST2( --0-0-, DST, SRC, MOD, IMM )

#define TMAJI( DST, SRC, MOD,  IMM ) \
  INST2( --0-00, DST, SRC, MOD, IMM )

#define TADDI( DST, SRC, MOD,  IMM ) \
  INST2( --0-0+, DST, SRC, MOD, IMM )

#define TMULI( DST, SRC, MOD,  IMM ) \
  INST2( --0-+-, DST, SRC, MOD, IMM )

#define TMINI( DST, SRC, MOD,  IMM ) \
  INST2( --0-+0, DST, SRC, MOD, IMM )

#define TMAXI( DST, SRC, MOD,  IMM ) \
  INST2( --0-++, DST, SRC, MOD, IMM )
