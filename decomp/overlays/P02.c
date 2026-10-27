// ===== ovl_028a @ 1ca8:028a

int ovl_028a(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  iVar1 = iRam000004f8 + -0x100;
  *(undefined2 *)(*piRam000004fc + -0x728a) = piRam000004fc;
  return iVar1;
}


// ===== ovl_02ab @ 1ca8:02ab

void ovl_02ab(void)

{
  code *pcVar1;
  int iVar2;
  uint uVar3;
  int in_BX;
  int unaff_SI;
  uint unaff_DI;
  undefined2 unaff_DS;
  byte bVar4;
  bool bVar5;
  int iStack000e;
  int in_stack_00000010;
  
  ovl_028a();
  OV_0x127 = 0;
  OV_0x132 = 0;
  OV_0x12a = 0;
  OV_0x133 = 0;
  G_swgreet = 0;
  G_curbfl = 0xff;
  G_lookprt = 1;
  G_scroll = 1;
  iVar2 = EXE_InDungeon();
  if (iVar2 == 0) {
    G_wlkwcount = 0;
  }
  pcVar1 = INT_0x60_handler;
  iVar2 = (*pcVar1)();
  bVar4 = 0;
  if (iVar2 == 0) {
    pcVar1 = INT_0x60_handler;
    (*pcVar1)();
    pcVar1 = INT_0x60_handler;
    (*pcVar1)();
    pcVar1 = INT_0x60_handler;
    (*pcVar1)();
    OV_0x13e = G_lastdir;
    G_winxy = G_pwinxy;
    EXE_NewPXY();
    EXE_PartyMusRegs();
    G_curmap = 0xff;
    ovl_07cb();
    EXE_NewLoc();
    ovl_0e8a();
    EXE_clearkbd();
    iStack000e = in_BX;
    goto L_0343;
  }
  pcVar1 = INT_0x60_handler;
  (*pcVar1)();
  ovl_196b();
L_047f:
  if (OV_0x132 != '\0') {
    return;
  }
  if ((bVar4 & 1) == 0) {
    (*(code *)*(undefined2 *)(in_BX + 200))();
    OV_0x135 = OV_0x135 + '\x01';
    iStack000e = in_stack_00000010;
    if (OV_0x135 < 0xc) goto L_04c0;
    OV_0x135 = 0;
    OV_0x136 = OV_0x136 + '\x01';
    if ((OV_0x136 & 1) != 0) {
      ovl_0fca();
      iStack000e = in_stack_00000010;
    }
    EXE_CalUpd();
    goto L_04c0;
  }
  EXE_GameSound();
  pcVar1 = INT_0x60_handler;
  (*pcVar1)();
L_034e:
  in_stack_00000010 = in_BX;
  ovl_0e6a();
  iStack000e = 0;
  iVar2 = EXE_Parser();
  if (G_restarting != 0) {
    return;
  }
  if (iVar2 == 0xfd) goto L_0343;
  if (iVar2 == 0xfe) {
L_034b:
    ovl_1a0f();
    in_BX = iStack000e;
    goto L_034e;
  }
  G_lookdata = 0xff;
  if (G_used == -1) {
    bVar5 = G_whspnum != -1;
    if (G_whspnum == -1) {
      if (iVar2 == 5) {
        EXE_LoadOvly();
        EXE_RoomPgm();
        EXE_Reload91();
        goto L_0343;
      }
      if (iVar2 == 6) {
        EXE_CalUpd();
        in_BX = iStack000e;
        goto L_034e;
      }
      if (iVar2 == 7) {
        EXE_NewFormatn();
        ovl_1a0f();
L_04c0:
        ovl_0e9a();
        EXE_GameSound();
        if (G_swtext != '\0') {
          EXE_ClrTxtWnd();
          G_swtext = 0;
        }
        if (G_wlkwcount != '\0') {
          G_wlkwcount = G_wlkwcount + -1;
        }
        ovl_151a();
        in_BX = iStack000e;
        if (OV_0x132 != '\0') {
          return;
        }
        goto L_034e;
      }
      in_BX = iStack000e;
      if (((G_curmen != 5) ||
          (uVar3 = iVar2 - 0x31, in_BX = iStack000e, 8 < uVar3)) || (in_BX = iStack000e, uVar3 == 4)
         ) goto L_034e;
      OV_0x13e = uVar3;
      uVar3 = *(uint *)(uVar3 * 2 + &OV_0x60d);
      bVar4 = CARRY2(uVar3,unaff_DI);
      (*(code *)(uVar3 + unaff_DI))();
      in_BX = iStack000e;
      goto L_047f;
    }
    LOCK();
    G_whspnum = 0xff;
    UNLOCK();
    ovl_0830();
    if (bVar5) {
      EXE_SetTxtWnd();
      EXE_ClrTxtWnd();
      EXE_InitScrap();
      EXE_AddScrap();
      EXE_PrtScrap();
      in_BX = iStack000e;
      goto L_034e;
    }
  }
  else {
    LOCK();
    bVar4 = G_used;
    G_used = 0xff;
    UNLOCK();
    if (bVar4 == 0x46) {
      ovl_1131();
      goto L_034b;
    }
    if (bVar4 == 0x50) {
      ovl_1044();
      goto L_034b;
    }
    if ((bVar4 != 0x40) &&
       ((bVar5 = bVar4 < 0x3e, bVar4 != 0x3e || (bVar4 = ovl_13c4(), bVar5)))) {
      if (bVar4 == 0x3f) {
        ovl_13ab();
        goto L_0343;
      }
      G_used = bVar4;
      EXE_NoUse();
      in_BX = iStack000e;
      goto L_034e;
    }
  }
L_0343:
  ovl_1a0f();
  ovl_0e81();
  in_BX = iStack000e;
  goto L_034e;
}


// ===== ovl_07cb @ 1ca8:07cb

void ovl_07cb(void)

{
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (OV_0x127 == '\0') {
    G_zp_10 = G_winxy;
    ovl_0f4a();
    return;
  }
  return;
}


// ===== ovl_0830 @ 1ca8:0830

void ovl_0830(void)

