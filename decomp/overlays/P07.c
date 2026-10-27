// ===== ovl_0077 @ 1ca8:0077

int ovl_0077(void)

{
  return iRam000004f8 + -0x100;
}


// ===== ovl_0099 @ 1ca8:0099

void ovl_0099(uint param_1)

{
  uint uVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  byte bVar6;
  int iVar7;
  undefined2 uVar8;
  int iVar9;
  int *piVar10;
  undefined1 *puVar11;
  uint in_BX;
  int unaff_SI;
  undefined2 *puVar12;
  int unaff_DI;
  undefined2 *puVar13;
  undefined2 unaff_DS;
  bool bVar14;
  undefined4 uVar15;
  uint uVar16;
  
  ovl_0077();
  OV_0x8fc = 0;
  G_swgreet = 0;
  ovl_069e();
  if (G_p07flg == '\0') {
    G_winxy = 0;
    G_curseg = 0;
    G_npcptr = 0;
    EXE_LoadMap(5,0,0x47);
    bVar6 = G_hroomrec+4 & 0xf;
    if (bVar6 != 0) {
      puVar13 = (undefined2 *)&G_thismap;
      puVar12 = (undefined2 *)((int)puVar13 + (uint)bVar6 * 0x65);
      for (iVar9 = 0x32; iVar9 != 0; iVar9 = iVar9 + -1) {
        puVar3 = puVar13;
        puVar13 = puVar13 + 1;
        puVar2 = puVar12;
        puVar12 = puVar12 + 1;
        *puVar3 = *puVar2;
      }
      for (iVar9 = 1; iVar9 != 0; iVar9 = iVar9 + -1) {
        puVar3 = puVar13;
        puVar13 = (undefined2 *)((int)puVar13 + 1);
        puVar2 = puVar12;
        puVar12 = (undefined2 *)((int)puVar12 + 1);
        *(undefined1 *)puVar3 = *(undefined1 *)puVar2;
      }
    }
    EXE_InitMap();
    if (G_hroomrec+2 != 0) {
      if ((G_hroomrec+2 & 0x80) == 0) {
        EXE_Locate(1,1);
        LOCK();
        puVar11 = (undefined1 *)G_zp_0A;
        G_zp_0A = in_BX;
        UNLOCK();
        *puVar11 = 0x1f;
        LOCK();
        in_BX = G_zp_0A;
        G_zp_0A = (uint)puVar11;
        UNLOCK();
        G_secwin+12 = 0x1f;
      }
      else {
        EXE_Locate(9,0);
        LOCK();
        puVar11 = (undefined1 *)G_zp_0A;
        G_zp_0A = in_BX;
        UNLOCK();
        *puVar11 = 0x1c;
        puVar11[0xb] = 0xe;
        LOCK();
        in_BX = G_zp_0A;
        G_zp_0A = (uint)puVar11;
        UNLOCK();
        G_secwin+9 = 0x1c;
        G_secwin+20 = 0xe;
      }
    }
    iVar9 = 4;
    piVar10 = (int *)&G_hroomrec+11;
    do {
      if (*piVar10 != 0) {
        ovl_049a();
      }
      piVar10 = piVar10 + -1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    bVar6 = G_hroomtype;
    if (((1 < bVar6) && (bVar6 < 6)) &&
       (iVar7 = EXE_FindBit(&G_events,(char)bVar6 + 0x3c), iVar7 != 0)) {
      ovl_07c1();
    }
    OV_0x121 = 0;
    OV_0x123 =
         CONCAT11((char)((uint)iVar9 >> 8),G_rmdata+6 + -6);
    iVar9 = 6;
    do {
      if (*(int *)(OV_0x121 * 2 + &G_party) != 0xff) {
        puVar11 = (undefined1 *)
                  (&G_setupxy +
                  (OV_0x123 * 2 + OV_0x123) * 2 +
                  (OV_0x121 & 0x7fff));
        uVar4 = *puVar11;
        uVar5 = puVar11[0x18];
        LOCK();
        uVar1 = OV_0x121;
        OV_0x121 = in_BX;
        UNLOCK();
        *(undefined1 *)(uVar1 + &G_p1x) = 0xff;
        *(undefined1 *)(uVar1 + &G_p1y) = 0xff;
        LOCK();
        uVar16 = OV_0x121;
        OV_0x121 = uVar1;
        UNLOCK();
        uVar8 = EXE_PlacePerson(uVar4,uVar5);
        LOCK();
        uVar1 = OV_0x121;
        OV_0x121 = uVar16;
        UNLOCK();
        *(undefined1 *)(uVar1 + &G_p1x) = (char)uVar8;
        *(undefined1 *)(uVar1 + &G_p1y) = (char)((uint)uVar8 >> 8);
        LOCK();
        in_BX = OV_0x121;
        OV_0x121 = uVar1;
        UNLOCK();
      }
      OV_0x121 = OV_0x121 + 1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    EXE_FixMusRegs(in_BX);
  }
  else {
    G_curseg = 0;
    EXE_InitMap();
    ovl_04da();
    param_1 = in_BX;
    EXE_FixMusRegs();
    ovl_04e1();
    ovl_0572();
  }
L_00d3:
  EXE_InitMap();
  ovl_04da();
  ovl_04e1();
L_00de:
  do {
    EXE_Menu();
    EXE_InitCom(&OV_0x113,0x1000);
    do {
      while( true ) {
        do {
          while( true ) {
            while( true ) {
              G_lookprt = 0;
              G_lookdata = 0xff;
              OV_0x125 = 0xff;
              iVar9 = EXE_Parser&G_mnuparms;
              if (G_restarting != 0) goto L_0090;
              if (iVar9 == 0xfd) goto L_00d3;
              if (iVar9 == 0xfe) goto L_00de;
              if (iVar9 == 5) {
                EXE_LoadOvly(0x5d,&OV_0x2100);
                EXE_RoomPgm();
                EXE_Reload91();
                goto L_00d3;
              }
              if (G_swgreet == -2) {
                ovl_04ef();
                goto L_00d3;
              }
              if (G_used == -1) break;
              bVar6 = G_used;
              if (bVar6 == 0x40) {
                G_used = 0xff;
                goto L_00d3;
              }
              if ((((G_hroomtype < 2) || (5 < G_hroomtype)) ||
                  (bVar6 < 0x4c)) || (bVar14 = bVar6 < 0x4f, 0x4f < bVar6)) {
                bVar14 = bVar6 < 0x50;
                if ((bVar6 == 0x50) && (ovl_0969(), !bVar14)) {
                  G_used = 0xff;
                  goto L_00d3;
                }
              }
              else {
                ovl_06c2();
                if (!bVar14) {
                  G_used = 0xff;
                  goto L_00d3;
                }
              }
              EXE_NoUse();
            }
            if (G_whspnum == -1) break;
            EXE_SetTxtWnd(1);
            EXE_ClrTxtWnd();
            EXE_InitScrap();
            EXE_AddScrap(G_comtxtptr);
            EXE_PrtScrap();
            G_whspnum = 0xff;
          }
          if (G_mnusel == '\x19') {
            if ((G_lookdata == '\x1c') ||
               (G_lookdata == '\x0e')) {
              ovl_0d54();
              G_lookdata = 0xff;
              goto L_00d3;
            }
            if ((G_lookdata == '\x1f') && (OV_0x8fc != '\0'))
            {
              ovl_0969();
              G_lookdata = 0xff;
              goto L_00d3;
            }
            if (G_lookdata != -1) {
              EXE_PrtScrap();
              G_lookdata = 0xff;
              goto L_00d3;
            }
          }
        } while (G_curmen != '\x05');
        iVar9 = EXE_RMove();
        if (iVar9 != 1) break;
        uVar15 = EXE_ChkDoor(G_zp_1415 & 0xff);
        if ((int)uVar15 != 0) {
          LOCK();
          uVar1 = G_curpla;
          G_curpla = param_1;
          UNLOCK();
          *(uint *)(uVar1 * 2 + &G_exitdir) = (uint)((ulong)uVar15 >> 0x10) & 0xff;
          LOCK();
          param_1 = G_curpla;
          G_curpla = uVar1 & 0x7fff;
          UNLOCK();
          goto L_0278;
        }
        EXE_GameSound();
      }
    } while (iVar9 != 2);
L_0278:
    EXE_SetTxtWnd(1);
    EXE_ClrTxtWnd();
    EXE_InitScrap();
    EXE_AddScrap(G_comtxtptr);
    EXE_PrtScrap();
    iVar9 = EXE_SetYN();
    if (iVar9 == 0) {
      ovl_0634();
      G_lookprt = 1;
      G_pwinxy =
           *(undefined2 *)
            (*(int *)(G_curpla * 2 + &G_exitdir) * 2 + &G_hroomrec+5);
      EXE_ResLocD();
      EXE_ClrTxtWnd();
L_0090:
      G_p07flg = 0;
      return;
    }
  } while( true );
}


// ===== ovl_049a @ 1ca8:049a

void ovl_049a(void)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  int in_CX;
  uint uVar3;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar3 = (in_CX + -1) * 2;
  do {
    EXE_Locate(*(undefined1 *)(uVar3 + &OV_0x103),
               *(undefined1 *)(uVar3 + &OV_0x10b));
    uVar2 = *(undefined1 *)(G_tdata+8 + uVar3);
    LOCK();
    puVar1 = (undefined1 *)G_zp_0A;
    G_zp_0A = in_BX;
    UNLOCK();
    *puVar1 = uVar2;
    LOCK();
    in_BX = G_zp_0A;
    G_zp_0A = (int)puVar1;
    UNLOCK();
    uVar3 = uVar3 + 1;
  } while ((uVar3 & 1) != 0);
  return;
}


// ===== ovl_04da @ 1ca8:04da

void ovl_04da(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_InitNPC();
  return;
}


// ===== ovl_04e1 @ 1ca8:04e1

void ovl_04e1(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_FillWindow(0,0);
  return;
}


// ===== ovl_04ef @ 1ca8:04ef

void ovl_04ef(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_swgreet = 2;
  EXE_Offer1();
  EXE_AddScrap(G_loc+10);
  EXE_PrtScrap(1);
  EXE_SetBit(&G_met,G_npcno,in_BX);
  return;
}


// ===== ovl_0572 @ 1ca8:0572

void ovl_0572(void)

{
  char *pcVar1;
  int iVar2;
  undefined2 uVar3;
  int iVar4;
  byte *pbVar5;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  char *pcVar6;
  undefined2 unaff_DS;
  bool bVar7;
  undefined1 uStack0000;
  
  if (G_hroomtype != '\x01') {
    return;
  }
  pbVar5 = (byte *)&G_assgn0;
  iVar4 = 0x1f;
  do {
    iVar2 = EXE_AssignedHere(pbVar5);
    if ((iVar2 != 0) && (pbVar5[5] == 0x65)) {
      pbVar5[5] = 0xff;
      G_npcno = (uint)*pbVar5;
      uVar3 = EXE_PlacePerson(2,4);
      bVar7 = &uStack0000 == (undefined1 *)0x6;
      *(undefined2 *)(pbVar5 + 3) = uVar3;
      pcVar6 = (char *)&OV_0x66a;
      iVar2 = 4;
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        pcVar1 = pcVar6;
        pcVar6 = pcVar6 + 1;
        bVar7 = (char)uVar3 == *pcVar1;
      } while (!bVar7);
      if (bVar7) {
        EXE_SetBit(&G_events,pcVar6[3]);
      }
      EXE_SetTxtWnd(1);
      EXE_ClrTxtWnd();
      EXE_InitScrap();
      EXE_AddScrap(&OV_0x639,0x1ca8,0);
      EXE_PrtScrap(3);
    }
    pbVar5 = pbVar5 + 0x19;
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
      return;
    }
  } while( true );
}


