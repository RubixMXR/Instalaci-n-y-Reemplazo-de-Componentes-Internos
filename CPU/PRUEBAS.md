# Caso 1 ADD y SUB

## Descripción: 
Pruebo las instrucciones ADD y SUB del tipo R, verificando que la ALU realiza correctamente las operaciones de suma y resta. Para esto uso números positivos, negativos y combinaciones de ambos, asegurándome de que el resultado en el registro destino sea el esperado.

## Instructiones: 
- ADD $1, $2, $3
- SUB $1, $2, $3

## Precondiciones: 
- Setear R2 = 5 y R3 = 3 para la prueba de ADD.
- Setear R2 = 10 y R3 = 4 para la prueba de SUB.
- Setear R2 = 5 y R3 = -2 para probar SUB con número negativo.
- Setear R2 = 5 y R3 = -3 para probar ADD con número negativo.
- Cargar el código de la instrucción en la dirección 0x00000000.
- Setear el PC a 0x00000000 antes de cada ejecución.

## Code
reset
set r2 5
set r3 3
set [0x00000000] 0x0086101C
set pc 0x00000000
n

reset
set r2 10
set r3 4
set [0x00000000] 0x0086101D
set pc 0x00000000
n

reset
set r2 5
set r3 -2
set [0x00000000] 0x0086101D
set pc 0x00000000
n

reset
set r2 5
set r3 -3
set [0x00000000] 0x0086101C
set pc 0x00000000
n

## Postcondiciones: 
- Visualizar los registros con el comando 'r' después de cada ejecución para verificar el valor de R[1].
- Verificar que el PC avanzó a 0x00000004.
- Revisar que el registro CAUSE sea 0x00000000.

## Conclusiones: 
Las instrucciones de ADD y SUB andan. Llegué a esta conclusión porque en cada prueba el valor de R[1] fue el esperado:
- ADD: 5 + 3 = 8 (0x00000008)
- SUB: 10 - 4 = 6 (0x00000006)
- SUB con negativo: 5 - (-2) = 7 (0x00000007)
- ADD con negativo: 5 + (-3) = 2 (0x00000002)

Además, en todos los casos el PC avanzó correctamente a 0x00000004 y el registro CAUSE se mantuvo en 0, indicando que no hubo excepciones. Las instrucciones funcionan correctamente.

# Caso 2 AND, OR, XOR, NOR

## Descripción: 
Pruebo las instrucciones AND, OR, XOR y NOR del tipo R, verificando que la ALU realiza correctamente las operaciones lógicas bit a bit. Para esto uso números con bits alternados y complementarios, asegurándome de que el resultado en el registro destino sea el esperado.

## Instructiones: 
- AND $1, $2, $3
- OR $1, $2, $3
- XOR $1, $2, $3
- NOR $1, $2, $3

## Precondiciones: 
- Setear R2 = 0xFFFF y R3 = 0x0F0F para la prueba de AND.
- Setear R2 = 0xFF00 y R3 = 0x00FF para la prueba de OR.
- Setear R2 = 0xFFFF y R3 = 0x0F0F para la prueba de XOR.
- Setear R2 = 0xFF00 y R3 = 0x00FF para la prueba de NOR.
- Cargar el código de la instrucción en la dirección 0x00000000.
- Setear el PC a 0x00000000 antes de cada ejecución.

## Code
reset
set r2 0xFFFF
set r3 0x0F0F
set [0x00000000] 0x00861008
set pc 0x00000000
n

reset
set r2 0xFF00
set r3 0x00FF
set [0x00000000] 0x00861009
set pc 0x00000000
n

reset
set r2 0xFFFF
set r3 0x0F0F
set [0x00000000] 0x0086100A
set pc 0x00000000
n

reset
set r2 0xFF00
set r3 0x00FF
set [0x00000000] 0x0086100B
set pc 0x00000000
n

## Postcondiciones: 
- Visualizar los registros con el comando 'r' después de cada ejecución para verificar el valor de R[1].
- Verificar que el PC avanzó a 0x00000004.
- Revisar que el registro CAUSE sea 0x00000000.

