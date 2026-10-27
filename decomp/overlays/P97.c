// ===== ovl_01ba @ 1ca8:01ba

void __cdecl16near ovl_01ba(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 unaff_DS;
  
  iVar2 = iRam000004f8;
  uVar1 = *(undefined4 *)(*piRam000004fc + 0x5a80);
  *(undefined2 *)(iRam000004f8 + 0x2010) = (int)uVar1;
  *(undefined2 *)(iVar2 + 0x2012) = (int)((ulong)uVar1 >> 0x10);
  return;
}


// ===== ovl_01e1 @ 1ca8:01e1

void __cdecl16far ovl_01e1(void)

{
  undefined4 uVar1;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar1 = OV_0x110;
  G_txtptr = (int)uVar1;
  G_txtptr+2 = (int)((ulong)uVar1 >> 0x10);
  return;
}


// ===== ovl_01f2 @ 1ca8:01f2

void ovl_01f2(void)

{
  undefined4 uVar1;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_01ba();
  ovl_01fd();
  uVar1 = OV_0x110;
  G_txtptr = (int)uVar1;
  G_txtptr+2 = (int)((ulong)uVar1 >> 0x10);
  return;
}


// ===== ovl_01fd @ 1ca8:01fd

void ovl_01fd(void)

{
  undefined1 *puVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  int iVar4;
  undefined2 *puVar5;
  int in_BX;
  int unaff_SI;
  undefined2 *puVar6;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar7;
  
  G_txtptr = &OV_0x117;
  G_txtptr+2 = 0x1ca8;
  OV_0x116 = 1;
  bVar7 = false;
  if ((G_swass == '\0') && (ovl_02e8(), bVar7)) {
    return;
  }
  iVar4 = ovl_073e();
  OV_0x109 = iVar4;
  *(undefined2 *)(iVar4 * 2 + &G_party) = 0xff;
  ovl_063c();
  iVar4 = *(int *)(OV_0x109 * 2 + &G_heroptr);
  OV_0x10f = (char)*(undefined2 *)(iVar4 + 8);
  OV_0x10d = iVar4;
  ovl_06bc();
  if ((G_swass == '\0') || (G_swass == '\x03')) {
    EXE_ClearBit&G_npcsta;
  }
  if ((G_swass < 2) && (OV_0x116 == '\x01')) {
    ovl_075d();
    EXE_AddScrap(G_comtxtptr);
    EXE_PrtScrap();
  }
  ovl_0719();
  puVar5 = (undefined2 *)(&G_member6 + (uint)(byte)(OV_0x10f - 1) * 0xdc);
  puVar6 = (undefined2 *)OV_0x10d;
  *(undefined1 *)((int)puVar6 + 0xbf) = 0xff;
  for (iVar4 = 0x6e; iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar3 = puVar5;
    puVar5 = puVar5 + 1;
    puVar2 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar3 = *puVar2;
  }
  for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar3 = puVar5;
    puVar5 = (undefined2 *)((int)puVar5 + 1);
    puVar2 = puVar6;
    puVar6 = (undefined2 *)((int)puVar6 + 1);
    *(undefined1 *)puVar3 = *(undefined1 *)puVar2;
  }
  LOCK();
  puVar1 = (undefined1 *)OV_0x10d;
  OV_0x10d = in_BX;
  UNLOCK();
  *puVar1 = 0;
  LOCK();
  iVar4 = OV_0x10d;
  OV_0x10d = (int)puVar1;
  UNLOCK();
  if (G_swcomb == '\0') {
    EXE_RestorP();
  }
  EXE_PrtW3();
  EXE_SumStat();
  return;
}


// ===== ovl_02e8 @ 1ca8:02e8

