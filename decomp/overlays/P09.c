// ===== ovl_01e1 @ 1ca8:01e1

int ovl_01e1(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  iVar1 = iRam000004f8 + -0x100;
  *(undefined2 *)(*piRam000004fc + -0x728a) = piRam000004fc;
  return iVar1;
}


// ===== ovl_0202 @ 1ca8:0202

void ovl_0202(void)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  byte *pbVar3;
  char *pcVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 *puVar7;
  undefined4 uVar8;
  char cVar9;
  byte bVar10;
  undefined1 uVar11;
  uint uVar12;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined2 *puVar13;
  int iVar14;
  undefined2 extraout_DX;
  undefined2 extraout_DX_00;
  undefined2 extraout_DX_01;
  undefined2 extraout_DX_02;
  undefined1 uVar15;
  undefined2 extraout_DX_03;
  char cVar16;
  int in_BX;
  int iVar17;
  int *piVar18;
  byte bVar20;
  char *pcVar19;
  int unaff_SI;
  int unaff_DI;
  byte *pbVar21;
  int iVar22;
  int unaff_DS;
  undefined1 uVar23;
  bool bVar24;
  int iStack0006;
  int in_stack_0000000a;
  int in_stack_0000000e;
  int iStack0018;
  int in_stack_0000001a;
  int in_stack_0000001c;
  
  ovl_01e1();
  G_curbfl = 0xff;
  G_winxy = 0;
  G_curseg = 0;
  OV_0x158 = 0;
  OV_0x159 = 0;
  OV_0x155 = 0;
  OV_0x157 = 0;
  G_txtptr = &OV_0x1fb;
  G_txtptr+2 = 0x1000;
  iVar14 = 4;
  iVar17 = 0;
  do {
    *(undefined2 *)(iVar17 + &OV_0x103) = *(undefined2 *)(iVar17 + &G_rmdata);
    iVar17 = iVar17 + 2;
    iVar14 = iVar14 + -1;
  } while (iVar14 != 0);
  iVar14 = 0;
  bVar10 = OV_0x103;
  while (*(byte *)(iVar14 + &OV_0x166) <= bVar10) {
    iVar14 = iVar14 + 1;
  }
  G_rmtyp = (char)iVar14;
  if ((char)iVar14 == '\r') {
    OV_0x158 = 1;
  }
  G_swgreet = *(undefined1 *)(iVar14 + &OV_0x16f);
  OV_0x181 = bVar10 - *(char *)(iVar14 + &OV_0x165);
  OV_0x183 =
       *(undefined1 *)(G_loc+8 + OV_0x181 + 1);
  ovl_1790();
  ovl_16cd();
  G_loc+16 = extraout_DX;
  ovl_16cd();
  G_loc+2 = extraout_DX_00;
  ovl_16cd();
  G_loc+4 = extraout_DX_01;
  EXE_InitMap();
  if ((G_rmtyp == '\f') || (G_rmtyp == '\r')) {
    ovl_17f3();
    ovl_1777();
  }
  ovl_1720();
  EXE_NewLoc();
  G_currm = (uint)OV_0x103;
  G_locspec = (uint)OV_0x10a;
  EXE_ProAss();
  EXE_FixMusRegs();
  if (G_rmtyp == '\x0e') {
    ovl_15ee();
  }
L_0310:
  iStack0018 = in_stack_0000000e;
  EXE_InitMap();
  ovl_1710();
  ovl_17e5();
L_031b:
  EXE_Menu();
  EXE_InitCom&OV_0x184;
