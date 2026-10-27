// ===== ovl_0102 @ 1ca8:0102

int ovl_0102(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  iVar1 = iRam000004f8 + 0x1f00;
  *(undefined2 *)(*piRam000004fc + -0x728a) = piRam000004fc;
  return iVar1;
}


// ===== ovl_0123 @ 1ca8:0123

void ovl_0123(void)

{
  int iVar1;
  char cVar2;
  char cVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  int in_BX;
  undefined2 unaff_BP;
  undefined2 *unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined2 in_stack_00000000;
  
  ovl_0102();
  uVar4 = unaff_SI[0x2d40];
  uVar5 = unaff_SI[0x2d41];
  unaff_SI[0x2d40] = &OV_0x139;
  unaff_SI[0x2d41] = 0x1ca8;
  *unaff_SI = 0;
  unaff_SI[1] = unaff_SI[1] + 1;
  ovl_0321(uVar5,uVar4);
  LOCK();
  iVar1 = unaff_SI[3];
  unaff_SI[3] = in_BX;
  UNLOCK();
  cVar2 = *(char *)(iVar1 + &OV_0x10e);
  cVar3 = *(char *)(iVar1 + &OV_0x11a);
  LOCK();
  unaff_SI[3] = iVar1;
  UNLOCK();
  if (cVar2 == *(char *)(unaff_SI + 1)) {
    *(undefined1 *)(unaff_SI + 5) = 0x4c;
    *(byte *)((int)&G_events) = *(byte *)((int)&G_events) & 0xfe;
  }
  else if (cVar3 == *(char *)(unaff_SI + 1)) {
    *(undefined1 *)(unaff_SI + 5) = 0x44;
    *(byte *)((int)&G_events) = *(byte *)((int)&G_events) | 1;
  }
  else if (0x17 < *(byte *)(unaff_SI + 1)) {
    ovl_01cd();
  }
  if (*(char *)(unaff_SI + 1) == '\a') {
    ovl_0447();
  }
  if (*(char *)(unaff_SI + 1) == '\b') {
    ovl_040d();
  }
  if (*(char *)(unaff_SI + 1) == '\f') {
    ovl_04b0();
  }
  if (*(char *)(unaff_SI + 1) == '\x11') {
    ovl_09ff();
  }
  if (*(char *)(unaff_SI + 1) == '\x12') {
    ovl_09ff();
  }
  ovl_04c7();
  ovl_0561();
  unaff_SI[0x2d41] = unaff_BP;
  unaff_SI[0x2d40] = in_stack_00000000;
  return;
}


// ===== ovl_01cd @ 1ca8:01cd

void ovl_01cd(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_juldate = G_juldate + 1;
  if ((G_disasterday != 0) &&
     (G_juldate - G_disasterday == 7)) {
    G_events = G_events | 2;
  }
  if (G_juldate == 0x14) {
    G_events+14 = G_events+14 | 4;
  }
  if (G_remdays != 0) {
    G_remdays = G_remdays + -1;
  }
  if ((G_juldate & 7) == 0) {
    ovl_02cb();
  }
  *(undefined2 *)(unaff_SI + 2) = 0;
  ovl_02ed();
  *(int *)(unaff_SI + 4) = *(int *)(unaff_SI + 4) + 1;
  if (0x1e < *(uint *)(unaff_SI + 4)) {
    *(undefined2 *)(unaff_SI + 4) = 1;
    *(int *)(unaff_SI + 6) = *(int *)(unaff_SI + 6) + 1;
    if (0xb < *(uint *)(unaff_SI + 6)) {
      *(undefined2 *)(unaff_SI + 6) = 0;
      *(int *)(unaff_SI + 8) = *(int *)(unaff_SI + 8) + 1;
    }
    if (*(int *)(unaff_SI + 6) == 9) {
      G_events+3 = G_events+3 | 8;
    }
    ovl_0265();
    ovl_02ac();
  }
  return;
}


// ===== ovl_0265 @ 1ca8:0265

