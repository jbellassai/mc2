// ===== ovl_0003 @ 1ca8:0003

void ovl_0003(void)

{
  ovl_0147();
  return;
}


// ===== ovl_0147 @ 1ca8:0147

void ovl_0147(void)

{
  undefined1 uVar1;
  undefined2 uVar2;
  uint uVar3;
  byte bVar4;
  int iVar5;
  int in_BX;
  int iVar6;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar7;
  
  OV_0x107 = 0x14;
  bVar4 = EXE_GetMagSkl();
  iVar6 = 4;
  while (bVar4 < *(byte *)(iVar6 + &OV_0x109)) {
    iVar6 = iVar6 + -1;
  }
  OV_0x10e = iVar6;
  uVar1 = *(undefined1 *)(iVar6 + &OV_0x115);
  G_workx = CONCAT11(uVar1,*(undefined1 *)(iVar6 + &OV_0x110));
  G_zp_13 = uVar1;
  G_worky =
       CONCAT11(*(undefined1 *)(iVar6 + &OV_0x11f),*(undefined1 *)(iVar6 + &OV_0x11a))
  ;
  iVar6 = G_savebx;
  do {
    G_zp_12 = (char)G_workx;
    do {
      iVar5 = G_zp_12 + G_winxy;
      G_zp_10 = iVar5;
      G_zp_1415 = iVar5;
      ovl_03d3();
      ovl_0392();
      uVar2 = G_worky;
      G_zp_12 = G_zp_12 + '\x01';
    } while (G_zp_12 < (byte)uVar2);
    G_zp_13 = G_zp_13 + '\x01';
  } while (G_zp_13 < (byte)((uint)uVar2 >> 8));
  EXE_PageFlip();
  iVar6 = EXE_Mark(&G_scrap,0xd,iVar6);
  if ((iVar6 != -1) &&
     ((G_scrap+2 = G_scrap+2 - G_winxy,
      G_scrap+2 != '\x05' || (G_scrap+3 != '\x04')))) {
    iVar6 = OV_0x10e;
    uVar3 = G_scrap+2;
    if ((*(byte *)(iVar6 + &OV_0x110) <= (byte)uVar3) &&
       ((((byte)uVar3 < *(byte *)(iVar6 + &OV_0x11a) &&
         (bVar4 = (byte)(uVar3 >> 8), *(byte *)(iVar6 + &OV_0x115) <= bVar4)) &&
        (bVar4 < *(byte *)(iVar6 + &OV_0x11f))))) {
      iVar6 = G_savebx;
      bVar7 = CARRY2(uVar3,G_winxy);
      iVar5 = uVar3 + G_winxy;
      G_zp_10 = iVar5;
      G_zp_1415 = iVar5;
      ovl_03d3();
      if (!bVar7) {
        EXE_GameSound(0x14);
        G_winxy = G_zp_10 + -0x405;
        ovl_0434();
        G_crossovlycall = *(int *)(iVar6 + 0x14c) + 0x39;
        G_crossovlycall+2 = *(undefined2 *)(iVar6 + 0x14e);
        EXE_crossovlycall();
        (*(code *)*(undefined2 *)(iVar6 + 300))(0x1000);
        G_crossovlycall = *(int *)(iVar6 + 0x14c) + 0x3c;
        G_crossovlycall+2 = *(undefined2 *)(iVar6 + 0x14e);
        EXE_crossovlycall();
        EXE_InitMap();
        G_crossovlycall = *(int *)(iVar6 + 0x14c) + 3;
        G_crossovlycall+2 = *(undefined2 *)(iVar6 + 0x14e);
        EXE_crossovlycall();
        G_crossovlycall = *(int *)(iVar6 + 0x14c) + 0x3f;
        G_crossovlycall+2 = *(undefined2 *)(iVar6 + 0x14e);
        EXE_crossovlycall();
        G_crossovlycall = *(int *)(iVar6 + 0x14c) + 0x30;
        G_crossovlycall+2 = *(undefined2 *)(iVar6 + 0x14e);
        EXE_crossovlycall();
        G_crossovlycall = *(int *)(iVar6 + 0x14c) + 0x36;
        G_crossovlycall+2 = *(undefined2 *)(iVar6 + 0x14e);
        EXE_crossovlycall();
        G_lastdir = 0xffff;
        return;
      }
    }
  }
  iVar6 = G_savebx;
  EXE_GameSound(0xe);
  EXE_InitMap();
  G_crossovlycall = *(int *)(iVar6 + 0x14c) + 3;
  G_crossovlycall+2 = *(undefined2 *)(iVar6 + 0x14e);
  EXE_crossovlycall(0x1000);
  G_crossovlycall = *(int *)(iVar6 + 0x14c) + 0x30;
  G_crossovlycall+2 = *(undefined2 *)(iVar6 + 0x14e);
  EXE_crossovlycall(0x1000);
  G_crossovlycall = *(int *)(iVar6 + 0x14c) + 0x36;
  G_crossovlycall+2 = *(undefined2 *)(iVar6 + 0x14e);
  EXE_crossovlycall(0x1000);
  return;
}


// ===== ovl_0392 @ 1ca8:0392

void ovl_0392(void)

{
  int in_AX;
  uint uVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (in_AX != 1) {
    uVar1 = G_zp_10 - G_winxy;
    EXE_OrTile(OV_0x107,uVar1 & 0xff,uVar1 >> 8);
    G_crossovlycall = *(int *)(in_BX + 0x14c) + 0x42;
    G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14e);
    EXE_crossovlycall(0x1000);
  }
  return;
}


// ===== ovl_03d3 @ 1ca8:03d3

void ovl_03d3(void)

{
  undefined2 *puVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  
  ovl_045b();
  if (((((bool)in_CF) && (ovl_045b(), (bool)in_CF)) && (ovl_045b(), (bool)in_CF)) &&
     (ovl_045b(), (bool)in_CF)) {
    uVar4 = 0;
    do {
      bVar2 = (byte)G_zp_10;
      if (((*(byte *)(uVar4 + &OV_0x20c) <= bVar2) &&
          (bVar2 <= *(byte *)(uVar4 + &OV_0x212))) &&
         ((bVar2 = (byte)((uint)G_zp_10 >> 8),
          *(byte *)(uVar4 + &OV_0x20f) <= bVar2 &&
          (bVar2 <= *(byte *)(uVar4 + &OV_0x215))))) {
        return;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < OV_0x20a);
    puVar1 = (undefined2 *)(G_savebx + 0xc4);
    iVar3 = EXE_ChkWlk();
    if (iVar3 != 0) {
      return;
    }
  }
  return;
}


// ===== ovl_0434 @ 1ca8:0434

void ovl_0434(void)

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


// ===== ovl_045b @ 1ca8:045b

void ovl_045b(void)

{
  int in_CX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_crossovlycall = in_CX + *(int *)(in_BX + 0x14c);
  G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14e);
  EXE_crossovlycall();
  return;
}