{
  undefined2 *puVar1;
  undefined1 *puVar2;
  undefined2 uVar3;
  uint uVar4;
  char in_AL;
  byte bVar5;
  char cVar6;
  int in_BX;
  int iVar7;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar8;
  
  iVar7 = 0;
  while( true ) {
    if (*(char *)(iVar7 + &OV_0x157) == -1) {
      return;
    }
    if ((in_AL == *(char *)(iVar7 + &OV_0x157)) &&
       (G_locspec == *(char *)(iVar7 + &OV_0x159))) break;
    iVar7 = iVar7 + 1;
  }
  OV_0x163 = iVar7;
  OV_0x165 = &OV_0x15a;
  do {
    LOCK();
    puVar1 = (undefined2 *)OV_0x165;
    OV_0x165 = in_BX;
    UNLOCK();
    uVar3 = *puVar1;
    LOCK();
    in_BX = OV_0x165;
    OV_0x165 = (int)(puVar1 + 2);
    UNLOCK();
    bVar5 = (byte)uVar3;
    if (bVar5 == 0xff) {
      OV_0x165 = &OV_0x15a;
      while( true ) {
        LOCK();
        puVar1 = (undefined2 *)OV_0x165;
        OV_0x165 = in_BX;
        UNLOCK();
        uVar3 = *puVar1;
        uVar4 = puVar1[1];
        LOCK();
        in_BX = OV_0x165;
        OV_0x165 = (int)(puVar1 + 2);
        UNLOCK();
        cVar6 = (char)uVar3;
        if (cVar6 == -1) break;
        if (cVar6 == OV_0x163) {
          EXE_Locate(uVar4 & 0xff,uVar4 >> 8);
          LOCK();
          puVar2 = (undefined1 *)G_zp_0A;
          G_zp_0A = in_BX;
          UNLOCK();
          *puVar2 = (char)((uint)uVar3 >> 8);
          LOCK();
          in_BX = G_zp_0A;
          G_zp_0A = (int)puVar2;
          UNLOCK();
        }
      }
      return;
    }
    bVar8 = bVar5 < OV_0x163;
  } while ((bVar5 != OV_0x163) || (ovl_08d8(), !bVar8));
  return;
}


// ===== ovl_08d8 @ 1ca8:08d8

void ovl_08d8(void)

{
  byte in_AL;
  byte in_AH;
  byte bVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  bVar1 = (byte)G_winxy;
  if ((((in_AL < bVar1) || (G_winxl <= (byte)(in_AL - bVar1))) ||
      (bVar1 = (byte)((uint)G_winxy >> 8), in_AH < bVar1)) ||
     (G_winyl <= (byte)(in_AH - bVar1))) {
    return;
  }
  return;
}


// ===== ovl_0cf1 @ 1ca8:0cf1

void ovl_0cf1(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  puVar3 = (undefined2 *)((uint)G_rmdata * 6 + G_loc+6);
  OV_0xaff = puVar3;
  uVar1 = puVar3[1];
  uVar2 = *puVar3;
  G_rmdata+1 = uVar2;
  G_rmdata+3 = uVar1;
  OV_0x12e = (char)uVar2;
  *(undefined1 *)(unaff_DI + 300) = (char)((uint)uVar2 >> 8);
  return;
}


// ===== ovl_0d1d @ 1ca8:0d1d

void ovl_0d1d(void)

{
  undefined2 in_AX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(0x1ca8,1);
  EXE_ClrTxtWnd(0x1ca8);
  EXE_InitScrap(0x1ca8);
  EXE_AddScrap(0x1ca8,(int)G_txtptr,
             (int)((ulong)G_txtptr >> 0x10),in_AX,in_BX);
  return;
}


// ===== ovl_0d45 @ 1ca8:0d45

void ovl_0d45(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(0x1ca8,1);
  EXE_ClrTxtWnd(0x1ca8);
  EXE_InitScrap(0x1ca8);
  EXE_AddScrap(0x1ca8,G_loc+10);
  return;
}


// ===== ovl_0d5c @ 1ca8:0d5c

void ovl_0d5c(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_AddScrap(0x1ca8,G_loc+10);
  return;
}


// ===== ovl_0d70 @ 1ca8:0d70

void ovl_0d70(void)

{
  undefined2 *puVar1;
  uint uVar2;
  int iVar3;
  int in_BX;
  char *pcVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar2 = EXE_BreakPoint(0x1ca8);
  OV_0xe6c = uVar2 & 0x7f;
  iVar3 = EXE_SearchInv(OV_0xe6c,0xffff,&OV_0xaf7,0x1000);
  if (iVar3 == 0) {
    ovl_0d45();
    EXE_PrtScrap(2,in_BX);
    return;
  }
  pcVar4 = (char *)G_loc+32;
  OV_0xe6e = pcVar4[4];
  do {
    OV_0xe6f = pcVar4[3];
    uVar2 = *(uint *)(pcVar4 + 1);
    puVar1 = (undefined2 *)(G_savebx + 0xf4);
    EXE_viaptr_puVar1(0x1000,uVar2 & 0xff,uVar2 >> 8,G_savebx,uVar2);
    *(undefined1 *)G_zp_0A = OV_0xe6f;
    uVar2 = uVar2 - G_winxy;
    puVar1 = (undefined2 *)(G_savebx + 0x120);
    EXE_viaptr_puVar1(0x1000,uVar2 & 0xff,uVar2 >> 8,G_savebx);
    pcVar4 = pcVar4 + 5;
  } while (*pcVar4 != -1);
  iVar3 = G_savebx;
  EXE_SetTxtObj(OV_0xe6c);
  EXE_RoomPgm(OV_0xafb);
  ovl_0d5c();
  EXE_PrtScrap(2);
  EXE_PrtWrd(G_comtxtptr);
  return;
}


// ===== ovl_0e6a @ 1ca8:0e6a

void ovl_0e6a(void)

{
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (*(int *)(unaff_SI + 2) != OV_0x125) {
    OV_0x125 = *(int *)(unaff_SI + 2);
    ovl_0e8a();
    ovl_0e81();
  }
  return;
}


// ===== ovl_0e81 @ 1ca8:0e81

void ovl_0e81(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_InitMap(0x1ca8);
  ovl_0e9a();
  return;
}


// ===== ovl_0e8a @ 1ca8:0e8a

void ovl_0e8a(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_InitNPC(0x1ca8);
  OV_0x125 = *(undefined2 *)(unaff_SI + 2);
  return;
}


// ===== ovl_0e9a @ 1ca8:0e9a