void ovl_02e8(void)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  cVar1 = (char)G_npcno;
  if (cVar1 == '\x15') {
    OV_0x114 = 3;
  }
  else {
    if (cVar1 != '\x1d') {
      return;
    }
    if ((G_events & 0x20) != 0) {
      return;
    }
    if ((G_events & 0x10) == 0) {
      OV_0x114 = 4;
    }
    else {
      cVar1 = (char)G_locspec;
      if (((cVar1 == '\x03') || (cVar1 == '\x14')) || (cVar1 == '\x15')) {
        uVar2 = ovl_073e();
        OV_0x109 = uVar2;
        ovl_075d();
        EXE_AddScrap((int)G_txtptr,
                   (int)((ulong)G_txtptr >> 0x10),6);
        EXE_PrtScrap(2);
        EXE_IncObj(G_heroptr,7,3);
        G_events = G_events | 0x20;
        return;
      }
      OV_0x114 = 5;
    }
  }
  uVar2 = ovl_073e();
  OV_0x109 = uVar2;
  ovl_075d();
  EXE_AddScrap((int)G_txtptr,
             (int)((ulong)G_txtptr >> 0x10),
             OV_0x114);
  uVar2 = G_curpla;
  G_curpla = OV_0x109;
  EXE_AddScrap((int)G_txtptr,
             (int)((ulong)G_txtptr >> 0x10),2);
  G_curpla = uVar2;
  EXE_PrtScrap(3);
  iVar3 = EXE_SetYN();
  if (iVar3 == 0) {
    OV_0x116 = 0;
    return;
  }
  return;
}


// ===== ovl_03e9 @ 1ca8:03e9

void ovl_03e9(void)

{
  ovl_01ba();
  ovl_03f7();
  ovl_01e1();
  return;
}


// ===== ovl_03f7 @ 1ca8:03f7

void __cdecl16near ovl_03f7(void)

{
  int iVar1;
  undefined2 uVar2;
  undefined1 *puVar3;
  int in_BX;
  undefined2 *puVar4;
  int unaff_BP;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined1 uVar5;
  
  G_txtptr = &OV_0x117;
  G_txtptr+2 = 0x1ca8;
  iVar1 = *(int *)(unaff_BP + 6);
  OV_0x109 = iVar1;
  uVar5 = iVar1 < 0;
  uVar2 = *(undefined2 *)(iVar1 * 2 + &G_heroptr);
  OV_0x10d = uVar2;
  G_othername = uVar2;
  G_othername+2 = unaff_DS;
  ovl_0664();
  ovl_0569();
  if ((bool)uVar5) {
    ovl_063c();
    return;
  }
  *(uint *)(OV_0x109 * 2 + &G_party) =
       (uint)*(byte *)(OV_0x10d + 8);
  uVar2 = ovl_06ac();
  EXE_SetBit(&G_npcsta,uVar2);
  for (puVar4 = (undefined2 *)&G_npclocs;
      *(char *)(puVar4 + 2) != (char)G_npcno;
      puVar4 = (undefined2 *)((int)puVar4 + 5)) {
  }
  uVar2 = *puVar4;
  iVar1 = OV_0x109;
  *(undefined1 *)(iVar1 + &G_p1x) = (char)uVar2;
  *(undefined1 *)(iVar1 + &G_p1y) = (char)((uint)uVar2 >> 8);
  puVar3 = (undefined1 *)
           EXE_FindAss(G_npcno);
  if (puVar3 != (undefined1 *)0x0) {
    *puVar3 = 0xff;
    OV_0x10b = puVar3;
    EXE_IncObj(OV_0x10d,0,*(undefined2 *)(puVar3 + 0x11));
    ovl_0511();
  }
  ovl_0719();
  EXE_LoadFolks(0);
  if (G_curmpg == '\x02') {
    EXE_NewPXY();
  }
  ovl_075d();
  EXE_AddScrap(G_comtxtptr);
  EXE_PrtScrap(2);
  if (G_swcomb == '\0') {
    EXE_RestorP();
  }
  EXE_PrtW3();
  EXE_SumStat(in_BX);
  return;
}


// ===== ovl_0511 @ 1ca8:0511

