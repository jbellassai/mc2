// ===== ovl_00c8 @ 3100:00c8

undefined2 ovl_00c8(void)

{
  undefined2 in_AX;
  char cVar1;
  
  cVar1 = (char)((uint)in_AX >> 8);
  if (cVar1 == '\r') {
    in_AX = INT60_0d();
  }
  else if (cVar1 == '\f') {
    in_AX = INT60_0c();
  }
  else if (cVar1 == '\v') {
    in_AX = INT60_0b();
  }
  else if (cVar1 == '\0') {
    in_AX = INT60_00();
  }
  else if (cVar1 == '\x01') {
    in_AX = INT60_01();
  }
  else if (cVar1 == '\x02') {
    in_AX = INT60_02();
  }
  else if (cVar1 == '\x06') {
    in_AX = INT60_06();
  }
  else if (cVar1 == '\a') {
    in_AX = INT60_07();
  }
  else if (cVar1 == '\b') {
    in_AX = INT60_08();
  }
  else if (cVar1 == '\t') {
    in_AX = INT60_09();
  }
  else if (cVar1 == '\n') {
    in_AX = INT60_0a();
  }
  else if (cVar1 == '\x03') {
    in_AX = INT60_03();
  }
  else if (cVar1 == '\x12') {
    in_AX = INT60_12();
  }
  else if (cVar1 == '\x0e') {
    in_AX = INT60_0e();
  }
  else if (cVar1 == '\x0f') {
    in_AX = INT60_0f();
  }
  else if (cVar1 == '\x10') {
    in_AX = INT60_10();
  }
  else if (cVar1 == '\x11') {
    in_AX = INT60_11();
  }
  else if (cVar1 == '\x13') {
    in_AX = INT60_13();
  }
  else if (cVar1 == '\x15') {
    in_AX = INT60_15();
  }
  else if (cVar1 == '\x14') {
    in_AX = INT60_14();
  }
  else if (cVar1 == '\x16') {
    in_AX = INT60_16();
  }
  return in_AX;
}


// ===== INT60_00 @ 3100:01c3

uint INT60_00(void)

{
  byte bVar1;
  undefined2 *puVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  char cVar6;
  int *piVar7;
  byte *pbVar8;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar5 = CONCAT11(*(undefined1 *)(G_curpla + &G_p1y),
                   *(undefined1 *)(G_curpla + &G_p1x)) -
          G_winxy;
  puVar2 = (undefined2 *)(G_savebx + 0x1f0);
  iVar4 = EXE_Target(uVar5 & 0xff,uVar5 >> 8,0xd);
  if (iVar4 == -1) {
    uVar5 = 0xffff;
  }
  else {
    cVar6 = (char)G_worky;
    cVar3 = (char)G_workx;
    iVar4 = CONCAT11(cVar6,cVar3);
    for (piVar7 = (int *)G_loc; (char)*piVar7 != '\0';
        piVar7 = (int *)((int)piVar7 + 5)) {
      if (*piVar7 == iVar4) {
        puVar2 = (undefined2 *)(G_savebx + 0x36c);
        EXE_Spef6(CONCAT11(cVar6 - G_winy,
                                           cVar3 - G_winxy),piVar7,iVar4);
        bVar1 = *(byte *)((int)piVar7 + 3);
        if ((*(byte *)(piVar7 + 2) < 6) || (9 < *(byte *)(piVar7 + 2))) {
          iVar4 = 0;
          while (*(byte *)(iVar4 + &OV_0x18c) <= bVar1) {
            iVar4 = iVar4 + 1;
          }
          return (uint)*(byte *)(iVar4 + &OV_0x19c);
        }
        for (pbVar8 = (byte *)G_loc+26; *pbVar8 != bVar1;
            pbVar8 = pbVar8 + 0xd) {
        }
        puVar2 = (undefined2 *)(G_savebx + 0x11c);
        iVar4 = EXE_FindBit(&G_dunrms,bVar1);
        if (iVar4 == 0) {
          if (*(int *)(pbVar8 + 2) == 0) {
            return 0xe1;
          }
          if (pbVar8[2] < 0x80) {
            return 0xe2;
          }
          return 0xe3;
        }
        if (*(int *)(pbVar8 + 2) == 0) {
          return 0xe4;
        }
        if (pbVar8[2] < 0x80) {
          return 0xe5;
        }
        return 0xe6;
      }
    }
    uVar5 = 0xe0;
  }
  return uVar5;
}


// ===== INT60_01 @ 3100:02b5

void INT60_01(void)

