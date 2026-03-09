// KEYBOARD.C
#include "KEYBOARD.H"


unsigned char Keys[256];
/**************************************************************************
 *  kbc_irq_handler                                                       *
 *    handle the interrrupt for the keyboard                              *
 **************************************************************************/

void interrupt ( *old_irq)();

void interrupt kbc_irq_handler()
{
  unsigned char code, state, val = 1;
  disable();
  code = inportb(KBC_PORT);
  state = inportb(KBC_SCP);
  if(code & KBC_BREAK)
  {
    val = 0;
    code -= KBC_BREAK;
  }
  else
  {
    val = 1;
  }
  Keys[code] = val;
  outportb(KBC_SCP, state | SCP_KBC_DIS);
  outportb(KBC_SCP, state);
  outportb(IRQ_PORT, 0x20);
  enable();
}


unsigned char* set_keyboard()
{
    old_irq = getvect(KBC_IRQ);
    setvect(KBC_IRQ, kbc_irq_handler);
    return Keys;
}

void unset_keyboard()
{
    setvect(KBC_IRQ, old_irq);
}