// ===== ovl_03e2 @ 1ca8:03e2

int ovl_03e2(void)

{
  return iRam000004f8 + 0x1f00;
}


// ===== ovl_0404 @ 1ca8:0404

void ovl_0404(void)

{
  undefined2 *puVar1;
  uint uVar2;
  int iVar3;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 uVar4;
  int unaff_DS;
  undefined1 uVar5;
  bool bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined2 uVar11;
  
  uVar4 = 0x1ca8;
  ovl_03e2();
  if (G_notepadsize == 0) {
    ovl_0922();
    puVar1 = (undefined2 *)(in_BX + 0x178);
    in_BX = 0;
    EXE_PrtWrd(G_comtxtptr);
L_03fb:
    EXE_ClrTxtWnd(uVar4,in_BX);
    return;
  }
L_0429:
  EXE_InitMap(uVar4);
  if (G_curmpg == '\x01') {
    G_crossovlycall = *(int *)(in_BX + 0x14c) + 3;
    G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14e);
    EXE_crossovlycall(uVar4);
  }
  else {
    EXE_FillWindow(uVar4,G_winxy & 0xff,G_winxy >> 8);
  }
L_046a:
  EXE_Menu(uVar4,0x13);
  EXE_InitCom(uVar4,&OV_0x2f4,uVar4,6);
  ovl_06fa();
  while( true ) {
    uVar2 = EXE_Parser(uVar4,&G_mnuparms,0);
    if (uVar2 == 0xffff) {
      uVar2 = 5;
    }
    if (uVar2 == 0xfd) goto L_0429;
    if (uVar2 == 0xfe) goto L_046a;
    if (uVar2 < 2) break;
    bVar6 = uVar2 == 3;
    if (uVar2 < 4) goto code_r0x0001cf43;
    if (uVar2 < 6) {
      if (uVar2 != 5) {
        EXE_InitScrap(uVar4);
        EXE_AddScrap(uVar4,&OV_0x2fa,uVar4,8);
        EXE_PrtScrap(uVar4,0xff);
L_0657:
        ovl_06ab();
        do {
          EXE_Menu(uVar4,7);
          EXE_InitCom(uVar4,&OV_0x2f4,uVar4,4);
          while( true ) {
            G_animoff = 1;
            uVar2 = EXE_Parser(uVar4,&G_mnuparms,0);
            if (uVar2 == 0xffff) goto L_0429;
            if (uVar2 == 0xfd) goto L_0657;
            if (uVar2 == 0xfe) break;
            if (uVar2 < 4) {
              G_e_notelev = (char)uVar2;
              goto L_0429;
            }
          }
        } while( true );
      }
      goto L_03fb;
    }
  }
  if (uVar2 == 1) {
    uVar5 = 0;
    bVar6 = G_noteptr == 0;
    if ((bVar6) || (ovl_076c(), bVar6)) goto L_0429;
    OV_0x108 = 2;
    ovl_0922();
    goto L_09cf;
  }
  bVar6 = G_noteptr == 0;
  EXE_ShowMouse(uVar4);
  if (!bVar6) {
    EXE_Menu(uVar4,2);
    EXE_InitCom(uVar4,&OV_0x2f4,uVar4,1);
    ovl_0922();
    uVar4 = (undefined2)((ulong)G_notepad >> 0x10);
    OV_0x103 =
         *(undefined2 *)((int)G_notepad + G_noteptr);
    OV_0x105 = uVar4;
    EXE_SetTxtWnd(0);
    uVar11 = 0xcfbb;
    ovl_07a0();
    while( true ) {
      uVar4 = 0x1000;
      uVar2 = EXE_ReadKbd(0,in_BX,uVar11);
      if (((uVar2 == 0x1b) || (uVar2 == 0x20)) || (uVar2 == 0xd)) break;
      uVar5 = (undefined1)(uVar2 >> 8);
      if ((uVar2 < 0x31) || (0x39 < uVar2)) {
        uVar2 = CONCAT11((char)uVar2,uVar5);
      }
      else {
        uVar2 = CONCAT11(uVar5,*(undefined1 *)(ulong)(&OV_0x5a7 + (uVar2 & 0xff)));
      }
      if ((0x46 < uVar2) && (uVar2 < 0x52)) {
                    /* WARNING: Could not recover jumptable at 0x0001d00d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (*(code *)(*(int *)((uVar2 - 0x47) * 2 + &OV_0x698) + unaff_DI))();
        return;
      }
    }
  }
  EXE_ShowMouse(uVar4);
  goto L_0429;
code_r0x0001cf43:
  if (!bVar6) {
    if (G_e_printer == '\0') {
      ovl_0922();
      iVar7 = 0;
      EXE_PrtWrd(uVar4,G_comtxtptr,unaff_DS,0,in_BX);
      in_BX = iVar7;
    }
    else {
      uVar5 = 0;
      bVar6 = G_noteptr == 0;
      if ((!bVar6) && (ovl_076c(), !bVar6)) {
        OV_0x108 = 1;
        ovl_0922();
L_09cf:
        OV_0x10d = &OV_0x128;
        OV_0x10f = 0x1000;
        uVar11 = (undefined2)((ulong)G_notepad >> 0x10);
        uVar4 = (undefined2)G_notepad;
        OV_0x109 = uVar4;
        OV_0x10b = uVar11;
        OV_0x111 = uVar4;
        OV_0x2b8 = 0;
        iVar7 = -0x2b81;
        iVar8 = in_BX;
        iVar9 = unaff_DI;
        iVar10 = unaff_SI;
        iVar3 = ovl_0ab0();
        unaff_SI = iVar9;
        if ((bool)uVar5) goto L_0aa8;
        goto L_0a04;
      }
    }
    goto L_0429;
  }
  ovl_076c();
  if (!bVar6) {
    (*(code *)*(undefined2 *)(in_BX + 100))
              (uVar4,(int)G_notepad,
               (int)((ulong)G_notepad >> 0x10),
               G_notepadsize,0);
    G_noteptr = 0;
  }
  goto L_046a;
L_0a04:
  iVar3 = EXE_ReadKbd(0,in_BX,iVar3);
  if ((iVar3 == 0x1b) || (iVar3 == 0x20)) goto L_0aa4;
  ovl_0c75();
  iVar7 = -0x2b56;
  ovl_0d07();
  iVar8 = -0x2b53;
  ovl_0c5a();
  iVar9 = -0x2b50;
  ovl_0b7c();
  iVar10 = -0x2b4d;
  ovl_0bf1();
  ovl_0d24();
  ovl_0c1e();
  ovl_0d24();
  ovl_0d24();
  ovl_0c2d();
  ovl_0d07();
  ovl_0c4b();
  ovl_0d24();
  ovl_0c3c();
  ovl_0b7c();
  ovl_0b7c();
  ovl_0d07();
  ovl_0cac();
  ovl_0b7c();
  ovl_0b7c();
  ovl_0ce3();
  ovl_0b7c();
  iVar3 = *(int *)(OV_0x111 + 2) + OV_0x109;
  if (*(int *)(iVar3 + 2) + OV_0x109 == OV_0x109)
  goto L_0aa4;
  OV_0x111 = iVar3;
  goto L_0a04;
L_0aa4:
  ovl_0b47();
  unaff_SI = iVar9;
L_0aa8:
  unaff_DS = iVar10;
  unaff_DI = iVar8;
  in_BX = iVar7;
  uVar4 = 0x1000;
  goto L_0429;
}


// ===== ovl_06ab @ 1ca8:06ab

void ovl_06ab(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(0);
  EXE_ClrTxtWnd();
  ovl_0957();
  G_cursory = G_cursory + 0x10;
  G_cursorx = G_txtwx;
  ovl_0957();
  G_cursory = (uint)(byte)(G_e_notelev + 4) << 3;
  G_cursorx =
       CONCAT11((char)((uint)G_txtwx >> 8),
                (char)G_txtwx + '\x04');
  EXE_MyCout();
  return;
}


// ===== ovl_06fa @ 1ca8:06fa

void ovl_06fa(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  G_deftxtparms = G_notepadsize;
  EXE_AddScrap(&OV_0x2fa,0x1ca8,1);
  EXE_PrtScrap(0xff);
  EXE_MyRet();
  EXE_InitScrap();
  G_deftxtparms = G_noteptr;
  EXE_AddScrap(&OV_0x2fa,0x1ca8,2);
  EXE_PrtScrap(0xff);
  EXE_MyRet(in_BX);
  return;
}


// ===== ovl_076c @ 1ca8:076c

uint ovl_076c(void)

{
  undefined2 in_AX;
  uint uVar1;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_InitScrap();
  EXE_AddScrap(&OV_0x2fa,0x1ca8,in_AX);
  EXE_PrtScrap(0xff);
  uVar1 = EXE_SetYN(in_BX);
  if (uVar1 != 0xffff) {
    uVar1 = uVar1 ^ 1;
  }
  return uVar1;
}


// ===== ovl_07a0 @ 1ca8:07a0

void ovl_07a0(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  undefined2 uVar5;
  int iVar6;
  undefined2 extraout_DX;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 *puVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  undefined2 unaff_DS;
  uint uVar10;
  
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  puVar7 = (undefined2 *)&G_scrap2;
  uVar3 = OV_0x103;
  puVar4 = (undefined2 *)((int)uVar3 + G_notepad + 0x10);
  for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar2 = puVar7;
    puVar7 = puVar7 + 1;
    puVar1 = puVar4;
    puVar4 = puVar4 + 1;
    *puVar2 = *puVar1;
  }
  *(undefined1 *)puVar7 = 0;
  EXE_AddScrap&G_scrap2;
  EXE_PrtScrap(0xff);
  G_cursorx = G_cursorx + 4;
  uVar10 = *(uint *)((int)OV_0x103 + G_notepad + 0xe);
  EXE_PrtNum(uVar10 & 0xff,in_BX,uVar10);
  EXE_MyCout(0x2c);
  EXE_PrtNum(uVar10 >> 8);
  EXE_MyRet();
  uVar8 = (undefined2)((ulong)OV_0x103 >> 0x10);
  iVar6 = (int)OV_0x103 + G_notepad;
  G_deftxtparms = *(undefined2 *)(iVar6 + 8);
  uVar5 = *(undefined2 *)(iVar6 + 4);
  uVar9 = *(undefined2 *)(unaff_SI + 6);
  *(undefined2 *)(unaff_SI + 6) = *(undefined2 *)(iVar6 + 6);
  EXE_PrtMonth(in_BX,uVar9,uVar5);
  *(undefined2 *)(unaff_SI + 6) = uVar9;
  G_cursorx = G_cursorx + 2;
  EXE_PrtNum(uVar5);
  G_cursorx = G_cursorx + 4;
  uVar9 = (undefined2)((ulong)OV_0x103 >> 0x10);
  iVar6 = (int)OV_0x103 + G_notepad;
  uVar5 = *(undefined2 *)(iVar6 + 10);
  EXE_PrtNum(*(undefined2 *)(iVar6 + 0xc));
  EXE_MyCout(0x3a);
  if ((byte)uVar5 < 10) {
    EXE_MyCout(0x30,in_BX,uVar5);
  }
  EXE_PrtNum(uVar5);
  G_cursorx = G_cursorx + 4;
  ovl_0933();
  EXE_MyRet();
  EXE_MyRet();
  EXE_InitScrap();
  uVar3 = OV_0x103;
  ovl_08f8();
  EXE_AddScrap(extraout_DX,(int)((ulong)uVar3 >> 0x10));
  EXE_PrtScrap();
  return;
}


// ===== ovl_08f8 @ 1ca8:08f8

void ovl_08f8(void)

{
  return;
}


// ===== ovl_0922 @ 1ca8:0922

void ovl_0922(void)

{
  undefined2 in_AX;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap(in_BX,in_AX);
  EXE_AddScrap(&OV_0x2fa,0x1ca8,in_AX);
  EXE_PrtScrap(0xff,in_BX);
  return;
}


// ===== ovl_0957 @ 1ca8:0957

void ovl_0957(void)

{
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_PrtWrd(&OV_0x2fa,0x1ca8);
  return;
}


// ===== ovl_0ab0 @ 1ca8:0ab0

void ovl_0ab0(void)

{
  code *pcVar1;
  undefined2 uVar2;
  int in_CX;
  int in_BX;
  int unaff_DI;
  int unaff_DS;
  int iVar3;
  bool bVar4;
  int iVar5;
  
  if (OV_0x108 == '\x02') {
    bVar4 = false;
    while( true ) {
      iVar5 = in_CX;
      iVar3 = unaff_DS;
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      if (bVar4) break;
      pcVar1 = (code *)swi(0x21);
      in_CX = in_BX;
      (*pcVar1)();
      OV_0x11c = OV_0x11c + '\x01';
      bVar4 = OV_0x11c < 0x39;
      in_BX = iVar3;
      unaff_DS = iVar5;
      if ('9' < (char)OV_0x11c) {
        OV_0x11c = 0x30;
        OV_0x11b = OV_0x11b + '\x01';
        bVar4 = OV_0x11b < 0x39;
        if ('9' < (char)OV_0x11b) {
          OV_0x11b = 0x30;
          OV_0x11a = OV_0x11a + '\x01';
        }
      }
    }
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    OV_0x113 = uVar2;
    if (bVar4) {
      ovl_0922();
      EXE_ReadKbd(0);
    }
  }
  else {
    OV_0x113 = 4;
  }
  OV_0x2b8 = 0;
  OV_0x128 = 0;
  return;
}


// ===== ovl_0b47 @ 1ca8:0b47

void ovl_0b47(void)

{
  code *pcVar1;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (OV_0x108 == '\x02') {
    G_events+19 = G_events+19 | 2;
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
  }
  else {
    OV_0x128 = 0xc;
    OV_0x129 = 0;
    OV_0x2b8 = 1;
    ovl_0bc9();
  }
  return;
}


// ===== ovl_0b7c @ 1ca8:0b7c

void ovl_0b7c(void)

{
  int iVar1;
  code *pcVar2;
  int unaff_DI;
  
  iVar1 = OV_0x2b8;
  *(undefined1 *)(iVar1 + &OV_0x128) = 0xd;
  OV_0x2b8 = OV_0x2b8 + 1;
  *(undefined1 *)(iVar1 + &OV_0x129) = 10;
  OV_0x2b8 = OV_0x2b8 + 1;
  if (OV_0x108 == '\x02') {
    pcVar2 = (code *)swi(0x21);
    (*pcVar2)();
  }
  else {
    ovl_0bc9();
  }
  OV_0x2b8 = 0;
  return;
}


// ===== ovl_0bc9 @ 1ca8:0bc9

void ovl_0bc9(void)

{
  code *pcVar1;
  int iVar2;
  int unaff_DI;
  
  for (iVar2 = 0; iVar2 != OV_0x2b8; iVar2 = iVar2 + 1) {
    pcVar1 = (code *)swi(0x17);
    (*pcVar1)();
  }
  return;
}


// ===== ovl_0bf1 @ 1ca8:0bf1

void ovl_0bf1(void)

{
  ovl_0d24();
  ovl_0d24();
  ovl_0d24();
  return;
}


// ===== ovl_0c1e @ 1ca8:0c1e

void ovl_0c1e(void)

{
  ovl_0db6();
  return;
}


// ===== ovl_0c2d @ 1ca8:0c2d

void ovl_0c2d(void)

{
  ovl_0db6();
  return;
}


// ===== ovl_0c3c @ 1ca8:0c3c

void ovl_0c3c(void)

{
  ovl_0db6();
  return;
}


// ===== ovl_0c4b @ 1ca8:0c4b

void ovl_0c4b(void)

{
  ovl_0db6();
  return;
}


// ===== ovl_0c5a @ 1ca8:0c5a

void ovl_0c5a(void)

{
  ovl_0d37();
  ovl_0d24();
  ovl_0d37();
  return;
}


// ===== ovl_0c75 @ 1ca8:0c75

void ovl_0c75(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int unaff_DI;
  undefined2 unaff_ES;
  
  iVar3 = OV_0x2b8;
  iVar2 = OV_0x111;
  for (iVar1 = 10; (*(char *)(iVar2 + 0x10) != '\0' && (iVar1 != 0)); iVar1 = iVar1 + -1) {
    *(char *)(iVar3 + &OV_0x128) = *(char *)(iVar2 + 0x10);
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + 1;
  }
  OV_0x2b8 = iVar3;
  return;
}


// ===== ovl_0cac @ 1ca8:0cac

void ovl_0cac(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_DI;
  undefined2 unaff_ES;
  
  iVar3 = OV_0x111;
  iVar2 = OV_0x2b8;
  while (iVar4 = iVar2, cVar1 = *(char *)(iVar3 + 0x1a), cVar1 != '\0') {
    *(char *)(iVar4 + &OV_0x128) = cVar1;
    iVar3 = iVar3 + 1;
    iVar2 = iVar4 + 1;
    if (cVar1 == '\r') {
      *(undefined1 *)(iVar4 + 1 + &OV_0x128) = 10;
      iVar2 = iVar4 + 2;
    }
  }
  OV_0x2b8 = iVar4;
  return;
}


// ===== ovl_0ce3 @ 1ca8:0ce3

void ovl_0ce3(void)

{
  int iVar1;
  int iVar2;
  int unaff_DI;
  
  iVar2 = OV_0x2b8;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined1 *)(iVar2 + &OV_0x128) = 0x2d;
    iVar2 = iVar2 + 1;
  }
  OV_0x2b8 = iVar2;
  return;
}


// ===== ovl_0d07 @ 1ca8:0d07

void ovl_0d07(void)

{
  int in_CX;
  int iVar1;
  int unaff_DI;
  
  for (iVar1 = OV_0x2b8; iVar1 < in_CX; iVar1 = iVar1 + 1) {
    *(undefined1 *)(iVar1 + &OV_0x128) = 0x20;
  }
  OV_0x2b8 = iVar1;
  return;
}


// ===== ovl_0d24 @ 1ca8:0d24

void ovl_0d24(void)

{
  int iVar1;
  undefined1 in_AL;
  int unaff_DI;
  
  iVar1 = OV_0x2b8;
  *(undefined1 *)(iVar1 + &OV_0x128) = in_AL;
  OV_0x2b8 = iVar1 + 1;
  return;
}


// ===== ovl_0d37 @ 1ca8:0d37

undefined4 ovl_0d37(void)

{
  byte in_AL;
  uint uVar1;
  undefined2 in_CX;
  uint uVar2;
  undefined2 in_DX;
  int unaff_DI;
  
  OV_0x107 = 0;
  uVar2 = (uint)in_AL;
  uVar1 = (uint)(in_AL / 100);
  if (*(char *)(&OV_0x2ea + uVar1) != '0') {
    OV_0x107 = 1;
    ovl_0d24();
  }
  uVar2 = uVar2 + (uVar1 & 0xff) * -100;
  uVar1 = uVar2 / 10 & 0xff;
  if ((OV_0x107 == '\x01') || (*(char *)(&OV_0x2ea + uVar1) != '0')) {
    OV_0x107 = 1;
    ovl_0d24(uVar1);
  }
  ovl_0d24(uVar2 + (uVar1 & 0xff) * -10);
  return CONCAT22(in_CX,in_DX);
}


// ===== ovl_0db6 @ 1ca8:0db6

undefined4 ovl_0db6(void)

{
  byte in_AL;
  uint uVar1;
  undefined2 in_CX;
  uint uVar2;
  undefined2 in_DX;
  int unaff_DI;
  int iVar3;
  
  OV_0x107 = 0;
  uVar2 = (uint)in_AL;
  iVar3 = 0;
  if (OV_0x2ea != '0') {
    OV_0x107 = 1;
    ovl_0d24();
  }
  uVar2 = uVar2 + iVar3 * -10000;
  uVar1 = uVar2 / 1000;
  if ((OV_0x107 == '\x01') || (*(char *)(&OV_0x2ea + uVar1) != '0')) {
    OV_0x107 = 1;
    ovl_0d24();
  }
  uVar2 = uVar2 + uVar1 * -1000;
  uVar1 = uVar2 / 100 & 0xff;
  if ((OV_0x107 == '\x01') || (*(char *)(&OV_0x2ea + uVar1) != '0')) {
    OV_0x107 = 1;
    ovl_0d24();
  }
  uVar2 = uVar2 + (uVar1 & 0xff) * -100;
  uVar1 = uVar2 / 10 & 0xff;
  if ((OV_0x107 == '\x01') || (*(char *)(&OV_0x2ea + uVar1) != '0')) {
    OV_0x107 = 1;
    ovl_0d24(uVar1);
  }
  ovl_0d24(uVar2 + (uVar1 & 0xff) * -10);
  return CONCAT22(in_CX,in_DX);
}


