// ===== ovl_0568 @ 1ca8:0568

void __cdecl16near ovl_0568(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  iVar2 = iRam000004f8;
  uVar1 = *(undefined4 *)(*piRam000004fc + 0x5a80);
  *(undefined2 *)(iRam000004f8 + 0x22d5) = (int)uVar1;
  *(undefined2 *)(iVar2 + 0x22d7) = (int)((ulong)uVar1 >> 0x10);
  return;
}


// ===== ovl_05a0 @ 1ca8:05a0

undefined2 ovl_05a0(void)

{
  undefined4 uVar1;
  byte bVar2;
  byte bVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  byte bVar7;
  undefined2 extraout_DX;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  bool bVar8;
  undefined2 uVar9;
  
  ovl_0568();
  G_txtptr = &OV_0x3d9;
  G_txtptr+2 = 0x1ca8;
  OV_0x3d2 = 0;
  OV_0x3c7 = 0xff;
  OV_0x3c9 = G_wildxy;
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  iVar5 = ovl_0abc();
  if ((bool)in_CF) {
    uVar9 = 0xff;
    EXE_SetTxtWnd(1,in_BX,0x6f,0xff);
    EXE_ClrTxtWnd();
    EXE_InitScrap();
    EXE_AddScrap(G_comtxtptr);
    EXE_PrtScrap(uVar9,in_BX);
    uVar9 = 0xff;
    goto L_058f;
  }
  OV_0x3bb = iVar5;
  iVar5 = *(int *)(iVar5 * 2 + &G_heroptr);
  OV_0x3c5 = iVar5;
  G_othername = iVar5;
  G_othername+2 = unaff_DS;
  if (*(char *)(iVar5 + 0xb8) != '\x01') {
    EXE_OnlyCompanions(in_BX);
    uVar9 = 0xff;
    goto L_058f;
  }
  if (G_indisguise != '\0') {
    EXE_IModTxt(0x38,in_BX);
    uVar9 = 0xff;
    goto L_058f;
  }
  uVar9 = G_npcno;
  OV_0x3c1 = uVar9;
  EXE_FindAss(uVar9);
  OV_0x3bf = extraout_DX;
  if (G_currm == -1) {
L_0689:
    do {
      ovl_11ee();
      while( true ) {
        uVar6 = EXE_Parser(&G_mnuparms,0);
        if (uVar6 == 0xffff) {
          uVar9 = 0xff;
          goto L_058f;
        }
        if (uVar6 == 0xfd) break;
        OV_0x3c3 = uVar6;
        if (uVar6 < 2) {
          if (uVar6 == 1) {
            ovl_0a97();
            iVar5 = EXE_GetNum(0,0x1e);
            bVar8 = iVar5 == 0;
            if (iVar5 < 1) {
              EXE_ClrTxtWnd(in_BX);
              goto L_08b9;
            }
            OV_0x3bd = iVar5;
            ovl_0909();
            if (bVar8) goto L_08b9;
            G_crecs+5 = 7;
            uVar4 = (undefined1)OV_0x3bd;
            goto L_0890;
          }
          ovl_0a97();
          iVar5 = ovl_0932();
          if (iVar5 == -1) {
            EXE_ClrTxtWnd();
            goto L_08b9;
          }
          bVar2 = *(byte *)(iVar5 + &G_scrap2+12);
          OV_0x3c7 = bVar2;
          iVar5 = (uint)bVar2 * 3;
          uVar4 = *(undefined1 *)(iVar5 + &OV_0x1ab);
          uVar9 = *(undefined2 *)(iVar5 + &OV_0x1ac);
          OV_0x3c9 = uVar9;
          bVar2 = (char)uVar9 - G_wildxy;
          if ((char)bVar2 < '\0') {
            bVar2 = -bVar2;
          }
          bVar7 = (char)((uint)uVar9 >> 8) - G_wildy;
          if ((char)bVar7 < '\0') {
            bVar7 = -bVar7;
          }
          bVar3 = bVar2;
          if (bVar2 <= bVar7) {
            bVar3 = bVar7;
            bVar7 = bVar2;
          }
          bVar7 = (byte)(bVar7 + 2) >> 2;
          bVar2 = bVar3 + bVar7;
          if (CARRY1(bVar3,bVar7)) {
            bVar2 = 0xff;
          }
          bVar2 = bVar2 >> 4;
          if (bVar2 == 0) {
            bVar2 = 1;
          }
          OV_0x3cf = bVar2;
          OV_0x3d0 = 1;
          OV_0x3d1 = uVar4;
          if (OV_0x3d2 != '\0') {
            return CONCAT11(bVar7,bVar2);
          }
          EXE_SetTxtWnd(1,in_BX,0x75);
          EXE_ClrTxtWnd();
          EXE_InitScrap();
          EXE_AddScrap(G_comtxtptr);
          EXE_PrtScrap(0xff);
          iVar5 = EXE_SetYN();
          if (iVar5 == 0) {
            ovl_09a8();
            G_crecs+5 = 8;
            G_crecs+20 = OV_0x3cf;
            G_crecs+1 = OV_0x3d0;
            G_crecs+2 = OV_0x3d1;
            G_crecs+11 = 0xff;
            ovl_0a62();
            goto L_0a8f;
          }
          EXE_ClrTxtWnd();
          goto L_08b9;
        }
      }
      iVar5 = 0x1000;
      EXE_RestorP(in_BX);
      in_BX = iVar5;
    } while( true );
  }
  bVar2 = (byte)G_curvar;
  if ((bVar2 < 8) || (0xb < bVar2)) goto L_0689;
  OV_0x3c3 = G_curvar;
  if ((char)*(undefined2 *)(*(int *)(OV_0x3bb * 2 + &G_heroptr) + 0xb9) ==
      -1) {
    EXE_InitScrap();
    EXE_AddScrap(G_comtxtptr);
    EXE_AddScrap(G_comtypptr);
    EXE_AddScrap(G_comtxtptr);
    EXE_PrtScrap(0xff,in_BX);
    uVar9 = 0xff;
    goto L_058f;
  }
  bVar2 = (byte)OV_0x3c3;
  bVar8 = bVar2 < 8;
  if (bVar2 == 8) {
    ovl_0909();
    if (bVar8) goto L_08b9;
  }
  else if (bVar2 == 9) {
    ovl_09a8();
  }
  else {
    bVar8 = bVar2 < 10;
    if (bVar2 == 10) {
      ovl_0909();
      if (bVar8) {
L_08b9:
        uVar9 = 0xff;
        goto L_058f;
      }
    }
    else {
      ovl_0909();
      if (bVar8) goto L_08b9;
    }
  }
  iVar5 = *(int *)(OV_0x3bb * 2 + &G_heroptr);
  G_crecs+5 = (char)*(undefined2 *)(iVar5 + 0xb9);
  G_crecs+8 = *(undefined1 *)(iVar5 + 0xd7);
  uVar9 = *(undefined2 *)(iVar5 + 0xd8);
  G_crecs+19 = (char)uVar9;
  G_crecs+21 = (char)((uint)uVar9 >> 8);
  uVar4 = *(undefined1 *)(iVar5 + 0xdb);
  *(byte *)(iVar5 + 0x16) = *(byte *)(iVar5 + 0x16) | 0x80;
L_0890:
  G_crecs+20 = uVar4;
  G_crecs+24 = OV_0x3cf;
  G_crecs+22 = OV_0x3d0;
  G_crecs+23 = OV_0x3d1;
  ovl_0a62();
L_0a8f:
  uVar9 = OV_0x3c3;
L_058f:
  uVar1 = OV_0x3d5;
  G_txtptr = (int)uVar1;
  G_txtptr+2 = (int)((ulong)uVar1 >> 0x10);
  return uVar9;
}