{
  undefined2 *puVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined2 uVar5;
  
  puVar1 = (undefined2 *)(G_savebx + 0x26c);
  iVar3 = EXE_InDungeon();
  if (iVar3 == 0) {
    uVar5 = 0xff;
    puVar1 = (undefined2 *)(G_savebx + 0x54);
    EXE_SetTxtWnd(1,in_BX,0x95,0xff);
    puVar1 = (undefined2 *)(G_savebx + 0x5c);
    EXE_ClrTxtWnd(in_BX);
    puVar1 = (undefined2 *)(G_savebx + 0xe4);
    EXE_InitScrap(in_BX);
    puVar1 = (undefined2 *)(G_savebx + 0xe8);
    EXE_AddScrap(G_comtxtptr);
    puVar1 = (undefined2 *)(G_savebx + 0xec);
    EXE_PrtScrap(uVar5,in_BX);
  }
  else {
    puVar1 = (undefined2 *)(G_savebx + 0xd0);
    EXE_GameSound(10,in_BX);
    puVar1 = (undefined2 *)(G_savebx + 0x2b4);
    uVar4 = EXE_GetMagSkl(in_BX);
    cVar2 = (char)((uVar4 & 0xff) / 0x14) + '\x02';
    G_wlkwcount = cVar2;
    G_deftxtparms+2 = cVar2;
    ovl_08dc();
    puVar1 = (undefined2 *)(G_savebx + 0x54);
    EXE_SetTxtWnd(1,in_BX,0xc9);
    puVar1 = (undefined2 *)(G_savebx + 0x5c);
    EXE_ClrTxtWnd(in_BX);
    puVar1 = (undefined2 *)(G_savebx + 0xe4);
    EXE_InitScrap(in_BX);
    puVar1 = (undefined2 *)(G_savebx + 0xe8);
    EXE_AddScrap(G_comtxtptr);
    puVar1 = (undefined2 *)(G_savebx + 0xec);
    EXE_PrtScrap(0xff);
  }
  return;
}


// ===== INT60_02 @ 3100:03f0

void INT60_02(void)

{
  char *pcVar1;
  undefined2 *puVar2;
  char cVar3;
  uint in_DX;
  char *pcVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar2 = (undefined2 *)(G_savebx + 0xf4);
  cVar3 = EXE_Locate(in_DX & 0xff,in_DX >> 8);
  pcVar4 = (char *)G_tdata+8;
  do {
    if (cVar3 == *pcVar4) {
      return;
    }
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (*pcVar1 != -1);
  return;
}


// ===== INT60_08 @ 3100:041d

undefined2 INT60_08(void)

{
  undefined2 *puVar1;
  char cVar2;
  undefined2 uVar3;
  uint uVar4;
  int in_DX;
  char *pcVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xf4);
  cVar2 = EXE_Locate(G_zp_1415 & 0xff,
                             G_zp_1415 >> 8);
  pcVar5 = (char *)G_tdata+6;
  do {
    if (*pcVar5 == -1) {
      uVar3 = 5;
L_0463:
      uVar4 = G_zp_1415 - G_winxy;
      *(uint *)(in_DX * 2 + &G_bangx) = uVar4 & 0xff;
      *(uint *)(in_DX * 2 + &G_bangy) = uVar4 >> 8;
      return uVar3;
    }
    if (*pcVar5 == cVar2) {
      if (pcVar5[2] == 'C') {
        uVar3 = 1;
        goto L_0463;
      }
      if (pcVar5[2] == 'B') {
        uVar3 = 2;
        goto L_0463;
      }
    }
    pcVar5 = pcVar5 + 7;
  } while( true );
}


// ===== INT60_09 @ 3100:047e

void INT60_09(void)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  undefined2 uVar4;
  undefined2 in_BX;
  uint uVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar5 = 0;
  iVar3 = 6;
  do {
    puVar1 = (undefined2 *)(G_savebx + 0x134);
    iVar2 = EXE_RndCo(10);
    iVar2 = iVar2 + 10;
    uVar4 = 0xba;
    if (*(int *)(uVar5 + &G_bangstg) == 1) {
L_04ae:
      puVar1 = (undefined2 *)(G_savebx + 0xd8);
      EXE_DecSta(uVar5 >> 1,uVar4,iVar2);
      iVar2 = *(int *)(uVar5 + &G_heroptr);
      if (*(char *)(iVar2 + 0xca) == '\0') {
        *(char *)(iVar2 + 0xca) = *(char *)(iVar2 + 0xca) + '\x01';
      }
      puVar1 = (undefined2 *)(G_savebx + 0xd4);
      EXE_IsHeTr(iVar2);
    }
    else {
      iVar2 = 1;
      uVar4 = 0xca;
      if (*(int *)(uVar5 + &G_bangstg) == 2) goto L_04ae;
    }
    uVar5 = uVar5 + 2;
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      puVar1 = (undefined2 *)(G_savebx + 0x2c4);
      EXE_MultiBang(0x17,in_BX);
      puVar1 = (undefined2 *)(G_savebx + 0x88);
      EXE_SumStat(in_BX);
      return;
    }
  } while( true );
}