void ovl_0e9a(void)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  int in_BX;
  uint uVar6;
  uint uVar7;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_FillWindow(0x1ca8,G_winxy & 0xff,G_winxy >> 8);
  if (G_mfxfadein != 0) {
    EXE_GameSound(0x1ca8,0x14);
    EXE_MFXInit(0x1ca8,in_BX);
    uVar6 = 0;
    iVar5 = 6;
    do {
      if (*(char *)(uVar6 * 2 + &G_party) != -1) {
        uVar7 = uVar6 & 0x7fff;
        iVar4 = CONCAT11(*(undefined1 *)(uVar7 + &G_p1y),
                         *(undefined1 *)(uVar7 + &G_p1x)) - G_winxy;
        iVar2 = G_mfxcnt;
        *(uint *)(iVar2 + &G_mfxtnum) = (uint)*(byte *)(uVar7 + &G_pltilno);
        *(undefined2 *)(iVar2 + &G_mfxcoords) =
             CONCAT11((char)((uint)iVar4 >> 8) * '\x10' + '\b',(char)iVar4 * '\x04' + '\x04');
        G_mfxcnt = G_mfxcnt + 2;
      }
      uVar6 = uVar6 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    iVar5 = G_savebx;
    G_mfxcnt = 0;
    G_egadrawcode = 0;
    G_egaeffectstimer = 10000;
    LOCK();
    uVar1 = G_mfxfadein;
    G_mfxfadein = 0;
    UNLOCK();
    G_egaeffectsflag = uVar1;
    G_egaeffectssound = 0;
    puVar3 = (undefined2 *)(iVar5 + 0x2f8);
    EXE_viaptr_puVar3(0x1ca8,0,0,0,iVar5);
  }
  return;
}


// ===== ovl_0f4a @ 1ca8:0f4a

void ovl_0f4a(void)

{
  code *pcVar1;
  undefined1 uVar3;
  int iVar2;
  undefined2 uVar4;
  uint uVar5;
  byte bVar6;
  byte bVar7;
  int in_BX;
  int iVar8;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar5 = (uint)*(byte *)(G_loc+8 + -1);
  iVar8 = 0;
  do {
    bVar7 = *(byte *)(iVar8 + G_mapxptr);
    bVar6 = (byte)G_zp_10;
    if ((bVar7 <= bVar6) && (bVar6 < (byte)(bVar7 + 0x20))) {
      bVar6 = *(byte *)(iVar8 + G_mapyptr);
      uVar4 = CONCAT11(bVar6,bVar7);
      bVar7 = (byte)((uint)G_zp_10 >> 8);
      if ((bVar6 <= bVar7) && (bVar7 < (byte)(bVar6 + 0x22))) break;
    }
    iVar8 = iVar8 + 1;
    uVar5 = uVar5 - 1;
    uVar4 = 0;
  } while (uVar5 != 0);
  G_cursegx0 = uVar4;
  G_curseg = iVar8;
  uVar3 = (undefined1)((uint)iVar8 >> 8);
  iVar2 = CONCAT11(uVar3,*(undefined1 *)(G_loc+8 + iVar8));
  if (iVar2 != G_curmap) {
    EXE_LoadMap(0x1ca8,iVar2,CONCAT11(uVar3,*(undefined1 *)(G_maptileptr + iVar8)),
               0x4d);
    pcVar1 = INT_0x60_handler;
    (*pcVar1)();
  }
  return;
}


// ===== ovl_0fca @ 1ca8:0fca

void ovl_0fca(void)