## Conclusiones: 
Las instrucciones de AND, OR, XOR y NOR andan. Llegué a esta conclusión porque en cada prueba el valor de R[1] fue el esperado:
- AND: 0xFFFF & 0x0F0F = 0x00000F0F
- OR: 0xFF00 | 0x00FF = 0x0000FFFF
- XOR: 0xFFFF ^ 0x0F0F = 0x0000F0F0
- NOR: ~(0xFF00 | 0x00FF) = 0xFFFF0000

Además, en todos los casos el PC avanzó correctamente a 0x00000004 y el registro CAUSE se mantuvo en 0, indicando que no hubo excepciones. Las instrucciones funcionan correctamente.

# Caso 3 SLT y SLTU

## Descripción: 
Pruebo las instrucciones SLT y SLTU del tipo R, verificando que la ALU realiza correctamente las operaciones de comparación. Para SLT pruebo casos verdaderos y falsos incluyendo números negativos, y para SLTU verifico que trata los números como sin signo dando resultados diferentes a SLT. Me aseguro de que el resultado en el registro destino sea 1 o 0 según corresponda.

## Instructiones: 
- SLT $1, $2, $3
- SLTU $1, $2, $3

## Precondiciones: 
- Setear R2 = 3 y R3 = 5 para probar SLT con caso verdadero.
- Setear R2 = 8 y R3 = 5 para probar SLT con caso falso.
- Setear R2 = -1 y R3 = 0 para probar SLT con números negativos.
- Setear R2 = -1 y R3 = 0 para probar SLTU y ver su comportamiento sin signo.
- Setear R2 = 3 y R3 = 5 para probar SLTU con caso verdadero.
- Cargar el código de la instrucción en la dirección 0x00000000.
- Setear el PC a 0x00000000 antes de cada ejecución.

## Code
reset
set r2 3
set r3 5
set [0x00000000] 0x0086100C
set pc 0x00000000
n

reset
set r2 8
set r3 5
set [0x00000000] 0x0086100C
set pc 0x00000000
n

reset
set r2 -1
set r3 0
set [0x00000000] 0x0086100C
set pc 0x00000000
n

reset
set r2 -1
set r3 0
set [0x00000000] 0x0086100D
set pc 0x00000000
n

reset
set r2 3
set r3 5
set [0x00000000] 0x0086100D
set pc 0x00000000
n

## Postcondiciones: 
- Visualizar los registros con el comando 'r' después de cada ejecución para verificar el valor de R[1].
- Verificar que el PC avanzó a 0x00000004.
- Revisar que el registro CAUSE sea 0x00000000.

## Conclusiones: 
Las instrucciones de SLT y SLTU andan. Llegué a esta conclusión porque en cada prueba el valor de R[1] fue el esperado:
- SLT: 3 < 5 = 1 (0x00000001)
- SLT: 8 < 5 = 0 (0x00000000)
- SLT con negativo: -1 < 0 = 1 (0x00000001)
- SLTU con negativo: 0xFFFFFFFF < 0 = 0 (0x00000000)
- SLTU: 3 < 5 = 1 (0x00000001)

Además, en todos los casos el PC avanzó correctamente a 0x00000004 y el registro CAUSE se mantuvo en 0, indicando que no hubo excepciones. Las instrucciones funcionan correctamente.

# Caso 4 SLL, SRL, SRA, SLLV, SRLV, SRAV

## Descripción: 
Pruebo las instrucciones de desplazamiento del tipo R, verificando que la ALU realiza correctamente las operaciones de shift lógico, aritmético y variable. Para SLL, SRL y SRA uso una cantidad fija de 5 bits de desplazamiento. Para SLLV, SRLV y SRAV la cantidad de desplazamiento está determinada por los 5 bits menos significativos del registro R3. Me aseguro de que el resultado en R4 coincida con el valor esperado en cada caso y de que el shift aritmético preserve correctamente el bit de signo.

