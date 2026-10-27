// ===== ovl_0051 @ 1ca8:0051

void ovl_0051(void)

{
  ovl_130b();
  return;
}


// ===== ovl_0055 @ 1ca8:0055

void ovl_0055(void)

{
  ovl_169e();
  return;
}


// ===== ovl_0059 @ 1ca8:0059

void ovl_0059(void)

{
  ovl_0846();
  return;
}


// ===== ovl_005d @ 1ca8:005d

void ovl_005d(void)

{
  ovl_06a1();
  return;
}


// ===== ovl_0061 @ 1ca8:0061

void ovl_0061(void)

{
  ovl_05de();
  return;
}


// ===== ovl_0065 @ 1ca8:0065

void ovl_0065(void)

{
  ovl_06d6();
  return;
}


// ===== ovl_0069 @ 1ca8:0069

void ovl_0069(void)

{
  ovl_0620();
  return;
}


// ===== ovl_006d @ 1ca8:006d

void ovl_006d(void)

{
  ovl_053c();
  return;
}


// ===== ovl_0071 @ 1ca8:0071

void ovl_0071(void)

{
  ovl_05fb();
  return;
}


// ===== ovl_0075 @ 1ca8:0075

void ovl_0075(void)

{
  ovl_063d();
  return;
}


// ===== ovl_0079 @ 1ca8:0079

void ovl_0079(void)

{
  ovl_05c1();
  return;
}


// ===== ovl_007d @ 1ca8:007d

void ovl_007d(void)

{
  ovl_066f();
  return;
}


// ===== ovl_0081 @ 1ca8:0081

void ovl_0081(void)

{
  ovl_0a94();
  return;
}


// ===== ovl_0085 @ 1ca8:0085

void ovl_0085(void)

{
  ovl_076c();
  return;
}


// ===== ovl_0089 @ 1ca8:0089

void ovl_0089(void)

{
  ovl_14fd();
  return;
}


// ===== ovl_008d @ 1ca8:008d

void ovl_008d(void)

{
  ovl_13f1();
  return;
}


// ===== ovl_0091 @ 1ca8:0091

void ovl_0091(void)

{
  ovl_0d01();
  return;
}


// ===== ovl_0095 @ 1ca8:0095

void ovl_0095(void)

{
  ovl_0a40();
  return;
}


// ===== ovl_0099 @ 1ca8:0099

void ovl_0099(void)

{
  ovl_0bb1();
  return;
}


// ===== ovl_009d @ 1ca8:009d

void ovl_009d(void)

{
  ovl_0be8();
  return;
}


// ===== ovl_00a1 @ 1ca8:00a1

void ovl_00a1(void)

{
  ovl_0c1e();
  return;
}


// ===== ovl_00a5 @ 1ca8:00a5

void ovl_00a5(void)

{
  ovl_0c28();
  return;
}


// ===== ovl_0374 @ 1ca8:0374

int ovl_0374(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  iVar1 = iRam000004f8 + -0x100;
  *(undefined2 *)(*piRam000004fc + -0x728a) = piRam000004fc;
  return iVar1;
}


// ===== ovl_0395 @ 1ca8:0395

void ovl_0395(void)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  int in_BX;
  int unaff_SI;
  uint unaff_DI;
  undefined2 unaff_DS;
  byte bVar5;
  int iStack0004;
  
  ovl_0374();
  OV_0x233 = 0;
  OV_0x1b3 = 0;
  OV_0x1c6 = 0;
  G_lookprt = 1;
  OV_0x234 = 0xff;
  OV_0x1c3 = G_lastdir;
  uVar2 = G_pwinxy;
  G_winxy = uVar2;
  OV_0x1c1 = uVar2;
  ovl_154f();
  G_curreg = 0xff;
  ovl_14fd();
  G_curmap = 0xff;
  ovl_13f1();
  G_curbfl = 0xff;
  EXE_FixMusRegs();
  EXE_InitNPC();
  FUN_1000_e4c7();
  ovl_169e();
  ovl_15e4();
L_0404:
  do {
    ovl_13d2();
    EXE_InitMap();
    ovl_130b();
    ovl_0a94();
    ovl_076c();
    while( true ) {
      while( true ) {
        while( true ) {
          while( true ) {
            while( true ) {
              while( true ) {
                iVar3 = EXE_Parser();
                if (G_restarting != 0) {
                  return;
                }
                if (iVar3 == 0xfd) goto L_0404;
                if (iVar3 != 0xfe) break;
                ovl_13d2();
              }
              G_lookdata = 0xff;
              if (G_used == -1) break;
              LOCK();
              cVar1 = G_used;
              G_used = -1;
              UNLOCK();
              if (cVar1 == '?') {
                ovl_1334();
                goto L_0404;
              }
              if (cVar1 == '@') goto L_0404;
              if (cVar1 == 'K') {
                ovl_1349();
              }
              else {
                G_used = cVar1;
                EXE_NoUse();
              }
            }
            if (G_whspnum == -1) break;
            ovl_15b0();
            G_whspnum = 0xff;
          }
          if (iVar3 != 4) break;
          ovl_1576();
        }
        if (iVar3 == 5) break;
        if (iVar3 == 6) {
          EXE_CalUpd();
          ovl_15e4();
          ovl_130b();
          ovl_169e();
          ovl_0846();
          if (OV_0x233 != '\0') {
            return;
          }
          ovl_0a94();
          ovl_076c();
        }
        else if (((G_curmen == 5) && (uVar4 = iVar3 - 0x31, uVar4 < 9)) &&
                (uVar4 != 4)) {
          OV_0x1c1 = G_winxy;
          OV_0x1c3 = uVar4;
          uVar4 = *(uint *)(uVar4 * 2 + &OV_0x6af);
          bVar5 = CARRY2(uVar4,unaff_DI);
          (*(code *)(uVar4 + unaff_DI))();
          if (OV_0x233 != '\0') {
            return;
          }
          if ((bVar5 & 1) == 0) {
            ovl_10f7();
            ovl_14fd();
            ovl_169e();
            ovl_0846();
            if (OV_0x233 != '\0') {
              return;
            }
            ovl_0a94();
            ovl_076c();
          }
          else {
            iStack0004 = 0xe;
            EXE_GameSound();
            in_BX = iStack0004;
          }
          if (G_swcamp != '\0') {
            if (OV_0x1c6 == '\0') {
              return;
            }
            G_swcamp = 0;
            if (OV_0x1c6 == '\x02') {
              OV_0x1c6 = 0;
            }
            return;
          }
        }
      }
      if (OV_0x1c6 != '\x01') break;
      ovl_126a();
      ovl_158d();
    }
    EXE_LoadOvly(0x5d);
    EXE_RoomPgm();
    EXE_Reload91();
    FUN_1000_e4c7();
    if (G_docmbt != 0) {
      return;
    }
  } while( true );
}


// ===== ovl_05c1 @ 1ca8:05c1

void ovl_05c1(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar1;
  
  uVar1 = 0;
  if (G_winy == '\0') {
    ovl_1576();
    return;
  }
  G_winy = G_winy + -1;
  ovl_0753();
  ovl_0cb2();
  if ((bool)uVar1) {
    G_winy = G_winy + '\x01';
    ovl_073a();
    return;
  }
  return;
}


// ===== ovl_05de @ 1ca8:05de

void ovl_05de(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar1;
  
  uVar1 = G_p1y != -1;
  if (G_p1y == -1) {
    ovl_1576();
    return;
  }
  G_winy = G_winy + '\x01';
  ovl_073a();
  ovl_0cb2();
  if ((bool)uVar1) {
    G_winy = G_winy + -1;
    ovl_0753();
    return;
  }
  return;
}


// ===== ovl_05fb @ 1ca8:05fb

void ovl_05fb(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar1;
  
  uVar1 = G_p1x != -1;
  if (G_p1x == -1) {
    ovl_1576();
    return;
  }
  G_winxy = G_winxy + '\x01';
  ovl_0708();
  ovl_0cb2();
  if ((bool)uVar1) {
    G_winxy = G_winxy + -1;
    ovl_0721();
    return;
  }
  return;
}


// ===== ovl_0620 @ 1ca8:0620

void ovl_0620(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar1;
  
  uVar1 = 0;
  if (G_winxy == '\0') {
    ovl_1576();
    return;
  }
  G_winxy = G_winxy + -1;
  ovl_0721();
  ovl_0cb2();
  if ((bool)uVar1) {
    G_winxy = G_winxy + '\x01';
    ovl_0708();
    return;
  }
  return;
}


// ===== ovl_063d @ 1ca8:063d