{
  int iVar1;
  uint uVar2;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = 6;
  uVar2 = 0;
  do {
    if (*(int *)(uVar2 + &G_party) != 0xff) {
      EXE_DecSta(0x1ca8,uVar2 >> 1,0xba,1);
      EXE_IsHeTr(0x1ca8,*(undefined2 *)(uVar2 + &G_heroptr));
    }
    uVar2 = uVar2 + 2;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_100b @ 1ca8:100b

void ovl_100b(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined2 uVar1;
  
  uVar1 = 0xff;
  EXE_SetTxtWnd(0x1ca8,1);
  EXE_ClrTxtWnd(0x1ca8);
  EXE_InitScrap(0x1ca8);
  EXE_AddScrap(0x1ca8,G_comtxtptr);
  EXE_PrtScrap(0x1ca8,uVar1,in_BX);
  return;
}


// ===== ovl_1010 @ 1ca8:1010

void ovl_1010(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined2 uVar1;
  
  uVar1 = 3;
  EXE_SetTxtWnd(0x1ca8,1);
  EXE_ClrTxtWnd(0x1ca8);
  EXE_InitScrap(0x1ca8);
  EXE_AddScrap(0x1ca8,G_comtxtptr);
  EXE_PrtScrap(0x1ca8,uVar1,in_BX);
  return;
}


// ===== ovl_1044 @ 1ca8:1044

void ovl_1044(int param_1)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  code *pcVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  undefined2 uVar7;
  int iVar8;
  uint uVar9;
  int in_BX;
  char *pcVar11;
  char *pcVar10;
  uint *puVar12;
  uint *puVar13;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar5 = EXE_Mark(0x1ca8,&G_scrap,0xd);
  if (iVar5 == -1) {
    return;
  }
  uVar6 = G_scrap+2;
  G_zp_1415 = uVar6;
  iVar5 = EXE_ChkRng(0x1ca8,uVar6 & 0xff,uVar6 >> 8,1,1);
  if (iVar5 == 0) {
    return;
  }
  ovl_1926();
  if (OV_0x137 == 0) {
    ovl_100b();
    return;
  }
  iVar5 = *(int *)(G_curpla * 2 + &G_heroptr);
  bVar4 = (*(byte *)(iVar5 + 0xf) >> 1) + (char)*(undefined2 *)(iVar5 + 0x21);
  if (0x62 < bVar4) {
    bVar4 = 99;
  }
  OV_0x142 = bVar4;
  bVar4 = EXE_RndCo(100);
  if (OV_0x142 <= bVar4) {
    ovl_100b();
    EXE_GameSound(0x15);
    EXE_DecObj0(0x50,1);
    puVar1 = (undefined2 *)(in_BX + 0x178);
    in_BX = 0;
    EXE_viaptr_puVar1(0x1000,G_comtxtptr);
  }
  uVar6 = ovl_1926();
  if ((char)(uVar6 >> 8) != '\0') {
    pcVar3 = INT_0x60_handler;
    iVar5 = (*pcVar3)();
    if (iVar5 != 0) goto L_11b0;
  }
  G_zp_0A = 10;
  EXE_SkillUp0();
L_11b0:
  OV_0x141 = (char)uVar6;
  iVar5 = EXE_FindBit(&G_chests,uVar6 & 0xff,in_BX,uVar6 & 0xff);
  if (iVar5 != 0) {
    ovl_100b();
    return;
  }
  ovl_100b();
  EXE_PrtWrd(G_comtxtptr);
  pcVar10 = (char *)G_loc+30;
  while (OV_0x141 != *pcVar10) {
    do {
      pcVar11 = pcVar10;
      pcVar10 = pcVar11 + 1;
    } while (*pcVar10 != -1);
    pcVar10 = pcVar11 + 2;
  }
  OV_0x13b = 0;
  pcVar10 = pcVar10 + 1;
  OV_0x137 = pcVar10;
  while( true ) {
    uVar7 = *(undefined2 *)pcVar10;
    if ((char)uVar7 == -1) break;
    pcVar10 = pcVar10 + 2;
    if ((char)uVar7 == -0x80) {
      ovl_1366();
    }
    else {
      iVar5 = G_savebx;
      EXE_ClrTxtWnd();
      EXE_InitScrap();
      bVar4 = (byte)uVar7;
      if ((8 < bVar4) && (bVar4 < 0x31)) {
        uVar7 = CONCAT11(1,bVar4);
      }
      EXE_PrtTreasure(uVar7);
      EXE_PrtWrd(G_comtxtptr);
      OV_0x13b = 1;
    }
  }
  iVar5 = G_savebx;
  if (OV_0x13b != '\x01') {
    return;
  }
  do {
    EXE_IComTxt(0x85);
    iVar8 = EXE_HeroSel(0,0);
    if (iVar8 == -1) {
      return;
    }
    EXE_SetBit(&G_chests,OV_0x141,iVar5);
    ovl_178a();
    OV_0x139 = *(undefined2 *)(param_1 * 2 + &G_heroptr);
    puVar13 = (uint *)OV_0x137;
    while( true ) {
      do {
        puVar12 = puVar13;
        uVar6 = *puVar12;
        puVar13 = puVar12 + 1;
        bVar4 = (byte)uVar6;
        if (bVar4 == 0xff) {
          return;
        }
      } while (bVar4 == 0x80);
      uVar9 = uVar6 >> 8;
      if ((8 < bVar4) && (bVar4 < 0x31)) {
        uVar9 = 0x80;
      }
      puVar2 = (undefined2 *)(G_savebx + 0x164);
      iVar5 = EXE_viaptr_puVar2(0x1000,OV_0x139,uVar6 & 0xff,uVar9);
      if (iVar5 == 0) break;
      ovl_1315();
    }
    OV_0x137 = puVar12;
    param_1 = G_savebx;
    iVar5 = 0;
    EXE_PrtWrd(G_comtxtptr);
  } while( true );
}


// ===== ovl_1131 @ 1ca8:1131

void ovl_1131(int param_1)

{
  uint uVar1;
  undefined2 *puVar2;
  undefined1 uVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  undefined2 uVar7;
  uint uVar8;
  int in_BX;
  int *piVar9;
  char *pcVar11;
  char *pcVar10;
  uint *puVar12;
  uint *puVar13;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar5 = EXE_Mark(0x1ca8,&G_scrap,0x7f);
  if (iVar5 == -1) {
    return;
  }
  uVar1 = G_scrap+2;
  G_zp_1415 = uVar1;
  iVar5 = EXE_ChkRng(0x1ca8,uVar1 & 0xff,uVar1 >> 8,1,1);
  if (iVar5 == 0) {
    return;
  }
  iVar5 = EXE_ChkWlk(0x1ca8,in_BX);
  if (iVar5 == 0) {
    piVar9 = (int *)G_loc+12;
    while( true ) {
      if ((char)*piVar9 == '\0') {
        ovl_100b();
        return;
      }
      if (*piVar9 == G_scrap+2) break;
      piVar9 = (int *)((int)piVar9 + 3);
    }
  }
  iVar5 = G_savebx;
  uVar3 = ovl_1926();
  if (OV_0x137 != 0) {
    OV_0x141 = uVar3;
    iVar6 = EXE_FindBit(&G_chests,uVar3,iVar5,uVar3);
    if (iVar6 == 0) {
      ovl_100b();
      EXE_PrtWrd(G_comtxtptr);
      pcVar10 = (char *)G_loc+30;
      while (OV_0x141 != *pcVar10) {
        do {
          pcVar11 = pcVar10;
          pcVar10 = pcVar11 + 1;
        } while (*pcVar10 != -1);
        pcVar10 = pcVar11 + 2;
      }
      OV_0x13b = 0;
      pcVar10 = pcVar10 + 1;
      OV_0x137 = pcVar10;
      while( true ) {
        uVar7 = *(undefined2 *)pcVar10;
        if ((char)uVar7 == -1) break;
        pcVar10 = pcVar10 + 2;
        if ((char)uVar7 == -0x80) {
          ovl_1366();
        }
        else {
          iVar5 = G_savebx;
          EXE_ClrTxtWnd();
          EXE_InitScrap();
          bVar4 = (byte)uVar7;
          if ((8 < bVar4) && (bVar4 < 0x31)) {
            uVar7 = CONCAT11(1,bVar4);
          }
          EXE_PrtTreasure(uVar7);
          EXE_PrtWrd(G_comtxtptr);
          OV_0x13b = 1;
        }
      }
      iVar5 = G_savebx;
      if (OV_0x13b != '\x01') {
        return;
      }
      do {
        EXE_IComTxt(0x85);
        iVar6 = EXE_HeroSel(0,0);
        if (iVar6 == -1) {
          return;
        }
        EXE_SetBit(&G_chests,OV_0x141,iVar5);
        ovl_178a();
        OV_0x139 = *(undefined2 *)(param_1 * 2 + &G_heroptr);
        puVar13 = (uint *)OV_0x137;
        while( true ) {
          do {
            puVar12 = puVar13;
            uVar1 = *puVar12;
            puVar13 = puVar12 + 1;
            bVar4 = (byte)uVar1;
            if (bVar4 == 0xff) {
              return;
            }
          } while (bVar4 == 0x80);
          uVar8 = uVar1 >> 8;
          if ((8 < bVar4) && (bVar4 < 0x31)) {
            uVar8 = 0x80;
          }
          puVar2 = (undefined2 *)(G_savebx + 0x164);
          iVar5 = EXE_viaptr_puVar2(0x1000,OV_0x139,uVar1 & 0xff,uVar8);
          if (iVar5 == 0) break;
          ovl_1315();
        }
        OV_0x137 = puVar12;
        param_1 = G_savebx;
        iVar5 = 0;
        EXE_PrtWrd(G_comtxtptr);
      } while( true );
    }
  }
  ovl_100b();
  return;
}


// ===== ovl_1315 @ 1ca8:1315

void ovl_1315(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int in_BX;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x1413 =
       *(int *)(G_lootvalptr + (*(uint *)(in_BX + -2) & 0xff) * 2) *
       (*(uint *)(in_BX + -2) >> 8);
  iVar4 = 0;
  iVar3 = 6;
  do {
    if ((*(int *)(iVar4 + &G_party) != 0xff) &&
       (iVar1 = *(int *)(iVar4 + &G_heroptr), *(char *)(iVar1 + 0xb8) == '\x02')) {
      uVar2 = OV_0x1413 + *(int *)(iVar1 + 0xce);
      if (29999 < uVar2) {
        uVar2 = 30000;
      }
      *(uint *)(iVar1 + 0xce) = uVar2;
    }
    iVar4 = iVar4 + 2;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


// ===== ovl_1366 @ 1ca8:1366

void ovl_1366(void)

{
  uint in_AX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  int iVar1;
  
  iVar1 = G_savebx;
  EXE_ClrTxtWnd(0x1ca8,iVar1,in_AX >> 8);
  EXE_InitScrap(0x1ca8);
  EXE_AddScrap(0x1ca8,&OV_0x167,0x1ca8,0x10);
  EXE_AddScrap(0x1ca8,G_loc+10);
  EXE_PrtScrap(0x1ca8,2,iVar1);
  return;
}


// ===== ovl_13ab @ 1ca8:13ab

void ovl_13ab(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_loc+58 == '\0') {
    EXE_ShowMiniMap(0x1ca8);
    return;
  }
  ovl_100b();
  return;
}


// ===== ovl_13c4 @ 1ca8:13c4

undefined2 ovl_13c4(void)

{
  byte bVar1;
  int iVar2;
  undefined2 uVar3;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  byte bVar4;
  
  if (G_loc+58 == '\0') {
    return 0x3f;
  }
  OV_0x14c0 = 0;
  G_txtptr = &OV_0x167;
  G_txtptr+2 = 0x1000;
  iVar2 = EXE_SearchInv(1,G_curpla,&G_invinfobuf);
  if (iVar2 != 0) {
    OV_0x14c0 = G_invinfobuf;
  }
  iVar2 = EXE_SearchInv(2,G_curpla,&G_invinfobuf);
  if (iVar2 != 0) {
    OV_0x14c1 = G_invinfobuf;
  }
  iVar2 = OV_0x14c0;
  if (iVar2 == 0) {
    uVar3 = EXE_IModTxt(0xc,in_BX);
  }
  else {
    if ((char)iVar2 == '\0') {
      OV_0x14c2 = 2;
    }
    else {
      OV_0x14c2 = 1;
      if ((char)((uint)iVar2 >> 8) != '\0') {
        EXE_IModTxt(0xe);
        iVar2 = EXE_SetYN();
        if (iVar2 == -1) {
          return 0xffff;
        }
        if (iVar2 == 0) {
          OV_0x14c2 = 2;
        }
      }
    }
    EXE_SetTxtObj(OV_0x14c2);
    EXE_IModTxt(0xf);
    EXE_DecObj0(OV_0x14c2,1);
    if ((OV_0x14c2 != 2) &&
       (iVar2 = EXE_RndCo(10), iVar2 == 0)) {
      bVar4 = (byte)*(undefined2 *)
                     (*(int *)(G_curpla * 2 + &G_heroptr) + 0xf);
      bVar1 = EXE_RndCo(0x14);
      if (bVar4 <= bVar1) {
        EXE_PrtWrd(G_comtxtptr);
        EXE_IModTxt(0xd);
        uVar3 = EXE_DecObj0(0x3e,1,in_BX);
        return uVar3;
      }
    }
    uVar3 = EXE_ShowMiniMap(in_BX);
  }
  return uVar3;
}


// ===== ovl_151a @ 1ca8:151a

uint ovl_151a(void)

{
  undefined1 uVar1;
  undefined2 *puVar2;
  code *pcVar3;
  undefined1 uVar4;
  uint uVar5;
  int iVar6;
  int in_CX;
  int iVar7;
  char cVar8;
  char cVar10;
  uint uVar9;
  byte bVar11;
  int in_BX;
  int iVar12;
  int iVar13;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined4 uVar14;
  
  G_lastdir = OV_0x13e;
  OV_0x140 = 0;
  while( true ) {
    uVar14 = FUN_1000_e31d();
    uVar5 = (uint)uVar14;
    if (OV_0x137 == 0) {
      return uVar5;
    }
    cVar8 = (char)((ulong)uVar14 >> 0x10);
    cVar10 = (char)((ulong)uVar14 >> 0x18);
    if (cVar8 == '\0') {
      G_grpno = cVar10;
      G_entrno = (char)uVar14;
      G_hroomrec = (char)uVar14;
      G_hroomrec+1 = cVar10;
      G_hroomrec+4 = (char)((ulong)uVar14 >> 8);
      G_hroomrec+2 = 0;
      G_hroomrec+5 = 0;
      G_hroomrec+7 = 0;
      G_hroomrec+9 = 0;
      G_hroomrec+11 = 0;
      uVar5 = EXE_FindBit(&G_ambush,uVar5 & 0xff);
      if (uVar5 == 0) {
        ovl_174f();
        G_cmbtyp = 0;
        ovl_1712();
        G_ambflg = 1;
        uVar5 = OV_0x133;
        if (uVar5 != G_zp_1415) {
          uVar4 = EXE_HighStat();
          OV_0x1742 = uVar4;
          uVar5 = EXE_RndCo();
          if (OV_0x1742 <= (byte)uVar5) {
            return uVar5;
          }
          EXE_SetTxtWnd(1);
          EXE_ClrTxtWnd();
          EXE_InitScrap();
          EXE_AddScrap(G_comtxtptr);
          EXE_PrtScrap();
          uVar5 = EXE_PrtWrd(G_comtxtptr);
        }
        G_ambflg = 0;
      }
      return uVar5;
    }
    if ((cVar8 == '\x01') && (in_CX != -1)) {
      G_pwinxy = uVar5;
      ovl_1010((int)((ulong)uVar14 >> 0x10));
      EXE_GameSound(0x14);
      EXE_MFXInit(in_BX);
      iVar6 = 9;
      iVar12 = 0;
      do {
        cVar8 = *(char *)(iVar12 + &G_formatn);
        if (cVar8 != -1) {
          iVar13 = CONCAT11((char)((uint)iVar12 >> 8),cVar8);
          uVar4 = *(undefined1 *)(iVar13 + &G_p1x);
          uVar1 = *(undefined1 *)(iVar13 + &G_p1y);
          iVar7 = CONCAT11(uVar1,uVar4);
          puVar2 = (undefined2 *)(G_savebx + 0xf4);
          uVar5 = EXE_viaptr_puVar2(0x1000,uVar4,uVar1,G_savebx);
          iVar7 = iVar7 - G_winxy;
          iVar13 = G_mfxcnt;
          *(uint *)(iVar13 + &G_mfxtnum) = uVar5 & 0xff;
          *(undefined2 *)(iVar13 + &G_mfxcoords) =
               CONCAT11((char)((uint)iVar7 >> 8) * '\x10' + '\b',(char)iVar7 * '\x04' + '\x04');
          G_mfxcnt = G_mfxcnt + 2;
        }
        iVar12 = iVar12 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      G_mfxcnt = 0;
      iVar6 = G_savebx;
      G_egadrawcode = 0;
      G_egaeffectstimer = 10000;
      G_egaeffectsflag = 6;
      G_egaeffectssound = 0;
      puVar2 = (undefined2 *)(iVar6 + 0x33c);
      EXE_viaptr_puVar2(0x1000,0,0,0,iVar6);
      G_mfxfadein = 6;
      uVar5 = ovl_196b();
      return uVar5;
    }
    if ((cVar8 == '\x04') && (in_CX != -1)) {
      uVar5 = ovl_1010();
      return uVar5;
    }
    if ((cVar8 == '\x05') && (in_CX != -1)) {
      G_pwinxy = uVar5;
      ovl_196b();
      uVar5 = ovl_1010();
      return uVar5;
    }
    if (cVar8 == '\x06') break;
    OV_0x140 = OV_0x140 + '\x01';
  }
  if (cVar10 == -2) {
    OV_0x13c = 0xfe;
    EXE_InitScrap();
  }
  else {
    uVar9 = CONCAT11(cVar10,cVar10) & 0xff7f;
    iVar6 = 1;
    do {
      if (*(int *)(iVar6 * 2 + &G_party) != 0xff) {
        iVar12 = *(int *)(iVar6 * 2 + &G_heroptr);
        bVar11 = (byte)(uVar9 >> 8);
        if (((0x7f < bVar11) && (*(char *)(iVar12 + 6) == (char)uVar9)) ||
           (*(byte *)(iVar12 + 8) == bVar11)) break;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 != 6);
    in_BX = G_savebx;
    if (iVar6 == 6) {
      return uVar5;
    }
    OV_0x13c = iVar6;
  }
  if ((char)uVar5 != -1) {
    iVar6 = EXE_ChkEvent(uVar5 & 0xff,in_BX);
    if (iVar6 != 0) {
      return uVar5;
    }
  }
  pcVar3 = INT_0x60_handler;
  (*pcVar3)();
  ovl_1852();
  *(undefined1 *)(OV_0x137 + 2) = 0xff;
  puVar2 = (undefined2 *)(G_savebx + 0xe0);
  uVar5 = EXE_viaptr_puVar2(0x1000);
  return uVar5;
}


// ===== ovl_1712 @ 1ca8:1712

void ovl_1712(void)

{
  undefined2 *puVar1;
  int iVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 *puVar3;
  undefined2 unaff_DS;
  
  G_diff = G_loc+57 + -1;
  G_pwinxy = G_winxy;
  puVar3 = (undefined2 *)&G_exitdir;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar1 = 0xffff;
  }
  OV_0x132 = 1;
  G_docmbt = 1;
  return;
}


// ===== ovl_174f @ 1ca8:174f

void ovl_174f(void)

{
  char *pcVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  char *pcVar3;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  iVar2 = 6;
  pcVar3 = (char *)&OV_0x1843;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar1 = pcVar3;
    pcVar3 = pcVar3 + 1;
    in_ZF = G_entrno == *pcVar1;
  } while (!(bool)in_ZF);
  if ((bool)in_ZF) {
    EXE_SetBit(&G_events,*(undefined1 *)((unaff_DI - iVar2) + 0x184e));
  }
  return;
}


// ===== ovl_178a @ 1ca8:178a

void ovl_178a(void)

{
  char *pcVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  char *pcVar3;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  iVar2 = 4;
  pcVar3 = (char *)&OV_0x1882;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar1 = pcVar3;
    pcVar3 = pcVar3 + 1;
    in_ZF = OV_0x141 == *pcVar1;
  } while (!(bool)in_ZF);
  if ((bool)in_ZF) {
    EXE_SetBit(&G_events,*(undefined1 *)((unaff_DI - iVar2) + 0x1889));
  }
  return;
}


// ===== ovl_1852 @ 1ca8:1852

void ovl_1852(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar1 = OV_0x13c;
  uVar2 = G_curpla;
  G_curpla = uVar1;
  if ((char)uVar1 != -2) {
    EXE_RoomPgm(OV_0x13c);
  }
  G_othername = G_heroptr;
  G_othername+2 = unaff_DS;
  EXE_AddScrap(G_loc+10);
  EXE_PrtScrap(2,in_BX);
  G_curpla = uVar2;
  return;
}


// ===== FUN_1000_e31d @ 1000:e31d

undefined2 __cdecl16near FUN_1000_e31d(void)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  char local_4;
  
  local_4 = '\0';
  iVar2 = 3;
  do {
    G_zp_15 = G_winy + '\x02' + (char)iVar2;
    iVar3 = 3;
    do {
      G_zp_1415 = G_winxy + '\x03' + (char)iVar3;
      uVar1 = ovl_1926();
      if (OV_0x137 != 0) {
        if (OV_0x140 == local_4) {
          uVar4 = 0;
          while ((*(int *)(uVar4 * 2 + &G_party) == 0xff ||
                 (CONCAT11(*(undefined1 *)(uVar4 + &G_p1y),
                           *(undefined1 *)(uVar4 + &G_p1x)) != G_zp_1415
                 ))) {
            uVar4 = uVar4 + 1;
            if (5 < uVar4) {
              return uVar1;
            }
          }
          return uVar1;
        }
        local_4 = local_4 + '\x01';
      }
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  OV_0x137 = 0;
  return uVar1;
}


// ===== ovl_1926 @ 1ca8:1926

int __cdecl16near ovl_1926(void)

{
  int iVar1;
  char in_DL;
  int *piVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  piVar2 = (int *)G_loc+28;
  OV_0x130 = 0;
  while( true ) {
    if ((char)*piVar2 == '\0') {
      OV_0x137 = 0;
      return 0;
    }
    if ((*piVar2 == G_zp_1415) && ((in_DL == -1 || (in_DL == (char)piVar2[1]))))
    break;
    piVar2 = piVar2 + 3;
    OV_0x130 = OV_0x130 + '\x01';
  }
  iVar1 = piVar2[2];
  OV_0x137 = piVar2;
  return iVar1;
}


// ===== ovl_196b @ 1ca8:196b

void ovl_196b(void)

{
  undefined2 uVar1;
  code *pcVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  char cVar7;
  undefined2 *puVar6;
  uint in_CX;
  undefined2 uVar8;
  int in_BX;
  int unaff_SI;
  uint unaff_DI;
  int unaff_DS;
  bool bVar9;
  int iStack0002;
  
  while( true ) {
    bVar3 = OV_0x12a;
    if ((bVar3 == 0) || (bVar3 == 3)) goto L_198c;
    bVar9 = false;
    if ((bVar3 & 0x80) != 0) break;
    *(undefined1 *)(unaff_DI + 299) = (char)in_CX;
    G_txtptr = &OV_0x167;
    G_txtptr+2 = 0x1000;
    ovl_0cf1();
    iVar5 = EXE_InParty(*(undefined2 *)(unaff_DI + 300));
    if (iVar5 == -1) {
      puVar6 = (undefined2 *)(in_BX + 0x264);
      in_BX = 0;
      EXE_viaptr_puVar6(0x1000);
L_0a39:
      do {
        EXE_Menu(0x10);
        EXE_InitCom(&OV_0x151,0x1000,4);
        while (uVar4 = EXE_Parser(&G_mnuparms,0),
              uVar4 != 0xfd) {
          if (uVar4 == 0xfe) goto L_0a39;
          if (uVar4 == 0xffff) goto L_0a8b;
          if (uVar4 < 2) {
            if (uVar4 == 1) {
              if (G_loc+56 == -1) {
                ovl_0d1d();
                puVar6 = (undefined2 *)(in_BX + 0xec);
                in_BX = 0xff;
                EXE_viaptr_puVar6(0x1000);
                goto L_0a8b;
              }
              iVar5 = EXE_SearchInv(0x50,G_curpla,&OV_0xaf7,
                                 0x1000);
              if (iVar5 == 0) {
                ovl_0d1d();
                puVar6 = (undefined2 *)(in_BX + 0xec);
                in_BX = 0xff;
                EXE_viaptr_puVar6(0x1000);
                goto L_0a8b;
              }
              iVar5 = *(int *)(G_curpla * 2 + &G_heroptr);
              uVar8 = *(undefined2 *)(*(int *)(iVar5 * 2 + &G_heroptr) + 0xf);
              uVar8 = CONCAT11((char)((uint)uVar8 >> 8),
                               ((byte)uVar8 >> 1) + (char)*(undefined2 *)(iVar5 + 0x21));
              bVar3 = EXE_RndCo(100,in_BX,uVar8,iVar5);
              if ((byte)uVar8 < bVar3) {
                EXE_DecObj(iVar5,OV_0xaf9,1);
                ovl_100b();
                goto L_0a8b;
              }
              ovl_0d1d();
              ovl_0d34();
              EXE_PrtScrap();
              puVar6 = (undefined2 *)(in_BX + 0x178);
              in_BX = unaff_DS;
              EXE_viaptr_puVar6(0x1000,G_comtxtptr);
              G_rmdata+5 = 1;
              goto L_0cdd;
            }
            EXE_GameSound(0x11);
            iVar5 = EXE_TimCalc(G_rmdata+3 & 0xff,
                               G_rmdata+3 >> 8);
            if ((iVar5 != 0) &&
               (iVar5 = EXE_FindBit(&G_npcsta,*(undefined2 *)(unaff_DI + 300)),
               iVar5 == 0)) {
              LOCK();
              iVar5 = OV_0xaff;
              OV_0xaff = in_BX;
              UNLOCK();
              uVar4 = *(uint *)(iVar5 + 4);
              LOCK();
              in_BX = OV_0xaff;
              OV_0xaff = iVar5;
              UNLOCK();
              if ((uVar4 == 0) ||
                 ((((char)uVar4 == '\0' ||
                   (iVar5 = EXE_FindBit(&G_events,uVar4 & 0xff), iVar5 != 0)) &&
                  ((cVar7 = (char)(uVar4 >> 8), cVar7 == '\0' ||
                   (iVar5 = EXE_FindBit(&G_events,cVar7), iVar5 == 0)))))) {
                EXE_IModTxt(2);
                EXE_WordIn(&G_wrkstr,0xf);
                EXE_InitScrap();
                EXE_ClrTxtWnd();
                iVar5 = EXE_WMatch(&G_wrkstr,G_loc+18);
                uVar8 = 4;
                if (iVar5 == OV_0x12e) goto L_0cc9;
                EXE_ModTxt(3);
                goto L_0a8b;
              }
            }
            EXE_IModTxt(1);
            goto L_0a8b;
          }
          if (uVar4 < 4) {
            if (uVar4 == 3) goto L_0a8b;
            if (G_loc+56 == -1) {
              ovl_0d1d();
              puVar6 = (undefined2 *)(in_BX + 0xec);
              in_BX = 0xff;
              EXE_viaptr_puVar6(0x1000);
              goto L_0a8b;
            }
            if (G_loc+56 <
                (byte)*(undefined2 *)
                       (*(int *)(G_curpla * 2 + &G_heroptr) + 0xe)) {
              ovl_0d1d();
              ovl_0d34();
              EXE_PrtScrap();
              puVar6 = (undefined2 *)(in_BX + 0x178);
              in_BX = unaff_DS;
              EXE_viaptr_puVar6(0x1000,G_comtxtptr);
              G_rmdata+5 = 2;
              goto L_0cdd;
            }
            ovl_0d1d();
            puVar6 = (undefined2 *)(in_BX + 0xec);
            in_BX = 0xff;
            EXE_viaptr_puVar6(0x1000);
            goto L_0a8b;
          }
        }
        ovl_0e81();
      } while( true );
    }
    OV_0x13c = iVar5;
    puVar6 = (undefined2 *)(in_BX + 0x1b4);
    in_BX = OV_0x13c;
    EXE_viaptr_puVar6(0x1000);
    uVar8 = 5;
L_0cc9:
    EXE_ModTxt(uVar8);
    iVar5 = EXE_SetYN();
    if (iVar5 != 0) {
L_0a8b:
      ovl_1a0f();
      goto L_034e;
    }
L_0cdd:
    OV_0x128 = 0;
    OV_0x12a = 0;
    in_CX = (uint)*(byte *)(unaff_DI + 299);
  }
  ovl_0d70();
  if (bVar9) {
    return;
  }
L_198c:
  puVar6 = (undefined2 *)((in_CX & 0xff) * 4 + G_loc+14);
  uVar8 = *puVar6;
  uVar1 = puVar6[1];
  bVar3 = (byte)uVar8;
  G_curmpg = bVar3;
  if (bVar3 != 2) {
    G_mfxfadein = 0;
  }
  if (bVar3 < 3) {
    G_indisguise = 0;
  }
  G_curtils = (char)((uint)uVar8 >> 8);
  G_curvar = (char)uVar1;
  G_lastdir = OV_0x13e;
  OV_0x132 = 1;
  return;
L_034e:
  ovl_0e6a();
  iStack0002 = 0;
  iVar5 = EXE_Parser();
  if (G_restarting != 0) {
    return;
  }
  if (iVar5 == 0xfd) goto L_0343;
  if (iVar5 == 0xfe) {
L_034b:
    ovl_1a0f();
    in_BX = iStack0002;
    goto L_034e;
  }
  G_lookdata = 0xff;
  if (G_used == -1) {
    bVar9 = G_whspnum != -1;
    if (G_whspnum == -1) {
      if (iVar5 == 5) {
        EXE_LoadOvly(0x1000,0x5d,&OV_0x2100);
        EXE_RoomPgm();
        EXE_Reload91();
        goto L_0343;
      }
      in_BX = iStack0002;
      if (iVar5 == 6) {
        EXE_CalUpd();
        goto L_034e;
      }
      if (iVar5 == 7) {
        EXE_NewFormatn();
        ovl_1a0f();
      }
      else {
        if (((G_curmen != 5) || (uVar4 = iVar5 - 0x31, 8 < uVar4)) ||
           (uVar4 == 4)) goto L_034e;
        OV_0x13e = uVar4;
        uVar4 = *(uint *)(uVar4 * 2 + &OV_0x60d);
        bVar3 = CARRY2(uVar4,unaff_DI);
        (*(code *)(uVar4 + unaff_DI))();
        if (OV_0x132 != '\0') {
          return;
        }
        if ((bVar3 & 1) != 0) {
          EXE_GameSound();
          pcVar2 = INT_0x60_handler;
          (*pcVar2)();
          in_BX = iStack0002;
          goto L_034e;
        }
        (*(code *)*(undefined2 *)(iStack0002 + 200))();
        OV_0x135 = OV_0x135 + '\x01';
        if (0xb < OV_0x135) {
          OV_0x135 = 0;
          OV_0x136 = OV_0x136 + '\x01';
          if ((OV_0x136 & 1) != 0) {
            ovl_0fca();
          }
          EXE_CalUpd();
        }
      }
      ovl_0e9a();
      EXE_GameSound();
      if (G_swtext != '\0') {
        EXE_ClrTxtWnd();
        G_swtext = 0;
      }
      if (G_wlkwcount != '\0') {
        G_wlkwcount = G_wlkwcount + -1;
      }
      ovl_151a();
      in_BX = iStack0002;
      if (OV_0x132 != '\0') {
        return;
      }
      goto L_034e;
    }
    LOCK();
    G_whspnum = 0xff;
    UNLOCK();
    ovl_0830();
    if (bVar9) {
      EXE_SetTxtWnd(1);
      EXE_ClrTxtWnd();
      EXE_InitScrap();
      EXE_AddScrap(G_comtxtptr);
      EXE_PrtScrap();
      in_BX = iStack0002;
      goto L_034e;
    }
  }
  else {
    LOCK();
    bVar3 = G_used;
    G_used = 0xff;
    UNLOCK();
    if (bVar3 == 0x46) {
      ovl_1131();
      goto L_034b;
    }
    if (bVar3 == 0x50) {
      ovl_1044();
      goto L_034b;
    }
    if ((bVar3 != 0x40) &&
       ((bVar9 = bVar3 < 0x3e, bVar3 != 0x3e || (bVar3 = ovl_13c4(), bVar9)))) {
      if (bVar3 == 0x3f) {
        ovl_13ab();
        goto L_0343;
      }
      G_used = bVar3;
      EXE_NoUse();
      in_BX = iStack0002;
      goto L_034e;
    }
  }
L_0343:
  ovl_1a0f();
  ovl_0e81();
  in_BX = iStack0002;
  goto L_034e;
}


// ===== ovl_19cf @ 1ca8:19cf

void ovl_19cf(void)

{
  ovl_028a();
  ovl_19db();
  return;
}


// ===== ovl_19db @ 1ca8:19db

void ovl_19db(void)

{
  return;
}


// ===== ovl_19dc @ 1ca8:19dc

void ovl_19dc(void)

{
  ovl_028a();
  ovl_19ea();
  return;
}


// ===== ovl_19ea @ 1ca8:19ea

void ovl_19ea(void)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 in_BX;
  int unaff_DI;
  
  OV_0x1ae8 = 5;
  iVar2 = 6;
  do {
    LOCK();
    uVar1 = OV_0x1ae8;
    OV_0x1ae8 = in_BX;
    UNLOCK();
    LOCK();
    in_BX = OV_0x1ae8;
    OV_0x1ae8 = uVar1;
    UNLOCK();
    OV_0x1ae8 = OV_0x1ae8 + -1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


// ===== ovl_1a0f @ 1ca8:1a0f

void ovl_1a0f(void)

{
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_Menu(0x1ca8,5);
  EXE_InitCom(0x1ca8,&OV_0x143,0x1ca8,0xe,in_BX);
  return;
}


// ===== ovl_1a2e @ 1ca8:1a2e

void ovl_1a2e(void)

{
  code *pcVar1;
  
  ovl_028a();
  pcVar1 = INT_0x60_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_1a7a @ 1ca8:1a7a

void ovl_1a7a(void)

{
  code *pcVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_028a();
  pcVar1 = INT_0x60_handler;
  iVar2 = (*pcVar1)();
  if (iVar2 != -1) {
    EXE_SetTxtWnd(0x1ca8,1,in_BX,iVar2);
    EXE_ClrTxtWnd(0x1ca8);
    EXE_InitScrap(0x1ca8);
    EXE_AddScrap(0x1ca8,G_comtxtptr);
    EXE_AddScrap(0x1ca8,G_comtxtptr);
    EXE_PrtScrap(0x1ca8,0xff,in_BX);
  }
  return;
}


