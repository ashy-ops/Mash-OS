[BITS 32]

global LOAD_IDT

LOAD_IDT:
  mov eax,[esp + 4]
  lidt [eax]
  ret