L_0339:
  iVar17 = in_BX;
  ovl_16f9();
  G_lookprt = 0;
  G_lookdata = 0xff;
  in_BX = 0;
  iVar14 = EXE_Parser();
  if (G_restarting != 0) {
    G_swgreet = 0;
    return;
  }
  if (iVar14 == 0xfd) goto L_0310;
  if (iVar14 == 0xfe) goto L_031b;
  if (iVar14 == 6) {
    EXE_CalUpd();
    goto L_0339;
  }
  if (iVar14 == 5) {
    EXE_LoadOvly(0x1000,0x5d);
    EXE_RoomPgm();
    EXE_Reload91();
    goto L_0310;
  }
  if (G_swgreet == -2) {
    ovl_0611();
    G_swgreet = 2;
    goto L_0310;
  }
  if (G_swgreet == -3) {
    G_swgreet = 0;
    if (G_rmtyp == '\a') goto L_066f;
    goto L_0339;
  }
  if (G_used != -1) {
    LOCK();
    bVar10 = G_used;
    G_used = 0xff;
    UNLOCK();
    if (bVar10 == 0x40) goto L_0310;
    if (G_rmtyp == '\n') {
      pbVar21 = (byte *)&OV_0x14b;
      iVar14 = 5;
      bVar24 = true;
      do {
        if (iVar14 == 0) break;
        iVar14 = iVar14 + -1;
        pbVar3 = pbVar21;
        pbVar21 = pbVar21 + 1;
        bVar24 = bVar10 == *pbVar3;
      } while (!bVar24);
      if (bVar24) {
        G_used = 0xff;
        OV_0xade = (uint)bVar10;
        EXE_SetTxtObj();
        iVar14 = EXE_Mark(0x1000);
        if (iVar14 == -1) goto L_0310;
        G_lookdata = 0xff;
        uVar12 = G_lookdata+2;
        in_BX = 0;
        iVar14 = EXE_ChkRng(0x1000,uVar12 & 0xff,uVar12 >> 8,1);
        if (iVar14 == 0) goto L_0310;
        if (((char)(uVar12 >> 8) != '\x03') || (bVar10 = (char)uVar12 - 4, 2 < bVar10)) {
          EXE_SetTxtWnd(0x1000,1);
          EXE_ClrTxtWnd(0x1000);
          EXE_InitScrap(0x1000);
          EXE_AddScrap(0x1000,G_comtxtptr);
          in_BX = 0;
          EXE_PrtScrap();
          goto L_0310;
        }
        OV_0xae0 = bVar10;
        uVar5 = OV_0xade;
        LOCK();
        iVar14 = OV_0xae0;
        OV_0xae0 = 0;
        UNLOCK();
        *(undefined1 *)(iVar14 + &OV_0x155) = (char)uVar5;
        LOCK();
        iVar17 = OV_0xae0;
        OV_0xae0 = iVar14;
        UNLOCK();
        EXE_DecObj0();
        EXE_GameSound();
        pcVar19 = (char *)&OV_0x14b;
        iVar14 = 5;
        goto code_r0x0001d542;
      }
    }
    G_used = bVar10;
    EXE_NoUse();
    goto L_0339;
  }
  if (G_whspnum == -1) {
    if ((G_mnusel == '\x19') && (G_lookdata != -1)) {
      if ((G_rmtyp == '\f') &&
         (((cVar9 = G_lookdata, cVar9 == OV_0x13a ||
           (cVar9 == OV_0x13b)) || (cVar9 == OV_0x13c)))) {
        ovl_1413();
        goto L_04d3;
      }
      bVar24 = G_rmtyp == '\f';
      if ((!bVar24) && (bVar24 = G_rmtyp == '\r', !bVar24))
      goto L_04d3;
      pcVar19 = (char *)&OV_0x13d;
      iVar14 = 8;
      goto code_r0x0001cf47;
    }
    if (G_curmen == '\x05') {
      iVar14 = EXE_RMove();
      if (iVar14 == 2) {
        OV_0x17f = G_loc+16;
L_0579:
        EXE_SetTxtWnd(0x1000,1);
        EXE_ClrTxtWnd(0x1000);
        EXE_InitScrap(0x1000);
        EXE_AddScrap(0x1000,G_comtxtptr);
        EXE_PrtScrap();
        in_BX = iVar17;
L_05af:
        puVar13 = (undefined2 *)(in_BX + 0x108);
        in_BX = 0x1000;
        iVar14 = EXE_viaptr_puVar13();
        if (iVar14 == 0) {
          uVar5 = *(undefined2 *)
                   ((uint)*(byte *)(OV_0x17f + 2) * 4 +
                   G_loc+14);
          bVar10 = (byte)uVar5;
          G_curmpg = bVar10;
          if (bVar10 < 3) {
            G_currm = 0xff;
          }
          G_curtils = (char)((uint)uVar5 >> 8);
          uVar11 = *(undefined1 *)(OV_0x17f + 5);
          G_pwinxy = *(undefined2 *)(OV_0x17f + 3);
          G_curvar = uVar11;
          if (G_curmpg == '\x01') {
            G_curvar = 0xff;
          }
          G_swgreet = 0;
          G_lookprt = 1;
          return;
        }
        goto L_031b;
      }
      if (iVar14 == 1) {
        for (piVar18 = (int *)G_loc+16; (char)*piVar18 != -1;
            piVar18 = piVar18 + 3) {
          if (G_zp_1415 == *piVar18) {
            if (OV_0x159 == '\x01') {
              ovl_167e();
              EXE_PrtScrap();
              goto L_0339;
            }
            OV_0x17f = piVar18;
            if (OV_0x159 != '\x02') goto L_0579;
            ovl_15c9();
            goto L_05af;
          }
        }
        EXE_GameSound();
      }
      else if ((iVar14 == 0) && (G_swtext != '\0')) {
        EXE_ClrTxtWnd();
        G_swtext = 0;
      }
    }
    goto L_0339;
  }
  if (((G_whspnum != -2) && (0xc < G_rmtyp)) &&
     (G_rmtyp < 0xf)) {
    if (G_rmtyp < 0xe) {
      iVar14 = OV_0x181;
      if ((byte)iVar14 == G_whspnum) {
        iVar17 = 1 << ((byte)iVar14 & 0x1f);
        OV_0x15c = (byte)iVar17;
        iVar22 = unaff_DI + iVar14;
        unaff_DI = iVar22 - iVar14;
        iVar14 = CONCAT11((char)((uint)iVar14 >> 8),*(undefined1 *)(iVar22 + 0xd86));
        pcVar19 = (char *)&G_member0;
        do {
          if ((*pcVar19 != '\0') && ((byte)(pcVar19[0xaa] & (byte)iVar17) == 0)) {
            iVar17 = (uint)(byte)((char)((uint)iVar17 >> 8) + 1) << 8;
            break;
          }
          pcVar19 = pcVar19 + 0xdc;
          iVar14 = iVar14 + -1;
        } while (iVar14 != 0);
        if ((char)((uint)iVar17 >> 8) != '\0') {
          G_whspnum = 0xff;
          EXE_GameSound();
          EXE_ChangeMap(0x1000,CONCAT11(extraout_AH,OV_0x145),&OV_0x148
                    );
          ovl_17e5();
          EXE_SetTxtWnd();
          EXE_InitScrap();
          EXE_ClrTxtWnd();
          LOCK();
          iVar14 = G_loc+6;
          G_loc+6 = in_BX;
          UNLOCK();
          LOCK();
          iVar17 = G_loc+6;
          G_loc+6 = iVar14;
          UNLOCK();
          ovl_1695();
          ovl_1695();
          ovl_1695();
          EXE_PrtScrap();
          EXE_PrtWrd();
          in_BX = CONCAT11(extraout_AH_00,OV_0x148);
          EXE_ChangeMap();
          LOCK();
          iVar14 = G_loc+6;
          G_loc+6 = iVar17;
          UNLOCK();
          LOCK();
          iVar17 = G_loc+6;
          G_loc+6 = iVar14;
          UNLOCK();
          in_stack_0000000a = -0x2804;
          ovl_17d4();
          *(undefined1 *)(iVar17 + &G_mapyl+1) = (char)extraout_DX_02;
          LOCK();
          puVar1 = (undefined1 *)(iVar17 + &G_secwin);
          uVar11 = *puVar1;
          *puVar1 = (char)extraout_DX_02;
          uVar15 = (undefined1)((uint)extraout_DX_02 >> 8);
          UNLOCK();
          bVar10 = (byte)iVar17;
          bVar24 = CARRY1(bVar10,G_thismap);
          bVar20 = (byte)((uint)iVar17 >> 8);
          uVar23 = CARRY1(bVar20,bVar24);
          iVar14 = CONCAT11(bVar20 + bVar24,bVar10 + G_thismap);
          *(undefined1 *)(iVar14 + &G_mapyl+1) = uVar15;
          LOCK();
          puVar1 = (undefined1 *)(iVar14 + &G_secwin);
          uVar2 = *puVar1;
          *puVar1 = uVar15;
          UNLOCK();
          OV_0x15a = CONCAT11(uVar2,uVar11);
          in_stack_0000000e = -0x27e4;
          ovl_17e5();
          ovl_0f91();
          cVar9 = ovl_0fb8();
          if ((bool)uVar23) {
            if (OV_0x181 < 4) {
              ovl_1695();
              EXE_PrtScrap();
              EXE_PrtWrd();
              goto L_0f38;
            }
            ovl_1695();
            ovl_1695();
            EXE_PrtScrap();
            in_stack_0000000e = -0x277d;
            EXE_PrtWrd();
L_0e07:
            ovl_123e();
            ovl_167e();
            in_stack_0000001a = iStack0018;
          }
          else {
            if (cVar9 != '\0') {
              OV_0x15d = cVar9;
              if (cVar9 == G_curpla) {
                G_curpla = 0;
                EXE_PrtW3();
                EXE_SumStat();
              }
              uVar8 = G_othername;
              OV_0x1a7 = (int)uVar8;
              OV_0x1a9 = (int)((ulong)uVar8 >> 0x10);
              ovl_1695();
              ovl_1695();
              in_stack_0000001a = iStack0018;
              if (OV_0x181 == '\a') {
                ovl_1695();
                in_stack_0000001a = iStack0018;
              }
              ovl_1695();
              EXE_PrtScrap();
              iStack0018 = 0x1000;
              iVar14 = EXE_SetYN();
              if (iVar14 != 0) goto L_0e07;
              if (OV_0x15d == -1) {
                EXE_slot0x1168();
              }
              else {
                ovl_1290();
                in_stack_0000001c = iStack0018;
                ovl_17e5();
                in_stack_0000001a = 0x1000;
                iStack0018 = -0x26d1;
                EXE_SumStat();
              }
              ovl_0f91();
            }
            ovl_1695();
            EXE_PrtScrap();
            EXE_PrtWrd();
            FUN_1000_db88();
            iVar14 = iStack0018;
            if ((3 < OV_0x181) && (OV_0x181 != 6)) {
              uVar8 = OV_0x1a7;
              G_othername = (int)uVar8;
              G_othername+2 = (int)((ulong)uVar8 >> 0x10);
              ovl_0f91();
              ovl_1695();
              EXE_PrtScrap();
              EXE_PrtWrd();
              iVar14 = unaff_DS;
              in_stack_0000001a = iStack0018;
            }
            iStack0018 = iVar14;
            iVar14 = 6;
            bVar10 = OV_0x15c;
            pcVar19 = (char *)&G_member0;
            do {
              if (*pcVar19 != '\0') {
                pcVar19[0xaa] = pcVar19[0xaa] | bVar10;
              }
              pcVar19 = pcVar19 + 0xdc;
              iVar14 = iVar14 + -1;
            } while (iVar14 != 0);
L_0f38:
            in_stack_0000000e = 0x1000;
            EXE_ClrTxtWnd();
            EXE_InitScrap();
          }
          LOCK();
          iVar14 = G_loc+6;
          G_loc+6 = in_stack_0000001a;
          UNLOCK();
          LOCK();
          iVar17 = G_loc+6;
          G_loc+6 = iVar14;
          UNLOCK();
          ovl_17d4();
          *(undefined1 *)(iVar17 + &G_mapyl+1) = (char)extraout_DX_03;
          *(undefined1 *)(iVar17 + &G_secwin) = (char)extraout_DX_03;
          iVar14 = CONCAT11((char)((uint)iVar17 >> 8) +
                            CARRY1((byte)iVar17,G_thismap),
                            (byte)iVar17 + G_thismap);
          uVar11 = (undefined1)((uint)extraout_DX_03 >> 8);
          *(undefined1 *)(iVar14 + &G_mapyl+1) = uVar11;
          *(undefined1 *)(iVar14 + &G_secwin) = uVar11;
          ovl_1695();
          ovl_1695();
          in_stack_0000001a = -0x25fa;
          EXE_PrtScrap();
          puVar13 = (undefined2 *)(in_stack_0000001c + 0x88);
          in_stack_0000001c = -0x25f3;
          EXE_viaptr_puVar13();
          goto L_0310;
        }
      }
    }
    else if (((char)OV_0x181 == G_whspnum) &&
            (OV_0x159 != '\x02')) {
      EXE_SetBit(0x1000);
      OV_0x159 = 2;
      EXE_SetTxtParm(0x1000);
      ovl_167e();
      EXE_PrtScrap();
      EXE_GameSound();
      EXE_HideMouse();
      puVar13 = (undefined2 *)(OV_0x181 * 4 + G_loc+28);
      uVar5 = *puVar13;
      uVar6 = puVar13[1];
      G_scrap2 = (char)uVar5;
      G_scrap2+1 = 0;
      cVar16 = (char)((uint)uVar5 >> 8);
      G_scrap2+2 = cVar16;
      G_scrap2+3 = 0;
      G_scrap2+4 = (char)uVar6;
      G_scrap2+5 = 0;
      cVar9 = (char)((uint)uVar6 >> 8);
      G_scrap2+6 = cVar9;
      G_scrap2+7 = 0;
      uVar12 = (uint)(byte)(cVar9 - cVar16);
      do {
        EXE_ScrlUD(G_scrap2,G_scrap2+2,
                   G_scrap2+4);
        EXE_delay();
        uVar12 = uVar12 - 1;
      } while (uVar12 != 0);
      EXE_CopyScreen();
      EXE_ShowMouse();
      ovl_1612();
      G_whspnum = 0xff;
      goto L_0310;
    }
  }
  EXE_SetTxtWnd(0x1000,1);
  EXE_ClrTxtWnd(0x1000);
  EXE_InitScrap(0x1000);
  EXE_AddScrap(0x1000,G_comtxtptr);
  EXE_PrtScrap();
  G_whspnum = 0xff;
  in_BX = 0;
  goto L_0339;
