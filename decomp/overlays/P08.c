// ===== ovl_0400 @ 1ca8:0400

int ovl_0400(void)

{
  return iRam000004f8 + -0x100;
}


// ===== ovl_041d @ 1ca8:041d

void ovl_041d(void)

{
  undefined1 uVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  int in_BX;
  int iVar6;
  int *piVar7;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar8;
  int iStack0008;
  
  ovl_0400();
  G_curbfl = 0xff;
  G_winxy = 0;
  G_curseg = 0;
  OV_0x1c9 = 0;
  OV_0x1c8 = 0;
  OV_0x152 = 0;
  G_txtptr = &OV_0x223;
  G_txtptr+2 = 0x1000;
  iVar4 = 4;
  iVar6 = 0;
  do {
    *(undefined2 *)(iVar6 + &OV_0x148) = *(undefined2 *)(iVar6 + &G_rmdata);
    iVar6 = iVar6 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  OV_0x1d0 = 0xff;
  G_swgreet = 2;
  ovl_13e9();
  ovl_1484();
  EXE_FixMusRegs();
  EXE_InitMap();
  EXE_NewLoc&G_loc+40;
  G_currm = (uint)OV_0x148;
  G_locspec = (uint)OV_0x14f;
  EXE_ProAss();
  iStack0008 = in_BX;
  EXE_InitMap();
  if ((G_events+15 & 4) != 0) {
    OV_0x1d2 = 1;
  }
  ovl_13bb();
  ovl_1541();
  ovl_1581();
  ovl_15c7();
  ovl_0c92();
  if (OV_0x1d2 != '\0') {
    EXE_song();
    EXE_ClrMnuWnd();
    G_curmen = 9;
    if (0x13 < *(uint *)(unaff_SI + 2)) {
      *(int *)(unaff_SI + 4) = *(int *)(unaff_SI + 4) + 1;
    }
    *(undefined2 *)(unaff_SI + 2) = 0x14;
    EXE_CalUpd();
    ovl_1855();
    EXE_PrtWrd();
    ovl_09df();
    ovl_1855();
    EXE_SetBit();
    EXE_finishsong();
L_0906:
    ovl_13bb();
    ovl_15c7();
    do {
      EXE_Menu();
      EXE_InitCom();
      while( true ) {
        iVar4 = EXE_Parser();
        if (iVar4 == 0xfd) goto L_0906;
        if (iVar4 == 0xfe) break;
        if (iVar4 == 0) {
          EXE_XQSRGame();
          if (G_restarting != 0) {
            return;
          }
          goto L_0906;
        }
      }
    } while( true );
  }
L_04e0:
  EXE_Menu();
  EXE_InitCom();
  iVar4 = iStack0008;
L_04fe:
  do {
    while( true ) {
      ovl_13a4();
      G_lookprt = 0;
      G_lookdata = 0xff;
      iStack0008 = 0;
      uVar3 = EXE_Parser();
      if (G_restarting != 0) {
        return;
      }
      if (uVar3 == 0xfd) goto L_04d2;
      if (uVar3 == 0xfe) goto L_04e0;
      iVar4 = iStack0008;
      if (uVar3 != 6) break;
      EXE_CalUpd();
    }
    if (uVar3 == 5) {
      EXE_LoadOvly();
      EXE_RoomPgm();
      EXE_Reload91();
      goto L_04d2;
    }
    if (G_swgreet == -2) {
      ovl_1034();
      iVar4 = iStack0008;
      if (OV_0x152 != 0) {
L_0772:
        iStack0008 = iVar4;
        if ((G_events+15 & 1) != 0) {
          ovl_187e();
          G_curpla = 0;
          G_events+15 = G_events+15 | 2;
          ovl_13bb();
          FUN_1000_e310();
          ovl_15c7();
          OV_0x1d0 = 1;
          ovl_1855();
          EXE_HighStat();
          ovl_1855();
          if ((G_events+15 & 8) == 0) {
            iStack0008 = 0x1000;
            EXE_SearchInv();
            G_curpla = OV_0x15f;
            ovl_1855();
            EXE_GameSound();
            G_curpla = 0;
            ovl_1855();
            ovl_0c41();
            iVar4 = G_savebx;
            EXE_ClrMnuWnd();
            EXE_SetTxtWnd();
            EXE_ClrTxtWnd();
            EXE_InitScrap();
            EXE_AddScrap();
            EXE_PrtScrap();
            EXE_PrtWrd();
            G_restarting = 0xffff;
          }
          else {
            ovl_1855();
            EXE_GameSound();
            FUN_1000_e334();
            EXE_HighStat();
            ovl_1855();
            G_events+15 = G_events+15 | 4;
            EXE_GameSound();
            ovl_13bb();
            FUN_1000_e310();
            ovl_15c7();
            ovl_1855();
            ovl_1855();
            ovl_1855();
            ovl_1855();
            OV_0x1c9 = 0x49;
            LOCK();
            iVar6 = G_loc+16;
            G_loc+16 = iVar4;
            UNLOCK();
            *(undefined1 *)(iVar6 + 2) = 1;
            *(undefined1 *)(iVar6 + 5) = 0x10;
            LOCK();
            iStack0008 = G_loc+16;
            G_loc+16 = iVar6;
            UNLOCK();
          }
        }
        if (OV_0x1c9 != '\0') {
          ovl_0f20();
        }
        uVar2 = *(undefined2 *)
                 ((uint)*(byte *)(OV_0x152 + 2) * 4 + G_loc+14)
        ;
        bVar5 = (byte)uVar2;
        G_curmpg = bVar5;
        if (bVar5 < 3) {
          G_currm = 0xff;
        }
        G_curtils = (char)((uint)uVar2 >> 8);
        uVar1 = *(undefined1 *)(OV_0x152 + 5);
        G_pwinxy = *(undefined2 *)(OV_0x152 + 3);
        G_curvar = uVar1;
        if (G_curmpg == '\x01') {
          G_curvar = 0xff;
        }
        G_swgreet = 0;
        G_lookprt = 1;
        EXE_ClrTxtWnd();
        return;
      }
      goto L_04d2;
    }
    if (G_used == -1) {
      bVar8 = G_whspnum != -1;
      if (G_whspnum == -1) {
        if ((G_mnusel == '\x19') && (G_lookdata != -1)) {
          if ((OV_0x1c5 == 0) || (G_lookdata != 'c')) {
            EXE_PrtScrap();
            G_lookdata = 0xff;
          }
          else {
            ovl_16e9();
            G_lookdata = 0xff;
          }
          goto L_04d2;
        }
        if ((uVar3 < 0x3a) && (G_curmen == '\x05')) {
          if ((OV_0x1c3 == '\0') || ((byte)uVar3 < 0x37)) {
            iVar6 = EXE_RMove();
            if (iVar6 == 2) {
              OV_0x152 = G_loc+16;
L_06fa:
              if ((OV_0x1c5 == 0) || (OV_0x1c3 != 0)) {
                EXE_SetTxtWnd();
                EXE_ClrTxtWnd();
                EXE_InitScrap();
                EXE_AddScrap(0x1000);
                iStack0008 = 0;
                EXE_PrtScrap();
                iVar6 = EXE_SetYN();
                iVar4 = iStack0008;
                if (iVar6 == 0) goto L_0772;
              }
              else {
                EXE_HighStat();
                EXE_SetTxtObj();
                EXE_IModTxt();
              }
              goto L_04e0;
            }
            if (iVar6 == 1) {
              for (piVar7 = (int *)G_loc+16; (char)*piVar7 != -1;
                  piVar7 = piVar7 + 3) {
                if (G_zp_1415 == *piVar7) {
                  OV_0x152 = piVar7;
                  goto L_06fa;
                }
              }
              EXE_GameSound();
            }
            else if ((iVar6 == 0) && (G_swtext != '\0')) {
              EXE_ClrTxtWnd();
              G_swtext = 0;
            }
          }
          else {
            EXE_IModTxt();
          }
        }
        goto L_04fe;
      }
      ovl_101c();
      if (bVar8) {
        if (((G_locspec == '\x01') &&
            (bVar8 = G_currm < 5, G_currm == 5)) &&
           (ovl_1339(), !bVar8)) goto L_05e9;
      }
      else if (((G_events+3 & 4) == 0) &&
              (G_whspnum == '\x01')) break;
      EXE_SetTxtWnd();
      EXE_ClrTxtWnd();
      EXE_InitScrap();
      EXE_AddScrap();
      EXE_PrtScrap();
      G_whspnum = 0xff;
      iVar4 = iStack0008;
      goto L_04fe;
    }
    LOCK();
    bVar5 = G_used;
    G_used = 0xff;
    UNLOCK();
    if (bVar5 == 0x40) goto L_04d2;
    bVar8 = bVar5 < 0x49;
    if (bVar5 == 0x49) {
      ovl_0d8e();
      if (!bVar8) goto L_04d2;
      bVar5 = 0x49;
    }
    G_used = bVar5;
    EXE_NoUse();
    iVar4 = iStack0008;
  } while( true );
  ovl_12e1();
L_05e9:
  G_whspnum = 0xff;
L_04d2:
  EXE_InitMap();
  ovl_13bb();
  ovl_1541();
  ovl_15c7();
  goto L_04e0;
}


// ===== ovl_099d @ 1ca8:099d

void ovl_099d(void)

{
  char *pcVar1;
  char cVar2;
  uint in_AX;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  LOCK();
  pcVar1 = (char *)(in_AX + &OV_0xa5c);
  cVar2 = *pcVar1;
  *pcVar1 = '\x01';
  UNLOCK();
  if (cVar2 == '\0') {
    G_othername = (in_AX & 0xff) * 0xdc + &G_member0+1271;
    G_othername+2 = unaff_DS;
    ovl_1855();
    EXE_PrtWrd(G_comtxtptr);
  }
  return;
}


// ===== ovl_09df @ 1ca8:09df

void ovl_09df(void)

{
  undefined2 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int in_BX;
  int iVar6;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  int iStack0002;
  
  (*(code *)*(undefined2 *)(in_BX + 100))(&OV_0xa5c,0x1ca8,0x20,0);
  OV_0xa5c = 1;
  OV_0xa76 = 1;
  iVar4 = 0x1f;
  iVar6 = &G_member6;
  iVar5 = 0;
  do {
    if ((*(byte *)(iVar6 + 0x16) & 0x80) != 0) {
      puVar1 = (undefined2 *)(G_savebx + 0x280);
      iVar2 = EXE_InParty(0x1000,-(iVar4 + -0x20));
      if (iVar2 == -1) {
        iVar5 = iVar5 + 1;
      }
    }
    iVar6 = iVar6 + 0xdc;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  OV_0xa9c = (char)iVar5;
  ovl_1855();
  ovl_1855();
  EXE_PrtWrd(G_comtxtptr);
  uVar3 = EXE_CntPar();
  if (2 < uVar3) {
    ovl_1855();
    iStack0002 = 0;
    EXE_PrtWrd(G_comtxtptr);
    iVar6 = 2;
    iVar4 = 5;
    in_BX = iStack0002;
    do {
      if ((char)*(undefined2 *)(iVar6 + &G_party) != -1) {
        ovl_099d();
      }
      iVar6 = iVar6 + 2;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  if (OV_0xa9c != '\0') {
    ovl_1855();
    EXE_PrtWrd(G_comtxtptr);
    iVar4 = 0x1f;
    iVar6 = &G_member6;
    do {
      if ((*(byte *)(iVar6 + 0x16) & 0x80) != 0) {
        ovl_099d();
      }
      iVar6 = iVar6 + 0xdc;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  ovl_1855();
  ovl_1855();
  return;
}


// ===== ovl_0af8 @ 1ca8:0af8

void ovl_0af8(void)

{
  char *pcVar1;
  int iVar2;
  char cVar3;
  char cVar4;
  undefined1 uVar5;
  undefined2 *puVar6;
  int iVar7;
  undefined2 uVar8;
  int iVar9;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar9 = 0;
  iVar7 = 6;
  OV_0xbf6 = G_heroptr;
  OV_0xbf4 = &G_herotiles;
  do {
    LOCK();
    pcVar1 = (char *)OV_0xbf6;
    OV_0xbf6 = iVar9;
    UNLOCK();
    pcVar1[0xbf] = -1;
    cVar3 = *pcVar1;
    cVar4 = pcVar1[8];
    LOCK();
    iVar9 = OV_0xbf6;
    OV_0xbf6 = (int)pcVar1;
    UNLOCK();
    if (cVar3 != '\0') {
      puVar6 = (undefined2 *)(G_savebx + 0xac);
      EXE_SetPlTilNo(0x1000,6 - iVar7);
      if (cVar4 == '\x1a') {
        LOCK();
        iVar2 = OV_0xbf4;
        OV_0xbf4 = iVar9;
        UNLOCK();
        uVar5 = *(undefined1 *)(iVar2 + 6);
        LOCK();
        iVar9 = OV_0xbf4;
        OV_0xbf4 = iVar2;
        UNLOCK();
        *(undefined1 *)((unaff_SI - iVar7) + -0x700c) = uVar5;
        uVar8 = OV_0xbf2;
      }
      else {
        LOCK();
        iVar2 = OV_0xbf4;
        OV_0xbf4 = iVar9;
        UNLOCK();
        uVar5 = *(undefined1 *)(iVar2 + 2);
        LOCK();
        iVar9 = OV_0xbf4;
        OV_0xbf4 = iVar2;
        UNLOCK();
        *(undefined1 *)((unaff_SI - iVar7) + -0x700c) = uVar5;
        uVar8 = *(undefined2 *)(iVar9 + &OV_0xbe8);
        iVar9 = iVar9 + 2;
      }
      *(undefined1 *)((6 - iVar7) + &G_p1x) = (char)uVar8;
      *(undefined1 *)((6 - iVar7) + &G_p1y) = (char)((uint)uVar8 >> 8);
    }
    OV_0xbf6 = OV_0xbf6 + 0xdc;
    OV_0xbf4 = OV_0xbf4 + 0xe;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  ovl_15c7();
  return;
}


// ===== ovl_0c41 @ 1ca8:0c41

void ovl_0c41(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_1a6e();
  iVar1 = 6;
  do {
    iVar2 = (iVar1 - 1U) * 2;
    if (*(int *)(iVar2 + &G_party) != 0xff) {
      uVar3 = iVar1 - 1U & 0x7fff;
      FUN_1000_e406(*(undefined1 *)(uVar3 + &G_pltilno),
                    CONCAT11(*(undefined1 *)(uVar3 + &G_p1y),
                             *(undefined1 *)(uVar3 + &G_p1x)));
      *(undefined2 *)(iVar2 + &G_party) = 0xff;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  FUN_1000_e406(*(undefined1 *)((uint)G_npclocs+3 + &G_npctile));
  return;
}


// ===== ovl_0c92 @ 1ca8:0c92

void ovl_0c92(void)

{
  int iVar1;
  char cVar2;
  int in_BX;
  int iVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined2 in_stack_00000000;
  undefined2 uVar4;
  
  if ((G_currm == 0) && (G_locspec == 1)) {
    LOCK();
    iVar1 = G_heroptr;
    G_heroptr = in_BX;
    UNLOCK();
    cVar2 = *(char *)(iVar1 + 0x52);
    LOCK();
    iVar3 = G_heroptr;
    G_heroptr = iVar1;
    UNLOCK();
    if ((cVar2 == -1) && ((G_events+3 & 0x10) == 0)) {
      if ((G_events+3 & 8) == 0) {
        if ((G_events+12 & 0x80) == 0) {
          uVar4 = G_curpla;
          G_curpla = 0;
          OV_0x1d0 = 2;
          ovl_1855(uVar4);
          OV_0x1d0 = 0xff;
          EXE_IncObj(G_heroptr,0x55,1,iVar3);
          G_events+12 = G_events+12 | 0x80;
          G_curpla = in_stack_00000000;
        }
      }
      else {
        uVar4 = G_curpla;
        G_curpla = 0;
        OV_0x1d0 = 2;
        ovl_1855(uVar4);
        OV_0x1d0 = 0xff;
        EXE_IncObj(G_heroptr,0x58,1,iVar3);
        G_events+3 = G_events+3 | 0x10;
        G_curpla = in_stack_00000000;
      }
    }
  }
  else if (((G_currm == 6) && (G_locspec == 0x38)) &&
          ((G_events+11 & 0x40) == 0)) {
    uVar4 = G_curpla;
    G_curpla = 0;
    EXE_IModTxt(0xc);
    G_curpla = uVar4;
  }
  return;
}


// ===== ovl_0d8e @ 1ca8:0d8e

void ovl_0d8e(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  int iVar1;
  
  if (((G_locspec != 1) || (G_currm != 5)) ||
     (OV_0x1c8 != '\0')) {
    return;
  }
  if ((G_events+4 & 0x1c) == 0x1c) {
    EXE_GameSound(10);
    iVar1 = G_savebx;
    EXE_Spef6(CONCAT11(*(undefined1 *)(G_curpla + &G_p1y),
                               *(undefined1 *)(G_curpla + &G_p1x)),
               G_curpla);
    EXE_IModTxt(0xe,iVar1);
    G_mapyl+27 = 0x1011;
    G_mapyl+38 = 0x1514;
    OV_0x1c8 = 1;
    return;
  }
  EXE_InitScrap();
  EXE_ClrTxtWnd();
  EXE_AddScrap(G_comtxtptr);
  EXE_HighStat(0x14);
  EXE_AddScrap(&OV_0x223,0x1000,0xf);
  EXE_PrtScrap(2,in_BX);
  return;
}


// ===== ovl_0e86 @ 1ca8:0e86

void ovl_0e86(void)

{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int in_BX;
  int iVar6;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  LOCK();
  iVar4 = G_heroptr;
  G_heroptr = in_BX;
  UNLOCK();
  cVar1 = *(char *)(iVar4 + 0x52);
  LOCK();
  iVar6 = G_heroptr;
  G_heroptr = iVar4;
  UNLOCK();
  if (cVar1 != -1) {
    OV_0xf84 = 0;
    if (OV_0x1cc != 0x49) {
      OV_0xf84 = OV_0xf84 + 1;
    }
    do {
      do {
        LOCK();
        iVar4 = OV_0xf84;
        OV_0xf84 = iVar6;
        UNLOCK();
        uVar2 = *(undefined1 *)(iVar4 + 0xf49);
        LOCK();
        iVar6 = OV_0xf84;
        OV_0xf84 = iVar4 + 1;
        UNLOCK();
        iVar4 = EXE_SearchInv(uVar2,0,&OV_0x15b,0x1000);
      } while (iVar4 == 0);
      uVar3 = OV_0x15b >> 8;
      uVar5 = OV_0x15b & 0xff;
      if ((8 < uVar3) && (uVar3 < 0x31)) {
        uVar5 = 1;
      }
      G_suppresstext = 1;
      iVar4 = EXE_DecObj0(uVar3,uVar5);
      G_suppresstext = 0;
    } while (iVar4 == 0);
  }
  EXE_IncObj(G_heroptr,OV_0x1cc,1,iVar6);
  return;
}


// ===== ovl_0f20 @ 1ca8:0f20

void ovl_0f20(void)

{
  int iVar1;
  undefined2 uVar2;
  int in_BX;
  int iVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  LOCK();
  iVar1 = G_loc;
  G_loc = in_BX;
  UNLOCK();
  uVar2 = *(undefined2 *)(iVar1 + 3);
  LOCK();
  iVar3 = G_loc;
  G_loc = iVar1;
  UNLOCK();
  G_rmdata = (char)uVar2;
  G_rmdata+6 = (char)((uint)uVar2 >> 8);
  G_rmdata+7 = 3;
  G_curpla = 0;
  EXE_PrtW3();
  EXE_SumStat();
  ovl_100c();
  EXE_SetTxtWnd(0);
  EXE_ClrTxtWnd();
  EXE_SetTxtWnd(1);
  if (OV_0x1c9 == 'L') {
    EXE_ClrTxtWnd();
    EXE_ClrMnuWnd();
    EXE_InitScrap();
    EXE_AddScrap(G_loc+10);
    EXE_PrtScrap(1);
  }
  ovl_0fb9();
  if (OV_0x1c9 == 'L') {
    EXE_PrtWrd(G_comtxtptr);
  }
  return;
}


// ===== ovl_0fb9 @ 1ca8:0fb9

void ovl_0fb9(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  int iVar5;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar1 = G_cursorx;
  uVar2 = G_cursory;
  uVar3 = G_txtbkgd;
  EXE_SetTxtWnd(0);
  iVar5 = 0x50;
  do {
    uVar4 = EXE_RndCo(0x100);
    G_txtbkgd = uVar4;
    EXE_ClrTxtWnd();
    EXE_GameSound(0xe);
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  EXE_SetTxtWnd(1,in_BX);
  G_txtbkgd = uVar3;
  G_cursory = uVar2;
  G_cursorx = uVar1;
  return;
}


// ===== ovl_100c @ 1ca8:100c

void ovl_100c(void)

{
  undefined1 *puVar1;
  int iVar2;
  int unaff_SI;
  undefined1 *puVar3;
  undefined2 unaff_DS;
  
  puVar3 = (undefined1 *)&G_secwin;
  for (iVar2 = 99; iVar2 != 0; iVar2 = iVar2 + -1) {
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar1 = 0xff;
  }
  return;
}


// ===== ovl_101c @ 1ca8:101c

void ovl_101c(void)

{
  char in_AL;
  int iVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar2 = &G_npclocs;
  iVar1 = 0x32;
  do {
    if (in_AL == *(char *)(iVar2 + 4)) {
      return;
    }
    iVar2 = iVar2 + 5;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_1034 @ 1ca8:1034

/* WARNING: Possible PIC construction at 0x0001dd25: Changing call to branch */
/* WARNING: Possible PIC construction at 0x0001dd3f: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0001dd28) */
/* WARNING: Removing unreachable block (ram,0x0001dd42) */

void ovl_1034(undefined2 param_1)

{
  undefined2 *puVar1;
  char cVar2;
  int iVar3;
  undefined2 uVar4;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar5;
  undefined2 in_stack_00000000;
  
  uVar4 = 0x1ca8;
  G_swgreet = 2;
  if (G_npcno == 'H') {
    if ((G_curpla == '\0') && ((G_events+1 & 0x20) == 0)) {
      EXE_IModTxt(0);
      EXE_PrtWrd(G_comtxtptr);
      iVar3 = EXE_SearchInv(0x11,0xffff,&OV_0x15b,0x1ca8);
      if (iVar3 != 0) {
        OV_0x1194 = 0xff;
      }
      OV_0x1ca = &OV_0x1192;
      while( true ) {
        LOCK();
        puVar1 = (undefined2 *)OV_0x1ca;
        OV_0x1ca = in_BX;
        UNLOCK();
        uVar4 = *puVar1;
        LOCK();
        in_BX = OV_0x1ca;
        OV_0x1ca = (int)puVar1;
        UNLOCK();
        cVar2 = (char)uVar4;
        if (cVar2 == -1) break;
        OV_0x1cc = cVar2;
        OV_0x1ce = (char)((uint)uVar4 >> 8);
        iVar3 = EXE_IncObj(G_heroptr,
                           OV_0x1cc,OV_0x1ce);
        if (iVar3 == 0) goto L_1169;
        if (OV_0x1cc == 0x11) {
          EXE_IModTxt(0x10);
        }
        else {
          EXE_SetTxtObj(OV_0x1cc);
          G_deftxtparms+2 = (char)OV_0x1ce;
          EXE_IModTxt(1);
        }
        EXE_PrtWrd(G_comtxtptr);
        OV_0x1ca = OV_0x1ca + 2;
      }
      G_events+1 = G_events+1 | 0x20;
L_1169:
      EXE_ClrTxtWnd(in_BX);
      return;
    }
  }
  else {
    uVar4 = 0x1000;
    if (OV_0x1c3 != 0) {
      EXE_IModTxt(5);
      return;
    }
    if (G_npcno != -0x62) {
      if (OV_0x1c7 == '\0') {
        return;
      }
      uVar4 = 0x1000;
      if (G_npcno == 0x93) {
        uVar4 = 0x1000;
        bVar5 = (OV_0x1c7 & 0x20) == 0;
        if (bVar5) {
          ovl_1394();
          if (!bVar5) goto L_108b;
          if (*(int *)(G_curpla * 2 + &G_party) == 0x1a) {
            OV_0x1d0 = 1;
            uVar4 = 6;
          }
          else {
            uVar4 = 5;
          }
        }
        else {
          uVar4 = 2;
        }
      }
      else {
        if ((OV_0x1c7 & 7) != 7) goto L_108b;
        if ((OV_0x1c7 & 0x10) == 0) {
          if ((G_events+10 & 0x20) == 0) {
            uVar4 = G_curpla;
            G_curpla = 0;
            OV_0x1d0 = 1;
            ovl_12ce(uVar4);
            OV_0x1cc = 0x4f;
            ovl_0e86();
            G_events+10 = G_events+10 | 0x20;
            G_curpla = param_1;
            return;
          }
          OV_0x1d0 = 1;
          uVar4 = 1;
        }
        else {
          uVar4 = 0x1000;
          if ((OV_0x1c7 & 8) == 0) goto L_108b;
          uVar4 = 0x1000;
          bVar5 = (OV_0x1c7 & 0x20) == 0;
          if (bVar5) {
            ovl_1394();
            if (!bVar5) goto L_108b;
            if (*(int *)(G_curpla * 2 + &G_party) == 0x1a) {
              uVar4 = 3;
            }
            else {
              uVar4 = 4;
            }
          }
          else {
            uVar4 = 2;
          }
        }
      }
      EXE_Offer1(in_BX,uVar4);
      ovl_1862();
      OV_0x1d0 = 0xff;
      return;
    }
    if ((G_events+11 & 0x40) == 0) {
      EXE_SetBit(&G_met,0x9e);
      uVar4 = G_curpla;
      G_curpla = 0;
      EXE_IModTxt(0xd,in_BX,uVar4);
      OV_0x1cc = 0x49;
      ovl_0e86();
      G_events+11 = G_events+11 | 0x40;
      G_curpla = in_stack_00000000;
      EXE_PrtWrd(G_comtxtptr);
      puVar1 = (undefined2 *)G_loc+16;
      OV_0x152 = puVar1;
      G_zp_1415 = *puVar1;
      return;
    }
  }
L_108b:
  EXE_GreetKNPC(uVar4,in_BX);
  return;
}


// ===== ovl_12e1 @ 1ca8:12e1

void ovl_12e1(void)

{
  int iVar1;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_npcno = 0x39;
  EXE_IModTxt(2);
  EXE_PrtWrd(G_comtxtptr);
  iVar1 = EXE_IncObj(*(undefined2 *)(G_curpla * 2 + &G_heroptr),0x5a,
                     1);
  if (iVar1 != 0) {
    EXE_IModTxt(3,in_BX);
    G_events+3 = G_events+3 | 4;
  }
  return;
}


// ===== ovl_1339 @ 1ca8:1339

void ovl_1339(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if ((G_whspnum != '\0') || ((G_events+15 & 1) != 0)) {
    return;
  }
  if (OV_0x1c8 == '\0') {
    ovl_1855();
    return;
  }
  if (*(int *)(G_curpla * 2 + &G_party) == 0x1a) {
    EXE_GameSound(0x1a);
    ovl_1855();
    G_mapyl+38 = 0x1716;
    G_events+15 = G_events+15 | 1;
    return;
  }
  ovl_1855();
  return;
}


// ===== ovl_1394 @ 1ca8:1394

void ovl_1394(void)

{
  int *piVar1;
  int in_AX;
  int iVar2;
  int unaff_SI;
  int *piVar3;
  undefined2 unaff_DS;
  
  iVar2 = 6;
  piVar3 = (int *)&G_party;
  do {
    if (iVar2 == 0) {
      return;
    }
    iVar2 = iVar2 + -1;
    piVar1 = piVar3;
    piVar3 = piVar3 + 1;
  } while (in_AX != *piVar1);
  return;
}


// ===== ovl_13a4 @ 1ca8:13a4

void ovl_13a4(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (*(int *)(unaff_SI + 2) != OV_0x155) {
    ovl_13bb();
    EXE_InitMap();
    ovl_15c7();
  }
  return;
}


// ===== ovl_13bb @ 1ca8:13bb

void ovl_13bb(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_InitNPC();
  OV_0x155 = *(undefined2 *)(unaff_SI + 2);
  if (OV_0x1d2 != '\0') {
    ovl_0af8();
  }
  if (G_scrollonfloor != '\0') {
    OV_0x1c5 = G_scrollonfloor;
    G_mapyl+28 = 99;
  }
  return;
}


// ===== ovl_13e9 @ 1ca8:13e9

void ovl_13e9(void)

{
  int *piVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  int unaff_SI;
  undefined2 *puVar6;
  int unaff_DI;
  undefined2 *puVar7;
  undefined2 unaff_DS;
  
  G_rmtyp = 0;
  OV_0x157 = 0;
  puVar6 = (undefined2 *)*(undefined2 *)((G_rmdata + 1) * 2 + &G_loc)
  ;
  puVar7 = (undefined2 *)&G_loc;
  for (iVar4 = 0x9e3; iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar3 = puVar7;
    puVar7 = puVar7 + 1;
    puVar2 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar3 = *puVar2;
  }
  for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar3 = puVar7;
    puVar7 = (undefined2 *)((int)puVar7 + 1);
    puVar2 = puVar6;
    puVar6 = (undefined2 *)((int)puVar6 + 1);
    *(undefined1 *)puVar3 = *(undefined1 *)puVar2;
  }
  iVar4 = 0x14;
  iVar5 = 0;
  do {
    piVar1 = (int *)(iVar5 + &G_loc);
    *piVar1 = *piVar1 + &G_loc;
    iVar5 = iVar5 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  OV_0x154 =
       (char)((uint)*(undefined2 *)G_loc+8 >> 8);
  ovl_1507();
  return;
}


// ===== ovl_1484 @ 1ca8:1484

void ovl_1484(void)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int in_BX;
  char *pcVar7;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar3 = 0;
  OV_0x150 = 0;
  pcVar7 = (char *)G_loc+16;
  while( true ) {
    if (*pcVar7 == -1) break;
    OV_0x150 = OV_0x150 + '\x01';
    if (*pcVar7 == '\0') {
      uVar3 = uVar3 | 2;
    }
    else if (pcVar7[1] == '\0') {
      uVar3 = uVar3 | 4;
    }
    else if (*pcVar7 == '\n') {
      uVar3 = uVar3 | 8;
    }
    else if (pcVar7[1] == '\b') {
      uVar3 = uVar3 | 0x10;
    }
    pcVar7 = pcVar7 + 6;
  }
  OV_0x151 = (byte)uVar3;
  if (1 < OV_0x150) {
    if ((G_lastdir & 1) == 0) {
      uVar3 = (uint)((byte)uVar3 & *(byte *)((G_lastdir >> 1) + &OV_0x1ac)
                    );
    }
    else {
      LOCK();
      iVar1 = G_lastdir;
      G_lastdir = in_BX;
      UNLOCK();
      uVar3 = (uint)*(byte *)(iVar1 + &OV_0x1a3);
      LOCK();
      G_lastdir = iVar1;
      UNLOCK();
    }
  }
  iVar1 = *(int *)(uVar3 + &OV_0x183);
  iVar6 = 0;
  iVar4 = 6;
  do {
    if (*(int *)(iVar6 * 2 + &G_party) != 0xff) {
      pcVar7 = (char *)&G_formatn;
      iVar5 = 9;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar2 = pcVar7;
        pcVar7 = pcVar7 + 1;
      } while ((char)iVar6 != *pcVar2);
      iVar5 = CONCAT11(*(undefined1 *)((8 - iVar5) + &OV_0x17a),
                       *(undefined1 *)((8 - iVar5) + &OV_0x171)) + iVar1;
      *(undefined1 *)(iVar6 + &G_p1x) = (char)iVar5;
      *(undefined1 *)(iVar6 + &G_p1y) = (char)((uint)iVar5 >> 8);
    }
    iVar6 = iVar6 + 1;
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
      return;
    }
  } while( true );
}


// ===== ovl_1507 @ 1ca8:1507

void ovl_1507(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined1 in_DL;
  int in_BX;
  int unaff_SI;
  undefined2 *puVar4;
  int unaff_DI;
  undefined2 *puVar5;
  undefined2 unaff_DS;
  
  EXE_LoadMap(in_DL,0,0x47);
  if (OV_0x154 != 0) {
    puVar5 = (undefined2 *)&G_thismap;
    puVar4 = (undefined2 *)((int)puVar5 + (uint)OV_0x154 * 0x65);
    for (iVar3 = 0x32; iVar3 != 0; iVar3 = iVar3 + -1) {
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
  }
  return;
}


// ===== ovl_1541 @ 1ca8:1541

int ovl_1541(void)

{
  int iVar1;
  int iVar2;
  int in_BX;
  int unaff_DI;
  undefined1 uVar3;
  
  uVar3 = 0;
  OV_0x1c3 = 0;
  OV_0x159 = 0;
  iVar2 = 3;
  do {
    LOCK();
    iVar1 = OV_0x159;
    OV_0x159 = in_BX;
    UNLOCK();
    LOCK();
    in_BX = OV_0x159;
    OV_0x159 = iVar1 + 1;
    UNLOCK();
    iVar1 = ovl_101c();
    if (!(bool)uVar3) {
      iVar1 = OV_0x159;
      OV_0x1c3 = iVar1;
      OV_0x1c5 =
           CONCAT11((char)((uint)iVar2 >> 8),*(undefined1 *)(iVar1 + &OV_0x1b6));
      return iVar1;
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return iVar1;
}


// ===== ovl_1581 @ 1ca8:1581

void ovl_1581(void)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  
  OV_0x1c7 = 0;
  iVar2 = 4;
  bVar3 = 1;
  iVar1 = 0x90;
  do {
    ovl_101c(iVar1);
    if (!(bool)in_CF) {
      OV_0x1c7 = OV_0x1c7 | bVar3;
    }
    iVar1 = iVar1 + 1;
    in_CF = (char)bVar3 < '\0';
    bVar3 = bVar3 << 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (((OV_0x1c7 != '\0') && ((G_events+10 & 0x20) != 0)) &&
     (OV_0x1c7 = OV_0x1c7 | 0x10,
     (G_events+14 & 8) != 0)) {
    OV_0x1c7 = OV_0x1c7 | 0x20;
  }
  return;
}


// ===== ovl_15c7 @ 1ca8:15c7

void ovl_15c7(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_FillWindow(0,0);
  return;
}


// ===== ovl_15d5 @ 1ca8:15d5

void ovl_15d5(void)

{
  uint uVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  undefined2 *puVar4;
  undefined1 extraout_AH;
  uint in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  uint uVar5;
  
  ovl_0400();
  if (OV_0x1c3 == 0) {
    EXE_IComTxt(0x24,in_BX);
  }
  else {
    LOCK();
    uVar1 = OV_0x1c3;
    OV_0x1c3 = in_BX;
    UNLOCK();
    uVar3 = *(undefined2 *)(uVar1 * 2 + &OV_0x1bb);
    LOCK();
    uVar5 = OV_0x1c3;
    OV_0x1c3 = uVar1 & 0x7fff;
    UNLOCK();
    OV_0x32e = uVar3;
    EXE_IModTxt(6);
    LOCK();
    uVar1 = OV_0x1c3;
    OV_0x1c3 = uVar5;
    UNLOCK();
    uVar2 = *(undefined1 *)(uVar1 + &OV_0x1b0);
    LOCK();
    uVar5 = OV_0x1c3;
    OV_0x1c3 = uVar1;
    UNLOCK();
    puVar4 = (undefined2 *)(uVar5 + 0xe0);
    EXE_SetBit(0x1000,&G_events,CONCAT11(extraout_AH,uVar2),uVar5);
  }
  return;
}


// ===== ovl_16e9 @ 1ca8:16e9

void ovl_16e9(void)

{
  undefined2 uVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  int iVar3;
  
  EXE_InitScrap();
  EXE_ClrTxtWnd();
  EXE_SetTxtObj(OV_0x1c5);
  EXE_AddScrap(&OV_0x223,0x1000,8);
  iVar2 = EXE_ChkRng(G_lookdata+2 & 0xff,G_lookdata+2 >> 8,
                     1,0);
  if (iVar2 == 0) {
    EXE_AddScrap(&OV_0x223,0x1000,9);
    EXE_PrtScrap(0xff,in_BX);
    return;
  }
  EXE_AddScrap(&OV_0x223,0x1000,10);
  EXE_PrtScrap(0xff);
  iVar2 = EXE_SetYN();
  if (iVar2 != 0) {
    EXE_ClrTxtWnd(in_BX);
    return;
  }
  iVar2 = EXE_IncObj(*(undefined2 *)(G_curpla * 2 + &G_heroptr),
                     OV_0x1c5,1);
  if (iVar2 == 0) {
    return;
  }
  EXE_InitScrap();
  EXE_ClrTxtWnd();
  EXE_AddScrap(G_loc+10);
  EXE_HighStat(0x14);
  EXE_AddScrap(&OV_0x223,0x1000,0x11);
  EXE_PrtScrap(1);
  G_mapyl+28 = 0x26;
  G_scrollonfloor = 0;
  LOCK();
  uVar1 = OV_0x1c5;
  OV_0x1c5 = 0;
  UNLOCK();
  if ((char)uVar1 == 'L') {
    OV_0x1c9 = 0x4c;
    LOCK();
    iVar2 = G_loc+16;
    G_loc+16 = in_BX;
    UNLOCK();
    *(undefined1 *)(iVar2 + 2) = 1;
    *(undefined1 *)(iVar2 + 5) = 0x10;
    LOCK();
    iVar3 = G_loc+16;
    G_loc+16 = iVar2;
    UNLOCK();
    G_events = G_events | 0x80;
    G_disasterday = G_juldate;
    EXE_SetBit(&G_npcsta,0x38);
    EXE_SetBit(&G_npcsta,0x3c);
    EXE_SetBit(&G_npcsta,0x3d,iVar3);
  }
  return;
}


// ===== ovl_1855 @ 1ca8:1855

void ovl_1855(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_InitScrap();
  EXE_ClrTxtWnd();
  EXE_AddScrap(G_loc+10);
  EXE_PrtScrap(OV_0x1d0,in_BX);
  return;
}


// ===== ovl_187e @ 1ca8:187e

void ovl_187e(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_InvertWindow(0,3);
  return;
}


// ===== FUN_1000_e310 @ 1000:e310

void __cdecl16near FUN_1000_e310(uint param_1)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(&G_npclocs + (param_1 & 0xff) * 5);
  ovl_191b(*(undefined1 *)((uint)*(byte *)((int)puVar1 + 3) + &G_npctile),*puVar1);
  return;
}


// ===== FUN_1000_e334 @ 1000:e334

void __cdecl16near FUN_1000_e334(uint param_1)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_18cd(*(undefined2 *)(&G_npclocs + (param_1 & 0xff) * 5));
  return;
}


// ===== ovl_18cd @ 1ca8:18cd

void __cdecl16near ovl_18cd(uint param_1)

{
  uint uVar1;
  undefined2 uVar2;
  int iVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar3 = G_savebx;
  EXE_MFXInit();
  uVar1 = EXE_Locate(param_1 & 0xff,param_1 >> 8);
  G_mfxtnum = uVar1 & 0xff;
  uVar2 = ovl_1976();
  G_mfxcoords = uVar2;
  G_mfxcflag = 0;
  G_egadrawcode = 0;
  G_egaeffectstimer = 60000;
  G_egaeffectsflag = 3;
  EXE_MultiFX(iVar3);
  return;
}


// ===== ovl_191b @ 1ca8:191b

void __cdecl16near ovl_191b(undefined2 param_1)

{
  undefined2 uVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar2 = G_savebx;
  EXE_MFXInit();
  G_mfxtnum = param_1;
  uVar1 = ovl_1976();
  G_mfxcoords = uVar1;
  G_mfxcflag = 1;
  G_egadrawcode = 0;
  G_egaeffectstimer = 4000;
  G_egaeffectsflag = 7;
  EXE_MultiFX();
  EXE_MultiFX();
  EXE_MultiFX();
  EXE_MultiFX();
  G_egaeffectsflag = 3;
  EXE_MultiFX(iVar2);
  return;
}


// ===== ovl_1976 @ 1ca8:1976

undefined2 __cdecl16near ovl_1976(void)

{
  char in_AL;
  char in_AH;
  
  return CONCAT11(in_AH * '\x10' + '\b',in_AL * '\x04' + '\x04');
}


// ===== FUN_1000_e406 @ 1000:e406

void __cdecl16near FUN_1000_e406(undefined1 param_1,uint param_2)

{
  undefined2 *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_1a52();
  G_zp_1415 = param_2;
  ovl_1a8a();
  iVar4 = 0;
  iVar3 = 0;
  G_zp_1415 = 0;
  do {
    *(uint *)(iVar3 + &G_bangstg) =
         (uint)(byte)(*(char *)(iVar4 + &G_blobmap) + 0x14);
    *(uint *)(iVar3 + &G_bangx) = (uint)G_zp_1415;
    *(uint *)(iVar3 + &G_bangy) = (uint)G_zp_15;
    iVar3 = iVar3 + 2;
    G_zp_1415 = G_zp_1415 + '\x01';
    if (G_zp_1415 == '\v') {
      G_zp_1415 = 0;
      G_zp_15 = G_zp_15 + '\x01';
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 99);
  puVar1 = (undefined2 *)(G_savebx + 0x2c4);
  EXE_MultiBang(0,G_savebx);
  G_egaeffectsflag = 0x1001;
  G_egadrawcode = 0;
  G_egaeffectstimer = 1;
  uVar2 = ovl_1976();
  iVar3 = G_savebx;
  EXE_movectileFX(param_1,uVar2 & 0xff,uVar2 >> 8);
  EXE_GameSound(0x1d);
  EXE_WaitForSound();
  EXE_RestBG(param_2 & 0xff,param_2 >> 8);
  EXE_PageFlip(iVar3);
  return;
}


// ===== ovl_1a52 @ 1ca8:1a52

void __cdecl16near ovl_1a52(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar1 = 200;
  iVar2 = 0;
  do {
    *(undefined2 *)(iVar2 + &G_bangstg) = 5;
    iVar2 = iVar2 + 2;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  OV_0x1b50 = 0;
  return;
}


// ===== ovl_1a6e @ 1ca8:1a6e

void ovl_1a6e(void)

{
  char cVar1;
  undefined2 uVar2;
  char cVar3;
  undefined2 *puVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar4 = (undefined2 *)&G_cmbcrds+196;
  uVar2 = 0x80a;
  do {
    do {
      *puVar4 = uVar2;
      puVar4 = puVar4 + -1;
      cVar1 = (char)uVar2;
      cVar3 = (char)((uint)uVar2 >> 8);
      uVar2 = CONCAT11(cVar3,cVar1 + -1);
    } while ('\0' < cVar1);
    uVar2 = CONCAT11(cVar3 + -1,10);
  } while ('\0' < cVar3);
  return;
}


// ===== ovl_1a8a @ 1ca8:1a8a

void __cdecl16near ovl_1a8a(void)

{
  char *pcVar1;
  char cVar2;
  undefined2 uVar3;
  bool bVar4;
  uint uVar5;
  undefined1 *puVar6;
  int iVar7;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar3 = G_zp_1415;
  G_zp_1415 = 0x80a;
  puVar6 = (undefined1 *)&G_blobmap+98;
  do {
    *puVar6 = 0x7e;
    pcVar1 = (char *)&G_zp_1415;
    cVar2 = *pcVar1;
    *pcVar1 = *pcVar1 + -1;
    if (SBORROW1(cVar2,'\x01') != *pcVar1 < '\0') {
      G_zp_1415 = 10;
      pcVar1 = (char *)&G_zp_15;
      cVar2 = *pcVar1;
      *pcVar1 = *pcVar1 + -1;
      if (SBORROW1(cVar2,'\x01') != *pcVar1 < '\0') {
        G_zp_1415 = uVar3;
        ovl_1b64();
        puVar6[&G_blobmap] = 0;
        uVar5 = 0;
        while( true ) {
          OV_0x1b85 = 1;
          while( true ) {
            OV_0x1b87 = 0;
            iVar7 = 0x62;
            do {
              if (*(char *)(iVar7 + &G_blobmap) == (char)uVar5) {
                ovl_1b13();
              }
              bVar4 = 0 < iVar7;
              iVar7 = iVar7 + -1;
            } while (bVar4);
            if (OV_0x1b87 != '\x01') break;
            OV_0x1b85 = 0;
          }
          if (OV_0x1b85 == 1) break;
          uVar5 = (uint)(byte)((char)uVar5 + 1);
        }
        return;
      }
    }
    puVar6 = puVar6 + -1;
  } while( true );
}


// ===== ovl_1b13 @ 1ca8:1b13

void __cdecl16near ovl_1b13(void)

{
  undefined2 uVar1;
  bool bVar2;
  char in_CL;
  char cVar3;
  char cVar4;
  uint in_BX;
  uint uVar5;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  int local_4;
  
  local_4 = 0;
  cVar3 = in_CL + '\x01';
  cVar4 = '\a';
  do {
    uVar1 = *(undefined2 *)(in_BX * 2 + &G_cmbcrds);
    uVar5 = in_BX & 0x7fff;
    if (((byte)((char)uVar1 + *(char *)(local_4 + &OV_0x1c03)) < 0xb) &&
       ((byte)((char)((uint)uVar1 >> 8) + *(char *)(local_4 + &OV_0x1c0b)) < 9)) {
      ovl_1b64();
      if (cVar3 < *(char *)(uVar5 + &G_blobmap)) {
        OV_0x1b87 = 1;
        *(char *)(uVar5 + &G_blobmap) = cVar3;
      }
    }
    local_4 = local_4 + 1;
    bVar2 = '\0' < cVar4;
    cVar4 = cVar4 + -1;
  } while (bVar2);
  return;
}


// ===== ovl_1b64 @ 1ca8:1b64

void __cdecl16near ovl_1b64(void)

{
  return;
}