## Instrucciones: 
- SLL $0, $2, $4, 5
- SRL $0, $2, $4, 5
- SRA $0, $2, $4, 5
- SLLV $3, $2, $4
- SRLV $3, $2, $4
- SRAV $3, $2, $4

## Precondiciones: 
- Setear R2 = 1 para probar SLL con desplazamiento a izquierda.
- Setear R2 = 0x80000000 para probar SRL y SRA con desplazamiento a derecha de un número con bit de signo en 1.
- Setear R2 = 1 y R3 = 10 para probar SLLV con desplazamiento variable a izquierda.
- Setear R2 = 0x80000000 y R3 = 10 para probar SRLV y SRAV con desplazamiento variable a derecha.
- Cargar el código de la instrucción en la dirección 0x00000000.
- Setear el PC a 0x00000000 antes de cada ejecución.

## Code
reset
set r2 1
set [0x00000000] 0x00044280
set pc 0x00000000
n

reset
set r2 0x80000000
set [0x00000000] 0x00044281
set pc 0x00000000
n

reset
set r2 0x80000000
set [0x00000000] 0x00044282
set pc 0x00000000
n

reset
set r2 1
set r3 10
set [0x00000000] 0x00C44003
set pc 0x00000000
n

reset
set r2 0x80000000
set r3 10
set [0x00000000] 0x00C44004
set pc 0x00000000
n

reset
set r2 0x80000000
set r3 10
set [0x00000000] 0x00C44005
set pc 0x00000000
n

## Postcondiciones: 
- Visualizar los registros con el comando 'r' después de cada ejecución para verificar el valor de R4.
- Verificar que el PC avanzó a 0x00000004.
- Revisar que el registro CAUSE sea 0x00000000.

## Conclusiones: 
Las instrucciones de desplazamiento SLL, SRL, SRA, SLLV, SRLV y SRAV andan. Llegué a esta conclusión porque en cada prueba el valor de R4 fue el esperado:
- SLL: 1 << 5 = 0x00000020
- SRL: 0x80000000 >> 5 = 0x04000000
- SRA: 0x80000000 >>> 5 = 0xFC000000
- SLLV: 1 << 10 = 0x00000400
- SRLV: 0x80000000 >> 10 = 0x00200000
- SRAV: 0x80000000 >>> 10 = 0xFFE00000

El shift lógico introduce ceros por la izquierda, mientras que el shift aritmético preserva el bit de signo extendiéndolo. Las instrucciones variables toman correctamente la cantidad de desplazamiento de los bits [4:0] de R3. Además, en todos los casos el PC avanzó correctamente a 0x00000004 y el registro CAUSE se mantuvo en 0, indicando que no hubo excepciones. Las instrucciones funcionan correctamente.

# Caso 5 ADDI, SLTI, SLTIU

## Descripción: 
Pruebo las instrucciones ADDI, SLTI y SLTIU del tipo I, verificando que la ALU realiza correctamente las operaciones aritméticas con inmediatos y las comparaciones con constantes. Para ADDI pruebo la suma con un inmediato positivo partiendo desde cero y luego una resta con un inmediato negativo. Para SLTI pruebo casos verdaderos y falsos incluyendo números negativos, y para SLTIU verifico que trata los números como sin signo dando un resultado diferente a SLTI cuando el operando es negativo. Me aseguro de que el resultado en R2 coincida con el valor esperado en cada caso.

## Instrucciones: 
- ADDI $zero, $2, 42
- ADDI $2, $2, -10
- SLTI $2, $2, 10
- SLTI $2, $2, 5
- SLTIU $2, $2, 10

## Precondiciones: 
- Setear R2 = 5 para probar SLTI con caso verdadero (5 < 10).
- Setear R2 = 10 para probar SLTI con caso falso (10 < 5).
- Setear R2 = -5 para probar SLTI con número negativo (-5 < 10).
- Setear R2 = -5 para probar SLTIU y ver su comportamiento sin signo (0xFFFFFFFB < 10).
- Setear R2 = 42 antes del ADDI con -10 para verificar la resta.
- Cargar el código de la instrucción en la dirección 0x00000000.
- Setear el PC a 0x00000000 antes de cada ejecución.