L_066f:
  iVar14 = *(int *)(G_curpla * 2 + &G_heroptr);
  iVar17 = *(int *)(iVar14 + 0xcc);
  OV_0x763 = iVar14;
  if (iVar17 == 0) {
    EXE_UseMindstone();
    ovl_1695();
    EXE_PrtScrap();
    EXE_SetTxtWnd();
    puVar13 = (undefined2 *)(in_BX + 0xe4);
    in_BX = 0x1000;
    EXE_viaptr_puVar13();
  }
  else {
    OV_0x765 = iVar17;
    OV_0x767 = iVar17;
    iVar14 = *(int *)((uint)OV_0x181 * 2 + &G_casino);
    if (iVar14 != 0) {
      OV_0x769 = iVar14;
      EXE_SetTxtToD();
      EXE_UseMindstone();
      ovl_1695();
      EXE_PrtScrap();
      iVar14 = EXE_SetYN();
      if (iVar14 == 0) {
        EXE_UseMindstone();
        ovl_1695();
        EXE_PrtScrap();
        EXE_PrtWrd();
        goto L_075e;
      }
      EXE_ClrTxtWnd();
      iStack0006 = in_BX;
      goto L_09cb;
    }
    EXE_UseMindstone();
    ovl_1695();
    EXE_PrtScrap();
    EXE_SetTxtWnd();
    puVar13 = (undefined2 *)(in_BX + 0xe4);
    in_BX = 0x1000;
    EXE_viaptr_puVar13();
  }
  goto L_031b;
  while( true ) {
    iVar14 = *(int *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0xcc);
    if (iVar14 == 0) {
      ovl_167e();
      EXE_PrtScrap();
      in_BX = G_comtxtptr;
      EXE_PrtWrd();
      break;
    }
    OV_0x765 = iVar14;
    ovl_167e();
    in_BX = -0x2c51;
    EXE_PrtScrap();
    in_stack_0000000a = -0x2c4a;
    iVar14 = EXE_SetYN();
    if (iVar14 != 0) break;
L_075e:
    EXE_ClrMnuWnd();
    EXE_ClrTxtWnd();
    EXE_InitScrap();
    iVar14 = OV_0x769;
    if (OV_0x765 < iVar14) {
      iVar14 = OV_0x765;
    }
    G_deftxtparms = iVar14;
    ovl_1695();
    EXE_PrtScrap();
    iVar14 = EXE_GetNum();
    in_BX = in_stack_0000000a;
    if (iVar14 == 0) break;
    OV_0x76b = iVar14;
    EXE_ClrTxtWnd();
    EXE_InitScrap();
    cVar9 = EXE_RndCo();
    OV_0x76d = cVar9 + '\x01';
    cVar9 = EXE_RndCo();
    bVar10 = cVar9 + '\x01' + OV_0x76d;
    OV_0x76d = bVar10;
    G_deftxtparms = (uint)bVar10;
    ovl_1695();
    EXE_GameSound();
    uVar11 = EXE_RndCo();
    OV_0x76e = uVar11;
    cVar9 = EXE_RndCo();
    bVar10 = cVar9 + OV_0x76e + 2;
    OV_0x76e = bVar10;
    G_deftxtparms = (uint)bVar10;
    ovl_1695();
    EXE_GameSound();
    if ((OV_0x76e == '\x02') ||
       (OV_0x76d < OV_0x76e)) {
      G_deftxtparms = OV_0x76b;
      ovl_1695();
      EXE_PrtScrap();
      EXE_IncObj();
      bVar10 = OV_0x181;
      iVar14 = OV_0x769 - OV_0x76b;
      OV_0x769 = iVar14;
      *(int *)((uint)bVar10 * 2 + &G_casino) = iVar14;
      in_stack_0000000e = in_stack_0000000a;
    }
    else {
      G_deftxtparms = OV_0x76b;
      ovl_1695();
      EXE_PrtScrap();
      EXE_DecObj();
      bVar10 = OV_0x181;
      iVar14 = OV_0x769 + OV_0x76b;
      OV_0x769 = iVar14;
      *(int *)((uint)bVar10 * 2 + &G_casino) = iVar14;
      in_stack_0000000e = in_stack_0000000a;
    }
    EXE_PrtWrd();
    if (iVar14 == 0) {
      ovl_167e();
      EXE_PrtScrap();
      in_BX = G_comtxtptr;
      EXE_PrtWrd();
      break;
    }
  }
  EXE_UseMindstone();
  EXE_SetTxtToD();
  ovl_1695();
  if (*(uint *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0xcc) <
      OV_0x767) {
    ovl_1695();
  }
  iStack0006 = 0x1000;
  EXE_PrtScrap();
  in_stack_0000000a = in_BX;