void ovl_063d(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar1;
  
  if ((G_winxy == '\0') || (uVar1 = 0, G_winy == '\0')) {
    ovl_1576();
    return;
  }
  G_winxy = G_winxy + -1;
  G_winy = G_winy + -1;
  ovl_0721();
  ovl_0753();
  ovl_0cb2();
  if ((bool)uVar1) {
    G_winxy = G_winxy + '\x01';
    G_winy = G_winy + '\x01';
    ovl_0708();
    ovl_073a();
    return;
  }
  return;
}


// ===== ovl_066f @ 1ca8:066f

void ovl_066f(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar1;
  
  if ((G_p1x == -1) || (uVar1 = 0, G_winy == '\0')) {
    ovl_1576();
    return;
  }
  G_winxy = G_winxy + '\x01';
  G_winy = G_winy + -1;
  ovl_0708();
  ovl_0753();
  ovl_0cb2();
  if ((bool)uVar1) {
    G_winxy = G_winxy + -1;
    G_winy = G_winy + '\x01';
    ovl_0721();
    ovl_073a();
    return;
  }
  return;
}


// ===== ovl_06a1 @ 1ca8:06a1

void ovl_06a1(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar1;
  
  if ((G_winxy == '\0') ||
     (uVar1 = G_p1y != -1, G_p1y == -1)) {
    ovl_1576();
    return;
  }
  G_winxy = G_winxy + -1;
  G_winy = G_winy + '\x01';
  ovl_0721();
  ovl_073a();
  ovl_0cb2();
  if ((bool)uVar1) {
    G_winxy = G_winxy + '\x01';
    G_winy = G_winy + -1;
    ovl_0708();
    ovl_0753();
    return;
  }
  return;
}


// ===== ovl_06d6 @ 1ca8:06d6

void ovl_06d6(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar1;
  
  if ((G_p1x == -1) ||
     (uVar1 = G_p1y != -1, G_p1y == -1)) {
    ovl_1576();
    return;
  }
  G_winxy = G_winxy + '\x01';
  G_winy = G_winy + '\x01';
  ovl_0708();
  ovl_073a();
  ovl_0cb2();
  if ((bool)uVar1) {
    G_winxy = G_winxy + -1;
    G_winy = G_winy + -1;
    ovl_0721();
    ovl_0753();
    return;
  }
  return;
}


// ===== ovl_0708 @ 1ca8:0708