## Code
reset
set [0x00000000] 0x0804002A
set pc 0x00000000
n

reset
set r2 42
set [0x00000000] 0x0885FFF6
set pc 0x00000000
n

reset
set r2 5
set [0x00000000] 0xB084000A
set pc 0x00000000
n

reset
set r2 10
set [0x00000000] 0xB0840005
set pc 0x00000000
n

reset
set r2 -5
set [0x00000000] 0xB084000A
set pc 0x00000000
n

reset
set r2 -5
set [0x00000000] 0xB884000A
set pc 0x00000000
n

## Postcondiciones: 
- Visualizar los registros con el comando 'r' después de cada ejecución para verificar el valor de R2.
- Verificar que el PC avanzó a 0x00000004.
- Revisar que el registro CAUSE sea 0x00000000.

## Conclusiones: 
Las instrucciones ADDI, SLTI y SLTIU andan. Llegué a esta conclusión porque en cada prueba el valor de R2 fue el esperado:
- ADDI: 0 + 42 = 42 (0x0000002A)
- ADDI: 42 + (-10) = 32 (0x00000020)
- SLTI: 5 < 10 = 1 (0x00000001)
- SLTI: 10 < 5 = 0 (0x00000000)
- SLTI con negativo: -5 < 10 = 1 (0x00000001)
- SLTIU con negativo: 0xFFFFFFFB < 10 = 0 (0x00000000)

El SLTI trata el inmediato con signo, por lo que -5 < 10 es verdadero. En cambio SLTIU trata ambos como sin signo, por lo que 0xFFFFFFFB (4294967291) no es menor que 10 y el resultado es 0. Además, en todos los casos el PC avanzó correctamente a 0x00000004 y el registro CAUSE se mantuvo en 0, indicando que no hubo excepciones. Las instrucciones funcionan correctamente.

# Caso 6 ANDI, ORI, XORI, LUI

## Descripción: 
Pruebo las instrucciones lógicas con inmediatos del tipo L, verificando que la ALU realiza correctamente las operaciones AND, OR y XOR con constantes, y que el bit h controla correctamente si la operación se aplica sobre la parte baja (h=0) o la parte alta (h=1) del registro. También pruebo LUI para verificar que carga correctamente el inmediato en los 16 bits más significativos del registro destino dejando los 16 bits inferiores en cero. Me aseguro de que el resultado en R2 coincida con el valor esperado en cada caso.

## Instrucciones: 
- LUI $2, 0xABCD
- ORI $2, $2, 0x1234
- ANDI $2, $2, 0xFFFF
- XORI $2, $2, 0xFFFF
- ANDI/H $2, $2, 0xABCD
- ORI/H $2, $2, 0x5678
- XORI/H $2, $2, 0xABCD

## Precondiciones: 
- Setear R2 = 0xABCD0000 antes del ORI para verificar la combinación con la parte baja.
- Setear R2 = 0xABCD1234 antes del ANDI para verificar la máscara de parte baja.
- Setear R2 = 0xABCD1234 antes del XORI para verificar el XOR de parte baja.
- Setear R2 = 0xABCD1234 antes del ANDI/H para verificar la máscara de parte alta.
- Setear R2 = 0x00000000 antes del ORI/H para verificar la inserción en parte alta.
- Setear R2 = 0xABCD1234 antes del XORI/H para verificar el XOR de parte alta.
- Cargar el código de la instrucción en la dirección 0x00000000.
- Setear el PC a 0x00000000 antes de cada ejecución.

## Code
reset
set [0x00000000] 0x3804ABCD
set pc 0x00000000
n

reset
set r2 0xABCD0000
set [0x00000000] 0x28841234
set pc 0x00000000
n