L_09cb:
  EXE_SetTxtWnd();
  in_BX = 0x1000;
  EXE_InitScrap();
  goto L_0310;
  while( true ) {
    iVar14 = iVar14 + -1;
    pcVar4 = pcVar19;
    pcVar19 = pcVar19 + 1;
    if ((char)OV_0xade == *pcVar4) break;
code_r0x0001d542:
    if (iVar14 == 0) break;
  }
  cVar9 = pcVar19[4];
  LOCK();
  iVar14 = OV_0xae0;
  OV_0xae0 = iVar17;
  UNLOCK();
  *(char *)(iVar14 + &G_mapyl+38) = cVar9;
  *(char *)(iVar14 + &G_secwin+37) = cVar9;
  LOCK();
  in_BX = OV_0xae0;
  OV_0xae0 = iVar14;
  UNLOCK();
  if (((OV_0x157 != '\0') && (OV_0x156 != '\0')) &&
     (OV_0x155 != '\0')) {
    ovl_17e5();
    iVar14 = OV_0x155;
    cVar9 = OV_0x157;
    LOCK();
    piVar18 = (int *)G_loc+26;
    G_loc+26 = in_BX;
    UNLOCK();
    for (; (char)*piVar18 != -1; piVar18 = (int *)((int)piVar18 + 0xd)) {
      if ((*piVar18 == iVar14) && ((char)piVar18[1] == cVar9)) {
        G_curlev = (uint)*(byte *)((int)piVar18 + 3);
        G_curseg = (uint)*(byte *)(piVar18 + 2);
        G_locspec = (uint)*(byte *)((int)piVar18 + 5);
        G_currm = (uint)*(byte *)(piVar18 + 3);
        G_curmpg = (uint)*(byte *)((int)piVar18 + 7);
        G_curtils = (uint)*(byte *)(piVar18 + 4);
        G_curvar = (uint)*(byte *)((int)piVar18 + 9);
        G_pwinxy = *(undefined2 *)(char *)((int)piVar18 + 0xb);
        LOCK();
        iVar14 = G_loc+26;
        G_loc+26 = (int)piVar18;
        UNLOCK();
        puVar7 = (undefined2 *)(iVar14 + 0x340);
        EXE_viaptr_puVar7();
        iVar14 = 9;
        iVar17 = 0;
        do {
          cVar9 = *(char *)(iVar17 + &G_formatn);
          if (cVar9 != -1) {
            iVar22 = CONCAT11((char)((uint)iVar17 >> 8),cVar9);
            uVar12 = CONCAT11(*(undefined1 *)(iVar22 + &G_p1y),
                              *(undefined1 *)(iVar22 + &G_p1x)) -
                     G_winxy;
            iVar22 = G_mfxcnt;
            *(uint *)(iVar22 + &G_mfxtnum) =
                 (uint)*(byte *)(&G_mapyl+1 +
                                (uVar12 >> 8) * (uint)G_thismap + (uVar12 & 0xff)
                                );
            *(undefined2 *)(iVar22 + &G_mfxcoords) =
                 CONCAT11((char)(uVar12 >> 8) * '\x10' + '\b',(char)uVar12 * '\x04' + '\x04');
            G_mfxcnt = G_mfxcnt + 2;
          }
          iVar17 = iVar17 + 1;
          iVar14 = iVar14 + -1;
        } while (iVar14 != 0);
        G_mfxcnt = 0;
        iVar14 = G_savebx;
        G_egadrawcode = 0;
        G_egaeffectstimer = 10000;
        G_egaeffectsflag = 6;
        G_egaeffectssound = 0;
        EXE_movetileFX();
        if (G_curmpg == 2) {
          G_mfxfadein = 6;
        }
        EXE_GameSound();
        EXE_Wait();
        return;
      }
    }
    LOCK();
    iVar14 = G_loc+26;
    G_loc+26 = (int)piVar18;
    UNLOCK();
    EXE_SetTxtWnd();
    EXE_ClrTxtWnd();
    EXE_InitScrap();
    EXE_AddScrap(G_comtxtptr);
    EXE_PrtScrap();
    in_BX = 0;
    EXE_PrtWrd();
    OV_0x155 = 0;
    OV_0x157 = 0;
    G_mapyl+38 = 0x7070;
    G_mapyl+40 = 0x70;
    G_secwin+37 = 0x7070;
    G_secwin+39 = 0x70;
  }
  goto L_0310;
  while( true ) {
    iVar14 = iVar14 + -1;
    pcVar4 = pcVar19;
    pcVar19 = pcVar19 + 1;
    bVar24 = G_lookdata+1 == *pcVar4;
    if (bVar24) break;
code_r0x0001cf47:
    if (iVar14 == 0) break;
  }
  if (bVar24) {
    ovl_14a0();
  }
