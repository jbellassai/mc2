// ===== ovl_02e0 @ 1ca8:02e0

void ovl_02e0(void)

{
  undefined2 unaff_DS;
  code *in_stack_00000000;
  
  *(undefined2 *)(*piRam000004fc + -0x728a) = piRam000004fc;
                    /* WARNING: Could not recover jumptable at 0x0001cd82. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*in_stack_00000000)();
  return;
}


// ===== ovl_0308 @ 1ca8:0308

void ovl_0308(void)

{
  undefined2 uVar1;
  int in_BX;
  int iVar2;
  int unaff_BP;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  ovl_02e0();
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  LOCK();
  iVar2 = *(int *)(unaff_BP + 6);
  *(int *)(unaff_BP + 6) = in_BX;
  UNLOCK();
  iVar2 = iVar2 * 2;
  if (*(int *)(iVar2 + &G_party) == 0x1a) {
    iVar2 = *(int *)(unaff_BP + 6);
    G_othername = &OV_0x13f;
    G_othername+2 = 0x1ca8;
    EXE_AddScrap(&OV_0x13f,0x1ca8,0);
  }
  else {
    uVar1 = *(undefined2 *)(iVar2 + &G_heroptr);
    iVar2 = *(int *)(unaff_BP + 6);
    G_othername = uVar1;
    G_othername+2 = unaff_DS;
    EXE_AddScrap(uVar1);
  }
  EXE_AddScrap(G_comtxtptr);
  return;
}


// ===== ovl_037e @ 1ca8:037e

void ovl_037e(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_02e0();
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  ovl_039f();
  EXE_AddScrap(G_comtxtptr);
  return;
}


// ===== ovl_039f @ 1ca8:039f

void ovl_039f(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  undefined4 uVar1;
  
  ovl_03e4();
  if ((bool)in_CF) {
    uVar1 = EXE_AddScrap(&G_member0+1100 + (G_npcno & 0xff) * 0xdc);
  }
  else {
    uVar1 = EXE_AddScrap(G_loc+18);
  }
  G_othername = (int)uVar1;
  G_othername+2 = (int)((ulong)uVar1 >> 0x10);
  return;
}


// ===== ovl_03e4 @ 1ca8:03e4

void ovl_03e4(void)

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


// ===== ovl_0406 @ 1ca8:0406

void ovl_0406(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_02e0();
  EXE_SetTxtWnd(1);
  ovl_0419();
  EXE_AddScrap(G_comtxtptr);
  return;
}


// ===== ovl_0419 @ 1ca8:0419

void ovl_0419(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined4 uVar1;
  
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap(G_comtxtptr);
  G_npctyp = *(undefined1 *)(G_npcptr + 2);
  uVar1 = EXE_AddScrap(G_comtypptr);
  G_othername = (int)uVar1;
  G_othername+2 = (int)((ulong)uVar1 >> 0x10);
  return;
}


// ===== ovl_045d @ 1ca8:045d

void ovl_045d(void)

{
  int iVar1;
  int extraout_DX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  ovl_02e0();
  EXE_SetBit(&G_met,G_npcno);
  ovl_05af();
  ovl_0dd0();
  if (*(byte *)*(undefined2 *)(extraout_DX + 0x44) == 0xff) {
    if (G_loc+60 == 0xff) {
      EXE_UseMindstone();
      EXE_AddScrap(G_comtxtptr);
      EXE_AddScrap(G_comtxtptr);
      ovl_039f();
      EXE_AddScrap();
      EXE_PrtScrap();
      return;
    }
    G_TALKRSP = (uint)G_loc+60;
    ovl_039f();
  }
  else {
    G_TALKRSP = (uint)*(byte *)*(undefined2 *)(extraout_DX + 0x44);
    ovl_039f();
    LOCK();
    iVar1 = G_convbufptr;
    G_convbufptr = in_BX;
    UNLOCK();
    LOCK();
    in_BX = G_convbufptr;
    G_convbufptr = iVar1;
    UNLOCK();
  }
  EXE_SetTxtWnd();
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap();
  EXE_PrtScrap();
  return;
}


// ===== ovl_0546 @ 1ca8:0546

void ovl_0546(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  int extraout_DX;
  byte bVar3;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  ovl_02e0();
  ovl_0dd0();
  bVar3 = (byte)((uint)*(undefined2 *)*(undefined2 *)(extraout_DX + 0x44) >> 8);
  if (((char)*(undefined2 *)*(undefined2 *)(extraout_DX + 0x44) == -1) || (bVar3 == 0xff)) {
    if (G_loc+61 == 0xff) {
      EXE_Offer1();
      EXE_AddScrap(G_comtxtptr);
      EXE_PrtScrap();
      return;
    }
    G_TALKRSP = (uint)G_loc+61;
    ovl_039f();
    uVar2 = G_loc+10;
  }
  else {
    G_TALKRSP = (uint)bVar3;
    ovl_039f();
    LOCK();
    puVar1 = (undefined2 *)G_convbufptr;
    G_convbufptr = in_BX;
    UNLOCK();
    uVar2 = *puVar1;
    LOCK();
    in_BX = G_convbufptr;
    G_convbufptr = (int)puVar1;
    UNLOCK();
  }
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap(uVar2);
  EXE_PrtScrap();
  return;
}


// ===== ovl_05af @ 1ca8:05af

void ovl_05af(void)

{
  char *pcVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  char *pcVar3;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  iVar2 = 10;
  pcVar3 = (char *)&OV_0x116;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar1 = pcVar3;
    pcVar3 = pcVar3 + 1;
    in_ZF = (char)G_npcno == *pcVar1;
  } while (!(bool)in_ZF);
  if ((bool)in_ZF) {
    EXE_SetBit(&G_events,*(undefined1 *)((unaff_DI - iVar2) + 0x129));
  }
  return;
}


// ===== ovl_05e2 @ 1ca8:05e2

void ovl_05e2(void)

{
  char *pcVar1;
  undefined1 *puVar2;
  byte *pbVar3;
  undefined2 *puVar4;
  undefined2 *puVar5;
  undefined1 uVar6;
  byte bVar7;
  char cVar8;
  uint uVar9;
  int iVar10;
  char *in_BX;
  char *pcVar11;
  int unaff_SI;
  undefined2 *puVar12;
  int unaff_DI;
  undefined2 *puVar13;
  undefined2 uVar14;
  char *pcVar15;
  undefined2 unaff_DS;
  bool bVar16;
  
  pcVar15 = (char *)0x1ca8;
  ovl_02e0();
  G_TALKRSP = 0;
  bVar16 = G_npcno < 0xfa;
  if (bVar16) {
    ovl_0a95();
    if (bVar16) {
      return;
    }
    ovl_0dd0();
    goto L_0600;
  }
L_08a0:
  do {
    puVar13 = (undefined2 *)&G_GWRDMNU;
    puVar12 = (undefined2 *)&OV_0x12a;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      puVar5 = puVar13;
      puVar13 = puVar13 + 1;
      puVar4 = puVar12;
      puVar12 = puVar12 + 1;
      *puVar5 = *puVar4;
    }
    ovl_0ae9();
    do {
      uVar9 = (**(code **)(in_BX + 0x48))(pcVar15,&G_mnuparms);
      if (uVar9 == 0xffff) {
        return;
      }
      if (uVar9 == 0xfd) {
        (**(code **)(in_BX + 0x1b0))();
        in_BX = pcVar15;
        goto L_08a0;
      }
    } while ((uVar9 == 0xf) || (uVar9 == 0xff));
    if (uVar9 != 0) {
      if (uVar9 == 1) {
        (**(code **)(in_BX + 0x54))(pcVar15);
        (**(code **)(in_BX + 0x5c))();
        for (in_BX = (char *)&OV_0x148; cVar8 = (char)G_weather,
            *in_BX != cVar8; in_BX = in_BX + 2) {
          if (*in_BX == -1) goto L_09bb;
        }
        iVar10 = 0;
        do {
          iVar10 = iVar10 + 1;
          in_BX = in_BX + 2;
        } while (*in_BX == cVar8);
        puVar4 = (undefined2 *)(G_savebx + 0x134);
        EXE_RndCo(0x1000,iVar10,G_savebx);
        in_BX = (char *)G_savebx;
        ovl_0de7();
L_09bb:
        pcVar15 = (char *)0x1000;
      }
      else {
        if (2 < uVar9) {
          return;
        }
        (**(code **)(in_BX + 0x5c))();
        (**(code **)(in_BX + 0x34))(pcVar15);
        (**(code **)(in_BX + 0x40))();
        iVar10 = (**(code **)(in_BX + 0x188))(pcVar15,&G_otherword);
        (**(code **)(in_BX + 0x5c))(pcVar15);
        if (iVar10 == -1) {
          return;
        }
        uVar9 = (**(code **)(in_BX + 0x1c8))
                          (pcVar15,&G_otherword,G_loc+18);
        if (uVar9 != 0xffff) {
          G_mnusel = (char)uVar9;
          pcVar11 = (char *)G_loc+24;
          uVar14 = unaff_DS;
L_06bf:
          if ((char)uVar9 != *pcVar11) break;
          bVar7 = pcVar11[1];
          uVar9 = (uint)bVar7;
          G_TALKPTR = pcVar11 + 1;
          pcVar11 = (char *)G_savebx;
          if (bVar7 == 0xff) {
            return;
          }
          goto L_06fa;
        }
        ovl_0a08();
      }
      goto L_08a0;
    }
    cVar8 = ovl_0b0e();
    in_BX = (char *)G_savebx;
    if (cVar8 != -1) {
      G_TALKRSP = cVar8;
      pcVar11 = in_BX;
      goto L_0810;
    }
    ovl_0a08();
  } while( true );
  for (; *pcVar11 != -1; pcVar11 = pcVar11 + 1) {
    if (*pcVar11 == '\0') {
      pcVar11 = pcVar11 + 1;
      goto L_06bf;
    }
  }
  if (G_npcno != '\0') {
    in_BX = (char *)G_savebx;
    ovl_0a08();
    if (0xf9 < G_npcno) goto L_08a0;
    goto L_0600;
  }
L_06fa:
  while (G_npcno != '\0') {
    G_TALKRSP = (char)uVar9;
    do {
      while( true ) {
        G_TALKPTR = G_TALKPTR + 1;
        LOCK();
        pcVar1 = (char *)G_TALKPTR;
        G_TALKPTR = (int)pcVar11;
        UNLOCK();
        cVar8 = *pcVar1;
        LOCK();
        pcVar11 = (char *)G_TALKPTR;
        G_TALKPTR = (int)pcVar1;
        UNLOCK();
        if (cVar8 == '\0') goto L_0810;
        if (cVar8 == 'E') break;
        if (cVar8 == 'C') {
          G_TALKPTR = G_TALKPTR + 1;
          LOCK();
          pbVar3 = (byte *)G_TALKPTR;
          G_TALKPTR = (int)pcVar11;
          UNLOCK();
          bVar7 = *pbVar3;
          LOCK();
          pcVar11 = (char *)G_TALKPTR;
          G_TALKPTR = (int)pbVar3;
          UNLOCK();
          iVar10 = unaff_SI + G_convix;
          if (bVar7 <= *(byte *)(iVar10 + -0x7b4c)) {
            bVar7 = *(byte *)(iVar10 + -0x7b4c);
          }
          G_deftxtparms+2 = bVar7 - *(char *)(iVar10 + -0x7b4c);
          if ((byte)((char)*(undefined2 *)
                            (*(int *)(G_curpla * 2 + &G_heroptr) + 0x13) +
                    G_tailorcharm) < G_deftxtparms+2) {
            G_TALKPTR = G_TALKPTR + 1;
            LOCK();
            puVar2 = (undefined1 *)G_TALKPTR;
            G_TALKPTR = (int)pcVar11;
            UNLOCK();
            uVar6 = *puVar2;
            LOCK();
            pcVar11 = (char *)G_TALKPTR;
            G_TALKPTR = (int)puVar2;
            UNLOCK();
            G_TALKRSP = uVar6;
            G_SWCHARM = G_SWCHARM + '\x01';
            goto L_0810;
          }
          G_TALKPTR = G_TALKPTR + 1;
        }
        else if (cVar8 == 'S') {
          (**(code **)(pcVar11 + 0x288))();
          G_TALKPTR = G_TALKPTR + 1;
          LOCK();
          iVar10 = G_TALKPTR;
          G_TALKPTR = (int)pcVar11;
          UNLOCK();
          LOCK();
          G_TALKPTR = iVar10;
          UNLOCK();
          ovl_0c57();
          return;
        }
      }
      G_TALKPTR = G_TALKPTR + 1;
      LOCK();
      puVar2 = (undefined1 *)G_TALKPTR;
      G_TALKPTR = (int)pcVar11;
      UNLOCK();
      uVar6 = *puVar2;
      LOCK();
      pcVar11 = (char *)G_TALKPTR;
      G_TALKPTR = (int)puVar2;
      UNLOCK();
      G_TALKPTR = G_TALKPTR + 1;
      iVar10 = (**(code **)(pcVar11 + 0x11c))(pcVar15,&G_events,uVar6);
    } while (iVar10 != 0);
    LOCK();
    pbVar3 = (byte *)G_TALKPTR;
    G_TALKPTR = (int)pcVar11;
    UNLOCK();
    uVar9 = (uint)*pbVar3;
    LOCK();
    pcVar11 = (char *)G_TALKPTR;
    G_TALKPTR = (int)pbVar3;
    UNLOCK();
  }
  pcVar11 = (char *)G_savebx;
  (**(code **)(pcVar11 + 0x54))(pcVar15);
  (**(code **)(pcVar11 + 0x5c))();
  (**(code **)(pcVar11 + 0xe4))();
  (**(code **)(pcVar11 + 0xe8))(pcVar15,&OV_0x17f,pcVar15);
  goto L_0888;
L_0810:
  if (0xf9 < G_npcno) {
    (**(code **)(pcVar11 + 0x104))();
    (**(code **)(pcVar11 + 0xe8))(pcVar15,G_loc+10,unaff_DS);
    in_BX = (char *)0x2;
    (**(code **)(pcVar11 + 0xec))(pcVar15);
    goto L_08a0;
  }
  if (G_npccat == '\x01') {
    (**(code **)(pcVar11 + 0x1b4))(pcVar15);
  }
  else {
    (**(code **)(pcVar11 + 0x244))();
  }
  (**(code **)(pcVar11 + 0xe8))
            (pcVar15,*(undefined2 *)G_convbufptr,
             (int)((ulong)G_convbufptr >> 0x10));
  if (G_SWCHARM != '\0') {
    (**(code **)(pcVar11 + 0xe8))(pcVar15,G_comtxtptr,unaff_DS);
  }
L_0888:
  in_BX = (char *)0x1;
  (**(code **)(pcVar11 + 0xec))(pcVar15);
L_0600:
  ovl_0ae9();
  G_SWCHARM = 0;
  do {
    iVar10 = (**(code **)(in_BX + 0x48))(0x1000,&G_mnuparms);
    if (iVar10 == -1) {
      return;
    }
    if (iVar10 == 0xfd) {
      pcVar15 = in_BX + 0x1b0;
      in_BX = (char *)0x1000;
      (**(code **)pcVar15)();
      goto L_0600;
    }
  } while ((iVar10 == 0xf) || (iVar10 == 0xff));
  if (G_mnusel != '\x01') goto L_06b2;
  (**(code **)(in_BX + 0x5c))();
  (**(code **)(in_BX + 0x34))(0x1000);
  (**(code **)(in_BX + 0x40))();
  iVar10 = (**(code **)(in_BX + 0x188))(0x1000,&G_otherword);
  (**(code **)(in_BX + 0x5c))(0x1000);
  if (iVar10 == -1) {
    return;
  }
  iVar10 = (**(code **)(in_BX + 0x1c8))
                     (0x1000,&G_otherword,
                      *(undefined2 *)((int)G_convbufptr + 2));
  if (iVar10 == -1) {
    ovl_0a08();
    goto L_0600;
  }
  G_mnusel = (char)iVar10;
L_06b2:
  pcVar15 = (char *)0x1000;
  uVar14 = (undefined2)((ulong)OV_0x112 >> 0x10);
  pcVar11 = (char *)*(undefined2 *)((int)OV_0x112 + 4);
  uVar9 = (uint)G_mnusel;
  goto L_06bf;
}


// ===== ovl_09d9 @ 1ca8:09d9

void ovl_09d9(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_npccat == '\x01') {
    EXE_RoomPgm(G_npcptr);
    return;
  }
  if ((G_npccat == '\x03') || (G_npccat == '\x04')) {
    EXE_Offer1();
    return;
  }
  EXE_UseMindstone();
  return;
}


// ===== ovl_0a08 @ 1ca8:0a08

void ovl_0a08(void)

{
  undefined2 *puVar1;
  char cVar2;
  undefined2 uVar3;
  int in_BX;
  int unaff_SI;
  undefined2 uVar4;
  undefined2 unaff_DS;
  
  ovl_09d9();
  if (G_npcno < 0xf9) {
    uVar4 = (undefined2)((ulong)G_convbufptr >> 0x10);
    cVar2 = *(char *)((int)G_convbufptr + G_convix + 100)
    ;
    if (cVar2 != -1) {
      LOCK();
      puVar1 = (undefined2 *)G_convbufptr;
      G_convbufptr = in_BX;
      UNLOCK();
      uVar3 = *puVar1;
      LOCK();
      in_BX = G_convbufptr;
      G_convbufptr = (int)puVar1;
      UNLOCK();
      EXE_AddScrap(uVar3,uVar4,cVar2);
      goto L_0a51;
    }
  }
  EXE_AddScrap(G_comtxtptr);
L_0a51:
  EXE_PrtScrap(3);
  EXE_GameSound(0xe);
  return;
}


// ===== ovl_0a68 @ 1ca8:0a68

void ovl_0a68(void)

{
  char cVar1;
  undefined2 in_AX;
  int iVar2;
  char *in_DX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_ES;
  undefined2 unaff_DS;
  
  EXE_InitScrap();
  G_scrap = in_AX;
  G_scrap+2 = unaff_ES;
  iVar2 = 0;
  for (; cVar1 = *in_DX, *(char *)(iVar2 + &G_GWRDMNU) = cVar1, cVar1 != -1;
      in_DX = in_DX + 1) {
    iVar2 = iVar2 + 1;
  }
  return;
}


// ===== ovl_0a95 @ 1ca8:0a95

void ovl_0a95(void)

{
  char cVar1;
  undefined2 *puVar2;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if ((G_curpla != '\0') && (2 < G_curmpg)) {
    puVar2 = (undefined2 *)G_loc+26;
    while( true ) {
      cVar1 = (char)*puVar2;
      if (cVar1 == '\0') break;
      if (cVar1 == (char)G_npcno) {
        G_TALKRSP = (char)((uint)*puVar2 >> 8);
        EXE_Offer1();
        EXE_AddScrap(G_loc+10);
        EXE_PrtScrap(0xff,in_BX);
        return;
      }
      puVar2 = puVar2 + 1;
    }
  }
  return;
}


// ===== ovl_0ae9 @ 1ca8:0ae9

void ovl_0ae9(void)

{
  undefined2 uVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar1 = ovl_0a68();
  EXE_ScrMenu(uVar1,&G_GWRDMNU);
  EXE_InitCom(&OV_0x12f,0x1ca8,uVar1);
  return;
}


// ===== ovl_0b0e @ 1ca8:0b0e

undefined1 ovl_0b0e(void)

{
  char cVar1;
  undefined2 *puVar2;
  undefined1 uVar3;
  int iVar4;
  uint in_DX;
  uint uVar5;
  byte bVar6;
  char *in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  int iVar7;
  
  uVar5 = in_DX & 0xff;
  do {
    cVar1 = *in_BX;
    bVar6 = (byte)(uVar5 >> 8);
    if (cVar1 == -1) {
      if (bVar6 == 0) {
        uVar3 = 0xff;
      }
      else if (bVar6 < 2) {
        uVar3 = G_scrap;
      }
      else {
        LOCK();
        iVar7 = G_savebx;
        G_savebx = (int)in_BX;
        UNLOCK();
        puVar2 = (undefined2 *)(iVar7 + 0x134);
        iVar4 = EXE_RndCo(bVar6);
        LOCK();
        G_savebx = iVar7;
        UNLOCK();
        uVar3 = *(undefined1 *)(iVar4 + &G_scrap);
      }
      return uVar3;
    }
    if ((cVar1 == -2) || (cVar1 == G_npctyp)) {
      if ((char)uVar5 == 'E') {
        cVar1 = in_BX[1];
        if (cVar1 != -2) {
          LOCK();
          iVar7 = G_savebx;
          G_savebx = (int)in_BX;
          UNLOCK();
          iVar4 = EXE_FindBit(&G_events,cVar1);
          LOCK();
          in_BX = (char *)G_savebx;
          G_savebx = iVar7;
          UNLOCK();
          if (iVar4 == 0) goto L_0b63;
        }
      }
      else if (in_BX[1] != G_weather) goto L_0b63;
      *(char *)((uint)bVar6 + &G_scrap) = in_BX[2];
      uVar5 = CONCAT11(bVar6 + 1,(char)uVar5);
    }
L_0b63:
    in_BX = in_BX + 3;
  } while( true );
}


// ===== ovl_0c57 @ 1ca8:0c57

void ovl_0c57(void)

{
  byte in_AL;
  int iVar1;
  undefined2 uVar2;
  byte *pbVar3;
  int in_BX;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  uint uVar5;
  
  uVar5 = (uint)(in_AL >> 3);
  EXE_SetTxtObj(*(undefined1 *)((uint)(in_AL >> 3) + &OV_0xc96));
  ovl_039f(uVar5);
  uVar2 = G_deftxtparms+4;
  EXE_SetTxtSong(in_AL);
  G_deftxtparms+6 = G_deftxtparms+4;
  G_deftxtparms+8 = unaff_DS;
  G_deftxtparms+4 = uVar2;
  EXE_Offer1();
  EXE_AddScrap(*(undefined2 *)G_convbufptr,
             (int)((ulong)G_convbufptr >> 0x10),
             G_TALKRSP);
  EXE_AddScrap(&OV_0xc9a,0x1000,0);
  iVar1 = EXE_CntPar();
  G_psize = iVar1;
  uVar2 = 1;
  if (iVar1 != 1) {
    uVar2 = 3;
  }
  EXE_AddScrap(&OV_0xc9a,0x1000,uVar2);
  EXE_PrtScrap(1);
  EXE_PrtWrd(G_comtxtptr);
  EXE_CalUpd1();
  EXE_CalUpd1();
  EXE_CalUpd();
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  uVar2 = 2;
  if (G_psize != 1) {
    uVar2 = 4;
  }
  EXE_AddScrap(&OV_0xc9a,0x1000,uVar2);
  EXE_PrtScrap(1);
  EXE_PrtWrd(G_comtxtptr);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap(&OV_0xc9a,0x1000,5);
  EXE_PrtScrap(2);
  EXE_BreakPoint();
  pbVar3 = (byte *)(&G_member0+9 + in_BX);
  iVar1 = 6;
  iVar4 = 0;
  do {
    if (*(char *)(iVar4 + &G_party) != -1) {
      *pbVar3 = *pbVar3 | '\x01' << (in_AL & 7);
    }
    pbVar3 = pbVar3 + 0xdc;
    iVar4 = iVar4 + 2;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_0dd0 @ 1ca8:0dd0

void ovl_0dd0(void)

{
  undefined4 uVar1;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar1 = G_convbufptr;
  OV_0x112 = (int)uVar1 + G_convix * 2;
  OV_0x114 = (int)((ulong)uVar1 >> 0x10);
  return;
}


// ===== ovl_0de7 @ 1ca8:0de7

void ovl_0de7(void)

{
  undefined2 in_AX;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_InitScrap();
  EXE_AddScrap(&OV_0x17f,0x1ca8,in_AX);
  EXE_PrtScrap(0xff,in_BX);
  return;
}