reset
set r2 0xABCD1234
set [0x00000000] 0x2084FFFF
set pc 0x00000000
n

reset
set r2 0xABCD1234
set [0x00000000] 0x3084FFFF
set pc 0x00000000
n

reset
set r2 0xABCD1234
set [0x00000000] 0x2085ABCD
set pc 0x00000000
n

reset
set [0x00000000] 0x28855678
set pc 0x00000000
n

reset
set r2 0xABCD1234
set [0x00000000] 0x3085ABCD
set pc 0x00000000
n

## Postcondiciones: 
- Visualizar los registros con el comando 'r' después de cada ejecución para verificar el valor de R2.
- Verificar que el PC avanzó a 0x00000004.
- Revisar que el registro CAUSE sea 0x00000000.

## Conclusiones: 
Las instrucciones ANDI, ORI, XORI y LUI andan. Llegué a esta conclusión porque en cada prueba el valor de R2 fue el esperado:
- LUI: carga 0xABCD en parte alta → 0xABCD0000
- ORI: 0xABCD0000 | 0x00001234 = 0xABCD1234
- ANDI: 0xABCD1234 & 0x0000FFFF = 0x00001234
- XORI: 0xABCD1234 ^ 0x0000FFFF = 0xABCDEDCB
- ANDI/H: 0xABCD1234 & 0xABCD0000 = 0xABCD0000
- ORI/H: 0x00000000 | 0x56780000 = 0x56780000
- XORI/H: 0xABCD1234 ^ 0xABCD0000 = 0x00001234

El bit h funciona correctamente: cuando h=0 la operación se aplica sobre los 16 bits inferiores (extendiendo el inmediato con ceros a la izquierda), y cuando h=1 la operación se aplica sobre los 16 bits superiores (concatenando el inmediato con ceros a la derecha). LUI carga correctamente el inmediato en la parte alta y deja la parte baja en cero. Además, en todos los casos el PC avanzó correctamente a 0x00000004 y el registro CAUSE se mantuvo en 0, indicando que no hubo excepciones. Las instrucciones funcionan correctamente.

# Caso 7 LW, LH, LHU, LB, LBU

## Descripción: 
Pruebo las instrucciones de carga desde memoria del tipo I, verificando que la CPU lee correctamente palabras, medias palabras y bytes desde la memoria, aplicando la extensión de signo o de cero según corresponda. Para LW verifico la carga de una palabra completa. Para LH y LHU comparo la carga de media palabra con y sin extensión de signo. Para LB y LBU comparo la carga de un byte con y sin extensión de signo, usando diferentes offsets para acceder a bytes específicos. Me aseguro de que el resultado en R3 coincida con el valor esperado en cada caso.

## Instrucciones: 
- LW $2, $3, 0
- LH $2, $3, 0
- LHU $2, $3, 0
- LB $2, $3, 0
- LB $2, $3, 1
- LBU $2, $3, 1

## Precondiciones: 
- Escribir el valor 0xDEADBEEF en la dirección de memoria 0x00000100 para tener un dato conocido con bits variados en cada byte.
- Setear R2 = 0x00000100 como puntero base a la dirección donde está el dato.
- Para LW: probar que carga la palabra completa sin modificar ningún bit.
- Para LH: probar que carga media palabra con extensión de signo (0xBEEF → 0xFFFFBEEF).
- Para LHU: probar que carga media palabra con extensión de cero (0xBEEF → 0x0000BEEF).
- Para LB con offset 0: probar que carga el byte menos significativo con extensión de signo (0xEF → 0xFFFFFFEF).
- Para LB con offset 1: probar que carga el segundo byte con extensión de signo (0xBE → 0xFFFFFFBE).
- Para LBU con offset 1: probar que carga el segundo byte con extensión de cero (0xBE → 0x000000BE).
- Cargar el código de la instrucción en la dirección 0x00000000.
- Setear el PC a 0x00000000 antes de cada ejecución.

