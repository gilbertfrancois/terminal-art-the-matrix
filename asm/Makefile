ASM="vasmz80_oldstyle"
DIST_DIR="./dist"

# ASM_FLAGS=-Fbin -chklabels -nocase -DDEBUG=1
ASM_FLAGS=-Fbin -chklabels -nocase

all:  matrix

folders:
	mkdir -p ${DIST_DIR}

matrix:
		$(ASM) ${ASM_FLAGS} src/$@.bin.asm -L ${DIST_DIR}/$@.bin.sym -o ${DIST_DIR}/$@.bin
		$(ASM) ${ASM_FLAGS} src/$@.dos.asm -L ${DIST_DIR}/$@.dos.sym -o ${DIST_DIR}/$@.com

clean:
	rm -rf ${DIST_DIR}/*