// ===== ovl_0909 @ 1ca8:0909

void ovl_0909(void)

{
  int iVar1;
  undefined1 uVar2;
  undefined2 *puVar3;
  undefined1 uVar4;
  int iVar5;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_0a97();
  iVar5 = ovl_0932();
  if (iVar5 == -1) {
    EXE_ClrTxtWnd();
    return;
  }
  OV_0x3d2 = 1;
  ovl_076f();
  OV_0x3d2 = 0;
  G_crecs = (char)G_npcno;
  G_crecs+1 = (char)G_locspec;
  G_crecs+2 = (char)G_currm;
  LOCK();
  iVar5 = OV_0x3bb;
  OV_0x3bb = in_BX;
  UNLOCK();
  uVar4 = *(undefined1 *)(iVar5 + &G_p1x);
  uVar2 = *(undefined1 *)(iVar5 + &G_p1y);
  LOCK();
  iVar1 = OV_0x3bb;
  OV_0x3bb = iVar5;
  UNLOCK();
  G_crecs+3 = CONCAT11(uVar2,uVar4);
  G_crecs+6 = 0xff;
  G_crecs+7 = OV_0x3c9;
  G_crecs+9 =
       (char)*(undefined2 *)(*(int *)(OV_0x3bb * 2 + &G_heroptr) + 6);
  puVar3 = (undefined2 *)(iVar1 + 0x1b8);
  uVar4 = EXE_viaptr_puVar3();
  G_crecs+10 = uVar4;
  uVar4 = 0xff;
  if (G_curmpg == 7) {
    uVar4 = G_hroomrec;
  }
  G_crecs+11 = uVar4;
  G_crecs+12 = (char)G_curreg;
  G_crecs+13 = G_wildxy;
  G_crecs+15 = OV_0x3c7;
  G_crecs+16 = OV_0x3ca;
  LOCK();
  iVar5 = OV_0x3c5;
  OV_0x3c5 = iVar1;
  UNLOCK();
  G_crecs+17 = *(undefined2 *)(iVar5 + 0xcc);
  LOCK();
  OV_0x3c5 = iVar5;
  UNLOCK();
  G_crecs+19 = (char)*(undefined2 *)(unaff_SI + 4);
  G_crecs+21 = (char)*(undefined2 *)(unaff_SI + 2);
  return;
}


