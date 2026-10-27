// ===== ovl_00e3 @ 1ca8:00e3

void ovl_00e3(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  iVar2 = iRam000004f8;
  uVar1 = *(undefined4 *)(*piRam000004fc + 0x5a80);
  *(undefined2 *)(iRam000004f8 + 0x20de) = (int)uVar1;
  *(undefined2 *)(iVar2 + 0x20e0) = (int)((ulong)uVar1 >> 0x10);
  return;
}


// ===== ovl_010a @ 1ca8:010a

void ovl_010a(void)

{
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  G_txtptr = &OV_0x103;
  G_txtptr+2 = 0x1ca8;
  return;
}


// ===== ovl_0137 @ 1ca8:0137

void ovl_0137(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar4;
  int iVar5;
  
  iVar5 = unaff_SI;
  ovl_00e3();
  uVar1 = G_musregptr;
  G_musregptr = G_musregstartptr + 0x50;
  ovl_010a(uVar1);
  OV_0x1e2 = 0;
  G_restarting = 0;
  if (G_screen != 0) {
    EXE_PageFlip();
  }
L_0167:
  EXE_SetScene();
  if (G_curmpg == 'Q') {
    EXE_SetTxtWnd(6);
    ovl_035e();
    G_musregptr = iVar5;
  }
  else {
L_0177:
    do {
      EXE_Menu(6);
      EXE_InitCom(&OV_0x1d5,0x1000,4);
      EXE_SetTxtWnd(1);
      EXE_ClrTxtWnd();
      ovl_03f3();
      do {
        G_animoff = 1;
        uVar3 = EXE_Parser(&G_mnuparms,0);
        if (uVar3 == 0xfd) goto L_0167;
        if (uVar3 == 0xfe) goto L_0177;
        if (uVar3 == 0xffff) {
          G_musregptr = iVar5;
          goto L_0117;
        }
        if (uVar3 == 0) {
          ovl_027b();
          goto L_0167;
        }
        if (uVar3 == 1) {
          ovl_035e();
          if (G_restarting == '\0') goto L_0177;
          G_musregptr = iVar5;
          goto L_0117;
        }
        if (uVar3 == 2) {
          G_musregptr = iVar5;
          goto L_0117;
        }
        bVar4 = uVar3 < 3;
      } while (uVar3 != 3);
      ovl_0232();
    } while (bVar4);
    G_restarting = 0xffff;
    G_musregptr = iVar5;
  }
L_0117:
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd(in_BX);
  uVar2 = OV_0x1de;
  G_txtptr = (int)uVar2;
  G_txtptr+2 = (int)((ulong)uVar2 >> 0x10);
  return;
}


// ===== ovl_0232 @ 1ca8:0232

void ovl_0232(void)

{
  int iVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (OV_0x1e2 == '\0') {
    G_animoff = 1;
    EXE_IModTxt(8);
    iVar1 = EXE_SetYN();
    if (iVar1 != 0) {
      return;
    }
  }
  if ((G_events+19 & 2) == 0) {
    G_animoff = 1;
    EXE_IModTxt(4);
    iVar1 = EXE_SetYN(in_BX);
    if (iVar1 != 0) {
      return;
    }
  }
  return;
}


// ===== ovl_027b @ 1ca8:027b

void ovl_027b(int param_1)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  int in_BX;
  int unaff_SI;
  undefined1 *puVar5;
  int unaff_DI;
  undefined1 *puVar6;
  undefined2 unaff_DS;
  
  do {
    EXE_Menu(4);
    EXE_InitCom(&OV_0x1d5,0x1ca8,9);
    EXE_SetTxtWnd(1);
    EXE_ClrTxtWnd();
    ovl_03f3();
    while( true ) {
      G_animoff = 1;
      uVar3 = EXE_Parser(&G_mnuparms,0);
      if ((uVar3 == 0xfd) || (uVar3 == 0xfe)) break;
      if (uVar3 == 0xffff) {
        return;
      }
      if (uVar3 == 8) {
        return;
      }
      if (uVar3 < 8) {
        G_cursorx = 4;
        G_cursory = 0x68;
        ovl_03f3(uVar3);
        ovl_03f3();
        iVar4 = EXE_WordIn(&G_scrap,0xf);
        if (iVar4 == -1) {
          return;
        }
        if (iVar4 != 0) {
          puVar6 = (undefined1 *)(&G_gnames + param_1 * 0x10);
          puVar5 = (undefined1 *)&G_scrap;
          for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
            puVar2 = puVar6;
            puVar6 = puVar6 + 1;
            puVar1 = puVar5;
            puVar5 = puVar5 + 1;
            *puVar2 = *puVar1;
          }
          EXE_savegnames();
        }
        if (G_curmpg != 4) {
          G_pwinxy = G_winxy;
        }
        (*(code *)*(undefined2 *)(in_BX + 400))();
        OV_0x1e2 = 1;
        return;
      }
    }
  } while( true );
}


// ===== ovl_035e @ 1ca8:035e

void ovl_035e(void)

{
  uint uVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  do {
    EXE_Menu(4);
    EXE_InitCom(&OV_0x1d5,0x1ca8,9);
    EXE_SetTxtWnd(1);
    EXE_ClrTxtWnd();
    ovl_03f3();
    while( true ) {
      G_animoff = 1;
      uVar1 = EXE_Parser(&G_mnuparms,0);
      if ((uVar1 == 0xfd) || (uVar1 == 0xfe)) break;
      if (uVar1 == 0xffff) {
        return;
      }
      if (uVar1 == 8) {
        return;
      }
      if (uVar1 < 8) {
        iVar2 = EXE_RestoreGame(uVar1 + 0x41);
        if (iVar2 != 0) {
          (*(code *)*(undefined2 *)(in_BX + 300))(in_BX);
          G_restarting = 1;
          return;
        }
        G_cursory = 0x68;
        G_cursorx = 4;
        ovl_03f3();
      }
    }
  } while( true );
}


// ===== ovl_03f3 @ 1ca8:03f3

void ovl_03f3(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_PrtWrd((int)G_txtptr,
             (int)((ulong)G_txtptr >> 0x10));
  return;
}