// ===== ovl_0502 @ 3100:0502

undefined2 __cdecl16near ovl_0502(void)

{
  char in_AL;
  char in_AH;
  
  return CONCAT11(in_AH * '\x10' + '\b',in_AL * '\x04' + '\x04');
}


// ===== INT60_0a @ 3100:0522

void INT60_0a(void)

{
  undefined2 *puVar1;
  int iVar2;
  int unaff_SI;
  undefined2 *puVar3;
  undefined2 unaff_DS;
  
  puVar3 = (undefined2 *)&G_bangstg;
  for (iVar2 = 200; iVar2 != 0; iVar2 = iVar2 + -1) {
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar1 = 5;
  }
  return;
}


// ===== ovl_0533 @ 3100:0533

void ovl_0533(void)

{
  undefined2 *puVar1;
  int iVar2;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar2 = 3;
  do {
    puVar1 = (undefined2 *)(G_savebx + 0xd0);
    EXE_GameSound(0xf,in_BX);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


// ===== INT60_03 @ 3100:054a

void INT60_03(void)

{
  undefined2 *puVar1;
  uint uVar2;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_0533();
  puVar1 = (undefined2 *)(G_savebx + 0x2b4);
  uVar2 = EXE_GetMagSkl();
  uVar2 = (uVar2 & 0xff) >> 4;
  G_detectsw = G_detectsw + uVar2;
  if (G_detectsw <= uVar2) {
    ovl_08cf();
  }
  G_deftxtparms = G_detectsw * 4 + G_detectsw;
  puVar1 = (undefined2 *)(G_savebx + 0x54);
  EXE_SetTxtWnd(1,in_BX,0xf6);
  puVar1 = (undefined2 *)(G_savebx + 0x5c);
  EXE_ClrTxtWnd(in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0xe4);
  EXE_InitScrap(in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap(G_comtxtptr);
  puVar1 = (undefined2 *)(G_savebx + 0xec);
  EXE_PrtScrap(0xff);
  return;
}


// ===== ovl_05f8 @ 3100:05f8

undefined4 ovl_05f8(void)

{
  uint in_AX;
  undefined2 uVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if ((in_AX & 0xff) - (uint)*(byte *)(G_curseg + G_mapxptr) <
      (uint)G_thismap) {
    if ((in_AX >> 8) - (uint)*(byte *)(G_curseg + G_mapyptr) <
        (uint)G_mapyl) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return CONCAT22(uVar1,in_AX);
}


// ===== INT60_0d @ 3100:0634

int __cdecl16near INT60_0d(void)

{
  undefined2 *puVar1;
  int iVar2;
  uint uVar3;
  undefined2 *puVar4;
  int unaff_SI;
  undefined2 unaff_DI;
  undefined2 unaff_DS;
  bool bVar5;
  int local_4;
  
  local_4 = 0;
  G_worky = 0;
  for (puVar4 = (undefined2 *)G_loc+28; (char)*puVar4 != '\0';
      puVar4 = puVar4 + 3) {
    bVar5 = *(char *)(puVar4 + 1) == '\0';
    if (*(char *)(puVar4 + 1) == '\x01') {
      iVar2 = ovl_06af();
      if (!bVar5) {
        uVar3 = iVar2 - G_winxy;
        puVar1 = (undefined2 *)(G_savebx + 0x120);
        EXE_RestBG(uVar3 & 0xff,uVar3 >> 8,puVar4,uVar3);
        puVar1 = (undefined2 *)(G_savebx + 0x134);
        iVar2 = EXE_RndCo(2);
        iVar2 = iVar2 + 10;
        uVar3 = ovl_0502();
        puVar1 = (undefined2 *)(G_savebx + 0x74);
        EXE_movectile(iVar2,uVar3 & 0xff,uVar3 >> 8,
                           (int)G_oppscr,
                           (int)((ulong)G_oppscr >> 0x10),puVar4,unaff_DI)
        ;
        local_4 = local_4 + 1;
      }
    }
  }
  return local_4;
}


// ===== ovl_06af @ 3100:06af

undefined2 __cdecl16near ovl_06af(void)

{
  undefined2 in_AX;
  byte bVar1;
  byte bVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  bVar2 = (byte)G_winxy;
  if (((((byte)in_AX < bVar2) ||
       (bVar1 = (byte)((uint)in_AX >> 8),
       G_winxl <= (byte)((byte)in_AX - bVar2))) ||
      (bVar2 = (byte)((uint)G_winxy >> 8), bVar1 < bVar2)) ||
     (G_winyl <= (byte)(bVar1 - bVar2))) {
    return in_AX;
  }
  return in_AX;
}


// ===== INT60_13 @ 3100:06d2

undefined2 INT60_13(void)

{
  undefined2 *puVar1;
  byte bVar2;
  undefined2 *puVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined2 uVar4;
  
  G_workx = 0xff;
  OV_0x1c6 = 0;
  G_zp_12 = G_winxy + 0x405;
  for (puVar3 = (undefined2 *)G_loc+28; (char)*puVar3 != '\0';
      puVar3 = puVar3 + 3) {
    if (*(char *)(puVar3 + 1) == '\0') {
      ovl_07a4();
    }
  }
  uVar4 = G_savebx;
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(0x3000,0xf,uVar4);
  puVar1 = (undefined2 *)(G_savebx + 0x2b4);
  bVar2 = EXE_GetMagSkl(0x3000,uVar4);
  if ((uint)(bVar2 >> 2) * (uint)(bVar2 >> 2) < G_workx) {
    ovl_08f4();
  }
  else {
    OV_0x1c6 = G_zp_1415;
    puVar1 = (undefined2 *)(G_savebx + 0x54);
    EXE_SetTxtWnd(0x3000,1,uVar4);
    puVar1 = (undefined2 *)(G_savebx + 0x5c);
    EXE_ClrTxtWnd(0x3000,uVar4);
    puVar1 = (undefined2 *)(G_savebx + 0xe4);
    EXE_InitScrap(0x3000,uVar4);
    puVar1 = (undefined2 *)(G_savebx + 0xe8);
    EXE_AddScrap(0x3000,G_comtxtptr);
    ovl_082e();
    puVar1 = (undefined2 *)(G_savebx + 0xe8);
    EXE_AddScrap(0x3000,G_comtxtptr);
    puVar1 = (undefined2 *)(G_savebx + 0xec);
    EXE_PrtScrap(0x3000,3);
  }
  return OV_0x1c6;
}


// ===== ovl_07a4 @ 3100:07a4

void ovl_07a4(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  byte bVar6;
  undefined2 *in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar2 = (undefined2 *)(G_savebx + 0x11c);
  iVar4 = EXE_FindBit(&G_ambush,*(undefined1 *)(in_BX + 2),
                             G_savebx);
  if (iVar4 != 0) {
    return;
  }
  uVar1 = *in_BX;
  bVar3 = (char)uVar1 - G_zp_12;
  bVar6 = (char)((uint)uVar1 >> 8) - G_zp_13;
  if ((char)bVar3 < '\0') {
    bVar3 = -bVar3;
  }
  if ((char)bVar6 < '\0') {
    bVar6 = -bVar6;
  }
  uVar5 = (uint)bVar6 * (uint)bVar6 + (uint)bVar3 * (uint)bVar3;
  if (uVar5 < G_workx) {
    G_workx = uVar5;
    G_zp_1415 = uVar1;
  }
  return;
}


// ===== ovl_082e @ 3100:082e

void ovl_082e(void)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  cVar1 = G_zp_1415 - G_zp_12;
  cVar2 = G_zp_13 - G_zp_15;
  OV_0x8fa = CONCAT11(cVar2,cVar1);
  OV_0x8fc = 0;
  if (cVar1 < '\0') {
    OV_0x8fc = OV_0x8fc | 8;
    OV_0x8fa = -OV_0x8fa;
  }
  if (cVar2 < '\0') {
    OV_0x8fc = OV_0x8fc | 4;
    OV_0x8fb = -OV_0x8fb;
  }
  if ((char)(OV_0x8fb + '\x02') <= (char)(OV_0x8fa * '\x03'))
  {
    OV_0x8fc = OV_0x8fc | 2;
  }
  if ((char)(OV_0x8fb * '\x03') <= (char)(OV_0x8fa + '\x01'))
  {
    OV_0x8fc = OV_0x8fc | 1;
  }
  pcVar3 = (char *)(&OV_0x91e +
                   *(int *)(&OV_0x8fe + OV_0x8fc +
                           OV_0x8fc));
  G_zp_10 =
       CONCAT11(pcVar3[8] + G_zp_13,*pcVar3 + G_zp_12);
  return;
}


// ===== ovl_08cf @ 3100:08cf

void ovl_08cf(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x78);
  EXE_InitMap();
  ovl_08dc();
  return;
}


// ===== ovl_08dc @ 3100:08dc

void ovl_08dc(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xb0);
  EXE_FillWindow(G_winxy & 0xff,G_winxy >> 8);
  return;
}


// ===== ovl_08f4 @ 3100:08f4

void ovl_08f4(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined2 uVar2;
  undefined2 uVar3;
  
  uVar2 = G_savebx;
  uVar3 = 0xff;
  puVar1 = (undefined2 *)(G_savebx + 0x54);
  EXE_SetTxtWnd(1,uVar2);
  puVar1 = (undefined2 *)(G_savebx + 0x5c);
  EXE_ClrTxtWnd(uVar2);
  puVar1 = (undefined2 *)(G_savebx + 0xe4);
  EXE_InitScrap(uVar2);
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap(G_comtxtptr);
  puVar1 = (undefined2 *)(G_savebx + 0xec);
  EXE_PrtScrap(uVar3,uVar2);
  return;
}


// ===== INT60_07 @ 3100:0942

void INT60_07(void)

{
  byte bVar1;
  undefined2 *puVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar4 = CONCAT11(*(undefined1 *)(G_curpla + &G_p1y),
                   *(undefined1 *)(G_curpla + &G_p1x)) -
          G_winxy;
  puVar2 = (undefined2 *)(G_savebx + 0x1f0);
  iVar3 = EXE_Target(uVar4 & 0xff,uVar4 >> 8,0xd);
  if (iVar3 != -1) {
    for (pcVar5 = (char *)G_tdata+6; *pcVar5 != -1; pcVar5 = pcVar5 + 7) {
      if (((char)iVar3 == *pcVar5) && (pcVar5[2] == 'B')) {
        bVar1 = G_snakeptr;
        *(undefined1 *)((uint)bVar1 + &G_snakelocs) = G_curvar;
        *(undefined2 *)((uint)bVar1 * 2 + &G_snakes) =
             CONCAT11(G_worky,G_workx);
        G_snakeptr = G_snakeptr + '\x01';
        puVar2 = (undefined2 *)(G_savebx + 0x374);
        EXE_Spef5_a(CONCAT11(G_worky,
                                           G_workx) -
                                  G_winxy);
        ovl_08f4();
        *(char *)G_zp_0A = pcVar5[1];
        ovl_08dc();
        return;
      }
    }
    ovl_08f4();
  }
  return;
}


// ===== INT60_06 @ 3100:0947

/* WARNING: Removing unreachable block (ram,0x000319dc) */

void INT60_06(void)

{
  byte bVar1;
  undefined2 *puVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar4 = CONCAT11(*(undefined1 *)(G_curpla + &G_p1y),
                   *(undefined1 *)(G_curpla + &G_p1x)) -
          G_winxy;
  puVar2 = (undefined2 *)(G_savebx + 0x1f0);
  iVar3 = EXE_Target(uVar4 & 0xff,uVar4 >> 8,0xd);
  if (iVar3 != -1) {
    for (pcVar5 = (char *)G_tdata+6; *pcVar5 != -1; pcVar5 = pcVar5 + 7) {
      if (((char)iVar3 == *pcVar5) && (pcVar5[2] == 'C')) {
        bVar1 = G_snakeptr;
        *(undefined1 *)((uint)bVar1 + &G_snakelocs) = G_curvar;
        *(undefined2 *)((uint)bVar1 * 2 + &G_snakes) =
             CONCAT11(G_worky,G_workx);
        G_snakeptr = G_snakeptr + '\x01';
        puVar2 = (undefined2 *)(G_savebx + 0x374);
        EXE_Spef5_a(CONCAT11(G_worky,
                                           G_workx) -
                                  G_winxy);
        ovl_08f4();
        *(char *)G_zp_0A = pcVar5[1];
        ovl_08dc();
        return;
      }
    }
    ovl_08f4();
  }
  return;
}


// ===== INT60_14 @ 3100:09ff

void INT60_14(void)

{
  undefined2 *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined4 uVar6;
  
  iVar3 = 0xff;
  do {
    if (*(char *)(iVar3 + &G_snakelocs) == G_curvar) {
      iVar4 = iVar3 << 1;
      uVar6 = ovl_05f8();
      if ((int)((ulong)uVar6 >> 0x10) != 0) {
        puVar1 = (undefined2 *)(G_savebx + 0xf4);
        cVar2 = EXE_Locate((uint)uVar6 & 0xff,(uint)uVar6 >> 8,iVar4);
        for (pcVar5 = (char *)G_tdata+6; *pcVar5 != -1; pcVar5 = pcVar5 + 7
            ) {
          if (cVar2 == *pcVar5) {
            *(char *)G_zp_0A = pcVar5[1];
            break;
          }
        }
      }
    }
    iVar3 = iVar3 + -1;
    if (iVar3 < 0) {
      return;
    }
  } while( true );
}


// ===== INT60_16 @ 3100:0a57

void INT60_16(void)

{
  uint *puVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int unaff_SI;
  uint *puVar8;
  undefined2 unaff_DS;
  
  puVar8 = (uint *)&G_spetbldone;
  cVar3 = (char)G_curvar;
  if (cVar3 != G_lastp02var) {
    G_lastp02var = cVar3;
    for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
      puVar1 = puVar8;
      puVar8 = puVar8 + 1;
      *puVar1 = 0;
    }
    return;
  }
  iVar5 = G_loc+28;
  iVar6 = 8;
  do {
    uVar4 = *puVar8;
    iVar7 = 0x10;
    do {
      uVar2 = uVar4 & 1;
      uVar4 = uVar4 >> 1;
      if (uVar2 != 0) {
        *(undefined1 *)(iVar5 + 2) = 0xff;
      }
      iVar5 = iVar5 + 6;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    puVar8 = puVar8 + 1;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  return;
}


// ===== INT60_0b @ 3100:0a9b

void INT60_0b(void)

{
  char *pcVar1;
  char cVar2;
  undefined2 *puVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  undefined1 *puVar7;
  int iVar8;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar9;
  
  iVar8 = G_zp_1415;
  G_zp_16 = 0x80a;
  G_zp_1415 = G_winxy + 0x80a;
  puVar7 = (undefined1 *)&G_blobmap+98;
  do {
    bVar9 = G_terriflag == 1;
    if (!bVar9) {
      puVar3 = (undefined2 *)(G_savebx + 0xc4);
      iVar5 = EXE_ChkWlk();
      bVar9 = iVar5 == 1;
    }
    uVar4 = 0x7e;
    if (!bVar9) {
      uVar4 = 0xff;
    }
    *puVar7 = uVar4;
    G_zp_1415 = G_zp_1415 + -1;
    pcVar1 = (char *)&G_zp_16;
    cVar2 = *pcVar1;
    *pcVar1 = *pcVar1 + -1;
    if (SBORROW1(cVar2,'\x01') != *pcVar1 < '\0') {
      G_zp_1415 = G_zp_1415 + '\v';
      G_zp_16 = 10;
      G_zp_15 = G_zp_15 + -1;
      pcVar1 = (char *)&G_zp_17;
      cVar2 = *pcVar1;
      *pcVar1 = *pcVar1 + -1;
      if (SBORROW1(cVar2,'\x01') != *pcVar1 < '\0') {
        G_zp_1415 = iVar8 - G_winxy;
        ovl_0bca();
        puVar7[&G_blobmap] = 0;
        uVar6 = 0;
        while( true ) {
          OV_0xb99 = 1;
          while( true ) {
            G_BLOBFOUND = 0;
            iVar8 = 0x62;
            do {
              if (*(char *)(iVar8 + &G_blobmap) == (char)uVar6) {
                ovl_0b45();
              }
              bVar9 = 0 < iVar8;
              iVar8 = iVar8 + -1;
            } while (bVar9);
            if (G_BLOBFOUND != '\x01') break;
            OV_0xb99 = 0;
          }
          if (OV_0xb99 == 1) break;
          uVar6 = (uint)(byte)((char)uVar6 + 1);
        }
        return;
      }
    }
    puVar7 = puVar7 + -1;
  } while( true );
}


// ===== ovl_0b45 @ 3100:0b45

void ovl_0b45(void)

{
  bool bVar1;
  char in_CL;
  char cVar2;
  char cVar3;
  uint in_BX;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  cVar2 = in_CL + '\x01';
  cVar3 = '\a';
  do {
    iVar4 = CONCAT11((char)(in_BX >> 8),0xb);
    if (((byte)((char)(in_BX % 0xb) + OV_0x91e) < 0xb) &&
       ((byte)((char)(in_BX / 0xb) + OV_0x926) < 9)) {
      ovl_0bca();
      if (cVar2 < *(char *)(iVar4 + &G_blobmap)) {
        G_BLOBFOUND = 1;
        *(char *)(iVar4 + &G_blobmap) = cVar2;
      }
    }
    unaff_DI = unaff_DI + 1;
    bVar1 = '\0' < cVar3;
    cVar3 = cVar3 + -1;
  } while (bVar1);
  return;
}


// ===== INT60_0c @ 3100:0b87

void INT60_0c(void)

{
  undefined2 *puVar1;
  code *pcVar2;
  int iVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar3 = 0;
  G_cursory = 0xc;
  do {
    G_cursorx = 5;
    do {
      puVar1 = (undefined2 *)(G_savebx + 0x8c);
      EXE_MyCout(*(char *)(iVar3 + &G_blobmap) + '1');
      iVar3 = iVar3 + 1;
      if (iVar3 == 99) {
        pcVar2 = (code *)swi(0x16);
        (*pcVar2)();
        return;
      }
      G_cursorx = G_cursorx + 2;
    } while (G_cursorx < 0x31);
    G_cursory = G_cursory + 0x10;
  } while( true );
}


// ===== ovl_0bca @ 3100:0bca

void ovl_0bca(void)

{
  return;
}


// ===== INT60_0e @ 3100:0c2c

void INT60_0e(void)

{
  undefined2 uVar1;
  char *pcVar2;
  char cVar3;
  undefined2 *puVar4;
  undefined2 in_AX;
  int iVar5;
  int unaff_SI;
  int unaff_DI;
  char *pcVar6;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  bool bVar7;
  
  bVar7 = false;
  iVar5 = 0x1b;
  pcVar6 = (char *)&OV_0xcdb;
  do {
    if (iVar5 == 0) {
      return;
    }
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar2 = pcVar6;
      pcVar6 = pcVar6 + (uint)bVar7 * -2 + 1;
      in_ZF = (char)in_AX == *pcVar2;
    } while (!(bool)in_ZF);
    if (!(bool)in_ZF) {
      return;
    }
    LOCK();
    uVar1 = G_locspec;
    G_locspec = in_AX;
    UNLOCK();
    cVar3 = pcVar6[0x35];
    LOCK();
    in_AX = G_locspec;
    G_locspec = uVar1;
    UNLOCK();
    bVar7 = bVar7 != false;
    in_ZF = 0;
    if ((char)uVar1 == cVar3) {
      puVar4 = (undefined2 *)(G_savebx + 0xe0);
      EXE_SetBit(0x3000,&G_events,*(undefined1 *)((unaff_DI - iVar5) + 0xd10));
      return;
    }
  } while( true );
}


// ===== INT60_0f @ 3100:0c83

void INT60_0f(void)

{
  char *pcVar1;
  undefined2 *puVar2;
  int iVar3;
  int unaff_SI;
  int unaff_DI;
  char *pcVar4;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  iVar3 = 3;
  pcVar4 = (char *)&OV_0xd7d;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
    in_ZF = (char)G_locspec == *pcVar1;
  } while (!(bool)in_ZF);
  if ((bool)in_ZF) {
    puVar2 = (undefined2 *)(G_savebx + 0xe0);
    EXE_SetBit(0x3000,&G_events,*(undefined1 *)((unaff_DI - iVar3) + 0xd82));
  }
  return;
}