## Code
reset
set r2 0x00000100
set [0x00000100] 0xDEADBEEF
set [0x00000000] 0x40860000
set pc 0x00000000
n

reset
set r2 0x00000100
set [0x00000100] 0xDEADBEEF
set [0x00000000] 0x60860000
set pc 0x00000000
n

reset
set r2 0x00000100
set [0x00000100] 0xDEADBEEF
set [0x00000000] 0x68860000
set pc 0x00000000
n

reset
set r2 0x00000100
set [0x00000100] 0xDEADBEEF
set [0x00000000] 0x70860000
set pc 0x00000000
n

reset
set r2 0x00000100
set [0x00000100] 0xDEADBEEF
set [0x00000000] 0x70860001
set pc 0x00000000
n

reset
set r2 0x00000100
set [0x00000100] 0xDEADBEEF
set [0x00000000] 0x78860001
set pc 0x00000000
n

## Postcondiciones: 
- Visualizar los registros con el comando 'r' después de cada ejecución para verificar el valor de R3.
- Verificar que el PC avanzó a 0x00000004.
- Revisar que el registro CAUSE sea 0x00000000.

## Conclusiones: 
Las instrucciones LW, LH, LHU, LB y LBU andan. Llegué a esta conclusión porque en cada prueba el valor de R3 fue el esperado:
- LW: carga la palabra completa 0xDEADBEEF
- LH: carga media palabra con signo 0xBEEF → 0xFFFFBEEF
- LHU: carga media palabra sin signo 0xBEEF → 0x0000BEEF
- LB offset 0: carga byte con signo 0xEF → 0xFFFFFFEF
- LB offset 1: carga byte con signo 0xBE → 0xFFFFFFBE
- LBU offset 1: carga byte sin signo 0xBE → 0x000000BE

Se confirma que la máquina utiliza endianness little-endian, ya que en la dirección base (offset 0) se encuentra el byte menos significativo (0xEF) y en offset 1 el segundo byte (0xBE). La extensión de signo funciona correctamente tanto para media palabra como para byte, replicando el bit más significativo del dato cargado hacia los bits superiores del registro. La extensión de cero simplemente rellena con ceros los bits superiores. Además, en todos los casos el PC avanzó correctamente a 0x00000004 y el registro CAUSE se mantuvo en 0, indicando que no hubo excepciones. Las instrucciones funcionan correctamente.

# Caso 8 SW, SH, SB

## Descripción: 
Pruebo las instrucciones de almacenamiento en memoria del tipo I, verificando que la CPU escribe correctamente palabras, medias palabras y bytes en la memoria. Para SW verifico la escritura de una palabra completa de 32 bits. Para SH verifico que solo modifica los 16 bits inferiores de la dirección de memoria, preservando los 16 bits superiores. Para SB verifico la escritura de un byte usando diferentes offsets para acceder a posiciones específicas, y finalmente combino varias escrituras de byte para armar una palabra completa de 32 bits (0xDEADBEEF). Me aseguro de que el contenido de la memoria coincida con el valor esperado en cada caso. Como el comando `set [direccion] valor` no funciona para modificar la memoria de datos, utilizo SW con R3 = 0x00000000 o 0xFFFFFFFF para limpiar las direcciones antes de cada prueba.

## Instrucciones: 
- SW $2, $3, 0
- SH $2, $3, 0
- SB $2, $3, 0
- SB $2, $3, 1
- SW $2, $3, 4

