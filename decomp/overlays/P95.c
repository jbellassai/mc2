// ===== ovl_02d1 @ 1ca8:02d1

void ovl_02d1(void)

{
  byte *pbVar1;
  int *piVar2;
  byte bVar3;
  undefined1 uVar4;
  int iVar5;
  undefined2 *puVar6;
  undefined2 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar11;
  undefined4 uVar12;
  uint uStack_8;
  
  uStack_8 = 0xcd58;
  ovl_0666();
  ovl_111e();
  G_p07flg = 0;
  OV_0x122f = 0;
  G_txtptr = &OV_0x127;
  G_txtptr+2 = 0x1000;
  OV_0x3cd = 0;
  iVar9 = G_crecptrs+46;
  pbVar1 = (byte *)(iVar9 + 5);
  *pbVar1 = *pbVar1 | 8;
  *(undefined2 *)(iVar9 + 1) = 0xffff;
  iVar9 = G_crecptrs+44;
  pbVar1 = (byte *)(iVar9 + 5);
  *pbVar1 = *pbVar1 | 8;
  *(undefined2 *)(iVar9 + 1) = 0xffff;
  iVar9 = G_savebx;
  do {
    ovl_10f0();
    if ((G_rec1+5 & 8) == 0) {
      G_rec1+30 = 0;
      G_rec1+14 = 0;
      bVar3 = G_rec1+5;
      G_rec1+5 = bVar3 & 0x9f;
      if (((bVar3 & 0x10) != 0) && (bVar11 = G_endcmbt < 2, bVar11)) {
        ovl_0fc0();
        if (bVar11) goto L_042c;
        G_rec1+5 = bVar3 & 0x8f;
        OV_0x126 = 0;
        iVar9 = OV_0x3cd << 1;
        while( true ) {
          uStack_8 = (uint)*(byte *)(*(int *)(iVar9 + &G_exitdir) * 2 + &OV_0x116);
          puVar6 = (undefined2 *)(G_savebx + 0x24c);
          EXE_viaptr_puVar6(0x1000);
          bVar11 = (undefined1 *)0xfffb < &uStack_8;
          uVar7 = ovl_0607();
          if (!bVar11) break;
          iVar9 = OV_0x3cd * 2;
          piVar2 = (int *)(iVar9 + &G_exitdir);
          *piVar2 = *piVar2 + -1;
          if (*piVar2 < 0) {
            if (OV_0x126 == '\x01') break;
            *(undefined2 *)(iVar9 + &G_exitdir) = 3;
            OV_0x126 = 1;
          }
        }
        iVar9 = G_savebx;
        G_rec1+1 = uVar7;
        LOCK();
        iVar8 = OV_0x3cd;
        OV_0x3cd = iVar9;
        UNLOCK();
        *(undefined1 *)(iVar8 + &G_p1x) = (char)uVar7;
        *(undefined1 *)(iVar8 + &G_p1y) = (char)((uint)uVar7 >> 8);
        LOCK();
        iVar9 = OV_0x3cd;
        OV_0x3cd = iVar8;
        UNLOCK();
      }
      G_rec1 = G_rec1 & 0x9e;
      *(undefined1 *)(*(int *)(OV_0x3cd * 2 + &G_heroptr) + 0xbd) =
           G_rec1;
      iVar8 = OV_0x3cd;
      uVar4 = *(undefined1 *)(iVar8 + &G_savagi);
      iVar10 = *(int *)(iVar8 * 2 + &G_heroptr);
      *(undefined1 *)(iVar10 + 0xd) = *(undefined1 *)(iVar8 + &G_savcrg);
      *(undefined1 *)(iVar10 + 0x11) = uVar4;
      if (G_endcmbt != 4) {
        *(byte *)(iVar10 + 0xa5) = *(byte *)(iVar10 + 0xa5) & 0x3f;
      }
      ovl_10fa();
    }
L_042c:
    OV_0x3cd = OV_0x3cd + 1;
  } while (OV_0x3cd < 6);
  ovl_0682();
  ovl_06af();
  ovl_10f0();
  EXE_SumStat();
  ovl_0728();
  if (G_endcmbt == '\x01') {
    ovl_1049();
    EXE_PrtWrd();
  }
  else if (G_endcmbt != '\x04') goto L_048c;
  G_curphase = 2;
  G_endcmbt = 1;
  iVar9 = G_savebx;
  ovl_072d();
L_048c:
  G_lookprt = 1;
  if ((G_p07flg == '\0') && (1 < G_cmbtyp)) {
    iVar8 = G_curpla;
    if (G_endcmbt == '\x03') {
      iVar8 = 0;
    }
    G_pwinxy =
         *(undefined2 *)(*(int *)(iVar8 * 2 + &G_exitdir) * 2 + &G_hroomrec+5);
  }
  if (((G_endcmbt == '\x03') && (G_locspec == 1)) &&
     (G_ctype == '\0')) {
    G_pwinxy = G_hroomrec+5;
  }
  if ((*(uint *)(G_heroptr + 0xbd) & 0x80) == 0) {
    iVar10 = 0;
    OV_0x3d0 = 0;
    iVar8 = 6;
    do {
      if ((*(int *)(iVar10 + &G_party) != 0xff) &&
         (iVar5 = *(int *)(iVar10 + &G_heroptr), (*(byte *)(iVar5 + 0xbd) & 0x80) != 0)) {
        if (*(char *)(iVar5 + 8) == '\x1a') {
          iVar8 = G_savebx;
          iVar10 = iVar9;
          goto L_04fa;
        }
        G_swass = 4;
        uVar12 = ovl_05a4();
        iVar10 = (int)((ulong)uVar12 >> 0x10);
        if ((int)uVar12 == G_curpla) {
          G_curpla = 0;
        }
      }
      iVar10 = iVar10 + 2;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    EXE_PrtW3();
    EXE_SumStat();
  }
  else {
    iVar10 = &G_member0;
    iVar8 = iVar9;
L_04fa:
    G_othername = iVar10;
    G_othername+2 = unaff_DS;
    ovl_1049();
    EXE_PrtWrd();
    ovl_1049();
    EXE_PrtWrd();
    G_restarting = 0xffff;
  }
  G_swcomb = 0;
  return;
}


// ===== ovl_05a4 @ 1ca8:05a4

undefined4 ovl_05a4(void)

{
  undefined2 in_AX;
  undefined2 in_DX;
  int in_BX;
  int iVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_npcno = (uint)*(byte *)(in_BX + 8);
  iVar1 = G_savebx;
  EXE_LoadOvly(0x1ca8,0x61,*(undefined2 *)(iVar1 + 0x148),*(undefined2 *)(iVar1 + 0x14a));
  G_crossovlycall = *(undefined2 *)(iVar1 + 0x148);
  G_crossovlycall+2 = *(undefined2 *)(iVar1 + 0x14a);
  EXE_crossovlycall();
  EXE_LoadOvly(0x1ca8,6,*(undefined2 *)(iVar1 + 0x148),*(undefined2 *)(iVar1 + 0x14a),iVar1);
  return CONCAT22(in_DX,in_AX);
}


// ===== ovl_0607 @ 1ca8:0607

undefined2 ovl_0607(void)

{
  undefined2 uVar1;
  undefined2 in_AX;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined2 in_stack_00000000;
  
  G_zp_1415 = in_AX;
  uVar1 = G_bkonly;
  G_bkonly = 1;
  ovl_1123(uVar1);
  G_bkonly = in_stack_00000000;
  iVar2 = ovl_063b();
  if (iVar2 != 0) {
    ovl_0655();
  }
  return G_zp_1415;
}


// ===== ovl_063b @ 1ca8:063b

int ovl_063b(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar2 = G_crecptrs;
  iVar1 = 0x18;
  do {
    if ((*(byte *)(iVar2 + 5) & 0x48) == 0) {
      return iVar2;
    }
    iVar2 = iVar2 + 0x21;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return 0;
}


// ===== ovl_0655 @ 1ca8:0655

void ovl_0655(void)

{
  return;
}


// ===== ovl_0666 @ 1ca8:0666

int ovl_0666(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  iVar1 = iRam000004f8 + -0x100;
  *(undefined2 *)(*piRam000004fc + -0x728a) = piRam000004fc;
  return iVar1;
}


// ===== ovl_0682 @ 1ca8:0682

void ovl_0682(void)

{
  int iVar1;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(0x1ca8,5);
  G_scroll = 0;
  G_cursorx = G_cursorx + 0x1c;
  iVar1 = 6;
  do {
    ovl_10c6();
    G_cursorx = G_cursorx + -2;
    G_cursory = G_cursory + 8;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_06af @ 1ca8:06af

void ovl_06af(void)

{
  int iVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  int iVar2;
  
  iVar1 = 0x18;
  iVar2 = G_crecptrs;
  do {
    if (*(char *)(iVar2 + 0xe) != '\0') {
      *(undefined1 *)(iVar2 + 0xe) = 0;
      ovl_108e(iVar2);
      iVar2 = -0x2eb3;
      ovl_1113();
    }
    iVar2 = iVar2 + 0x21;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_0728 @ 1ca8:0728

void ovl_0728(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_072d @ 1ca8:072d

void ovl_072d(void)

{
  undefined2 *puVar1;
  code *pcVar2;
  uint uVar3;
  int iVar4;
  uint in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar5;
  undefined4 uVar6;
  uint uStack0006;
  
  G_corpsexfer = 0;
  pcVar2 = INT_0x61_handler;
  (*pcVar2)();
  OV_0x3cf = 1;
  OV_0x3cd = 6;
  OV_0x122d = 0;
  iVar4 = 0x12;
  uStack0006 = in_BX;
  do {
    ovl_08f6();
    OV_0x3cd = OV_0x3cd + '\x01';
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  ovl_164e();
  ovl_0c25();
L_0760:
  G_txtptr = &OV_0x127;
  G_txtptr+2 = 0x1000;
  EXE_InitMap();
  ovl_0728();
L_0774:
  do {
    iVar4 = ovl_0c36();
    if (iVar4 == 0) {
L_089c:
      iVar4 = ovl_0c36();
      bVar5 = false;
      if (iVar4 != 0) {
        ovl_0c87();
        if (bVar5) goto L_0774;
        EXE_IModTxt();
        iVar4 = EXE_SetYN();
        if (iVar4 != 0) goto L_0774;
      }
      ovl_0a06();
      EXE_ClrTxtWnd();
      G_p07flg = 1;
      if (G_cmbtyp < 2) {
        G_p07flg = 0;
        return;
      }
      G_curmpg = 7;
      G_curtils = (uint)G_rmdata+4;
      G_curvar = 0x62;
      return;
    }
    EXE_Menu();
    EXE_InitCom();
    do {
      while( true ) {
        iVar4 = ovl_0c36();
        if (iVar4 == 0) goto L_089c;
        iVar4 = EXE_Parser();
        if (iVar4 == 0xfd) goto L_0760;
        if (iVar4 == 0xfe) goto L_0774;
        if (iVar4 == 0) {
          EXE_UseItem();
          if (G_used != -1) {
            bVar5 = G_used < 0x50;
            if ((G_used != 0x50) || (ovl_129c(), bVar5)) {
              EXE_NoUse();
            }
            else {
              G_used = 0xff;
            }
          }
          goto L_0760;
        }
        if (iVar4 == 1) {
          EXE_RecSpl();
          goto L_0774;
        }
        if (iVar4 == 2) {
          EXE_Magic();
          goto L_0774;
        }
        if (iVar4 == 3) goto L_089c;
        uVar3 = EXE_RMove();
        if (uVar3 != 1) break;
        uVar6 = EXE_ChkDoor();
        if ((int)uVar6 != 0) {
          LOCK();
          uVar3 = G_curpla;
          G_curpla = uStack0006;
          UNLOCK();
          *(uint *)(uVar3 * 2 + &G_exitdir) = (uint)((ulong)uVar6 >> 0x10) & 0xff;
          bVar5 = false;
          LOCK();
          uStack0006 = G_curpla;
          G_curpla = uVar3 & 0x7fff;
          UNLOCK();
          goto L_0842;
        }
        EXE_GameSound();
      }
      bVar5 = uVar3 < 2;
    } while (uVar3 != 2);
L_0842:
    ovl_0c87();
    if (!bVar5) {
      ovl_1049();
      puVar1 = (undefined2 *)(uStack0006 + 0x108);
      uStack0006 = 0x1000;
      iVar4 = EXE_viaptr_puVar1();
      if (iVar4 == 0) {
        EXE_slot0x105c();
        ovl_0a06();
        return;
      }
    }
  } while( true );
}


// ===== ovl_08f6 @ 1ca8:08f6

void ovl_08f6(void)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  undefined2 uVar5;
  uint uVar6;
  char *pcVar7;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  char cVar8;
  
  ovl_10f5();
  if ((G_rec2+5 & 0x18) != 0) {
    return;
  }
  if (G_rec2+3 == '\x1c') {
    G_events+18 = G_events+18 | 0x40;
    if ((G_rec2+5 & 0x80) != 0) {
      G_events+7 = G_events+7 | 0x20;
    }
    return;
  }
  OV_0x3cf = 0;
  if (G_BRIBEAMT < 1) {
    iVar4 = EXE_RndCo(2);
    if (iVar4 == 0) {
      cVar1 = EXE_RndCo(0x14);
      if (10 < (byte)(cVar1 + G_diff)) {
        bVar2 = EXE_RndCo(100);
        iVar4 = (uint)G_rec2+3 * 4;
        if (*(char *)(iVar4 + &OV_0x31e) != '\0') {
          while (*(byte *)(iVar4 + &OV_0x31e) <= bVar2) {
            iVar4 = iVar4 + 1;
          }
          cVar1 = *(char *)(iVar4 + &OV_0x27a);
          for (pcVar7 = (char *)&OV_0x23a; *pcVar7 != -1; pcVar7 = pcVar7 + 3) {
            if (cVar1 == *pcVar7) {
              cVar8 = pcVar7[1];
              cVar3 = EXE_RndCo((byte)(pcVar7[2] - cVar8) + 1,in_BX);
              uVar6 = CONCAT11(cVar1,cVar3 + cVar8);
              goto L_09e5;
            }
          }
          uVar6 = CONCAT11(cVar1,1);
          goto L_09e5;
        }
      }
      uVar6 = 0;
    }
    else {
      uVar5 = EXE_RndCo(6);
      uVar6 = CONCAT11((char)((uint)uVar5 >> 8),(char)uVar5 + '\x05');
    }
  }
  else {
    LOCK();
    uVar6 = G_BRIBEAMT;
    G_BRIBEAMT = 0;
    UNLOCK();
  }
L_09e5:
  bVar2 = (byte)(uVar6 >> 8);
  G_rec2+25 = CONCAT11((char)uVar6,bVar2);
  OV_0x122d =
       OV_0x122d +
       *(int *)(G_lootvalptr + (uint)bVar2 * 2) * (uVar6 & 0xff);
  ovl_10ff();
  return;
}


// ===== ovl_0a06 @ 1ca8:0a06

void ovl_0a06(void)

{
  int iVar1;
  uint uVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 uVar3;
  undefined2 unaff_DS;
  
  uVar3 = 0x1ca8;
  do {
    iVar1 = ovl_0c5f();
    if (iVar1 == 0) {
      return;
    }
    ovl_1049();
    iVar1 = EXE_SetYN();
    if (iVar1 != 0) {
      return;
    }
    ovl_1049();
    do {
      uVar2 = EXE_HeroSel(uVar3);
      if (uVar2 == 0xffff) {
        return;
      }
      in_BX = G_savebx;
    } while ((*(byte *)(*(int *)((uVar2 & 0xff) * 2 + &G_crecptrs) + 5) & 0x80) != 0);
    G_crossovlycall = *(int *)(in_BX + 0x148) + 6;
    G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
    EXE_crossovlycall();
    ovl_0a78();
    uVar3 = 0x1000;
  } while (OV_0x3cf != '\x01');
  return;
}


// ===== ovl_0a78 @ 1ca8:0a78

undefined2 ovl_0a78(int param_1)

{
  undefined2 uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int in_BX;
  int iVar6;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(0x1ca8,1);
  uVar3 = 6;
  do {
    ovl_10f5();
    if (((G_rec2+5 & 0x18) == 0) && (G_rec2+4 != '\0')) {
      ovl_0f67(*(undefined2 *)(uVar3 * 2 + &G_crecptrs),uVar3);
      iVar6 = G_savebx;
      EXE_ClrTxtWnd(0x1ca8);
      EXE_InitScrap(0x1ca8);
      EXE_AddScrap(0x1ca8,G_comtxtptr);
      ovl_10b9(uVar3);
      ovl_0ce0();
      EXE_AddScrap(0x1ca8,G_comtxtptr);
      uVar1 = G_rec2+25;
      if ((char)((uint)uVar1 >> 8) == '\0') {
        EXE_AddScrap(0x1ca8,G_comtxtptr);
        EXE_PrtScrap(0x1ca8,0xff);
        G_animoff = 1;
        uVar3 = 0;
        EXE_PrtWrd(0x1ca8,G_comtxtptr);
        G_animoff = 0;
      }
      else {
        EXE_AddScrap(0x1ca8,G_comtxtptr);
        EXE_PrtScrap(0x1ca8,0xff);
        if (G_cursorx != G_txtwx) {
          EXE_MyRet(0x1ca8);
        }
        EXE_InitScrap(0x1ca8);
        EXE_PrtTreasure(0x1ca8,uVar1);
        G_animoff = 1;
        EXE_PrtWrd(0x1ca8,G_comtxtptr);
        G_animoff = 0;
        G_ATTHEROPTR =
             *(undefined2 *)(G_curpla * 2 + &G_heroptr);
        uVar4 = G_rec2+25;
        if ((8 < (byte)uVar4) && ((byte)uVar4 < 0x31)) {
          cVar2 = EXE_RndCo(0x1ca8,0x14);
          uVar4 = CONCAT11(cVar2 + -0x80,G_rec2+25);
        }
        uVar3 = uVar4 >> 8;
        iVar5 = EXE_IncObj(0x1ca8,G_ATTHEROPTR,uVar4 & 0xff);
        if (iVar5 == 0) {
          G_animoff = 1;
          EXE_PrtWrd(0x1ca8,G_comtxtptr);
          G_animoff = 0;
          uVar1 = *(undefined2 *)(param_1 * 2 + &G_crecptrs);
          ovl_0f89();
          return uVar1;
        }
      }
      G_rec2+25 = 0;
      ovl_10ff();
      ovl_0f89(*(undefined2 *)(uVar3 * 2 + &G_crecptrs));
    }
    uVar3 = uVar3 + 1;
    if (uVar3 == 0x18) {
      OV_0x3cf = 1;
      return 0x18;
    }
  } while( true );
}


// ===== ovl_0c25 @ 1ca8:0c25

void ovl_0c25(void)

{
  int iVar1;
  
  iVar1 = ovl_0c36();
  if (iVar1 != 0) {
    ovl_1049();
  }
  return;
}


// ===== ovl_0c36 @ 1ca8:0c36

undefined2 ovl_0c36(void)

{
  char in_AL;
  int iVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = 0x18;
  iVar2 = G_crecptrs;
  while (((*(char *)(iVar2 + 4) != in_AL || ((*(byte *)(iVar2 + 5) & 0x18) != 0)) ||
         ((*(byte *)(iVar2 + 5) & 0x80) == 0))) {
    iVar2 = iVar2 + 0x21;
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 1;
}


// ===== ovl_0c5f @ 1ca8:0c5f

undefined2 ovl_0c5f(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (OV_0x3cf != '\x01') {
    iVar1 = 0x18;
    iVar2 = G_crecptrs;
    do {
      if ((*(char *)(iVar2 + 4) == '\x01') && ((*(byte *)(iVar2 + 5) & 0x18) == 0)) {
        return 1;
      }
      iVar2 = iVar2 + 0x21;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return 0;
}


// ===== ovl_0c87 @ 1ca8:0c87

void ovl_0c87(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined2 in_stack_00000000;
  
  iVar4 = 5;
  iVar5 = G_heroptr+2;
  do {
    if ((*(byte *)(iVar5 + 0xbd) & 0x80) != 0) {
      iVar3 = ovl_1128();
      if (iVar3 != 0) {
        uVar1 = G_curpla;
        G_curpla = 0;
        puVar2 = (undefined2 *)(G_savebx + 0x13c);
        EXE_viaptr_puVar2(0x1ca8,iVar3,iVar5,uVar1);
        ovl_1049();
        G_curpla = in_stack_00000000;
        return;
      }
    }
    iVar5 = iVar5 + 0xdc;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}


// ===== ovl_0ce0 @ 1ca8:0ce0

undefined2 ovl_0ce0(void)

{
  char *pcVar1;
  undefined2 uVar2;
  int iVar3;
  int unaff_SI;
  int unaff_DI;
  char *pcVar4;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  pcVar4 = (char *)&OV_0xddb;
  iVar3 = 5;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
    in_ZF = G_rec2+3 == *pcVar1;
  } while (!(bool)in_ZF);
  uVar2 = 0xa8;
  if ((bool)in_ZF) {
    uVar2 = 0xa9;
  }
  return uVar2;
}


// ===== ovl_0eaf @ 1ca8:0eaf

void ovl_0eaf(void)

{
  uint uVar1;
  undefined2 uVar2;
  char cVar4;
  int iVar3;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined2 uVar5;
  
  EXE_ClrTxtWnd(0x1ca8);
  EXE_InitScrap(0x1ca8);
  EXE_AddScrap(0x1ca8,(int)G_txtptr,
             (int)((ulong)G_txtptr >> 0x10),4);
  uVar1 = G_rec2+25;
  cVar4 = (char)(uVar1 >> 8);
  if (cVar4 != '\0') {
    uVar2 = *(undefined2 *)(G_curpla * 2 + &G_heroptr);
    uVar5 = G_suppresstext;
    G_suppresstext = 1;
    iVar3 = EXE_IncObj(0x1ca8,uVar2,uVar1 & 0xff,cVar4);
    G_suppresstext = uVar5;
    if (iVar3 != 0) {
      G_scrapptr = G_scrapptr + -1;
      EXE_AddScrap(0x1ca8,(int)G_txtptr,
                 (int)((ulong)G_txtptr >> 0x10),5);
      EXE_PrtTreasure(0x1ca8,G_rec2+25);
      goto L_0f35;
    }
  }
  EXE_PrtScrap(0x1ca8,0xff);
L_0f35:
  EXE_PrtWrd(0x1ca8,G_comtxtptr);
  G_rec2+5 = G_rec2+5 | 0x10;
  LOCK();
  uVar1 = G_rec2+1;
  G_rec2+1 = 0xffff;
  UNLOCK();
  EXE_RestBG(0x1ca8,uVar1 & 0xff,uVar1 >> 8,in_BX);
  ovl_10ff();
  return;
}


// ===== ovl_0f67 @ 1ca8:0f67

void __cdecl16near ovl_0f67(int param_1)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x128);
  EXE_viaptr_puVar1(0x1ca8,*(uint *)(param_1 + 1) & 0xff,*(uint *)(param_1 + 1) >> 8,0x14,
                     G_savebx);
  return;
}


// ===== ovl_0f89 @ 1ca8:0f89

void __cdecl16near ovl_0f89(int param_1)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  int iVar2;
  
  puVar1 = (undefined2 *)(G_savebx + 0x120);
  EXE_viaptr_puVar1(0x1ca8,*(uint *)(param_1 + 1) & 0xff,*(uint *)(param_1 + 1) >> 8,
                     G_savebx);
  iVar2 = G_savebx;
  EXE_PDraw(0x1ca8,*(undefined1 *)(param_1 + 0x1f));
  EXE_PageFlip(0x1ca8,iVar2);
  return;
}


// ===== ovl_0fc0 @ 1ca8:0fc0

void ovl_0fc0(char param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_10b9();
  iVar3 = *(int *)((uint)G_rec1+31 * 2 + &G_heroptr);
  if (*(char *)(iVar3 + 0xb8) == '\x01') {
    cVar1 = *(char *)(iVar3 + 0xd2) + *(char *)(iVar3 + 0x12);
    cVar2 = cVar1 + -0x14;
    if (cVar1 < '\x14') {
      cVar2 = '\0';
    }
    *(char *)(iVar3 + 0xd2) = cVar2;
    if (cVar2 < ')') {
      cVar1 = ovl_10a8();
      if (param_1 <= cVar1) {
        cVar1 = ovl_10a8();
        if (*(char *)(iVar3 + 0x12) <= cVar1) {
          iVar3 = G_savebx;
          ovl_1049();
          EXE_PrtWrd(0x1ca8,G_comtxtptr);
          G_swass = 3;
          ovl_05a4();
          *(undefined2 *)((uint)G_rec1+31 * 2 + &G_party) = 0xff;
          return;
        }
      }
    }
  }
  return;
}


// ===== ovl_1049 @ 1ca8:1049

void ovl_1049(void)

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


// ===== ovl_108e @ 1ca8:108e

void ovl_108e(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x100);
  EXE_viaptr_puVar1(0x1ca8);
  return;
}


// ===== ovl_10a8 @ 1ca8:10a8

void ovl_10a8(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x134);
  EXE_viaptr_puVar1(0x1ca8);
  return;
}


// ===== ovl_10b5 @ 1ca8:10b5

void ovl_10b5(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x1d0);
  EXE_viaptr_puVar1(0x1ca8,G_curtar);
  return;
}


// ===== ovl_10b9 @ 1ca8:10b9

void ovl_10b9(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x1d0);
  EXE_viaptr_puVar1(0x1ca8);
  return;
}


// ===== ovl_10c6 @ 1ca8:10c6

void ovl_10c6(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x8c);
  EXE_viaptr_puVar1(0x1ca8);
  return;
}


// ===== ovl_10f0 @ 1ca8:10f0

void ovl_10f0(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0xf;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_10f5 @ 1ca8:10f5

void ovl_10f5(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0x12;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_10fa @ 1ca8:10fa

void ovl_10fa(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0x15;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_10ff @ 1ca8:10ff

void ovl_10ff(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0x18;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_1113 @ 1ca8:1113

void ovl_1113(void)

{
  ovl_10d3();
  return;
}


// ===== ovl_111e @ 1ca8:111e

void ovl_111e(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_1123 @ 1ca8:1123

void ovl_1123(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_1128 @ 1ca8:1128

void ovl_1128(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_129c @ 1ca8:129c

void ovl_129c(void)

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
  G_txtptr = &OV_0x1239;
  G_txtptr+2 = 0x1ca8;
  if (G_used == 'P') {
    EXE_SetTxtObj(0x1ca8,0x50);
    iVar6 = EXE_Mark(0x1ca8,&G_lookdata,0x2a);
    if (iVar6 == -1) {
      EXE_ClrTxtWnd(0x1ca8,in_BX);
      return;
    }
    LOCK();
    cVar2 = G_lookdata;
    G_lookdata = -1;
    UNLOCK();
    if (cVar2 != '\x1f') {
      return;
    }
    iVar6 = EXE_ChkRng(0x1ca8,G_lookdata+2 & 0xff,
                       G_lookdata+2 >> 8,1,1);
    if (iVar6 == 0) {
      return;
    }
    EXE_InitScrap(0x1ca8);
    iVar6 = ovl_184d();
    if (iVar6 != 0) {
      EXE_AddScrap(0x1ca8,(int)G_txtptr,
                 (int)((ulong)G_txtptr >> 0x10),0);
      goto L_15a1;
    }
    uVar7 = 0x1000;
    if (OV_0x122f == '\0') {
      iVar6 = *(int *)(G_curpla * 2 + &G_heroptr);
      bVar3 = (*(byte *)(iVar6 + 0xf) >> 1) + (char)*(undefined2 *)(iVar6 + 0x21);
      if (0x62 < bVar3) {
        bVar3 = 99;
      }
      OV_0x1230 = bVar3;
      bVar3 = EXE_RndCo(100);
      if (OV_0x1230 <= bVar3) {
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
      OV_0x122f = 1;
      iVar6 = EXE_RndCo(4);
      if ((iVar6 == 0) &&
         (bVar3 = EXE_RndCo(0x78),
         OV_0x1230 < bVar3)) {
        EXE_AddScrap((int)G_txtptr,
                   (int)((ulong)G_txtptr >> 0x10),2);
        uVar4 = (uint)(G_hroomrec & 1);
        OV_0x1235 = uVar4;
        EXE_AddScrap((int)G_txtptr,
                   (int)((ulong)G_txtptr >> 0x10),uVar4 + 3);
        EXE_PrtScrap(0xff);
        EXE_GameSound(OV_0x1235 + 0x17);
        EXE_PrtWrd(G_comtxtptr);
        EXE_InitScrap();
        EXE_ClrTxtWnd();
        LOCK();
        iVar6 = OV_0x1235;
        OV_0x1235 = in_BX;
        UNLOCK();
        bVar3 = *(byte *)(iVar6 + &OV_0x1237);
        LOCK();
        uVar7 = 0x1000;
        in_BX = OV_0x1235;
        OV_0x1235 = iVar6;
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
      goto L_150b;
    }
    puVar1 = (undefined2 *)(in_BX + 0xe8);
    in_BX = 0;
    EXE_viaptr_puVar1(0x1000,(int)G_txtptr,
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
  iVar6 = ovl_184d();
  if (iVar6 == 0) {
L_150b:
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
      ovl_1837();
      iVar6 = EXE_IncObj(uVar7,extraout_DX,G_hroomrec+2 & 0xff);
      if (iVar6 != 0) {
        if (G_hroomrec+2 == '\x1e') {
          G_events+11 = G_events+11 | 0x20;
        }
        OV_0x122d =
             *(int *)(G_lootvalptr + (G_hroomrec+2 & 0xff) * 2) *
             (G_hroomrec+2 >> 8);
        ovl_164e();
        EXE_SetTxtWnd(1);
        EXE_ClrTxtWnd();
        EXE_InitScrap();
        EXE_AddScrap(G_comtxtptr);
        EXE_PrtScrap();
        ovl_1861();
        return;
      }
    }
    return;
  }
L_15a1:
  EXE_AddScrap(uVar7,(int)G_txtptr,
             (int)((ulong)G_txtptr >> 0x10),1);
  EXE_PrtScrap(uVar7,0xff);
  return;
}


// ===== ovl_164e @ 1ca8:164e

void ovl_164e(void)

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
      uVar2 = OV_0x122d + *(int *)(iVar1 + 0xce);
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


// ===== ovl_1837 @ 1ca8:1837

undefined2 ovl_1837(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)*(undefined2 *)(G_curpla * 2 + &G_heroptr);
  uVar2 = *puVar1;
  OV_0x1233 = puVar1;
  return uVar2;
}


// ===== ovl_184d @ 1ca8:184d

void ovl_184d(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_FindBit(0x1ca8,&G_duntre,G_hroomrec);
  return;
}


// ===== ovl_1861 @ 1ca8:1861

void ovl_1861(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SetBit(0x1ca8,&G_duntre,G_hroomrec);
  return;
}