// ===== INT60_10 @ 3100:0cbd

undefined2 INT60_10(void)

{
  char *pcVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined2 in_BX;
  int unaff_SI;
  int unaff_DI;
  char *pcVar4;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  undefined2 uVar5;
  
  pcVar4 = (char *)&OV_0xdba;
  iVar3 = 3;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
    in_ZF = (char)G_curvar == *pcVar1;
  } while (!(bool)in_ZF);
  if ((bool)in_ZF) {
    if (G_indisguise == 0) {
      puVar2 = (undefined2 *)(G_savebx + 0x54);
      EXE_SetTxtWnd(1);
      puVar2 = (undefined2 *)(G_savebx + 0x5c);
      EXE_ClrTxtWnd(in_BX);
      puVar2 = (undefined2 *)(G_savebx + 0xe4);
      EXE_InitScrap(in_BX);
      puVar2 = (undefined2 *)(G_savebx + 0xe8);
      EXE_AddScrap(&OV_0x107,0x3100,0,in_BX);
      if ((char)*(undefined2 *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0xcb)
          != '\x1d') {
        puVar2 = (undefined2 *)(G_savebx + 0xec);
        EXE_PrtScrap(3,in_BX);
        return 1;
      }
      puVar2 = (undefined2 *)(G_savebx + 0xe8);
      EXE_AddScrap(&OV_0x107,0x3100,1,in_BX);
      puVar2 = (undefined2 *)(G_savebx + 0xec);
      EXE_PrtScrap(3,in_BX);
      uVar5 = G_animoff;
      G_animoff = 1;
      puVar2 = (undefined2 *)(G_savebx + 0x108);
      iVar3 = EXE_SetYN(in_BX);
      G_animoff = uVar5;
      if (iVar3 != 0) {
        return 1;
      }
      puVar2 = (undefined2 *)(G_savebx + 0x5c);
      EXE_ClrTxtWnd(in_BX);
      G_indisguise = 2;
      puVar2 = (undefined2 *)(G_savebx + 0x1fc);
      iVar3 = EXE_Magic(in_BX);
      if (iVar3 == 0) {
        return 1;
      }
    }
  }
  else {
    LOCK();
    iVar3 = G_indisguise;
    G_indisguise = 0;
    UNLOCK();
    if (iVar3 == 0) {
      return 0;
    }
  }
  puVar2 = (undefined2 *)(G_savebx + 0x1f8);
  EXE_LoadFolks(0,in_BX);
  return 0;
}