// ===== ovl_0634 @ 1ca8:0634

void ovl_0634(void)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined1 *extraout_DX;
  undefined1 *puVar4;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_hroomtype != '\x01') {
    return;
  }
  puVar4 = (undefined1 *)&G_assgn0;
  iVar3 = 0x1f;
  do {
    iVar2 = EXE_AssignedHere(puVar4);
    if ((iVar2 != 0) && (puVar4[5] == -1)) {
      puVar4[0xb] = 0xff;
      LOCK();
      uVar1 = *puVar4;
      *puVar4 = 0xff;
      UNLOCK();
      EXE_ClearBit(&G_npcsta,uVar1);
      puVar4 = extraout_DX;
    }
    puVar4 = puVar4 + 0x19;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


// ===== ovl_069e @ 1ca8:069e

void ovl_069e(void)

{
  undefined2 *puVar1;
  byte bVar2;
  undefined2 uVar3;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  bVar2 = G_hroomtype;
  if (1 < bVar2) {
    if (bVar2 < 6) {
      G_loc+12 = G_loc+12 + (char)(bVar2 - 1) * 4;
      G_swgreet = 2;
      return;
    }
    if (bVar2 == 6) {
      if ((G_events+8 & 4) != 0) {
        G_loc+4 = G_loc+4 + 0x37;
        uVar3 = G_VANKRUHXY;
        LOCK();
        puVar1 = (undefined2 *)G_loc+4;
        G_loc+4 = in_BX;
        UNLOCK();
        *puVar1 = uVar3;
        LOCK();
        G_loc+4 = puVar1;
        UNLOCK();
        G_swgreet = 2;
      }
      return;
    }
  }
  return;
}


// ===== ovl_06c2 @ 1ca8:06c2

void ovl_06c2(void)

{
  char *pcVar1;
  undefined1 uVar2;
  byte in_AL;
  int iVar3;
  int iVar4;
  int in_BX;
  int iVar5;
  int unaff_SI;
  int unaff_DI;
  char *pcVar6;
  undefined2 unaff_DS;
  
  if ((byte)(G_hroomtype + 0x4aU) != in_AL) {
    return;
  }
  OV_0x7c0 = (uint)in_AL;
  EXE_SearchInv((uint)in_AL,G_curpla,&G_invinfobuf);
  if (G_invinfobuf+7 == '\0') {
    ovl_07c7();
  }
  else if ((char)*(undefined2 *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0x1a)
           == '\0') {
    ovl_07c7();
  }
  else {
    OV_0x125 = 2;
    ovl_07c7();
    EXE_GameSound(5);
    ovl_07c7();
    EXE_DecObj0(OV_0x7c0);
    ovl_07c1();
    LOCK();
    iVar4 = G_curpla;
    G_curpla = in_BX;
    UNLOCK();
    uVar2 = *(undefined1 *)(iVar4 + &G_p1x);
    LOCK();
    iVar5 = G_curpla;
    G_curpla = iVar4;
    UNLOCK();
    EXE_Bang(uVar2);
    pcVar6 = (char *)G_loc+18;
    for (iVar4 = OV_0x7c0 + -0x4c; iVar4 != 0; iVar4 = iVar4 + -1) {
      iVar3 = 0xff;
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar1 = pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (*pcVar1 != '\0');
    }
    G_othername = (int)pcVar6;
    G_othername+2 = unaff_DS;
    ovl_07c7();
    G_loc+4 =
         G_loc+4 + ((int)G_hroomtype - 1U & 0xff) * 0xb;
    EXE_SetBit();
  }
  return;
}


// ===== ovl_07c1 @ 1ca8:07c1

void ovl_07c1(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_mapyl+6 = 0x5d;
  return;
}


// ===== ovl_07c7 @ 1ca8:07c7

void ovl_07c7(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap(G_loc+10);
  EXE_PrtScrap(OV_0x125,in_BX);
  return;
}


// ===== ovl_0969 @ 1ca8:0969

void ovl_0969(void)

{
  undefined2 *puVar1;
  char cVar2;
  byte bVar3;
  uint uVar4;
  undefined2 uVar5;
  int iVar6;
  undefined2 extraout_DX;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 uVar7;
  undefined2 unaff_DS;
  
  uVar7 = 0x1ca8;
  G_txtptr = &OV_0x906;
  G_txtptr+2 = 0x1ca8;
  if (G_used == 'P') {
    EXE_SetTxtObj(0x50);
    iVar6 = EXE_Mark(&G_lookdata,0x2a);
    if (iVar6 == -1) {
      EXE_ClrTxtWnd(in_BX);
      return;
    }
    LOCK();
    cVar2 = G_lookdata;
    G_lookdata = -1;
    UNLOCK();
    if (cVar2 != '\x1f') {
      return;
    }
    iVar6 = EXE_ChkRng(G_lookdata+2 & 0xff,
                       G_lookdata+2 >> 8,1,1);
    if (iVar6 == 0) {
      return;
    }
    EXE_InitScrap();
    iVar6 = ovl_0f1a();
    if (iVar6 != 0) {
      EXE_AddScrap((int)G_txtptr,
                 (int)((ulong)G_txtptr >> 0x10),0);
      goto L_0c6e;
    }
    uVar7 = 0x1000;
    if (OV_0x8fc == '\0') {
      iVar6 = *(int *)(G_curpla * 2 + &G_heroptr);
      bVar3 = (*(byte *)(iVar6 + 0xf) >> 1) + (char)*(undefined2 *)(iVar6 + 0x21);
      if (0x62 < bVar3) {
        bVar3 = 99;
      }
      OV_0x8fd = bVar3;
      bVar3 = EXE_RndCo(100);
      if (OV_0x8fd <= bVar3) {
        EXE_SetTxtWnd(1,in_BX,0x90);
        EXE_ClrTxtWnd();
        EXE_InitScrap();
        EXE_AddScrap(G_comtxtptr);
        EXE_PrtScrap(0xff);
        EXE_GameSound(0x15);
        EXE_DecObj0(0x50,1);
        EXE_PrtWrd(G_comtxtptr);
        EXE_ClrTxtWnd();
        EXE_InitScrap();
      }
      EXE_GameSound(0x16);
      OV_0x8fc = 1;
      iVar6 = EXE_RndCo(4);
      if ((iVar6 == 0) &&
         (bVar3 = EXE_RndCo(0x78),
         OV_0x8fd < bVar3)) {
        EXE_AddScrap((int)G_txtptr,
                   (int)((ulong)G_txtptr >> 0x10),2);
        uVar4 = (uint)(G_hroomrec & 1);
        OV_0x902 = uVar4;
        EXE_AddScrap((int)G_txtptr,
                   (int)((ulong)G_txtptr >> 0x10),uVar4 + 3);
        EXE_PrtScrap(0xff);
        EXE_GameSound(OV_0x902 + 0x17);
        EXE_PrtWrd(G_comtxtptr);
        EXE_InitScrap();
        EXE_ClrTxtWnd();
        LOCK();
        iVar6 = OV_0x902;
        OV_0x902 = in_BX;
        UNLOCK();
        bVar3 = *(byte *)(iVar6 + &OV_0x904);
        LOCK();
        uVar7 = 0x1000;
        in_BX = OV_0x902;
        OV_0x902 = iVar6;
        UNLOCK();
        iVar6 = *(int *)(G_curpla * 2 + &G_heroptr);
        *(byte *)(iVar6 + 0xbd) = *(byte *)(iVar6 + 0xbd) | bVar3;
        *(byte *)(iVar6 + 0xba) = *(byte *)(iVar6 + 0xba) >> 1;
        *(byte *)(iVar6 + 0xca) = *(byte *)(iVar6 + 0xca) >> 1;
        EXE_SumStat();
        EXE_AddScrap((int)G_txtptr,
                   (int)((ulong)G_txtptr >> 0x10),5);
      }
      else {
        uVar7 = 0x1000;
        G_zp_0A = 10;
        iVar6 = EXE_SkillUp0();
        if (iVar6 != 0) {
          EXE_ClrTxtWnd();
          EXE_InitScrap();
        }
        EXE_AddScrap((int)G_txtptr,
                   (int)((ulong)G_txtptr >> 0x10),9);
      }
      goto L_0bd8;
    }
    puVar1 = (undefined2 *)(in_BX + 0xe8);
    in_BX = 0;
    EXE_AddScrap(0x1000,(int)G_txtptr,
                       (int)((ulong)G_txtptr >> 0x10));
  }
  iVar6 = EXE_ChkRng(uVar7,G_lookdata+2 & 0xff,G_lookdata+2 >> 8,1
                     ,0);
  if (iVar6 == 0) {
    EXE_Advice(uVar7,(int)G_txtptr,
               (int)((ulong)G_txtptr >> 0x10),8,7,0x14);
    EXE_PrtScrap(uVar7,0xff,in_BX);
    return;
  }
  iVar6 = ovl_0f1a();
  if (iVar6 == 0) {
L_0bd8:
    uVar4 = G_hroomrec+2;
    G_deftxtparms+2 = (char)(uVar4 >> 8);
    EXE_SetTxtObj(uVar7,uVar4 & 0xff);
    uVar5 = 6;
    if (G_deftxtparms+2 == '\x01') {
      uVar5 = 0xe;
    }
    EXE_AddScrap(uVar7,(int)G_txtptr,
               (int)((ulong)G_txtptr >> 0x10),uVar5);
    EXE_PrtScrap(uVar7,1);
    iVar6 = EXE_SetYN(uVar7);
    if (iVar6 == 0) {
      ovl_0f04();
      iVar6 = EXE_IncObj(uVar7,extraout_DX,G_hroomrec+2 & 0xff);
      if (iVar6 != 0) {
        if (G_hroomrec+2 == '\x1e') {
          G_events+11 = G_events+11 | 0x20;
        }
        OV_0x8fa =
             *(int *)(G_lootvalptr + (G_hroomrec+2 & 0xff) * 2) *
             (G_hroomrec+2 >> 8);
        ovl_0d1b();
        EXE_SetTxtWnd(1);
        EXE_ClrTxtWnd();
        EXE_InitScrap();
        EXE_AddScrap(G_comtxtptr);
        EXE_PrtScrap();
        ovl_0f2e();
        return;
      }
    }
    return;
  }
L_0c6e:
  EXE_AddScrap(uVar7,(int)G_txtptr,
             (int)((ulong)G_txtptr >> 0x10),1);
  EXE_PrtScrap(uVar7,0xff);
  return;
}


// ===== ovl_0d1b @ 1ca8:0d1b

void ovl_0d1b(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar4 = 0;
  iVar3 = 6;
  do {
    if ((*(int *)(iVar4 + &G_party) != 0xff) &&
       (iVar1 = *(int *)(iVar4 + &G_heroptr), *(char *)(iVar1 + 0xb8) == '\x02')) {
      uVar2 = OV_0x8fa + *(int *)(iVar1 + 0xce);
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


// ===== ovl_0d54 @ 1ca8:0d54

void ovl_0d54(void)

{
  byte bVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  char cVar4;
  int iVar5;
  byte bVar6;
  char cVar7;
  undefined2 extraout_DX;
  undefined2 uVar8;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar8 = 0x1ca8;
  G_txtptr = &OV_0x906;
  G_txtptr+2 = 0x1ca8;
  iVar5 = EXE_ChkRng(G_lookdata+2 & 0xff,G_lookdata+2 >> 8,
                     1,0);
  if (iVar5 == 0) {
    EXE_Advice((int)G_txtptr,
               (int)((ulong)G_txtptr >> 0x10),8,7,0x14);
    EXE_PrtScrap(0xff,in_BX);
    return;
  }
  iVar5 = ovl_0f1a();
  if (iVar5 == 0) {
    ovl_0f04();
    uVar8 = 0x1000;
    if (*(char *)(OV_0x900 + 0x1a) != '\0') {
      uVar2 = G_hroomrec+2;
      cVar4 = (char)uVar2 + -0x80;
      if (cVar4 != '*') {
        OV_0x8fe = cVar4;
        OV_0x8ff = (char)((uint)uVar2 >> 8);
        EXE_SetTxtSpell(cVar4);
        G_scrapptr = G_scrapptr + -1;
        EXE_AddScrap((int)G_txtptr,
                   (int)((ulong)G_txtptr >> 0x10),10);
        EXE_PrtScrap(2);
        EXE_PrtWrd(G_comtxtptr);
        EXE_IModTxt(0xb,0xff);
        iVar5 = EXE_SetYN();
        if (iVar5 != 0) {
          return;
        }
        EXE_GameSound(0x19);
        bVar1 = OV_0x8fe;
        iVar5 = OV_0x900;
        bVar6 = *(char *)(iVar5 + (uint)bVar1 + 0x7b) + OV_0x8ff;
        if (99 < bVar6) {
          cVar7 = bVar6 - OV_0x8ff;
          cVar4 = 'c' - cVar7;
          OV_0x8ff = cVar4;
          bVar6 = cVar7 + cVar4;
        }
        *(byte *)(iVar5 + (uint)bVar1 + 0x7b) = bVar6;
        ovl_0f2e();
        G_deftxtparms+2 = OV_0x8ff;
        EXE_SetTxtSpell();
        uVar8 = 0xc;
        goto L_0ef5;
      }
    }
  }
  uVar3 = G_txtptr;
  EXE_ScrapCOut(uVar8,0x20);
  EXE_AddScrap(uVar8,extraout_DX,(int)((ulong)uVar3 >> 0x10),0xb);
  EXE_PrtScrap(uVar8,0xff);
  iVar5 = EXE_SetYN(uVar8);
  if (iVar5 != 0) {
    return;
  }
  EXE_GameSound(uVar8,0x19);
  ovl_0f04();
  *(undefined1 *)(OV_0x900 + 0xba) = 99;
  EXE_IsHeTr();
  EXE_SumStat();
  uVar8 = 0xd;
L_0ef5:
  EXE_IModTxt(uVar8);
  return;
}


// ===== ovl_0f04 @ 1ca8:0f04

undefined2 ovl_0f04(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)*(undefined2 *)(G_curpla * 2 + &G_heroptr);
  uVar2 = *puVar1;
  OV_0x900 = puVar1;
  return uVar2;
}


// ===== ovl_0f1a @ 1ca8:0f1a

void ovl_0f1a(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_FindBit(&G_duntre,G_hroomrec);
  return;
}


// ===== ovl_0f2e @ 1ca8:0f2e

void ovl_0f2e(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SetBit(&G_duntre,G_hroomrec);
  return;
}


