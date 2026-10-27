// ===== ovl_050c @ 3000:050c

undefined2 ovl_050c(void)

{
  undefined2 in_AX;
  char cVar1;
  
  cVar1 = (char)((uint)in_AX >> 8);
  if (cVar1 == '&') {
    in_AX = INT61_26();
  }
  else if (cVar1 == '\'') {
    in_AX = INT61_27();
  }
  else if (cVar1 == '(') {
    in_AX = INT61_28();
  }
  else if (cVar1 == ')') {
    in_AX = INT61_29();
  }
  else if (cVar1 == '*') {
    in_AX = INT61_2a();
  }
  else if (cVar1 == '\0') {
    in_AX = INT61_00();
  }
  else if (cVar1 == '\x02') {
    in_AX = INT61_02();
  }
  else if (cVar1 == '\x01') {
    in_AX = INT61_01();
  }
  else if (cVar1 == '\x03') {
    in_AX = INT61_03();
  }
  else if (cVar1 == '\x04') {
    in_AX = INT61_04();
  }
  else if (cVar1 == '\x05') {
    in_AX = INT61_05();
  }
  else if (cVar1 == '\a') {
    in_AX = INT61_07();
  }
  else if (cVar1 == ' ') {
    in_AX = INT61_20();
  }
  else if (cVar1 == '!') {
    in_AX = INT61_21();
  }
  else if (cVar1 == '\"') {
    in_AX = INT61_22();
  }
  else if (cVar1 == '#') {
    in_AX = INT61_23();
  }
  else if (cVar1 == '\b') {
    in_AX = INT61_08();
  }
  else if (cVar1 == '\t') {
    in_AX = INT61_09();
  }
  else if (cVar1 == '\n') {
    in_AX = INT61_0a();
  }
  else if (cVar1 == '\v') {
    in_AX = INT61_0b();
  }
  else if (cVar1 == '\f') {
    in_AX = INT61_0c();
  }
  else if (cVar1 == '\r') {
    in_AX = INT61_0d();
  }
  else if (cVar1 == '\x0e') {
    in_AX = INT61_0e();
  }
  else if (cVar1 == '\x0f') {
    in_AX = INT61_0f();
  }
  else if (cVar1 == '\x10') {
    in_AX = INT61_10();
  }
  else if (cVar1 == '\x11') {
    in_AX = INT61_11();
  }
  else if (cVar1 == '\x12') {
    in_AX = INT61_12();
  }
  else if (cVar1 == '\x13') {
    in_AX = INT61_13();
  }
  else if (cVar1 == '\x14') {
    in_AX = INT61_14();
  }
  else if (cVar1 == '\x15') {
    in_AX = INT61_15();
  }
  else if (cVar1 == '\x16') {
    in_AX = INT61_16();
  }
  else if (cVar1 == '\x17') {
    in_AX = INT61_17();
  }
  else if (cVar1 == '\x18') {
    in_AX = INT61_18();
  }
  else if (cVar1 == '\x19') {
    in_AX = INT61_19();
  }
  else if (cVar1 == '\x1a') {
    in_AX = INT61_1a();
  }
  else if (cVar1 == '\x1b') {
    in_AX = INT61_1b();
  }
  else if (cVar1 == '\x06') {
    in_AX = INT61_06();
  }
  else if (cVar1 == '\x1e') {
    in_AX = INT61_1e();
  }
  else if (cVar1 == '\x1d') {
    in_AX = INT61_1d();
  }
  else if (cVar1 == '\x1c') {
    in_AX = INT61_1c();
  }
  else if (cVar1 == '\x1f') {
    in_AX = INT61_1f();
  }
  else if (cVar1 == '@') {
    in_AX = INT61_40();
  }
  else if (cVar1 == 'A') {
    in_AX = INT61_41();
  }
  else if (cVar1 == '$') {
    in_AX = INT61_24();
  }
  else if (cVar1 == 'B') {
    in_AX = INT61_42();
  }
  else if (cVar1 == '`') {
    in_AX = INT61_60();
  }
  else if (cVar1 == -0x80) {
    in_AX = INT61_80();
  }
  else if (cVar1 == '%') {
    in_AX = INT61_25();
  }
  else if (cVar1 == 'C') {
    in_AX = INT61_43();
  }
  else if (cVar1 == 'D') {
    in_AX = INT61_44();
  }
  else if (cVar1 == 'F') {
    in_AX = INT61_46();
  }
  else if (cVar1 == 'E') {
    in_AX = INT61_45();
  }
  else if (cVar1 == 'G') {
    in_AX = INT61_47();
  }
  else if (cVar1 == 'H') {
    in_AX = INT61_48();
  }
  else if (cVar1 == 'I') {
    in_AX = INT61_49();
  }
  else if (cVar1 == 'J') {
    in_AX = INT61_4a();
  }
  else if (cVar1 == '+') {
    in_AX = INT61_2b();
  }
  else if (cVar1 == ',') {
    in_AX = INT61_2c();
  }
  else if (cVar1 == -1) {
    in_AX = INT61_ff();
  }
  return in_AX;
}


// ===== ovl_07da @ 3000:07da

