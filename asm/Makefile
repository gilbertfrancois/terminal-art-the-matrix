ASM="vasmz80_oldstyle"
DIST_DIR="./dist"

# ASM_FLAGS=-Fbin -chklabels -nocase -DDEBUG=1
ASM_FLAGS=-Fbin -chklabels -nocase

all: matrixm matrixc

folders:
	mkdir -p ${DIST_DIR}

matrixm:
		$(ASM) ${ASM_FLAGS} src/$@.bin.asm -L ${DIST_DIR}/$@.bin.sym -o ${DIST_DIR}/$@.bin

matrixc:
		$(ASM) ${ASM_FLAGS} src/$@.bin.asm -L ${DIST_DIR}/$@.bin.sym -o ${DIST_DIR}/$@.bin

clean:
	rm -rf ${DIST_DIR}/*