L_04d3:
  EXE_PrtScrap();
  G_lookdata = 0xff;
  goto L_0310;
}


// ===== ovl_0611 @ 1ca8:0611

void ovl_0611(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_npcno != 'q') {
    return;
  }
  if ((G_events & 0x10) != 0) {
    EXE_GreetKNPC(0x1ca8);
    return;
  }
  if ((G_events+1 & 1) == 0) {
    EXE_IModTxt(0x1ca8,4);
    return;
  }
  EXE_IModTxt(0x1ca8,5);
  G_events = G_events | 0x10;
  EXE_SetBit(0x1ca8,&G_met,0x71,in_BX);
  return;
}


// ===== ovl_0f91 @ 1ca8:0f91

void ovl_0f91(void)

{
  int iVar1;
  int in_BX;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  LOCK();
  iVar1 = G_loc+6;
  G_loc+6 = in_BX;
  UNLOCK();
  LOCK();
  iVar2 = G_loc+6;
  G_loc+6 = iVar1;
  UNLOCK();
  ovl_167e();
  G_scrapptr = G_scrapptr + -1;
  EXE_AddScrap(0x1ca8,G_comtxtptr);
  return;
}


// ===== ovl_0fb8 @ 1ca8:0fb8

void ovl_0fb8(void)