void __cdecl16near ovl_0511(void)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  LOCK();
  iVar1 = OV_0x10b;
  OV_0x10b = in_BX;
  UNLOCK();
  bVar3 = *(byte *)(iVar1 + 5);
  uVar4 = *(undefined1 *)(iVar1 + 8);
  uVar5 = *(undefined1 *)(iVar1 + 0x13);
  uVar6 = *(undefined1 *)(iVar1 + 0x15);
  uVar7 = *(undefined1 *)(iVar1 + 0x14);
  LOCK();
  iVar2 = OV_0x10b;
  OV_0x10b = iVar1;
  UNLOCK();
  if ((bVar3 < 10) || (0x27 < bVar3)) {
    LOCK();
    iVar1 = OV_0x10d;
    OV_0x10d = iVar2;
    UNLOCK();
    *(undefined1 *)(iVar1 + 0xb9) = 0xff;
    LOCK();
    OV_0x10d = iVar1;
    UNLOCK();
    return;
  }
  LOCK();
  iVar1 = OV_0x10d;
  OV_0x10d = iVar2;
  UNLOCK();
  *(byte *)(iVar1 + 0xb9) = bVar3;
  *(undefined1 *)(iVar1 + 0xd7) = uVar4;
  *(undefined2 *)(iVar1 + 0xd8) = CONCAT11(uVar6,uVar5);
  *(undefined1 *)(iVar1 + 0xda) = (char)G_currm;
  *(undefined1 *)(iVar1 + 0xdb) = uVar7;
  LOCK();
  OV_0x10d = iVar1;
  UNLOCK();
  return;
}


// ===== ovl_0569 @ 1ca8:0569

void __cdecl16near ovl_0569(void)

{
  byte bVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  int iVar3;
  
  LOCK();
  iVar2 = OV_0x10d;
  OV_0x10d = in_BX;
  UNLOCK();
  bVar1 = *(byte *)(iVar2 + 0xb8);
  LOCK();
  iVar3 = OV_0x10d;
  OV_0x10d = iVar2;
  UNLOCK();
  if (1 < bVar1) {
    if (bVar1 < 3) {
      EXE_IModTxt(1);
      iVar2 = EXE_SetYN(iVar3);
      if (iVar2 != 0) {
        return;
      }
      ovl_0612();
    }
    else if ((G_events+8 & 2) == 0) {
      EXE_IModTxt(0,iVar3);
      return;
    }
  }
  return;
}


// ===== ovl_05af @ 1ca8:05af

void ovl_05af(void)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_01ba();
  G_swass = 3;
  iVar5 = 2;
  iVar4 = 5;
  do {
    OV_0x10d = *(undefined2 *)(iVar5 + &G_heroptr);
    if (*(int *)(iVar5 + &G_party) != 0xff) {
      LOCK();
      iVar1 = OV_0x10d;
      OV_0x10d = in_BX;
      UNLOCK();
      cVar2 = *(char *)(iVar1 + 0xd2);
      LOCK();
      in_BX = OV_0x10d;
      OV_0x10d = iVar1;
      UNLOCK();
      if (cVar2 == -1) {
        ovl_05f7();
      }
    }
    iVar5 = iVar5 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  uVar3 = OV_0x110;
  G_txtptr = (int)uVar3;
  G_txtptr+2 = (int)((ulong)uVar3 >> 0x10);
  return;
}


// ===== ovl_05f7 @ 1ca8:05f7

void ovl_05f7(void)