void ovl_07da(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  undefined2 in_stack_00000000;
  
  *(undefined2 *)(G_farstackptr * 2 + &G_vvreturn) = in_stack_00000000;
  (*(code *)G_roomvec)();
                    /* WARNING: Could not recover jumptable at 0x000307fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)*(undefined2 *)(G_farstackptr * 2 + &G_vvreturn))();
  return;
}


// ===== INT61_00 @ 3000:07fe

int INT61_00(void)

{
  char cVar1;
  undefined2 *puVar2;
  undefined1 uVar3;
  char cVar4;
  int iVar5;
  byte bVar6;
  int in_DX;
  uint uVar7;
  int iVar8;
  int unaff_SI;
  int iVar9;
  undefined2 unaff_DS;
  
  G_rec1 = *(undefined1 *)(in_DX + 0xbd);
  G_rec1+10 = (uint)*(byte *)(in_DX + 0xca);
  G_rec1+12 = *(undefined1 *)(in_DX + 0xbb);
  G_rec1+13 = *(undefined1 *)(in_DX + 0xba);
  bVar6 = *(byte *)(in_DX + 0xbf);
  uVar7 = (uint)bVar6;
  if (bVar6 != 0xff) {
    iVar8 = in_DX + uVar7;
    bVar6 = *(byte *)(iVar8 + 0x2b);
    in_DX = iVar8 - uVar7;
  }
  G_rec1+15 = bVar6;
  G_rec1+24 = *(undefined1 *)(in_DX + 0x1a);
  puVar2 = (undefined2 *)(G_savebx + 0x6c);
  uVar3 = EXE_GetWpnSkl(in_DX);
  G_rec1+23 = uVar3;
  cVar4 = '\0';
  iVar8 = 0;
  iVar9 = 0;
  iVar5 = 6;
  do {
    cVar1 = *(char *)(in_DX + iVar9 + 0xc0);
    iVar8 = CONCAT11((char)((uint)iVar8 >> 8),cVar1);
    if (cVar1 != -1) {
      bVar6 = *(byte *)(in_DX + iVar8 + 0x2b);
      iVar8 = iVar9;
      if ((0x1e < bVar6) && (bVar6 < 0x2b)) {
        cVar4 = cVar4 + *(char *)(CONCAT11((char)((uint)iVar5 >> 8),bVar6) +
                                  G_loc+18 + -0x1f);
      }
    }
    iVar9 = iVar9 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  G_rec1+16 = cVar4;
  return in_DX;
}


// ===== INT61_2a @ 3000:0890

void INT61_2a(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x120);
  EXE_RestBG(G_rec2+1 & 0xff,G_rec2+1 >> 8,
                     G_savebx);
  return;
}


// ===== INT61_29 @ 3000:0896

void INT61_29(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x120);
  EXE_RestBG(G_rec1+1 & 0xff,G_rec1+1 >> 8,
                     G_savebx);
  return;
}


// ===== INT61_28 @ 3000:08b4

void INT61_28(void)

{
  ovl_08ca();
  return;
}


// ===== INT61_27 @ 3000:08ba

void INT61_27(void)

{
  ovl_08ca();
  return;
}


// ===== ovl_08ca @ 3000:08ca

void ovl_08ca(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x100);
  EXE_PDraw();
  return;
}


// ===== INT61_22 @ 3000:08d7

void INT61_22(void)

{
  undefined2 *puVar1;
  undefined1 in_DL;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x1cc);
  EXE_OrTile(in_DL,G_TILEXY & 0xff,
                     G_TILEXY >> 8);
  return;
}


// ===== INT61_23 @ 3000:08f2

int __cdecl16near INT61_23(void)

{
  int iVar1;
  int in_DX;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar2 = G_crecptrs;
  iVar1 = 0x18;
  do {
    if (in_DX == *(int *)(iVar2 + 1)) break;
    iVar2 = iVar2 + 0x21;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return 0x18 - iVar1;
}


// ===== INT61_2b @ 3000:090b

undefined1 __cdecl16near INT61_2b(void)

{
  int *piVar1;
  byte *pbVar2;
  undefined2 *puVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  int iVar9;
  byte *pbVar11;
  byte *pbVar10;
  int unaff_SI;
  byte *unaff_DI;
  undefined2 unaff_DS;
  char cVar12;
  byte *pbStack_8;
  
  G_ANIFLAG = 0;
  iVar6 = 0x18;
  pbVar10 = (byte *)G_crecptrs;
  do {
    pbVar11 = pbVar10;
    if ((((G_timestop == '\0') || (pbVar10[4] == 0)) &&
        ((pbVar10[5] & 0x98) == 0)) &&
       (((*pbVar10 & 0x20) == 0 &&
        (iVar7 = iVar6, pbVar8 = pbVar10, ovl_120a(), (char)pbVar8 == '\x04')))) {
      piVar1 = (int *)(iVar6 * 2 + &G_ANIMCLOCK);
      *piVar1 = *piVar1 - G_e_delay;
      pbVar11 = pbVar10;
      if (*piVar1 < 0) {
        iVar9 = 0x18 - iVar6;
        cVar12 = *(char *)(iVar9 + &G_ANIMSTATE);
        pbVar2 = (byte *)(iVar9 + &G_ANIMSTATE);
        *pbVar2 = *pbVar2 ^ 1;
        puVar3 = (undefined2 *)(G_savebx + 0x1b8);
        cVar4 = EXE_FirsTil(iVar9);
        *(char *)(iVar9 + &G_pltilno) = cVar4 + cVar12;
        ovl_07da(pbVar10,iVar7,unaff_DI);
        G_ANIFLAG = 1;
        puVar3 = (undefined2 *)(G_savebx + 0x134);
        uVar5 = EXE_RndCo(6);
        *(int *)(iVar6 * 2 + &G_ANIMCLOCK) = (uVar5 & 0xff) * 10;
        unaff_DI = pbStack_8;
        pbStack_8 = pbVar10;
      }
    }
    pbVar10 = pbVar11 + 0x21;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  return G_ANIFLAG;
}


// ===== INT61_20 @ 3000:09ee

void INT61_20(void)

{
  int iVar1;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar1 = G_curatt * 2;
  ovl_120a(*(undefined2 *)(iVar1 + &G_crecptrs));
  (*(code *)(*(int *)(iVar1 * 2 + &OV_0xb2a) + unaff_DI))();
  return;
}


// ===== INT61_21 @ 3000:0a0c

void INT61_21(void)

{
  int iVar1;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar1 = G_curatt * 2;
  ovl_120a(*(undefined2 *)(iVar1 + &G_crecptrs));
  (*(code *)(*(int *)(iVar1 * 2 + &OV_0xb40) + unaff_DI))();
  return;
}


// ===== ovl_0a57 @ 3000:0a57

void ovl_0a57(void)

{
  undefined1 uVar1;
  int iVar2;
  undefined2 uVar3;
  undefined2 *puVar4;
  int extraout_DX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  puVar4 = (undefined2 *)(G_savebx + 0x1b8);
  EXE_FirsTil(G_curatt);
  uVar1 = *(undefined1 *)
           (*(int *)(G_CURDIR * 2 + &OV_0xade) + extraout_DX);
  iVar2 = G_curatt;
  OV_0xb56 = *(undefined1 *)(iVar2 + &G_pltilno);
  *(undefined1 *)(iVar2 + &G_pltilno) = uVar1;
  INT61_29();
  ovl_08ca();
  if (G_wpnt - 1U < 2) {
    uVar3 = G_zp_10;
    G_TILEXY = uVar3;
    G_WEAPXY = uVar3;
    if (5 < G_CURDIR) {
      G_TILEY = G_TILEY + -1;
      G_WEAPXY+1 = G_WEAPXY+1 + -1;
    }
    INT61_22();
  }
  return;
}


// ===== INT61_2c @ 3000:0d76

undefined1 INT61_2c(void)

{
  uint in_DX;
  int unaff_DI;
  
  return *(undefined1 *)(ulong)(&OV_0xe4c + (in_DX & 0xff));
}


// ===== INT61_08 @ 3000:0d7f

void INT61_08(void)

{
  bool bVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar3 = 0x12;
  iVar5 = G_crecptrs+12;
  do {
    if ((*(char *)(iVar5 + 4) == '\x01') &&
       (((*(byte *)(iVar5 + 5) & 0x98) == 0 || ((*(byte *)(iVar5 + 5) & 0x82) == 0x82)))) {
      iVar5 = &G_crecs;
      uVar4 = 0x18;
      bVar1 = false;
      uVar2 = 0;
      goto L_0db5;
    }
    iVar5 = iVar5 + 0x21;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uVar2 = 1;
  goto L_0ddc;
L_0db5:
  do {
    if (*(char *)(iVar5 + 4) == '\0') {
      if ((*(byte *)(iVar5 + 5) & 0x98) == 0) goto L_0ddc;
      if ((0x12 < uVar4) && ((*(byte *)(iVar5 + 5) & 0x88) == 0)) {
        bVar1 = true;
      }
    }
    iVar5 = iVar5 + 0x21;
    uVar4 = uVar4 - 1;
  } while (uVar4 != 0);
  uVar2 = 3;
  if (!bVar1) {
    uVar2 = 2;
  }
L_0ddc:
  G_endcmbt = uVar2;
  return;
}


// ===== INT61_1c @ 3000:0de5

void INT61_1c(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 in_BX;
  int iVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x54);
  EXE_SetTxtWnd(5);
  G_scroll = 0;
  G_cursorx = G_cursorx + 0x1c;
  iVar4 = &G_crecs;
  iVar3 = 6;
  do {
    uVar2 = 0x17;
    if ((*(char *)(iVar4 + 0x1e) != '\0') && ((*(byte *)(iVar4 + 5) & 0xc0) == 0)) {
      uVar2 = 0x18;
    }
    puVar1 = (undefined2 *)(G_savebx + 0x8c);
    EXE_MyCout(uVar2);
    G_cursorx = G_cursorx + -2;
    G_cursory = G_cursory + 8;
    iVar4 = iVar4 + 0x21;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  puVar1 = (undefined2 *)(G_savebx + 0x54);
  EXE_SetTxtWnd(1,in_BX);
  return;
}


// ===== ovl_0e43 @ 3000:0e43

int ovl_0e43(int param_1)

{
  undefined2 *puVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  
  iVar2 = ovl_0e8f();
  if (((bool)in_CF) || (G_curtar == 0x18)) {
    return param_1;
  }
  if (iVar2 == 0) {
    ovl_0fc0();
    ovl_0f64();
    puVar1 = (undefined2 *)(G_savebx + 0x338);
    iVar2 = EXE_AutoPause();
    return iVar2;
  }
  return iVar2;
}


// ===== ovl_0e5b @ 3000:0e5b

undefined2 ovl_0e5b(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  undefined2 in_stack_00000000;
  
  puVar1 = (undefined2 *)(G_savebx + 0x208);
  uVar2 = EXE_SpelTarg();
  if (((bool)in_CF) || (G_curtar == 0x18)) {
    return in_stack_00000000;
  }
  return uVar2;
}


// ===== ovl_0e8f @ 3000:0e8f

void ovl_0e8f(void)

{
  undefined2 *puVar1;
  undefined1 uVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  
  puVar1 = (undefined2 *)(G_savebx + 0x208);
  EXE_SpelTarg();
  if ((bool)in_CF) {
    return;
  }
  if (G_curtar == 0x18) {
    return;
  }
  uVar2 = INT61_43();
  G_deftxtparms+2 = uVar2;
  return;
}


// ===== ovl_0eae @ 3000:0eae

void ovl_0eae(void)

{
  byte bVar1;
  char cVar2;
  undefined2 uVar3;
  char cVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar3 = INT61_01();
  cVar4 = (char)((uint)uVar3 >> 8);
  bVar1 = (byte)uVar3 >> 3;
  cVar2 = bVar1 - cVar4;
  if ((char)bVar1 < cVar4) {
    cVar2 = '\0';
  }
  G_deftxtparms+2 = cVar2;
  return;
}


// ===== INT61_43 @ 3000:0ecf

char __cdecl16near INT61_43(void)

{
  byte bVar1;
  char cVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  bVar1 = INT61_01();
  cVar2 = (bVar1 >> 3) - G_rec2+21;
  if ((char)(bVar1 >> 3) < G_rec2+21) {
    cVar2 = '\0';
  }
  return cVar2;
}


// ===== ovl_0ee1 @ 3000:0ee1

void ovl_0ee1(void)

{
  INT61_43();
  return;
}


// ===== INT61_02 @ 3000:0ef4

void INT61_02(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar1 = 200;
  iVar2 = 0;
  do {
    *(undefined2 *)(iVar2 + &G_bangstg) = 5;
    iVar2 = iVar2 + 2;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  OV_0x1337 = 0;
  return;
}


// ===== INT61_01 @ 3000:0f10

undefined1 __cdecl16near INT61_01(void)

{
  int iVar1;
  undefined1 uVar2;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar2 = G_rec1+24;
  if (G_rec1+31 < 6) {
    LOCK();
    iVar1 = G_ATTHEROPTR;
    G_ATTHEROPTR = in_BX;
    UNLOCK();
    if ((*(byte *)(iVar1 + 0xa5) & 8) != 0) {
      uVar2 = 99;
      *(byte *)(iVar1 + 0xa5) = *(byte *)(iVar1 + 0xa5) & 0xf7;
    }
    LOCK();
    G_ATTHEROPTR = iVar1;
    UNLOCK();
  }
  return uVar2;
}


// ===== INT61_07 @ 3000:0f34

void INT61_07(void)

{
  undefined2 *puVar1;
  uint uVar2;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_egaeffectstimer = 1;
  uVar2 = ovl_1f3d();
  puVar1 = (undefined2 *)(G_savebx + 0x2f8);
  EXE_movectileFX(*(undefined1 *)(G_curtar + &G_pltilno),
                     uVar2 & 0xff,uVar2 >> 8,in_BX);
  return;
}


// ===== ovl_0f64 @ 3000:0f64

void __cdecl16near ovl_0f64(void)

{
  undefined2 *puVar1;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined2 uVar2;
  
  uVar2 = 0xff;
  puVar1 = (undefined2 *)(G_savebx + 0x54);
  EXE_SetTxtWnd(1);
  puVar1 = (undefined2 *)(G_savebx + 0x5c);
  EXE_ClrTxtWnd(in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0xe4);
  EXE_InitScrap(in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap(G_comtxtptr);
  puVar1 = (undefined2 *)(G_savebx + 0xec);
  EXE_PrtScrap(uVar2,in_BX);
  return;
}


// ===== ovl_0fac @ 3000:0fac

void ovl_0fac(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x204);
  EXE_Spef1();
  return;
}


// ===== ovl_0fbc @ 3000:0fbc

void ovl_0fbc(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x1d0);
  EXE_SetName(G_curtar);
  return;
}


// ===== ovl_0fc0 @ 3000:0fc0

void __cdecl16near ovl_0fc0(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x1d0);
  EXE_SetName();
  return;
}


// ===== INT61_80 @ 3000:0fcd

void INT61_80(void)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  undefined2 uVar4;
  int unaff_SI;
  undefined2 unaff_DI;
  undefined2 unaff_DS;
  
  iVar2 = 99;
  iVar3 = 0;
  do {
    ovl_07da(G_savebx,iVar2,unaff_DI,iVar2,iVar3);
    iVar3 = iVar3 + 2;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  uVar4 = G_savebx;
  puVar1 = (undefined2 *)(G_savebx + 0x80);
  EXE_NPCDraw(uVar4);
  if (G_needpalette != '\0') {
    puVar1 = (undefined2 *)(G_savebx + 0x330);
    EXE_VGAPalette((int)G_mtileix,
                       (int)((ulong)G_mtileix >> 0x10),uVar4);
  }
  puVar1 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip(uVar4);
  return;
}


// ===== INT61_0c @ 3000:102c

void INT61_0c(void)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  int iVar4;
  undefined2 uVar5;
  
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(0xb);
  iVar2 = 0x17;
  iVar3 = G_crecptrs+46;
  do {
    if (((*(byte *)(iVar3 + 5) & 0x98) == 0) && (*(char *)(iVar3 + 0xe) == '\0')) {
      iVar4 = iVar3;
      ovl_0fc0();
      puVar1 = (undefined2 *)(G_savebx + 0x54);
      EXE_SetTxtWnd(1);
      puVar1 = (undefined2 *)(G_savebx + 0x5c);
      EXE_ClrTxtWnd();
      puVar1 = (undefined2 *)(G_savebx + 0xe4);
      EXE_InitScrap();
      ovl_120a();
      puVar1 = (undefined2 *)(G_savebx + 0xe8);
      EXE_AddScrap(G_comtxtptr);
      puVar1 = (undefined2 *)(G_savebx + 0xec);
      EXE_PrtScrap(0xff,iVar3);
      puVar1 = (undefined2 *)(G_savebx + 0x40);
      EXE_MyRet(iVar3);
      G_deftxtparms = *(undefined2 *)(iVar4 + 10);
      puVar1 = (undefined2 *)(G_savebx + 0xe4);
      iVar3 = iVar4;
      EXE_InitScrap(iVar4);
      puVar1 = (undefined2 *)(G_savebx + 0xe8);
      EXE_AddScrap(G_comtxtptr);
      puVar1 = (undefined2 *)(G_savebx + 0xec);
      EXE_PrtScrap(0xff,iVar4);
      puVar1 = (undefined2 *)(G_savebx + 0x40);
      EXE_MyRet(iVar4);
      G_deftxtparms+2 = *(undefined1 *)(iVar3 + 0x10);
      puVar1 = (undefined2 *)(G_savebx + 0xe4);
      iVar4 = iVar3;
      EXE_InitScrap(iVar3);
      puVar1 = (undefined2 *)(G_savebx + 0xe8);
      EXE_AddScrap(G_comtxtptr);
      puVar1 = (undefined2 *)(G_savebx + 0xec);
      EXE_PrtScrap(0xff,iVar3);
      puVar1 = (undefined2 *)(G_savebx + 0x40);
      EXE_MyRet(iVar3);
      G_deftxtparms+2 = *(undefined1 *)(iVar4 + 0xc);
      puVar1 = (undefined2 *)(G_savebx + 0xe4);
      iVar3 = iVar4;
      EXE_InitScrap(iVar4);
      puVar1 = (undefined2 *)(G_savebx + 0xe8);
      EXE_AddScrap(G_comtxtptr);
      puVar1 = (undefined2 *)(G_savebx + 0xec);
      EXE_PrtScrap(0xff,iVar4);
      ovl_11b0();
      uVar5 = G_animoff;
      G_animoff = 1;
      puVar1 = (undefined2 *)(G_savebx + 0x178);
      EXE_PrtWrd(G_comtxtptr);
      G_animoff = uVar5;
      ovl_11d2();
    }
    iVar3 = iVar3 + -0x21;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 5);
  return;
}


// ===== ovl_11b0 @ 3000:11b0

void __cdecl16near ovl_11b0(int param_1)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x128);
  EXE_MaskChr(*(uint *)(param_1 + 1) & 0xff,*(uint *)(param_1 + 1) >> 8,0x14,param_1);
  return;
}


// ===== ovl_11d2 @ 3000:11d2

void __cdecl16near ovl_11d2(int param_1)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x120);
  EXE_RestBG(*(uint *)(param_1 + 1) & 0xff,*(uint *)(param_1 + 1) >> 8);
  puVar1 = (undefined2 *)(G_savebx + 0x100);
  EXE_PDraw(*(undefined1 *)(param_1 + 0x1f),param_1);
  puVar1 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip(param_1);
  return;
}


// ===== ovl_120a @ 3000:120a

void __cdecl16near ovl_120a(void)

{
  return;
}


// ===== INT61_03 @ 3000:1240

void INT61_03(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  undefined2 in_CX;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined2 in_BX;
  int iVar6;
  int unaff_BP;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined1 uVar7;
  
  OV_0x133b = in_BX;
  INT61_02();
  OV_0x1339 = 0;
  OV_0x133d = 0;
  ovl_07da(in_BX,in_CX);
  iVar6 = G_crecptrs;
  G_curtar = 0;
  INT61_01();
  iVar3 = 0x18;
  do {
    if (*(char *)(iVar3 + &G_pathblk+1) == '\0') {
      puVar1 = (undefined2 *)(G_savebx + 0x5c);
      iVar4 = iVar3;
      EXE_ClrTxtWnd();
      puVar1 = (undefined2 *)(G_savebx + 0xe4);
      EXE_InitScrap();
      uVar7 = 0;
      iVar5 = unaff_BP;
      ovl_07da(*(undefined2 *)(unaff_BP + 0x133b),iVar4,unaff_BP);
      unaff_BP = iVar6;
      iVar6 = 0x12c1;
      uVar2 = ovl_13ee();
      if (!(bool)uVar7) {
        ovl_11b0(iVar6,uVar2);
        ovl_07da(iVar6,iVar5);
        ovl_07da(iVar5);
        ovl_11d2();
      }
    }
    iVar6 = iVar6 + 0x21;
    G_curtar = G_curtar + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


// ===== INT61_04 @ 3000:12f9

void INT61_04(void)

{
  uint uVar1;
  undefined2 *puVar2;
  undefined2 in_CX;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined2 in_BX;
  int unaff_BP;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar6;
  undefined1 auStackY_8a [128];
  int iVar7;
  
  bVar6 = auStackY_8a + 0x88 < (undefined1 *)0x2;
  G_offense = 0;
  puVar2 = (undefined2 *)(G_savebx + 0x208);
  EXE_SpelTarg();
  if (!bVar6) {
    OV_0x133b = in_BX;
    INT61_02();
    puVar2 = (undefined2 *)(G_savebx + 0xd0);
    EXE_GameSound(2,in_BX);
    ovl_07da(in_BX,in_CX);
    uVar1 = G_TILEXY;
    *(uint *)(unaff_BP + 0x133e) = uVar1;
    puVar2 = (undefined2 *)(G_savebx + 0x2c0);
    EXE_BigBang(uVar1 & 0xff,uVar1 >> 8);
    puVar2 = (undefined2 *)(G_savebx + 0x5c);
    EXE_ClrTxtWnd();
    puVar2 = (undefined2 *)(G_savebx + 0xe4);
    EXE_InitScrap();
    INT61_01();
    iVar7 = G_crecptrs+46;
    iVar3 = 0x18;
    do {
      iVar4 = iVar3 + -1;
      G_curtar = iVar4;
      if (((*(byte *)(iVar7 + 5) & 0x98) == 0) && (*(char *)(iVar7 + 0xe) == '\0')) {
        if (((byte)(((char)*(undefined2 *)(iVar7 + 1) - (char)*(undefined2 *)(unaff_BP + 0x133e)) +
                   1U) < 3) &&
           ((byte)(((char)((uint)*(undefined2 *)(iVar7 + 1) >> 8) -
                   (char)((uint)*(undefined2 *)(unaff_BP + 0x133e) >> 8)) + 1U) < 3)) {
          iVar5 = unaff_BP;
          ovl_07da(*(undefined2 *)(unaff_BP + 0x133b),iVar4,unaff_BP);
          unaff_BP = iVar7;
          bVar6 = (bool)((byte)unaff_BP & 1);
          iVar7 = 0x13c6;
          ovl_13ee();
          if (!bVar6) {
            ovl_07da(iVar4,iVar5);
            ovl_07da(iVar5);
          }
        }
      }
      iVar7 = iVar7 + -0x21;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}


// ===== ovl_13ee @ 3000:13ee

void ovl_13ee(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_rec2+3 == ' ') {
    ovl_0f64();
    ovl_30ed();
    return;
  }
  return;
}


// ===== INT61_05 @ 3000:1405

void INT61_05(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 in_BX;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined1 uVar5;
  int iVar6;
  int iStack_2;
  
  OV_0x133d = 0;
  puVar1 = (undefined2 *)(G_savebx + 0x5c);
  EXE_ClrTxtWnd();
  puVar1 = (undefined2 *)(G_savebx + 0xe4);
  EXE_InitScrap();
  OV_0x133b = in_BX;
  iVar4 = G_crecptrs+46;
  iStack_2 = 0x18;
  do {
    G_curtar = iStack_2 + -1;
    if ((((*(byte *)(iVar4 + 5) & 0x98) == 0) && (*(char *)(iVar4 + 0xe) == '\0')) &&
       (uVar2 = CONCAT11((char)((uint)(iStack_2 + -1) >> 8),OV_0x133d),
       *(char *)(iVar4 + 4) != OV_0x133d)) {
      uVar5 = 0;
      iVar3 = unaff_DI;
      ovl_07da(OV_0x133b,uVar2);
      iVar6 = 0x1466;
      ovl_13ee();
      unaff_DI = iVar4;
      if (!(bool)uVar5) {
        ovl_0fac();
        G_rec2+16 = 0;
        G_rec2+12 = 0;
        ovl_07da(uVar2,iVar3,iVar4);
        ovl_0f64();
        iVar6 = G_UserDelay;
        puVar1 = (undefined2 *)(G_savebx + 0x338);
        EXE_AutoPause();
        unaff_DI = iStack_2;
        iStack_2 = iVar3;
      }
      iVar4 = iVar6;
    }
    iVar4 = iVar4 + -0x21;
    iStack_2 = iStack_2 + -1;
  } while (iStack_2 != 0);
  return;
}


// ===== INT61_09 @ 3000:14d7

void INT61_09(undefined2 param_1)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  char cVar3;
  undefined2 *puVar4;
  char cVar5;
  uint uVar6;
  undefined2 in_BX;
  int unaff_SI;
  int iVar7;
  undefined1 *puVar8;
  int unaff_DI;
  undefined1 *puVar9;
  undefined2 unaff_DS;
  undefined1 in_CF;
  byte bVar10;
  byte bVar11;
  byte in_AF;
  byte bVar12;
  byte bVar13;
  byte in_TF;
  byte in_IF;
  byte bVar14;
  byte in_NT;
  undefined4 uVar15;
  
  OV_0x15ac = 1;
  G_offense = 0;
  puVar4 = (undefined2 *)(G_savebx + 0x208);
  EXE_SpelTarg();
  if (((bool)in_CF) || (G_curtar == 0x18)) {
    return;
  }
  if (OV_0x15ac == 1) {
    cVar3 = G_rec2+31;
    bVar14 = SBORROW1(cVar3,'\x06');
    cVar5 = cVar3 + -6;
    bVar13 = cVar5 < '\0';
    bVar12 = cVar5 == '\0';
    bVar11 = (POPCOUNT(cVar5) & 1U) == 0;
    if ('\x05' < cVar3) {
      bVar10 = 1;
      goto L_16bd;
    }
  }
  else {
    cVar3 = *(char *)((uint)G_rec2+3 + &OV_0x15ae);
    bVar14 = SBORROW1(cVar3,-1);
    cVar3 = cVar3 + '\x01';
    bVar13 = cVar3 < '\0';
    bVar12 = cVar3 == '\0';
    bVar11 = (POPCOUNT(cVar3) & 1U) == 0;
    if (!(bool)bVar12) {
      bVar10 = 1;
      goto L_16bd;
    }
  }
  ovl_0eae();
  iVar7 = unaff_SI + OV_0x15ac * -2;
  puVar9 = (undefined1 *)*(undefined2 *)(iVar7 + -0x7a42);
  puVar8 = (undefined1 *)(iVar7 + OV_0x15ac * 2 + -0x7707);
  for (iVar7 = 0x21; iVar7 != 0; iVar7 = iVar7 + -1) {
    puVar2 = puVar9;
    puVar9 = puVar9 + 1;
    puVar1 = puVar8;
    puVar8 = puVar8 + 1;
    *puVar2 = *puVar1;
  }
  INT61_49();
  ovl_0fac(G_zp_1415 >> 8);
  iVar7 = 0x17 - OV_0x15ac;
  if (OV_0x15ac == 1) {
    G_cloneno = (char)G_curtar;
  }
  puVar4 = (undefined2 *)(G_savebx + 0xac);
  EXE_SetPlTilNo(iVar7,in_BX);
  uVar15 = ovl_1f3d();
  G_egadrawcode = 0;
  G_egaeffectstimer = 0x1d4c;
  G_egaeffectsflag = 0xf01;
  uVar6 = (uint)*(byte *)(iVar7 + &G_pltilno);
  puVar4 = (undefined2 *)(G_savebx + 0x2f8);
  EXE_movectileFX(uVar6,(char)uVar15,(char)((ulong)uVar15 >> 8),iVar7,uVar6);
  puVar4 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(9,iVar7);
  uVar15 = ovl_1f3d();
  G_egaeffectsflag = 3;
  puVar4 = (undefined2 *)(G_savebx + 0x2f8);
  EXE_movectileFX(uVar6,(char)uVar15,(char)((ulong)uVar15 >> 8),iVar7);
  puVar4 = (undefined2 *)(G_savebx + 0x120);
  EXE_RestBG(param_1);
  iVar7 = unaff_SI + OV_0x15ac * -2;
  puVar8 = (undefined1 *)*(undefined2 *)(iVar7 + -0x7a42);
  iVar7 = iVar7 + OV_0x15ac * 2;
  if (OV_0x15ac == 1) {
    puVar8[0x1b] = 0xff;
    puVar8[0x1c] = 0xff;
    puVar8[0x19] = 0;
    puVar8[0x1a] = 0;
    puVar8[0x18] = 0;
    puVar8[0x20] = 0;
    puVar8[0x1f] = 0x16;
    puVar8[0xe] = 0;
    puVar8[0x1e] = 1;
    *(undefined2 *)(puVar8 + 1) = *(undefined2 *)(iVar7 + -0x76d0);
    *(int *)(iVar7 + -0x647c) = *(int *)(iVar7 + -0x647c) + 1;
  }
  else {
    *(undefined2 *)(puVar8 + 10) =
         *(undefined2 *)((uint)G_rec2+31 * 2 + &G_MAXHPTS);
    *(undefined2 *)(puVar8 + 1) = *(undefined2 *)(iVar7 + -0x76d0);
    puVar8[0xd] = 99;
    puVar8[7] = 0xff;
    puVar8[0x1f] = 0x17;
    puVar8[0xe] = 0;
    puVar8[4] = 0;
    *puVar8 = 0;
    *(int *)(iVar7 + -0x647c) = *(int *)(iVar7 + -0x647c) + 1;
  }
  puVar4 = (undefined2 *)(*(int *)(iVar7 + -0x728a) + 0x5c);
  EXE_RestBG();
  bVar14 = 0;
  bVar13 = 0;
  bVar12 = 1;
  bVar11 = 1;
  puVar4 = (undefined2 *)(*(int *)(iVar7 + -0x728a) + 600);
  EXE_RestBG();
  bVar10 = 0;
L_16bd:
  ovl_0f64((uint)(in_NT & 1) * 0x4000 | (uint)(bVar14 & 1) * 0x800 | (uint)(in_IF & 1) * 0x200
                | (uint)(in_TF & 1) * 0x100 | (uint)(bVar13 & 1) * 0x80 | (uint)(bVar12 & 1) * 0x40
                | (uint)(in_AF & 1) * 0x10 | (uint)(bVar11 & 1) * 4 | (uint)bVar10);
  INT61_80();
  return;
}


// ===== INT61_0a @ 3000:14e1

void INT61_0a(undefined2 param_1)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  char cVar3;
  undefined2 *puVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  int unaff_SI;
  undefined1 *puVar8;
  int unaff_DI;
  undefined1 *puVar9;
  undefined2 unaff_DS;
  bool bVar10;
  byte bVar11;
  byte bVar12;
  byte in_AF;
  byte bVar13;
  byte bVar14;
  byte in_TF;
  byte in_IF;
  byte bVar15;
  byte in_NT;
  undefined4 uVar16;
  
  OV_0x15ac = 0;
  iVar6 = 0x10;
  uVar7 = G_crecptrs+12;
  while (((*(byte *)(uVar7 + 5) & 8) != 0 ||
         (cVar3 = *(char *)((uint)*(byte *)(uVar7 + 3) + &OV_0x15ae), bVar10 = cVar3 != -1,
         cVar3 != -1))) {
    bVar15 = SCARRY2(uVar7,0x21);
    uVar7 = uVar7 + 0x21;
    bVar14 = (int)uVar7 < 0;
    bVar13 = uVar7 == 0;
    bVar12 = POPCOUNT(uVar7 & 0xff);
    iVar6 = iVar6 + -1;
    if (iVar6 == 0) {
L_1544:
      bVar12 = (bVar12 & 1) == 0;
      bVar11 = 1;
L_16bd:
      ovl_0f64((uint)(in_NT & 1) * 0x4000 | (uint)(bVar15 & 1) * 0x800 |
                    (uint)(in_IF & 1) * 0x200 | (uint)(in_TF & 1) * 0x100 |
                    (uint)(bVar14 & 1) * 0x80 | (uint)(bVar13 & 1) * 0x40 | (uint)(in_AF & 1) * 0x10
                    | (uint)(bVar12 & 1) * 4 | (uint)bVar11);
      INT61_80();
      return;
    }
  }
  G_offense = 0;
  puVar4 = (undefined2 *)(G_savebx + 0x208);
  EXE_SpelTarg(uVar7);
  if ((bVar10) || (G_curtar == 0x18)) {
    return;
  }
  if (OV_0x15ac == 1) {
    cVar3 = G_rec2+31;
    bVar15 = SBORROW1(cVar3,'\x06');
    cVar5 = cVar3 + -6;
    bVar14 = cVar5 < '\0';
    bVar13 = cVar5 == '\0';
    bVar12 = (POPCOUNT(cVar5) & 1U) == 0;
    if ('\x05' < cVar3) {
      bVar11 = 1;
      goto L_16bd;
    }
  }
  else {
    cVar3 = *(char *)((uint)G_rec2+3 + &OV_0x15ae);
    bVar15 = SBORROW1(cVar3,-1);
    cVar3 = cVar3 + '\x01';
    bVar14 = cVar3 < '\0';
    bVar13 = cVar3 == '\0';
    bVar12 = POPCOUNT(cVar3);
    if (!(bool)bVar13) goto L_1544;
  }
  ovl_0eae();
  iVar6 = unaff_SI + OV_0x15ac * -2;
  puVar9 = (undefined1 *)*(undefined2 *)(iVar6 + -0x7a42);
  puVar8 = (undefined1 *)(iVar6 + OV_0x15ac * 2 + -0x7707);
  for (iVar6 = 0x21; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar2 = puVar9;
    puVar9 = puVar9 + 1;
    puVar1 = puVar8;
    puVar8 = puVar8 + 1;
    *puVar2 = *puVar1;
  }
  INT61_49();
  ovl_0fac(G_zp_1415 >> 8);
  iVar6 = 0x17 - OV_0x15ac;
  if (OV_0x15ac == 1) {
    G_cloneno = (char)G_curtar;
  }
  puVar4 = (undefined2 *)(G_savebx + 0xac);
  EXE_SetPlTilNo(iVar6,uVar7);
  uVar16 = ovl_1f3d();
  G_egadrawcode = 0;
  G_egaeffectstimer = 0x1d4c;
  G_egaeffectsflag = 0xf01;
  uVar7 = (uint)*(byte *)(iVar6 + &G_pltilno);
  puVar4 = (undefined2 *)(G_savebx + 0x2f8);
  EXE_movectileFX(uVar7,(char)uVar16,(char)((ulong)uVar16 >> 8),iVar6,uVar7);
  puVar4 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(9,iVar6);
  uVar16 = ovl_1f3d();
  G_egaeffectsflag = 3;
  puVar4 = (undefined2 *)(G_savebx + 0x2f8);
  EXE_movectileFX(uVar7,(char)uVar16,(char)((ulong)uVar16 >> 8),iVar6);
  puVar4 = (undefined2 *)(G_savebx + 0x120);
  EXE_RestBG(param_1);
  iVar6 = unaff_SI + OV_0x15ac * -2;
  puVar8 = (undefined1 *)*(undefined2 *)(iVar6 + -0x7a42);
  iVar6 = iVar6 + OV_0x15ac * 2;
  if (OV_0x15ac == 1) {
    puVar8[0x1b] = 0xff;
    puVar8[0x1c] = 0xff;
    puVar8[0x19] = 0;
    puVar8[0x1a] = 0;
    puVar8[0x18] = 0;
    puVar8[0x20] = 0;
    puVar8[0x1f] = 0x16;
    puVar8[0xe] = 0;
    puVar8[0x1e] = 1;
    *(undefined2 *)(puVar8 + 1) = *(undefined2 *)(iVar6 + -0x76d0);
    *(int *)(iVar6 + -0x647c) = *(int *)(iVar6 + -0x647c) + 1;
  }
  else {
    *(undefined2 *)(puVar8 + 10) =
         *(undefined2 *)((uint)G_rec2+31 * 2 + &G_MAXHPTS);
    *(undefined2 *)(puVar8 + 1) = *(undefined2 *)(iVar6 + -0x76d0);
    puVar8[0xd] = 99;
    puVar8[7] = 0xff;
    puVar8[0x1f] = 0x17;
    puVar8[0xe] = 0;
    puVar8[4] = 0;
    *puVar8 = 0;
    *(int *)(iVar6 + -0x647c) = *(int *)(iVar6 + -0x647c) + 1;
  }
  puVar4 = (undefined2 *)(*(int *)(iVar6 + -0x728a) + 0x5c);
  EXE_RestBG();
  bVar15 = 0;
  bVar14 = 0;
  bVar13 = 1;
  bVar12 = 1;
  puVar4 = (undefined2 *)(*(int *)(iVar6 + -0x728a) + 600);
  EXE_RestBG();
  bVar11 = 0;
  goto L_16bd;
}


// ===== INT61_49 @ 3000:16d6

void INT61_49(void)

{
  undefined2 *puVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  undefined2 uVar5;
  uint uVar6;
  undefined1 uVar7;
  undefined2 in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined2 uStack_8;
  undefined2 uStack_6;
  
  iVar4 = 0;
  if (G_cmbtyp < 2) {
    if (G_cmbtyp != 1) {
      G_zp_1415 = G_rec1+1;
      INT61_25();
      puVar1 = (undefined2 *)(G_savebx + 0x134);
      uVar6 = EXE_RndCo(99,in_BX);
      goto L_1787;
    }
  }
  else {
    iVar4 = (uint)(byte)(G_rmdata+6 - 6) << 1;
  }
  uStack_6 = *(undefined2 *)(iVar4 + &OV_0x17c6);
  uStack_8 = *(undefined2 *)(iVar4 + &OV_0x17ce);
  do {
    puVar1 = (undefined2 *)(G_savebx + 0x134);
    uVar5 = EXE_RndCo((byte)(uStack_8._1_1_ - (char)uStack_8) + 1,in_BX);
    uStack_8._0_1_ = (char)uStack_8 + (char)uVar5;
    puVar1 = (undefined2 *)(G_savebx + 0x134);
    cVar2 = EXE_RndCo(CONCAT11((char)((uint)uVar5 >> 8),
                                               uStack_6._1_1_ - (char)uStack_6) + 1);
    puVar1 = (undefined2 *)(G_savebx + 0x24c);
    uVar6 = EXE_PlacePerson(cVar2 + (char)uStack_6,(char)uStack_8);
    G_zp_1415 = G_rec1+1;
    G_bkonly = 1;
    INT61_25();
    G_bkonly = 0;
    iVar4 = (uVar6 >> 8) * 0xb;
    uVar6 = CONCAT11((char)((uint)iVar4 >> 8),(char)iVar4 + (char)uVar6);
    while (iVar4 = INT61_23(), iVar4 == 0x18) {
      if (*(byte *)(uVar6 + &G_blobmap) < 100) {
        G_zp_1415 = CONCAT11((char)(uVar6 / 0xb),(char)(uVar6 % 0xb));
        return;
      }
      if (G_cmbtyp != '\0') break;
L_1787:
      cVar2 = (char)uVar6;
      uVar7 = (undefined1)(uVar6 >> 8);
      bVar3 = cVar2 + 0x11;
      uVar6 = CONCAT11(uVar7,bVar3);
      if (0x62 < bVar3) {
        uVar6 = CONCAT11(uVar7,cVar2 + -0x52);
      }
    }
  } while( true );
}


// ===== INT61_0b @ 3000:17c9

void __cdecl16near INT61_0b(void)

{
  undefined2 *puVar1;
  bool bVar2;
  byte bVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  char extraout_DL;
  char cVar8;
  char extraout_DH;
  char cVar9;
  undefined2 in_BX;
  int iVar10;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar11;
  char local_4;
  char cStack_3;
  
  bVar11 = (undefined1 *)((int)register0x00000010 + -2) < (undefined1 *)0x6;
  bVar2 = false;
  G_offense = 0;
  puVar1 = (undefined2 *)(G_savebx + 0x208);
  EXE_SpelTarg();
  if (!bVar11) {
    puVar1 = (undefined2 *)(G_savebx + 0xd0);
    EXE_GameSound(10,in_BX);
    uVar5 = G_zp_1415;
    bVar3 = INT61_01();
    cVar8 = extraout_DL;
    cVar9 = extraout_DH;
    if (0x4a < bVar3) {
      uVar5 = CONCAT11((char)((uint)uVar5 >> 8) + -1,(char)uVar5 + -1);
      cVar8 = extraout_DL + '\x01';
      cVar9 = extraout_DH + '\x01';
    }
    if (0x31 < bVar3) {
      uVar5 = CONCAT11((char)((uint)uVar5 >> 8) + -1,(char)uVar5 + -1);
      cVar8 = cVar8 + '\x01';
      cVar9 = cVar9 + '\x01';
    }
    puVar1 = (undefined2 *)(G_savebx + 0x340);
    EXE_MFXInit(in_BX);
    iVar10 = G_crecptrs+46;
    iVar6 = 0x17;
    do {
      iVar7 = iVar6;
      if ((((*(char *)(iVar10 + 4) != '\0') && (*(char *)(iVar10 + 1) <= cVar8)) &&
          (local_4 = (char)uVar5, local_4 <= *(char *)(iVar10 + 1))) &&
         (((*(char *)(iVar10 + 2) <= cVar9 &&
           (cStack_3 = (char)((uint)uVar5 >> 8), cStack_3 <= *(char *)(iVar10 + 2))) &&
          (*(char *)(iVar10 + 0xe) != '\0')))) {
        bVar2 = true;
        *(undefined1 *)(iVar10 + 0xe) = 0;
        uVar4 = ovl_1f3d();
        bVar3 = *(byte *)(iVar6 + &G_pltilno);
        iVar6 = G_mfxcnt;
        *(undefined2 *)(iVar6 + &G_mfxcoords) = uVar4;
        *(uint *)(iVar6 + &G_mfxtnum) = (uint)bVar3;
        G_mfxcnt = G_mfxcnt + 2;
      }
      iVar10 = iVar10 + -0x21;
      iVar6 = iVar7 + -1;
    } while (0 < iVar7);
    if (bVar2) {
      G_egadrawcode = 0;
      G_egaeffectstimer = 5000;
      G_egaeffectsflag = 6;
      puVar1 = (undefined2 *)(G_savebx + 0xd0);
      EXE_GameSound(9,iVar10);
      puVar1 = (undefined2 *)(G_savebx + 0x2f8);
      EXE_movectileFX(0,0,0,iVar10);
      ovl_07da(iVar10,iVar6);
    }
    else {
      ovl_0f64();
      puVar1 = (undefined2 *)(G_savebx + 0x338);
      EXE_AutoPause(G_UserDelay,iVar10);
    }
  }
  return;
}


// ===== INT61_40 @ 3000:18fc

void INT61_40(void)

{
  byte bVar1;
  undefined2 *puVar2;
  char cVar3;
  undefined2 in_CX;
  undefined2 in_BX;
  undefined1 uVar5;
  int iVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar5 = (undefined1)((uint)in_BX >> 8);
  G_offense = 0;
  ovl_0e5b();
  cVar3 = G_rec2+17 + '\x05';
  if ('\f' < cVar3) {
    cVar3 = '\f';
  }
  G_rec2+17 = cVar3;
  bVar1 = G_rec2+31;
  iVar4 = CONCAT11(uVar5,bVar1);
  if (bVar1 < 6) {
    iVar4 = *(int *)((uint)bVar1 * 2 + &G_heroptr);
    cVar3 = *(char *)(iVar4 + 0xd) + '\x05';
    if ('\f' < cVar3) {
      cVar3 = '\f';
    }
    *(char *)(iVar4 + 0xd) = cVar3;
  }
  if ((G_rec2+5 & 0x20) != 0) {
    G_rec2+30 = 1;
  }
  G_rec2+5 = G_rec2+5 & 0x9f;
  G_rec2+25 = G_rec2+25 & 0xf;
  ovl_07da(iVar4,in_CX);
  ovl_07da(in_CX);
  puVar2 = (undefined2 *)(G_savebx + 0x36c);
  EXE_Spef6();
  INT61_1c();
  ovl_0fbc();
  ovl_0f64();
  puVar2 = (undefined2 *)(G_savebx + 0x338);
  EXE_AutoPause();
  return;
}


// ===== INT61_0d @ 3000:1994

void INT61_0d(void)

{
  undefined2 *puVar1;
  char cVar2;
  undefined2 in_CX;
  undefined1 uVar3;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar3 = (undefined1)((uint)in_CX >> 8);
  G_offense = 1;
  cVar2 = ovl_0e43();
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(10,in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0x35c);
  EXE_Spef3(in_BX);
  G_rec2+25 = G_rec2+25 & 0xf;
  G_rec2+25 = G_rec2+25 | cVar2 << 4;
  G_rec2+5 = G_rec2+5 | 0x20;
  G_rec2+30 = 0;
  ovl_07da(G_savebx,CONCAT11(uVar3,4));
  INT61_1c();
  ovl_0fbc();
  ovl_0f64();
  puVar1 = (undefined2 *)(G_savebx + 0x338);
  EXE_AutoPause();
  return;
}


// ===== INT61_0e @ 3000:19fd

void INT61_0e(void)

{
  undefined2 *puVar1;
  byte bVar2;
  uint uVar3;
  undefined2 uVar4;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 1;
  uVar3 = ovl_0e43();
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(0xf,in_BX);
  uVar4 = G_rec2+1;
  puVar1 = (undefined2 *)(G_savebx + 0x364);
  EXE_Spef3Single(uVar4,9,G_rec2+31,in_BX);
  bVar2 = ((byte)(uVar3 >> 1) & 0x7f) + 1;
  G_rec2+25 = G_rec2+25 & 0xf0;
  G_rec2+25 = G_rec2+25 | bVar2;
  G_deftxtparms+2 = bVar2;
  G_rec2 = G_rec2 | 0x20;
  G_rec2+30 = 0;
  ovl_07da(G_savebx,uVar4);
  puVar1 = (undefined2 *)(G_savebx + 0x84);
  EXE_PrtW3();
  INT61_1c();
  ovl_07da();
  ovl_0fbc();
  ovl_0f64();
  puVar1 = (undefined2 *)(G_savebx + 0x338);
  EXE_AutoPause();
  return;
}


// ===== INT61_0f @ 3000:1a82

void INT61_0f(void)

{
  undefined2 *puVar1;
  byte bVar2;
  undefined2 in_CX;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 1;
  ovl_0e43();
  if (G_rec2+21 < 9) {
    puVar1 = (undefined2 *)(G_savebx + 0xd0);
    EXE_GameSound(10);
    puVar1 = (undefined2 *)(G_savebx + 0x37c);
    bVar2 = EXE_Spef7(G_rec2+1,
                               G_rec2+31);
    G_rec2+26 = G_rec2+26 & 0xf0;
    G_rec2+26 = G_rec2+26 | bVar2;
    G_rec2+4 = G_rec2+4 ^ 1;
    G_rec2+7 = 0xff;
    ovl_07da(in_BX,in_CX);
    ovl_0fbc();
    ovl_0f64();
    puVar1 = (undefined2 *)(G_savebx + 0x338);
    EXE_AutoPause();
    ovl_07da();
    return;
  }
  ovl_0fc0();
  ovl_0f64();
  puVar1 = (undefined2 *)(G_savebx + 0x338);
  EXE_AutoPause(G_UserDelay);
  return;
}


// ===== INT61_10 @ 3000:1b0d

void INT61_10(void)

{
  undefined2 *puVar1;
  undefined1 uVar2;
  undefined2 in_CX;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 1;
  ovl_0e5b();
  G_zp_1415 = G_rec2+1;
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(2);
  ovl_07da(in_BX,in_CX);
  ovl_27d0();
  if (G_ARESULT != '\0') {
    uVar2 = INT61_01();
    G_zp_0E = uVar2;
    puVar1 = (undefined2 *)(G_savebx + 0x134);
    EXE_RndCo();
    ovl_07da();
    ovl_07da();
  }
  return;
}


// ===== INT61_11 @ 3000:1b83

void INT61_11(void)

{
  undefined2 *puVar1;
  undefined2 in_CX;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 1;
  ovl_0e5b();
  G_zp_1415 = G_rec2+1;
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(2);
  ovl_07da(in_BX,in_CX);
  puVar1 = (undefined2 *)(G_savebx + 0x1e4);
  EXE_Bang(G_TILEXY & 0xff,G_TILEXY >> 8)
  ;
  if (G_ARESULT != '\0') {
    INT61_01();
    ovl_07da(in_CX);
    ovl_07da();
  }
  return;
}


// ===== INT61_12 @ 3000:1bdd

void INT61_12(void)

{
  undefined2 *puVar1;
  undefined2 in_CX;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 1;
  ovl_0e5b();
  G_zp_1415 = G_rec2+1;
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(2);
  ovl_07da(in_BX,in_CX);
  puVar1 = (undefined2 *)(G_savebx + 0x378);
  EXE_AcidBang();
  if (G_ARESULT == '\0') {
    return;
  }
  INT61_01();
  ovl_07da(in_CX);
  ovl_07da();
  return;
}


// ===== INT61_13 @ 3000:1c3f

void INT61_13(void)

{
  undefined2 *puVar1;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 1;
  ovl_0e5b();
  ovl_0fac();
  G_rec2+16 = 0;
  G_rec2+12 = 0;
  ovl_07da(in_BX);
  if (G_rec2+31 < 6) {
    ovl_07da();
  }
  ovl_0f64();
  puVar1 = (undefined2 *)(G_savebx + 0x338);
  EXE_AutoPause();
  return;
}


// ===== INT61_14 @ 3000:1c95

void INT61_14(void)

{
  undefined2 *puVar1;
  byte bVar2;
  uint uVar3;
  undefined2 uVar4;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 0;
  ovl_0e5b();
  if (G_curtar < 0x18) {
    ovl_0fbc();
    bVar2 = INT61_01();
    G_deftxtparms+2 = bVar2 >> 3;
    G_rec2+14 = bVar2 >> 3;
    ovl_0f64();
    ovl_07da(in_BX);
    ovl_07da();
    puVar1 = (undefined2 *)(G_savebx + 0xd0);
    EXE_GameSound();
    ovl_30ed();
    puVar1 = (undefined2 *)(G_savebx + 0x340);
    EXE_MFXInit();
    puVar1 = (undefined2 *)(G_savebx + 0xf4);
    uVar3 = EXE_Locate();
    G_mfxtnum = uVar3 & 0xff;
    uVar4 = ovl_1f3d();
    G_mfxcoords = uVar4;
    G_mfxcflag = 0;
    G_egadrawcode = 0;
    G_egaeffectstimer = 6000;
    G_egaeffectsflag = 3;
    puVar1 = (undefined2 *)(G_savebx + 0x344);
    EXE_MultiFX();
    ovl_07da();
    puVar1 = (undefined2 *)(G_savebx + 0x50);
    EXE_PageFlip();
  }
  return;
}


// ===== INT61_15 @ 3000:1d6b

void INT61_15(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 0;
  ovl_0e5b();
  if (G_curtar < 0x18) {
    ovl_0fac();
    G_rec2 = G_rec2 & 0xdf;
    ovl_0fbc();
    ovl_0f64();
    puVar1 = (undefined2 *)(G_savebx + 0x338);
    EXE_AutoPause();
    return;
  }
  return;
}


// ===== INT61_16 @ 3000:1d96

void INT61_16(void)

{
  undefined2 *puVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  undefined2 uVar5;
  undefined1 uVar6;
  uint uVar7;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_1ef6();
  uVar7 = G_rec2+1 & 0xff;
  puVar1 = (undefined2 *)(G_savebx + 0x1f0);
  iVar3 = EXE_Target(uVar7,G_rec2+1 >> 8,0x65);
  if (iVar3 != -1) {
    G_zp_1415 =
         CONCAT11(G_worky,(char)G_workx);
    iVar3 = ovl_07da(in_BX,uVar7);
    if ((iVar3 == 1) && (iVar3 = ovl_27e6(), iVar3 != -1)) {
      puVar1 = (undefined2 *)(G_savebx + 0x340);
      EXE_MFXInit();
      uVar7 = G_rec2+1;
      puVar1 = (undefined2 *)(G_savebx + 0xf4);
      uVar4 = EXE_Locate(uVar7 & 0xff,uVar7 >> 8);
      G_mfxtnum = uVar4 & 0xff;
      puVar1 = (undefined2 *)(G_savebx + 0x120);
      EXE_RestBG(uVar7 & 0xff,uVar7 >> 8);
      uVar5 = ovl_1f3d();
      G_mfxcoords = uVar5;
      G_mfxcflag = 0;
      G_mfxtnum+2 =
           (uint)*(byte *)((uint)G_rec2+31 + &G_pltilno);
      uVar5 = ovl_1f3d();
      G_mfxcoords+2 = uVar5;
      G_mfxcflag+2 = 1;
      G_egadrawcode = 0;
      G_egaeffectstimer = 0x1d4c;
      G_egaeffectsflag = 3;
      uVar5 = G_savebx;
      puVar1 = (undefined2 *)(G_savebx + 0xd0);
      EXE_GameSound();
      uVar7 = G_curtar;
      uVar2 = (undefined1)G_zp_1415;
      uVar6 = (undefined1)((uint)G_zp_1415 >> 8);
      if (uVar7 < 6) {
        *(undefined1 *)(uVar7 + &G_p1x) = uVar2;
        *(undefined1 *)(uVar7 + &G_p1y) = uVar6;
      }
      G_rec2+1 = uVar2;
      G_rec2+2 = uVar6;
      ovl_07da(uVar5);
      puVar1 = (undefined2 *)(G_savebx + 0x344);
      EXE_MultiFX();
      ovl_07da();
      INT61_42();
      ovl_07da();
      puVar1 = (undefined2 *)(G_savebx + 0x32c);
      EXE_FixMusRegs();
    }
    else {
      ovl_0f64();
      puVar1 = (undefined2 *)(G_savebx + 0xd0);
      EXE_GameSound();
    }
  }
  return;
}


// ===== ovl_1ef6 @ 3000:1ef6

undefined2 ovl_1ef6(void)

{
  undefined2 *puVar1;
  int iVar2;
  undefined2 uVar3;
  uint uVar4;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined2 in_stack_00000000;
  
  uVar4 = G_rec1+1 & 0xff;
  puVar1 = (undefined2 *)(G_savebx + 0x1f0);
  iVar2 = EXE_Target(uVar4,G_rec1+1 >> 8,0x111);
  if ((iVar2 == -1) || (iVar2 = INT61_23(), iVar2 == 0x18)) {
    return in_stack_00000000;
  }
  G_curtar = iVar2;
  uVar3 = ovl_07da(in_BX,uVar4);
  return uVar3;
}


// ===== ovl_1f3d @ 3000:1f3d

undefined2 __cdecl16near ovl_1f3d(void)

{
  char in_AL;
  char in_AH;
  
  return CONCAT11(in_AH * '\x10' + '\b',in_AL * '\x04' + '\x04');
}


// ===== INT61_17 @ 3000:1f4d

void INT61_17(void)

{
  undefined2 *puVar1;
  undefined2 in_CX;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 0;
  ovl_0e5b();
  if ((G_rec2+5 & 0x82) == 0x82) {
    puVar1 = (undefined2 *)(G_savebx + 0xd0);
    EXE_GameSound(5);
    ovl_1fcf();
    G_rec2+5 = G_rec2+5 & 0xfd;
    G_rec2+5 = G_rec2+5 | 8;
    G_rec2+1 = 0xffff;
    ovl_07da(in_BX,in_CX);
    ovl_07da(in_CX);
    puVar1 = (undefined2 *)(G_savebx + 0x344);
    EXE_MultiFX();
    ovl_0fc0();
    ovl_0f64();
    puVar1 = (undefined2 *)(G_savebx + 0x338);
    EXE_AutoPause();
    return;
  }
  ovl_0fc0();
  ovl_0f64();
  puVar1 = (undefined2 *)(G_savebx + 0x338);
  EXE_AutoPause(G_UserDelay);
  return;
}


// ===== ovl_1fcf @ 3000:1fcf

void __cdecl16near ovl_1fcf(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  uint uVar5;
  
  uVar5 = 0;
  iVar4 = (G_rec2+1 + 1) * 4;
  for (uVar3 = (uint)G_rec2+2 * 0x10 + 8; 8 < uVar3; uVar3 = uVar3 - 4) {
    uVar5 = (uint)(byte)((char)uVar5 + 1);
    ovl_20e1(uVar5,iVar4);
    ovl_2114();
  }
  puVar1 = (undefined2 *)(G_savebx + 0x340);
  EXE_MFXInit();
  uVar3 = G_rec2+1;
  puVar1 = (undefined2 *)(G_savebx + 0xf4);
  uVar5 = EXE_Locate(uVar3 & 0xff,uVar3 >> 8,in_BX,uVar3);
  G_mfxtnum+2 = uVar5 & 0xff;
  uVar2 = ovl_1f3d(uVar3);
  G_mfxcoords+2 = uVar2;
  uVar3 = uVar3 & 0xff;
  puVar1 = (undefined2 *)(G_savebx + 0xf4);
  uVar5 = EXE_Locate(uVar3,0,in_BX,uVar3);
  G_mfxtnum = uVar5 & 0xff;
  uVar2 = ovl_1f3d();
  G_mfxcoords = uVar2;
  iVar4 = INT61_23(uVar3);
  if ((iVar4 == 0x18) || ((char)iVar4 == G_rec2+31)) {
    ovl_2b36();
    if (*(char *)(in_BX + &G_globemap) != '\0') {
      G_mfxtnum+4 = 0x1b;
      G_mfxcflag+4 = 1;
      G_mfxcoords+4 = G_mfxcoords;
    }
  }
  else {
    G_mfxtnum+4 = (uint)*(byte *)(iVar4 + &G_pltilno);
    G_mfxcflag+4 = 1;
    G_mfxcoords+4 = G_mfxcoords;
  }
  G_mfxcflag = 0;
  G_mfxcflag+2 = 0;
  G_egadrawcode = 0;
  G_egaeffectstimer = 3000;
  G_egaeffectsflag = 3;
  return;
}


// ===== ovl_20e1 @ 3000:20e1

void __cdecl16near ovl_20e1(byte param_1)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar2 = 0x2c;
  if ((param_1 & 1) != 0) {
    uVar2 = 0x2d;
  }
  puVar1 = (undefined2 *)(G_savebx + 0x74);
  EXE_movectile(uVar2);
  puVar1 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip(in_BX);
  return;
}


// ===== ovl_2114 @ 3000:2114

void __cdecl16near ovl_2114(void)

{
  undefined2 *puVar1;
  int in_CX;
  int iVar2;
  uint uVar3;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar2 = in_CX + -8 >> 4;
  uVar3 = (uint)G_rec2+1;
  puVar1 = (undefined2 *)(G_savebx + 500);
  EXE_viaptr_puVar1(uVar3,iVar2);
  puVar1 = (undefined2 *)(G_savebx + 500);
  EXE_viaptr_puVar1(uVar3,iVar2 + 1,in_BX);
  return;
}


// ===== INT61_18 @ 3000:2149

void INT61_18(void)

{
  byte bVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined2 in_CX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 1;
  ovl_0e5b();
  puVar3 = (undefined2 *)(G_savebx + 0x368);
  EXE_Spef5(G_rec2+1);
  if (G_rec2+31 < 6) {
    iVar2 = *(int *)((uint)G_rec2+31 * 2 + &G_heroptr);
    bVar1 = *(byte *)(iVar2 + 0xcb);
    if (bVar1 == 0xff) goto L_21c4;
    *(undefined1 *)(iVar2 + 0xcb) = 0xff;
    *(undefined1 *)(iVar2 + (uint)bVar1 + 0x7b) = 0;
  }
  else {
    if (G_rec2+27 == -1) goto L_21c4;
    G_rec2+27 = 0xff;
    ovl_07da(G_savebx,in_CX);
  }
  ovl_0fc0();
L_21c4:
  ovl_0f64();
  return;
}


// ===== INT61_19 @ 3000:21cd

uint __cdecl16near INT61_19(void)

{
  undefined2 *puVar1;
  bool bVar2;
  undefined1 extraout_AH;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined2 in_BX;
  int iVar6;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined2 uVar7;
  
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(0xf);
  bVar2 = false;
  uVar7 = G_curtar;
  ovl_0fc0();
  ovl_0f64();
  G_DRAWCODE = 0;
  ovl_2704();
  G_DRAWCODE = 1;
  ovl_2704();
  iVar5 = 0x17;
  do {
    G_curtar = iVar5;
    iVar6 = iVar5;
    ovl_07da(in_BX,iVar5,unaff_DI);
    uVar4 = CONCAT11(extraout_AH,G_rec2+4);
    if ((G_rec2+4 != G_rec1+4) &&
       ((G_rec2+5 & 0x98) == 0)) {
      uVar3 = ovl_0ee1();
      puVar1 = (undefined2 *)(G_savebx + 0x134);
      uVar4 = EXE_RndCo(0xc);
      if (uVar4 < uVar3) {
        bVar2 = true;
        G_rec2+17 = 0;
        G_rec2+5 = G_rec2+5 | 0x40;
        ovl_07da(in_BX,iVar5,unaff_DI);
        unaff_DI = iVar6;
        iVar6 = (uint)G_rec2+31 * 2;
        ovl_11b0(*(undefined2 *)(iVar6 + &G_crecptrs));
        ovl_0fbc();
        ovl_0f64();
        uVar4 = G_UserDelay;
        puVar1 = (undefined2 *)(G_savebx + 0x338);
        in_BX = 0x3000;
        EXE_AutoPause();
        ovl_11d2();
      }
    }
    iVar5 = iVar6 + -1;
  } while (iVar5 != 0);
  if (!bVar2) {
    uVar4 = ovl_0f64();
  }
  G_curtar = uVar7;
  return uVar4;
}


// ===== INT61_1a @ 3000:22a8

void INT61_1a(void)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x288);
  EXE_BreakPoint();
  G_offense = 0;
  ovl_0e5b();
  if (G_rec2+4 == '\0') {
    ovl_0f64();
  }
  else {
    iVar3 = *(int *)((uint)G_rec1+31 * 2 + &G_heroptr);
    iVar2 = 0x2a;
    do {
      *(undefined1 *)(iVar3 + 0x7b) = 0;
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    INT61_02();
    G_terriflag = 1;
    G_zp_1415 = G_rec2+1;
    INT61_25();
    G_terriflag = 0;
    iVar2 = 0;
    iVar3 = 0;
    G_zp_1415 = 0;
    do {
      *(uint *)(iVar3 + &G_bangstg) =
           (uint)(byte)(*(char *)(iVar2 + &G_blobmap) + 0x14);
      *(uint *)(iVar3 + &G_bangx) = (uint)G_zp_1415;
      *(uint *)(iVar3 + &G_bangy) = (uint)G_zp_15;
      iVar3 = iVar3 + 2;
      G_zp_1415 = G_zp_1415 + '\x01';
      if (G_zp_1415 == '\v') {
        G_zp_1415 = 0;
        G_zp_15 = G_zp_15 + '\x01';
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 != 99);
    puVar1 = (undefined2 *)(G_savebx + 0x2c4);
    EXE_MultiBang();
    if (*(char *)((uint)G_rec2+3 + &OV_0x2566) == '\x01') {
      G_egaeffectsflag = 0x1001;
      G_egadrawcode = 0;
      INT61_07();
      puVar1 = (undefined2 *)(G_savebx + 0xd0);
      EXE_GameSound(4);
      puVar1 = (undefined2 *)(G_savebx + 0x120);
      EXE_RestBG();
      G_rec2+5 = 0x98;
      G_rec2+1 = 0xffff;
      ovl_07da();
      ovl_07da();
    }
    else {
      ovl_0fbc();
      ovl_0f64();
      INT61_02();
      iVar2 = 0;
      iVar3 = 0;
      G_zp_1415 = 0;
      do {
        *(uint *)(iVar3 + &G_bangstg) =
             (uint)(byte)(0x20 - *(char *)(iVar2 + &G_blobmap));
        *(uint *)(iVar3 + &G_bangx) = (uint)G_zp_1415;
        *(uint *)(iVar3 + &G_bangy) = (uint)G_zp_15;
        iVar3 = iVar3 + 2;
        G_zp_1415 = G_zp_1415 + '\x01';
        if (G_zp_1415 == '\v') {
          G_zp_1415 = 0;
          G_zp_15 = G_zp_15 + '\x01';
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 != 99);
      puVar1 = (undefined2 *)(G_savebx + 0x2c4);
      EXE_MultiBang();
      puVar1 = (undefined2 *)(G_savebx + 0x40);
      EXE_MyRet();
      puVar1 = (undefined2 *)(G_savebx + 0x178);
      EXE_PrtWrd();
    }
    ovl_0f64();
    puVar1 = (undefined2 *)(G_savebx + 0x338);
    EXE_AutoPause();
  }
  return;
}


// ===== INT61_06 @ 3000:248f

void INT61_06(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 0;
  ovl_0e5b();
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(0xf);
  uVar2 = G_rec2+1;
  puVar1 = (undefined2 *)(G_savebx + 0x364);
  EXE_Spef3Single(uVar2,0xc,G_rec2+31);
  if ((G_rec2 & 0x20) == 0) {
    ovl_0fbc();
    ovl_0f64();
    return;
  }
  G_rec2+25 = 0;
  G_rec2 = G_rec2 & 0xdf;
  G_rec2+30 = 1;
  ovl_07da(in_BX,uVar2);
  INT61_1c();
  puVar1 = (undefined2 *)(G_savebx + 200);
  EXE_Spef3Single();
  puVar1 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip();
  ovl_07da();
  ovl_0fbc();
  ovl_0f64();
  puVar1 = (undefined2 *)(G_savebx + 0x338);
  EXE_AutoPause();
  return;
}


// ===== INT61_1b @ 3000:2530

void INT61_1b(void)

{
  undefined2 *puVar1;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x370);
  EXE_InvertWindow(0,0xb);
  puVar1 = (undefined2 *)(G_savebx + 0xe4);
  EXE_InitScrap(in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0x5c);
  EXE_ClrTxtWnd(in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap(G_comtxtptr);
  puVar1 = (undefined2 *)(G_savebx + 0xec);
  EXE_PrtScrap(0xff,in_BX);
  G_timestop = 1;
  return;
}


// ===== INT61_41 @ 3000:2584

void INT61_41(char param_1)

{
  undefined2 *puVar1;
  char cVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  undefined1 extraout_DH;
  undefined1 extraout_DH_00;
  undefined1 uVar7;
  undefined2 uVar6;
  int iVar8;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined4 uVar9;
  int iVar10;
  
  G_offense = 1;
  ovl_0e5b();
  uVar9 = ovl_1f3d();
  uVar5 = (uint)(byte)((ulong)uVar9 >> 8);
  G_egadrawcode = 0;
  G_egaeffectstimer = 1;
  G_egaeffectsflag = 0xf01;
  iVar10 = G_curtar;
  uVar3 = (uint)*(byte *)(iVar10 + &G_pltilno);
  puVar1 = (undefined2 *)(G_savebx + 0x2f8);
  EXE_movectileFX(uVar3,(char)uVar9,uVar5,iVar10,uVar3,uVar5);
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(0x18,iVar10);
  G_egaeffectstimer = 0xffff;
  G_egaeffectsflag = 1;
  puVar1 = (undefined2 *)(G_savebx + 0x2f8);
  EXE_movectileFX(uVar3,(char)uVar9,uVar5);
  if (G_rec1+4 == '\0') {
    uVar3 = INT61_01();
    cVar2 = (char)(uVar3 / 10);
    uVar7 = extraout_DH_00;
  }
  else {
    cVar2 = '\x01';
    uVar7 = extraout_DH;
  }
  if (G_rec2+23 < '\x10') {
    ovl_0fbc();
    ovl_0f64();
    puVar1 = (undefined2 *)(G_savebx + 0x338);
    EXE_AutoPause(G_UserDelay);
  }
  else {
    cVar4 = G_rec2+23 - cVar2;
    uVar6 = CONCAT11(uVar7,cVar4);
    if (cVar4 < '\x0f') {
      uVar6 = CONCAT11(uVar7,0xf);
    }
    G_rec2+23 = (char)uVar6;
    ovl_0fbc(uVar6);
    G_deftxtparms+2 = cVar2;
    ovl_0f64();
    puVar1 = (undefined2 *)(G_savebx + 0x338);
    EXE_AutoPause(G_UserDelay);
  }
  if (G_rec2+24 < '\x10') {
    ovl_0fbc();
    ovl_0f64();
    puVar1 = (undefined2 *)(G_savebx + 0x338);
    EXE_AutoPause();
  }
  else {
    param_1 = G_rec2+24 - param_1;
    if (param_1 < '\x0f') {
      param_1 = '\x0f';
    }
    G_rec2+24 = param_1;
    G_deftxtparms+2 = param_1;
    ovl_0fbc();
    ovl_0f64();
    puVar1 = (undefined2 *)(G_savebx + 0x338);
    EXE_AutoPause();
  }
  ovl_07da();
  ovl_07da();
  if (G_curtar < 6) {
    iVar10 = *(int *)(G_curtar * 2 + &G_heroptr);
    *(undefined1 *)(iVar10 + 0x1a) = G_rec2+24;
    if (G_rec2+15 == -1) {
      iVar8 = iVar10 + 4;
    }
    else {
      iVar8 = iVar10;
      if (('\x11' < G_rec2+15) &&
         (iVar8 = iVar10 + 1, '\x19' < G_rec2+15)) {
        iVar8 = iVar10 + 2;
      }
    }
    *(undefined1 *)(iVar8 + 0x17) = G_rec2+23;
  }
  return;
}


// ===== ovl_2704 @ 3000:2704

void __cdecl16near ovl_2704(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_savmpg == 2) {
    G_bkonly = 1;
  }
  else {
    G_terriflag = 1;
  }
  G_zp_1415 = G_rec1+1;
  INT61_25();
  ovl_2738();
  G_terriflag = 0;
  G_bkonly = 0;
  return;
}


// ===== ovl_2738 @ 3000:2738

void __cdecl16near ovl_2738(void)

{
  undefined2 *puVar1;
  bool bVar2;
  char extraout_DL;
  char cVar3;
  int iVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  cVar3 = '\x01';
  while( true ) {
    bVar2 = false;
    iVar4 = 0;
    do {
      if (cVar3 == *(char *)(iVar4 + &G_blobmap)) {
        ovl_2779();
        bVar2 = true;
        cVar3 = extraout_DL;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 != 99);
    if (!bVar2) break;
    cVar3 = cVar3 + '\x01';
    if (G_DRAWCODE != '\0') {
      puVar1 = (undefined2 *)(G_savebx + 0x50);
      EXE_PageFlip(G_savebx);
    }
    ovl_30ed();
  }
  return;
}


// ===== ovl_2779 @ 3000:2779

undefined4 __cdecl16near ovl_2779(void)

{
  undefined2 *puVar1;
  undefined2 in_CX;
  int in_BX;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined4 uVar3;
  undefined2 in_stack_00000000;
  
  iVar2 = in_BX << 1;
  if (G_DRAWCODE == '\0') {
    uVar3 = ovl_1f3d();
    puVar1 = (undefined2 *)(G_savebx + 0x74);
    EXE_movectile(10,(char)uVar3,(char)((ulong)uVar3 >> 8),
                       (int)G_oppscr,
                       (int)((ulong)G_oppscr >> 0x10),iVar2);
    puVar1 = (undefined2 *)(G_savebx + 0x50);
    EXE_PageFlip(iVar2);
  }
  else {
    ovl_07da(G_savebx);
  }
  return CONCAT22(in_CX,in_stack_00000000);
}


// ===== ovl_27d0 @ 3000:27d0

void ovl_27d0(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x1e4);
  EXE_Bang();
  return;
}


// ===== ovl_27e6 @ 3000:27e6

undefined2 ovl_27e6(void)

{
  undefined2 uVar1;
  undefined2 in_BX;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_bkonly = 1;
  INT61_25();
  G_bkonly = 0;
  iVar2 = 0;
  uVar1 = ovl_2b36(in_BX);
  if (*(char *)(iVar2 + &G_blobmap) == '~') {
    uVar1 = 0xffff;
  }
  return uVar1;
}


// ===== INT61_1e @ 3000:2819

void INT61_1e(void)

{
  byte bVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  undefined2 in_BX;
  int iVar5;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  int iVar6;
  int iVar7;
  
  puVar2 = (undefined2 *)(G_savebx + 0x3cc);
  EXE_song(0xd);
  puVar2 = (undefined2 *)(G_savebx + 0x3d0);
  EXE_finishsong(in_BX);
  G_used = 0xff;
  iVar5 = 0;
  do {
    bVar1 = *(byte *)(iVar5 + &OV_0x290e);
    if (bVar1 == 0) {
L_28ac:
      ovl_0f64();
      puVar2 = (undefined2 *)(G_savebx + 0x338);
      EXE_AutoPause(G_UserDelay,iVar5);
      return;
    }
    if (G_curreg == (uint)bVar1) {
      if (OV_0x290d == '\0') {
        OV_0x290d = 1;
        iVar5 = G_savebx;
        iVar4 = *(byte *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0x23) / 0x14
                + 1;
        iVar3 = 0x11;
        do {
          iVar6 = iVar4;
          ovl_07da(iVar5);
          ovl_28c4(iVar6);
          iVar6 = unaff_DI;
          iVar7 = iVar3;
          ovl_07da();
          unaff_DI = iVar4;
          iVar3 = iVar6 + 1;
          iVar4 = iVar7 + -1;
        } while (iVar4 != 0);
        INT61_80();
      }
      goto L_28ac;
    }
    iVar5 = iVar5 + 1;
  } while( true );
}


// ===== ovl_28c4 @ 3000:28c4

void ovl_28c4(void)

{
  undefined2 *puVar1;
  uint uVar2;
  undefined2 uVar3;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_rec2+5 = 0;
  puVar1 = (undefined2 *)(G_savebx + 0x134);
  uVar2 = EXE_RndCo(0x2d);
  puVar1 = (undefined2 *)(G_savebx + 0x24c);
  uVar3 = EXE_PlacePerson(uVar2 / 9 & 0xff,uVar2 % 9,in_BX);
  G_rec2+1 = uVar3;
  G_rec2+30 = 1;
  return;
}


// ===== INT61_1d @ 3000:290c

void INT61_1d(void)

{
  char cVar1;
  byte bVar2;
  undefined2 *puVar3;
  uint uVar4;
  int iVar5;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar5 = 0;
  LOCK();
  cVar1 = G_used;
  G_used = -1;
  UNLOCK();
  while (*(char *)(iVar5 + &OV_0x29ff) != cVar1) {
    iVar5 = iVar5 + 1;
  }
  OV_0x29fb = iVar5;
  iVar5 = *(int *)(G_curpla * 2 + &G_heroptr);
  cVar1 = *(char *)(iVar5 + 0x23);
  if (cVar1 == '\0') {
    ovl_0f64();
  }
  else {
    OV_0x2a03 = cVar1;
    iVar5 = iVar5 + OV_0x29fb;
    bVar2 = *(byte *)(iVar5 + 9);
    uVar4 = (uint)bVar2;
    if ((bVar2 & 3) == 0) {
      ovl_0f64();
      puVar3 = (undefined2 *)(G_savebx + 0x3cc);
      EXE_song(0xc,iVar5);
      puVar3 = (undefined2 *)(G_savebx + 0x3d0);
      EXE_finishsong(iVar5);
    }
    else {
      iVar5 = OV_0x29fb << 3;
      OV_0x29fd = iVar5;
      if ((bVar2 & 1) != 0) {
        ovl_2a56(iVar5,uVar4);
        uVar4 = G_savebx;
        puVar3 = (undefined2 *)(G_savebx + 0x2b8);
        EXE_SetTxtSong(OV_0x29fd);
        ovl_0f64();
        puVar3 = (undefined2 *)(G_savebx + 0x3cc);
        EXE_song(*(undefined1 *)
                                   (OV_0x29fb * 2 + &OV_0x2a04));
        puVar3 = (undefined2 *)(G_savebx + 0x310);
        EXE_delay(0xfa);
        ovl_2ad3();
        puVar3 = (undefined2 *)(G_savebx + 0x3d0);
        EXE_finishsong();
      }
      if (((uVar4 & 2) != 0) && (ovl_2a56(), G_workx != 0)) {
        puVar3 = (undefined2 *)(G_savebx + 0x2b8);
        EXE_SetTxtSong(OV_0x29fd + 1);
        ovl_0f64();
        puVar3 = (undefined2 *)(G_savebx + 0x3cc);
        EXE_song(*(undefined1 *)
                                   (OV_0x29fb * 2 + &OV_0x2a05));
        puVar3 = (undefined2 *)(G_savebx + 0x310);
        EXE_delay(0xfa);
        ovl_2ad3();
        puVar3 = (undefined2 *)(G_savebx + 0x3d0);
        EXE_finishsong();
      }
    }
  }
  return;
}


// ===== ovl_2a56 @ 3000:2a56

void ovl_2a56(void)

{
  int iVar1;
  undefined2 *puVar2;
  char in_AL;
  byte bVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  puVar2 = (undefined2 *)(G_savebx + 0x340);
  EXE_MFXInit();
  G_workx = 0;
  iVar7 = G_crecptrs+12;
  iVar5 = 0x12;
  do {
    iVar6 = iVar7;
    if ((((*(byte *)(iVar7 + 5) & 0x98) == 0) && (*(char *)(iVar7 + 3) == in_AL)) &&
       (G_workx = G_workx + 1,
       OV_0x2a03 != '\0')) {
      puVar2 = (undefined2 *)(G_savebx + 0x134);
      bVar3 = EXE_RndCo(200);
      iVar6 = iVar7;
      if (bVar3 <= (byte)(OV_0x2a03 + 100U)) {
        *(byte *)(iVar7 + 5) = *(byte *)(iVar7 + 5) | 0x21;
        uVar4 = ovl_1f3d();
        iVar1 = G_mfxcnt;
        *(uint *)(iVar1 + &G_mfxtnum) =
             (uint)*(byte *)((uint)*(byte *)(iVar7 + 0x1f) + &G_pltilno);
        *(undefined2 *)(iVar1 + &G_mfxcoords) = uVar4;
        G_mfxcnt = G_mfxcnt + 2;
      }
    }
    iVar7 = iVar6 + 0x21;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}


// ===== ovl_2ad3 @ 3000:2ad3

void ovl_2ad3(void)

{
  undefined2 *puVar1;
  int iVar2;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_mfxcnt != 0) {
    G_egaeffectstimer = 1000;
    do {
      G_egadrawcode = 0x18;
      G_egaeffectsflag = 7;
      puVar1 = (undefined2 *)(G_savebx + 0x2f8);
      EXE_movectileFX(0,0,0,in_BX);
      puVar1 = (undefined2 *)(G_savebx + 0x3d8);
      iVar2 = EXE_pollmusic();
    } while (iVar2 != 0);
    G_egadrawcode = 0;
    G_egaeffectsflag = 6;
    puVar1 = (undefined2 *)(G_savebx + 0x2f8);
    EXE_movectileFX(0,0,0,in_BX);
  }
  return;
}


// ===== ovl_2b36 @ 3000:2b36

void __cdecl16near ovl_2b36(void)

{
  return;
}


// ===== INT61_1f @ 3000:2b47

void INT61_1f(undefined2 param_1)

{
  undefined2 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined2 uVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_used = 0xff;
  uVar3 = (uint)*(byte *)(G_curpla + &G_p1x);
  uVar5 = G_savebx;
  puVar1 = (undefined2 *)(G_savebx + 0x1f0);
  iVar2 = EXE_Target(uVar3,
                             *(undefined1 *)(G_curpla + &G_p1y),0xd,uVar5)
  ;
  if (((iVar2 == -1) ||
      (CONCAT11(G_worky,G_workx) ==
       G_rec1+1)) ||
     (puVar1 = (undefined2 *)(G_savebx + 0x1d4),
     iVar2 = EXE_Target(G_workx,
                                G_worky,1,1,uVar5), iVar2 != 1)) {
    return;
  }
  G_zp_12 = G_rec1+1;
  G_zp_1415 =
       CONCAT11(G_worky,G_workx);
  ovl_07da(uVar5,uVar3);
  G_wpnt = 0;
  ovl_0a57();
  puVar1 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip();
  G_wpnt = param_1;
  iVar4 = 0x18;
  iVar2 = G_crecptrs;
  do {
    if (((*(byte *)(iVar2 + 5) & 8) == 0) && (*(int *)(iVar2 + 1) == G_zp_1415))
    goto L_2c1a;
    iVar2 = iVar2 + 0x21;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  ovl_2b36();
  if ((*(char *)(iVar2 + &G_globemap) == '\0') &&
     (puVar1 = (undefined2 *)(G_savebx + 0xc4), iVar4 = EXE_PageFlip(),
     iVar4 != 0)) {
    *(undefined1 *)(iVar2 + &G_globemap) = 1;
    uVar5 = G_savebx;
    ovl_0f64();
    puVar1 = (undefined2 *)(G_savebx + 0x1a0);
    EXE_DecObj0(0x39);
    ovl_07da(uVar5);
    puVar1 = (undefined2 *)(G_savebx + 0x50);
    EXE_PageFlip();
    puVar1 = (undefined2 *)(G_savebx + 0xd0);
    EXE_GameSound();
  }
  else {
L_2c1a:
    ovl_0f64();
  }
  INT61_29();
  puVar1 = (undefined2 *)(G_savebx + 0xac);
  EXE_SetPlTilNo();
  ovl_08ca();
  puVar1 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip();
  return;
}


// ===== INT61_42 @ 3000:2c96

void INT61_42(undefined2 param_1,undefined2 param_2,undefined1 param_3,undefined2 param_4)

{
  undefined2 *puVar1;
  uint uVar2;
  undefined2 in_CX;
  undefined2 uVar3;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DI;
  undefined2 unaff_DS;
  undefined2 in_stack_00000000;
  
  ovl_2b36();
  if (*(char *)(in_BX + &G_globemap) != '\0') {
    *(undefined1 *)(in_BX + &G_globemap) = 0;
    uVar3 = G_curtar;
    ovl_07da(G_savebx,in_CX);
    G_curtar = (uint)G_rec1+31;
    ovl_07da(in_CX,unaff_DI,uVar3);
    puVar1 = (undefined2 *)(G_savebx + 0x134);
    uVar2 = EXE_RndCo(0x1e);
    if (0x18 < uVar2) {
      uVar2 = 0x3c;
    }
    G_DAM = uVar2 + 0x28;
    G_HIT = uVar2 + 0x28;
    uVar3 = 0;
    puVar1 = (undefined2 *)(G_savebx + 0x1e4);
    EXE_Bang(G_rec2+1 & 0xff,
                       G_rec2+1 >> 8,0);
    G_swcast = 1;
    G_GLOBEHIT = 1;
    ovl_07da(unaff_DI,uVar3,in_stack_00000000);
    ovl_07da(uVar3,in_stack_00000000);
    ovl_07da(in_stack_00000000);
    G_swcast = param_3;
    G_GLOBEHIT = 0;
    G_curtar = param_4;
  }
  return;
}


// ===== INT61_60 @ 3000:2d62

void INT61_60(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  
  INT61_02();
  iVar4 = 0;
  uVar5 = 0;
  iVar3 = 99;
  do {
    if (*(char *)(uVar5 + &G_globemap) != '\0') {
      *(undefined1 *)(uVar5 + &G_globemap) = 0;
      uVar1 = *(undefined2 *)(uVar5 * 2 + &G_cmbcrds);
      uVar5 = uVar5 & 0x7fff;
      *(undefined1 *)(iVar4 + &G_bangx) = (char)uVar1;
      *(undefined1 *)(iVar4 + &G_bangy) = (char)((uint)uVar1 >> 8);
      *(undefined2 *)(iVar4 + &G_bangstg) = 1;
      iVar4 = iVar4 + 2;
    }
    uVar5 = uVar5 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (iVar4 != 0) {
    ovl_0f64();
    puVar2 = (undefined2 *)(G_savebx + 0x2c4);
    EXE_MultiBang(3);
  }
  return;
}


// ===== INT61_24 @ 3000:2db6

void INT61_24(void)

{
  byte bVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_rec2+3 == ' ') {
    bVar1 = *(byte *)(G_curtar + &G_doombstlst);
    if ((bVar1 & 0x80) == 0) {
      ovl_2e08();
      G_rec1+7 = 0xff;
    }
    else if (G_ARESULT == -1) {
      iVar2 = 0;
      do {
        if ((bVar1 & 0x7f) == *(byte *)(iVar2 + &G_doombstlst)) {
          ovl_2e08();
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 != 0x18);
      G_rec1+7 = 0xff;
    }
  }
  return;
}


// ===== ovl_2e08 @ 3000:2e08

void ovl_2e08(void)

{
  undefined2 *puVar1;
  char cVar2;
  undefined2 in_CX;
  int in_BX;
  int iVar3;
  int unaff_SI;
  undefined2 unaff_DI;
  undefined2 unaff_DS;
  
  *(undefined1 *)(in_BX + &G_doombstlst) = 0;
  iVar3 = *(int *)(in_BX * 2 + &G_crecptrs);
  *(undefined1 *)(iVar3 + 5) = 8;
  cVar2 = *(char *)(iVar3 + 0x1f);
  if (cVar2 == G_rec2+31) {
    ovl_07da();
  }
  if (cVar2 == G_rec1+31) {
    ovl_07da(iVar3,in_CX,unaff_DI);
  }
  *(undefined2 *)(iVar3 + 1) = 0xffff;
  ovl_07da(G_savebx,in_CX,unaff_DI);
  puVar1 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip(in_CX);
  ovl_0f64();
  puVar1 = (undefined2 *)(G_savebx + 0x338);
  EXE_AutoPause(G_UserDelay,in_CX);
  return;
}


// ===== INT61_26 @ 3000:2e7c

void INT61_26(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if ((G_rec1+5 & 0x40) == 0) {
    return;
  }
  iVar2 = 0;
  while( true ) {
    iVar1 = *(int *)(iVar2 + &G_fleetbl);
    if (iVar1 == -1) {
      return;
    }
    if (iVar1 == G_rec1+1) break;
    iVar2 = iVar2 + 2;
  }
  return;
}


// ===== INT61_25 @ 3000:2ea5

void __cdecl16near INT61_25(void)

{
  char *pcVar1;
  char cVar2;
  undefined2 uVar3;
  undefined2 *puVar4;
  undefined1 uVar5;
  int iVar6;
  uint uVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar10;
  
  uVar3 = G_zp_1415;
  G_zp_1415 = 0x80a;
  puVar9 = (undefined1 *)&G_blobmap+98;
  do {
    bVar10 = G_terriflag == 1;
    if (!bVar10) {
      puVar4 = (undefined2 *)(G_savebx + 0xc4);
      iVar6 = EXE_ChkWlk();
      bVar10 = iVar6 == 1;
    }
    uVar5 = 0x7e;
    if (!bVar10) {
      uVar5 = 0xff;
    }
    *puVar9 = uVar5;
    pcVar1 = (char *)&G_zp_1415;
    cVar2 = *pcVar1;
    *pcVar1 = *pcVar1 + -1;
    if (SBORROW1(cVar2,'\x01') != *pcVar1 < '\0') {
      G_zp_1415 = 10;
      pcVar1 = (char *)&G_zp_15;
      cVar2 = *pcVar1;
      *pcVar1 = *pcVar1 + -1;
      if (SBORROW1(cVar2,'\x01') != *pcVar1 < '\0') {
        if (G_FIREFLAG == 1) {
          ovl_2ff9();
        }
        if ((G_terriflag != 1) && (G_bkonly != 1)) {
          puVar9 = (undefined1 *)&G_crecs;
          iVar6 = 0x18;
          do {
            if (((puVar9[5] & 0x98) == 0) && (puVar9[0x1f] != G_curatt)) {
              puVar8 = puVar9;
              ovl_2b36();
              puVar8[&G_blobmap] = 0xff;
            }
            puVar9 = puVar9 + 0x21;
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
        }
        G_zp_1415 = uVar3;
        if (G_FLEEBLOB == 1) {
          ovl_2fd4();
        }
        else {
          ovl_2b36();
          puVar9[&G_blobmap] = 0;
        }
        uVar7 = 0;
        while( true ) {
          OV_0x2fa3 = 1;
          while( true ) {
            G_BLOBFOUND = 0;
            iVar6 = 0x62;
            do {
              if (*(char *)(iVar6 + &G_blobmap) == (char)uVar7) {
                ovl_2f92();
              }
              bVar10 = 0 < iVar6;
              iVar6 = iVar6 + -1;
            } while (bVar10);
            if (G_BLOBFOUND != '\x01') break;
            OV_0x2fa3 = 0;
          }
          if (OV_0x2fa3 == 1) break;
          uVar7 = (uint)(byte)((char)uVar7 + 1);
        }
        return;
      }
    }
    puVar9 = puVar9 + -1;
  } while( true );
}


// ===== ovl_2f92 @ 3000:2f92

void __cdecl16near ovl_2f92(void)

{
  undefined2 uVar1;
  bool bVar2;
  char in_CL;
  char cVar3;
  char cVar4;
  uint in_BX;
  uint uVar5;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  cVar3 = in_CL + '\x01';
  cVar4 = '\a';
  do {
    uVar1 = *(undefined2 *)(in_BX * 2 + &G_cmbcrds);
    uVar5 = in_BX & 0x7fff;
    if (((byte)((char)uVar1 + OV_0x3082) < 0xb) &&
       ((byte)((char)((uint)uVar1 >> 8) + OV_0x308a) < 9)) {
      ovl_2b36();
      if (cVar3 < *(char *)(uVar5 + &G_blobmap)) {
        G_BLOBFOUND = 1;
        *(char *)(uVar5 + &G_blobmap) = cVar3;
      }
    }
    unaff_DI = unaff_DI + 1;
    bVar2 = '\0' < cVar4;
    cVar4 = cVar4 + -1;
  } while (bVar2);
  return;
}


// ===== ovl_2fd4 @ 3000:2fd4

void __cdecl16near ovl_2fd4(void)

{
  int extraout_DX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  for (; G_fleetbl != -1; unaff_SI = unaff_SI + 2) {
    ovl_2b36();
    in_BX = in_BX + extraout_DX;
    if (*(char *)(in_BX + 0x5788) == '~') {
      *(undefined1 *)(in_BX + 0x5788) = 0;
    }
  }
  return;
}


// ===== ovl_2ff9 @ 3000:2ff9

void __cdecl16near ovl_2ff9(void)

{
  int iVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = 0;
  do {
    if (*(char *)(iVar1 + &G_globemap) != '\0') {
      *(undefined1 *)(iVar1 + &G_blobmap) = 0xff;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 != 99);
  return;
}


// ===== INT61_44 @ 3000:3021

void INT61_44(void)

{
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x3120 = 0;
  G_fleetbl = 0xffff;
  return;
}


// ===== INT61_48 @ 3000:302e

void INT61_48(void)

{
  int unaff_DI;
  
  OV_0x3120 = 1;
  return;
}


// ===== INT61_45 @ 3000:3035

void INT61_45(void)

{
  return;
}


// ===== INT61_46 @ 3000:303c

void INT61_46(void)

{
  undefined2 *puVar1;
  int iVar2;
  int *piVar3;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (OV_0x3120 == '\x01') {
    return;
  }
  puVar1 = (undefined2 *)(G_savebx + 0x340);
  EXE_MFXInit();
  iVar2 = 4;
  piVar3 = (int *)&G_hroomrec+11;
  do {
    if (*piVar3 != 0) {
      ovl_3093();
    }
    piVar3 = piVar3 + -1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  OV_0x3120 = 1;
  INT61_47();
  return;
}


// ===== INT61_47 @ 3000:3077

void INT61_47(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_egadrawcode = 0;
  G_egaeffectstimer = 20000;
  G_egaeffectsflag = 6;
  puVar1 = (undefined2 *)(G_savebx + 0x344);
  EXE_MultiFX();
  return;
}


// ===== ovl_3093 @ 3000:3093

void ovl_3093(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  byte bVar3;
  undefined2 *puVar4;
  undefined2 uVar5;
  int in_CX;
  uint uVar6;
  int iVar7;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar6 = (in_CX + -1) * 2;
  do {
    uVar1 = *(undefined1 *)(uVar6 + &OV_0x3110);
    uVar2 = *(undefined1 *)(uVar6 + &OV_0x3118);
    puVar4 = (undefined2 *)(G_savebx + 0xf4);
    EXE_Locate(uVar1,uVar2,uVar6,uVar6,CONCAT11(uVar2,uVar1));
    bVar3 = *(byte *)(G_tdata+8 + uVar6);
    *(byte *)G_zp_0A = bVar3;
    iVar7 = G_mfxcnt;
    *(uint *)(iVar7 + &G_mfxtnum) = (uint)bVar3;
    uVar5 = ovl_1f3d();
    *(undefined2 *)(iVar7 + &G_mfxcoords) = uVar5;
    *(undefined2 *)(iVar7 + &G_mfxcflag) = 0;
    G_mfxcnt = G_mfxcnt + 2;
    uVar6 = uVar6 + 1;
  } while ((uVar6 & 1) != 0);
  return;
}


// ===== ovl_30ed @ 3000:30ed

void __cdecl16near ovl_30ed(void)

{
  undefined2 *puVar1;
  uint in_AX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x124);
  EXE_Wait((int)((in_AX & 0xff) * (uint)G_UserDelay) >> 2);
  return;
}


// ===== INT61_4a @ 3000:31c2

char INT61_4a(void)

{
  int iVar1;
  int iVar2;
  uint in_DX;
  char *pcVar3;
  int unaff_SI;
  char *pcVar4;
  int unaff_DI;
  undefined2 unaff_DS;
  
  pcVar3 = (char *)(*(int *)((in_DX & 0xff) * 2 + &G_heroptr) + 0x2b);
  iVar1 = 0x28;
  do {
    iVar2 = 8;
    pcVar4 = (char *)&OV_0x32ba;
    do {
      if (*pcVar4 == *pcVar3) {
        return *pcVar4;
      }
      pcVar4 = pcVar4 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    pcVar3 = pcVar3 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return '\0';
}


// ===== INT61_ff @ 3000:31f9

void INT61_ff(void)

{
  undefined2 *puVar1;
  uint uVar2;
  undefined2 uVar3;
  undefined2 in_CX;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_events+18 = G_events+18 | 0x80;
  puVar1 = (undefined2 *)(G_savebx + 0x340);
  EXE_MFXInit();
  uVar2 = G_rec2+1;
  puVar1 = (undefined2 *)(G_savebx + 0xf4);
  uVar2 = EXE_Locate(uVar2 & 0xff,uVar2 >> 8,in_BX,uVar2);
  G_mfxtnum = uVar2 & 0xff;
  uVar3 = ovl_1f3d();
  G_mfxcoords = uVar3;
  G_mfxcflag = 0;
  G_egadrawcode = 0;
  G_egaeffectstimer = 25000;
  G_egaeffectsflag = 3;
  uVar3 = G_savebx;
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(0xd,uVar3);
  puVar1 = (undefined2 *)(G_savebx + 0x39c);
  EXE_WaitForSound(uVar3);
  puVar1 = (undefined2 *)(G_savebx + 0x344);
  EXE_MultiFX(uVar3);
  G_rec2+5 = 8;
  G_rec2+1 = 0xffff;
  ovl_07da(uVar3,in_CX);
  return;
}