void ovl_0708(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = 6;
  iVar2 = 0;
  do {
    if (*(char *)(iVar2 + &G_party) != -1) {
      G_p1x = G_p1x + '\x01';
    }
    unaff_SI = unaff_SI + 1;
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_0721 @ 1ca8:0721

void ovl_0721(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = 6;
  iVar2 = 0;
  do {
    if (*(char *)(iVar2 + &G_party) != -1) {
      G_p1x = G_p1x + -1;
    }
    unaff_SI = unaff_SI + 1;
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_073a @ 1ca8:073a

void ovl_073a(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = 6;
  iVar2 = 0;
  do {
    if (*(char *)(iVar2 + &G_party) != -1) {
      G_p1y = G_p1y + '\x01';
    }
    unaff_SI = unaff_SI + 1;
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_0753 @ 1ca8:0753

void ovl_0753(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = 6;
  iVar2 = 0;
  do {
    if (*(char *)(iVar2 + &G_party) != -1) {
      G_p1y = G_p1y + -1;
    }
    unaff_SI = unaff_SI + 1;
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_076c @ 1ca8:076c

void ovl_076c(void)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar4;
  
  if (OV_0x1bb == 0) {
    if ((G_events+13 & 2) == 0) {
      return;
    }
  }
  else {
    OV_0x1bb = OV_0x1bb + -1;
  }
  OV_0x1b7 = 0;
  do {
    iVar2 = EXE_FindBit(&G_ptrlsta,OV_0x1b7);
    if (iVar2 == 0) {
      uVar1 = *(undefined2 *)(OV_0x1b7 * 2 + &G_ptrlxy);
      in_BX = G_savebx;
      bVar4 = false;
      if ((char)uVar1 != '\0') {
        G_zp_10 = uVar1;
        ovl_0a6c();
        if (!bVar4) {
          ovl_0833();
        }
      }
    }
    OV_0x1b7 = OV_0x1b7 + 1;
  } while (OV_0x1b7 != 0x80);
  OV_0x1b7 = 0;
  G_zp_0E = G_curreg << 3;
  do {
    uVar3 = EXE_FindBit(&G_grdsta,
                       G_zp_0E + OV_0x1b7);
    if (uVar3 == 0) {
      uVar3 = OV_0x1b7 * 3;
      bVar4 = CARRY2(uVar3,G_loc+18);
      G_zp_10 = *(undefined2 *)(uVar3 + G_loc+18);
      in_BX = G_savebx;
      uVar3 = ovl_0a6c();
      if (!bVar4) {
        uVar3 = ovl_0833();
      }
    }
    OV_0x1b7 = OV_0x1b7 + 1;
  } while (uVar3 < 8);
  return;
}


// ===== ovl_0833 @ 1ca8:0833

void ovl_0833(void)

{
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x1b1 = 0xf;
  G_zp_12 = G_zp_10;
  ovl_0a1c();
  return;
}


// ===== ovl_0846 @ 1ca8:0846

int ovl_0846(undefined2 param_1,undefined2 param_2,int param_3)

{
  int *piVar1;
  undefined1 *puVar2;
  uint uVar3;
  undefined2 *puVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  undefined1 extraout_DL;
  int unaff_SI;
  int unaff_DI;
  undefined2 *puVar8;
  undefined1 *puVar9;
  undefined2 unaff_DS;
  undefined1 in_CF;
  
  G_zp_10 =
       CONCAT11(G_p1y,G_p1x);
  ovl_0bb1();
  if ((bool)in_CF) {
    iVar6 = ovl_0be8();
    if (!(bool)in_CF) {
      uVar3 = OV_0x1ab;
      G_entrno = (char)uVar3;
      G_grpno =
           *(undefined1 *)(G_loc+20 + (uVar3 & 7));
      uVar5 = ovl_13aa();
      G_terrain = uVar5;
      G_diff =
           *(undefined1 *)(G_curreg + &OV_0x43a);
      G_ctype = 1;
      G_ambflg = 0;
      puVar4 = (undefined2 *)(G_savebx + 0x11c);
      iVar6 = EXE_FindBit(0x1000);
      if (iVar6 == 0) goto L_08b2;
    }
    return iVar6;
  }
  G_entrno = extraout_DL;
  G_grpno = *(undefined1 *)(OV_0x1b9 + 2);
  uVar5 = ovl_13aa();
  G_terrain = uVar5;
  G_diff = *(undefined1 *)(G_curreg + &OV_0x43a)
  ;
  G_ctype = 0;
  G_ambflg = 0;
  puVar4 = (undefined2 *)(G_savebx + 0x11c);
  iVar6 = EXE_FindBit(0x1000,&G_grdsta);
  if (iVar6 != 0) {
    return iVar6;
  }
L_08b2:
  G_cmbtyp = 1;
  if (G_swcamp != '\0') {
    OV_0x1b5 = 6;
    do {
      iVar6 = (OV_0x1b5 + -1) * 2;
      if ((*(int *)(iVar6 + &G_party) != 0xff) &&
         (*(char *)(*(int *)(iVar6 + &G_heroptr) + 0xb9) == '\t')) goto L_08f4;
      piVar1 = (int *)&OV_0x1b5;
      *piVar1 = *piVar1 + -1;
    } while (*piVar1 != 0);
    G_ambflg = 1;
  }
L_08f4:
  iVar6 = G_savebx;
  puVar8 = (undefined2 *)&G_exitdir;
  for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
    puVar4 = puVar8;
    puVar8 = puVar8 + 1;
    *puVar4 = 0;
  }
  puVar9 = (undefined1 *)&G_hroomrec;
  for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
    puVar2 = puVar9;
    puVar9 = puVar9 + 1;
    *puVar2 = 0;
  }
  G_hroomrec+5 = OV_0x1c1;
  G_hroomrec =
       CONCAT11(G_grpno,G_entrno);
  iVar7 = G_winxy;
  G_pwinxy = iVar7;
  G_wildxy = iVar7 + 0x405;
  G_rmdata+6 = 6;
  ovl_09bf();
  iVar6 = EXE_LoadTiles();
  G_docmbt = 1;
  if (G_swcamp == '\0') {
    return param_3;
  }
  return iVar6;
}


// ===== ovl_09bf @ 1ca8:09bf

undefined1 ovl_09bf(void)

{
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  return *(undefined1 *)((uint)G_terrain + &OV_0x46a);
}


// ===== ovl_09d1 @ 1ca8:09d1

void ovl_09d1(int param_1)

{
  undefined2 in_AX;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  int iVar1;
  
  OV_0x1b1 = in_AX;
  ovl_0a6c();
  if ((bool)in_CF) {
    return;
  }
  G_zp_12 = G_zp_10;
  while( true ) {
    ovl_0a1c();
    param_1 = param_1 + -1;
    if (param_1 == 0) break;
    EXE_RestBG(G_zp_12 & 0xff,G_zp_12 >> 8);
    iVar1 = 9;
    EXE_GameSound();
    in_BX = iVar1;
    EXE_Wait(5);
  }
  return;
}


// ===== ovl_0a1c @ 1ca8:0a1c

int ovl_0a1c(void)

{
  uint uVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar1 = G_zp_12 + G_winxy;
  G_zp_1415 = uVar1;
  G_zp_10 = uVar1;
  EXE_MaskChr(uVar1 & 0xff,uVar1 >> 8,OV_0x1b1);
  EXE_Locate(G_zp_10 & 0xff,G_zp_10 >> 8);
  *(undefined1 *)(G_zp_0A + 0x1c68) = (char)OV_0x1b1;
  return in_BX;
}


// ===== ovl_0a40 @ 1ca8:0a40

int ovl_0a40(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_Locate(G_zp_10 & 0xff,G_zp_10 >> 8);
  *(undefined1 *)(G_zp_0A + 0x1c68) = (char)OV_0x1b1;
  return in_BX;
}


// ===== ovl_0a6c @ 1ca8:0a6c

void ovl_0a6c(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  bVar3 = (byte)G_winxy;
  bVar1 = (byte)G_zp_10;
  if (bVar3 <= bVar1) {
    bVar2 = (byte)((uint)G_zp_10 >> 8);
    bVar1 = bVar1 - bVar3;
    if (((bVar1 < G_winxl) &&
        (bVar3 = (byte)((uint)G_winxy >> 8), bVar3 <= bVar2)) &&
       (bVar2 = bVar2 - bVar3, bVar2 < G_winyl)) {
      G_zp_10 = CONCAT11(bVar2,bVar1);
      return;
    }
  }
  return;
}


// ===== ovl_0a94 @ 1ca8:0a94

void ovl_0a94(void)

{
  char *pcVar1;
  byte bVar2;
  int iVar3;
  int extraout_DX;
  int extraout_DX_00;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined1 uVar4;
  bool bVar5;
  undefined2 uStack_8;
  int iStack_6;
  undefined2 uStack_4;
  int iVar6;
  
  uStack_4 = (char *)0x1ca8;
  iStack_6 = 0xd519;
  EXE_ClearShadowMap();
  OV_0x1b1 = 0x12;
  iVar3 = 6;
  uStack_4 = (char *)&G_capsta;
  do {
    uVar4 = false;
    bVar5 = true;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar1 = uStack_4;
      uStack_4 = uStack_4 + 1;
      uVar4 = *pcVar1 != '\0';
      bVar5 = *pcVar1 == '\0';
    } while (bVar5);
    if (bVar5) break;
    uVar4 = 0xfffa < (uint)-iVar3;
    iStack_6 = 0xd54b;
    ovl_0a6c();
    if (!(bool)uVar4) {
      iStack_6 = 0xd550;
      ovl_0a1c();
    }
  } while (iVar3 != 0);
  iStack_6 = 8;
  do {
    G_zp_10 =
         CONCAT11(G_p1y,G_p1x);
    iStack_6 = iStack_6 + -1;
    uStack_8 = 0x1000;
    uStack_4 = (char *)in_BX;
    EXE_SearSq();
    iVar3 = (int)uStack_4;
    uStack_4 = (char *)0xd576;
    ovl_0bb1();
    if ((bool)uVar4) {
      ovl_0be8();
      in_BX = iVar3;
      iVar6 = -0x2a7c;
      if (!(bool)uVar4) {
        uStack_4 = (char *)0xd58c;
        ovl_09d1();
        iStack_6 = &G_ptrleng;
        uStack_4 = (char *)OV_0x1ab;
        uStack_8 = 0x1000;
        EXE_SetBit();
        uVar4 = (undefined1 *)0xfffb < &uStack_8;
        in_BX = (int)uStack_4;
        iVar6 = iVar3;
      }
    }
    else {
      ovl_09d1();
      in_BX = iVar3;
      iVar6 = -0x2a82;
    }
    iStack_6 = iVar6 + -1;
  } while (iStack_6 != 0);
  iVar3 = 8;
  do {
    G_zp_10 =
         CONCAT11(G_p1y,G_p1x);
    iStack_6 = iVar3 + -1;
    uStack_8 = 0x1000;
    uStack_4 = (char *)in_BX;
    EXE_SearSq();
    in_BX = (int)uStack_4;
    uStack_4 = (char *)0xd5bf;
    ovl_0c1e();
    if ((bool)uVar4) {
      uStack_4 = (char *)0xd5db;
      uStack_4._1_1_ = ovl_0c28();
      if (!(bool)uVar4) {
        uStack_4._0_1_ = *(undefined1 *)(extraout_DX_00 + 9);
        bVar2 = *(byte *)(extraout_DX_00 + 4);
        goto L_0b69;
      }
    }
    else {
      bVar2 = *(byte *)(extraout_DX + 4);
      uStack_4._0_1_ = *(undefined1 *)((uint)bVar2 + &OV_0x402);
      uStack_4._1_1_ = *(byte *)((uint)bVar2 + &OV_0x416);
L_0b69:
      uVar4 = 0;
      if (bVar2 < 0x14) {
        iStack_6 = 0xd5f5;
        ovl_09d1();
        uVar4 = uStack_4._1_1_ < 0xfe;
        if (uStack_4._1_1_ != 0xfe) {
          uVar4 = 0;
          OV_0x234 = 3;
          uStack_4 = (char *)0xd608;
          ovl_1576();
        }
      }
    }
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      return;
    }
  } while( true );
}


// ===== ovl_0bb1 @ 1ca8:0bb1

void ovl_0bb1(void)

{
  int iVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  undefined4 uVar2;
  
  uVar2 = ovl_0b8c();
  if ((bool)in_CF) {
    return;
  }
  OV_0x1b9 = (int)((ulong)uVar2 >> 0x10);
  iVar1 = EXE_FindBit(&G_grdsta,(int)uVar2 + G_curreg * 8,in_BX);
  if (iVar1 == 0) {
    return;
  }
  return;
}


// ===== ovl_0be8 @ 1ca8:0be8

void ovl_0be8(void)

{
  int *piVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  int *piVar3;
  undefined2 unaff_DS;
  undefined1 in_ZF;
  
  piVar3 = (int *)&G_ptrlxy;
  iVar2 = 0x80;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    piVar1 = piVar3;
    piVar3 = piVar3 + 1;
    in_ZF = G_zp_10 == *piVar1;
  } while (!(bool)in_ZF);
  if ((bool)in_ZF) {
    OV_0x1ab = 0x7f - iVar2;
    iVar2 = EXE_FindBit(&G_ptrlsta,0x7f - iVar2);
    if (iVar2 == 0) {
      return;
    }
  }
  return;
}


// ===== ovl_0c1e @ 1ca8:0c1e

undefined4 ovl_0c1e(void)

{
  int *piVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  piVar1 = (int *)G_loc;
  iVar2 = 0;
  while( true ) {
    if ((char)*piVar1 == '\0') {
      return 5;
    }
    if (G_zp_10 == *piVar1) break;
    piVar1 = (int *)((int)piVar1 + 5);
    iVar2 = iVar2 + 1;
  }
  return CONCAT22(piVar1,iVar2);
}


// ===== ovl_0c28 @ 1ca8:0c28

undefined4 ovl_0c28(void)

{
  uint uVar1;
  int iVar2;
  undefined2 in_BX;
  int *piVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar4;
  
  piVar3 = (int *)G_loc+34;
  iVar2 = G_zp_10;
  do {
    if ((char)*piVar3 == -1) {
      return CONCAT22(in_BX,iVar2);
    }
    if (iVar2 == *piVar3) {
      bVar4 = *(byte *)((int)piVar3 + 7) < 0xfe;
      if (*(byte *)((int)piVar3 + 7) == 0xfe) {
        uVar1 = (uint)*(byte *)(piVar3 + 4);
L_0c5e:
        return CONCAT22(piVar3,uVar1);
      }
      uVar1 = ovl_0c64();
      if (!bVar4) goto L_0c5e;
      iVar2 = G_zp_10;
    }
    piVar3 = piVar3 + 5;
  } while( true );
}


// ===== ovl_0c64 @ 1ca8:0c64

void ovl_0c64(void)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  int in_DX;
  int in_BX;
  int unaff_SI;
  char *pcVar4;
  undefined2 unaff_DS;
  
  uVar3 = (uint)*(byte *)(in_DX + 7);
  pcVar4 = (char *)G_loc+36;
  do {
    if (uVar3 == 0) {
      while ((*pcVar4 != -1 &&
             (iVar2 = EXE_FindBit(&G_events,*pcVar4),
             iVar2 == 0))) {
        pcVar4 = pcVar4 + 2;
      }
      return;
    }
    iVar2 = 0xff;
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      pcVar1 = pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (*pcVar1 != -1);
    uVar3 = uVar3 - 1;
  } while( true );
}


// ===== ovl_0cb2 @ 1ca8:0cb2

int ovl_0cb2(void)

{
  int *piVar1;
  char *pcVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  byte bVar5;
  undefined1 uVar6;
  int iVar7;
  undefined2 *puVar8;
  char cVar9;
  int extraout_DX;
  int *piVar10;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar11;
  undefined4 uVar12;
  
  OV_0xdb0 = 5;
  do {
    if (((*(int *)(OV_0xdb0 * 2 + &G_party) != 0xff) &&
        ((*(uint *)(*(int *)(OV_0xdb0 * 2 + &G_heroptr) + 0xbd) & 0xfc) !=
         0)) && (G_sailsw != '\x01')) {
      EXE_SetName(OV_0xdb0,in_BX);
      iVar7 = ovl_15b0();
      return iVar7;
    }
    piVar1 = (int *)&OV_0xdb0;
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
  } while (SBORROW2(iVar7,1) == *piVar1 < 0);
  G_zp_1415 =
       CONCAT11(G_p1y,G_p1x);
  uVar6 = ovl_13aa();
  G_terrain = uVar6;
  iVar7 = ovl_12ea();
  bVar11 = false;
  if (iVar7 == 0) {
    G_zp_10 = G_zp_1415;
    uVar12 = ovl_0c28();
    iVar7 = (int)uVar12;
    if (bVar11) {
      iVar7 = EXE_ChkWlk();
      if (iVar7 == 0) {
        iVar7 = ovl_13aa();
        if (((char)iVar7 == '\r') && (bVar11 = false, G_sailsw != '\0')) {
          iVar7 = ovl_0f3b();
          if (bVar11) {
            return iVar7;
          }
        }
        else {
          if (G_sailsw != '\0') {
            return iVar7;
          }
          piVar10 = (int *)G_loc+16;
          while( true ) {
            bVar11 = false;
            if ((char)*piVar10 == '\0') break;
            if (*piVar10 == G_zp_1415) {
              bVar5 = *(byte *)(piVar10 + 1);
              G_pwinxy = *(undefined2 *)((int)piVar10 + 3);
              G_lastdir = OV_0x1c3;
              goto L_12a8;
            }
            piVar10 = (int *)((int)piVar10 + 5);
          }
          uVar6 = ovl_1070();
          if (!bVar11) {
            G_curcap = uVar6;
            ovl_1098();
            cVar9 = *(char *)((uint)G_curcap + &G_capsta);
            bVar11 = cVar9 == '\0';
            if (cVar9 == '\x01') {
              OV_0x1b3 = 0xf;
            }
            else {
              iVar7 = ovl_0f5c();
              if (bVar11) {
                return iVar7;
              }
              OV_0x1b3 = 0x24;
            }
            G_sailsw = 1;
            OV_0x1c6 = 0;
            bVar5 = G_curcap;
            *(undefined1 *)((uint)bVar5 + &G_capsta) = 5;
            if (bVar5 == 2) {
              G_capsta+2 = G_capsta+2 + '\x01';
            }
            return in_BX;
          }
          iVar7 = ovl_194e();
          if (iVar7 == 0) {
            return 0;
          }
        }
      }
      else {
        OV_0x1bd = 0;
        if (G_sailsw != '\0') {
          if (G_swcamp != '\0') {
            ovl_1576();
            iVar7 = EXE_PrtWrd();
            return iVar7;
          }
          ovl_1576();
          iVar7 = EXE_SetYN();
          if (iVar7 != 0) {
            iVar7 = ovl_13d2();
            return iVar7;
          }
          cVar9 = *(char *)((uint)G_curcap + &G_capdays);
          if (cVar9 == '\0') {
            ovl_1576();
          }
          else {
            G_deftxtparms+2 = cVar9;
            ovl_126a();
            ovl_158d();
          }
          iVar7 = EXE_SetYN();
          if (iVar7 == 0) {
            do {
              bVar11 = false;
              iVar7 = ovl_0fcc();
              if (bVar11) goto L_0df6;
            } while (iVar7 == 0);
          }
          else {
L_0df6:
            if (*(char *)((uint)G_curcap + &G_capdays) == '\0') {
              ovl_13d2();
              G_sailsw = 0;
              OV_0x1c6 = 0;
              uVar6 = ovl_1664();
              *(undefined1 *)(extraout_DX + &G_capdays) = uVar6;
              *(undefined1 *)(extraout_DX + &G_capsta) = 0;
              G_curter = 0;
              G_curcap = 0xff;
              iVar7 = ovl_13f1();
              return iVar7;
            }
            OV_0x1c5 = 0;
          }
          ovl_13d2();
          G_sailsw = 0;
          OV_0x1c6 = 0;
          bVar5 = G_curcap;
          *(undefined1 *)((uint)bVar5 + &G_capsta) = 1;
          pcVar2 = (char *)((uint)bVar5 + &G_capdays);
          *pcVar2 = *pcVar2 + OV_0x1c5;
          G_curcap = 0xff;
          in_BX = G_savebx;
          G_curter = 0;
        }
      }
      G_zp_10 = G_winxy;
      iVar7 = ovl_147c();
      if (iVar7 != -1) {
        if (iVar7 == 1) {
          iVar7 = EXE_InitMap();
        }
        return iVar7;
      }
      iVar7 = ovl_1576();
    }
    else if (G_sailsw == '\0') {
      OV_0x231 = (int)((ulong)uVar12 >> 0x10);
      ovl_10f7();
      LOCK();
      iVar7 = OV_0x231;
      OV_0x231 = in_BX;
      UNLOCK();
      G_pwinxy = *(undefined2 *)(iVar7 + 5);
      LOCK();
      in_BX = OV_0x231;
      OV_0x231 = iVar7;
      UNLOCK();
      goto L_10b8;
    }
  }
  else if (G_sailsw == '\0') {
    OV_0x231 = iVar7 + -2;
    ovl_10f7();
    G_pwinxy = G_winxy;
L_10b8:
    uVar6 = ovl_13aa();
    G_terrain = uVar6;
    G_curter = uVar6;
    G_lastdir = OV_0x1c3;
    iVar7 = OV_0x231;
    G_rmdata = *(undefined1 *)(iVar7 + 3);
    G_rmdata+6 = *(undefined1 *)(iVar7 + 4);
    G_rmdata+7 = (char)G_locspec;
    bVar5 = *(byte *)(iVar7 + 2);
L_12a8:
    EXE_SavLocD();
    puVar8 = (undefined2 *)((uint)bVar5 * 4 + G_loc+14);
    uVar3 = *puVar8;
    uVar4 = puVar8[1];
    cVar9 = (char)uVar3;
    G_curmpg = cVar9;
    G_curtils = (char)((uint)uVar3 >> 8);
    G_curvar = (char)uVar4;
    if (cVar9 == '\x04') {
      uVar6 = ovl_09bf();
      G_curtils = uVar6;
    }
    iVar7 = G_winxy + 0x405;
    G_wildxy = iVar7;
    OV_0x233 = 1;
    return iVar7;
  }
  return iVar7;
}


// ===== ovl_0d01 @ 1ca8:0d01

int ovl_0d01(void)

{
  char *pcVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  byte bVar4;
  undefined1 uVar5;
  int iVar6;
  undefined2 *puVar7;
  char cVar8;
  int extraout_DX;
  int *piVar9;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar10;
  undefined4 uVar11;
  
  G_zp_1415 =
       CONCAT11(G_p1y,G_p1x);
  uVar5 = ovl_13aa();
  G_terrain = uVar5;
  iVar6 = ovl_12ea();
  bVar10 = false;
  if (iVar6 == 0) {
    G_zp_10 = G_zp_1415;
    uVar11 = ovl_0c28();
    iVar6 = (int)uVar11;
    if (bVar10) {
      iVar6 = EXE_ChkWlk();
      if (iVar6 == 0) {
        iVar6 = ovl_13aa();
        if (((char)iVar6 == '\r') && (bVar10 = false, G_sailsw != '\0')) {
          iVar6 = ovl_0f3b();
          if (bVar10) {
            return iVar6;
          }
        }
        else {
          if (G_sailsw != '\0') {
            return iVar6;
          }
          piVar9 = (int *)G_loc+16;
          while( true ) {
            bVar10 = false;
            if ((char)*piVar9 == '\0') break;
            if (*piVar9 == G_zp_1415) {
              bVar4 = *(byte *)(piVar9 + 1);
              G_pwinxy = *(undefined2 *)((int)piVar9 + 3);
              G_lastdir = OV_0x1c3;
              goto L_12a8;
            }
            piVar9 = (int *)((int)piVar9 + 5);
          }
          uVar5 = ovl_1070();
          if (!bVar10) {
            G_curcap = uVar5;
            ovl_1098();
            cVar8 = *(char *)((uint)G_curcap + &G_capsta);
            bVar10 = cVar8 == '\0';
            if (cVar8 == '\x01') {
              OV_0x1b3 = 0xf;
            }
            else {
              iVar6 = ovl_0f5c();
              if (bVar10) {
                return iVar6;
              }
              OV_0x1b3 = 0x24;
            }
            G_sailsw = 1;
            OV_0x1c6 = 0;
            bVar4 = G_curcap;
            *(undefined1 *)((uint)bVar4 + &G_capsta) = 5;
            if (bVar4 == 2) {
              G_capsta+2 = G_capsta+2 + '\x01';
            }
            return in_BX;
          }
          iVar6 = ovl_194e();
          if (iVar6 == 0) {
            return 0;
          }
        }
      }
      else {
        OV_0x1bd = 0;
        if (G_sailsw != '\0') {
          if (G_swcamp != '\0') {
            ovl_1576();
            iVar6 = EXE_PrtWrd();
            return iVar6;
          }
          ovl_1576();
          iVar6 = EXE_SetYN();
          if (iVar6 != 0) {
            iVar6 = ovl_13d2();
            return iVar6;
          }
          cVar8 = *(char *)((uint)G_curcap + &G_capdays);
          if (cVar8 == '\0') {
            ovl_1576();
          }
          else {
            G_deftxtparms+2 = cVar8;
            ovl_126a();
            ovl_158d();
          }
          iVar6 = EXE_SetYN();
          if (iVar6 == 0) {
            do {
              bVar10 = false;
              iVar6 = ovl_0fcc();
              if (bVar10) goto L_0df6;
            } while (iVar6 == 0);
          }
          else {
L_0df6:
            if (*(char *)((uint)G_curcap + &G_capdays) == '\0') {
              ovl_13d2();
              G_sailsw = 0;
              OV_0x1c6 = 0;
              uVar5 = ovl_1664();
              *(undefined1 *)(extraout_DX + &G_capdays) = uVar5;
              *(undefined1 *)(extraout_DX + &G_capsta) = 0;
              G_curter = 0;
              G_curcap = 0xff;
              iVar6 = ovl_13f1();
              return iVar6;
            }
            OV_0x1c5 = 0;
          }
          ovl_13d2();
          G_sailsw = 0;
          OV_0x1c6 = 0;
          bVar4 = G_curcap;
          *(undefined1 *)((uint)bVar4 + &G_capsta) = 1;
          pcVar1 = (char *)((uint)bVar4 + &G_capdays);
          *pcVar1 = *pcVar1 + OV_0x1c5;
          G_curcap = 0xff;
          in_BX = G_savebx;
          G_curter = 0;
        }
      }
      G_zp_10 = G_winxy;
      iVar6 = ovl_147c();
      if (iVar6 != -1) {
        if (iVar6 == 1) {
          iVar6 = EXE_InitMap();
        }
        return iVar6;
      }
      iVar6 = ovl_1576();
    }
    else if (G_sailsw == '\0') {
      OV_0x231 = (int)((ulong)uVar11 >> 0x10);
      ovl_10f7();
      LOCK();
      iVar6 = OV_0x231;
      OV_0x231 = in_BX;
      UNLOCK();
      G_pwinxy = *(undefined2 *)(iVar6 + 5);
      LOCK();
      in_BX = OV_0x231;
      OV_0x231 = iVar6;
      UNLOCK();
      goto L_10b8;
    }
  }
  else if (G_sailsw == '\0') {
    OV_0x231 = iVar6 + -2;
    ovl_10f7();
    G_pwinxy = G_winxy;
L_10b8:
    uVar5 = ovl_13aa();
    G_terrain = uVar5;
    G_curter = uVar5;
    G_lastdir = OV_0x1c3;
    iVar6 = OV_0x231;
    G_rmdata = *(undefined1 *)(iVar6 + 3);
    G_rmdata+6 = *(undefined1 *)(iVar6 + 4);
    G_rmdata+7 = (char)G_locspec;
    bVar4 = *(byte *)(iVar6 + 2);
L_12a8:
    EXE_SavLocD();
    puVar7 = (undefined2 *)((uint)bVar4 * 4 + G_loc+14);
    uVar2 = *puVar7;
    uVar3 = puVar7[1];
    cVar8 = (char)uVar2;
    G_curmpg = cVar8;
    G_curtils = (char)((uint)uVar2 >> 8);
    G_curvar = (char)uVar3;
    if (cVar8 == '\x04') {
      uVar5 = ovl_09bf();
      G_curtils = uVar5;
    }
    iVar6 = G_winxy + 0x405;
    G_wildxy = iVar6;
    OV_0x233 = 1;
    return iVar6;
  }
  return iVar6;
}


// ===== ovl_0f3b @ 1ca8:0f3b

void ovl_0f3b(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (((G_events+12 & 0x40) == 0) && (G_p1y == 'e')) {
    ovl_1098();
    ovl_1576();
    return;
  }
  return;
}


// ===== ovl_0f5c @ 1ca8:0f5c

void ovl_0f5c(void)

{
  byte bVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar3;
  
  ovl_126a();
  ovl_158d();
  iVar2 = EXE_SetYN();
  if (iVar2 == 0) {
    while( true ) {
      bVar3 = false;
      iVar2 = ovl_0fcc();
      if (bVar3) break;
      if (iVar2 != 0) {
        bVar1 = G_curcap;
        *(undefined1 *)((uint)bVar1 + &G_capdays) = (char)iVar2;
        *(undefined1 *)((uint)bVar1 + &G_capsta) = 5;
        ovl_13d2();
        return;
      }
    }
  }
  ovl_13d2();
  return;
}


// ===== ovl_0f95 @ 1ca8:0f95

void ovl_0f95(void)

{
  byte bVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar3;
  int iStack0002;
  
  ovl_126a();
  ovl_158d();
  iVar2 = EXE_SetYN();
  if (iVar2 != 0) goto L_0fb3;
  do {
    while( true ) {
      bVar3 = false;
      iVar2 = ovl_0fcc();
      if (!bVar3) break;
L_0fb3:
      ovl_1576();
      iStack0002 = 0x1ca8;
      iVar2 = EXE_SetYN();
      in_BX = iStack0002;
      if (iVar2 == 0) {
        OV_0x1c6 = 1;
        EXE_slot0x1d5c(0x1000);
        EXE_slot0x1d60(0x1000,&OV_0x223,0x1000);
        return;
      }
    }
  } while (iVar2 == 0);
  bVar1 = G_curcap;
  *(undefined1 *)((uint)bVar1 + &G_capdays) = (char)iVar2;
  *(undefined1 *)((uint)bVar1 + &G_capsta) = 5;
  ovl_13d2();
  return;
}


// ===== ovl_0fcc @ 1ca8:0fcc

uint ovl_0fcc(void)

{
  int iVar1;
  uint uVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  G_deftxtparms+2 =
       *(undefined1 *)((uint)G_curcap + &OV_0x44a);
  ovl_1576();
  iVar1 = EXE_GetNum(0,99);
  if (iVar1 == 0) {
    return 0;
  }
  OV_0x1c5 = (char)iVar1;
  if (CONCAT11((char)((uint)iVar1 >> 8),
               (char)iVar1 + *(char *)((uint)G_curcap + &G_capdays)) <
      100) {
    G_deftxtparms =
         (uint)OV_0x1c5 * (uint)G_deftxtparms+2;
    ovl_1576();
    iVar1 = EXE_SetYN();
    if (iVar1 == 0) {
      iVar1 = EXE_Enough();
      if (iVar1 == 0) {
        uVar2 = EXE_IComTxt();
        return uVar2;
      }
      EXE_DecGold();
      uVar2 = (uint)OV_0x1c5;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    ovl_126a();
    ovl_158d();
    uVar2 = 0;
  }
  return uVar2;
}


// ===== ovl_1070 @ 1ca8:1070

int ovl_1070(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = 6;
  iVar2 = 0;
  while ((((char)G_zp_1415 != *(char *)(iVar2 + &G_boatx) ||
          ((char)((uint)G_zp_1415 >> 8) !=
           *(char *)(iVar2 + &G_boaty))) || (*(char *)(iVar2 + &G_capsta) == '\0'))
        ) {
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) {
      return iVar2;
    }
  }
  return iVar2;
}


// ===== ovl_1098 @ 1ca8:1098

void ovl_1098(void)

{
  char *pcVar1;
  int in_AX;
  int iVar2;
  int iVar3;
  int unaff_SI;
  char *pcVar4;
  undefined2 unaff_DS;
  
  iVar2 = in_AX + 2;
  pcVar4 = (char *)G_loc+10;
  do {
    iVar3 = 0xff;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar1 = pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (*pcVar1 != '\0');
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) {
      G_deftxtparms+6 = (int)pcVar4;
      G_deftxtparms+8 = unaff_DS;
      return;
    }
  } while( true );
}


