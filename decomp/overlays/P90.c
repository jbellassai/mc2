// ===== ovl_0358 @ 1ca8:0358

void __cdecl16near ovl_0358(void)

{
  undefined2 unaff_DS;
  
  *(undefined2 *)(*piRam000004fc + -0x728a) = piRam000004fc;
  ovl_1181();
  return;
}


// ===== ovl_037c @ 1ca8:037c

void ovl_037c(void)

{
  byte *pbVar1;
  char cVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int in_BX;
  char *pcVar7;
  char *pcVar8;
  byte *pbVar9;
  int unaff_SI;
  int unaff_DI;
  undefined2 uVar10;
  undefined2 unaff_DS;
  byte bVar11;
  int iVar12;
  
  iVar12 = unaff_SI;
  ovl_0358();
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap(G_comtxtptr);
  EXE_PrtScrap(0xff);
  uVar3 = EXE_ItemSel(G_curpla,in_BX);
  if ((char)((uint)uVar3 >> 8) == '\0') {
    OV_0x130 = uVar3;
    uVar10 = *(undefined2 *)(G_curpla * 2 + &G_heroptr);
    OV_0x12e = uVar10;
    iVar5 = G_savebx;
    iVar4 = EXE_BookChk(uVar10,0,uVar3,1);
    if (iVar4 == 1) {
      ovl_1198();
      iVar4 = OV_0x12e + OV_0x130;
      OV_0x134 = *(undefined1 *)(iVar4 + 0x53);
      bVar11 = *(byte *)(iVar4 + 0x2b);
      OV_0x132 = bVar11;
      if (bVar11 == 0x49) {
        ovl_0621();
      }
      else {
        iVar4 = EXE_OK2Give(OV_0x12e,
                           OV_0x112,OV_0x130);
        if (iVar4 == 1) {
          if ((bVar11 < 9) || (0x30 < bVar11)) {
            if (OV_0x132 == '\0') {
              LOCK();
              iVar12 = OV_0x12e;
              OV_0x12e = iVar5;
              UNLOCK();
              uVar6 = *(uint *)(iVar12 + 0xcc);
              LOCK();
              iVar5 = OV_0x12e;
              OV_0x12e = iVar12;
              UNLOCK();
            }
            else {
              uVar6 = (uint)OV_0x134;
            }
            OV_0x135 = uVar6;
            ovl_1097();
            EXE_AddScrap(G_comtxtptr);
            EXE_PrtScrap(0xff);
            iVar12 = iVar5;
            iVar5 = EXE_GetNum(0,OV_0x135);
            if (iVar5 == 0) {
              EXE_ClrTxtWnd(iVar12);
              return;
            }
            OV_0x135 = iVar5;
            iVar5 = 0x1000;
            EXE_ClrTxtWnd(iVar12);
          }
          else {
            OV_0x135 = (uint)OV_0x134;
          }
          if (G_npcno < 0x20) {
            iVar4 = G_npcno - 1;
            if ((OV_0x132 == 0) &&
               (pcVar7 = (char *)(&G_assgn0 + iVar4 * 0x19), *pcVar7 != -1)) {
              iVar5 = *(int *)(pcVar7 + 0x11) + OV_0x135;
              if (9999 < iVar5) {
                iVar5 = 9999;
              }
              *(int *)(pcVar7 + 0x11) = iVar5;
              iVar5 = G_savebx;
            }
            else {
              iVar5 = G_savebx;
              iVar4 = EXE_IncObj(&G_member6 + iVar4 * 0xdc,
                                 OV_0x132,OV_0x135
                                );
              if (iVar4 != 1) {
                return;
              }
            }
          }
          EXE_DecObj(OV_0x12e,OV_0x130,
                     OV_0x135,iVar5);
          if (G_npcno < 0xfa) {
            uVar3 = (undefined2)((ulong)OV_0x109 >> 0x10);
            pcVar7 = (char *)(*(int *)((int)OV_0x109 + 0x24) + -5);
            do {
              pcVar8 = pcVar7;
              cVar2 = pcVar8[5];
              if (cVar2 == -1) goto L_05bc;
              pcVar7 = pcVar8 + 5;
            } while (cVar2 != OV_0x132);
            pbVar9 = (byte *)(pcVar8 + 7);
            if (((char)((uint)OV_0x135 >> 8) != '\0') ||
               ((byte)pcVar8[6] <= (byte)OV_0x135)) {
              pbVar9 = (byte *)(pcVar8 + 8);
              pbVar1 = (byte *)((uint)((byte)pcVar8[9] >> 3) + &G_events);
              *pbVar1 = *pbVar1 | '\x01' << (pcVar8[9] & 7U);
            }
            uVar6 = (uint)*pbVar9;
            uVar3 = *(undefined2 *)G_convbufptr;
            uVar10 = (int)((ulong)G_convbufptr >> 0x10);
          }
          else {
L_05bc:
            uVar6 = 0xd4;
            uVar3 = G_comtxtptr;
            uVar10 = unaff_DS;
          }
          iVar5 = G_savebx;
          ovl_10ad(uVar3,uVar6,uVar10);
          EXE_AddScrap(uVar6,iVar12,uVar10);
          EXE_PrtScrap(2,iVar5);
        }
      }
    }
  }
  return;
}


