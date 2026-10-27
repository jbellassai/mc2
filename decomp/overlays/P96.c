// ===== ovl_00c9 @ 1ca8:00c9

undefined2 ovl_00c9(void)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int in_BX;
  int iVar5;
  undefined2 *puVar6;
  int unaff_SI;
  int iVar7;
  int unaff_DI;
  undefined2 uVar8;
  undefined2 unaff_DS;
  
  ovl_01b3();
  ovl_129f();
  uVar8 = (undefined2)((ulong)G_rvarbuf >> 0x10);
  G_txtptr = *(undefined2 *)((int)G_rvarbuf + 5);
  G_txtptr+2 = uVar8;
  G_ocurpla = G_curpla;
  G_curpsize = G_psize;
  OV_0x18c = G_winxy;
  G_endcmbt = 0;
  G_terriflag = 0;
  G_bkonly = 0;
  G_swwill = 0;
  G_leader = 0;
  G_swauto = 0;
  G_BRIBEAMT = 0;
  G_GLOBEHIT = 0;
  iVar3 = 99;
  do {
    iVar7 = unaff_SI;
    *(undefined1 *)(iVar7 + -0x67bc) = 0;
    iVar3 = iVar3 + -1;
    unaff_SI = iVar7 + 1;
  } while (iVar3 != 0);
  OV_0x196 = 0;
  EXE_Locate(*(uint *)(iVar7 + 0x2c6e) & 0xff,*(uint *)(iVar7 + 0x2c6e) >> 8);
  OV_0x194 = *(undefined2 *)(iVar7 + -0x773c);
  EXE_LoadVar(0x44,6,in_BX);
  *(undefined1 *)(iVar7 + -0x7bcc) = 1;
  iVar4 = 0x18;
  iVar3 = iVar7 + -0x7aa2;
  iVar5 = 0;
  do {
    *(int *)(iVar5 + iVar7 + -0x7ad2) = iVar3;
    iVar3 = iVar3 + 0x21;
    iVar5 = iVar5 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  puVar6 = (undefined2 *)(iVar7 + 0x584d);
  uVar8 = 0x80a;
  do {
    do {
      *puVar6 = uVar8;
      puVar6 = puVar6 + -1;
      cVar1 = (char)uVar8;
      cVar2 = (char)((uint)uVar8 >> 8);
      uVar8 = CONCAT11(cVar2,cVar1 + -1);
    } while ('\0' < cVar1);
    uVar8 = CONCAT11(cVar2 + -1,10);
  } while ('\0' < cVar2);
  ovl_134b();
  *(undefined2 *)(iVar7 + -0x6596) = 0;
  ovl_020a();
  ovl_05fd();
  return *(undefined2 *)(iVar7 + -0x7076);
}


// ===== ovl_01b3 @ 1ca8:01b3

int ovl_01b3(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  iVar1 = iRam000004f8 + -0x100;
  *(undefined2 *)(*piRam000004fc + -0x728a) = piRam000004fc;
  return iVar1;
}


// ===== ovl_0205 @ 1ca8:0205