{
  undefined1 *puVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  byte bVar4;
  int iVar5;
  undefined2 *puVar6;
  int iVar7;
  int in_BX;
  undefined2 *puVar8;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar9;
  
  LOCK();
  iVar5 = OV_0x10d;
  OV_0x10d = in_BX;
  UNLOCK();
  *(undefined1 *)(iVar5 + 0xd2) = 5;
  bVar4 = *(byte *)(iVar5 + 8);
  LOCK();
  iVar7 = OV_0x10d;
  OV_0x10d = iVar5;
  UNLOCK();
  G_npcno = (uint)bVar4;
  G_txtptr = &OV_0x117;
  G_txtptr+2 = 0x1000;
  OV_0x116 = 1;
  bVar9 = false;
  if ((G_swass == '\0') && (ovl_02e8(), bVar9)) {
    return;
  }
  iVar5 = ovl_073e();
  OV_0x109 = iVar5;
  *(undefined2 *)(iVar5 * 2 + &G_party) = 0xff;
  ovl_063c();
  iVar5 = *(int *)(OV_0x109 * 2 + &G_heroptr);
  OV_0x10f = (char)*(undefined2 *)(iVar5 + 8);
  OV_0x10d = iVar5;
  ovl_06bc();
  if ((G_swass == '\0') || (G_swass == '\x03')) {
    EXE_ClearBit&G_npcsta;
  }
  if ((G_swass < 2) && (OV_0x116 == '\x01')) {
    ovl_075d();
    EXE_AddScrap(G_comtxtptr);
    EXE_PrtScrap();
  }
  ovl_0719();
  puVar6 = (undefined2 *)(&G_member6 + (uint)(byte)(OV_0x10f - 1) * 0xdc);
  puVar8 = (undefined2 *)OV_0x10d;
  *(undefined1 *)((int)puVar8 + 0xbf) = 0xff;
  for (iVar5 = 0x6e; iVar5 != 0; iVar5 = iVar5 + -1) {
    puVar3 = puVar6;
    puVar6 = puVar6 + 1;
    puVar2 = puVar8;
    puVar8 = puVar8 + 1;
    *puVar3 = *puVar2;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    puVar3 = puVar6;
    puVar6 = (undefined2 *)((int)puVar6 + 1);
    puVar2 = puVar8;
    puVar8 = (undefined2 *)((int)puVar8 + 1);
    *(undefined1 *)puVar3 = *(undefined1 *)puVar2;
  }
  LOCK();
  puVar1 = (undefined1 *)OV_0x10d;
  OV_0x10d = iVar7;
  UNLOCK();
  *puVar1 = 0;
  LOCK();
  iVar5 = OV_0x10d;
  OV_0x10d = (int)puVar1;
  UNLOCK();
  if (G_swcomb == '\0') {
    EXE_RestorP();
  }
  EXE_PrtW3();
  EXE_SumStat();
  return;
}


// ===== ovl_0612 @ 1ca8:0612