// ===== ovl_0621 @ 1ca8:0621

void ovl_0621(void)

{
  byte bVar1;
  undefined2 *puVar2;
  char cVar3;
  int iVar4;
  int in_BX;
  uint uVar5;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  int iVar6;
  
  OV_0x211 = &OV_0x213;
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap(OV_0x211,0x1000,0);
  cVar3 = (char)G_npcno;
  if (cVar3 == -0x5a) {
    EXE_AddScrap(OV_0x211,0x1000,0x12);
    EXE_PrtScrap(1);
    G_events+15 = G_events+15 | 8;
    EXE_DecObj0(0x49,1,in_BX);
    return;
  }
  uVar5 = 0;
  do {
    if (cVar3 == *(char *)(uVar5 + &OV_0x20b)) {
      bVar1 = *(byte *)(uVar5 + &OV_0x20e);
      if ((G_events+4 & bVar1) == 0) {
        G_events+4 = G_events+4 | bVar1;
        if ((G_events+4 & 0x1c) == 0x1c) {
          puVar2 = (undefined2 *)(G_savebx + 0xe8);
          EXE_PrtScrap(0x1000,OV_0x211,0x1000,0xf,uVar5);
          puVar2 = (undefined2 *)(G_savebx + 0xe8);
          EXE_PrtScrap(0x1000,OV_0x211,0x1000,0x10,uVar5);
        }
        else {
          puVar2 = (undefined2 *)(G_savebx + 0xe8);
          EXE_PrtScrap(0x1000,OV_0x211,0x1000,5,uVar5);
          puVar2 = (undefined2 *)(G_savebx + 0xe8);
          EXE_PrtScrap(0x1000,OV_0x211,0x1000,uVar5 + 6,uVar5);
          puVar2 = (undefined2 *)(G_savebx + 0xe8);
          EXE_PrtScrap(0x1000,OV_0x211,0x1000,9,uVar5);
          puVar2 = (undefined2 *)(G_savebx + 0xe8);
          EXE_PrtScrap(0x1000,OV_0x211,0x1000,10,uVar5);
          puVar2 = (undefined2 *)(G_savebx + 0xe8);
          EXE_PrtScrap(0x1000,OV_0x211,0x1000,uVar5 + 0xb,uVar5);
          puVar2 = (undefined2 *)(G_savebx + 0xe8);
          EXE_PrtScrap(0x1000,OV_0x211,0x1000,0xe,uVar5);
        }
        puVar2 = (undefined2 *)(G_savebx + 0xec);
        EXE_PrtScrap(0x1000,1,G_savebx);
        return;
      }
      break;
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 < 3);
  iVar6 = G_savebx;
  EXE_AddScrap(OV_0x211,0x1000,1);
  iVar4 = EXE_RndCo(3);
  EXE_AddScrap(OV_0x211,0x1000,iVar4 + 2);
  EXE_PrtScrap(0xff,iVar6);
  return;
}


// ===== ovl_0792 @ 1ca8:0792

void ovl_0792(void)

{
  undefined2 *puVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar5;
  int iStack0004;
  
  ovl_0358();
  OV_0x137 = 0;
  OV_0x110 =
       *(undefined2 *)(G_curpla * 2 + &G_heroptr);
  iStack0004 = G_savebx;
  ovl_10ad();
  EXE_AddScrap(G_comtxtptr);
  EXE_PrtScrap(0xff);
  ovl_0c97();
  iVar4 = EXE_ListSel(OV_0x209,&OV_0xe80,0x1000);
  bVar5 = iVar4 != -1;
  if (iVar4 == -1) {
    return;
  }
  ovl_0eb1();
  if (!bVar5) {
    return;
  }
  ovl_0f5e();
  ovl_10ad();
  EXE_AddScrap(G_comtxtptr);
  G_deftxtparms = OV_0x122;
  EXE_AddScrap(G_comtxtptr);
  EXE_AddScrap(G_comtxtptr);
  cVar3 = (char)OV_0x11a;
  if (cVar3 != '\x01') {
    G_deftxtparms+2 = cVar3;
    EXE_AddScrap(G_comtxtptr);
  }
  EXE_AddScrap(G_comtxtptr);
  OV_0x114 = 0xb4;
  OV_0x116 = 99;
  cVar3 = ovl_0dd2();
  if (cVar3 == '\0') {
L_0904:
    ovl_10ad();
    EXE_AddScrap();
    EXE_PrtScrap();
  }
  else {
    bVar2 = OV_0x11c;
    OV_0x124 = OV_0x122 * (uint)bVar2;
    bVar5 = bVar2 == 0;
    if ((bVar2 == 1) || (ovl_0f41(), bVar5)) {
      ovl_10ad();
      G_deftxtparms = OV_0x124;
      EXE_AddScrap();
      EXE_AddScrap();
      EXE_PrtScrap();
      puVar1 = (undefined2 *)(iStack0004 + 0x108);
      iStack0004 = 0x1000;
      iVar4 = EXE_SetYN();
      if (iVar4 != 0) goto L_0904;
      if (OV_0x124 <=
          *(int *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0xcc)) {
        iVar4 = EXE_slot0x1164(0x1000,OV_0x110);
        if (iVar4 == 0) {
          return;
        }
        EXE_slot0x1168(0x1000,OV_0x110);
        if (G_npcno == 'X') {
          G_events+3 = G_events+3 | 0x40;
        }
        ovl_10ad();
        EXE_AddScrap();
        EXE_PrtScrap();
        return;
      }
      ovl_1097();
      EXE_AddScrap();
    }
    else {
      ovl_10ad();
      EXE_AddScrap();
    }
    EXE_PrtScrap();
    EXE_GameSound();
  }
  return;
}


// ===== ovl_09b8 @ 1ca8:09b8

void ovl_09b8(void)

{
  undefined2 *puVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  byte extraout_DL;
  uint uVar6;
  byte *pbVar7;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar8;
  int iStack0004;
  
  ovl_0358();
  OV_0x137 = 1;
  ovl_10ad();
  OV_0x110 =
       *(undefined2 *)(G_curpla * 2 + &G_heroptr);
  iVar4 = G_savebx;
  if (*(char *)((int)G_convbufptr + G_convix + 0x5c) ==
      '\0') {
    ovl_0c97();
    if (OV_0x209 == 0) {
      EXE_InitScrap();
      EXE_AddScrap(G_comtxtptr);
      EXE_PrtScrap(0xff,iVar4);
      return;
    }
    EXE_AddScrap(G_comtxtptr);
    EXE_PrtScrap(0xff);
    iStack0004 = iVar4;
    iVar4 = EXE_ListSel(OV_0x209,&OV_0xe80,0x1000);
    bVar8 = iVar4 != -1;
    if (iVar4 == -1) {
      return;
    }
    ovl_0eb1();
    if (!bVar8) {
      return;
    }
    if (((0x52 < extraout_DL) && (extraout_DL < 0x5a)) &&
       ((char)*(undefined2 *)(*(int *)(G_curpla * 2 + &G_heroptr) + 6) ==
        '\x01')) {
      pbVar7 = (byte *)(OV_0x110 + 0x2b);
      iVar4 = 0x28;
      uVar6 = 0;
      do {
        if ((0x52 < *pbVar7) && (*pbVar7 < 0x5a)) {
          uVar6 = uVar6 + 1;
        }
        pbVar7 = pbVar7 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      if (uVar6 < 2) {
        ovl_1097();
        iVar4 = G_comtxtptr;
        EXE_AddScrap();
        goto L_107e;
      }
    }
    ovl_0f5e();
    EXE_SearchInv(OV_0x118,G_curpla,
               &OV_0x126,0x1000);
    ovl_10ad();
    EXE_AddScrap(G_comtxtptr);
    G_deftxtparms = OV_0x120;
    EXE_AddScrap(G_comtxtptr);
    EXE_AddScrap(G_comtxtptr);
    cVar2 = (char)OV_0x11a;
    if (cVar2 != '\x01') {
      G_deftxtparms+2 = cVar2;
      EXE_AddScrap(G_comtxtptr);
    }
    iVar4 = 0x1000;
    EXE_AddScrap(G_comtxtptr);
    OV_0x114 = 0xb5;
    cVar2 = (char)((uint)(int)OV_0x126 / (uint)OV_0x11a);
    if (cVar2 == '\0') {
      EXE_PrtScrap();
      G_deftxtparms+2 = (char)OV_0x11a;
      ovl_10ad();
      EXE_AddScrap&OV_0x213;
      EXE_PrtScrap();
      return;
    }
    OV_0x116 = cVar2;
    iVar5 = ovl_0dd2();
    if (iVar5 != 0) {
      bVar3 = OV_0x11c;
      if (bVar3 != 0) {
        OV_0x124 = OV_0x120 * (uint)bVar3;
        bVar8 = bVar3 == 0;
        if ((bVar3 != 1) && (ovl_0f41(), !bVar8)) {
          ovl_10ad();
          EXE_AddScrap();
          goto L_107e;
        }
        ovl_10ad();
        G_deftxtparms = OV_0x124;
        EXE_AddScrap();
        EXE_AddScrap();
        EXE_PrtScrap();
        puVar1 = (undefined2 *)(iStack0004 + 0x108);
        iStack0004 = 0x1000;
        iVar4 = EXE_SetYN();
        if (iVar4 == 0) {
          bVar3 = (byte)OV_0x11a;
          if (OV_0x126 < bVar3) {
            G_deftxtparms+2 = bVar3;
            ovl_10ad();
            EXE_AddScrap();
            EXE_PrtScrap();
            return;
          }
          iVar4 = EXE_slot0x1164(0x1000,OV_0x110);
          if (iVar4 == 0) {
            return;
          }
          EXE_slot0x1168(0x1000,OV_0x110);
          ovl_10ad();
          EXE_AddScrap();
          EXE_PrtScrap();
          return;
        }
      }
    }
    ovl_10ad();
    EXE_AddScrap();
    EXE_PrtScrap();
  }
  else {
    EXE_AddScrap(G_comtxtptr);
L_107e:
    EXE_PrtScrap(0xff);
    EXE_GameSound(0xe,iVar4);
  }
  return;
}


// ===== ovl_0c97 @ 1ca8:0c97

void ovl_0c97(void)

{
  char cVar1;
  byte bVar2;
  undefined2 uVar3;
  int iVar4;
  undefined1 *puVar5;
  byte *pbVar6;
  char *pcVar7;
  int iVar8;
  int unaff_SI;
  int unaff_DI;
  undefined2 uVar9;
  undefined2 unaff_DS;
  
  uVar9 = (undefined2)((ulong)OV_0x109 >> 0x10);
  iVar8 = G_savebx;
  OV_0x207 = *(undefined2 *)((int)OV_0x109 + 0x34)
  ;
  OV_0x209 = 0;
  pbVar6 = (byte *)&G_scrap2+12;
  puVar5 = (undefined1 *)&G_blasty+5;
  do {
    LOCK();
    pcVar7 = (char *)OV_0x207;
    OV_0x207 = iVar8;
    UNLOCK();
    cVar1 = *pcVar7;
    LOCK();
    iVar8 = OV_0x207;
    OV_0x207 = (int)(pcVar7 + 5);
    UNLOCK();
    if (cVar1 == -1) {
      return;
    }
    uVar3 = CONCAT11(1,cVar1);
    for (pcVar7 = (char *)&OV_0x1f2; *pcVar7 != -1; pcVar7 = pcVar7 + 2) {
      if (cVar1 == *pcVar7) {
        uVar3 = CONCAT11(pcVar7[1],cVar1);
        break;
      }
    }
    bVar2 = (byte)uVar3;
    *pbVar6 = bVar2;
    if (8 < bVar2) {
      if (bVar2 < 0x31) {
        uVar3 = 0x100;
      }
      else if ((0x52 < bVar2) && (bVar2 < 0x5a)) {
        uVar3 = 0x100;
      }
    }
    *puVar5 = (char)((uint)uVar3 >> 8);
    if ((OV_0x137 != '\x01') || (iVar4 = ovl_0d2b(), iVar4 != 0)) {
      OV_0x209 = OV_0x209 + 1;
      pbVar6 = pbVar6 + 1;
      puVar5 = puVar5 + 1;
    }
  } while( true );
}


// ===== ovl_0d2b @ 1ca8:0d2b

undefined2 ovl_0d2b(void)

{
  int iVar1;
  char *pcVar2;
  char cVar3;
  char cVar4;
  undefined1 in_AL;
  int iVar5;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  char *pcVar6;
  undefined2 unaff_DS;
  bool bVar7;
  
  iVar5 = EXE_SearchInv(in_AL,G_curpla,&OV_0x126,0x1ca8);
  if (iVar5 == 0) {
    return 0;
  }
  cVar3 = OV_0x128;
  LOCK();
  iVar5 = OV_0x110;
  OV_0x110 = in_BX;
  UNLOCK();
  cVar4 = *(char *)(iVar5 + 0xbf);
  LOCK();
  iVar1 = OV_0x110;
  OV_0x110 = iVar5;
  UNLOCK();
  if (cVar3 == cVar4) {
    return 0;
  }
  LOCK();
  iVar5 = OV_0x110;
  OV_0x110 = iVar1;
  UNLOCK();
  pcVar6 = (char *)(iVar5 + 0xc0);
  LOCK();
  OV_0x110 = iVar5;
  UNLOCK();
  iVar5 = 6;
  bVar7 = false;
  do {
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar2 = pcVar6;
    pcVar6 = pcVar6 + 1;
    bVar7 = cVar3 == *pcVar2;
  } while (!bVar7);
  if (bVar7) {
    return 0;
  }
  return 1;
}


// ===== ovl_0d80 @ 1ca8:0d80

void __cdecl16far ovl_0d80(int param_1)

{
  undefined2 uVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_0358();
  uVar1 = G_scroll;
  G_scroll = 0;
  LOCK();
  UNLOCK();
  LOCK();
  UNLOCK();
  EXE_SetTxtObj(*(undefined1 *)(param_1 + &G_scrap2+12));
  EXE_PrtWrdX(&OV_0x10d,0x1ca8,0);
  EXE_Pad(in_BX);
  G_scroll = uVar1;
  return;
}


// ===== ovl_0dd2 @ 1ca8:0dd2

undefined2 ovl_0dd2(void)

{
  byte bVar1;
  int iVar2;
  undefined2 uVar3;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  bVar1 = (byte)OV_0x118;
  if ((8 < bVar1) && ((bVar1 < 0x31 || ((0x52 < bVar1 && (bVar1 < 0x5a)))))) {
    OV_0x11c = 1;
    EXE_AddScrap(G_comtxtptr);
    EXE_AddScrap(G_comtxtptr);
    EXE_AddScrap(G_comtxtptr);
    EXE_PrtScrap(0xff);
    iVar2 = EXE_SetYN(in_BX);
    if (iVar2 == 0) {
      return 1;
    }
    return 0;
  }
  EXE_AddScrap(G_comtxtptr);
  EXE_AddScrap(G_comtxtptr);
  EXE_AddScrap(G_comtxtptr);
  EXE_PrtScrap(0xff);
  if ((uint)((G_txtwx + G_txtww) -
            G_cursorx) < 4) {
    EXE_MyRet();
  }
  uVar3 = EXE_GetNum(0,OV_0x116,in_BX);
  OV_0x11c = (char)uVar3;
  return uVar3;
}


// ===== ovl_0eb1 @ 1ca8:0eb1

void ovl_0eb1(void)

{
  char cVar1;
  int in_AX;
  char *pcVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  OV_0x11a = *(undefined1 *)(in_AX + &G_blasty+5);
  cVar1 = *(char *)(in_AX + &G_scrap2+12);
  OV_0x118 = cVar1;
  uVar3 = (undefined2)((ulong)OV_0x109 >> 0x10);
  pcVar2 = (char *)*(undefined2 *)((int)OV_0x109 + 0x34);
  do {
    if (cVar1 == *pcVar2) {
      uVar3 = ovl_0f32();
      OV_0x120 = uVar3;
      uVar3 = ovl_0f32();
      OV_0x122 = uVar3;
      cVar1 = (char)*(undefined2 *)
                     (*(int *)(G_curpla * 2 + &G_heroptr) + 0x1d) -
              *(char *)((int)G_convbufptr + G_convix +
                       0x54);
      if (cVar1 < '\0') {
        OV_0x11e = 1;
        cVar1 = -cVar1;
      }
      else {
        OV_0x11e = 0;
      }
      OV_0x11d = cVar1;
      return;
    }
    pcVar2 = pcVar2 + 5;
  } while (*pcVar2 != -1);
  return;
}


// ===== ovl_0f32 @ 1ca8:0f32

undefined2 ovl_0f32(void)

{
  byte bVar1;
  byte *in_BX;
  undefined2 unaff_ES;
  
  bVar1 = (byte)((uint)*in_BX * 100);
  return CONCAT11((char)((uint)*in_BX * 100 >> 8) + CARRY1(bVar1,in_BX[1]),bVar1 + in_BX[1]);
}


// ===== ovl_0f41 @ 1ca8:0f41

void ovl_0f41(void)

{
  uint uVar1;
  byte in_CL;
  int unaff_DI;
  
  uVar1 = (OV_0x11a & 0xff) * (uint)in_CL;
  if (uVar1 < 100) {
    OV_0x11a = uVar1;
    return;
  }
  return;
}


// ===== ovl_0f5e @ 1ca8:0f5e

void ovl_0f5e(void)

{
  int *piVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  int unaff_DI;
  
  uVar3 = OV_0x122;
  OV_0x1056 = uVar3;
  OV_0x1058 = uVar3 >> 1;
  iVar4 = OV_0x120;
  OV_0x105c = iVar4;
  OV_0x105a = iVar4 << 1;
  iVar4 = OV_0x118 * 2;
  bVar2 = *(byte *)(iVar4 + &OV_0x139);
  if ((bVar2 != 0) && (OV_0x11d != 0)) {
    iVar4 = (uint)(OV_0x11d / bVar2) * (uint)*(byte *)(iVar4 + &OV_0x138);
    if (OV_0x11e == 0) {
      OV_0x120 = OV_0x120 + iVar4;
      piVar1 = (int *)&OV_0x122;
      *piVar1 = *piVar1 - iVar4;
      if (*piVar1 < 0) {
        OV_0x122 = 1;
      }
    }
    else {
      OV_0x122 = OV_0x122 + iVar4;
      piVar1 = (int *)&OV_0x120;
      *piVar1 = *piVar1 - iVar4;
      if (*piVar1 < 0) {
        OV_0x120 = 1;
      }
    }
  }
  if (OV_0x105a < OV_0x122) {
    OV_0x122 = OV_0x105a;
  }
  if (OV_0x122 < OV_0x105c) {
    OV_0x122 = OV_0x105c;
  }
  if (OV_0x1056 < OV_0x120) {
    OV_0x120 = OV_0x1056;
  }
  if (OV_0x120 < OV_0x1058) {
    OV_0x120 = OV_0x1058;
  }
  if (OV_0x122 < OV_0x120) {
    OV_0x120 = OV_0x122;
  }
  return;
}


// ===== ovl_1097 @ 1ca8:1097

void ovl_1097(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap(in_BX);
  return;
}


// ===== ovl_10ad @ 1ca8:10ad

void ovl_10ad(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined4 uVar1;
  
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  if (G_npcno < 0x20) {
    uVar1 = EXE_AddScrap(&G_member6 + (G_npcno - 1) * 0xdc);
    G_othername = (int)uVar1;
    G_othername+2 = (int)((ulong)uVar1 >> 0x10);
  }
  else {
    ovl_1106();
  }
  EXE_AddScrap(G_comtxtptr);
  return;
}


// ===== ovl_1106 @ 1ca8:1106

void ovl_1106(void)

{
  undefined2 *puVar1;
  int extraout_DX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined4 uVar2;
  
  ovl_115f();
  if (extraout_DX == 0) {
    EXE_AddScrap(G_comtxtptr);
    puVar1 = (undefined2 *)(G_savebx + 0xe8);
    uVar2 = EXE_AddScrap(G_comtypptr);
  }
  else {
    uVar2 = EXE_AddScrap(G_loc+18);
  }
  G_othername = (int)uVar2;
  G_othername+2 = (int)((ulong)uVar2 >> 0x10);
  return;
}


// ===== ovl_115f @ 1ca8:115f

void ovl_115f(void)

{
  char in_AL;
  char *pcVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  pcVar1 = (char *)G_loc+4;
  while( true ) {
    if (*pcVar1 == '\0') {
      return;
    }
    if (pcVar1[4] == in_AL) break;
    pcVar1 = pcVar1 + 10;
  }
  return;
}


// ===== ovl_1181 @ 1ca8:1181

void __cdecl16near ovl_1181(void)

{
  undefined4 uVar1;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar1 = G_convbufptr;
  OV_0x109 = (int)uVar1 + G_convix * 2;
  OV_0x10b = (int)((ulong)uVar1 >> 0x10);
  return;
}


// ===== ovl_1198 @ 1ca8:1198

void ovl_1198(void)

{
  int iVar1;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar1 = 0;
  if (G_npcno < 0x20) {
    iVar1 = (G_npcno - 1 & 0xff) * 0xdc + &G_member6;
  }
  OV_0x112 = iVar1;
  return;
}