void ovl_0205(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_020a @ 1ca8:020a

void ovl_020a(void)

{
  char *pcVar1;
  undefined2 *puVar2;
  byte bVar3;
  int iVar4;
  undefined1 uVar5;
  char cVar6;
  uint uVar7;
  int iVar8;
  undefined1 *puVar9;
  int in_BX;
  byte *pbVar10;
  int iVar11;
  int unaff_SI;
  int unaff_DI;
  undefined2 *puVar12;
  undefined2 uVar13;
  undefined2 unaff_DS;
  bool bVar14;
  int in_stack_00000010;
  
  uVar13 = 0x1ca8;
  ovl_0cca();
  EXE_InitNPC(0x1ca8);
  if (G_cmbtyp == '\0') {
    G_npclocs = 0;
  }
  puVar12 = (undefined2 *)&G_magbits;
  for (iVar8 = 4; iVar8 != 0; iVar8 = iVar8 + -1) {
    puVar2 = puVar12;
    puVar12 = puVar12 + 1;
    *puVar2 = 0;
  }
  bVar3 = G_grpno;
  if (bVar3 < 0x3c) {
    G_monstlist = CONCAT11(bVar3,bVar3);
    G_monstlist+2 = CONCAT11(bVar3,bVar3);
    G_monstlist+4 = 0x29;
  }
  else {
    pbVar10 = (byte *)(G_grpsptr + (uint)(byte)(bVar3 - 0x3c) * 5);
    G_moncnt = (uint)*pbVar10;
    G_monstlist = *(undefined2 *)(pbVar10 + 1);
    G_monstlist+2 = *(undefined2 *)(pbVar10 + 3);
    G_monstlist+4 = 0x29;
  }
  if ((G_monstlist+3 & 0x80) != 0) {
    G_monstlist+3 = G_monstlist+3 & 0x7f;
    uVar5 = 1;
    if (G_monstlist+3 == ' ') {
      uVar5 = 6;
    }
    uVar13 = 0x1000;
    OV_0x196 = uVar5;
  }
  ovl_0496();
  EXE_LoadFolks(uVar13);
  iVar11 = 0;
  iVar8 = 6;
  do {
    iVar4 = *(int *)(iVar11 * 2 + &G_heroptr);
    *(undefined1 *)(iVar11 + &G_savcrg) = (char)*(undefined2 *)(iVar4 + 0xd);
    *(undefined1 *)(iVar11 + &G_savagi) = *(undefined1 *)(iVar4 + 0x11);
    iVar11 = iVar11 + 1;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  puVar12 = (undefined2 *)&G_crecs;
  cVar6 = '\0';
  for (iVar8 = 0x18c; iVar8 != 0; iVar8 = iVar8 + -1) {
    puVar2 = puVar12;
    puVar12 = puVar12 + 1;
    *puVar2 = 0;
  }
  iVar8 = &G_crecs;
  iVar11 = 0x18;
  do {
    *(undefined1 *)(iVar8 + 5) = 8;
    *(undefined2 *)(iVar8 + 1) = 0xffff;
    *(char *)(iVar8 + 0x1f) = cVar6;
    cVar6 = cVar6 + '\x01';
    iVar8 = iVar8 + 0x21;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  iVar8 = 6;
  do {
    if (*(int *)((iVar8 + -1) * 2 + &G_party) != 0xff) {
      ovl_0f2a();
    }
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  G_crecs+5 = G_crecs+5 | 4;
  ovl_12c2();
  if (OV_0x196 != '\0') {
    ovl_06b8();
  }
  iVar8 = G_moncnt;
  if (iVar8 == 0) {
    cVar6 = G_diff;
    iVar11 = G_loc+16;
    iVar8 = ovl_1323();
    iVar8 = iVar8 + (uint)*(byte *)((uint)(byte)(cVar6 * '\a') + iVar11);
    G_moncnt = iVar8;
  }
  if (G_curreg == 0xc) {
    FUN_1000_dab7();
    G_rec1+4 = 0;
    G_rec1+5 = 8;
    G_rec1+1 = 0xffff;
    iVar11 = 5;
    uVar5 = G_pltilno+17;
    do {
      *(undefined1 *)((uint)G_rec1+31 + &G_pltilno) = uVar5;
      ovl_1405();
      G_rec1+31 = G_rec1+31 + '\x01';
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
  }
  cVar6 = OV_0x196;
  G_moncnt = G_moncnt + cVar6;
  if (cVar6 == '\0') {
    OV_0x192 = 0;
    OV_0x193 = 0;
  }
  do {
    do {
      iVar11 = ovl_1323();
    } while (*(char *)(iVar11 + &OV_0x19b) == '\0');
    pcVar1 = (char *)(iVar11 + &OV_0x19b);
    *pcVar1 = *pcVar1 + -1;
    FUN_1000_dab7();
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  ovl_06c7();
  ovl_0b5c();
  G_zp_1415 = G_crecs+1;
  G_bkonly = 1;
  ovl_140f();
  G_bkonly = 0;
  iVar8 = 0;
  ovl_0c5c();
  ovl_0c6f();
  ovl_0c5c();
  ovl_0c6f();
  *(undefined2 *)(iVar8 + &G_fleetbl) = 0xffff;
  G_sklbits = 0;
  G_sklbits+2 = 0;
  G_sklbits+4 = 0;
  ovl_0205();
  EXE_SumStat();
  ovl_13fb();
  G_NEXTPHASE = 0;
  if (G_ambflg != '\0') {
    return;
  }
  EXE_FixMusRegs();
  if (G_cmbtyp == '\0') {
    return;
  }
L_04b8:
  EXE_InitMap();
  ovl_0205();
L_04c0:
  do {
    EXE_Menu();
    EXE_InitCom();
    while( true ) {
      uVar7 = EXE_Parser();
      if (uVar7 == 0xfd) goto L_04b8;
      if (uVar7 == 0xfe) goto L_04c0;
      if (uVar7 < 2) {
        if (uVar7 == 1) {
          EXE_RecSpl();
          goto L_04c0;
        }
        EXE_DrawWeap();
        ovl_1405();
        goto L_04b8;
      }
      bVar14 = uVar7 < 3;
      if (uVar7 < 4) break;
      if (uVar7 < 6) {
        if (uVar7 != 5) goto L_0583;
        EXE_Sheathe();
        ovl_1405();
        goto L_04b8;
      }
      iVar8 = EXE_RMove();
      if (iVar8 == 1) {
        EXE_GameSound();
      }
      else if (iVar8 == 2) {
        EXE_GameSound();
      }
    }
    if (uVar7 == 3) {
      EXE_Look();
      G_lookdata = 0xff;
      goto L_04b8;
    }
    ovl_06e7();
    if (bVar14) {
L_0583:
      iVar8 = 0;
      if (G_cmbtyp != '\0') {
        if (G_cmbtyp != '\x01') {
          if (G_endcmbt != 4) {
            ovl_05d5();
          }
          iVar8 = (uint)(byte)(G_rmdata+6 - 6) * 6;
        }
        puVar9 = (undefined1 *)(&G_setupxy + iVar8);
        iVar11 = 0;
        iVar8 = 6;
        do {
          if (*(char *)(iVar11 + &G_party) != -1) {
            *puVar9 = G_p1x;
            puVar9[0x18] = G_p1y;
          }
          puVar9 = puVar9 + 1;
          unaff_SI = unaff_SI + 1;
          iVar11 = iVar11 + 1;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      return;
    }
  } while( true );
}


// ===== ovl_0496 @ 1ca8:0496

void ovl_0496(void)

{
  byte *pbVar1;
  undefined1 uVar2;
  int iVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar3 = 0;
  do {
    uVar2 = 0xff;
    if ((*(byte *)(iVar3 + &G_monstlist) & 0x80) != 0) {
      uVar2 = 1;
    }
    *(undefined1 *)(iVar3 + &OV_0x19b) = uVar2;
    pbVar1 = (byte *)(iVar3 + &G_monstlist);
    *pbVar1 = *pbVar1 & 0x7f;
    iVar3 = iVar3 + 1;
  } while (iVar3 != 4);
  return;
}


// ===== ovl_05d5 @ 1ca8:05d5

undefined2 ovl_05d5(void)

{
  code *pcVar1;
  undefined2 uVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if ((*(char *)(G_crecptrs+12 + 3) == '\x1c') ||
     (*(char *)(G_crecptrs+12 + 3) == '\x1e')) {
    ovl_134b();
    ovl_0e98();
    pcVar1 = INT_0x61_handler;
    uVar2 = (*pcVar1)();
    return uVar2;
  }
  return 0x116;
}


// ===== ovl_05fd @ 1ca8:05fd

void __cdecl16near ovl_05fd(void)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  int local_4;
  
  local_4 = 0;
  ovl_1432();
  ovl_1437();
  iVar2 = 0x10;
  iVar3 = G_crecptrs+12;
  do {
    *(undefined1 *)(iVar3 + 0xe) = 0;
    iVar3 = iVar3 + 0x21;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar3 = 0x10;
  do {
    iVar2 = iVar3;
    if ((*(byte *)(iVar3 + &G_curdoombst) & 0x80) != 0) {
      ovl_064d();
      local_4 = iVar3;
    }
    iVar3 = iVar2 + -1;
  } while (iVar3 != 0);
  if (local_4 != 0) {
    puVar1 = (undefined2 *)(G_savebx + 0x380);
    EXE_viaptr_puVar1(0x1ca8,9,G_savebx);
  }
  return;
}


// ===== ovl_064d @ 1ca8:064d

void __cdecl16near ovl_064d(void)

{
  byte bVar1;
  int in_CX;
  int iVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  bVar1 = *(byte *)(in_BX + &G_curdoombst) & 0x7f;
  ovl_13fb(bVar1,in_CX + -1);
  ovl_1400();
  OV_0x1333 = 1;
  ovl_10ec();
  OV_0x1333 = 0;
  G_rec1+1 = G_rec2+1;
  iVar2 = 0x18;
  do {
    if ((*(byte *)(iVar2 + &G_curdoombst) & 0x7f) == bVar1) {
      ovl_1400();
      G_zp_1415 = G_rec2+1;
      ovl_143c();
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


// ===== ovl_06b8 @ 1ca8:06b8

void ovl_06b8(void)

{
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x192 = G_monstlist+3;
  FUN_1000_dab7();
  return;
}


// ===== ovl_06c7 @ 1ca8:06c7

void ovl_06c7(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar1 = G_moncnt;
  iVar2 = G_crecptrs+12;
  do {
    if (OV_0x192 == *(char *)(iVar2 + 3)) {
      *(byte *)(iVar2 + 5) = *(byte *)(iVar2 + 5) | 4;
      return;
    }
    iVar2 = iVar2 + 0x21;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_06e7 @ 1ca8:06e7

void ovl_06e7(void)

{
  int iVar1;
  undefined2 uVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  byte bVar7;
  int iVar8;
  int in_BX;
  int unaff_SI;
  uint unaff_DI;
  undefined2 uVar9;
  undefined2 unaff_DS;
  bool bVar10;
  char in_AF;
  
  uVar9 = 0x1ca8;
code_r0x0001d167:
  EXE_InitMap(0x1ca8);
  ovl_0205();
L_06ef:
  EXE_Menu(0x1ca8,0xe);
  EXE_InitCom(0x1ca8,&OV_0x103,0x1ca8,2);
L_070d:
  iVar5 = EXE_Parser(0x1ca8,&G_mnuparms,0);
  if (iVar5 == -1) {
    return;
  }
  if (iVar5 == 0xfd) goto code_r0x0001d167;
  if (iVar5 != 0xfe) {
    if (iVar5 != 0) goto code_r0x0001d1b4;
    uVar6 = EXE_CntPar(0x1ca8);
    if (uVar6 < 2) {
      ovl_139d();
      return;
    }
    iVar8 = EXE_RndCo(0x1ca8,2);
    iVar5 = in_BX;
    if (iVar8 == 0) goto L_075a;
    ovl_139d();
    EXE_PrtWrd(0x1ca8,G_comtxtptr);
    iVar5 = 100;
    bVar3 = EXE_RndCo(0x1ca8);
    if (bVar3 < (byte)in_BX) {
      cVar4 = EXE_RndCo(0x1ca8,3);
      G_deftxtparms+2 = cVar4 + '\x01';
      G_deftxtparms = 4;
      iVar8 = 6;
      uVar6 = 0;
      do {
        bVar3 = in_AF << 4;
        in_AF = (bVar3 & 0x10) != 0;
        if ((*(char *)(uVar6 * 2 + &G_party) != -1 && (bVar3 & 0x40) == 0) &&
           ((uVar6 & 0x7fff) != G_curpla)) {
          iVar1 = *(int *)(uVar6 * 2 + &G_heroptr);
          bVar3 = (char)*(undefined2 *)(iVar1 + 0xd) + G_deftxtparms+2;
          if (0xc < bVar3) {
            bVar3 = 0xc;
          }
          *(byte *)(iVar1 + 0xd) = bVar3;
          bVar7 = *(char *)(iVar1 + 0x11) + 4;
          uVar9 = CONCAT11(bVar7,bVar3);
          if (0xc < bVar7) {
            uVar9 = CONCAT11(0xc,bVar3);
          }
          *(undefined1 *)(iVar1 + 0x11) = (char)((uint)uVar9 >> 8);
          OV_0x18e = uVar9;
          ovl_13fb();
          uVar9 = 0x1000;
          uVar2 = OV_0x18e;
          G_rec1+17 = (char)uVar2;
          G_rec1+20 = (char)((uint)uVar2 >> 8);
          ovl_1405();
        }
        uVar6 = (uVar6 & 0x7fff) + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    goto L_082a;
  }
  goto L_06ef;
code_r0x0001d1b4:
  if (iVar5 == 1) {
    if (*(char *)(G_crecptrs+12 + 3) == '\x1c') {
      G_VANKRUHXY = *(undefined2 *)(G_crecptrs+12 + 1);
      iVar8 = 6;
      iVar5 = G_crecptrs;
      while (((*(byte *)(iVar5 + 5) & 8) != 0 || (*(char *)(iVar5 + 0xf) == -1))) {
        iVar5 = iVar5 + 0x21;
        iVar8 = iVar8 + -1;
        if (iVar8 == 0) {
          ovl_134b();
          G_events+8 = G_events+8 | 4;
          G_events+18 = G_events+18 | 0x40;
          ovl_0b18();
          return;
        }
      }
      G_ambflg = 1;
      iVar5 = G_savebx;
      ovl_134b();
      EXE_PrtWrd(0x1ca8,G_comtxtptr);
      return;
    }
    iVar5 = G_savebx;
    (*(code *)*(undefined2 *)(iVar5 + 600))(0x1000,OV_0x192);
    if (OV_0x197 < 6) {
      ovl_139d();
      EXE_PrtWrd(G_comtxtptr);
      ovl_139d();
      EXE_PrtWrd(G_comtxtptr);
      uVar6 = *(uint *)(OV_0x197 * 2 + &OV_0xa4b);
      bVar10 = CARRY2(uVar6,unaff_DI);
      (*(code *)(uVar6 + unaff_DI))();
      if (bVar10) {
        return;
      }
      iVar5 = EXE_SetYN();
      if (iVar5 == 0) {
        (*(code *)(*(int *)(OV_0x197 * 2 + &OV_0xa57) + unaff_DI))();
        ovl_0b18();
        return;
      }
      return;
    }
    uVar9 = 0x1000;
    ovl_139d();
    EXE_PrtWrd(G_comtxtptr);
    iVar5 = 0;
L_075a:
    G_ambflg = 1;
L_082a:
    ovl_139d();
    EXE_PrtWrd(uVar9,G_comtxtptr);
    return;
  }
  goto L_070d;
}


// ===== ovl_0b18 @ 1ca8:0b18

void ovl_0b18(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_endcmbt = 4;
  return;
}


// ===== ovl_0b5c @ 1ca8:0b5c

void ovl_0b5c(void)

{
  ulong uVar1;
  byte bVar2;
  undefined1 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int in_BX;
  int iVar9;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (OV_0x192 == 0) {
    uVar3 = 6;
  }
  else if (OV_0x192 < 0x19) {
    uVar4 = 0;
    uVar8 = 0;
    iVar9 = &G_crecs;
    iVar7 = 0x18;
    do {
      if ((*(byte *)(iVar9 + 5) & 8) == 0) {
        if (*(char *)(iVar9 + 4) == '\x01') {
          iVar5 = uVar4 + *(int *)(iVar9 + 10);
          bVar2 = (byte)iVar5;
          uVar4 = CONCAT11((char)((uint)iVar5 >> 8) + CARRY1(bVar2,*(byte *)(iVar9 + 0x18)),
                           bVar2 + *(byte *)(iVar9 + 0x18));
          if ('\x19' < *(char *)(iVar9 + 0xf)) {
            uVar4 = uVar4 + 10;
          }
        }
        else {
          uVar8 = uVar8 + *(int *)((uint)*(byte *)(iVar9 + 3) * 2 + &OV_0xc3f);
        }
      }
      iVar9 = iVar9 + 0x21;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    uVar1 = (ulong)uVar4 / (ulong)uVar8;
    uVar6 = (uint)uVar1;
    if (uVar6 == 0) {
      iVar9 = (int)((uVar1 << 0x10 | (ulong)uVar4 % (ulong)uVar8) / (ulong)(uVar8 >> 3));
      iVar7 = EXE_RndCo(4);
      uVar3 = *(undefined1 *)(iVar9 + iVar7 + &OV_0xc4b);
    }
    else if (uVar6 < 2) {
      iVar9 = EXE_RndCo(6);
      uVar3 = *(undefined1 *)(iVar9 + &OV_0xc56);
    }
    else {
      uVar3 = 5;
    }
  }
  else {
    uVar3 = 7;
  }
  OV_0x197 = uVar3;
  iVar9 = G_savebx;
  if ((*(char *)(G_crecptrs+12 + 3) != '\x1c') &&
     (G_cmbtyp != '\0')) {
    EXE_SetTxtAttitude(uVar3);
    EXE_ClrTxtWnd();
    EXE_InitScrap();
    iVar7 = EXE_Advice((int)G_txtptr,
                       (int)((ulong)G_txtptr >> 0x10),0x1e,0x1d,0x20);
    if (iVar7 != 0) {
      EXE_PrtScrap(0xff,iVar9);
    }
  }
  return;
}


// ===== ovl_0c5c @ 1ca8:0c5c

void ovl_0c5c(void)

{
  char cVar1;
  
  do {
    ovl_0ca5();
    cVar1 = ovl_0c83();
  } while (cVar1 != '\n');
  return;
}


// ===== ovl_0c6f @ 1ca8:0c6f

void ovl_0c6f(void)

{
  char extraout_AH;
  
  do {
    ovl_0ca5();
    ovl_0c83();
  } while (extraout_AH != '\a');
  return;
}


// ===== ovl_0c83 @ 1ca8:0c83

undefined2 ovl_0c83(void)

{
  undefined2 in_AX;
  int iVar1;
  uint in_DX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = (in_DX >> 8) * 0xb;
  if (*(byte *)(CONCAT11((char)((uint)iVar1 >> 8),(char)iVar1 + (char)in_DX) + &G_blobmap) <
      100) {
    *(uint *)(in_BX + &G_fleetbl) = in_DX;
    return in_AX;
  }
  return in_AX;
}


// ===== ovl_0ca5 @ 1ca8:0ca5

undefined4 ovl_0ca5(void)

{
  undefined2 *puVar1;
  uint in_AX;
  undefined2 in_DX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x230);
  EXE_viaptr_puVar1(0x1ca8,in_AX & 0xff,in_AX >> 8);
  return CONCAT22(in_DX,in_AX);
}


// ===== ovl_0cca @ 1ca8:0cca

void ovl_0cca(void)

{
  undefined1 *puVar1;
  undefined2 *puVar2;
  undefined1 *puVar3;
  undefined2 *puVar4;
  undefined1 uVar5;
  byte bVar6;
  char cVar7;
  char cVar8;
  int *piVar9;
  int in_BX;
  undefined1 *puVar10;
  int unaff_SI;
  undefined2 *puVar11;
  undefined1 *puVar12;
  int iVar13;
  int unaff_DI;
  undefined2 *puVar14;
  undefined2 unaff_DS;
  
  cVar7 = *(char *)((uint)G_cmbtyp + &OV_0xdc4);
  if (cVar7 == -1) {
    EXE_InitMap();
    puVar10 = (undefined1 *)OV_0x194;
    bVar6 = G_thismap;
    G_thismap = 0xb;
    G_mapyl = 9;
    cVar7 = '\t';
    iVar13 = unaff_SI;
    do {
      cVar8 = '\v';
      do {
        puVar12 = puVar10;
        uVar5 = *puVar12;
        *(undefined1 *)(iVar13 + 0x2cd6) = uVar5;
        *(undefined1 *)(iVar13 + 0x7f33) = uVar5;
        iVar13 = iVar13 + 1;
        cVar8 = cVar8 + -1;
        puVar10 = puVar12 + 1;
      } while (cVar8 != '\0');
      puVar10 = puVar12 + (bVar6 - 10);
      cVar7 = cVar7 + -1;
    } while (cVar7 != '\0');
  }
  else {
    EXE_LoadMap(cVar7,0,0x47);
    if (G_cmbtyp == '\x01') {
      bVar6 = G_terrain;
    }
    else {
      bVar6 = G_hroomrec+4 & 0xf;
    }
    if (bVar6 != 0) {
      puVar14 = (undefined2 *)&G_thismap;
      puVar11 = (undefined2 *)((int)puVar14 + (uint)bVar6 * 0x65);
      for (iVar13 = 0x32; iVar13 != 0; iVar13 = iVar13 + -1) {
        puVar4 = puVar14;
        puVar14 = puVar14 + 1;
        puVar2 = puVar11;
        puVar11 = puVar11 + 1;
        *puVar4 = *puVar2;
      }
      for (iVar13 = 1; iVar13 != 0; iVar13 = iVar13 + -1) {
        puVar4 = puVar14;
        puVar14 = (undefined2 *)((int)puVar14 + 1);
        puVar2 = puVar11;
        puVar11 = (undefined2 *)((int)puVar11 + 1);
        *(undefined1 *)puVar4 = *(undefined1 *)puVar2;
      }
    }
    puVar10 = (undefined1 *)&G_secwin;
    puVar12 = (undefined1 *)&G_mapyl+1;
    for (iVar13 = 99; iVar13 != 0; iVar13 = iVar13 + -1) {
      puVar3 = puVar10;
      puVar10 = puVar10 + 1;
      puVar1 = puVar12;
      puVar12 = puVar12 + 1;
      *puVar3 = *puVar1;
    }
    EXE_InitMap();
    if (G_cmbtyp == '\x05') {
      if (G_hroomrec+2 != 0) {
        if ((G_hroomrec+2 & 0x80) == 0) {
          EXE_Locate(1,1);
          LOCK();
          puVar10 = (undefined1 *)G_zp_0A;
          G_zp_0A = in_BX;
          UNLOCK();
          *puVar10 = 0x1f;
          LOCK();
          in_BX = G_zp_0A;
          G_zp_0A = (int)puVar10;
          UNLOCK();
          G_secwin+12 = 0x1f;
        }
        else {
          EXE_Locate(9,0);
          LOCK();
          puVar10 = (undefined1 *)G_zp_0A;
          G_zp_0A = in_BX;
          UNLOCK();
          *puVar10 = 0x1c;
          puVar10[0xb] = 0xe;
          LOCK();
          in_BX = G_zp_0A;
          G_zp_0A = (int)puVar10;
          UNLOCK();
          G_secwin+9 = 0x1c;
          G_secwin+20 = 0xe;
        }
      }
      ovl_0e7e();
      iVar13 = 4;
      *(undefined2 *)(unaff_DI + 400) = 0;
      piVar9 = (int *)&G_hroomrec+11;
      do {
        if (*piVar9 != 0) {
          ovl_0e19();
        }
        piVar9 = piVar9 + -1;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
      LOCK();
      iVar13 = *(int *)(unaff_DI + 400);
      *(int *)(unaff_DI + 400) = in_BX;
      UNLOCK();
      *(undefined2 *)(iVar13 + &G_fleetbl) = 0xffff;
      LOCK();
      *(int *)(unaff_DI + 400) = iVar13;
      UNLOCK();
    }
  }
  G_winxy = 0;
  return;
}


// ===== ovl_0e19 @ 1ca8:0e19

void ovl_0e19(void)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  int in_CX;
  uint uVar7;
  uint extraout_DX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar7 = (in_CX + -1) * 2;
  do {
    *(undefined2 *)OV_0x19f =
         CONCAT11(*(undefined1 *)(uVar7 + &OV_0x111),
                  *(undefined1 *)(uVar7 + &OV_0x109));
    ovl_0c83();
    iVar5 = G_savebx;
    EXE_Locate(extraout_DX & 0xff);
    uVar4 = *(undefined1 *)(G_tdata+8 + iVar5);
    LOCK();
    puVar3 = (undefined1 *)G_zp_0A;
    G_zp_0A = extraout_DX >> 8;
    UNLOCK();
    LOCK();
    puVar1 = puVar3;
    uVar2 = *puVar1;
    *puVar1 = uVar4;
    UNLOCK();
    iVar6 = OV_0x19f;
    *(undefined1 *)(iVar6 + 0x14) = uVar2;
    LOCK();
    G_zp_0A = iVar6;
    UNLOCK();
    uVar7 = iVar5 + 1;
    OV_0x19f = OV_0x19f + 1;
    OV_0x19f = OV_0x19f + 1;
  } while ((uVar7 & 1) != 0);
  return;
}


// ===== ovl_0e7e @ 1ca8:0e7e

void ovl_0e7e(void)

{
  int iVar1;
  undefined2 *puVar2;
  int unaff_DI;
  
  puVar2 = (undefined2 *)&OV_0x1a1;
  OV_0x19f = puVar2;
  iVar1 = 10;
  do {
    *puVar2 = 0xffff;
    puVar2 = puVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_0e98 @ 1ca8:0e98

void __cdecl16near ovl_0e98(void)

{
  undefined2 *puVar1;
  uint uVar2;
  undefined2 uVar3;
  uint *puVar4;
  int iVar5;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  uint uVar6;
  
  puVar1 = (undefined2 *)(G_savebx + 0x340);
  EXE_viaptr_puVar1(0x1ca8,G_savebx);
  for (puVar4 = (uint *)&OV_0x1a1; *puVar4 != 0xffff; puVar4 = puVar4 + 1) {
    uVar2 = (uint)(byte)puVar4[10];
    uVar6 = *puVar4;
    puVar1 = (undefined2 *)(G_savebx + 0xf4);
    EXE_viaptr_puVar1(0x1000,uVar6 & 0xff,uVar6 >> 8,G_savebx,uVar2,uVar6);
    *(undefined1 *)G_zp_0A = (char)uVar2;
    puVar1 = (undefined2 *)(G_savebx + 0x120);
    EXE_viaptr_puVar1(0x1000,uVar6 & 0xff,uVar6 >> 8,G_savebx,uVar6);
    iVar5 = G_mfxcnt;
    *(uint *)(iVar5 + &G_mfxtnum) = uVar2 & 0xff;
    uVar3 = ovl_0f1a();
    *(undefined2 *)(iVar5 + &G_mfxcoords) = uVar3;
    *(undefined2 *)(iVar5 + &G_mfxcflag) = 0;
    G_mfxcnt = G_mfxcnt + 2;
  }
  ovl_1423();
  return;
}


// ===== ovl_0f1a @ 1ca8:0f1a

undefined2 __cdecl16near ovl_0f1a(void)

{
  char in_AL;
  char in_AH;
  
  return CONCAT11(in_AH * '\x10' + '\b',in_AL * '\x04' + '\x04');
}


// ===== ovl_0f2a @ 1ca8:0f2a

void __cdecl16near ovl_0f2a(void)

{
  undefined1 *puVar1;
  byte bVar2;
  code *pcVar3;
  char cVar4;
  int in_AX;
  int iVar5;
  undefined1 *puVar6;
  int unaff_BP;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  puVar6 = (undefined1 *)&G_rec1;
  for (iVar5 = 0x21; iVar5 != 0; iVar5 = iVar5 + -1) {
    puVar1 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar1 = 0;
  }
  G_rec1+31 = (char)((uint)in_AX >> 8);
  pcVar3 = INT_0x61_handler;
  (*pcVar3)();
  *(byte *)(in_AX + 0x16) = *(byte *)(in_AX + 0x16) | 0x80;
  G_rec1+3 = *(undefined1 *)(in_AX + 6);
  G_rec1+17 = *(undefined1 *)(in_AX + 0xd);
  G_rec1+18 = *(undefined1 *)(in_AX + 0xe);
  G_rec1+19 = *(undefined1 *)(in_AX + 0xf);
  G_rec1+20 = *(undefined1 *)(in_AX + 0x11);
  G_rec1+21 = *(undefined1 *)(in_AX + 0x15);
  G_rec1+22 = *(undefined1 *)(in_AX + 0x14);
  G_rec1+10 = *(undefined1 *)(in_AX + 0xca);
  G_rec1+12 = *(undefined1 *)(in_AX + 0xbb);
  G_rec1+13 = *(undefined1 *)(in_AX + 0xba);
  if ((*(byte *)(in_AX + 0xa5) & 0x40) != 0) {
    G_rec1+29 = 3;
  }
  G_rec1+7 = 0xff;
  G_rec1+30 = 1;
  if (G_cmbtyp == 1) {
    cVar4 = '\0';
  }
  else {
    if (G_cmbtyp < 2) {
      iVar5 = CONCAT11(*(undefined1 *)((uint)G_rec1+31 + &G_p1y),
                       *(undefined1 *)((uint)G_rec1+31 + &G_p1x)) -
              OV_0x18c;
      goto L_101c;
    }
    cVar4 = G_rmdata+6 + -6;
  }
  puVar6 = (undefined1 *)
           (&G_setupxy + (uint)(byte)(cVar4 * '\x06' + G_rec1+31));
  iVar5 = EXE_PlacePerson(0x1ca8,*puVar6,puVar6[0x18],unaff_BP);
L_101c:
  bVar2 = G_rec1+31;
  G_rec1+1 = iVar5;
  *(undefined1 *)((uint)bVar2 + &G_p1x) = (char)iVar5;
  *(undefined1 *)((uint)bVar2 + &G_p1y) = (char)((uint)iVar5 >> 8);
  ovl_1405();
  return;
}


// ===== FUN_1000_dab7 @ 1000:dab7

void FUN_1000_dab7(void)

{
  undefined2 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined2 *puVar4;
  char cVar5;
  char cVar6;
  byte bVar7;
  undefined1 uVar8;
  uint in_AX;
  undefined2 uVar9;
  uint uVar10;
  int iVar11;
  int in_BX;
  int iVar12;
  int unaff_SI;
  undefined1 *puVar13;
  undefined2 *puVar14;
  undefined1 *puVar15;
  int unaff_DI;
  undefined2 *puVar16;
  undefined1 *puVar17;
  undefined2 unaff_DS;
  undefined2 uStack_8;
  undefined2 uStack_6;
  
  OV_0x1333 = 0;
  puVar15 = (undefined1 *)&G_rec1;
  for (iVar11 = 0x21; iVar11 != 0; iVar11 = iVar11 + -1) {
    puVar2 = puVar15;
    puVar15 = puVar15 + 1;
    *puVar2 = 0;
  }
  uVar8 = (undefined1)(in_AX >> 8);
  G_rec1+31 = uVar8;
  G_curatt = uVar8;
  cVar5 = (char)in_AX;
  G_rec1+3 = cVar5;
  G_rec1+5 =
       G_rec1+5 | *(char *)((in_AX & 0xff) + &OV_0x162) << 1;
  G_curatt+1 = 0;
  cVar6 = *(char *)((in_AX & 0xff) + &OV_0x139);
  puVar15 = (undefined1 *)*(undefined2 *)((uint)(byte)(cVar5 - 5) * 2 + &G_monsptr);
  if ((OV_0x196 == '\0') && (OV_0x193 < cVar6)) {
    OV_0x193 = cVar6;
    OV_0x192 = cVar5;
  }
  G_rec1+4 = 1;
  G_rec1+7 = 0xff;
  G_rec1+13 = 99;
  LOCK();
  UNLOCK();
  puVar17 = (undefined1 *)&G_rec1+10;
  puVar13 = puVar15;
  for (iVar11 = 3; iVar11 != 0; iVar11 = iVar11 + -1) {
    puVar3 = puVar17;
    puVar17 = puVar17 + 1;
    puVar2 = puVar13;
    puVar13 = puVar13 + 1;
    *puVar3 = *puVar2;
  }
  puVar16 = (undefined2 *)&G_rec1+15;
  puVar14 = (undefined2 *)(puVar15 + 3);
  for (iVar11 = 5; iVar11 != 0; iVar11 = iVar11 + -1) {
    puVar4 = puVar16;
    puVar16 = puVar16 + 1;
    puVar1 = puVar14;
    puVar14 = puVar14 + 1;
    *puVar4 = *puVar1;
  }
  puVar17 = (undefined1 *)&G_rec1+27;
  puVar15 = puVar15 + 0xd;
  for (iVar11 = 3; iVar11 != 0; iVar11 = iVar11 + -1) {
    puVar3 = puVar17;
    puVar17 = puVar17 + 1;
    puVar2 = puVar15;
    puVar15 = puVar15 + 1;
    *puVar3 = *puVar2;
  }
  LOCK();
  UNLOCK();
  iVar11 = 0;
  if (G_cmbtyp < 2) {
    if (G_cmbtyp != 1) {
      G_zp_1415 = G_crecs+1;
      G_bkonly = 1;
      ovl_140f();
      G_bkonly = 0;
      uVar10 = EXE_RndCo(99);
      goto L_11aa;
    }
  }
  else {
    iVar11 = (uint)(byte)(G_rmdata+6 - 6) << 1;
  }
  if (((G_rec1+24 != '\0') && (G_rec1+3 != ' ')) &&
     (G_rec1+3 != '\x1c')) {
    iVar11 = CONCAT11((char)((uint)iVar11 >> 8),(char)iVar11 + '\b');
  }
  uStack_6 = *(undefined2 *)(iVar11 + &OV_0x119);
  uStack_8 = *(undefined2 *)(iVar11 + &OV_0x129);
  do {
    uVar9 = EXE_RndCo((byte)(uStack_8._1_1_ - (char)uStack_8) + 1);
    uStack_8._0_1_ = (char)uStack_8 + (char)uVar9;
    cVar6 = EXE_RndCo(CONCAT11((char)((uint)uVar9 >> 8),uStack_6._1_1_ - (char)uStack_6) + 1
                      );
    uVar10 = EXE_PlacePerson(cVar6 + (char)uStack_6,(char)uStack_8)
    ;
    G_zp_1415 = G_crecs+1;
    G_bkonly = 1;
    ovl_140f();
    G_bkonly = 0;
    iVar11 = (uVar10 >> 8) * 0xb;
    uVar10 = CONCAT11((char)((uint)iVar11 >> 8),(char)iVar11 + (char)uVar10);
    while( true ) {
      iVar11 = ovl_1419();
      if (iVar11 == 0x18) {
        if (*(byte *)(uVar10 + &G_blobmap) < 100) {
          G_rec1+1 = CONCAT11((char)(uVar10 / 0xb),(char)(uVar10 % 0xb));
          ovl_1405();
          if (OV_0x1333 == '\x01') {
            return;
          }
          uVar8 = EXE_FirsTil(G_curatt);
          LOCK();
          iVar11 = G_curatt;
          G_curatt = in_BX;
          UNLOCK();
          *(undefined1 *)(iVar11 + &G_pltilno) = uVar8;
          LOCK();
          G_curatt = iVar11;
          UNLOCK();
          iVar12 = 0;
          iVar11 = 0x18;
          do {
            *(undefined2 *)(iVar12 + &G_MAXHPTS) =
                 *(undefined2 *)(*(int *)(iVar12 + &G_crecptrs) + 10);
            iVar12 = iVar12 + 2;
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
          ovl_1234();
          return;
        }
        cVar6 = G_cmbtyp;
      }
      else {
        cVar6 = G_cmbtyp;
      }
      if (cVar6 != '\0') break;
L_11aa:
      cVar6 = (char)uVar10;
      uVar8 = (undefined1)(uVar10 >> 8);
      bVar7 = cVar6 + 0x11;
      uVar10 = CONCAT11(uVar8,bVar7);
      if (0x62 < bVar7) {
        uVar10 = CONCAT11(uVar8,cVar6 + -0x52);
      }
    }
  } while( true );
}


// ===== ovl_10ec @ 1ca8:10ec

void __cdecl16near ovl_10ec(void)

{
  char cVar1;
  byte bVar2;
  undefined1 uVar3;
  int iVar4;
  undefined2 uVar5;
  uint uVar6;
  int in_BX;
  int iVar7;
  int unaff_BP;
  int unaff_SI;
  int unaff_DI;
  undefined2 uVar8;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar8 = 0x1ca8;
  iVar4 = 0;
  if (G_cmbtyp < 2) {
    if (G_cmbtyp != 1) {
      G_zp_1415 = G_crecs+1;
      G_bkonly = 1;
      ovl_140f();
      G_bkonly = 0;
      uVar6 = EXE_RndCo(0x1ca8,99);
      goto L_11aa;
    }
  }
  else {
    iVar4 = (uint)(byte)(G_rmdata+6 - 6) << 1;
  }
  if (((G_rec1+24 != '\0') && (G_rec1+3 != ' ')) &&
     (G_rec1+3 != '\x1c')) {
    iVar4 = CONCAT11((char)((uint)iVar4 >> 8),(char)iVar4 + '\b');
  }
  *(undefined2 *)(unaff_BP + -4) = *(undefined2 *)(iVar4 + &OV_0x119);
  uVar8 = 0x1000;
  *(undefined2 *)(unaff_BP + -6) = *(undefined2 *)(iVar4 + &OV_0x129);
  do {
    uVar5 = EXE_RndCo(uVar8,(byte)(*(char *)(unaff_BP + -5) - *(char *)(unaff_BP + -6)) + 1);
    *(char *)(unaff_BP + -6) = *(char *)(unaff_BP + -6) + (char)uVar5;
    cVar1 = EXE_RndCo(uVar8,CONCAT11((char)((uint)uVar5 >> 8),
                                      *(char *)(unaff_BP + -3) - *(char *)(unaff_BP + -4)) + 1);
    uVar6 = EXE_PlacePerson(uVar8,cVar1 + *(char *)(unaff_BP + -4),*(undefined1 *)(unaff_BP + -6));
    G_zp_1415 = G_crecs+1;
    G_bkonly = 1;
    ovl_140f();
    G_bkonly = 0;
    iVar4 = (uVar6 >> 8) * 0xb;
    uVar6 = CONCAT11((char)((uint)iVar4 >> 8),(char)iVar4 + (char)uVar6);
    while( true ) {
      iVar4 = ovl_1419();
      if (iVar4 == 0x18) {
        if (*(byte *)(uVar6 + &G_blobmap) < 100) {
          G_rec1+1 = CONCAT11((char)(uVar6 / 0xb),(char)(uVar6 % 0xb));
          ovl_1405();
          if (OV_0x1333 == '\x01') {
            return;
          }
          uVar3 = EXE_FirsTil(G_curatt);
          LOCK();
          iVar4 = G_curatt;
          G_curatt = in_BX;
          UNLOCK();
          *(undefined1 *)(iVar4 + &G_pltilno) = uVar3;
          LOCK();
          G_curatt = iVar4;
          UNLOCK();
          iVar7 = 0;
          iVar4 = 0x18;
          do {
            *(undefined2 *)(iVar7 + &G_MAXHPTS) =
                 *(undefined2 *)(*(int *)(iVar7 + &G_crecptrs) + 10);
            iVar7 = iVar7 + 2;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
          ovl_1234();
          return;
        }
        cVar1 = G_cmbtyp;
      }
      else {
        cVar1 = G_cmbtyp;
      }
      if (cVar1 != '\0') break;
L_11aa:
      cVar1 = (char)uVar6;
      uVar3 = (undefined1)(uVar6 >> 8);
      bVar2 = cVar1 + 0x11;
      uVar6 = CONCAT11(uVar3,bVar2);
      if (0x62 < bVar2) {
        uVar6 = CONCAT11(uVar3,cVar1 + -0x52);
      }
    }
  } while( true );
}


// ===== ovl_1234 @ 1ca8:1234

void __cdecl16near ovl_1234(void)

{
  byte bVar1;
  undefined2 *puVar2;
  undefined1 uVar3;
  int iVar4;
  undefined2 in_BX;
  uint uVar5;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (G_rec1+3 == ' ') {
    OV_0x1333 = 1;
    iVar4 = 5;
    do {
      G_rec1+31 = G_rec1+31 + '\x01';
      G_rec1+14 = 1;
      ovl_10ec();
      ovl_1405();
      puVar2 = (undefined2 *)(G_savebx + 0x1b8);
      uVar3 = EXE_viaptr_puVar2(0x1000,G_curatt,in_BX);
      *(undefined1 *)((uint)G_rec1+31 + &G_pltilno) = uVar3;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    uVar5 = (uint)(byte)(G_rec1+31 - 5);
    bVar1 = G_curdoombst;
    *(byte *)(uVar5 + &G_doombstlst) = bVar1 | 0x80;
    iVar4 = 5;
    do {
      uVar5 = uVar5 + 1;
      *(byte *)(uVar5 + &G_doombstlst) = bVar1 & 0x7f;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    OV_0x1333 = 0;
    G_curdoombst = G_curdoombst + '\x01';
  }
  return;
}


// ===== ovl_129f @ 1ca8:129f

void ovl_129f(void)

{
  int iVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_curdoombst = 1;
  iVar1 = 0xc;
  do {
    G_doombstlst = 0;
    unaff_SI = unaff_SI + 2;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_12c2 @ 1ca8:12c2

void ovl_12c2(void)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar8;
  bool bVar9;
  
  iVar6 = 0;
  iVar5 = 10;
  do {
    *(undefined1 *)(iVar6 + &G_semiranseed) = *(undefined1 *)(iVar6 + &OV_0x13b8);
    iVar6 = iVar6 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  pbVar7 = (byte *)&G_hroomrec;
  iVar5 = 5;
  bVar9 = false;
  do {
    pbVar1 = (byte *)&G_semiranseed;
    bVar2 = *pbVar1 + *pbVar7;
    bVar8 = CARRY1(*pbVar1,*pbVar7) || CARRY1(bVar2,bVar9);
    *pbVar1 = bVar2 + bVar9;
    pbVar7 = pbVar7 + 1;
    iVar5 = iVar5 + -1;
    bVar9 = bVar8;
  } while (iVar5 != 0);
  pbVar1 = (byte *)&G_semiranseed+1;
  bVar3 = (byte)G_curlev;
  bVar2 = *pbVar1 + bVar3;
  bVar9 = CARRY1(*pbVar1,bVar3) || CARRY1(bVar2,bVar8);
  *pbVar1 = bVar2 + bVar8;
  pbVar1 = (byte *)&G_semiranseed+2;
  bVar3 = (byte)G_curreg;
  bVar2 = *pbVar1 + bVar3;
  bVar8 = CARRY1(*pbVar1,bVar3) || CARRY1(bVar2,bVar9);
  *pbVar1 = bVar2 + bVar9;
  pbVar1 = (byte *)&G_semiranseed+3;
  bVar3 = (byte)G_curmpg;
  bVar2 = *pbVar1 + bVar3;
  bVar9 = CARRY1(*pbVar1,bVar3) || CARRY1(bVar2,bVar8);
  *pbVar1 = bVar2 + bVar8;
  pbVar1 = (byte *)&G_semiranseed+4;
  bVar3 = (byte)G_locspec;
  bVar2 = *pbVar1 + bVar3;
  bVar8 = CARRY1(*pbVar1,bVar3) || CARRY1(bVar2,bVar9);
  *pbVar1 = bVar2 + bVar9;
  pbVar1 = (byte *)&G_semiranseed+5;
  bVar2 = *pbVar1;
  bVar4 = (byte)G_curtils;
  bVar3 = *pbVar1 + bVar4;
  *pbVar1 = bVar3 + bVar8;
  G_semiranseed+6 =
       G_semiranseed+6 + G_diff +
       (CARRY1(bVar2,bVar4) || CARRY1(bVar3,bVar8));
  iVar5 = 10;
  do {
    ovl_1333();
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}


// ===== ovl_1323 @ 1ca8:1323

uint ovl_1323(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  uint in_stack_00000000;
  
  ovl_1333();
  return G_semiranseed % in_stack_00000000;
}


// ===== ovl_1333 @ 1ca8:1333

void ovl_1333(void)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar4;
  bool bVar5;
  
  pbVar3 = (byte *)&G_semiranseed;
  iVar2 = 9;
  bVar4 = false;
  do {
    bVar1 = *pbVar3 + pbVar3[1];
    bVar5 = CARRY1(*pbVar3,pbVar3[1]) || CARRY1(bVar1,bVar4);
    *pbVar3 = bVar1 + bVar4;
    pbVar3 = pbVar3 + 1;
    iVar2 = iVar2 + -1;
    bVar4 = bVar5;
  } while (iVar2 != 0);
  *pbVar3 = *pbVar3 + 0x65 + bVar5;
  return;
}


// ===== ovl_134b @ 1ca8:134b

void ovl_134b(void)

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


// ===== ovl_139d @ 1ca8:139d

void ovl_139d(void)

{
  undefined2 in_AX;
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(0x1ca8,1);
  EXE_IModTxt(0x1ca8,in_AX,in_BX);
  return;
}


// ===== ovl_13de @ 1ca8:13de

void __cdecl16near ovl_13de(void)

{
  int in_CX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = in_CX + *(int *)(in_BX + 0x148);
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_13fb @ 1ca8:13fb

void ovl_13fb(void)

{
  ovl_13de();
  return;
}


// ===== ovl_1400 @ 1ca8:1400

void ovl_1400(void)

{
  ovl_13de();
  return;
}


// ===== ovl_1405 @ 1ca8:1405

void ovl_1405(void)

{
  ovl_13de();
  return;
}


// ===== ovl_140f @ 1ca8:140f

void ovl_140f(void)

{
  ovl_13de();
  return;
}


// ===== ovl_1419 @ 1ca8:1419

void __cdecl16near ovl_1419(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_1423 @ 1ca8:1423

void __cdecl16near ovl_1423(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_1432 @ 1ca8:1432

void __cdecl16near ovl_1432(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_1437 @ 1ca8:1437

void ovl_1437(void)

{
  ovl_13de();
  return;
}


// ===== ovl_143c @ 1ca8:143c

void ovl_143c(void)

{
  ovl_13de();
  return;
}


