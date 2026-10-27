// ===== ovl_0fe9 @ 1ca8:0fe9

void ovl_0fe9(void)

{
  int iVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_1011();
  G_failcause = 0;
  ovl_1062();
  if (G_failcause == 0) {
    iVar1 = ovl_1029();
    if (iVar1 != 0) {
      G_failcause = 0xf0;
    }
  }
  return;
}


// ===== ovl_1011 @ 1ca8:1011

int __cdecl16near ovl_1011(void)

{
  return iRam000004f8 + -0x100;
}


// ===== ovl_1029 @ 1ca8:1029

void ovl_1029(void)

{
  int iVar1;
  int in_BX;
  int iVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar2 = 0;
  iVar1 = 0xd;
  do {
    *(undefined1 *)(iVar2 + &G_wrkstr) = *(undefined1 *)(iVar2 + &OV_0x8b1);
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  G_wrkamt = 0xbf;
  (*(code *)*(undefined2 *)(in_BX + 4))
            (0x1000,&G_startcfdta,&G_wrkstr,&G_wrkamt);
  return;
}


// ===== ovl_1062 @ 1ca8:1062

void ovl_1062(undefined2 param_1,int param_2,undefined2 param_3,int param_4,int param_5)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  code *pcVar3;
  char cVar4;
  undefined2 uVar5;
  int iVar6;
  int unaff_BP;
  undefined1 *puVar7;
  undefined1 *puVar8;
  undefined2 unaff_DS;
  
  pcVar3 = (code *)swi(0x11);
  uVar5 = (*pcVar3)();
  *(undefined2 *)(unaff_BP + 0x8be) = uVar5;
  puVar8 = (undefined1 *)(unaff_BP + 0x8c0);
  puVar7 = (undefined1 *)0xfff5;
  for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar2 = puVar8;
    puVar8 = puVar8 + 1;
    puVar1 = puVar7;
    puVar7 = puVar7 + 1;
    *puVar2 = *puVar1;
  }
  *puVar8 = puVar7[1];
  pcVar3 = (code *)swi(0x21);
  uVar5 = (*pcVar3)();
  *(undefined2 *)(param_2 + 0x8c9) = uVar5;
  if ((byte)uVar5 < 2) {
    *(undefined2 *)0x2b18 = 0xff;
    return;
  }
  if (2 < (byte)uVar5) {
    pcVar3 = (code *)swi(0x21);
    (*pcVar3)();
    cVar4 = '\0';
    pcVar3 = (code *)swi(0x33);
    (*pcVar3)();
    if (cVar4 != '\0') {
      *(undefined1 *)(param_2 + 0x8cb) = 1;
      goto L_10e3;
    }
  }
  *(undefined1 *)(param_2 + 0x8cb) = 0;
L_10e3:
  pcVar3 = (code *)swi(0x10);
  cVar4 = (*pcVar3)();
  *(char *)(param_4 + 0x8cc) = cVar4;
  if (cVar4 == '\a') {
    *(undefined2 *)(param_5 + 0x2b18) = 0xfe;
    return;
  }
  *(undefined1 *)(param_4 + 0x8cd) = 0;
  return;
}


// ===== FUN_1000_db87 @ 1000:db87

void __cdecl16far FUN_1000_db87(int param_1)