// ===== INT60_11 @ 3100:0dc7

void INT60_11(void)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined2 *puVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0xec4 = 0xff;
  puVar4 = (undefined2 *)G_loc+16;
  iVar3 = G_pwinxy + 0x405;
  while( true ) {
    cVar1 = (char)*puVar4;
    if (cVar1 == -1) break;
    cVar1 = cVar1 - (char)iVar3;
    if (cVar1 < '\0') {
      cVar1 = -cVar1;
    }
    cVar2 = (char)((uint)*puVar4 >> 8) - (char)((uint)iVar3 >> 8);
    if (cVar2 < '\0') {
      cVar2 = -cVar2;
    }
    if ((byte)(cVar1 + cVar2) < OV_0xec4) {
      OV_0xec4 = cVar1 + cVar2;
      OV_0xec5 = (int)(puVar4 + 1);
    }
    puVar4 = (undefined2 *)((int)puVar4 + 5);
  }
  LOCK();
  iVar3 = OV_0xec5;
  OV_0xec5 = unaff_SI;
  UNLOCK();
  *(undefined2 *)(OV_0xec5 + 0x2049) = *(undefined2 *)(iVar3 + 1);
  return;
}


// ===== INT60_12 @ 3100:0e35

char INT60_12(void)

{
  byte *pbVar1;
  char *pcVar2;
  char in_AL;
  int iVar3;
  int unaff_SI;
  int unaff_DI;
  char *pcVar4;
  undefined2 unaff_DS;
  bool bVar5;
  
  bVar5 = false;
  if (in_AL == -4) {
    if (G_curvar == 'A') {
      pbVar1 = (byte *)&G_events+3;
      *pbVar1 = *pbVar1 | 0x80;
      bVar5 = *pbVar1 == 0;
    }
    else {
      pbVar1 = (byte *)&G_events+4;
      *pbVar1 = *pbVar1 | 1;
      bVar5 = *pbVar1 == 0;
    }
  }
  iVar3 = 0xe;
  pcVar4 = (char *)&OV_0xf19;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar2 = pcVar4;
    pcVar4 = pcVar4 + 1;
    bVar5 = in_AL == *pcVar2;
  } while (!bVar5);
  if (bVar5) {
    return pcVar4[0xd];
  }
  return '\0';
}