## Precondiciones: 
- Usar la dirección 0x00000200 como zona de pruebas de memoria.
- Setear R2 = 0x00000200 como puntero base para todos los stores.
- Para SW: guardar 0xCAFE1234 y verificar que la palabra completa se escribe correctamente.
- Para SH: limpiar la dirección con SW escribiendo 0x00000000, luego guardar 0xABCD1234 con SH y verificar que solo se modifican los 16 bits bajos.
- Para SB offset 0: limpiar con SW escribiendo 0xFFFFFFFF, luego guardar 0xAB y verificar que solo se modifica el byte menos significativo.
- Para SB offset 1: limpiar con SW escribiendo 0xFFFFFFFF, luego guardar 0xCD y verificar que se modifica el segundo byte.
- Para SW offset 4: limpiar la dirección 0x00000204 con SW escribiendo 0x00000000, luego guardar 0xBEEF y verificar que se escribe en la dirección correcta.
- Para la prueba combinada: limpiar con SW escribiendo 0x00000000 y luego escribir byte por byte 0xEF, 0xBE, 0xAD, 0xDE en offsets 0, 1, 2 y 3 para formar 0xDEADBEEF.
- Cargar el código de la instrucción en la dirección 0x00000000.
- Setear el PC a 0x00000000 antes de cada ejecución.

## Code
reset
set r2 0x00000200
set r3 0xCAFE1234
set [0x00000000] 0x48860000
set pc 0x00000000
n

reset
set r2 0x00000200
set r3 0x00000000
set [0x00000000] 0x48860000
set pc 0x00000000
n
set r3 0xABCD1234
set [0x00000000] 0x50860000
set pc 0x00000000
n

reset
set r2 0x00000200
set r3 0xFFFFFFFF
set [0x00000000] 0x48860000
set pc 0x00000000
n
set r3 0xAB
set [0x00000000] 0x58860000
set pc 0x00000000
n

reset
set r2 0x00000200
set r3 0xFFFFFFFF
set [0x00000000] 0x48860000
set pc 0x00000000
n
set r3 0xCD
set [0x00000000] 0x58860001
set pc 0x00000000
n

reset
set r2 0x00000200
set r3 0x00000000
set [0x00000000] 0x48860004
set pc 0x00000000
n
set r3 0xBEEF
set [0x00000000] 0x48860004
set pc 0x00000000
n

reset
set r2 0x00000200
set r3 0x00000000
set [0x00000000] 0x48860000
set pc 0x00000000
n
set r3 0xEF
set [0x00000000] 0x58860000
set pc 0x00000000
n
set r3 0xBE
set [0x00000000] 0x58860001
set pc 0x00000000
n
set r3 0xAD
set [0x00000000] 0x58860002
set pc 0x00000000
n
set r3 0xDE
set [0x00000000] 0x58860003
set pc 0x00000000
n

## Postcondiciones: 
- Visualizar la memoria con el comando 'x 0x00000200' después de cada prueba para verificar el valor almacenado.
- Para la prueba de SW offset 4, visualizar con 'x 0x00000204'.
- Verificar que el PC avanzó correctamente después de cada store.
- Revisar que el registro CAUSE sea 0x00000000 después de cada ejecución.

## Conclusiones: 
Las instrucciones SW, SH y SB andan. Llegué a esta conclusión porque en cada prueba el valor en memoria fue el esperado:
- SW: almacena 0xCAFE1234 completo en [0x00000200]
- SH: almacena 0x1234 en los 16 bits bajos de [0x00000200], resultado = 0x00001234
- SB offset 0: almacena 0xAB en el byte menos significativo, resultado = 0xFFFFFFAB
- SB offset 1: almacena 0xCD en el segundo byte, resultado = 0xFFFFCDFF
- SW offset 4: almacena 0xBEEF en [0x00000204], resultado = 0x0000BEEF
- Prueba combinada: las escrituras byte por byte forman correctamente 0xDEADBEEF en [0x00000200]

Se confirma que la máquina utiliza endianness little-endian, ya que el primer byte escrito con SB offset 0 corresponde al byte menos significativo de la palabra. SH modifica únicamente los 16 bits inferiores de la dirección de memoria, preservando el contenido de los 16 bits superiores. SB modifica únicamente el byte apuntado por el offset, sin afectar los bytes adyacentes. El offset de SW y SB funciona correctamente, permitiendo acceder a direcciones desplazadas respecto al puntero base. El PC avanzó correctamente y el registro CAUSE se mantuvo en 0 en todos los casos, indicando que no hubo excepciones. Las instrucciones funcionan correctamente.