{
  int *piVar1;
  undefined1 uVar2;
  int iVar3;
  undefined2 uVar4;
  int iVar5;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  int *piVar6;
  undefined2 unaff_DS;
  
  if (param_1 != 0) {
    ovl_1011();
  }
  uVar2 = G_e_inpdev;
  G_e_inpdev = 0;
  EXE_LoadAlphabet(0x1ca8);
  ovl_2c48();
  G_suppresstext = 0;
  G_curmap = 0x7fff;
  G_svdtalth = 0x2a57;
  G_lookprt = 1;
  G_p07flg = 0;
  G_swcamp = 0;
  G_buf2dgt = 0;
  G_kmhero = 0xff;
  piVar6 = (int *)&G_heroptr;
  iVar5 = 6;
  iVar3 = &G_member0;
  do {
    piVar1 = piVar6;
    piVar6 = piVar6 + 1;
    *piVar1 = iVar3;
    iVar3 = iVar3 + 0xdc;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  G_screen = 0;
  if (G_e_display == '\x04') {
    G_tilebkgd = 2;
    G_txtbkgd = 7;
    ovl_2cde();
    G_mtileary = G_mtileary + 0x206;
    G_egadrawcode = 0;
    G_screen+2 = 0xa000;
    G_oppscr = 0x4000;
    G_oppscr+2 = 0xa000;
    G_egamask = 0xff;
    ovl_1469();
    ovl_1343();
    ovl_1469();
  }
  else if (G_e_display < 2) {
    G_tilebkgd = 0;
    G_txtbkgd = 0xff;
    EXE_graphmode(0x1ca8,4);
    EXE_graphbackground(0x1ca8,0);
    EXE_palette(0x1ca8,3);
    EXE_textcolor(0x1ca8,3);
    G_screen+2 = 0xb800;
    G_oppscr = G_scrbuf;
    G_oppscr+2 = G_scrbuf+2;
    EXE_fillYofstbl(0x1ca8,&G_yofstbl);
    ovl_13c2();
    ovl_1343();
    ovl_13c2();
  }
  else if (G_e_display == 2) {
    G_tilebkgd = 2;
    G_txtbkgd = 7;
    EXE_graphmode(0x1ca8,0xd);
    EXE_fillEGAYofstbl(0x1ca8,&G_yofstbl);
    G_egadrawcode = 0;
    G_screen+2 = 0xa000;
    G_oppscr = 0x2000;
    G_oppscr+2 = 0xa000;
    G_egamask = 0xff;
    ovl_14ff();
    ovl_1343();
    ovl_14ff();
  }
  else {
    G_tilebkgd = 2;
    G_txtbkgd = 0x77;
    EXE_graphmode(0x1ca8,9);
    EXE_fillT1KYofstbl(0x1ca8,&G_yofstbl);
    G_screen+2 = 0xb800;
    G_oppscr = G_scrbuf;
    G_oppscr+2 = G_scrbuf+2;
    ovl_1428();
    ovl_1343();
    ovl_1428();
  }
  G_txtptr = &OV_0x115;
  G_txtptr+2 = 0x1ca8;
  G_txtwx = 1;
  G_mnuwx = 1;
  G_cursorx = 1;
  G_txtwy = 0x72;
  G_mnuwy = 0x72;
  G_cursory = 0x72;
  uVar4 = 0x12;
  if (G_e_display == '\x02') {
    uVar4 = 0x14;
  }
  G_txtww = uVar4;
  G_mnuww = uVar4;
  G_txtwh = 0x28;
  G_mnuwh = 0x28;
  EXE_IModTxt(0x1ca8,0);
  G_animoff = 1;
  G_e_inpdev = uVar2;
  EXE_ShowMouse(0x1ca8);
  EXE_PrtWrd(0x1ca8,G_comtxtptr);
  EXE_ClrTxtWnd(0x1ca8,in_BX);
  return;
}


// ===== ovl_1343 @ 1ca8:1343

void __cdecl16near ovl_1343(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_song(0x1ca8,1);
  EXE_delay(0x1ca8,0x5dc);
  EXE_finishsong(0x1ca8,in_BX);
  return;
}


// ===== FUN_1000_dde0 @ 1000:dde0

void __cdecl16far FUN_1000_dde0(void)

{
  ovl_1011();
  ovl_1373();
  return;
}


// ===== ovl_1373 @ 1ca8:1373

void __cdecl16near ovl_1373(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_e_display < 2) {
    ovl_13c2();
  }
  else if (G_e_display == 2) {
    ovl_14ff();
  }
  else if (G_e_display == '\x04') {
    ovl_1469();
  }
  else {
    ovl_1428();
  }
  return;
}


// ===== ovl_1398 @ 1ca8:1398

void __cdecl16near ovl_1398(void)

{
  byte *pbVar1;
  byte bVar2;
  byte *pbVar3;
  uint uVar4;
  int in_DX;
  int unaff_SI;
  byte *pbVar5;
  byte *pbVar6;
  byte *pbVar7;
  undefined2 uVar8;
  undefined2 unaff_DS;
  undefined2 uVar9;
  
  uVar8 = (undefined2)((ulong)G_scrbuf >> 0x10);
  pbVar7 = (byte *)(byte *)G_scrbuf;
  uVar9 = (undefined2)((ulong)G_lvarbuf >> 0x10);
  pbVar5 = (byte *)(byte *)G_lvarbuf;
  do {
    pbVar6 = pbVar5 + 1;
    uVar4 = *pbVar5 & 0xff7f;
    in_DX = in_DX - uVar4;
    if ((*pbVar5 & 0x80) == 0) {
      pbVar1 = pbVar6;
      pbVar6 = pbVar5 + 2;
      bVar2 = *pbVar1;
      for (; uVar4 != 0; uVar4 = uVar4 - 1) {
        pbVar1 = pbVar7;
        pbVar7 = pbVar7 + 1;
        *pbVar1 = bVar2;
      }
    }
    else {
      for (; uVar4 != 0; uVar4 = uVar4 - 1) {
        pbVar3 = pbVar7;
        pbVar7 = pbVar7 + 1;
        pbVar1 = pbVar6;
        pbVar6 = pbVar6 + 1;
        *pbVar3 = *pbVar1;
      }
    }
    pbVar5 = pbVar6;
  } while (in_DX != 0);
  return;
}


