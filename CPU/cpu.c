#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define MEM_SIZE 65536

typedef struct {
    uint16_t pc;
    uint16_t psw;
    uint16_t regs[16];
    uint8_t  data_memory[MEM_SIZE];
    uint16_t program_memory[MEM_SIZE];
} CPU;

static inline int16_t sign_extend4(uint16_t imm4) {
    return (imm4 & 0x8) ? (int16_t)(imm4 | 0xFFF0) : (int16_t)(imm4 & 0xF);
}

int execute(CPU *cpu) {
    uint16_t instr = cpu->program_memory[cpu->pc];
    uint8_t opcode = (instr >> 12) & 0xF;
    uint8_t rd     = (instr >> 8) & 0xF;
    uint8_t rs     = (instr >> 4) & 0xF;
    uint8_t rt     = instr & 0xF;
    int16_t imm    = sign_extend4(instr & 0xF);

    switch (opcode) {
        case 0x0:
            cpu->regs[rd] = cpu->regs[rs] + cpu->regs[rt];
            break;
        case 0x2:
            cpu->regs[rd] = cpu->data_memory[cpu->regs[rs] + imm];
            break;
        case 0x3:
            cpu->data_memory[cpu->regs[rs] + imm] = cpu->regs[rd] & 0xFF;
            break;
        case 0x4:
            if (cpu->regs[rd] == cpu->regs[rs]) {
                cpu->pc += imm;
                return 0;
            }
            break;
        case 0xE:
            cpu->pc = instr & 0xFFF;
            return 0;
        default:
            printf("Opcode desconocido: %X\n", opcode);
            return -1;
    }
    cpu->pc++;
    return 1;
}

void dump_memory(CPU *cpu, uint16_t start, uint16_t len) {
    printf("Volcado de memoria de datos desde 0x%04X:\n", start);
    for (int i = 0; i < len; i++) {
        if (i % 16 == 0) printf("0x%04X: ", start + i);
        printf("%02X ", cpu->data_memory[start + i]);
        if (i % 16 == 15) printf("\n");
    }
    if (len % 16 != 0) printf("\n");
}

int load_binary(const char *filename, void *buffer, size_t max_size) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("Error al abrir archivo");
        return 0;
    }
    size_t bytes = fread(buffer, 1, max_size, f);
    fclose(f);
    printf("Cargado '%s': %zu bytes\n", filename, bytes);
    return 1;
}

int main(int argc, char *argv[]) {
    CPU cpu = {0};
    char line[256];
    char cmd[32];
    uint16_t addr, val;
    int reg;

    if (argc >= 2) {
        if (!load_binary(argv[1], cpu.program_memory, sizeof(cpu.program_memory)))
            return 1;
    } else {
        printf("No se especificó archivo de programa (os.obj).\n");
    }
    if (argc >= 3) {
        if (!load_binary(argv[2], cpu.data_memory, sizeof(cpu.data_memory)))
            return 1;
    } else {
        printf("No se especificó archivo de memoria (mem.obj).\n");
    }

    printf("Monitor de CPU (comandos: w, R, G, D, s, h, q)\n");
    printf("PC inicial = 0x%04X\n", cpu.pc);

    while (1) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) continue;

        char *args = line;
        while (*args && !isspace(*args)) args++;
        if (*args) {
            *args = '\0';
            args++;
            while (*args && isspace(*args)) args++;
        } else {
            args = "";
        }

        strcpy(cmd, line);

        if (strcmp(cmd, "w") == 0) {
            if (sscanf(args, "%hx %hx", &addr, &val) == 2) {
                cpu.data_memory[addr] = val & 0xFF;
                printf("M[0x%04X] = 0x%02X\n", addr, cpu.data_memory[addr]);
            } else {
                printf("Uso: w <dir> <valor>\n");
            }
        } else if (strcmp(cmd, "R") == 0) {
            if (sscanf(args, "%d", &reg) == 1 && reg >= 0 && reg < 16) {
                printf("r%d = 0x%04X (%d)\n", reg, cpu.regs[reg], cpu.regs[reg]);
            } else {
                printf("Uso: R <0..15>\n");
            }
        } else if (strcmp(cmd, "G") == 0) {
            if (strlen(args) > 0) {
                if (sscanf(args, "%hx", &addr) == 1) {
                    cpu.pc = addr;
                }
            }
            printf("Ejecutando desde PC=0x%04X...\n", cpu.pc);
            int steps = 0;
            while (steps < 1000) {
                int ret = execute(&cpu);
                if (ret < 0) break;
                steps++;
            }
            printf("Detenido después de %d instrucciones, PC=0x%04X\n", steps, cpu.pc);
        } else if (strcmp(cmd, "D") == 0) {
            if (sscanf(args, "%hx %hx", &addr, &val) == 2) {
                dump_memory(&cpu, addr, val);
            } else {
                printf("Uso: D <dir_inicio> <longitud>\n");
            }
        } else if (strcmp(cmd, "s") == 0) {
            if (strlen(args) > 0) {
                if (sscanf(args, "%hx", &addr) == 1) cpu.pc = addr;
            }
            printf("PC=0x%04X ", cpu.pc);
            int ret = execute(&cpu);
            if (ret >= 0) printf("-> PC=0x%04X\n", cpu.pc);
        } else if (strcmp(cmd, "h") == 0 || strcmp(cmd, "?") == 0) {
            printf("Comandos:\n");
            printf("  w <addr> <val>   : escribir byte en memoria de datos\n");
            printf("  R <reg>          : leer registro (0-15)\n");
            printf("  G [addr]         : ejecutar programa (desde PC o addr)\n");
            printf("  D <start> <len>  : volcar memoria de datos\n");
            printf("  s [addr]         : ejecutar una instrucción (step)\n");
            printf("  h                : esta ayuda\n");
            printf("  q                : salir\n");
        } else if (strcmp(cmd, "q") == 0) {
            break;
        } else {
            printf("Comando desconocido: %s\n", cmd);
        }
    }
    return 0;
}