// ===== ovl_0932 @ 1ca8:0932

void ovl_0932(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  char *pcVar5;
  undefined2 unaff_DS;
  bool bVar6;
  
  pcVar5 = (char *)&G_scrap2+12;
  iVar1 = *(int *)(unaff_SI + 100);
  iVar3 = 0;
  cVar4 = '\0';
  iVar2 = 0x10;
  do {
    bVar6 = iVar1 < 0;
    iVar1 = iVar1 << 1;
    if (bVar6) {
      *pcVar5 = cVar4;
      pcVar5 = pcVar5 + 1;
      iVar3 = iVar3 + 1;
    }
    cVar4 = cVar4 + '\x01';
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  EXE_ListSel(0x1ca8,iVar3,&OV_0xa61,0x1ca8);
  return;
}


// ===== ovl_0961 @ 1ca8:0961

void __cdecl16far ovl_0961(int param_1)

{
  undefined2 uVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_0568();
  uVar1 = G_scroll;
  G_scroll = 0;
  LOCK();
  UNLOCK();
  LOCK();
  UNLOCK();
  EXE_PrtWrdX(0x1ca8,&OV_0x124,0x1ca8,*(undefined1 *)(param_1 + &G_scrap2+12));
  EXE_Pad(0x1ca8,in_BX);
  G_scroll = uVar1;
  return;
}


// ===== ovl_09a8 @ 1ca8:09a8

void ovl_09a8(void)

{
  int iVar1;
  int iVar2;
  undefined1 uVar3;
  undefined2 *puVar4;
  undefined1 uVar5;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  G_crecs = (char)G_npcno;
  G_crecs+1 = (char)G_locspec;
  G_crecs+2 = (char)G_currm;
  LOCK();
  iVar1 = OV_0x3bb;
  OV_0x3bb = in_BX;
  UNLOCK();
  uVar5 = *(undefined1 *)(iVar1 + &G_p1x);
  uVar3 = *(undefined1 *)(iVar1 + &G_p1y);
  LOCK();
  iVar2 = OV_0x3bb;
  OV_0x3bb = iVar1;
  UNLOCK();
  G_crecs+3 = CONCAT11(uVar3,uVar5);
  G_crecs+6 = 0xff;
  G_crecs+7 = OV_0x3c9;
  G_crecs+9 =
       (char)*(undefined2 *)(*(int *)(OV_0x3bb * 2 + &G_heroptr) + 6);
  puVar4 = (undefined2 *)(iVar2 + 0x1b8);
  uVar5 = EXE_viaptr_puVar4(0x1000,OV_0x3bb);
  G_crecs+10 = uVar5;
  uVar5 = 0xff;
  if (G_curmpg == 7) {
    uVar5 = G_hroomrec;
  }
  G_crecs+11 = uVar5;
  G_crecs+12 = (char)G_curreg;
  G_crecs+13 = G_wildxy;
  G_crecs+15 = OV_0x3c7;
  G_crecs+16 = OV_0x3ca;
  LOCK();
  iVar1 = OV_0x3c5;
  OV_0x3c5 = iVar2;
  UNLOCK();
  G_crecs+17 = *(undefined2 *)(iVar1 + 0xcc);
  LOCK();
  OV_0x3c5 = iVar1;
  UNLOCK();
  G_crecs+19 = (char)*(undefined2 *)(unaff_SI + 4);
  G_crecs+21 = (char)*(undefined2 *)(unaff_SI + 2);
  return;
}


// ===== ovl_0a62 @ 1ca8:0a62

void ovl_0a62(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  int in_BX;
  int unaff_SI;
  undefined2 *puVar4;
  int unaff_DI;
  undefined2 *puVar5;
  undefined2 unaff_DS;
  
  puVar5 = (undefined2 *)OV_0x3bf;
  puVar4 = (undefined2 *)&G_crecs;
  for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar4;
    puVar4 = puVar4 + 1;
    *puVar2 = *puVar1;
  }
  for (iVar3 = 1; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar2 = puVar5;
    puVar5 = (undefined2 *)((int)puVar5 + 1);
    puVar1 = puVar4;
    puVar4 = (undefined2 *)((int)puVar4 + 1);
    *(undefined1 *)puVar2 = *(undefined1 *)puVar1;
  }
  LOCK();
  iVar3 = OV_0x3c5;
  OV_0x3c5 = in_BX;
  UNLOCK();
  *(undefined2 *)(iVar3 + 0xcc) = 0;
  LOCK();
  OV_0x3c5 = iVar3;
  UNLOCK();
  return;
}


