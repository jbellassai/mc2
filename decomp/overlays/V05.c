// ===== ovl_1895 @ 3200:1895

void ovl_1895(void)

{
  undefined1 *puVar1;
  char *pcVar2;
  undefined1 *puVar3;
  char cVar4;
  undefined2 in_AX;
  byte bVar5;
  int iVar6;
  int unaff_SI;
  undefined1 *puVar7;
  char *pcVar8;
  undefined1 *puVar9;
  undefined2 unaff_DS;
  bool bVar10;
  
  cVar4 = (char)((uint)in_AX >> 8);
  if (cVar4 == '\0') {
    pcVar8 = (char *)&G_scrap+4;
    iVar6 = 7;
    bVar5 = (byte)in_AX;
    cVar4 = 'S';
    do {
      bVar10 = (bool)(bVar5 & 1);
      bVar5 = bVar5 >> 1;
      if (bVar10) {
        pcVar2 = pcVar8;
        pcVar8 = pcVar8 + 1;
        *pcVar2 = cVar4;
      }
      cVar4 = cVar4 + '\x01';
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  else if (cVar4 == '\x01') {
    pcVar8 = (char *)&G_member6+1320;
    if (G_member6+1327 != '\0') {
      *(undefined1 *)(G_loc+4 + 0xd) = 1;
    }
    iVar6 = 6;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pcVar2 = pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (*pcVar2 != '\0');
    G_loc+18 = G_loc+18 + iVar6;
    puVar9 = (undefined1 *)G_loc+18;
    puVar7 = (undefined1 *)&G_member6+1320;
    for (iVar6 = 5 - iVar6; iVar6 != 0; iVar6 = iVar6 + -1) {
      puVar3 = puVar9;
      puVar9 = puVar9 + 1;
      puVar1 = puVar7;
      puVar7 = puVar7 + 1;
      *puVar3 = *puVar1;
    }
  }
  return;
}


// ===== INT60_00 @ 3200:18ce

int INT60_00(void)

{
  char *pcVar1;
  byte in_AL;
  char cVar2;
  int iVar3;
  int iVar4;
  int unaff_SI;
  char *pcVar5;
  undefined2 unaff_DS;
  bool bVar6;
  
  pcVar5 = (char *)&G_scrap+4;
  iVar3 = 7;
  iVar4 = 0;
  cVar2 = 'S';
  do {
    bVar6 = (bool)(in_AL & 1);
    in_AL = in_AL >> 1;
    if (bVar6) {
      iVar4 = iVar4 + 1;
      pcVar1 = pcVar5;
      pcVar5 = pcVar5 + 1;
      *pcVar1 = cVar2;
    }
    cVar2 = cVar2 + '\x01';
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return iVar4;
}


// ===== INT60_01 @ 3200:18eb

void INT60_01(void)

{
  undefined1 *puVar1;
  char *pcVar2;
  undefined1 *puVar3;
  int iVar4;
  int unaff_SI;
  undefined1 *puVar5;
  char *pcVar6;
  undefined1 *puVar7;
  undefined2 unaff_DS;
  
  pcVar6 = (char *)&G_member6+1320;
  if (G_member6+1327 != '\0') {
    *(undefined1 *)(G_loc+4 + 0xd) = 1;
  }
  iVar4 = 6;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    pcVar2 = pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (*pcVar2 != '\0');
  G_loc+18 = G_loc+18 + iVar4;
  puVar7 = (undefined1 *)G_loc+18;
  puVar5 = (undefined1 *)&G_member6+1320;
  for (iVar4 = 5 - iVar4; iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar3 = puVar7;
    puVar7 = puVar7 + 1;
    puVar1 = puVar5;
    puVar5 = puVar5 + 1;
    *puVar3 = *puVar1;
  }
  return;
}


