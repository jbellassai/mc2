// ===== ovl_008c @ 1ca8:008c

void ovl_008c(void)

{
  undefined2 unaff_DS;
  code *in_stack_00000000;
  
  *(undefined2 *)(*piRam000004fc + -0x728a) = piRam000004fc;
                    /* WARNING: Could not recover jumptable at 0x0001cb2e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*in_stack_00000000)();
  return;
}


// ===== ovl_00b4 @ 1ca8:00b4

void ovl_00b4(void)

{
  undefined2 uVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  undefined2 uVar3;
  undefined2 unaff_DS;
  undefined1 uVar4;
  
  ovl_008c();
  G_timestop = 0;
  G_UserDelay = 4;
  uVar3 = (undefined2)((ulong)G_rvarbuf >> 0x10);
  iVar2 = (int)G_rvarbuf;
  uVar1 = *(undefined2 *)(iVar2 + 7);
  G_txtptr = *(undefined2 *)(iVar2 + 5);
  G_txtptr+2 = uVar3;
  G_FLEEPTR = uVar1;
  G_FLEEPTR+2 = uVar3;
  G_WANNAFLEE = uVar1;
  G_WANNAFLEE+2 = uVar3;
  ovl_02e8();
  EXE_SetTxtWnd();
  EXE_ClrTxtWnd();
  uVar4 = G_endcmbt < 3;
  if (G_endcmbt == 3) {
    ovl_1b32();
  }
  ovl_05ad();
  if ((bool)uVar4) {
    G_curpla = 0;
  }
  return;
}


// ===== ovl_0118 @ 1ca8:0118

void ovl_0118(void)

{
  return;
}


// ===== ovl_0140 @ 1ca8:0140

void ovl_0140(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x120);
  EXE_RestBG(G_rec1+1 & 0xff,G_rec1+1 >> 8,
                     G_savebx);
  return;
}


// ===== ovl_015e @ 1ca8:015e

uint ovl_015e(void)

{
  char cVar1;
  code *pcVar2;
  byte extraout_AL;
  byte bVar3;
  uint uVar4;
  int iVar5;
  char extraout_AH;
  undefined2 uVar6;
  uint uVar7;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar8;
  byte bVar9;
  byte bVar10;
  byte in_AF;
  byte bVar11;
  byte bVar12;
  byte in_TF;
  byte in_IF;
  bool bVar13;
  byte bVar14;
  byte in_NT;
  int in_stack_00000000;
  
  bVar13 = false;
  uVar7 = (uint)G_mnusel;
  if (uVar7 == 0xe) {
    uVar6 = EXE_DrawWeap(G_curpla);
    ovl_0a25(uVar6);
    return 0xfd;
  }
  if (uVar7 == 0x23) {
    EXE_RecSpl(G_curpla);
    return 0xfe;
  }
  if (uVar7 == 0x13) {
    ovl_06db();
    if (G_leader == 0) {
      uVar7 = 0xfd;
      goto L_044c;
    }
    EXE_SetTxtWnd();
    uVar6 = 0xf5;
    EXE_IComTxt();
    G_headsw = 1;
    do {
      uVar7 = EXE_GetMousePress(0,uVar6);
      uVar4 = EXE_GetMousePress(1,uVar6);
      bVar9 = false;
      bVar14 = false;
      uVar4 = uVar4 | uVar7;
      bVar12 = (int)uVar4 < 0;
      bVar11 = uVar4 == 0;
      bVar10 = (POPCOUNT(uVar4 & 0xff) & 1U) == 0;
      if (!(bool)bVar11) {
        G_headsw = 0;
        goto L_0410;
      }
      iVar5 = EXE_keyhit();
      uVar8 = iVar5 == 0;
      if (iVar5 == 1) {
        G_headsw = 0;
        EXE_ReadKbd();
        bVar3 = extraout_AL;
        if (extraout_AL == 0) {
          bVar3 = extraout_AH - 0x38;
        }
        bVar9 = bVar3 < 0x30;
        bVar14 = SBORROW1(bVar3,'0');
        cVar1 = bVar3 - 0x30;
        bVar12 = cVar1 < '\0';
        bVar11 = cVar1 == '\0';
        bVar10 = (POPCOUNT(cVar1) & 1U) == 0;
        if ((char)bVar3 < '0') {
L_0410:
          G_UserDelay = 4;
L_045d:
          ovl_02bc();
L_0432:
          while (ovl_08a0(), !(bool)bVar9) {
            uVar7 = EXE_Parser(&G_mnuparms);
            bVar3 = (byte)uVar7;
            bVar14 = SBORROW1(bVar3,' ');
            cVar1 = bVar3 - 0x20;
            bVar12 = cVar1 < '\0';
            bVar11 = cVar1 == '\0';
            bVar10 = (POPCOUNT(cVar1) & 1U) == 0;
            bVar9 = 1;
            if (bVar3 < 0x20) break;
L_044c:
            bVar3 = (byte)uVar7;
            bVar9 = bVar3 < 0xfd;
            bVar14 = SBORROW1(bVar3,-3);
            cVar1 = bVar3 + 3;
            bVar12 = cVar1 < '\0';
            bVar11 = cVar1 == '\0';
            bVar10 = (POPCOUNT(cVar1) & 1U) == 0;
            if (!(bool)bVar11) {
              bVar9 = uVar7 < 0xfe;
              bVar14 = SBORROW2(uVar7,0xfe);
              uVar7 = uVar7 - 0xfe;
              bVar12 = (int)uVar7 < 0;
              bVar10 = (POPCOUNT(uVar7 & 0xff) & 1U) == 0;
              bVar11 = 1;
              if (uVar7 != 0) goto L_0462;
              goto L_045d;
            }
            ovl_02bc();
            ovl_02e3();
          }
          uVar7 = ovl_015e();
          if (G_swwill != 0) {
            in_NT = (in_NT & 1) != 0;
            bVar14 = (bVar14 & 1) != 0;
            in_IF = (in_IF & 1) != 0;
            in_TF = (in_TF & 1) != 0;
            bVar12 = (bVar12 & 1) != 0;
            bVar11 = (bVar11 & 1) != 0;
            in_AF = (in_AF & 1) != 0;
            bVar10 = (bVar10 & 1) != 0;
            G_swwill = 0;
            if ((bVar9 & 1) != 0) {
              return uVar7;
            }
            uVar8 = 0;
            goto L_042f;
          }
          ovl_0a2f((uint)((in_NT & 1) != 0) * 0x4000 | (uint)((bVar14 & 1) != 0) * 0x800 |
                        (uint)bVar13 * 0x400 | (uint)((in_IF & 1) != 0) * 0x200 |
                        (uint)((in_TF & 1) != 0) * 0x100 | (uint)((bVar12 & 1) != 0) * 0x80 |
                        (uint)((bVar11 & 1) != 0) * 0x40 | (uint)((in_AF & 1) != 0) * 0x10 |
                        (uint)((bVar10 & 1) != 0) * 4 | (uint)((bVar9 & 1) != 0));
          in_NT = (uVar7 & 0x4000) != 0;
          bVar14 = (uVar7 & 0x800) != 0;
          bVar13 = (uVar7 & 0x400) != 0;
          in_IF = (uVar7 & 0x200) != 0;
          in_TF = (uVar7 & 0x100) != 0;
          bVar12 = (uVar7 & 0x80) != 0;
          bVar11 = (uVar7 & 0x40) != 0;
          in_AF = (uVar7 & 0x10) != 0;
          bVar10 = (uVar7 & 4) != 0;
          bVar9 = (uVar7 & 1) != 0;
          if (!(bool)bVar9) {
            ovl_0613();
            if ((bool)bVar9) {
              return 0xcef5;
            }
            bVar9 = false;
          }
          goto L_045d;
        }
        bVar9 = bVar3 < 0x39;
        bVar14 = SBORROW1(bVar3,'9');
        cVar1 = bVar3 - 0x39;
        bVar12 = cVar1 < '\0';
        bVar11 = cVar1 == '\0';
        bVar10 = (POPCOUNT(cVar1) & 1U) == 0;
        if (!(bool)bVar11 && '8' < (char)bVar3) goto L_0410;
        uVar8 = 0xfff6 < -(uint)(byte)(bVar3 - 0x30);
        G_UserDelay = -(uint)(byte)(bVar3 - 0x30) + 9;
        G_headsw = 1;
      }
      uVar6 = 0x1ca8;
      ovl_0a98();
      uVar7 = ovl_0613();
      if ((bool)uVar8) {
        if (G_endcmbt < 1) {
          return uVar7;
        }
        return uVar7;
      }
    } while( true );
  }
  if (uVar7 == 0x19) {
    EXE_Look();
    G_lookdata = 0xff;
    return 0xff;
  }
  if (uVar7 == 0x2b) {
    uVar6 = EXE_UseItem(G_curpla,&G_rec1);
    ovl_0a25(uVar6);
    if (in_stack_00000000 == 0) {
      if (G_used == 'J') {
        pcVar2 = INT_0x61_handler;
        (*pcVar2)();
      }
      else if ((((G_used == 'H') || (G_used == 'D'))
               || (G_used == 'E')) || (G_used == '['))
      {
        pcVar2 = INT_0x61_handler;
        (*pcVar2)();
      }
      else if (G_used == '9') {
        pcVar2 = INT_0x61_handler;
        (*pcVar2)();
      }
      else {
        EXE_NoUse();
      }
    }
    return 0xfe;
  }
  if (uVar7 == 7) {
    ovl_0a4d();
    return 0xff;
  }
  if (uVar7 == 0x1b) {
    EXE_Magic();
    G_rec1+32 = 1;
    return 0xfd;
  }
  if (uVar7 != 0x2e) {
    if (uVar7 == 0x1e) {
      G_rec1+30 = 1;
      return 0xfe;
    }
    return uVar7;
  }
  uVar7 = G_curpla;
  uVar8 = false;
  do {
    ovl_0a98(uVar7);
    uVar7 = 0xd40c;
    ovl_0613();
    if ((bool)uVar8) break;
    uVar8 = uVar7 < G_curpla;
  } while (uVar7 == G_curpla);
  G_swwill = 1;
  return uVar7;
L_0462:
  bVar9 = bVar3 != 0xff;
  bVar14 = SBORROW1(bVar3,-1);
  cVar1 = bVar3 + 1;
  bVar12 = cVar1 < '\0';
  bVar11 = cVar1 == '\0';
  bVar10 = (POPCOUNT(cVar1) & 1U) == 0;
  if (!(bool)bVar11) {
    ovl_01ad();
    uVar8 = bVar9;
    if (!(bool)bVar9) {
      uVar7 = ovl_0613();
      uVar8 = 0;
      if ((bool)bVar9) {
        return uVar7;
      }
    }
L_042f:
    ovl_02bc();
    bVar9 = uVar8;
  }
  goto L_0432;
}


// ===== ovl_01ad @ 1ca8:01ad

void ovl_01ad(void)

{
  byte bVar1;
  code *pcVar2;
  byte in_AL;
  char cVar3;
  int iVar4;
  int iVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar6;
  
  if (((in_AL != 0) && (0x2f < in_AL)) && ((char)in_AL < ':')) {
    iVar5 = G_savebx;
    iVar4 = EXE_RMove(in_AL);
    if (iVar4 == 2) {
      ovl_1c80();
      EXE_MyRet();
      ovl_1b32();
      iVar4 = EXE_SetYN();
      EXE_ClrTxtWnd();
      if (iVar4 == 0) {
        bVar6 = false;
        if ((G_curpla != 0) || (ovl_09a8(), !bVar6)) {
          ovl_0a1b();
          ovl_0140();
          ovl_0a15();
          G_rec1+30 = 1;
          G_rec1+5 = G_rec1+5 | 0x10;
          G_rec1+1 = 0xffff;
          bVar1 = G_rec1+31;
          *(undefined1 *)((uint)bVar1 + &G_p1x) = 0xff;
          *(undefined1 *)((uint)bVar1 + &G_p1y) = 0xff;
          ovl_0a25();
          ovl_0a48();
          ovl_02bc();
          return;
        }
        ovl_02bc();
      }
      else {
        ovl_02bc();
      }
    }
    else {
      if (iVar4 != 1) {
        pcVar2 = INT_0x61_handler;
        (*pcVar2)();
        return;
      }
      iVar4 = EXE_IsItMon(&G_curtar);
      if (iVar4 == 0) {
        EXE_GameSound(0xe,iVar5);
      }
      else if (((*(char *)(*(int *)(G_curtar * 2 + &G_crecptrs) + 4) ==
                 '\x01') && (cVar3 = ovl_0a43(), cVar3 != '\x03')) &&
              ((G_rec1 & 0xf0) == 0)) {
        ovl_09e8();
        ovl_09e8();
        return;
      }
    }
  }
  return;
}


// ===== ovl_02bc @ 1ca8:02bc

void ovl_02bc(void)

{
  int iVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  LOCK();
  iVar1 = G_savebx;
  G_savebx = in_BX;
  UNLOCK();
  EXE_Menu(0xb);
  EXE_InitCom(&OV_0x183,0x1ca8,9);
  LOCK();
  G_savebx = iVar1;
  UNLOCK();
  return;
}


// ===== ovl_02e3 @ 1ca8:02e3

void ovl_02e3(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_02e8 @ 1ca8:02e8

void ovl_02e8(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar1;
  
  G_curphase = 1;
  G_NEXTPHASE = 0;
  uVar1 = 0;
  if (G_ambflg == '\0') goto L_0300;
  ovl_04a6();
  while( true ) {
    ovl_0b4b();
    G_timestop = 0;
    if ((bool)uVar1) break;
    ovl_0655();
L_0300:
    G_curatt = G_curpla;
    ovl_09e8();
    ovl_04a6();
    ovl_0742();
    ovl_05a8();
    ovl_05ad();
    if (!(bool)uVar1) {
      ovl_0346();
      if ((bool)uVar1) break;
    }
    uVar1 = 0;
    ovl_0655();
  }
  ovl_04a6();
  G_headsw = 0;
  return;
}


// ===== ovl_0346 @ 1ca8:0346

undefined2 ovl_0346(undefined2 param_1,uint param_2,int param_3)

{
  char cVar1;
  byte extraout_AL;
  byte bVar2;
  uint uVar3;
  int iVar4;
  char extraout_AH;
  uint uVar5;
  undefined2 uVar6;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  byte bVar7;
  undefined1 uVar8;
  byte bVar9;
  byte in_AF;
  byte bVar10;
  byte bVar11;
  byte in_TF;
  byte in_IF;
  bool bVar12;
  byte bVar13;
  byte in_NT;
  
  bVar12 = false;
  bVar7 = 0;
  bVar13 = 0;
  if (G_headsw == 0) {
    bVar10 = 1;
    bVar11 = 0;
    bVar9 = 1;
    goto L_042f;
  }
  G_headsw = 0;
  ovl_0a1b();
  ovl_05ea();
  if (((bool)bVar7) || ((G_rec1+5 & 0x40) != 0)) {
    G_UserDelay = 4;
    ovl_071f();
    param_2 = 0xcdfb;
    ovl_05ad();
    uVar5 = 0xfd;
    param_3 = in_BX;
    goto L_044c;
  }
  EXE_SetTxtWnd();
  EXE_IComTxt();
  G_headsw = 1;
  do {
    uVar5 = EXE_GetMousePress(0,param_2);
    uVar3 = EXE_GetMousePress(1,param_2);
    bVar7 = false;
    bVar13 = false;
    uVar3 = uVar3 | uVar5;
    bVar11 = (int)uVar3 < 0;
    bVar10 = uVar3 == 0;
    bVar9 = (POPCOUNT(uVar3 & 0xff) & 1U) == 0;
    if (!(bool)bVar10) {
      G_headsw = 0;
      goto L_0410;
    }
    iVar4 = EXE_keyhit();
    uVar8 = iVar4 == 0;
    if (iVar4 == 1) {
      G_headsw = 0;
      param_2 = 0x1ca8;
      EXE_ReadKbd();
      bVar2 = extraout_AL;
      if (extraout_AL == 0) {
        bVar2 = extraout_AH - 0x38;
      }
      bVar7 = bVar2 < 0x30;
      bVar13 = SBORROW1(bVar2,'0');
      cVar1 = bVar2 - 0x30;
      bVar11 = cVar1 < '\0';
      bVar10 = cVar1 == '\0';
      bVar9 = (POPCOUNT(cVar1) & 1U) == 0;
      if ((char)bVar2 < '0') {
L_0410:
        G_UserDelay = 4;
L_045d:
        ovl_02bc();
        do {
          while (ovl_08a0(), !(bool)bVar7) {
            param_2 = 0;
            uVar5 = EXE_Parser();
            bVar2 = (byte)uVar5;
            bVar13 = SBORROW1(bVar2,' ');
            cVar1 = bVar2 - 0x20;
            bVar11 = cVar1 < '\0';
            bVar10 = cVar1 == '\0';
            bVar9 = (POPCOUNT(cVar1) & 1U) == 0;
            bVar7 = 1;
            if (bVar2 < 0x20) break;
L_044c:
            bVar2 = (byte)uVar5;
            bVar7 = bVar2 < 0xfd;
            bVar13 = SBORROW1(bVar2,-3);
            cVar1 = bVar2 + 3;
            bVar11 = cVar1 < '\0';
            bVar10 = cVar1 == '\0';
            bVar9 = (POPCOUNT(cVar1) & 1U) == 0;
            if ((bool)bVar10) {
              ovl_02bc();
              ovl_02e3();
            }
            else {
              bVar7 = uVar5 < 0xfe;
              bVar13 = SBORROW2(uVar5,0xfe);
              uVar5 = uVar5 - 0xfe;
              bVar11 = (int)uVar5 < 0;
              bVar9 = (POPCOUNT(uVar5 & 0xff) & 1U) == 0;
              bVar10 = 1;
              if (uVar5 == 0) goto L_045d;
              bVar7 = bVar2 != 0xff;
              bVar13 = SBORROW1(bVar2,-1);
              cVar1 = bVar2 + 1;
              bVar11 = cVar1 < '\0';
              bVar10 = cVar1 == '\0';
              bVar9 = (POPCOUNT(cVar1) & 1U) == 0;
              if (!(bool)bVar10) {
                ovl_01ad();
                in_BX = param_3;
                if (!(bool)bVar7) {
                  uVar6 = ovl_0613();
                  if ((bool)bVar7) {
                    return uVar6;
                  }
                  bVar7 = 0;
                  in_BX = param_3;
                }
                goto L_042f;
              }
            }
          }
          uVar6 = ovl_015e();
          if (G_swwill == 0) {
            ovl_0a2f((uint)((in_NT & 1) != 0) * 0x4000 | (uint)((bVar13 & 1) != 0) * 0x800 |
                          (uint)bVar12 * 0x400 | (uint)((in_IF & 1) != 0) * 0x200 |
                          (uint)((in_TF & 1) != 0) * 0x100 | (uint)((bVar11 & 1) != 0) * 0x80 |
                          (uint)((bVar10 & 1) != 0) * 0x40 | (uint)((in_AF & 1) != 0) * 0x10 |
                          (uint)((bVar9 & 1) != 0) * 4 | (uint)((bVar7 & 1) != 0),uVar6);
            in_NT = (param_2 & 0x4000) != 0;
            bVar13 = (param_2 & 0x800) != 0;
            bVar12 = (param_2 & 0x400) != 0;
            in_IF = (param_2 & 0x200) != 0;
            in_TF = (param_2 & 0x100) != 0;
            bVar11 = (param_2 & 0x80) != 0;
            bVar10 = (param_2 & 0x40) != 0;
            in_AF = (param_2 & 0x10) != 0;
            bVar9 = (param_2 & 4) != 0;
            bVar7 = (param_2 & 1) != 0;
            if (!(bool)bVar7) {
              param_2 = 0xcf17;
              ovl_0613();
              if ((bool)bVar7) {
                return 0xcef5;
              }
              bVar7 = false;
            }
            goto L_045d;
          }
          in_NT = (in_NT & 1) != 0;
          bVar13 = (bVar13 & 1) != 0;
          in_IF = (in_IF & 1) != 0;
          in_TF = (in_TF & 1) != 0;
          bVar11 = (bVar11 & 1) != 0;
          bVar10 = (bVar10 & 1) != 0;
          in_AF = (in_AF & 1) != 0;
          bVar9 = (bVar9 & 1) != 0;
          G_swwill = 0;
          if ((bVar7 & 1) != 0) {
            return uVar6;
          }
          bVar7 = 0;
          in_BX = param_3;
L_042f:
          ovl_02bc();
          param_3 = in_BX;
        } while( true );
      }
      bVar7 = bVar2 < 0x39;
      bVar13 = SBORROW1(bVar2,'9');
      cVar1 = bVar2 - 0x39;
      bVar11 = cVar1 < '\0';
      bVar10 = cVar1 == '\0';
      bVar9 = (POPCOUNT(cVar1) & 1U) == 0;
      if (!(bool)bVar10 && '8' < (char)bVar2) goto L_0410;
      uVar8 = 0xfff6 < -(uint)(byte)(bVar2 - 0x30);
      G_UserDelay = -(uint)(byte)(bVar2 - 0x30) + 9;
      G_headsw = 1;
    }
    param_2 = 0x1ca8;
    ovl_0a98();
    uVar6 = ovl_0613();
    if ((bool)uVar8) {
      if (G_endcmbt < 1) {
        return uVar6;
      }
      return uVar6;
    }
  } while( true );
}


// ===== ovl_04a6 @ 1ca8:04a6

void __cdecl16near ovl_04a6(void)

{
  undefined2 *puVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  undefined1 *extraout_DX;
  uint uVar5;
  byte *pbVar6;
  int unaff_SI;
  undefined2 unaff_DS;
  int iVar7;
  
  uVar5 = 0;
  do {
    bVar2 = 0;
    pbVar6 = (byte *)*(undefined2 *)(uVar5 + &G_crecptrs);
    if (((pbVar6[5] & 0x18) == 0) &&
       ((pbVar6[3] != 0x20 ||
        (bVar2 = 0, (*(byte *)(unaff_SI + (uint)pbVar6[0x1f] + -0x633c) & 0x80) != 0)))) {
      if (((pbVar6[5] & 0x80) != 0) && ((pbVar6[5] & 2) != 0)) {
        pbVar6[5] = pbVar6[5] & 0x7f;
        *pbVar6 = *pbVar6 & 0x7f;
        (pbVar6 + 10)[0] = 1;
        (pbVar6 + 10)[1] = 0;
        LOCK();
        iVar7 = G_savebx;
        G_savebx = (int)pbVar6;
        UNLOCK();
        EXE_FirsTil(uVar5 >> 1);
        LOCK();
        pbVar6 = (byte *)G_savebx;
        G_savebx = iVar7;
        UNLOCK();
        *(undefined1 *)((uVar5 >> 1) + &G_pltilno) = *extraout_DX;
        puVar1 = (undefined2 *)(G_savebx + 0x120);
        EXE_RestBG(pbVar6[1],pbVar6[2],G_savebx,pbVar6,uVar5 >> 1
                          );
        ovl_1b25();
        ovl_0a15();
      }
      bVar2 = 0;
      if (((pbVar6[5] & 0xa0) == 0) && ((*pbVar6 & 0x20) == 0)) {
        bVar2 = 1;
        if ((pbVar6[0x13] == 0) ||
           ((0xb < (int)uVar5 ||
            ((*(byte *)(*(int *)(uVar5 + &G_heroptr) + 0xa5) & 0x80) == 0)))) {
          bVar4 = pbVar6[0x13] * '\b' + 4;
          if (0x31 < bVar4) {
            bVar2 = 2;
            bVar4 = pbVar6[0x13] * '\b' - 0x2e;
          }
          cVar3 = ovl_1b5b();
          if (cVar3 < (char)bVar4) {
            bVar2 = bVar2 + 1;
          }
        }
        else {
          bVar2 = 4;
        }
      }
    }
    pbVar6[0x1e] = bVar2;
    uVar5 = uVar5 + 2;
  } while ((int)uVar5 < 0x30);
  return;
}


// ===== ovl_05a8 @ 1ca8:05a8

void ovl_05a8(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_05ad @ 1ca8:05ad

void ovl_05ad(void)

{
  uint uVar1;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  int iVar2;
  
  uVar1 = 0;
  do {
    ovl_0a1b(uVar1);
    iVar2 = -0x2fc9;
    ovl_05ea();
    if (!(bool)in_CF) {
      G_crossovlycall = *(int *)(in_BX + 0x148) + 6;
      G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
      EXE_crossovlycall();
      EXE_FixMusRegs(in_BX);
      return;
    }
    uVar1 = iVar2 + 1;
    in_CF = 1;
  } while (uVar1 < 6);
  return;
}


// ===== ovl_05ea @ 1ca8:05ea

void ovl_05ea(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  if ((((G_timestop == '\x01') && (G_rec1+4 == '\x01')) ||
      ((G_rec1+5 & 0x99) != 0)) ||
     ((G_rec1+30 == '\0' || (G_rec1+25 != '\0')))) {
    return;
  }
  return;
}


// ===== ovl_0613 @ 1ca8:0613

undefined2 ovl_0613(void)

{
  undefined2 uVar1;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SumStat();
  ovl_0a1b();
  G_rec1+30 = G_rec1+30 + -1;
  ovl_0a2f();
  ovl_0a25();
  uVar1 = ovl_0650();
  if (G_endcmbt != 0) {
    return G_endcmbt;
  }
  if (G_rec1+30 == '\0') {
    ovl_05a8();
    uVar1 = ovl_05ad();
    return uVar1;
  }
  return uVar1;
}


// ===== ovl_0650 @ 1ca8:0650

void ovl_0650(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_0655 @ 1ca8:0655

void ovl_0655(void)

{
  byte *pbVar1;
  int iVar2;
  byte bVar3;
  uint in_AX;
  int iVar4;
  byte *pbVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  
  pbVar5 = (byte *)&G_crecs;
  iVar4 = 0x18;
  do {
    bVar3 = (byte)in_AX;
    if (bVar3 == pbVar5[4]) {
      if ((pbVar5[0xe] != 0) && (pbVar5[0xe] = pbVar5[0xe] - 1, pbVar5[0xe] == 0)) {
        ovl_1b25();
        ovl_0a15();
      }
      in_AX = in_AX & 0xff;
      if (((pbVar5[0x19] & 0xf) != 0) &&
         (pbVar5[0x19] = pbVar5[0x19] - 1, (pbVar5[0x19] & 0xf) == 0)) {
        *pbVar5 = *pbVar5 & 0xdf;
        in_AX = CONCAT11(1,bVar3);
      }
      if (((pbVar5[0x19] & 0xf0) != 0) &&
         (pbVar5[0x19] = pbVar5[0x19] - 0x10, (pbVar5[0x19] & 0xf0) == 0)) {
        pbVar5[5] = pbVar5[5] & 0xdf;
      }
      if (0x12 < (byte)iVar4) {
        iVar2 = *(int *)((0x18 - iVar4) * 2 + &G_heroptr);
        pbVar1 = (byte *)(iVar2 + 0xa5);
        *pbVar1 = *pbVar1 & 0x7f;
        if ((in_AX & 0x100) != 0) {
          pbVar1 = (byte *)(iVar2 + 0xbd);
          *pbVar1 = *pbVar1 & 0xdf;
        }
      }
    }
    pbVar5 = pbVar5 + 0x21;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}


// ===== ovl_06db @ 1ca8:06db

void ovl_06db(void)

{
  byte *pbVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_1c80();
  iVar2 = EXE_HeroSel(0,0);
  if (iVar2 == -1) {
    G_leader = 0;
    return;
  }
  if ((iVar2 == 0) ||
     ((pbVar1 = (byte *)*(undefined2 *)(iVar2 * 2 + &G_crecptrs), (*pbVar1 & 0xb0) == 0 &&
      ((pbVar1[5] & 0x70) == 0)))) {
    LOCK();
    G_leader = iVar2;
    UNLOCK();
    ovl_0a1b();
    G_rec1+5 = G_rec1+5 & 0xfb;
    ovl_0a25();
    G_headsw = G_leader;
    ovl_0a1b();
    G_rec1+5 = G_rec1+5 | 4;
    ovl_0a25();
    return;
  }
  G_leader = 0;
  return;
}


// ===== ovl_071f @ 1ca8:071f

void ovl_071f(void)

{
  undefined2 in_AX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  LOCK();
  G_leader = in_AX;
  UNLOCK();
  ovl_0a1b();
  G_rec1+5 = G_rec1+5 & 0xfb;
  ovl_0a25();
  G_headsw = G_leader;
  ovl_0a1b();
  G_rec1+5 = G_rec1+5 | 4;
  ovl_0a25();
  return;
}


// ===== ovl_0742 @ 1ca8:0742

void ovl_0742(void)

{
  int iVar1;
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_InitScrap();
  EXE_ClrTxtWnd(in_BX);
  iVar1 = 6;
  do {
    ovl_0761();
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_0761 @ 1ca8:0761

void ovl_0761(void)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined4 uVar4;
  
  if ((*(char *)(in_BX + 0x1e) != '\0') && ((*(byte *)(in_BX + 5) & 0x40) == 0)) {
    ovl_07e5();
    puVar1 = (undefined2 *)(G_savebx + 800);
    uVar4 = EXE_viaptr_puVar1();
    iVar3 = (int)((ulong)uVar4 >> 0x10);
    if ((uint)(*(int *)(in_BX + 10) << 2) < (uint)uVar4) {
      iVar3 = iVar3 + -2;
    }
    if (((iVar3 < 1) || (iVar2 = ovl_1b5b(), iVar3 * 8 + 0x32 < iVar2)) &&
       (*(byte *)(in_BX + 5) = *(byte *)(in_BX + 5) | 0x40, *(byte *)(in_BX + 0x1f) < 6)) {
      iVar3 = G_savebx;
      ovl_1b6c();
      EXE_ComTxt(0xf4);
      EXE_MyRet();
      EXE_InitScrap();
      EXE_AutoPause(G_UserDelay);
    }
  }
  return;
}


// ===== ovl_07e5 @ 1ca8:07e5

void ovl_07e5(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int in_BX;
  int iVar4;
  int iVar5;
  int unaff_SI;
  int iVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined4 uVar7;
  
  iVar6 = 0;
  iVar3 = 0;
  iVar2 = 0x18;
  iVar5 = G_crecptrs;
  do {
    if ((*(byte *)(iVar5 + 5) & 0x98) == 0) {
      iVar4 = G_savebx;
      G_crossovlycall = *(int *)(iVar4 + 0x148) + 0x7b;
      G_crossovlycall+2 = *(undefined2 *)(iVar4 + 0x14a);
      uVar7 = EXE_crossovlycall();
      iVar3 = (int)((ulong)uVar7 >> 0x10);
      iVar1 = (int)uVar7;
      if ((((iVar4 == 9) || (iVar4 == 6)) || (iVar4 == 5)) || (iVar4 == 2)) {
        iVar1 = iVar1 + 0x1e;
      }
      if (*(char *)(iVar5 + 4) == *(char *)(in_BX + 4)) {
        iVar6 = iVar6 + iVar1;
      }
      else {
        iVar3 = iVar3 + iVar1;
      }
    }
    iVar5 = iVar5 + 0x21;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if ((iVar6 != 0) && (iVar3 != 0)) {
    if (iVar6 < iVar3) {
      ovl_088c();
    }
    else {
      ovl_088c();
    }
  }
  return;
}


// ===== ovl_088c @ 1ca8:088c

int ovl_088c(void)

{
  int in_AX;
  int iVar1;
  uint unaff_DI;
  
  iVar1 = (in_AX + (unaff_DI >> 1)) / unaff_DI - 1;
  if (3 < iVar1) {
    iVar1 = 3;
  }
  return iVar1;
}


// ===== ovl_08a0 @ 1ca8:08a0

void ovl_08a0(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  if ((G_rec1+5 & 0x40) != 0) {
    G_mnusel = 0x2e;
  }
  return;
}


// ===== ovl_09a8 @ 1ca8:09a8

void ovl_09a8(void)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar3 = 5;
  iVar4 = G_crecptrs+2;
  do {
    if ((*(byte *)(iVar4 + 5) & 0x18) == 0) {
      iVar2 = ovl_0a6f();
      if (iVar2 != 0) {
        puVar1 = (undefined2 *)(G_savebx + 0x13c);
        EXE_SetTxtObj(iVar2,G_savebx);
        ovl_1c80();
        return;
      }
    }
    iVar4 = iVar4 + 0x21;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


// ===== ovl_0a07 @ 1ca8:0a07

void ovl_0a07(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_0a10 @ 1ca8:0a10

void ovl_0a10(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0xc;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_0a15 @ 1ca8:0a15

void __cdecl16near ovl_0a15(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_PageFlip();
  return;
}


// ===== ovl_0a1b @ 1ca8:0a1b

void ovl_0a1b(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0xf;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_0a20 @ 1ca8:0a20

void ovl_0a20(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0x12;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_0a25 @ 1ca8:0a25

void ovl_0a25(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0x15;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_0a2f @ 1ca8:0a2f

void ovl_0a2f(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0x1e;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_0a3e @ 1ca8:0a3e

void ovl_0a3e(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0x2d;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_0a43 @ 1ca8:0a43

void ovl_0a43(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0x36;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_0a48 @ 1ca8:0a48

void ovl_0a48(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0x3f;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_0a4d @ 1ca8:0a4d

void ovl_0a4d(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = *(int *)(in_BX + 0x148) + 0x30;
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
  EXE_crossovlycall();
  return;
}


// ===== ovl_0a6f @ 1ca8:0a6f

void ovl_0a6f(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_0a98 @ 1ca8:0a98

/* WARNING: Possible PIC construction at 0x0001d5c4: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0001d5c7) */

void ovl_0a98(void)

{
  byte bVar1;
  char cVar2;
  undefined2 *puVar3;
  code *pcVar4;
  char cVar5;
  byte bVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte extraout_DL;
  undefined2 extraout_DX;
  int *piVar11;
  int *piVar12;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 *puVar13;
  undefined2 unaff_DS;
  bool bVar14;
  undefined1 uVar15;
  int iStack000a;
  int in_stack_0000000e;
  
  G_curatt = G_curpla;
  ovl_0a1b();
  ovl_09e8();
  ovl_1b46();
  ovl_1b46();
  ovl_143d();
  cVar5 = ovl_1b5b();
  if ((cVar5 < *(char *)(G_LDRACE + G_loc+8)) &&
     (bVar14 = false,
     (*(byte *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0xa5) & 0x80) == 0)) {
    pcVar4 = INT_0x61_handler;
    (*pcVar4)();
    if ((!bVar14) && (ovl_148f(), !bVar14)) {
      return;
    }
  }
  bVar6 = *(byte *)(G_LDRACE + G_loc+12);
  bVar14 = bVar6 < G_rec1+10;
  if (((char)G_rec1+10 <= (char)bVar6) && (ovl_148f(), !bVar14)) {
    return;
  }
  bVar6 = *(byte *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0xba);
  bVar1 = *(byte *)(G_LDRACE + G_loc+10);
  bVar14 = bVar6 < bVar1;
  if (((char)bVar6 < (char)bVar1) && (ovl_148f(), !bVar14)) {
    return;
  }
  bVar6 = G_rec1+5;
joined_r0x0001d5bf:
  if ((bVar6 & 0x40) == 0) {
    ovl_1b46();
    ovl_1b46();
    do {
      if (*(char *)(*(int *)((uint)(byte)(G_rec1+7 << 1) + &G_crecptrs)
                   + 4) == G_rec1+4) {
        G_rec1+7 = 0xff;
      }
      iStack000a = in_BX;
      if (G_rec1+7 == -1) {
        ovl_11d1();
        G_swcrit = 1;
        cVar5 = ovl_124a();
        G_rec1+7 = cVar5;
        iStack000a = in_BX;
        if (cVar5 == -1) {
          ovl_11fb();
          cVar5 = ovl_124a();
          G_rec1+7 = cVar5;
          iStack000a = in_BX;
          if (cVar5 == -1) {
            bVar14 = G_curpla < 6;
            if ((bVar14) && (ovl_157b(), !bVar14)) {
              return;
            }
            goto L_0e75;
          }
        }
      }
      ovl_0a25();
      ovl_0a20();
      in_stack_0000000e = -0x2979;
      ovl_0d80();
      cVar5 = ovl_1b5b();
      in_BX = iStack000a;
      if (cVar5 < *(char *)(G_loc + G_LDRACE)) {
        bVar14 = G_curatt < 6;
        if ((int)G_curatt < 6) {
          ovl_157b();
          in_BX = iStack000a;
          if (!bVar14) {
            return;
          }
        }
        else {
          ovl_1553();
          in_BX = iStack000a;
          if (!bVar14) goto L_0ce6;
        }
      }
      if (G_curatt < 6) {
        G_crossovlycall = *(int *)(in_BX + 0x148) + 0x36;
        G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
        iVar8 = EXE_crossovlycall();
        if (iVar8 == 3) {
          iVar8 = EXE_SearchInv();
          uVar15 = iVar8 == 0;
          if (iVar8 != 1) {
            ovl_1c80();
            iVar8 = G_UserDelay;
            EXE_AutoPause();
            in_BX = iVar8;
            goto L_0c94;
          }
          goto L_0c9a;
        }
        uVar15 = 0;
        if (iVar8 != 0) goto L_0c9a;
L_0c94:
        ovl_19b7();
        if (!(bool)uVar15) {
          return;
        }
      }
      else {
L_0c9a:
        if ((G_curatt < 6) && ((G_rec1 & 0x10) != 0))
        goto L_0db1;
      }
      uVar7 = ovl_0a43();
      bVar14 = uVar7 < 3;
      if ((int)uVar7 < 3) {
        bVar6 = ovl_10bb();
        if (!bVar14) {
          G_zp_1415 = extraout_DX;
          ovl_09e8();
          ovl_09e8();
          iStack000a = in_BX;
          goto L_0ce6;
        }
        if ((bVar6 <= G_rec1+30) ||
           (bVar14 = G_rec1+30 == 0, 1 < G_rec1+30))
        goto L_0db1;
        ovl_0d33();
        iStack000a = in_BX;
        if (bVar14) goto L_0db1;
        goto L_0ce6;
      }
      ovl_10bb();
      if (!bVar14) goto L_0e75;
      ovl_1af1();
      if (!bVar14) {
        iStack000a = G_savebx;
        G_zp_1415 = G_rec2+1;
        ovl_09e8();
        goto L_0ce6;
      }
      if (OV_0x1286 == '\x01') goto code_r0x0001dc24;
      OV_0x1286 = 1;
      G_rec1+7 = 0xff;
    } while( true );
  }
  bVar14 = false;
  ovl_10ef();
  if (bVar14) {
    G_zp_1415 = G_rec1+1;
    G_FLEEBLOB = 1;
    if (G_curpla < 6) {
      G_FIREFLAG = 1;
    }
    ovl_0a3e();
    G_FIREFLAG = 0;
    G_FLEEBLOB = 0;
    iVar9 = 0;
    bVar6 = 0;
    iVar10 = 0x18;
    iVar8 = &G_crecs;
    do {
      if (((*(byte *)(iVar8 + 5) & 0x98) == 0) &&
         (G_rec1+4 != *(char *)(iVar8 + 4))) {
        iVar9 = iVar9 + *(int *)(iVar8 + 1);
        bVar6 = bVar6 + 1;
      }
      iVar8 = iVar8 + 0x21;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    if (bVar6 != 0) {
      iVar9 = (G_rec1+1 + 0x80a) -
              CONCAT11((byte)((char)((uint)iVar9 >> 8) + (bVar6 >> 1)) / bVar6,
                       (byte)((char)iVar9 + (bVar6 >> 1)) / bVar6);
    }
    piVar11 = (int *)(int *)G_FLEEPTR;
    bVar6 = (byte)((uint)iVar9 >> 8);
    piVar12 = piVar11;
    if ((6 < bVar6) && (piVar12 = piVar11 + 3, 0xb < bVar6)) {
      piVar12 = piVar11 + 6;
    }
    piVar11 = piVar12;
    if ((7 < (byte)iVar9) && (piVar11 = piVar12 + 1, 0xe < (byte)iVar9)) {
      piVar11 = piVar12 + 2;
    }
    G_WANNAFLEE = *piVar11 + G_rvarbuf;
    puVar3 = (undefined2 *)G_WANNAFLEE;
    puVar13 = (undefined2 *)puVar3;
    G_rec1+8 = 0xff70;
    iVar8 = 8;
    do {
      ovl_0118();
      if (*(byte *)((int)piVar11 + &G_blobmap) < extraout_DL) {
        G_rec1+8 =
             CONCAT11((char)((uint)*puVar13 >> 8) + G_rec1+2,
                      (char)*puVar13 + G_rec1+1);
      }
      puVar13 = puVar13 + 1;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    if ((G_rec1+5 & 4) != 0) {
      if (G_rec1+4 != '\0') {
        G_rec1+5 = G_rec1+5 & 0xfb;
        iVar8 = ovl_1089();
        if ((iVar8 != 0) && (iVar8 = ovl_1b5b(), iVar8 == 0)) goto L_107b;
      }
      cVar5 = G_rec1+4;
      cVar2 = G_rec1+31;
      iVar9 = 0x18;
      iVar8 = &G_crecs;
      do {
        if (((*(char *)(iVar8 + 4) == cVar5) && (*(char *)(iVar8 + &G_ssnwthrs+10) != cVar2)) &&
           (*(char *)(iVar8 + 0x11) != '\f')) {
          *(undefined1 *)(iVar8 + 0x11) = 0;
        }
        iVar8 = iVar8 + 0x21;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
    }
L_107b:
    if (G_rec1+8 == -0x90) goto L_0e75;
L_0db1:
    G_zp_1415 = G_rec1+8;
    G_bkonly = 0;
    if (G_curpla < 6) {
      G_FIREFLAG = 1;
    }
    ovl_0a3e();
    G_FIREFLAG = 0;
    iStack000a = -0x27a3;
    ovl_0118();
    if (*(char *)(in_BX + &G_blobmap) != '~') goto L_0de9;
    goto L_0e4c;
  }
  iStack000a = in_BX;
  if (G_curatt < 6) {
    return;
  }
  goto L_0ce6;
code_r0x0001dc24:
  OV_0x1286 = 0;
L_0e75:
  G_zp_1415 = G_rec1+1;
  G_bkonly = 0;
  if (G_curpla < 6) {
    G_FIREFLAG = 1;
  }
  ovl_0a3e();
  G_FIREFLAG = 0;
  iStack000a = -0x26df;
  ovl_0118();
L_0de9:
  ovl_0ea6();
  if (G_MVCNT != 0) {
    iVar8 = ovl_1b5b();
    G_CURDIR = *(undefined2 *)(iVar8 * 2 + &G_MVDIRS);
    puVar3 = (undefined2 *)(G_savebx + 0xfc);
    iVar8 = EXE_RMove();
    if (G_curpla < 6) {
      ovl_0a1b();
    }
    if (iVar8 == 1) {
L_0e4c:
      if (G_round1 != 1) {
        if (G_curatt < 6) {
          return;
        }
        iVar8 = G_savebx;
        ovl_1b6c();
        EXE_IModTxt();
        iStack000a = in_stack_0000000e;
        goto L_0d14;
      }
    }
    else {
      ovl_1b6c();
      iStack000a = -0x2744;
      ovl_1c80();
      pcVar4 = INT_0x61_handler;
      (*pcVar4)();
    }
  }
  if (G_curatt < 6) {
    return;
  }
L_0ce6:
  if (G_curatt < 6) {
    return;
  }
  EXE_SumStat();
  ovl_0650();
  if (G_endcmbt != 0) {
    return;
  }
  G_rec1+30 = G_rec1+30 + -1;
  ovl_0a25();
  uVar15 = false;
  if (G_rec1+30 == '\0') goto L_0d14;
  while( true ) {
    G_curpla = G_curatt;
    OV_0x1286 = 0;
    ovl_0a1b();
    ovl_05ea();
    if (!(bool)uVar15) break;
L_0d14:
    G_curatt = G_curatt + 1;
    uVar15 = G_curatt < 0x18;
    if (0x17 < (int)G_curatt) {
      uVar15 = G_round1 == 0;
      if (G_round1 == 1) {
        return;
      }
      G_round1 = 1;
      G_curatt = 6;
    }
  }
  (*(code *)*(undefined2 *)(iStack000a + 600))();
  in_stack_0000000e = -0x29f8;
  ovl_143d();
  ovl_10d7();
  bVar6 = G_rec1+5;
  in_BX = iStack000a;
  goto joined_r0x0001d5bf;
}


// ===== ovl_0b4b @ 1ca8:0b4b

void ovl_0b4b(void)

{
  char cVar1;
  code *pcVar2;
  undefined2 *puVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  byte bVar8;
  byte extraout_DL;
  undefined2 extraout_DX;
  int *piVar9;
  int *piVar10;
  int in_BX;
  int iVar11;
  int unaff_SI;
  int unaff_DI;
  undefined2 *puVar12;
  undefined2 unaff_DS;
  undefined1 in_CF;
  bool bVar13;
  undefined1 uVar14;
  int iStack0006;
  int iStack_2;
  
  G_LASTFLENO = 0xff;
  G_round1 = 0;
L_0b57:
  G_curatt = 6;
L_0b5d:
  G_curpla = G_curatt;
  OV_0x1286 = 0;
  ovl_0a1b();
  ovl_05ea();
  if (!(bool)in_CF) {
    (*(code *)*(undefined2 *)(in_BX + 600))(0x1000,G_rec1+3);
    iStack_2 = -0x29f8;
    ovl_143d();
    ovl_10d7();
    bVar13 = false;
    if ((G_rec1+5 & 0x40) == 0) {
      ovl_1b46();
      ovl_1b46();
      do {
        if (*(char *)(*(int *)((uint)(byte)(G_rec1+7 << 1) + &G_crecptrs
                              ) + 4) == G_rec1+4) {
          G_rec1+7 = 0xff;
        }
        if (G_rec1+7 == -1) {
          ovl_11d1();
          G_swcrit = 1;
          cVar4 = ovl_124a();
          G_rec1+7 = cVar4;
          if (cVar4 == -1) {
            ovl_11fb();
            cVar4 = ovl_124a();
            G_rec1+7 = cVar4;
            if (cVar4 == -1) {
              bVar13 = G_curpla < 6;
              if ((bVar13) && (ovl_157b(), !bVar13)) {
                return;
              }
              goto L_0e75;
            }
          }
        }
        ovl_0a25();
        ovl_0a20();
        ovl_0d80();
        cVar4 = ovl_1b5b();
        if (cVar4 < *(char *)(G_loc + G_LDRACE)) {
          bVar13 = G_curatt < 6;
          if ((int)G_curatt < 6) {
            ovl_157b();
            if (!bVar13) {
              return;
            }
          }
          else {
            ovl_1553();
            if (!bVar13) goto L_0ce6;
          }
        }
        if (G_curatt < 6) {
          G_crossovlycall = *(int *)(in_BX + 0x148) + 0x36;
          G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
          iVar11 = EXE_crossovlycall();
          if (iVar11 == 3) {
            iStack_2 = 0x51;
            iVar11 = EXE_SearchInv();
            uVar14 = iVar11 == 0;
            if (iVar11 != 1) {
              ovl_1c80();
              iVar11 = G_UserDelay;
              EXE_AutoPause();
              in_BX = iVar11;
              goto L_0c94;
            }
            goto L_0c9a;
          }
          uVar14 = 0;
          if (iVar11 != 0) goto L_0c9a;
L_0c94:
          ovl_19b7();
          if (!(bool)uVar14) {
            return;
          }
        }
        else {
L_0c9a:
          if ((G_curatt < 6) && ((G_rec1 & 0x10) != 0))
          goto L_0db1;
        }
        uVar5 = ovl_0a43();
        bVar13 = uVar5 < 3;
        if ((int)uVar5 < 3) {
          bVar8 = ovl_10bb();
          if (!bVar13) {
            G_zp_1415 = extraout_DX;
            ovl_09e8();
            ovl_09e8();
            goto L_0ce6;
          }
          if ((bVar8 <= G_rec1+30) ||
             (bVar13 = G_rec1+30 == 0, 1 < G_rec1+30))
          goto L_0db1;
          ovl_0d33();
          if (bVar13) goto L_0db1;
          goto L_0ce6;
        }
        ovl_10bb();
        if (!bVar13) goto L_0e75;
        ovl_1af1();
        if (!bVar13) {
          in_BX = G_savebx;
          G_zp_1415 = G_rec2+1;
          ovl_09e8();
          goto L_0ce6;
        }
        if (OV_0x1286 == '\x01') goto code_r0x0001dc24;
        OV_0x1286 = 1;
        G_rec1+7 = 0xff;
      } while( true );
    }
    ovl_10ef();
    if (bVar13) {
      G_zp_1415 = G_rec1+1;
      G_FLEEBLOB = 1;
      if (G_curpla < 6) {
        G_FIREFLAG = 1;
      }
      ovl_0a3e();
      G_FIREFLAG = 0;
      G_FLEEBLOB = 0;
      iVar6 = 0;
      bVar8 = 0;
      iVar7 = 0x18;
      iVar11 = &G_crecs;
      do {
        if (((*(byte *)(iVar11 + 5) & 0x98) == 0) &&
           (G_rec1+4 != *(char *)(iVar11 + 4))) {
          iVar6 = iVar6 + *(int *)(iVar11 + 1);
          bVar8 = bVar8 + 1;
        }
        iVar11 = iVar11 + 0x21;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      if (bVar8 != 0) {
        iVar6 = (G_rec1+1 + 0x80a) -
                CONCAT11((byte)((char)((uint)iVar6 >> 8) + (bVar8 >> 1)) / bVar8,
                         (byte)((char)iVar6 + (bVar8 >> 1)) / bVar8);
      }
      piVar9 = (int *)(int *)G_FLEEPTR;
      bVar8 = (byte)((uint)iVar6 >> 8);
      piVar10 = piVar9;
      if ((6 < bVar8) && (piVar10 = piVar9 + 3, 0xb < bVar8)) {
        piVar10 = piVar9 + 6;
      }
      piVar9 = piVar10;
      if ((7 < (byte)iVar6) && (piVar9 = piVar10 + 1, 0xe < (byte)iVar6)) {
        piVar9 = piVar10 + 2;
      }
      G_WANNAFLEE = *piVar9 + G_rvarbuf;
      puVar3 = (undefined2 *)G_WANNAFLEE;
      puVar12 = (undefined2 *)puVar3;
      G_rec1+8 = 0xff70;
      iVar11 = 8;
      do {
        ovl_0118();
        if (*(byte *)((int)piVar9 + &G_blobmap) < extraout_DL) {
          G_rec1+8 =
               CONCAT11((char)((uint)*puVar12 >> 8) + G_rec1+2,
                        (char)*puVar12 + G_rec1+1);
        }
        puVar12 = puVar12 + 1;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
      if ((G_rec1+5 & 4) != 0) {
        if (G_rec1+4 != '\0') {
          G_rec1+5 = G_rec1+5 & 0xfb;
          iVar11 = ovl_1089();
          if ((iVar11 != 0) && (iVar11 = ovl_1b5b(), iVar11 == 0)) goto L_107b;
        }
        cVar4 = G_rec1+4;
        cVar1 = G_rec1+31;
        iVar6 = 0x18;
        iVar11 = &G_crecs;
        do {
          if (((*(char *)(iVar11 + 4) == cVar4) && (*(char *)(iVar11 + &G_ssnwthrs+10) != cVar1))
             && (*(char *)(iVar11 + 0x11) != '\f')) {
            *(undefined1 *)(iVar11 + 0x11) = 0;
          }
          iVar11 = iVar11 + 0x21;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
L_107b:
      if (G_rec1+8 == -0x90) goto L_0e75;
L_0db1:
      G_zp_1415 = G_rec1+8;
      G_bkonly = 0;
      if (G_curpla < 6) {
        G_FIREFLAG = 1;
      }
      ovl_0a3e();
      G_FIREFLAG = 0;
      iStack0006 = -0x27a3;
      ovl_0118();
      if (*(char *)(in_BX + &G_blobmap) != '~') goto L_0de9;
      goto L_0e4c;
    }
    if (G_curatt < 6) {
      return;
    }
    goto L_0ce6;
  }
  goto L_0d14;
code_r0x0001dc24:
  OV_0x1286 = 0;
L_0e75:
  G_zp_1415 = G_rec1+1;
  G_bkonly = 0;
  if (G_curpla < 6) {
    G_FIREFLAG = 1;
  }
  ovl_0a3e();
  G_FIREFLAG = 0;
  iStack0006 = -0x26df;
  ovl_0118();
L_0de9:
  ovl_0ea6();
  if (G_MVCNT != 0) {
    iVar11 = ovl_1b5b();
    G_CURDIR = *(undefined2 *)(iVar11 * 2 + &G_MVDIRS);
    puVar3 = (undefined2 *)(G_savebx + 0xfc);
    iStack_2 = -0x2768;
    iVar11 = EXE_RMove();
    if (G_curpla < 6) {
      ovl_0a1b();
    }
    if (iVar11 == 1) {
L_0e4c:
      if (G_round1 != 1) {
        if (G_curatt < 6) {
          return;
        }
        iVar11 = G_savebx;
        ovl_1b6c();
        EXE_IModTxt();
        in_BX = iStack_2;
        goto L_0d14;
      }
    }
    else {
      ovl_1b6c();
      iStack0006 = -0x2744;
      ovl_1c80();
      pcVar2 = INT_0x61_handler;
      (*pcVar2)();
    }
  }
  in_BX = iStack0006;
  if (G_curatt < 6) {
    return;
  }
L_0ce6:
  if (G_curatt < 6) {
    return;
  }
  EXE_SumStat();
  ovl_0650();
  if (G_endcmbt != 0) {
    return;
  }
  G_rec1+30 = G_rec1+30 + -1;
  ovl_0a25();
  in_CF = 0;
  if (G_rec1+30 != '\0') goto L_0b5d;
L_0d14:
  G_curatt = G_curatt + 1;
  in_CF = G_curatt < 0x18;
  if (0x17 < (int)G_curatt) goto L_0d22;
  goto L_0b5d;
L_0d22:
  in_CF = G_round1 == 0;
  if (G_round1 == 1) {
    return;
  }
  G_round1 = 1;
  goto L_0b57;
}


// ===== ovl_0d33 @ 1ca8:0d33

void ovl_0d33(void)

{
  char cVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar2;
  undefined2 in_stack_00000008;
  undefined1 in_stack_0000000a;
  
  cVar1 = ovl_124a();
  if (cVar1 != -1) {
    uVar2 = 0;
    ovl_0a20();
    ovl_10bb();
    if (!(bool)uVar2) {
      LOCK();
      G_rec1+7 = G_rec2+31;
      UNLOCK();
      ovl_0d80();
      G_zp_1415 = G_rec2+1;
      ovl_09e8();
      ovl_09e8();
      G_rec1+8 = in_stack_00000008;
      G_rec1+7 = in_stack_0000000a;
      return;
    }
  }
  return;
}


// ===== ovl_0d80 @ 1ca8:0d80

void ovl_0d80(void)

{
  undefined1 uVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 in_stack_00000000;
  
  uVar1 = G_swcast;
  G_TILEXY = G_rec2+1;
  G_swcast = 0xff;
  G_swauto = 1;
  ovl_09e8(uVar1);
  G_swauto = 0;
  G_swcast = in_stack_00000000;
  return;
}


// ===== ovl_0ea6 @ 1ca8:0ea6

void ovl_0ea6(void)

{
  bool bVar1;
  undefined2 uVar2;
  byte in_CL;
  byte bVar3;
  int in_BX;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  int iVar5;
  undefined2 unaff_DS;
  
  G_MVCNT = 0;
  bVar3 = 7;
  do {
    iVar5 = unaff_DI + (uint)bVar3;
    unaff_DI = iVar5 - (uint)bVar3;
    iVar4 = in_BX * 2;
    uVar2 = *(undefined2 *)(iVar4 + &G_cmbcrds);
    if (((byte)((char)uVar2 + *(char *)(iVar5 + 0x163)) < 0xb) &&
       ((byte)((char)((uint)uVar2 >> 8) + *(char *)(iVar5 + 0x16b)) < 9)) {
      uVar2 = ovl_0118();
      if (*(byte *)(iVar4 + &G_blobmap) < in_CL) {
        iVar4 = G_MVCNT * 2;
        G_MVSQRS = uVar2;
        *(byte *)(iVar4 + &G_MVDIRS) = bVar3;
        *(undefined1 *)(iVar4 + &G_MVDIRS+1) = 0;
        G_MVCNT = G_MVCNT + 1;
      }
    }
    bVar1 = '\0' < (char)bVar3;
    bVar3 = bVar3 - 1;
  } while (bVar1);
  return;
}


// ===== ovl_1089 @ 1ca8:1089

undefined2 ovl_1089(void)

{
  byte in_AL;
  int iVar1;
  byte *pbVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  pbVar2 = (byte *)G_crecptrs+12;
  iVar1 = 0x12;
  while ((((pbVar2[4] == 0 || (pbVar2[3] != in_AL)) || ((pbVar2[5] & 0xf9) != 0)) ||
         ((*pbVar2 & 0xf0) != 0))) {
    pbVar2 = pbVar2 + 0x21;
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) {
      return 0;
    }
  }
  pbVar2[5] = pbVar2[5] | 4;
  return 1;
}


// ===== ovl_10bb @ 1ca8:10bb

void ovl_10bb(void)

{
  char in_AL;
  byte bVar1;
  char in_AH;
  byte bVar2;
  char in_DL;
  char in_DH;
  
  bVar1 = in_AL - in_DL;
  if (in_AL < in_DL) {
    bVar1 = -bVar1;
  }
  bVar2 = in_AH - in_DH;
  if (in_AH < in_DH) {
    bVar2 = -bVar2;
  }
  if (bVar1 < bVar2) {
    bVar1 = bVar2;
  }
  if (bVar1 < 2) {
    return;
  }
  return;
}


// ===== ovl_10d7 @ 1ca8:10d7

void ovl_10d7(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_rec1+31 != G_LASTFLENO) {
    G_LASTFLENO = G_rec1+31;
    ovl_0761();
  }
  return;
}


// ===== ovl_10ef @ 1ca8:10ef

void ovl_10ef(void)

{
  byte bVar1;
  int iVar2;
  int in_BX;
  int iVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar3 = 0;
  do {
    iVar2 = *(int *)(iVar3 + &G_fleetbl);
    if (iVar2 == -1) {
      return;
    }
    iVar3 = iVar3 + 2;
  } while (iVar2 != G_rec1+1);
  if (G_curatt < 6) {
    EXE_SetName(G_curatt);
  }
  else {
    (*(code *)*(undefined2 *)(in_BX + 600))(G_rec1+3);
  }
  EXE_SetTxtWnd(1);
  EXE_IComTxt(0xca,in_BX);
  ovl_1b46();
  ovl_0140();
  ovl_0a15();
  G_rec1+30 = 1;
  G_rec1+5 = G_rec1+5 | 0x10;
  G_rec1+1 = 0xffff;
  if (G_curatt < 6) {
    bVar1 = G_rec1+31;
    *(undefined1 *)((uint)bVar1 + &G_p1x) = 0xff;
    *(undefined1 *)((uint)bVar1 + &G_p1y) = 0xff;
  }
  ovl_0a25();
  ovl_0a48();
  return;
}


// ===== ovl_11d1 @ 1ca8:11d1

char ovl_11d1(void)

{
  int iVar1;
  byte bVar2;
  char cVar3;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  bVar2 = ovl_1217();
  iVar1 = G_loc+2;
  cVar3 = *(char *)(in_BX + iVar1);
  if ((cVar3 == -1) || (*(byte *)(in_BX + iVar1 + 1) <= bVar2)) {
    cVar3 = *(char *)(in_BX + iVar1 + 2);
  }
  return cVar3;
}


// ===== ovl_11fb @ 1ca8:11fb

undefined1 ovl_11fb(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_1217();
  return *(undefined1 *)(in_BX + G_loc+2 + 2);
}


// ===== ovl_1217 @ 1ca8:1217

void ovl_1217(void)

{
  ovl_1b5b();
  return;
}


// ===== ovl_124a @ 1ca8:124a

void ovl_124a(void)

{
  undefined2 in_AX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_CRITERION = in_AX;
  G_MINDIST = 100;
  G_MINSTAM = 30000;
  G_MINAGIL = 0x7f;
  G_MAXSTRN = 0;
  if (G_swcrit != 1) {
    G_CRITERION = G_CRITERION + 10;
  }
  ovl_1288();
  ovl_12c7();
  return;
}


// ===== ovl_1288 @ 1ca8:1288

void ovl_1288(void)

{
  undefined2 in_AX;
  uint uVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar2;
  int iVar3;
  
  G_CRITADR = in_AX;
  G_targcnt = 0;
  uVar2 = false;
  uVar1 = 0;
  do {
    ovl_0a20(uVar1);
    iVar3 = -0x22e0;
    ovl_12e1();
    if (!(bool)uVar2) {
      (*(code *)G_CRITADR)();
      if (!(bool)uVar2) {
        *(uint *)(G_targcnt * 2 + unaff_SI + -26000) =
             (uint)G_rec2+31;
        G_targcnt = G_targcnt + 1;
      }
    }
    uVar1 = iVar3 + 1;
    uVar2 = uVar1 < 0x18;
  } while (uVar1 != 0x18);
  return;
}


// ===== ovl_12c7 @ 1ca8:12c7

undefined2 ovl_12c7(void)

{
  int iVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_targcnt == 0) {
    return 0xff;
  }
  iVar1 = ovl_1b5b();
  return *(undefined2 *)(iVar1 * 2 + unaff_SI + -26000);
}


// ===== ovl_12e1 @ 1ca8:12e1

void ovl_12e1(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (((G_rec2+5 & 0x98) == 0) && (G_rec2+14 == '\0')) {
    if (G_swcrit == 1) {
      if (G_rec2+4 != G_rec1+4) {
        return;
      }
    }
    else if (G_rec2+4 == G_rec1+4) {
      return;
    }
  }
  return;
}


// ===== ovl_130e @ 1ca8:130e

undefined4 __cdecl16near ovl_130e(char param_1)

{
  int iVar1;
  int iVar2;
  undefined2 in_DX;
  int iVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar3 = G_crecptrs+12;
  iVar2 = 0x12;
  iVar1 = 0;
  do {
    if ((((*(byte *)(iVar3 + 5) & 0x98) == 0) && (*(char *)(iVar3 + 4) == '\x01')) &&
       (param_1 == *(char *)(iVar3 + 7))) {
      iVar1 = iVar1 + 1;
    }
    iVar3 = iVar3 + 0x21;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return CONCAT22(in_DX,iVar1);
}


// ===== ovl_143d @ 1ca8:143d

void ovl_143d(void)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_rec1+3 == ' ') {
    iVar4 = *(int *)((uint)G_rec1+31 * 2 + &G_crecptrs);
L_1474:
    cVar2 = *(char *)(iVar4 + 0x1f);
  }
  else {
    iVar3 = 0x18;
    iVar4 = &G_crecs;
    do {
      if ((G_rec1+4 == *(char *)(iVar4 + 4)) &&
         ((*(byte *)(iVar4 + 5) & 4) != 0)) goto L_1474;
      iVar4 = iVar4 + 0x21;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    cVar2 = '\0';
  }
  G_OWNLDR = cVar2;
  bVar1 = *(byte *)(iVar4 + 3);
  if (cVar2 == '\0') {
    bVar1 = G_rec1+3;
  }
  G_LDRACE = (uint)bVar1;
  return;
}


// ===== ovl_148f @ 1ca8:148f

void ovl_148f(void)

{
  undefined2 *puVar1;
  undefined2 in_AX;
  int iVar2;
  int iVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar3 = G_savebx;
  G_USEWHAT = in_AX;
  iVar2 = EXE_SearchInv(G_USEWHAT,G_curpla,
                     &G_invinfobuf);
  if ((iVar2 == 0) ||
     ((G_USEWHAT == 0x34 && ('\x01' < G_rec1+30)))) {
    return;
  }
  EXE_SetTxtObj(G_USEWHAT,iVar3);
  G_othername =
       *(undefined2 *)(G_curpla * 2 + &G_heroptr);
  G_othername+2 = unaff_DS;
  iVar3 = G_savebx;
  ovl_1c80();
  EXE_AutoPause(G_UserDelay);
  puVar1 = (undefined2 *)(G_savebx + 0x214);
  EXE_DoUse(*(undefined2 *)(G_curpla * 2 + &G_heroptr),
                     &G_rec1,G_USEWHAT);
  ovl_0a25();
  ovl_0a1b();
  return;
}


// ===== ovl_1553 @ 1ca8:1553

void ovl_1553(void)

{
  undefined2 *puVar1;
  bool bVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar3;
  int iVar4;
  
  G_NUMSPLS = 2;
  G_SPELBUF1 = G_rec1+28;
  if (G_rec1+27 != -1) {
    G_SPELBUF1+2 =
         CONCAT11(G_rec1+27,G_rec1+27);
    G_NUMSPLS = G_NUMSPLS + 2;
  }
  if (G_rec1+24 != '\0') {
    G_SBUFPTR = &G_SPELBUF1;
    bVar2 = false;
    do {
      bVar3 = bVar2;
      ovl_1647();
      if (bVar3) {
        return;
      }
      iVar4 = -0x1fb7;
      ovl_15f8();
      if (!bVar3) {
        EXE_SetTxtSpell(G_curspl,iVar4);
        G_deftxtparms+6 = G_deftxtparms+4;
        G_deftxtparms+8 = unaff_DS;
        ovl_1b6c();
        ovl_1c80();
        G_swauto = 1;
        if (G_curatt < 6) {
          *(undefined1 *)(*(int *)(G_curatt * 2 + &G_heroptr) + 0xcb) =
               (char)G_curspl;
        }
        if (5 < G_curatt) {
          ovl_16e0();
        }
        puVar1 = (undefined2 *)(G_savebx + 0x1fc);
        EXE_Magic();
        G_rec1+32 = 1;
        G_swauto = 0;
        return;
      }
      bVar2 = true;
    } while (bVar3);
  }
  return;
}


// ===== ovl_157b @ 1ca8:157b

void ovl_157b(void)

{
  undefined2 *puVar1;
  bool bVar2;
  int iVar3;
  undefined2 *puVar4;
  int unaff_SI;
  int iVar5;
  undefined2 unaff_DS;
  bool bVar6;
  
  ovl_196d();
  puVar4 = (undefined2 *)(G_loc+22 + G_rec1+3 * 10);
  iVar3 = 5;
  do {
    iVar5 = unaff_SI;
    *(undefined2 *)(iVar5 + -0x649a) = *puVar4;
    puVar4 = puVar4 + 1;
    iVar3 = iVar3 + -1;
    unaff_SI = iVar5 + 2;
  } while (iVar3 != 0);
  *(undefined2 *)(iVar5 + -0x648c) = 9;
  if (*(char *)(iVar5 + -0x7718) != '\0') {
    *(int *)(iVar5 + -0x648e) = iVar5 + -0x64a2;
    bVar2 = false;
    do {
      bVar6 = bVar2;
      ovl_1647();
      if (bVar6) {
        return;
      }
      ovl_15f8();
      if (!bVar6) {
        EXE_slot0xe1a5(*(undefined2 *)(iVar5 + 0x58b1));
        *(undefined2 *)(iVar5 + 0x6a85) = *(undefined2 *)(iVar5 + 0x6a83);
        *(undefined2 *)(iVar5 + 0x6a87) = unaff_DS;
        ovl_1b6c();
        ovl_1c80();
        *(undefined2 *)(iVar5 + -0x6556) = 1;
        if (*(uint *)(iVar5 + 0x58ad) < 6) {
          *(undefined1 *)(*(int *)(*(int *)(iVar5 + 0x58ad) * 2 + iVar5 + 0x2b1e) + 0xcb) =
               (char)*(undefined2 *)(iVar5 + 0x58b1);
        }
        if (5 < *(uint *)(iVar5 + 0x58ad)) {
          ovl_16e0();
        }
        puVar1 = (undefined2 *)(*(int *)(iVar5 + -0x7292) + 0x1fc);
        EXE_viaptr_puVar1();
        *(undefined1 *)(iVar5 + -0x7710) = 1;
        *(undefined2 *)(iVar5 + -0x6556) = 0;
        return;
      }
      bVar2 = true;
    } while (bVar6);
  }
  return;
}


// ===== ovl_15f8 @ 1ca8:15f8

void ovl_15f8(void)

{
  int iVar1;
  uint uVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined1 uVar3;
  
  if (G_curspl == 0xff) {
    return;
  }
  G_TALIGN =
       *(undefined1 *)(G_curspl + &OV_0x1629);
  uVar3 = G_curtar < 0x17;
  if ((G_curtar < 0x18) && (ovl_1721(), !(bool)uVar3)) {
    return;
  }
  iVar1 = 0x18;
  uVar2 = G_crecptrs;
  do {
    ovl_1721();
    if (!(bool)uVar3) {
      G_rec1+7 = '\x18' - (char)iVar1;
      ovl_0a20();
      ovl_0d80();
      return;
    }
    uVar3 = 0xffde < uVar2;
    uVar2 = uVar2 + 0x21;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_1647 @ 1ca8:1647

void ovl_1647(void)

{
  char cVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int unaff_SI;
  char *pcVar6;
  undefined2 unaff_DS;
  
  if (G_NUMSPLS == 0) {
    return;
  }
  puVar2 = (undefined2 *)(G_savebx + 0x134);
  iVar3 = EXE_RndCo(G_NUMSPLS,G_savebx
                            );
  cVar1 = *(char *)(G_SBUFPTR + iVar3);
  G_curspl = CONCAT11((char)((uint)iVar3 >> 8),cVar1);
  pcVar5 = (char *)G_SBUFPTR;
  pcVar6 = (char *)((unaff_SI * 2 + 0x36d6) - (int)pcVar5);
  G_SBUFPTR = pcVar6;
  iVar4 = 0;
  iVar3 = G_NUMSPLS;
  do {
    if (*pcVar5 != cVar1) {
      *pcVar6 = *pcVar5;
      pcVar6 = pcVar6 + 1;
      iVar4 = iVar4 + 1;
    }
    pcVar5 = pcVar5 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  G_NUMSPLS = iVar4;
  return;
}


// ===== ovl_16e0 @ 1ca8:16e0

void ovl_16e0(void)

{
  undefined2 *puVar1;
  int extraout_DX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if ((G_rec1+3 == ' ') || (G_rec1+3 == '\x1e')) {
    ovl_0a07();
  }
  else {
    puVar1 = (undefined2 *)(G_savebx + 0x1b8);
    EXE_FirsTil(G_curatt,G_savebx);
    *(undefined1 *)(G_curatt + &G_pltilno) =
         *(undefined1 *)(extraout_DX + 10);
    ovl_0a10();
    ovl_0a15();
  }
  return;
}


// ===== ovl_1721 @ 1ca8:1721

void ovl_1721(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar1;
  
  bVar1 = false;
  if ((*(byte *)(in_BX + 5) & 0x98) == 0) {
    ovl_1740();
    if (!bVar1) {
      (*(code *)(*(int *)(G_curspl * 2 + &OV_0x189c) + unaff_DI))();
      return;
    }
  }
  return;
}


// ===== ovl_1740 @ 1ca8:1740

void ovl_1740(void)

{
  undefined2 *puVar1;
  byte bVar2;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if ((((*(char *)(in_BX + 0xe) == '\0') && (G_rec1+31 < 6)) &&
      (puVar1 = (undefined2 *)(G_savebx + 0x228),
      bVar2 = EXE_viaptr_puVar1(G_curspl,
                                 G_rec1+31),
      bVar2 <= G_rec1+13)) &&
     (*(char *)(*(int *)((uint)G_rec1+31 * 2 + &G_heroptr) +
                G_curspl + 0x7b) == '\0')) {
    return;
  }
  return;
}


// ===== ovl_196d @ 1ca8:196d

void ovl_196d(void)

{
  undefined2 *puVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar6;
  
  G_TALIGN = 1;
  iVar4 = 0x10;
  iVar2 = G_crecptrs+10;
  do {
    while( true ) {
      iVar5 = iVar2;
      bVar3 = *(byte *)(iVar5 + 0x26) & 0x82;
      bVar6 = bVar3 < 0x82;
      iVar2 = iVar5 + 0x21;
      if (bVar3 != 0x82) break;
      G_curspl = 0x28;
      ovl_1740();
      if (!bVar6) {
        G_rec1+7 = *(undefined1 *)(iVar5 + 0x40);
        ovl_0a20();
        ovl_0d80();
        puVar1 = (undefined2 *)(G_savebx + 0x15c);
        EXE_Magic();
        G_deftxtparms+6 = G_deftxtparms+4;
        G_deftxtparms+8 = unaff_DS;
        ovl_1b6c();
        ovl_1c80();
        G_swauto = 1;
        if (G_curatt < 6) {
          *(undefined1 *)(*(int *)(G_curatt * 2 + &G_heroptr) + 0xcb) =
               (char)G_curspl;
        }
        if (5 < G_curatt) {
          ovl_16e0();
        }
        puVar1 = (undefined2 *)(G_savebx + 0x1fc);
        EXE_Magic();
        G_rec1+32 = 1;
        G_swauto = 0;
        return;
      }
    }
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}


// ===== ovl_19b7 @ 1ca8:19b7

void ovl_19b7(void)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  int unaff_SI;
  undefined2 unaff_DS;
  
  pbVar5 = (byte *)(G_loc+24 + (uint)G_rec1+3 * 0x16);
  do {
    uVar4 = (uint)*pbVar5;
    if (*pbVar5 == 0) {
      return;
    }
    puVar1 = (undefined2 *)(G_savebx + 0x158);
    iVar2 = EXE_SearchInv(uVar4,G_curpla,&G_invinfobuf);
    if (((iVar2 != 0) && (G_invinfobuf+6 < 99)) &&
       (pbVar6 = (byte *)((uint)(byte)((char)uVar4 - 9) * 9 + G_weaponsptr),
       *pbVar6 <= G_rec1+18)) {
      if ((pbVar6[2] != 3) || (0x17 < G_rec1+7)) {
L_1a83:
        *(undefined1 *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0xbf) =
             (char)G_invinfobuf+2;
        G_rec1+15 = G_invinfobuf+1;
        iVar2 = G_savebx;
        EXE_SetTxtObj(G_rec1+15);
        ovl_1c80();
        ovl_0a25();
        EXE_SetPlTilNo(G_curatt);
        EXE_PDraw(G_curpla);
        ovl_0a15();
        EXE_AutoPause(G_UserDelay,iVar2);
        return;
      }
      iVar2 = G_savebx;
      iVar3 = EXE_ChkRng(G_rec2+1 & 0xff,
                         G_rec2+1 >> 8,1,0);
      if ((iVar3 == 0) &&
         (iVar3 = EXE_SearchInv(0x51,G_curpla,&G_invinfobuf),
         iVar3 != 0)) {
        EXE_SearchInv(uVar4,G_curpla,&G_invinfobuf);
        goto L_1a83;
      }
    }
    pbVar5 = pbVar5 + 1;
  } while( true );
}


// ===== ovl_1af1 @ 1ca8:1af1

void ovl_1af1(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_zp_1415 = G_rec2+1;
  ovl_09e8();
  return;
}


// ===== ovl_1b25 @ 1ca8:1b25

void __cdecl16near ovl_1b25(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x100);
  EXE_PDraw();
  return;
}


// ===== ovl_1b32 @ 1ca8:1b32

void ovl_1b32(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x178);
  EXE_PrtWrd(G_comtxtptr);
  return;
}


// ===== ovl_1b46 @ 1ca8:1b46

void ovl_1b46(void)

{
  undefined2 *puVar1;
  uint in_AX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x124);
  EXE_Wait((int)((in_AX & 0xff) * (uint)G_UserDelay) >> 2);
  return;
}


// ===== ovl_1b5b @ 1ca8:1b5b

void __cdecl16near ovl_1b5b(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x134);
  EXE_RndCo();
  return;
}


// ===== ovl_1b6c @ 1ca8:1b6c

void ovl_1b6c(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x1d0);
  EXE_SetName();
  return;
}


// ===== ovl_1c80 @ 1ca8:1c80

void ovl_1c80(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined2 uVar1;
  
  uVar1 = 0xff;
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap(G_comtxtptr);
  EXE_PrtScrap(uVar1,in_BX);
  return;
}


