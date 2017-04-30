%DEFINE kernelAddress 0x1000
%DEFINE kernelSector 3   ;1. bootloader, 2. free, not yet implemented
%DEFINE drive 0x80       ;HDD

[BITS 16]                ;16bit code
[ORG 0x7C00]             ;bootloader address

;copy CS to DS and ES, we need to use AX becasue direct write is not allowed
MOV AX, CS
MOV DS, AX
MOV ES, AX

;video mode 80 x 25, 16 colors
MOV AL,03h
MOV AH,0
INT 10h

;no blinking text
MOV AX, 0x1003
MOV BX, 0x0
INT 0x10

;setup segments and stack
cli                ;turn off interupts
xor  ax, ax        ;null segment
mov  ds, ax
mov  es, ax
mov  ax, 0x9000    ;stack from 0x9000 to 0xffff
mov  ss, ax
mov  sp, 0xFFFF
sti                ;turn on interupts

;Hello World message
MOV SI, WelcomeMsg
CALL strPrint

MOV SI, A20
CALL strPrint

MOV ecx,0
dotLoop1:
  mov SI, dot8
	call strPrint
	inc ecx
	cmp ecx, 6
	jne dotLoop1




;Turn on A20 for keyboard
EnableA20_KKbrd_Out:
cli
pusha
      call    wait_cmd
      mov     al,0xAD      ;keyboard off
      out     0x64,al

      call    wait_cmd
      mov     al,0xD0      ;command to read from input
      out     0x64,al

      call    wait_data
      in      al,0x60      ;data from keyboard input is ready
      push    eax          ;store the data

      call    wait_cmd
      mov     al,0xD1      ;command to write to output
      out     0x64,al

      call    wait_cmd
      pop     eax          ;write the same data we received, just modify one bit
      or      al,2         ;set bit 1 to 1 => A20 ON
      out     0x60,al

      call    wait_cmd
      mov     al,0xAE      ;keyboard on
      out     0x64,al

      call    wait_cmd
popa
      sti



CALL printDone

MOV SI, loadSectorStr
CALL strPrint

MOV ecx,0
dotLoop2:
  mov SI, dot8
	call strPrint
	inc ecx
	cmp ecx, 7
	jne dotLoop2

;
;main()
;
resetDrive:
  MOV AH, 0           ;reset
  INT 13h
  OR AH, AH           ;check error code
  JNZ resetDrive      ;repeat until AH != 0

;;;;;;;;;;;;;;;;;;;;;;
;    Load kernel     ;
;;;;;;;;;;;;;;;;;;;;;;
MOV AX, 0
MOV ES, AX
MOV CL, kernelSector
MOV AL, 30             ;IMPORTANT: Number of sectors to be loaded to memory

CALL loadSector
CALL printDone

MOV SI, plzWait
CALL strPrint

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;wait for user to press any key
MOV AH, 0
INT 16h

;Start protected mode
CLI                    ;interupts off
XOR AX, AX             ;AX = 0
MOV DS, AX             ;DS = 0 - needed for lgdt

LGDT [gdtDescriptor]   ;load GDT descriptor

;setup bit0 = 1 in CR0
MOV EAX, CR0
OR EAX, 1
MOV CR0, EAX


JMP 08h:clearPipe      ;far jump to enter 32bit mode

;wait until controller is ready to receive command
wait_cmd:
  in      al,0x64
  test    al,2
  jnz     wait_cmd
  ret

;wait until controller is ready to receive data
wait_data:
  in      al,0x64
  test    al,1
  jz      wait_data
  ret

loadSector:
  MOV BX, kernelAddress
  MOV DL, drive     ;drive
  MOV DH, 0         ;head
  MOV CH, 0         ;track

  ;load in CHS mode
  MOV AH, 2
  INT 0x13
  JC exception
  RET

exception:
  MOV SI, errStr
  CALL strPrint
  JMP resetDrive

;
;echo
;
charPrint:         ;single char print
  MOV AH, 0x0E     ;inform BIOS we are writing one char
  MOV BH, 0x00     ;page number
  MOV BL, 0x0F     ;color
  INT 0x10         ;video interupt
  RET              ;return

strPrint:
nextChar:
  MOV AL, [SI]
  INC SI
  OR AL, AL        ;if(AL == 0)
  JZ exit          ;go to exit
  CALL charPrint
  JMP nextChar
  exit:
  RET

printDone:
  MOV SI, done
  call strPrint
  RET


;data - 10=line feed, 13=carriage return - 10,13 = \n
WelcomeMsg db 'ivebeOS bootloader v0.2', 10, 13, 10, 13, 0
plzWait db 10, 13, 10, 13, 'Press any key...', 10, 13, 0
errStr db 'Sector error', 10, 13, 0
A20 db 'Enable max memory up to 4GB.', 0
loadSectorStr  db 'Kernel loading......', 0
done db 'DONE', 0
dot8 db '........', 0

;GDT
[BITS 32]             ;32-bit mode
clearPipe:
  MOV AX, 10h         ;store data segment identificator
  MOV DS, AX          ;copy valid data segments into data segment register
  MOV SS, AX          ;copy valid data segments into stack segment registar
  MOV ESP, 090000h    ;move stack pointer to 090000h


JMP 08h:01000h

;while(1)
here:
  hlt
  jmp here


gdtStart:
;null segment - mandatory
dq 0

;code segment, read/execute, non-conforming
dw 0FFFFh
dw 0
db 0
db 10011010b
db 11001111b
db 0

;data segment, read/write, expand down
dw 0FFFFh
dw 0
db 0
db 10010010b
db 11001111b
db 0

gdtEnd:

gdtDescriptor:               ;GDT descriptor
  dw gdtEnd - gdtStart - 1   ;size
  dd gdtStart                ;address GDT-a


TIMES 510 - ($ - $$) db 0    ;fill the rest with 0
DW 0xAA55                    ;bootloader signature