{
  int unaff_DI;
  
                    /* WARNING: Could not recover jumptable at 0x0001da49. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(*(int *)(OV_0x181 * 2 + &OV_0x10cb) + unaff_DI))();
  return;
}


// ===== FUN_1000_db88 @ 1000:db88

void __cdecl16near FUN_1000_db88(void)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  char cVar5;
  int iVar4;
  int iVar6;
  byte bVar7;
  int in_BX;
  uint uVar8;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  uint local_6;
  uint *local_4;
  
  G_othername+2 = unaff_DS;
  local_6 = 0;
  iVar6 = 6;
  do {
    LOCK();
    UNLOCK();
    iVar4 = *(int *)(local_6 * 2 + &G_heroptr);
    uVar8 = local_6 & 0x7fff;
    LOCK();
    UNLOCK();
    if ((*(int *)(local_6 * 2 + &G_party) != 0xff) &&
       ((OV_0x15c & *(byte *)(iVar4 + 0xaa)) == 0)) {
      G_othername = iVar4;
      OV_0x161 = iVar4;
      local_4 = (uint *)G_loc+26;
      while( true ) {
        LOCK();
        UNLOCK();
        uVar3 = *local_4;
        LOCK();
        UNLOCK();
        bVar2 = (byte)uVar3;
        if (bVar2 == 0xff) break;
        bVar7 = (byte)OV_0x161;
        cVar1 = *(char *)CONCAT11((char)((uint)OV_0x161 >> 8) +
                                  CARRY1(bVar7,bVar2),bVar7 + bVar2);
        if (((uVar3 & 0x8000) == 0) ||
           (uVar3 = CONCAT11((char)(uVar3 >> 8) + -0x80,bVar2), cVar1 != '\0')) {
          cVar5 = (char)(uVar3 >> 8);
          G_deftxtparms+2 = cVar5;
          G_deftxtparms = (uint)(byte)(cVar1 + cVar5);
          EXE_SetTxtAttrib((uVar3 & 0xff) - 0xd);
          LOCK();
          UNLOCK();
          uVar3 = *local_4;
          LOCK();
          UNLOCK();
          if ((char)uVar3 == '\x10') {
            EXE_IncSta(uVar8,0xa6,(int)(char)(uVar3 >> 8) << 3,in_BX,uVar3);
          }
          iVar4 = EXE_IncSta(uVar8,uVar3 & 0xff,(byte)(uVar3 >> 8) & 0x7f);
          if (iVar4 != 0) {
            if (local_4 == (uint *)G_loc+26) {
              LOCK();
              UNLOCK();
              LOCK();
              UNLOCK();
              EXE_Spef1(*(undefined1 *)(uVar8 + &G_p1x),
                         *(undefined1 *)(uVar8 + &G_p1y));
            }
            ovl_167e();
            EXE_PrtScrap(0xff);
            EXE_PrtWrd(G_comtxtptr);
          }
        }
        local_4 = local_4 + 1;
      }
    }
    local_6 = uVar8 + 1;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  return;
}


// ===== ovl_123e @ 1ca8:123e

void ovl_123e(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar2 = 0;
  iVar3 = 6;
  do {
    G_zp_1415 =
         CONCAT11(*(undefined1 *)(iVar2 + &G_p1y),*(undefined1 *)(iVar2 + &G_p1x))
    ;
    iVar1 = *(int *)(iVar2 * 2 + &G_heroptr);
    if (*(int *)(iVar2 * 2 + &G_party) != 0xff) {
      *(undefined1 *)(iVar1 + 0xba) = 1;
      *(undefined1 *)(iVar1 + 0xca) = 1;
      EXE_Bang(0x1ca8,G_zp_1415 & 0xff,G_zp_1415 >> 8,0);
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


// ===== ovl_1290 @ 1ca8:1290

void ovl_1290(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 uVar3;
  undefined1 uVar4;
  int iVar5;
  undefined2 extraout_DX;
  int in_BX;
  int unaff_SI;
  undefined2 *puVar6;
  int unaff_DI;
  undefined2 *puVar7;
  undefined2 unaff_DS;
  undefined2 uVar8;
  
  uVar8 = *(undefined2 *)(OV_0x15d * 2 + &G_party);
  OV_0x15f = uVar8;
  G_scrap = (char)uVar8;
  EXE_FindAss(uVar8);
  OV_0x163 = extraout_DX;
  G_scrap+1 = (char)G_locspec;
  G_scrap+2 = (char)G_currm;
  G_scrap+3 = 0xffff;
  G_scrap+5 = 100;
  G_scrap+6 = 0xff;
  uVar8 = G_wildxy;
  G_scrap+7 = (char)uVar8;
  G_scrap+16 = (char)((uint)uVar8 >> 8);
  G_scrap+13 = uVar8;
  G_scrap+8 = 0;
  puVar6 = (undefined2 *)*(int *)(OV_0x15d * 2 + &G_heroptr);
  G_scrap+9 = (char)puVar6[3];
  uVar4 = EXE_FirsTil(OV_0x15d);
  G_scrap+10 = uVar4;
  G_scrap+11 = 0xff;
  *(byte *)(puVar6 + 0xb) = *(byte *)(puVar6 + 0xb) | 0x80;
  OV_0x1a1 = *puVar6;
  OV_0x1a3 = puVar6[1];
  OV_0x1a5 = *(undefined1 *)(puVar6 + 2);
  OV_0x1a7 = &OV_0x1a1;
  OV_0x1a9 = 0x1000;
  uVar4 = (undefined1)G_curreg;
  G_scrap+12 = uVar4;
  G_scrap+15 = uVar4;
  G_scrap+17 = 0;
  G_scrap+19 = (char)*(undefined2 *)(unaff_SI + 4);
  G_scrap+20 = 0xff;
  G_scrap+21 = (char)*(undefined2 *)(unaff_SI + 2);
  G_scrap+22 = G_scrap+1;
  G_scrap+24 = 0;
  puVar7 = (undefined2 *)OV_0x163;
  puVar6 = (undefined2 *)&G_scrap;
  for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
    puVar2 = puVar7;
    puVar7 = puVar7 + 1;
    puVar1 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar2 = *puVar1;
  }
  for (iVar5 = 1; iVar5 != 0; iVar5 = iVar5 + -1) {
    puVar2 = puVar7;
    puVar7 = (undefined2 *)((int)puVar7 + 1);
    puVar1 = puVar6;
    puVar6 = (undefined2 *)((int)puVar6 + 1);
    *(undefined1 *)puVar2 = *(undefined1 *)puVar1;
  }
  uVar8 = G_curpla;
  uVar3 = OV_0x15d;
  G_curpla = uVar3;
  iVar5 = EXE_SearchInv(0x40,uVar3,&OV_0x10e,0x1000);
  if (iVar5 != 0) {
    EXE_DecObj0(0x40,OV_0x10e);
  }
  G_curpla = uVar8;
  G_npcno = OV_0x15f;
  G_swass = 2;
  EXE_LoadOvly(0x61,&OV_0x2100,0x1000);
  EXE_RoomPgm();
  EXE_Reload91(in_BX);
  if (G_npcno == 0x1f) {
    G_events+12 = G_events+12 | 1;
  }
  return;
}


// ===== ovl_1413 @ 1ca8:1413

void ovl_1413(void)

{
  int iVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  G_txtptr = &OV_0x1fb;
  G_txtptr+2 = 0x1ca8;
  iVar1 = EXE_ChkRng(0x1ca8,G_lookdata+2 & 0xff,G_lookdata+2 >> 8,
                     1,0);
  if (iVar1 == 0) {
    EXE_SetTxtWnd(0x1ca8,1);
    EXE_ClrTxtWnd(0x1ca8);
    ovl_16bc();
    EXE_Advice(0x1ca8,(int)G_txtptr,
               (int)((ulong)G_txtptr >> 0x10),3,2,0x14);
    return;
  }
  EXE_SetTxtWnd(0x1ca8,1);
  EXE_ClrTxtWnd(0x1ca8);
  ovl_16bc();
  EXE_AddScrap(G_loc+18);
  return;
}


// ===== ovl_14a0 @ 1ca8:14a0

void ovl_14a0(void)

{
  char *pcVar1;
  int iVar2;
  char cVar3;
  undefined2 *puVar4;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_SetTxtParm(G_loc+10,OV_0x181);
  G_deftxtparms+6 = G_deftxtparms+4;
  G_deftxtparms+8 = unaff_DS;
  LOCK();
  pcVar1 = (char *)G_loc+6;
  G_loc+6 = in_BX;
  UNLOCK();
  cVar3 = *pcVar1;
  LOCK();
  iVar2 = G_loc+6;
  G_loc+6 = (int)pcVar1;
  UNLOCK();
  puVar4 = (undefined2 *)(iVar2 + 0x28c);
  EXE_viaptr_puVar4(0x1000,G_loc+10,(int)(char)(cVar3 + '\t'),iVar2);
  ovl_1695();
  ovl_1695();
  return;
}


// ===== ovl_15c9 @ 1ca8:15c9

void ovl_15c9(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_SetTxtParm(G_loc+10,OV_0x181);
  ovl_167e();
  EXE_PrtScrap(0xff,in_BX);
  return;
}


// ===== ovl_15ee @ 1ca8:15ee

int ovl_15ee(void)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 *puVar3;
  int iVar4;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x159 = 1;
  iVar2 = EXE_FindBit(&G_dnggates,OV_0x181);
  iVar4 = 0;
  if (iVar2 != 0) {
    OV_0x159 = 2;
    puVar3 = (undefined2 *)(OV_0x181 * 4 + G_loc+26);
    uVar1 = puVar3[1];
    G_scrap2 = *puVar3;
    G_scrap2+2 = uVar1;
    uVar1 = *(undefined2 *)(G_loc+16 + 0xc);
    G_scrap2+4 = *(undefined2 *)(G_loc+16 + 6);
    G_scrap2+6 = uVar1;
    iVar4 = (uint)G_scrap2+5 * 0xb;
    iVar4 = CONCAT11((char)((uint)iVar4 >> 8),(char)iVar4 + G_scrap2+4);
    *(undefined1 *)(iVar4 + &G_mapyl+1) = G_scrap2;
    *(undefined1 *)(iVar4 + &G_monstlist+1) = G_scrap2+1;
    iVar4 = (uint)G_scrap2+7 * 0xb;
    iVar4 = CONCAT11((char)((uint)iVar4 >> 8),(char)iVar4 + G_scrap2+6);
    *(undefined1 *)(iVar4 + &G_mapyl+1) = G_scrap2+2;
    *(undefined1 *)(iVar4 + &G_monstlist+1) = G_scrap2+3;
    iVar4 = in_BX;
  }
  return iVar4;
}


// ===== ovl_167e @ 1ca8:167e

void __cdecl16near ovl_167e(void)

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


// ===== ovl_16bc @ 1ca8:16bc

void ovl_16bc(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_AddScrap(0x1ca8,(int)G_txtptr,
             (int)((ulong)G_txtptr >> 0x10));
  return;
}


// ===== ovl_16cd @ 1ca8:16cd

void ovl_16cd(void)

{
  char *pcVar1;
  int iVar2;
  char *in_DX;
  int iVar3;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar3 = OV_0x181;
  if (OV_0x158 != '\0') {
    iVar3 = iVar3 + 8;
  }
  do {
    if (iVar3 == 0) {
      return;
    }
    iVar2 = -1;
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      pcVar1 = in_DX;
      in_DX = in_DX + 1;
    } while (*pcVar1 != -1);
    iVar3 = iVar3 + -1;
  } while( true );
}


// ===== ovl_16f9 @ 1ca8:16f9

void ovl_16f9(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (*(int *)(unaff_SI + 2) != OV_0x10b) {
    ovl_1710();
    EXE_InitMap();
    ovl_17e5();
  }
  return;
}


// ===== ovl_1710 @ 1ca8:1710

void ovl_1710(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_InitNPC(0x1ca8);
  OV_0x10b = *(undefined2 *)(unaff_SI + 2);
  return;
}


// ===== ovl_1720 @ 1ca8:1720

void ovl_1720(void)

{
  char *pcVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int unaff_SI;
  int unaff_DI;
  char *pcVar7;
  undefined2 unaff_DS;
  
  uVar2 = *(undefined1 *)((uint)G_rmtyp + &OV_0x10f);
  uVar3 = *(undefined1 *)((uint)G_rmtyp + &OV_0x118);
  iVar6 = 0;
  iVar4 = 6;
  do {
    if (*(int *)(iVar6 * 2 + &G_party) != 0xff) {
      pcVar7 = (char *)&G_formatn;
      iVar5 = 9;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar1 = pcVar7;
        pcVar7 = pcVar7 + 1;
      } while ((char)iVar6 != *pcVar1);
      iVar5 = CONCAT11(*(undefined1 *)((8 - iVar5) + &OV_0x131),
                       *(undefined1 *)((8 - iVar5) + &OV_0x128)) + CONCAT11(uVar3,uVar2);
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


// ===== ovl_1777 @ 1ca8:1777

void ovl_1777(void)

{
  undefined2 extraout_DX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  G_loc+6 = G_loc+6 + (uint)OV_0x181 * 5;
  ovl_16cd();
  G_loc+26 = extraout_DX;
  return;
}


// ===== ovl_1790 @ 1ca8:1790

void ovl_1790(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  byte bVar3;
  int iVar4;
  undefined1 in_DL;
  int in_BX;
  int unaff_SI;
  undefined2 *puVar5;
  int unaff_DI;
  undefined2 *puVar6;
  undefined2 unaff_DS;
  
  EXE_LoadMap(0x1ca8,in_DL,0,0x47);
  bVar3 = OV_0x183;
  if (OV_0x158 == '\x01') {
    bVar3 = bVar3 + 8;
  }
  if (bVar3 != 0) {
    puVar6 = (undefined2 *)&G_thismap;
    puVar5 = (undefined2 *)((int)puVar6 + (uint)bVar3 * 0x65);
    for (iVar4 = 0x32; iVar4 != 0; iVar4 = iVar4 + -1) {
      puVar2 = puVar6;
      puVar6 = puVar6 + 1;
      puVar1 = puVar5;
      puVar5 = puVar5 + 1;
      *puVar2 = *puVar1;
    }
    for (iVar4 = 1; iVar4 != 0; iVar4 = iVar4 + -1) {
      puVar2 = puVar6;
      puVar6 = (undefined2 *)((int)puVar6 + 1);
      puVar1 = puVar5;
      puVar5 = (undefined2 *)((int)puVar5 + 1);
      *(undefined1 *)puVar2 = *(undefined1 *)puVar1;
    }
  }
  return;
}


// ===== ovl_17d4 @ 1ca8:17d4

void ovl_17d4(void)

{
  return;
}


// ===== ovl_17e5 @ 1ca8:17e5

void ovl_17e5(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_FillWindow(0x1ca8,0,0);
  return;
}


// ===== ovl_17f3 @ 1ca8:17f3

void ovl_17f3(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  int in_BX;
  int unaff_SI;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined2 unaff_DS;
  
  EXE_InitScrap(0x1ca8);
  EXE_AddScrap(0x1ca8,G_loc+10);
  puVar5 = (undefined1 *)&G_loc+42;
  puVar4 = (undefined1 *)&G_scrap;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar4;
    puVar4 = puVar4 + 1;
    *puVar2 = *puVar1;
  }
  return;
}


