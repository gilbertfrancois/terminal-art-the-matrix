ASM="vasmz80_oldstyle"
DIST_DIR="./dist"

# ASM_FLAGS=-Fbin -chklabels -nocase -DDEBUG=1
ASM_FLAGS=-Fbin -chklabels -nocase

all: matrix matrix2

folders:
	mkdir -p ${DIST_DIR}

matrix:
		$(ASM) ${ASM_FLAGS} src/$@.bin.asm -L ${DIST_DIR}/$@.bin.sym -o ${DIST_DIR}/$@.bin

matrix2:
		$(ASM) ${ASM_FLAGS} src/$@.bin.asm -L ${DIST_DIR}/$@.bin.sym -o ${DIST_DIR}/$@.bin

matrix3:
		$(ASM) ${ASM_FLAGS} src/$@.bin.asm -L ${DIST_DIR}/$@.bin.sym -o ${DIST_DIR}/$@.bin

clean:
	rm -rf ${DIST_DIR}/*