// ===== ovl_0a97 @ 1ca8:0a97

void ovl_0a97(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_123b();
  EXE_AddScrap(G_comtxtptr);
  EXE_PrtScrap(3);
  return;
}


// ===== ovl_0abc @ 1ca8:0abc

int ovl_0abc(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int unaff_SI;
  int *piVar4;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  piVar4 = (int *)&G_party;
  iVar2 = G_npcno;
  iVar3 = 6;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    piVar1 = piVar4;
    piVar4 = piVar4 + 1;
    in_ZF = iVar2 == *piVar1;
  } while (!(bool)in_ZF);
  if ((bool)in_ZF) {
    iVar2 = 5 - iVar3;
  }
  return iVar2;
}


// ===== ovl_0d5e @ 1ca8:0d5e

void __cdecl16far ovl_0d5e(void)

{
  undefined2 uVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_0568();
  uVar1 = G_scroll;
  G_scroll = 0;
  LOCK();
  UNLOCK();
  LOCK();
  UNLOCK();
  iVar2 = ovl_0db0();
  G_deftxtparms+4 = iVar2 + 0xab;
  EXE_PrtWrdX(0x1ca8,&OV_0x65d,0x1ca8,0);
  EXE_Pad(0x1ca8,in_BX);
  G_scroll = uVar1;
  return;
}


// ===== ovl_0db0 @ 1ca8:0db0

int __cdecl16near ovl_0db0(void)

{
  char in_AL;
  int unaff_SI;
  
  return (uint)(byte)(in_AL - 1) * 0xdc + &G_member6;
}


// ===== ovl_11ee @ 1ca8:11ee

void ovl_11ee(void)

{
  undefined2 in_AX;
  undefined2 in_CX;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_InitScrap(0x1ca8);
  G_scrap = &OV_0x106;
  G_scrap+2 = 0x1ca8;
  G_scrap+4 = in_AX;
  EXE_ScrMenu(0x1ca8,in_CX,&G_scrap+4,in_BX,in_CX);
  EXE_InitCom(0x1ca8,&OV_0x3ab,0x1ca8,in_CX,in_BX);
  return;
}


// ===== ovl_123b @ 1ca8:123b

void ovl_123b(void)

{
  int in_AX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(0x1ca8,1);
  EXE_ClrTxtWnd(0x1ca8);
  EXE_InitScrap(0x1ca8);
  EXE_AddScrap(0x1ca8,*(undefined2 *)(in_AX * 2 + &G_heroptr));
  EXE_AddScrap(0x1ca8,G_comtxtptr);
  return;
}