void ovl_0265(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined1 uVar3;
  byte bVar4;
  undefined2 *puVar5;
  int iVar6;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 *puVar7;
  undefined2 unaff_DS;
  
  LOCK();
  iVar6 = *(int *)(unaff_SI + 6);
  *(int *)(unaff_SI + 6) = in_BX;
  UNLOCK();
  uVar3 = *(undefined1 *)(iVar6 + &OV_0x34d);
  bVar4 = *(byte *)(iVar6 + &OV_0x359);
  LOCK();
  *(int *)(unaff_SI + 6) = iVar6;
  UNLOCK();
  G_season = uVar3;
  G_events+1 = G_events+1 | bVar4;
  G_events+1 = G_events+1 & bVar4 - 0x1f;
  if (G_curmpg == 1) {
    puVar5 = (undefined2 *)((G_season & 0xff) * 0xc + G_loc+22)
    ;
    puVar7 = (undefined2 *)&G_ssnwthrs;
    for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
      puVar2 = puVar7;
      puVar7 = puVar7 + 1;
      puVar1 = puVar5;
      puVar5 = puVar5 + 1;
      *puVar2 = *puVar1;
    }
  }
  return;
}


// ===== ovl_02ac @ 1ca8:02ac

void ovl_02ac(void)

{
  int iVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = 8;
  do {
    G_casino = G_casino + 200;
    if (1000 < G_casino) {
      G_casino = 1000;
    }
    unaff_SI = unaff_SI + 2;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_02cb @ 1ca8:02cb

void ovl_02cb(void)

{
  int iVar1;
  byte *pbVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  pbVar2 = (byte *)&G_mushsta;
  iVar1 = 0x20;
  do {
    if ((*pbVar2 & 0xf) != 0xf) {
      *pbVar2 = *pbVar2 + 1;
    }
    if ((*pbVar2 & 0xf0) != 0xf0) {
      *pbVar2 = *pbVar2 + 0x10;
    }
    pbVar2 = pbVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_02ed @ 1ca8:02ed

void ovl_02ed(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar3 = G_heroptr+2;
  iVar1 = 2;
  iVar2 = 5;
  do {
    if (((*(int *)(iVar1 + &G_party) != 0xff) && (*(char *)(iVar3 + 0xb8) == '\x01')) &&
       (*(byte *)(iVar3 + 0xd2) < 100)) {
      *(char *)(iVar3 + 0xd2) = *(char *)(iVar3 + 0xd2) + '\x01';
    }
    iVar1 = iVar1 + 2;
    iVar3 = iVar3 + 0xdc;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


// ===== ovl_0321 @ 1ca8:0321

void ovl_0321(void)

{
  char *pcVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x130 = 5;
  iVar4 = 6;
  iVar5 = 0;
  *(undefined2 *)(unaff_DI + 300) = 0;
  do {
    if (*(int *)(iVar5 + &G_party) != 0xff) {
      ovl_039d();
    }
    *(int *)(unaff_DI + 300) = *(int *)(unaff_DI + 300) + 1;
    iVar5 = iVar5 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  OV_0x130 = 1;
  iVar5 = 0x1f;
  iVar4 = &G_member6;
  OV_0x131 = &G_assgn0;
  do {
    LOCK();
    pcVar1 = (char *)OV_0x131;
    OV_0x131 = in_BX;
    UNLOCK();
    cVar2 = *pcVar1;
    cVar3 = pcVar1[5];
    LOCK();
    in_BX = OV_0x131;
    OV_0x131 = (int)pcVar1;
    UNLOCK();
    if ((cVar2 != -1) && (cVar3 == '\a')) {
      ovl_039d(iVar5,iVar4);
    }
    *(int *)(unaff_DI + 300) = *(int *)(unaff_DI + 300) + 1;
    iVar4 = iVar4 + 0xdc;
    OV_0x131 = OV_0x131 + 0x19;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}


// ===== ovl_039d @ 1ca8:039d

void ovl_039d(void)

{
  int in_AX;
  int iVar1;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (*(char *)(in_AX + 0xbc) != -1) {
    *(char *)(in_AX + 0xbc) = *(char *)(in_AX + 0xbc) + '\x01';
  }
  if (*(byte *)((uint)*(byte *)(in_AX + 6) + &OV_0x126) <= *(byte *)(in_AX + 0xbc)) {
    iVar1 = EXE_SearchInv(0x31,*(undefined2 *)(unaff_DI + 300),&OV_0x106,0x1000);
    if ((iVar1 != 0) && (OV_0x130 < OV_0x106)) {
      EXE_DoUse(in_AX,0,0x31,in_BX);
      return;
    }
    EXE_IsHeHu(in_AX,in_BX);
  }
  return;
}


// ===== ovl_040d @ 1ca8:040d

void ovl_040d(void)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  char *pcVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  pcVar4 = (char *)&G_capdays;
  iVar3 = 6;
  do {
    if (*pcVar4 != '\0') {
      *pcVar4 = *pcVar4 + -1;
    }
    if (*pcVar4 == '\0') {
      cVar1 = G_capsta;
      if (cVar1 == '\0') {
        uVar2 = 3;
      }
      else if (cVar1 == '\x01') {
        uVar2 = 2;
      }
      else {
        if (cVar1 != '\x05') goto L_0440;
        uVar2 = 4;
      }
      G_capsta = uVar2;
    }
L_0440:
    pcVar4 = pcVar4 + 1;
    unaff_SI = unaff_SI + 1;
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      return;
    }
  } while( true );
}


// ===== ovl_0447 @ 1ca8:0447

void ovl_0447(void)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (G_capsta+2 != '\x06') {
    return;
  }
  G_capsta+2 = 7;
  G_capdays+2 = 0;
  uVar1 = G_curpla;
  iVar3 = 6;
  iVar4 = 0;
  do {
    G_curpla = iVar4;
    iVar2 = EXE_SearchInv(0,iVar4,&OV_0x106,0x1ca8);
    iVar4 = G_curpla;
    if (iVar2 != 0) {
      EXE_DecObj0(0,*(undefined2 *)(*(int *)(iVar4 * 2 + &G_heroptr) + 0xcc));
      iVar4 = G_curpla;
    }
    iVar4 = iVar4 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  G_curpla = uVar1;
  return;
}


// ===== ovl_04b0 @ 1ca8:04b0

void ovl_04b0(void)

{
  int iVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = 8;
  do {
    if (G_rents != '\0') {
      G_rents = G_rents + -1;
    }
    unaff_SI = unaff_SI + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_04c7 @ 1ca8:04c7

void ovl_04c7(void)

{
  undefined1 *puVar1;
  char cVar2;
  undefined2 uVar3;
  undefined2 *puVar4;
  byte bVar5;
  undefined1 uVar6;
  char cVar7;
  byte bVar9;
  uint uVar8;
  int iVar10;
  int in_BX;
  byte *pbVar11;
  int unaff_SI;
  int iVar12;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar10 = 0x10;
  iVar12 = unaff_SI;
  do {
    if (*(char *)(iVar12 + 0x2386) != '\0') {
      *(char *)(iVar12 + 0x2386) = *(char *)(iVar12 + 0x2386) + -1;
    }
    iVar12 = iVar12 + 2;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  iVar12 = &G_curwthrs + G_curreg * 2;
  if (*(char *)(iVar12 + 1) == '\0') {
    OV_0x5c4 = iVar12;
    bVar5 = EXE_RndCo(100);
    pbVar11 = (byte *)&G_ssnwthrs;
    iVar12 = 4;
    do {
      if (bVar5 < *pbVar11) break;
      pbVar11 = pbVar11 + 3;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
    uVar3 = *(undefined2 *)(pbVar11 + 1);
    uVar6 = (undefined1)uVar3;
    G_weather = uVar6;
    LOCK();
    puVar1 = (undefined1 *)OV_0x5c4;
    OV_0x5c4 = in_BX;
    UNLOCK();
    *puVar1 = uVar6;
    LOCK();
    iVar12 = OV_0x5c4;
    OV_0x5c4 = (int)puVar1;
    UNLOCK();
    bVar5 = (byte)((uint)uVar3 >> 8);
    bVar9 = bVar5 >> 4;
    OV_0x5c6 = bVar9;
    uVar8 = CONCAT11(bVar9,bVar5) & 0xff0f;
    puVar4 = (undefined2 *)(iVar12 + 0x134);
    cVar7 = EXE_RndCo(0x1000,((char)uVar8 - (char)(uVar8 >> 8)) + '\x02');
    cVar2 = OV_0x5c6;
    LOCK();
    iVar10 = OV_0x5c4;
    OV_0x5c4 = iVar12;
    UNLOCK();
    *(char *)(iVar10 + 1) = cVar7 + cVar2;
    LOCK();
    OV_0x5c4 = iVar10;
    UNLOCK();
  }
  return;
}


// ===== ovl_0555 @ 1ca8:0555

void ovl_0555(void)

{
  ovl_0102();
  ovl_0561();
  return;
}


// ===== ovl_0561 @ 1ca8:0561

void ovl_0561(void)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  pcVar3 = (char *)&G_assgn0;
  iVar2 = 0x1f;
  do {
    if (((*pcVar3 != -1) && ((uint)(byte)pcVar3[0x13] != *(uint *)(unaff_SI + 4))) &&
       ((uint)(byte)pcVar3[0x15] == *(uint *)(unaff_SI + 2))) {
      if ((byte)pcVar3[5] < 0x5a) {
        ovl_05b1();
      }
      else {
        pcVar3[0x13] = pcVar3[0x13] + '\x01';
        if ((byte)pcVar3[5] < 0x5e) {
          uVar1 = (uint)(byte)pcVar3[8] + *(int *)(pcVar3 + 0x11);
          if (9999 < uVar1) {
            uVar1 = 9999;
          }
          *(uint *)(pcVar3 + 0x11) = uVar1;
        }
      }
      ovl_08f7();
    }
    pcVar3 = pcVar3 + 0x19;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


// ===== ovl_05b1 @ 1ca8:05b1

void ovl_05b1(void)

{
  byte bVar1;
  char cVar2;
  int in_CX;
  int in_BX;
  undefined2 unaff_DS;
  bool bVar3;
  
  if (*(char *)(in_BX + 0x14) != '\0') {
    *(char *)(in_BX + 0x14) = *(char *)(in_BX + 0x14) + -1;
    bVar3 = *(byte *)(in_BX + 5) < 8;
    if (*(byte *)(in_BX + 5) == 8) {
      ovl_0716();
      if (bVar3) {
        return;
      }
    }
    if ((0x27 < *(byte *)(in_BX + 5)) && (*(byte *)(in_BX + 5) < 0x2f)) {
      ovl_0828();
    }
    if (*(char *)(in_BX + 0x14) != '\0') {
      return;
    }
  }
  bVar1 = *(byte *)(in_BX + 5);
  *(byte *)(in_BX + 6) = bVar1;
  if (bVar1 == 8) {
    *(undefined2 *)(in_BX + 3) = 0x205;
    *(undefined2 *)(in_BX + 0xd) =
         CONCAT11(*(undefined1 *)(in_BX + 0x10),*(undefined1 *)(in_BX + 7));
    *(undefined1 *)(in_BX + 5) = 0xff;
    return;
  }
  if (bVar1 < 0x1e) {
    if (9 < bVar1) {
      ovl_07b0(in_BX);
      in_BX = in_CX;
    }
  }
  else if (bVar1 < 0x22) {
    ovl_07c4(in_BX);
    in_BX = in_CX;
  }
  *(undefined1 *)(in_BX + 5) = 8;
  *(undefined1 *)(in_BX + 1) = *(undefined1 *)(in_BX + 0x16);
  *(undefined1 *)(in_BX + 2) = *(undefined1 *)(in_BX + 0x17);
  *(undefined1 *)(in_BX + 0xb) = 0xff;
  cVar2 = *(char *)(in_BX + 0x18);
  *(char *)(in_BX + 0x14) = cVar2;
  if (cVar2 == '\0') {
    *(undefined2 *)(in_BX + 3) = 0x205;
    *(undefined2 *)(in_BX + 0xd) =
         CONCAT11(*(undefined1 *)(in_BX + 0x10),*(undefined1 *)(in_BX + 7));
    *(undefined1 *)(in_BX + 5) = 0xff;
  }
  return;
}


// ===== ovl_06b3 @ 1ca8:06b3

void ovl_06b3(void)

{
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  int unaff_DI;
  bool bVar4;
  
  uVar1 = OV_0x137 * 4;
  bVar4 = CARRY2(&OV_0x74eU,uVar1);
  puVar3 = (undefined1 *)(&OV_0x74eU + uVar1);
  iVar2 = 4;
  do {
    OV_0x7b2 = *puVar3;
    ovl_06df();
    if (bVar4) {
      return;
    }
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + -1;
    bVar4 = false;
  } while (iVar2 != 0);
  return;
}


// ===== ovl_06df @ 1ca8:06df

void ovl_06df(void)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (OV_0x7b2 != -1) {
    pcVar3 = (char *)&G_assgn0;
    while( true ) {
      pcVar1 = pcVar3 + 2;
      pcVar2 = pcVar3 + 5;
      if (((*pcVar3 != -1) && (*pcVar1 == OV_0x7b2)) && (*pcVar2 == 'e')) break;
      pcVar3 = pcVar3 + 0x19;
      if (CONCAT11(*pcVar2,*pcVar1) == 1) {
        return;
      }
    }
  }
  return;
}


// ===== ovl_0716 @ 1ca8:0716

void ovl_0716(void)

{
  char *pcVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  byte bVar5;
  int iVar6;
  undefined2 in_BX;
  int iVar7;
  int unaff_SI;
  int unaff_DI;
  char *pcVar8;
  undefined2 unaff_DS;
  undefined1 uVar9;
  
  OV_0x131 = in_BX;
  ovl_0c06();
  OV_0x133 = in_BX;
  iVar7 = G_savebx;
  iVar6 = EXE_RndCo(10);
  if (iVar6 == 0) {
    bVar5 = EXE_RndCo(100);
    LOCK();
    iVar6 = OV_0x133;
    OV_0x133 = iVar7;
    UNLOCK();
    uVar9 = bVar5 < *(byte *)(iVar6 + 0x1e);
    LOCK();
    iVar7 = OV_0x133;
    OV_0x133 = iVar6;
    UNLOCK();
    if (!(bool)uVar9) {
      ovl_0b40();
      ovl_06b3();
      if (!(bool)uVar9) {
        return;
      }
      pcVar8 = (char *)&OV_0x78e;
      cVar2 = OV_0x7b2;
      iVar6 = 9;
      do {
        if (iVar6 == 0) break;
        iVar6 = iVar6 + -1;
        pcVar1 = pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar2 != *pcVar1);
      iVar6 = (unaff_DI + 8) - iVar6;
      uVar9 = *(undefined1 *)(iVar6 + 0x797);
      uVar3 = *(undefined1 *)(iVar6 + 0x7a0);
      uVar4 = *(undefined1 *)(iVar6 + 0x7a9);
      LOCK();
      iVar6 = OV_0x131;
      OV_0x131 = iVar7;
      UNLOCK();
      *(undefined1 *)(iVar6 + 1) = uVar9;
      *(char *)(iVar6 + 0xb) = cVar2;
      *(undefined1 *)(iVar6 + 2) = 0xff;
      *(undefined2 *)(iVar6 + 3) = 0x202;
      *(undefined2 *)(iVar6 + 0xd) = CONCAT11(uVar4,uVar3);
      *(undefined1 *)(iVar6 + 5) = 0x65;
      *(undefined1 *)(iVar6 + 6) = 0xff;
      *(undefined2 *)(iVar6 + 0x11) = 0;
      LOCK();
      OV_0x131 = iVar6;
      UNLOCK();
      return;
    }
  }
  return;
}


// ===== ovl_07b0 @ 1ca8:07b0

void ovl_07b0(void)

{
  char *pcVar1;
  char in_AL;
  byte bVar2;
  int in_BX;
  undefined2 unaff_DS;
  undefined2 in_stack_00000000;
  
  ovl_0c06(CONCAT11(in_AL + '\r',*(undefined1 *)(in_BX + 8)));
  bVar2 = (byte)((uint)in_stack_00000000 >> 8);
  pcVar1 = (char *)CONCAT11((char)((uint)in_BX >> 8) + CARRY1((byte)in_BX,bVar2),(byte)in_BX + bVar2
                           );
  *pcVar1 = *pcVar1 + (char)in_stack_00000000;
  return;
}


// ===== ovl_07c4 @ 1ca8:07c4

void ovl_07c4(void)

{
  byte *pbVar1;
  char cVar2;
  undefined2 *puVar3;
  char in_AL;
  char *in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x12e = in_AL + '.';
  OV_0x131 = in_BX;
  cVar2 = *in_BX;
  *(uint *)(unaff_DI + 300) = (uint)(byte)(cVar2 + 5);
  OV_0x133 = &G_member6 + (uint)(byte)(cVar2 - 1) * 0xdc;
  puVar3 = (undefined2 *)(G_savebx + 0x158);
  EXE_SearchInv(0x1000,OV_0x12e,*(undefined2 *)(unaff_DI + 300),
                     &OV_0x106,0x1000,G_savebx);
  pbVar1 = (byte *)(OV_0x133 + OV_0x108 + 0x53);
  *pbVar1 = *pbVar1 | 0x80;
  return;
}


// ===== ovl_0828 @ 1ca8:0828

void ovl_0828(void)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  char cVar4;
  char *in_BX;
  int iVar5;
  int unaff_SI;
  byte *pbVar6;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x131 = in_BX;
  cVar4 = *in_BX;
  *(uint *)(unaff_DI + 300) = (uint)(byte)(cVar4 + 5);
  OV_0x133 = &G_member6 + (uint)(byte)(cVar4 - 1) * 0xdc;
  uVar2 = (uint)(byte)((in_BX[5] + -0x28) * '\x06');
  OV_0x924 = uVar2;
  OV_0x91a = uVar2 + OV_0x133 + 0x7b;
  OV_0x918 = 0x96;
  while( true ) {
    iVar5 = 0;
    cVar4 = '\0';
    OV_0x91c = 0;
    pbVar6 = (byte *)OV_0x91a;
    iVar3 = 6;
    do {
      if (*pbVar6 < 99) {
        *(char *)(iVar5 + &OV_0x91e) = cVar4;
        OV_0x91c = OV_0x91c + 1;
        iVar5 = iVar5 + 1;
      }
      pbVar6 = pbVar6 + 1;
      cVar4 = cVar4 + '\x01';
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    if (OV_0x91c == 0) break;
    iVar3 = G_savebx;
    iVar5 = EXE_RndCo(OV_0x91c);
    uVar2 = (uint)*(byte *)(iVar5 + &OV_0x91e);
    OV_0x926 = uVar2;
    uVar2 = EXE_LrnTim(uVar2 + OV_0x924,*(undefined2 *)(unaff_DI + 300),
                       iVar3);
    if (OV_0x918 < uVar2) {
      return;
    }
    OV_0x918 = OV_0x918 - uVar2;
    pcVar1 = (char *)(OV_0x91a + OV_0x926);
    *pcVar1 = *pcVar1 + '\x01';
  }
  *(undefined1 *)(OV_0x131 + 0x14) = 0;
  return;
}


// ===== ovl_08f7 @ 1ca8:08f7

void ovl_08f7(void)

{
  undefined1 *puVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  byte *in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  int iVar7;
  
  OV_0x131 = in_BX;
  if (in_BX[5] == 100) {
    return;
  }
  if (in_BX[5] == 0x65) {
    return;
  }
  bVar4 = *in_BX;
  *(uint *)(unaff_DI + 300) = (uint)bVar4;
  iVar6 = &G_member0+1100 + (uint)bVar4 * 0xdc;
  OV_0x133 = iVar6;
  bVar4 = in_BX[5];
  if ((bVar4 != 7) && (bVar4 != 8)) {
    if ((bVar4 < 0x5a) || (0x5d < bVar4)) {
      bVar4 = in_BX[0x14];
    }
    else {
      if (0x270e < *(uint *)(in_BX + 0x11)) goto L_09ad;
      bVar4 = (byte)(*(uint *)(in_BX + 0x11) >> 10);
    }
    if (bVar4 < *(byte *)(iVar6 + 0x12)) {
      return;
    }
  }
  LOCK();
  iVar6 = OV_0x133;
  OV_0x133 = (int)in_BX;
  UNLOCK();
  bVar4 = *(char *)(iVar6 + 0xd2) + *(char *)(iVar6 + 0x12);
  bVar5 = bVar4 - 0xf;
  if (bVar4 < 0xf) {
    bVar5 = 0;
  }
  *(byte *)(iVar6 + 0xd2) = bVar5;
  LOCK();
  OV_0x133 = iVar6;
  UNLOCK();
  if (0x28 < bVar5) {
    return;
  }
  puVar3 = (undefined2 *)(G_savebx + 0x134);
  bVar4 = EXE_ClearBit(0x1000,0x50,G_savebx);
  if (bVar4 <= bVar5) {
    return;
  }
  iVar7 = G_savebx;
  bVar5 = EXE_RndCo(0xc);
  LOCK();
  iVar6 = OV_0x133;
  OV_0x133 = iVar7;
  UNLOCK();
  bVar4 = *(byte *)(iVar6 + 0x12);
  LOCK();
  OV_0x133 = iVar6;
  UNLOCK();
  if (bVar5 < bVar4) {
    return;
  }
L_09ad:
  LOCK();
  puVar1 = (undefined1 *)OV_0x131;
  OV_0x131 = G_savebx;
  UNLOCK();
  *puVar1 = 0xff;
  LOCK();
  uVar2 = *(undefined2 *)(puVar1 + 0x11);
  *(undefined2 *)(puVar1 + 0x11) = 0;
  UNLOCK();
  LOCK();
  iVar6 = OV_0x131;
  OV_0x131 = (int)puVar1;
  UNLOCK();
  EXE_IncObj(OV_0x133,0,uVar2);
  LOCK();
  iVar7 = OV_0x133;
  OV_0x133 = iVar6;
  UNLOCK();
  *(undefined1 *)(iVar7 + 0xb9) = 0xff;
  LOCK();
  iVar6 = OV_0x133;
  OV_0x133 = iVar7;
  UNLOCK();
  puVar3 = (undefined2 *)(iVar6 + 0x1bc);
  EXE_ClearBit(0x1000,&G_npcsta,*(undefined2 *)(unaff_DI + 300),iVar6);
  return;
}


// ===== ovl_09ff @ 1ca8:09ff

int ovl_09ff(void)

{
  char *pcVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int unaff_SI;
  int unaff_DI;
  char *pcVar7;
  undefined2 unaff_DS;
  bool bVar8;
  
  G_othername = G_heroptr;
  G_othername+2 = unaff_DS;
  iVar4 = 6;
  iVar6 = 0;
  *(undefined2 *)(unaff_DI + 300) = 0;
  do {
    iVar3 = *(int *)(iVar6 + &G_heroptr);
    if ((*(int *)(iVar6 + &G_party) != 0xff) && (*(char *)(iVar3 + 0xb8) == '\x02')) {
      pcVar7 = (char *)(iVar6 + 0xd3);
      bVar8 = pcVar7 == (char *)0x0;
      iVar5 = 4;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar1 = pcVar7;
        pcVar7 = pcVar7 + 1;
        bVar8 = *(char *)(unaff_SI + 4) == *pcVar1;
      } while (!bVar8);
      if (bVar8) {
        iVar3 = ovl_0a9d();
        bVar2 = (byte)iVar3;
        if (*(char *)(unaff_SI + 2) == '\x11') {
          if (bVar2 < 6) {
            iVar3 = ovl_0c13();
          }
        }
        else {
          *(byte *)(iVar6 + 0xd2) = bVar2;
          *(undefined2 *)(iVar6 + 0xce) = 0;
          *(undefined2 *)(iVar6 + 0xd0) = 0;
          if (bVar2 < 4) {
            iVar3 = ovl_0a88();
          }
        }
      }
    }
    *(int *)(unaff_DI + 300) = *(int *)(unaff_DI + 300) + 1;
    iVar6 = iVar6 + 2;
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
      return iVar3;
    }
  } while( true );
}


// ===== ovl_0a88 @ 1ca8:0a88

void ovl_0a88(void)

{
  int in_DX;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined2 in_stack_00000000;
  
  *(undefined1 *)(in_DX + 0xd2) = 0xff;
  ovl_0c39(1);
  EXE_AddScrap(&OV_0x139,0x1000,in_stack_00000000);
  EXE_PrtScrap(1);
  return;
}


// ===== ovl_0a9d @ 1ca8:0a9d

undefined2 ovl_0a9d(void)

{
  uint uVar1;
  byte bVar2;
  int in_AX;
  undefined2 uVar3;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0xb9b = *(undefined1 *)(in_AX + 0xd2);
  OV_0xb99 = *(undefined2 *)(in_AX + 0xce);
  uVar1 = *(uint *)(in_AX + 0xd0);
  OV_0xb97 = uVar1;
  if (uVar1 < 100) {
    OV_0xb9c = (char)uVar1;
    uVar3 = ovl_0af7();
  }
  else {
    bVar2 = (byte)(OV_0xb99 >> 8);
    if ((CONCAT11(bVar2 >> 2,(char)(OV_0xb99 >> 2)) & 0xffe0) == (uVar1 & 0xffe0)
       ) {
      uVar3 = CONCAT11(bVar2 >> 2,OV_0xb9b);
    }
    else {
      OV_0xb9c = 200;
      uVar3 = ovl_0af7();
    }
  }
  return uVar3;
}


// ===== ovl_0af7 @ 1ca8:0af7

uint ovl_0af7(void)

{
  ulong uVar1;
  uint in_AX;
  uint uVar2;
  uint in_DX;
  byte bVar3;
  int unaff_DI;
  
  bVar3 = (byte)(in_DX >> 8);
  if (bVar3 != 0) {
    if (bVar3 < 0x10) {
      in_AX = in_AX >> 4;
      in_DX = in_DX >> 4;
    }
    else {
      in_AX = in_AX >> 8;
      in_DX = (uint)bVar3;
    }
  }
  if (in_AX == 0) {
    in_AX = 1;
  }
  uVar1 = CONCAT22(in_AX >> 1,
                   in_DX * CONCAT11((char)(in_DX >> 8),OV_0xb9b) +
                   (in_AX >> 1)) / (ulong)in_AX;
  uVar2 = (uint)uVar1;
  if (199 < uVar2) {
    uVar2 = CONCAT11((char)(uVar1 >> 8),200);
  }
  if (OV_0xb9c <= (byte)uVar2) {
    uVar2 = CONCAT11((char)(uVar2 >> 8),OV_0xb9c);
  }
  return uVar2;
}


// ===== ovl_0b40 @ 1ca8:0b40

void ovl_0b40(void)

{
  int iVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar4;
  char cVar5;
  undefined2 uVar6;
  char cVar7;
  undefined2 extraout_DX;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  LOCK();
  iVar1 = OV_0x131;
  OV_0x131 = in_BX;
  UNLOCK();
  uVar6 = *(undefined2 *)(iVar1 + 0xd);
  uVar2 = *(undefined1 *)(iVar1 + 7);
  uVar3 = *(undefined1 *)(iVar1 + 0x10);
  cVar7 = *(char *)(iVar1 + 0x18);
  cVar4 = *(char *)(iVar1 + 0x14);
  cVar5 = *(char *)(iVar1 + 5);
  LOCK();
  OV_0x131 = iVar1;
  UNLOCK();
  if (cVar5 == '\b') {
    OV_0xc3c = uVar6;
    OV_0xc3e = CONCAT11(uVar3,uVar2);
    cVar7 = ovl_0bdc(CONCAT11(-(cVar4 - cVar7),cVar7));
    OV_0x135 = cVar7 + OV_0xc3c;
    cVar7 = ovl_0bdc();
    OV_0x136 = cVar7 + OV_0xc3d;
  }
  else {
    OV_0x135 = uVar6;
  }
  ovl_0bb5();
  OV_0x137 = extraout_DX;
  return;
}


// ===== ovl_0bb5 @ 1ca8:0bb5

void ovl_0bb5(void)

{
  byte in_AL;
  byte in_AH;
  int unaff_DI;
  
  for (; (((in_AL < OV_0x1c2 || (OV_0x1c4 < in_AL)) ||
          (in_AH < OV_0x1c3)) || (OV_0x1c5 < in_AH));
      unaff_DI = unaff_DI + 4) {
  }
  return;
}


// ===== ovl_0bdc @ 1ca8:0bdc

uint ovl_0bdc(void)

{
  byte bVar1;
  char cVar2;
  uint in_AX;
  uint uVar3;
  int iVar4;
  byte in_CL;
  byte in_CH;
  
  if (in_CL == 0) {
    return in_AX & 0xff00;
  }
  if (in_CL <= in_CH) {
    return in_AX;
  }
  uVar3 = in_AX;
  if ((in_AX & 0x8000) != 0) {
    uVar3 = (uint)(byte)-(char)in_AX;
  }
  iVar4 = (uVar3 & 0xff) * (uint)in_CH;
  bVar1 = (byte)iVar4;
  uVar3 = CONCAT11((char)((uint)iVar4 >> 8) + CARRY1(bVar1,in_CL >> 1),bVar1 + (in_CL >> 1));
  cVar2 = (char)(uVar3 / in_CL);
  if ((in_AX & 0x8000) != 0) {
    cVar2 = -cVar2;
  }
  return CONCAT11((char)(uVar3 % (uint)in_CL),cVar2);
}


// ===== ovl_0c06 @ 1ca8:0c06

int ovl_0c06(void)

{
  byte *in_BX;
  undefined2 unaff_DS;
  
  return (uint)*in_BX * 0xdc;
}


// ===== ovl_0c13 @ 1ca8:0c13

void ovl_0c13(void)

{
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined2 in_stack_00000000;
  
  ovl_0c39();
  EXE_AddScrap(&OV_0x139,0x1000,in_stack_00000000);
  EXE_PrtScrap(1);
  return;
}


// ===== ovl_0c39 @ 1ca8:0c39

void ovl_0c39(void)

{
  int in_AX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap(*(undefined2 *)(in_AX * 2 + &G_heroptr));
  EXE_AddScrap(G_comtxtptr);
  return;
}


