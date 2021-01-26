#include <inttypes.h>

#define TRITS_PER_WORD 30
#define BITS_PER_TRIT 2
#define BITS_PER_TRIWORD ( TRITS_PER_WORD * BITS_PER_TRIT)
#define N 3
#define TRIWORD_MASK 0x0FFFFFFFFFFFFFFFULL

typedef uint64_t TriWord;

#define PRITRIWORD PRIx64
#define SCNTRIWORD SCNi64

typedef enum TriReg
{
	REG_PC,
	REG_SP,
	REG_ZERO,
	REG_GP00,
	REG_GP01,
	REG_GP02,
	REG_GP03,
	REG_GP04,
	REG_GP05,
	REG_GP06,
	REG_GP07,
	REG_GP08,
	REG_GP09,
	REG_GP10,
	REG_GP11,
	REG_GP12,
	REG_GP13,
	REG_GP14,
	REG_GP15,
	REG_GP16,
	REG_GP17,
	REG_GP18,
	REG_GP19,
	REG_FLAGS,
	REG_CLOCK,
	REG_BASE,
	REG_INST,
	NUM_TRIREGS
} TriReg;

typedef struct {
	TriWord S :2 ;
	TriWord C :2 ;
	TriWord V :2 ;
	TriWord P :2 ;
} TriFlags;

typedef struct TriCpu
{
	TriWord* A;
	TriWord* B;
	TriWord* D;
	TriWord valA;
	TriWord valB;
	TriWord regs[NUM_TRIREGS];
	uint8_t running;
} TriCpu;