// ===== ovl_13c2 @ 1ca8:13c2

void __cdecl16near ovl_13c2(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined1 in_AL;
  undefined2 *puVar3;
  int iVar4;
  int in_BX;
  int iVar5;
  int unaff_SI;
  int unaff_DI;
  undefined2 *puVar6;
  undefined2 uVar7;
  undefined2 unaff_DS;
  undefined2 uVar8;
  
  OV_0x897 = in_AL;
  iVar5 = 0;
  iVar4 = 0xe;
  do {
    *(undefined1 *)(iVar5 + &G_filestr) = *(undefined1 *)(iVar5 + &OV_0x893);
    iVar5 = iVar5 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  EXE_readfile(&G_filestr,(int)G_lvarbuf,
             (int)((ulong)G_lvarbuf >> 0x10),0xf000,0xff);
  ovl_1398();
  uVar7 = (undefined2)((ulong)G_screen >> 0x10);
  puVar6 = (undefined2 *)(undefined2 *)G_screen;
  uVar8 = (undefined2)((ulong)G_scrbuf >> 0x10);
  puVar3 = (undefined2 *)(undefined2 *)G_scrbuf;
  iVar4 = 100;
  do {
    for (iVar5 = 0x28; iVar5 != 0; iVar5 = iVar5 + -1) {
      puVar2 = puVar6;
      puVar6 = puVar6 + 1;
      puVar1 = puVar3;
      puVar3 = puVar3 + 1;
      *puVar2 = *puVar1;
    }
    puVar6 = puVar6 + 0xfd8;
    for (iVar5 = 0x28; iVar5 != 0; iVar5 = iVar5 + -1) {
      puVar2 = puVar6;
      puVar6 = puVar6 + 1;
      puVar1 = puVar3;
      puVar3 = puVar3 + 1;
      *puVar2 = *puVar1;
    }
    puVar6 = puVar6 + -0x1000;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}


// ===== ovl_1428 @ 1ca8:1428

void __cdecl16near ovl_1428(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  int unaff_SI;
  undefined2 *puVar6;
  undefined2 uVar7;
  undefined2 unaff_DS;
  undefined2 uVar8;
  
  ovl_14ff();
  uVar7 = (undefined2)((ulong)G_screen >> 0x10);
  puVar6 = (undefined2 *)(undefined2 *)G_screen;
  uVar8 = (undefined2)((ulong)G_scrbuf >> 0x10);
  puVar3 = (undefined2 *)(undefined2 *)G_scrbuf;
  iVar4 = 0x32;
  do {
    for (iVar5 = 0x50; iVar5 != 0; iVar5 = iVar5 + -1) {
      puVar2 = puVar6;
      puVar6 = puVar6 + 1;
      puVar1 = puVar3;
      puVar3 = puVar3 + 1;
      *puVar2 = *puVar1;
    }
    puVar6 = puVar6 + 0xfb0;
    for (iVar5 = 0x50; iVar5 != 0; iVar5 = iVar5 + -1) {
      puVar2 = puVar6;
      puVar6 = puVar6 + 1;
      puVar1 = puVar3;
      puVar3 = puVar3 + 1;
      *puVar2 = *puVar1;
    }
    puVar6 = puVar6 + 0xfb0;
    for (iVar5 = 0x50; iVar5 != 0; iVar5 = iVar5 + -1) {
      puVar2 = puVar6;
      puVar6 = puVar6 + 1;
      puVar1 = puVar3;
      puVar3 = puVar3 + 1;
      *puVar2 = *puVar1;
    }
    puVar6 = puVar6 + 0xfb0;
    for (iVar5 = 0x50; iVar5 != 0; iVar5 = iVar5 + -1) {
      puVar2 = puVar6;
      puVar6 = puVar6 + 1;
      puVar1 = puVar3;
      puVar3 = puVar3 + 1;
      *puVar2 = *puVar1;
    }
    puVar6 = puVar6 + -0x3000;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}


// ===== ovl_1469 @ 1ca8:1469

void __cdecl16near ovl_1469(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined1 in_AL;
  int iVar3;
  undefined2 *puVar4;
  int in_BX;
  int iVar5;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x8ab = in_AL;
  iVar5 = 0;
  iVar3 = 0xe;
  do {
    *(undefined1 *)(iVar5 + &G_filestr) = *(undefined1 *)(iVar5 + &OV_0x8a7);
    iVar5 = iVar5 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  EXE_readfile(&G_filestr,(int)G_lvarbuf,
             (int)((ulong)G_lvarbuf >> 0x10),0xf000,0xff);
  ovl_1398();
  puVar2 = (undefined2 *)G_lvarbuf;
  puVar4 = (undefined2 *)puVar2;
  for (iVar3 = 0x180; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar1 = puVar4;
    puVar4 = puVar4 + 1;
    *puVar1 = 0;
  }
  EXE_VGAPalette((int)G_lvarbuf,
             (int)((ulong)G_lvarbuf >> 0x10));
  G_scrbuf = G_scrbuf + 0x300;
  EXE_buftoscr(0,0,0x50,200);
  G_scrbuf = G_scrbuf + -0x300;
  EXE_VGAFadeIn(G_lvarbuf,G_lvarbuf+2,
             G_scrbuf,G_scrbuf+2,in_BX);
  return;
}


// ===== ovl_14ff @ 1ca8:14ff

int __cdecl16near ovl_14ff(void)

{
  undefined1 in_AL;
  int iVar1;
  int iVar2;
  int in_BX;
  int iVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x8a1 = in_AL;
  iVar3 = 0;
  iVar1 = 0xe;
  do {
    *(undefined1 *)(iVar3 + &G_filestr) = *(undefined1 *)(iVar3 + &OV_0x89d);
    iVar3 = iVar3 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  EXE_readfile(&G_filestr,(int)G_lvarbuf,
             (int)((ulong)G_lvarbuf >> 0x10),0xf000,0xff);
  iVar1 = ovl_1398();
  if (G_e_display != '\x02') {
    return iVar1;
  }
  iVar1 = 0;
  do {
    iVar2 = iVar1 * 2 + 1;
    iVar3 = iVar2;
    do {
      ovl_158b();
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    iVar2 = iVar3;
    do {
      ovl_158b();
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    iVar3 = iVar2;
    do {
      ovl_158b();
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    do {
      iVar2 = ovl_158b();
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    iVar1 = iVar1 + 1;
  } while (iVar1 != 6);
  return iVar2 + -8;
}


// ===== ovl_158b @ 1ca8:158b

undefined4 __cdecl16near ovl_158b(void)

{
  undefined2 in_AX;
  undefined2 in_DX;
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_buftoscr(0x1ca8);
  return CONCAT22(in_DX,in_AX);
}


// ===== ovl_15ac @ 1ca8:15ac

undefined1 ovl_15ac(void)

{
  uint uVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_1011();
  G_member0 = 0;
  ovl_160a();
  EXE_Menu(0x1ca8,0);
  EXE_InitCom(0x1ca8,&OV_0x8ce,0x1ca8,4);
  do {
    G_animoff = 1;
    uVar1 = EXE_Parser(0x1ca8,&G_mnuparms,0);
  } while (3 < uVar1);
  if (G_screen != 0) {
    EXE_PageFlip(0x1ca8,in_BX);
  }
  return G_mnusel;
}


// ===== ovl_160a @ 1ca8:160a

void ovl_160a(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_MyRet(0x1ca8);
  EXE_MyRet(0x1ca8);
  EXE_MyRet(0x1ca8);
  EXE_MyRet(0x1ca8,in_BX);
  return;
}


// ===== FUN_1000_f3e4 @ 1000:f3e4

undefined2 __cdecl16near FUN_1000_f3e4(void)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  undefined2 in_CX;
  int iVar4;
  undefined2 in_DX;
  byte *pbVar5;
  byte bVar6;
  int unaff_DI;
  byte *pbVar7;
  undefined2 unaff_DS;
  bool bVar8;
  byte local_6;
  byte bStack_5;
  byte local_4;
  
  bVar6 = (byte)((uint)in_DX >> 8);
  pbVar5 = (byte *)(OV_0x8e0 + 0x2b);
  bVar8 = pbVar5 == (byte *)0x0;
  bVar2 = bVar6;
  do {
    iVar4 = 0x28;
    pbVar7 = pbVar5;
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pbVar1 = pbVar7;
      pbVar7 = pbVar7 + 1;
      bVar8 = bVar2 == *pbVar1;
    } while (!bVar8);
    local_4 = (byte)in_DX;
    local_6 = (byte)in_CX;
    bStack_5 = (byte)((uint)in_CX >> 8);
    if (bVar8) goto L_29b3;
    bVar2 = bVar2 - 1;
    bVar8 = bVar2 == local_4;
  } while (local_4 <= bVar2);
  bVar8 = bStack_5 == 0;
  bVar3 = bStack_5;
  bVar2 = 0;
  if (!bVar8) {
    do {
      iVar4 = 0x28;
      pbVar7 = pbVar5;
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        pbVar1 = pbVar7;
        pbVar7 = pbVar7 + 1;
        bVar8 = bVar3 == *pbVar1;
      } while (!bVar8);
      bVar2 = bVar3;
      if (bVar8) break;
      bVar3 = bVar3 - 1;
      bVar8 = bVar3 == local_6;
      bVar2 = 0;
    } while (local_6 <= bVar3);
  }
L_29b3:
  do {
    if (*(char *)((uint)bVar6 + &OV_0x21ff) != '\0') {
      if ((bVar2 < local_6) || (bStack_5 < bVar2)) goto L_29ee;
      goto L_29f2;
    }
    bVar6 = bVar6 - 1;
  } while (local_4 <= bVar6);
  if ((bVar2 == 0) || ((local_6 <= bVar2 && (bVar2 <= bStack_5)))) {
    do {
      bVar6 = bStack_5;
      if (*(char *)((uint)bStack_5 + &OV_0x21ff) != '\0') goto L_29ee;
      bStack_5 = bStack_5 - 1;
    } while (local_6 <= bStack_5);
  }
L_29f4:
  return CONCAT11(bVar2,bVar2);
L_29ee:
  if (bVar2 <= bVar6) {
L_29f2:
    bVar2 = bVar6;
  }
  goto L_29f4;
}


// ===== ovl_2c48 @ 1ca8:2c48

void __cdecl16near ovl_2c48(void)

{
  code *pcVar1;
  char cVar2;
  uint uVar3;
  int in_CX;
  undefined2 extraout_DX;
  undefined2 extraout_DX_00;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined4 uVar4;
  undefined2 uVar5;
  
  do {
    do {
      do {
        pcVar1 = (code *)swi(0x1a);
        cVar2 = (*pcVar1)();
      } while (cVar2 != '\0');
      OV_0x2d3a = extraout_DX;
      OV_0x2d3c = in_CX;
      pcVar1 = (code *)swi(0x1a);
      uVar4 = (*pcVar1)();
      uVar5 = (undefined2)uVar4;
    } while ((char)uVar4 != '\0');
    OV_0x2d3e = (int)((ulong)uVar4 >> 0x10);
    OV_0x2d40 = in_CX;
    in_CX = OV_0x2d46;
    do {
      ovl_2cd6(uVar5);
      in_CX = in_CX + -1;
    } while (in_CX != 0);
    pcVar1 = (code *)swi(0x1a);
    cVar2 = (*pcVar1)();
  } while (cVar2 != '\0');
  OV_0x2d42 = extraout_DX_00;
  OV_0x2d44 = in_CX;
  uVar3 = ((OV_0x2d42 + OV_0x2d3a) - OV_0x2d3e
          ) - OV_0x2d3e;
  if (0x80 < uVar3) {
    uVar3 = 0x80;
  }
  if (uVar3 == 0) {
    uVar3 = 1;
  }
  G_e_delay = uVar3;
  return;
}


// ===== ovl_2cd6 @ 1ca8:2cd6

void __cdecl16near ovl_2cd6(void)

{
  int iVar1;
  
  iVar1 = 0x1000;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_2cde @ 1ca8:2cde

undefined4 __cdecl16near ovl_2cde(undefined2 param_1)

{
  undefined2 *puVar1;
  code *pcVar2;
  byte bVar3;
  int iVar4;
  undefined2 in_BX;
  undefined2 *puVar5;
  
  pcVar2 = (code *)swi(0x10);
  (*pcVar2)();
  out(0x3c4,4);
  bVar3 = in(0x3c5);
  out(0x3c5,bVar3 & 0xf7 | 4);
  out(0x3ce,5);
  bVar3 = in(0x3cf);
  out(0x3cf,bVar3 & 0xef);
  out(0x3ce,6);
  bVar3 = in(0x3cf);
  out(0x3cf,bVar3 & 0xfd);
  out(0x3c4,0xf02);
  puVar5 = (undefined2 *)0x0;
  for (iVar4 = -0x8000; iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar1 = puVar5;
    puVar5 = puVar5 + 1;
    *puVar1 = 0;
  }
  out(0x3d4,0x14);
  bVar3 = in(0x3d5);
  out(0x3d5,bVar3 & 0xbf);
  out(0x3d4,0x17);
  bVar3 = in(0x3d5);
  out(0x3d5,bVar3 | 0x40);
  return CONCAT22(in_BX,param_1);
}