// ===== INT60_15 @ 3100:0e71

undefined2 INT60_15(void)

{
  int iVar1;
  undefined2 *puVar2;
  byte bVar3;
  undefined2 in_CX;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  int iVar4;
  
  OV_0xf6c = in_CX;
  puVar2 = (undefined2 *)(G_savebx + 0x134);
  bVar3 = EXE_RndCo(0x3000,0x78);
  if (OV_0xf6c < bVar3) {
    puVar2 = (undefined2 *)(G_savebx + 0xe4);
    EXE_InitScrap(0x3000);
    puVar2 = (undefined2 *)(G_savebx + 0x5c);
    EXE_ClrTxtWnd(0x3000);
    puVar2 = (undefined2 *)(G_savebx + 0xe8);
    EXE_AddScrap(0x3000,&OV_0x107,0x3000,2);
    puVar2 = (undefined2 *)(G_savebx + 0xe8);
    EXE_AddScrap(0x3000,&OV_0x107,0x3000,OV_0xf6d + 2);
    puVar2 = (undefined2 *)(G_savebx + 0xd0);
    EXE_GameSound(0x3000,OV_0xf6d + 0x16);
    puVar2 = (undefined2 *)(G_savebx + 0x178);
    EXE_PrtWrd(0x3000,G_comtxtptr);
    puVar2 = (undefined2 *)(G_savebx + 0xe4);
    EXE_InitScrap(0x3000);
    puVar2 = (undefined2 *)(G_savebx + 0x5c);
    EXE_ClrTxtWnd(0x3000);
    LOCK();
    iVar1 = OV_0xf6d;
    OV_0xf6d = in_BX;
    UNLOCK();
    bVar3 = *(byte *)(iVar1 + &OV_0xf6f);
    LOCK();
    iVar4 = OV_0xf6d;
    OV_0xf6d = iVar1;
    UNLOCK();
    iVar1 = *(int *)(G_curpla * 2 + &G_heroptr);
    *(byte *)(iVar1 + 0xbd) = *(byte *)(iVar1 + 0xbd) | bVar3;
    *(byte *)(iVar1 + 0xba) = *(byte *)(iVar1 + 0xba) >> 1;
    *(byte *)(iVar1 + 0xca) = *(byte *)(iVar1 + 0xca) >> 1;
    puVar2 = (undefined2 *)(G_savebx + 0x88);
    EXE_SumStat(0x3000,iVar4);
    puVar2 = (undefined2 *)(G_savebx + 0xe8);
    EXE_AddScrap(0x3000,&OV_0x107,0x3000,5,iVar4);
    puVar2 = (undefined2 *)(G_savebx + 0xec);
    EXE_PrtScrap(0x3000,0xff,iVar4);
    puVar2 = (undefined2 *)(G_savebx + 0x178);
    EXE_PrtWrd(0x3000,G_comtxtptr);
    return 1;
  }
  return 0;
}