void __cdecl16near ovl_0612(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar3 = OV_0x10d;
  *(undefined2 *)(iVar3 + 0xce) = 0;
  *(undefined2 *)(iVar3 + 0xd0) = 0;
  iVar2 = 4;
  bVar1 = (char)*(undefined2 *)(unaff_SI + 4) + 0x1d;
  do {
    if (0x1e < bVar1) {
      bVar1 = bVar1 - 0x1e;
    }
    *(byte *)(iVar3 + 0xd3) = bVar1;
    bVar1 = bVar1 + 7;
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


// ===== ovl_063c @ 1ca8:063c

void __cdecl16near ovl_063c(void)

{
  char *pcVar1;
  char in_AL;
  int iVar2;
  int in_BX;
  int unaff_SI;
  char *pcVar3;
  undefined2 unaff_DS;
  
  pcVar3 = (char *)&G_formatn;
  iVar2 = 9;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar1 = pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (in_AL != *pcVar1);
  *(undefined1 *)((unaff_SI - iVar2) + 0x37) = 0xff;
  if (G_curmpg == 2) {
    EXE_PartyMusRegs(0x1ca8);
  }
  return;
}


// ===== ovl_0664 @ 1ca8:0664

void __cdecl16near ovl_0664(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined2 *puVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 *puVar5;
  undefined2 unaff_DS;
  
  puVar4 = (undefined2 *)
           (&G_member6 + (uint)(byte)((char)G_npcno - 1) * 0xdc);
  puVar5 = (undefined2 *)OV_0x10d;
  for (iVar3 = 0x6e; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar4;
    puVar4 = puVar4 + 1;
    *puVar2 = *puVar1;
  }
  for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar2 = puVar5;
    puVar5 = (undefined2 *)((int)puVar5 + 1);
    puVar1 = puVar4;
    puVar4 = (undefined2 *)((int)puVar4 + 1);
    *(undefined1 *)puVar2 = *(undefined1 *)puVar1;
  }
  return;
}


// ===== ovl_06ac @ 1ca8:06ac

undefined2 __cdecl16near ovl_06ac(void)

{
  char *pcVar1;
  char cVar2;
  undefined2 *puVar3;
  undefined2 in_AX;
  char *pcVar4;
  int iVar5;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar6;
  
  if ((char)in_AX == '\x1d') {
    G_events+4 = G_events+4 | 2;
  }
  bVar6 = (undefined2 *)(in_BX + 0xe0) == (undefined2 *)0x0;
  pcVar4 = (char *)&OV_0x78e;
  iVar5 = 0xf;
  do {
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
    bVar6 = (char)in_AX == *pcVar1;
  } while (!bVar6);
  if (bVar6) {
    puVar3 = (undefined2 *)(in_BX + 0xe0);
    EXE_viaptr_puVar3(0x1ca8,&G_events,pcVar4[0xe]);
  }
  G_events+11 = G_events+11 | 1;
  G_events+14 = G_events+14 | 0x20;
  iVar5 = 6;
  pcVar4 = (char *)G_heroptr;
  do {
    cVar2 = pcVar4[6];
    if (*pcVar4 != '\0') {
      if (cVar2 == '\x03') {
        G_events+11 = G_events+11 & 0xfe;
      }
      if (cVar2 == '\x04') {
        G_events+14 = G_events+14 & 0xdf;
      }
    }
    pcVar4 = pcVar4 + 0xdc;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return in_AX;
}


// ===== ovl_06bc @ 1ca8:06bc

undefined2 ovl_06bc(void)

{
  char *pcVar1;
  char cVar2;
  undefined2 *puVar3;
  undefined2 in_AX;
  char *pcVar4;
  int iVar5;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar6;
  
  bVar6 = (undefined2 *)(in_BX + 0x1bc) == (undefined2 *)0x0;
  pcVar4 = (char *)&OV_0x78e;
  iVar5 = 0xf;
  do {
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
    bVar6 = (char)in_AX == *pcVar1;
  } while (!bVar6);
  if (bVar6) {
    puVar3 = (undefined2 *)(in_BX + 0x1bc);
    EXE_viaptr_puVar3(0x1ca8,&G_events,pcVar4[0xe]);
  }
  G_events+11 = G_events+11 | 1;
  G_events+14 = G_events+14 | 0x20;
  iVar5 = 6;
  pcVar4 = (char *)G_heroptr;
  do {
    cVar2 = pcVar4[6];
    if (*pcVar4 != '\0') {
      if (cVar2 == '\x03') {
        G_events+11 = G_events+11 & 0xfe;
      }
      if (cVar2 == '\x04') {
        G_events+14 = G_events+14 & 0xdf;
      }
    }
    pcVar4 = pcVar4 + 0xdc;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return in_AX;
}


// ===== ovl_0719 @ 1ca8:0719

void __cdecl16near ovl_0719(void)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar1 = 0;
  iVar2 = 6;
  pcVar3 = (char *)G_heroptr;
  do {
    if (*pcVar3 != '\0') {
      uVar1 = CONCAT11((char)(uVar1 >> 8) + CARRY1((byte)uVar1,pcVar3[0x27]),
                       (byte)uVar1 + pcVar3[0x27]);
    }
    pcVar3 = pcVar3 + 0xdc;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  G_tailorcharm = (char)(uVar1 >> 5);
  return;
}


// ===== ovl_073e @ 1ca8:073e

int ovl_073e(void)

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


// ===== ovl_075d @ 1ca8:075d

void __cdecl16near ovl_075d(void)

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