// ===== ovl_10f7 @ 1ca8:10f7

void ovl_10f7(void)

{
  byte bVar1;
  undefined2 uVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  undefined1 uVar7;
  int iVar6;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x1a9 =
       CONCAT11(G_p1y,G_p1x);
  G_lastdir = OV_0x1c3;
  if (G_sailsw == '\0') {
    EXE_GameSound(7);
  }
  else {
    bVar1 = G_curcap;
    uVar2 = OV_0x1a9;
    *(undefined1 *)((uint)bVar1 + &G_boatx) = (char)uVar2;
    *(undefined1 *)((uint)bVar1 + &G_boaty) = (char)((uint)uVar2 >> 8);
  }
  (*(code *)*(undefined2 *)(in_BX + 200))(0x1000);
  if (G_swtext != '\0') {
    EXE_ClrTxtWnd();
    G_swtext = 0;
  }
  if (G_sailsw == '\0') {
    uVar4 = (uint)(byte)(*(char *)((uint)G_curter + &OV_0x376) + '\x04' +
                        *(char *)(G_weather + &OV_0x380));
    do {
      EXE_CalUpd1();
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
    if (*(char *)(unaff_SI + 10) == 'D') {
      EXE_CalUpd1();
    }
    uVar4 = 0;
    while ((*(int *)(uVar4 + &G_party) == 0xff ||
           (*(int *)(*(int *)(uVar4 + &G_heroptr) + 0xbd) == 0))) {
      if (0xb < uVar4) goto L_11de;
      uVar4 = uVar4 + 2;
    }
    EXE_CalUpd1();
L_11de:
    iVar5 = 6;
    uVar4 = 0;
    do {
      if (*(int *)(uVar4 + &G_party) != 0xff) {
        uVar7 = (undefined1)((uint)iVar5 >> 8);
        cVar3 = *(char *)(*(int *)(uVar4 + &OV_0x1c7) + G_weather) -
                G_tailorcharm;
        if (cVar3 < '\0') {
          cVar3 = '\0';
          uVar7 = 0;
        }
        iVar6 = CONCAT11(uVar7,cVar3 + *(char *)(CONCAT11((char)(uVar4 >> 8),
                                                          G_curter) +
                                                 &OV_0x398));
        do {
          EXE_DecSta(uVar4 >> 1,0xba,1);
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        EXE_IsHeTr(*(undefined2 *)(uVar4 + &G_heroptr));
      }
      uVar4 = uVar4 + 2;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  else if (G_swcamp == '\0') {
    uVar4 = (uint)(byte)(*(char *)(G_weather + &OV_0x38c) + 4);
    do {
      EXE_CalUpd1();
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
  ovl_15e4();
  EXE_SumStat();
  ovl_130b();
  if (OV_0x1b3 != 0) {
    ovl_126a();
    LOCK();
    OV_0x1b3 = 0;
    UNLOCK();
    ovl_158d();
  }
  return;
}


// ===== ovl_126a @ 1ca8:126a

void ovl_126a(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap(G_loc+10);
  EXE_AddScrap(G_loc+10);
  return;
}


// ===== ovl_12ea @ 1ca8:12ea

int * ovl_12ea(void)

{
  int unaff_SI;
  int *piVar1;
  undefined2 unaff_DS;
  
  piVar1 = (int *)G_loc;
  while( true ) {
    if ((char)*piVar1 == '\0') {
      return (int *)0x0;
    }
    if (*piVar1 == G_zp_1415) break;
    piVar1 = (int *)((int)piVar1 + 5);
  }
  return piVar1 + 1;
}


// ===== ovl_130b @ 1ca8:130b

void ovl_130b(void)

{
  undefined1 uVar1;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_ClearShadowMap();
  EXE_FillWindow(G_winxy & 0xff,G_winxy >> 8,in_BX);
  uVar1 = ovl_13aa();
  G_curter = uVar1;
  return;
}


// ===== ovl_1334 @ 1ca8:1334

void ovl_1334(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_loc+58 == '\0') {
    EXE_ShowMiniMap();
    return;
  }
  ovl_15b0();
  return;
}


// ===== ovl_1349 @ 1ca8:1349

void ovl_1349(void)

{
  undefined2 *puVar1;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x3cc);
  EXE_finishsong(0xe);
  puVar1 = (undefined2 *)(G_savebx + 0x3d0);
  EXE_finishsong(in_BX);
  if (((G_sailsw == '\0') || (G_p1y != 'd')) ||
     ((G_events+12 & 0x40) != 0)) {
    ovl_15b0();
    return;
  }
  ovl_1576();
  G_events+12 = G_events+12 | 0x40;
  return;
}


// ===== ovl_13aa @ 1ca8:13aa

void ovl_13aa(void)

{
  byte bVar1;
  uint in_AX;
  uint uVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar2 = EXE_Locate(in_AX & 0xff,in_AX >> 8);
  bVar1 = *(byte *)(G_tdata+2 + (uVar2 & 0xff));
  OV_0x1bf =
       CONCAT11(*(undefined1 *)((uint)bVar1 + &OV_0x148d),bVar1);
  return;
}


// ===== ovl_13d2 @ 1ca8:13d2

void ovl_13d2(void)

{
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_Menu(5);
  EXE_InitCom(&OV_0x223,0x1ca8,0xe,in_BX);
  return;
}


// ===== ovl_13f1 @ 1ca8:13f1

void ovl_13f1(void)

{
  int iVar1;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_zp_10 = G_winxy;
  iVar1 = ovl_147c();
  if (iVar1 == -1) {
    ovl_1576();
    return;
  }
  if (iVar1 == 1) {
    EXE_InitMap();
  }
  return;
}


// ===== ovl_1416 @ 1ca8:1416

uint ovl_1416(void)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  uint uVar6;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar3 = (uint)*(byte *)(G_loc+8 + -1);
  uVar6 = G_curseg;
  uVar4 = uVar3;
  do {
    bVar1 = *(byte *)(uVar6 + G_mapxptr);
    bVar5 = (byte)G_zp_10;
    if (bVar1 <= bVar5) {
      bVar2 = bVar1 + 0x2a;
      if (0xd5 < bVar1) {
        bVar2 = 0xff;
      }
      if (bVar5 < bVar2) {
        bVar1 = *(byte *)(uVar6 + G_mapyptr);
        bVar5 = (byte)((uint)G_zp_10 >> 8);
        if ((bVar1 <= bVar5) && (bVar5 < (byte)(bVar1 + 0x2a))) {
          return uVar6;
        }
      }
    }
    uVar6 = uVar6 + 1;
    if (uVar3 <= uVar6) {
      uVar6 = 0;
    }
    uVar4 = uVar4 - 1;
  } while (uVar4 != 0);
  return 0xffff;
}


// ===== ovl_141b @ 1ca8:141b

uint ovl_141b(void)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  byte bVar5;
  uint uVar6;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar3 = (uint)*(byte *)(G_loc+8 + -1);
  uVar6 = G_curseg;
  uVar4 = uVar3;
  do {
    bVar1 = *(byte *)(uVar6 + G_mapxptr);
    bVar5 = (byte)G_zp_10;
    if (bVar1 <= bVar5) {
      bVar2 = bVar1 + 0x20;
      if (0xdf < bVar1) {
        bVar2 = 0xff;
      }
      if (bVar5 < bVar2) {
        bVar1 = *(byte *)(uVar6 + G_mapyptr);
        bVar5 = (byte)((uint)G_zp_10 >> 8);
        if ((bVar1 <= bVar5) && (bVar5 < (byte)(bVar1 + 0x22))) {
          return uVar6;
        }
      }
    }
    uVar6 = uVar6 + 1;
    if (uVar3 <= uVar6) {
      uVar6 = 0;
    }
    uVar4 = uVar4 - 1;
  } while (uVar4 != 0);
  return 0xffff;
}


// ===== ovl_147c @ 1ca8:147c

int ovl_147c(void)

{
  int iVar1;
  undefined1 uVar3;
  int iVar2;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = ovl_141b();
  if (iVar1 != -1) {
    G_curseg = iVar1;
    G_mapx = (uint)*(byte *)(G_mapxptr + iVar1);
    G_mapy = (uint)*(byte *)(G_mapyptr + iVar1);
    uVar3 = (undefined1)((uint)iVar1 >> 8);
    iVar2 = CONCAT11(uVar3,*(undefined1 *)(G_loc+8 + iVar1));
    if (iVar2 == G_curmap) {
      iVar1 = 0;
    }
    else {
      EXE_LoadMap(iVar2,CONCAT11(uVar3,*(undefined1 *)(G_maptileptr + iVar1)),
                 0x4d);
      iVar1 = 1;
    }
  }
  return iVar1;
}


// ===== ovl_14d6 @ 1ca8:14d6

void ovl_14d6(void)

{
  byte in_AL;
  byte in_AH;
  int unaff_DI;
  
  for (; (((in_AL < OV_0x336 || (OV_0x338 < in_AL)) ||
          (in_AH < OV_0x337)) || (OV_0x339 < in_AH));
      unaff_DI = unaff_DI + 4) {
  }
  return;
}


// ===== ovl_14fd @ 1ca8:14fd

void ovl_14fd(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  int iVar4;
  int extraout_DX;
  int in_BX;
  int unaff_SI;
  undefined2 *puVar5;
  undefined2 unaff_DS;
  
  ovl_14d6();
  if (extraout_DX != G_curreg) {
    G_curreg = extraout_DX;
    EXE_LoadVar(0x52,extraout_DX + 0x20);
    EXE_NewLoc(&G_loc+40);
    puVar3 = (undefined2 *)((G_season & 0xff) * 0xc + G_loc+22)
    ;
    puVar5 = (undefined2 *)&G_ssnwthrs;
    for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
      puVar2 = puVar5;
      puVar5 = puVar5 + 1;
      puVar1 = puVar3;
      puVar3 = puVar3 + 1;
      *puVar2 = *puVar1;
    }
  }
  return;
}


// ===== ovl_154f @ 1ca8:154f

void ovl_154f(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = G_winxy + 0x405;
  iVar2 = 6;
  iVar3 = 0;
  do {
    if (*(int *)(iVar3 + &G_party) != 0xff) {
      G_p1x = (char)iVar1;
      G_p1y = (char)((uint)iVar1 >> 8);
    }
    iVar3 = iVar3 + 1;
    unaff_SI = unaff_SI + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


// ===== ovl_1576 @ 1ca8:1576

void ovl_1576(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap(G_loc+10);
  EXE_PrtScrap(OV_0x234,in_BX);
  OV_0x234 = 0xff;
  return;
}


// ===== ovl_15b0 @ 1ca8:15b0

void ovl_15b0(void)

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


// ===== ovl_15e4 @ 1ca8:15e4

void ovl_15e4(void)

{
  undefined1 uVar1;
  uint extraout_DX;
  uint uVar2;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar2 = 0;
  do {
    if (*(char *)(uVar2 + &G_capsta) == '\x02') {
      uVar1 = ovl_1664();
      *(undefined1 *)(extraout_DX + &G_capdays) = uVar1;
      *(undefined1 *)(extraout_DX + &G_capsta) = 0;
      uVar2 = extraout_DX;
    }
    else if (*(char *)(uVar2 + &G_capsta) == '\x03') {
      *(undefined1 *)(uVar2 + &G_boatx) = *(undefined1 *)(uVar2 + &OV_0x450);
      *(undefined1 *)(uVar2 + &G_boaty) = *(undefined1 *)(uVar2 + &OV_0x456);
    }
    else if (*(char *)(uVar2 + &G_capsta) == '\x04') {
      if (OV_0x1c6 != '\x01') {
        OV_0x1c6 = 2;
        ovl_0f95();
      }
    }
    else if (*(char *)(uVar2 + &G_capsta) == '\a') {
      OV_0x234 = 1;
      ovl_1576();
      *(undefined1 *)(uVar2 + &G_capsta) = 5;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 6);
  return;
}


// ===== ovl_1664 @ 1ca8:1664

byte ovl_1664(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int in_DX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  bVar1 = *(char *)(in_DX + &OV_0x450) - *(char *)(in_DX + &G_boatx);
  if ((char)bVar1 < '\0') {
    bVar1 = -bVar1;
  }
  bVar3 = *(char *)(in_DX + &OV_0x456) - *(char *)(in_DX + &G_boaty);
  if ((char)bVar3 < '\0') {
    bVar3 = -bVar3;
  }
  bVar2 = bVar1;
  if (bVar1 <= bVar3) {
    bVar2 = bVar3;
    bVar3 = bVar1;
  }
  bVar3 = (byte)(bVar3 + 2) >> 2;
  bVar1 = bVar2 + bVar3;
  if (CARRY1(bVar2,bVar3)) {
    bVar1 = 0xff;
  }
  return bVar1 >> 4;
}


// ===== ovl_169e @ 1ca8:169e

void ovl_169e(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int unaff_SI;
  undefined2 *puVar7;
  int unaff_DI;
  undefined2 *puVar8;
  undefined2 unaff_DS;
  bool bVar9;
  
  OV_0x1b5 = 0;
  do {
    iVar6 = OV_0x1b5;
    bVar3 = *(char *)(iVar6 + &G_lastgen) + *(char *)(iVar6 + &OV_0x42a);
    if (0xb < bVar3) {
      bVar3 = bVar3 - 0xc;
    }
    if ((uint)bVar3 == *(uint *)(unaff_SI + 6)) {
      *(byte *)(iVar6 + &G_lastgen) = bVar3;
      *(undefined1 *)(iVar6 + &G_ptrlsta) = 0;
      *(undefined1 *)(iVar6 + &G_grdsta) = 0;
      *(undefined1 *)(iVar6 + &G_ptrleng) = 0;
      puVar8 = (undefined2 *)(iVar6 * 0x10 + &G_ptrlxy);
      puVar7 = (undefined2 *)(iVar6 * 0x10 + &OV_0x236);
      for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
        puVar2 = puVar8;
        puVar8 = puVar8 + 1;
        puVar1 = puVar7;
        puVar7 = puVar7 + 1;
        *puVar2 = *puVar1;
      }
    }
    OV_0x1b5 = OV_0x1b5 + 1;
  } while (OV_0x1b5 != 0x10);
  iVar6 = G_savebx;
  uVar4 = 0;
  OV_0x1ad = 0;
  do {
    iVar5 = EXE_FindBit(&G_ptrlsta,uVar4);
    if (iVar5 == 0) {
      G_zp_10 =
           *(undefined2 *)(OV_0x1ad * 2 + &G_ptrlxy);
      iVar5 = ovl_1416();
      if (iVar5 == G_curseg) {
        uVar4 = OV_0x1ad;
        OV_0x1af = uVar4 >> 3;
        iVar5 = EXE_FindBit(&G_ptrleng,uVar4);
        bVar9 = false;
        if ((iVar5 == 0) || (ovl_17c0(), bVar9)) {
          ovl_18c1();
        }
        *(undefined2 *)(OV_0x1ad * 2 + &G_ptrlxy) =
             G_zp_10;
      }
    }
    OV_0x1ad = OV_0x1ad + 1;
    uVar4 = OV_0x1ad;
  } while (uVar4 < 0x80);
  return;
}


// ===== ovl_17c0 @ 1ca8:17c0

void ovl_17c0(void)

{
  int *piVar1;
  byte bVar2;
  undefined2 uVar3;
  int iVar4;
  byte bVar5;
  char cVar6;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  int *piVar7;
  undefined2 unaff_DS;
  bool bVar8;
  undefined1 uVar9;
  
  bVar5 = G_p1x;
  bVar2 = G_p1y;
  iVar4 = G_zp_10;
  if (CONCAT11(bVar2,bVar5) != iVar4) {
    uVar3 = 0;
    if (bVar5 != (byte)iVar4) {
      if (bVar5 < (byte)iVar4) {
        G_zp_10 = G_zp_10 + -1;
        uVar3 = 0xff;
      }
      else {
        G_zp_10 = G_zp_10 + '\x01';
        uVar3 = 1;
      }
    }
    bVar5 = (byte)((uint)iVar4 >> 8);
    bVar8 = bVar2 < bVar5;
    if (bVar2 != bVar5) {
      if (bVar8) {
        G_zp_11 = G_zp_11 + -1;
        uVar3 = CONCAT11(0xff,(char)uVar3);
      }
      else {
        G_zp_11 = G_zp_11 + '\x01';
        uVar3 = CONCAT11(1,(char)uVar3);
      }
    }
    G_zp_12 = iVar4;
    OV_0x188e = uVar3;
    ovl_1910();
    if (!bVar8) {
      piVar7 = (int *)&OV_0x1890;
      iVar4 = 8;
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        piVar1 = piVar7;
        piVar7 = piVar7 + 1;
      } while (OV_0x188e != *piVar1);
      iVar4 = (7 - iVar4) * 2;
      OV_0x188e = iVar4;
      uVar3 = *(undefined2 *)(iVar4 + &OV_0x18a0);
      bVar5 = (byte)((uint)uVar3 >> 8);
      bVar8 = CARRY1(bVar5,G_zp_13);
      cVar6 = bVar5 + G_zp_13;
      uVar9 = cVar6 == '\0';
      G_zp_10 =
           CONCAT11(cVar6,(char)uVar3 + G_zp_12);
      ovl_1910();
      if ((!bVar8) || (ovl_188f(), (bool)uVar9)) {
        uVar3 = *(undefined2 *)(OV_0x188e + &OV_0x18b0);
        bVar5 = (byte)((uint)uVar3 >> 8);
        bVar8 = CARRY1(bVar5,G_zp_13);
        cVar6 = bVar5 + G_zp_13;
        uVar9 = cVar6 == '\0';
        G_zp_10 =
             CONCAT11(cVar6,(char)uVar3 + G_zp_12);
        ovl_1910();
        if ((!bVar8) || (ovl_188f(), (bool)uVar9)) {
          G_zp_10 = G_zp_12;
          EXE_ClearBit();
          return;
        }
      }
    }
  }
  return;
}


// ===== ovl_188f @ 1ca8:188f

undefined2 ovl_188f(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar1 = G_curpla;
  G_curpla = 0;
  uVar2 = EXE_ChkRng(G_zp_10 & 0xff,G_zp_10 >> 8,
                     1);
  G_curpla = uVar1;
  return uVar2;
}


// ===== ovl_18c1 @ 1ca8:18c1

void ovl_18c1(void)

{
  undefined2 uVar1;
  byte bVar2;
  int iVar3;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar4;
  
  G_zp_12 = G_zp_10;
  uVar1 = EXE_RndCo(8);
  OV_0x188e = uVar1;
  iVar3 = 3;
  do {
    uVar1 = *(undefined2 *)
             (CONCAT11((char)((uint)OV_0x188e >> 8),
                       *(undefined1 *)(OV_0x188e + &OV_0x19b7)) + unaff_DI
             + 0x1890);
    bVar2 = (byte)((uint)uVar1 >> 8);
    bVar4 = CARRY1(bVar2,G_zp_13);
    G_zp_10 =
         CONCAT11(bVar2 + G_zp_13,(char)uVar1 + G_zp_12)
    ;
    ovl_1910();
    if (bVar4) {
      return;
    }
    OV_0x188e = OV_0x188e + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  G_zp_10 = G_zp_12;
  return;
}


// ===== ovl_1910 @ 1ca8:1910

void ovl_1910(void)

{
  int iVar1;
  int extraout_DX;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar2;
  
  iVar1 = ovl_1416();
  if (iVar1 == G_curseg) {
    G_zp_1415 = G_zp_10;
    ovl_14d6();
    if (extraout_DX == OV_0x1af) {
      iVar1 = EXE_ChkWlk();
      bVar2 = false;
      if (iVar1 != 0) {
        ovl_0c1e();
        if (bVar2) {
          ovl_0c28();
          if (bVar2) {
            ovl_0bb1();
            if (bVar2) {
              ovl_0be8();
              if (bVar2) {
                return;
              }
            }
          }
        }
      }
    }
  }
  return;
}


// ===== ovl_194e @ 1ca8:194e

undefined2 ovl_194e(void)

{
  uint uVar1;
  undefined2 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar3 = OV_0x1bf;
  if (((char)uVar3 != '\f') && ((char)uVar3 != '\r')) {
    OV_0x1bd = 0;
    return 0;
  }
  if (OV_0x1bd != 0) {
    ovl_15b0();
    return 0;
  }
  iVar4 = 6;
  G_workx = 0;
  do {
    iVar5 = (iVar4 + -1) * 2;
    if (*(int *)(iVar5 + &G_party) != 0xff) {
      uVar1 = *(uint *)(*(int *)((iVar4 + -1) * 2 + &G_heroptr) + 0x1c);
      *(uint *)(iVar5 + &G_scrap) = uVar1 & 0xff;
      uVar3 = uVar1 & 0xff;
      if ((char)uVar1 == '\0') {
        puVar2 = (undefined2 *)(G_savebx + 0x1d0);
        EXE_SetName(0x1000,iVar4 + -1,G_savebx);
        ovl_15b0();
        return 0;
      }
      if (G_workx <= uVar3) {
        G_workx = uVar3;
      }
    }
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar4 = CONCAT11((char)(uVar3 >> 8),*(undefined1 *)(G_weather + &OV_0x3f6));
  G_worky = iVar4;
  if (G_workx <= iVar4 - 99U >> 1) {
    ovl_15b0();
    return 0;
  }
  iVar4 = 6;
  while( true ) {
    iVar5 = (iVar4 + -1) * 2;
    if ((*(int *)(iVar5 + &G_party) != 0xff) &&
       (*(uint *)(iVar5 + &G_scrap) <=
        G_worky -
        (*(uint *)(*(int *)((iVar4 + -1) * 2 + &G_heroptr) + 0xba) & 0xff) >> 1)) break;
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
      OV_0x1bd = 1;
      return 1;
    }
  }
  puVar2 = (undefined2 *)(G_savebx + 0x1d0);
  EXE_SetName(0x1000,iVar4 + -1,G_savebx);
  ovl_15b0();
  return 0;
}


// ===== FUN_1000_e4c7 @ 1000:e4c7

void __cdecl16near FUN_1000_e4c7(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar5 = 0;
  iVar2 = 6;
  do {
    if (*(int *)(iVar5 + &G_party) != 0xff) {
      iVar1 = *(int *)(iVar5 + &G_heroptr);
      uVar3 = 6;
      iVar6 = iVar1;
      do {
        bVar4 = *(byte *)((uint)*(byte *)(iVar6 + 0xc0) + iVar1 + 0x2b);
        if ((0x2a < bVar4) && (bVar4 < 0x31)) goto L_1a88;
        iVar6 = iVar6 + 1;
        uVar3 = (uVar3 & 0xff) - 1;
      } while (uVar3 != 0);
      bVar4 = 0x31;
L_1a88:
      *(int *)(iVar5 + &OV_0x1c7) = (int)(char)((bVar4 - 0x2b) * '\f') + &OV_0x3a2;
    }
    iVar5 = iVar5 + 2;
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) {
      return;
    }
  } while( true );
}


// ===== ovl_1aaf @ 1ca8:1aaf

void ovl_1aaf(void)

{
  int iVar1;
  int in_BX;
  undefined2 unaff_DS;
  
  iVar1 = 3;
  do {
    EXE_GameSound(0xf);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_1ac2 @ 1ca8:1ac2

void ovl_1ac2(void)

{
  uint uVar1;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_0374();
  ovl_1aaf();
  uVar1 = EXE_GetMagSkl(in_BX);
  OV_0x1bb = (uVar1 & 0xff) >> 2;
  ovl_076c();
  return;
}


// ===== ovl_1ae3 @ 1ca8:1ae3

void ovl_1ae3(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_0374();
  ovl_1aaf();
  *(undefined1 *)(G_curreg + &G_ptrleng) = 0;
  ovl_15b0();
  return;
}


// ===== ovl_1b02 @ 1ca8:1b02

void ovl_1b02(void)

{
  uint uVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  byte bVar2;
  byte bVar3;
  byte in_AF;
  byte bVar4;
  byte bVar5;
  byte in_TF;
  byte in_IF;
  byte bVar6;
  byte in_NT;
  
  ovl_0374();
  if (G_sailsw == '\0') {
    if (G_swcamp == '\0') {
      OV_0x1b1 = 0x14;
      EXE_LoadOvly(0x59,&OV_0x2100,0x1000);
      uVar1 = *(uint *)(in_BX + 0x148);
      bVar2 = 0;
      bVar6 = 0;
      bVar5 = (int)uVar1 < 0;
      bVar4 = uVar1 == 0;
      bVar3 = (POPCOUNT(uVar1 & 0xff) & 1U) == 0;
      G_crossovlycall = uVar1;
      G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14a);
      EXE_crossovlycall(0x1000);
      EXE_Reload91(in_BX,
                 (uint)(in_NT & 1) * 0x4000 | (uint)(bVar6 & 1) * 0x800 | (uint)(in_IF & 1) * 0x200
                 | (uint)(in_TF & 1) * 0x100 | (uint)(bVar5 & 1) * 0x80 | (uint)(bVar4 & 1) * 0x40 |
                 (uint)(in_AF & 1) * 0x10 | (uint)(bVar3 & 1) * 4 | (uint)(bVar2 & 1));
      return;
    }
    ovl_1576();
  }
  else {
    ovl_1576();
  }
  EXE_InitMap(in_BX);
  ovl_130b();
  ovl_0a94();
  ovl_076c();
  return;
}


// ===== ovl_1b80 @ 1ca8:1b80

void ovl_1b80(void)

{
  return;
}


