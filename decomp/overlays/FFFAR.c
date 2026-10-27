// ===== ovl_01d3 @ 2000:01d3

undefined2 ovl_01d3(void)

{
  undefined2 in_AX;
  uint uVar1;
  int unaff_BP;
  undefined2 unaff_SS;
  bool in_CF;
  
  if (in_CF) {
    uVar1 = *(uint *)(unaff_BP + 6) | 1;
  }
  else {
    uVar1 = *(uint *)(unaff_BP + 6) & 0xfffe;
  }
  *(uint *)(unaff_BP + 6) = uVar1;
  return in_AX;
}


// ===== ovl_026f @ 2000:026f

void __cdecl16near ovl_026f(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x54);
  EXE_SetTxtWnd(0);
  puVar1 = (undefined2 *)(G_savebx + 0x470);
  EXE_ClrTxtWndX(in_BX);
  G_cursorx = G_cursorx + 5;
  puVar1 = (undefined2 *)(G_savebx + 0x458);
  EXE_MyCoutX(CONCAT11((char)((uint)G_curpla >> 8),
                                     (char)G_curpla + '1'),in_BX);
  G_cursorx = G_cursorx + 2;
  ovl_03bd();
  puVar1 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  G_cursorx = G_cursorx + 5;
  uVar2 = 0x4d;
  if (*(char *)(unaff_DI + 7) != '\0') {
    uVar2 = 0x46;
  }
  puVar1 = (undefined2 *)(G_savebx + 0x458);
  EXE_MyCoutX(uVar2,in_BX);
  G_cursorx = G_cursorx + 2;
  puVar1 = (undefined2 *)(G_savebx + 600);
  EXE_MyCoutX(*(undefined1 *)(unaff_DI + 6),in_BX);
  ovl_03bd();
  G_cursorx = G_cursorx + 1;
  ovl_03ce();
  puVar1 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  if (OV_0xb9 != -1) {
    puVar1 = (undefined2 *)(G_savebx + 0x15c);
    EXE_SetTxtSpell(OV_0xd7,in_BX);
    G_cursorx = G_cursorx + 4;
    puVar1 = (undefined2 *)(G_savebx + 0x458);
    EXE_MyCoutX(0x28,in_BX);
    if (9 < OV_0xb9) {
      ovl_0396();
    }
    ovl_03ce();
    puVar1 = (undefined2 *)(G_savebx + 0x458);
    EXE_MyCoutX(0x29,in_BX);
  }
  puVar1 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0x98);
  iVar3 = EXE_FindPla();
  puVar1 = (undefined2 *)(G_savebx + 0x74);
  EXE_movectile(*(undefined1 *)(iVar3 + &G_pltilno),4,8,
                     (int)G_oppscr,
                     (int)((ulong)G_oppscr >> 0x10),in_BX);
  return;
}


// ===== ovl_0396 @ 2000:0396

undefined2 __cdecl16near ovl_0396(void)

{
  undefined2 *puVar1;
  byte in_AL;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (in_AL < 0x1e) {
    return 2;
  }
  if (in_AL < 0x28) {
    return 5;
  }
  if (in_AL < 0x5a) {
    puVar1 = (undefined2 *)(G_savebx + 0x13c);
    EXE_SetTxtObj(in_AL + 0x2b);
    return 7;
  }
  return 4;
}


// ===== ovl_03bd @ 2000:03bd

void __cdecl16near ovl_03bd(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x464);
  EXE_PrtWrdX();
  return;
}


// ===== ovl_03ce @ 2000:03ce

void __cdecl16near ovl_03ce(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x464);
  EXE_PrtWrdX();
  return;
}


// ===== ovl_03df @ 2000:03df

void __cdecl16near ovl_03df(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x474);
  EXE_Prt2DgtX();
  return;
}


// ===== FAR_STATS0 @ 2000:0451

void FAR_STATS0(void)

{
  int *piVar1;
  byte *pbVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined2 *puVar6;
  int iVar7;
  int iVar8;
  undefined2 in_BX;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined2 uVar9;
  undefined2 uVar10;
  
  uVar10 = G_scroll;
  G_scroll = 0;
  iVar5 = *(int *)(unaff_BP + 0xc);
  ovl_026f();
  ovl_03ce();
  ovl_03df();
  puVar6 = (undefined2 *)(G_savebx + 0x458);
  EXE_MyCoutX(0x2f,in_BX);
  ovl_03df();
  puVar6 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  ovl_03ce();
  ovl_03df();
  ovl_03ce();
  ovl_03df();
  puVar6 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  ovl_03ce();
  if (*(byte *)(iVar5 + 0xbf) != 0xff) {
    puVar6 = (undefined2 *)(G_savebx + 0x13c);
    EXE_SetTxtObj(*(undefined1 *)((uint)*(byte *)(iVar5 + 0xbf) + iVar5 + 0x2b),in_BX);
    ovl_03bd();
  }
  puVar6 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  ovl_03ce();
  if (*(char *)(iVar5 + 0xcb) != -1) {
    puVar6 = (undefined2 *)(G_savebx + 0x15c);
    EXE_SetTxtSpell(*(char *)(iVar5 + 0xcb),in_BX);
    ovl_03bd();
  }
  puVar6 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  uVar9 = G_cursory;
  puVar6 = (undefined2 *)(G_savebx + 0xe4);
  EXE_InitScrap(in_BX);
  ovl_06bd();
  iVar7 = CONCAT11((char)*(undefined2 *)(iVar5 + 0xbd),
                   (char)((uint)*(undefined2 *)(iVar5 + 0xbd) >> 8));
  *(int *)(unaff_BP + -6) = iVar7;
  if (iVar7 == 0) {
    puVar6 = (undefined2 *)(G_savebx + 0x2e0);
    EXE_SetTxtCond(0,in_BX);
    ovl_06ac();
    ovl_06bd();
  }
  else {
    iVar7 = 0x10;
    do {
      piVar1 = (int *)(unaff_BP + -6);
      iVar8 = *piVar1;
      *piVar1 = *piVar1 << 1;
      if (iVar8 < 0) {
        puVar6 = (undefined2 *)(G_savebx + 0x2e0);
        EXE_SetTxtCond(0x11 - iVar7,in_BX);
        ovl_06ac();
        ovl_06bd();
      }
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  G_scrapptr = G_scrapptr + -2;
  puVar6 = (undefined2 *)(G_savebx + 0x270);
  EXE_ScrapCOut(0x2e,in_BX);
  puVar6 = (undefined2 *)(G_savebx + 0x46c);
  EXE_PrtScrapX(0xff,in_BX);
  puVar6 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  G_cursory = uVar9;
  G_cursory = G_cursory + 0x20;
  ovl_03ce();
  puVar6 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  ovl_03ce();
  puVar6 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  uVar9 = G_cursory;
  cVar3 = *(char *)(iVar5 + 0xa5);
  *(char *)(unaff_BP + -6) = cVar3;
  if (cVar3 != '\0') {
    iVar7 = 8;
    do {
      pbVar2 = (byte *)(unaff_BP + -6);
      bVar4 = *pbVar2;
      *pbVar2 = *pbVar2 >> 1;
      if ((bool)(bVar4 & 1)) {
        puVar6 = (undefined2 *)(G_savebx + 0x2e4);
        EXE_SetTxtInUse(iVar7 + 2,in_BX);
        ovl_03bd();
        puVar6 = (undefined2 *)(G_savebx + 0x40);
        EXE_MyRet();
      }
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  G_cursory = uVar9;
  G_cursorx = G_cursorx + 0x10;
  G_txtwx = G_txtwx + 0x10;
  G_txtww = G_txtww + -0x10;
  iVar8 = 0;
  iVar7 = 6;
  do {
    bVar4 = *(byte *)(iVar8 + iVar5 + 0xc0);
    if (bVar4 != 0xff) {
      puVar6 = (undefined2 *)(G_savebx + 0x13c);
      EXE_SetTxtObj(*(undefined1 *)((uint)bVar4 + iVar5 + 0x2b),in_BX);
      ovl_03bd();
      puVar6 = (undefined2 *)(G_savebx + 0x40);
      EXE_MyRet();
    }
    iVar8 = iVar8 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  G_txtwx = G_txtwx + -0x10;
  G_txtww = G_txtww + 0x10;
  G_scroll = uVar10;
  puVar6 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip(in_BX);
  ovl_01d3();
  return;
}


// ===== ovl_06ac @ 2000:06ac

void __cdecl16near ovl_06ac(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap();
  return;
}


// ===== ovl_06bd @ 2000:06bd

void __cdecl16near ovl_06bd(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap();
  return;
}


// ===== FAR_STATS1 @ 2000:06ce

void FAR_STATS1(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar1 = G_scroll;
  G_scroll = 0;
  ovl_026f();
  iVar4 = 9;
  iVar3 = 0;
  do {
    puVar2 = (undefined2 *)(G_savebx + 0x294);
    EXE_SetTxtAttrib(iVar3,in_BX);
    ovl_03bd();
    puVar2 = (undefined2 *)(G_savebx + 0x458);
    EXE_MyCoutX(0x3a);
    G_cursorx = G_cursorx + 1;
    ovl_03df();
    puVar2 = (undefined2 *)(G_savebx + 0x40);
    EXE_MyRet();
    iVar3 = iVar3 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  G_scroll = uVar1;
  ovl_01d3();
  return;
}


// ===== FAR_STATS2 @ 2000:0734

void FAR_STATS2(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  undefined2 in_BX;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar1 = G_scroll;
  G_scroll = 0;
  uVar2 = *(undefined2 *)(unaff_BP + 0xc);
  ovl_026f();
  G_cursorx = G_cursorx + 8;
  ovl_03ce();
  puVar3 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  if (*(int *)(unaff_BP + 0xe) == 0) {
    s_Skills_2000_072d[2] = '\0';
    s_Skills_2000_072d[3] = '\0';
  }
  s_Leader_2000_01f1[2] = '\r';
  s_Leader_2000_01f1[3] = '\0';
  do {
    puVar3 = (undefined2 *)(G_savebx + 0x40);
    EXE_MyRet(in_BX);
    puVar3 = (undefined2 *)(G_savebx + 0x2e8);
    EXE_SetTxtSkill(s_Skills_2000_072d._2_2_);
    ovl_03bd();
    puVar3 = (undefined2 *)(G_savebx + 0x458);
    EXE_MyCoutX(0x3a);
    G_cursorx = G_cursorx + 2;
    ovl_03df();
    puVar3 = (undefined2 *)(G_savebx + 0x458);
    EXE_MyCoutX(0x2f);
    puVar3 = (undefined2 *)(G_savebx + 0x2ec);
    EXE_MaxSkill(uVar2,s_Skills_2000_072d._2_2_);
    ovl_03df();
    s_Skills_2000_072d._2_2_ = s_Skills_2000_072d._2_2_ + 1;
    s_Leader_2000_01f1._2_2_ = s_Leader_2000_01f1._2_2_ + -1;
    if (s_Leader_2000_01f1._2_2_ == 0) break;
  } while ((uint)s_Skills_2000_072d._2_2_ < 0x13);
  G_scroll = uVar1;
  ovl_01d3();
  return;
}


// ===== FAR_STATS4 @ 2000:082a

void FAR_STATS4(void)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  undefined2 *puVar4;
  byte bVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar2 = G_scroll;
  G_scroll = 0;
  iVar3 = *(int *)(unaff_BP + 0xc);
  ovl_026f();
  G_cursorx = G_cursorx + 8;
  ovl_03ce();
  puVar4 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet();
  if (*(char *)(unaff_BP + 0xe) == '\0') {
    iVar8 = 0;
    s_Inventory_2000_0809[0] = '\0';
    s_Inventory_2000_0809[1] = '\0';
    s_Inventory_2000_0809[2] = '\0';
    s_Inventory_2000_0809[3] = '\0';
    iVar7 = 0x28;
    do {
      if (*(char *)(iVar8 + iVar3 + 0x2b) != -1) {
        s_Inventory_2000_0809._2_2_ = s_Inventory_2000_0809._2_2_ + 1;
      }
      iVar8 = iVar8 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  s_Leader_2000_01f1[2] = '\r';
  s_Leader_2000_01f1[3] = '\0';
  do {
    if (s_Inventory_2000_0809._2_2_ == 0) break;
    LOCK();
    UNLOCK();
    cVar1 = *(char *)(s_Inventory_2000_0809._0_2_ + iVar3 + 0x2b);
    LOCK();
    UNLOCK();
    if (cVar1 != -1) {
      *(undefined2 *)(unaff_BP + -6) =
           CONCAT11(*(undefined1 *)(s_Inventory_2000_0809._0_2_ + iVar3 + 0x53),cVar1);
      puVar4 = (undefined2 *)(G_savebx + 0x40);
      EXE_MyRet();
      puVar4 = (undefined2 *)(G_savebx + 0x13c);
      EXE_SetTxtObj(*(undefined1 *)(unaff_BP + -6));
      ovl_03bd();
      G_cursorx = G_cursorx + 2;
      bVar5 = (byte)*(uint *)(unaff_BP + -6);
      if ((bVar5 < 9) || (0x30 < bVar5)) {
        uVar6 = *(uint *)(unaff_BP + -6) >> 8;
        if (bVar5 == 0) {
          uVar6 = *(uint *)(iVar3 + 0xcc);
        }
        else if ((0x4b < bVar5) && (bVar5 < 0x50)) {
          ovl_03ce();
          goto L_0929;
        }
        G_deftxtparms = uVar6;
        ovl_03bd();
      }
      else if (bVar5 < 0x2b) {
        G_deftxtparms+2 = *(byte *)(unaff_BP + -5) & 0x7f;
        ovl_03ce();
      }
L_0929:
      s_Leader_2000_01f1._2_2_ = s_Leader_2000_01f1._2_2_ + -1;
      s_Inventory_2000_0809._2_2_ = s_Inventory_2000_0809._2_2_ + -1;
    }
    s_Inventory_2000_0809._0_2_ = s_Inventory_2000_0809._0_2_ + 1;
  } while (s_Leader_2000_01f1._2_2_ != 0);
  G_scroll = uVar2;
  ovl_01d3();
  return;
}


// ===== FAR_STATS5 @ 2000:099b

void FAR_STATS5(void)

{
  undefined2 uVar1;
  char *pcVar2;
  undefined2 uVar3;
  int iVar4;
  undefined2 *puVar5;
  char cVar6;
  uint uVar7;
  int iVar8;
  undefined2 in_BX;
  int unaff_BP;
  int unaff_SI;
  char *pcVar9;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar10;
  
  uVar3 = G_scroll;
  G_scroll = 0;
  iVar4 = *(int *)(unaff_BP + 0xc);
  ovl_026f();
  ovl_03ce();
  puVar5 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet();
  if (*(char *)(iVar4 + 0x1a) != '\0') {
    if (*(char *)(unaff_BP + 0xe) == '\0') {
      uVar7 = 0;
      DAT_2000_095d = 0;
      DAT_2000_095f = 0;
      do {
        puVar5 = (undefined2 *)(G_savebx + 0x158);
        cVar6 = EXE_SearchInv(CONCAT11((char)(uVar7 >> 8),(char)uVar7 + 'S'),
                                   G_curpla,&G_invinfobuf);
        *(char *)(uVar7 + 0x961) = cVar6;
        *(char *)(uVar7 + 0x968) = cVar6;
        if (cVar6 == '\0') {
          bVar10 = uVar7 * 6 == 0;
          pcVar9 = (char *)(uVar7 * 6 + iVar4 + 0x7b);
          iVar8 = 6;
          do {
            if (iVar8 == 0) break;
            iVar8 = iVar8 + -1;
            pcVar2 = pcVar9;
            pcVar9 = pcVar9 + 1;
            bVar10 = *pcVar2 == '\0';
          } while (bVar10);
          if (!bVar10) {
            *(char *)(uVar7 + 0x968) = *(char *)(uVar7 + 0x968) + '\x01';
            goto L_0a3a;
          }
        }
        else {
L_0a3a:
          DAT_2000_095f = DAT_2000_095f + 1;
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < 7);
    }
    s_Leader_2000_01f1[2] = '\x02';
    s_Leader_2000_01f1[3] = '\0';
    do {
      if (DAT_2000_095f == 0) break;
      LOCK();
      UNLOCK();
      LOCK();
      UNLOCK();
      if (*(char *)(DAT_2000_095d + 0x968) != '\0') {
        if (*(char *)(DAT_2000_095d + 0x961) != '\0') {
          G_cursorx = 10;
          puVar5 = (undefined2 *)(G_savebx + 0x13c);
          EXE_SetTxtObj(CONCAT11((char)((uint)DAT_2000_095d >> 8),
                                             (char)DAT_2000_095d + 'S'));
          ovl_03ce();
        }
        puVar5 = (undefined2 *)(G_savebx + 0x40);
        EXE_MyRet();
        *(int *)(unaff_BP + -6) = DAT_2000_095d * 6;
        iVar8 = 6;
        do {
          puVar5 = (undefined2 *)(G_savebx + 0x15c);
          EXE_SetTxtSpell(*(undefined2 *)(unaff_BP + -6));
          ovl_03bd();
          G_cursorx = 0x1a;
          LOCK();
          uVar1 = *(undefined2 *)(unaff_BP + -6);
          *(undefined2 *)(unaff_BP + -6) = in_BX;
          UNLOCK();
          LOCK();
          in_BX = *(undefined2 *)(unaff_BP + -6);
          *(undefined2 *)(unaff_BP + -6) = uVar1;
          UNLOCK();
          ovl_03df();
          G_cursorx = G_cursorx + '\x04';
          puVar5 = (undefined2 *)(G_savebx + 0x160);
          EXE_LrnTim(*(undefined2 *)(unaff_BP + -6),G_curpla)
          ;
          ovl_03df();
          G_cursorx = G_cursorx + '\x04';
          puVar5 = (undefined2 *)(G_savebx + 0x228);
          EXE_EneUsg(*(undefined2 *)(unaff_BP + -6),G_curpla)
          ;
          ovl_03df();
          if ((*(char *)(iVar4 + 0xb9) == '\x01') &&
             (*(char *)(unaff_BP + -6) == *(char *)(iVar4 + 0xd7))) {
            puVar5 = (undefined2 *)(G_savebx + 0x458);
            EXE_MyCoutX(0x1c);
          }
          puVar5 = (undefined2 *)(G_savebx + 0x40);
          EXE_MyRet();
          *(char *)(unaff_BP + -6) = *(char *)(unaff_BP + -6) + '\x01';
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        s_Leader_2000_01f1._2_2_ = s_Leader_2000_01f1._2_2_ + -1;
        DAT_2000_095f = DAT_2000_095f + -1;
      }
      DAT_2000_095d = DAT_2000_095d + 1;
    } while (s_Leader_2000_01f1._2_2_ != 0);
  }
  G_scroll = uVar3;
  ovl_01d3();
  return;
}


// ===== FAR_STATS6 @ 2000:0bad

void FAR_STATS6(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  undefined2 in_BX;
  int unaff_BP;
  int unaff_SI;
  int iVar7;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar8;
  
  uVar1 = G_scroll;
  G_scroll = 0;
  iVar7 = *(int *)(unaff_BP + 0xc);
  ovl_026f();
  ovl_03ce();
  puVar2 = (undefined2 *)(G_savebx + 0x40);
  EXE_MyRet(in_BX);
  ovl_03ce();
  if (*(char *)(iVar7 + 0x23) != '\0') {
    puVar2 = (undefined2 *)(G_savebx + 0x40);
    EXE_MyRet(in_BX);
    ovl_03ce();
  }
  iVar4 = 4;
  iVar3 = 0;
  do {
    bVar6 = *(byte *)(iVar7 + 9);
    iVar5 = 8;
    do {
      bVar8 = (bool)(bVar6 & 1);
      bVar6 = bVar6 >> 1;
      if (bVar8) {
        puVar2 = (undefined2 *)(G_savebx + 0x2b8);
        EXE_SetTxtSong(iVar3,in_BX);
        puVar2 = (undefined2 *)(G_savebx + 0x40);
        EXE_MyRet();
        G_cursorx = G_cursorx + 2;
        ovl_03bd();
      }
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    iVar7 = iVar7 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  G_scroll = uVar1;
  ovl_01d3();
  return;
}


// ===== FAR_ADDSCRAP @ 2000:0c39

void FAR_ADDSCRAP(void)

{
  char *pcVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  int unaff_BP;
  int unaff_SI;
  char *pcVar5;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  pcVar5 = (char *)(char *)*(undefined4 *)(unaff_BP + 0xc);
  iVar4 = *(int *)(unaff_BP + 0x10);
  do {
    if (iVar4 == 0) {
      puVar2 = (undefined2 *)(G_savebx + 0x2f0);
      EXE_PrtAWrd(pcVar5,*(undefined2 *)(unaff_BP + 0xe),0,1);
      ovl_01d3();
      return;
    }
    iVar3 = 0x200;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar1 = pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (*pcVar1 != '\0');
    iVar4 = iVar4 + -1;
  } while( true );
}


// ===== FAR_PRTSCRAP @ 2000:0c70

void FAR_PRTSCRAP(void)

{
  char *pcVar1;
  undefined2 *puVar2;
  int iVar3;
  int unaff_BP;
  int unaff_SI;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  G_scraplines = 1;
  G_scraplptrs = 0;
  pcVar4 = (char *)(&G_scrap + G_scrapptr);
  *pcVar4 = ' ';
  pcVar5 = pcVar4 + -G_scrapptr;
  *(undefined2 *)(unaff_BP + -6) = pcVar5;
  do {
    iVar3 = 0xff;
    pcVar6 = pcVar5;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar1 = pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (*pcVar1 != '\r');
    iVar3 = 0xff;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar1 = pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (*pcVar1 != ' ');
    if (pcVar6 <= pcVar5) {
      pcVar5 = pcVar6;
    }
    if (G_txtww < (uint)((int)(pcVar5 + (-1 - *(int *)(unaff_BP + -6))) * 2)) {
L_0cd1:
      pcVar6 = FAR_PRTSCRAP;
      *(undefined2 *)(unaff_BP + -6) = FAR_PRTSCRAP;
      pcVar6[-1] = '\r';
      LOCK();
      iVar3 = G_scraplines;
      G_scraplines = (int)pcVar4;
      UNLOCK();
      *(char *)(iVar3 + &G_scraplptrs) = (char)pcVar6 - ((char)unaff_SI + 'B');
      LOCK();
      pcVar4 = (char *)G_scraplines;
      G_scraplines = iVar3 + 1;
      UNLOCK();
      if (pcVar4 < pcVar5) goto L_0cf5;
    }
    else {
      if (pcVar4 < pcVar5) {
L_0cf5:
        *pcVar4 = '\0';
        puVar2 = (undefined2 *)(G_savebx + 0x178);
        EXE_PrtWrd(&G_scrap);
        puVar2 = (undefined2 *)(G_savebx + 0x2f4);
        EXE_WriteNote(&G_scrap);
        ovl_01d3();
        return;
      }
      if (pcVar5 == pcVar6) {
        FAR_PRTSCRAP = pcVar6;
        goto L_0cd1;
      }
    }
    FAR_PRTSCRAP = pcVar5;
  } while( true );
}


// ===== FAR_INT62_1a @ 2000:0d2f

void FAR_INT62_1a(void)

{
  char *pcVar1;
  undefined2 *puVar2;
  int iVar3;
  int unaff_BP;
  int unaff_SI;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  G_scraplines = 1;
  G_scraplptrs = 0;
  pcVar4 = (char *)(&G_scrap + G_scrapptr);
  *pcVar4 = ' ';
  pcVar5 = pcVar4 + -G_scrapptr;
  *(undefined2 *)(unaff_BP + -6) = pcVar5;
  do {
    iVar3 = 0xff;
    pcVar6 = pcVar5;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar1 = pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (*pcVar1 != '\r');
    iVar3 = 0xff;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar1 = pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (*pcVar1 != ' ');
    if (pcVar6 <= pcVar5) {
      pcVar5 = pcVar6;
    }
    if (G_txtww < (uint)((int)(pcVar5 + (-1 - *(int *)(unaff_BP + -6))) * 2)) {
L_0d90:
      pcVar6 = FAR_PRTSCRAP;
      *(undefined2 *)(unaff_BP + -6) = FAR_PRTSCRAP;
      pcVar6[-1] = '\r';
      LOCK();
      iVar3 = G_scraplines;
      G_scraplines = (int)pcVar4;
      UNLOCK();
      *(char *)(iVar3 + &G_scraplptrs) = (char)pcVar6 - ((char)unaff_SI + 'B');
      LOCK();
      pcVar4 = (char *)G_scraplines;
      G_scraplines = iVar3 + 1;
      UNLOCK();
      if (pcVar4 < pcVar5) goto L_0db4;
    }
    else {
      if (pcVar4 < pcVar5) {
L_0db4:
        *pcVar4 = '\0';
        puVar2 = (undefined2 *)(G_savebx + 0x178);
        EXE_PrtWrd(&G_scrap);
        puVar2 = (undefined2 *)(G_savebx + 0x2f4);
        EXE_WriteNote(&G_scrap);
        ovl_01d3();
        return;
      }
      if (pcVar5 == pcVar6) {
        FAR_PRTSCRAP = pcVar6;
        goto L_0d90;
      }
    }
    FAR_PRTSCRAP = pcVar5;
  } while( true );
}


// ===== FAR_PRTAWRD @ 2000:0dee

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0x00020ebc) overlaps instruction at (ram,0x00020ebb)
    */

void FAR_PRTAWRD(void)

{
  byte *pbVar1;
  byte *pbVar2;
  byte bVar3;
  uint uVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  undefined2 extraout_DX;
  undefined2 extraout_DX_00;
  undefined2 extraout_DX_01;
  undefined2 extraout_DX_02;
  undefined2 extraout_DX_03;
  undefined2 extraout_DX_04;
  undefined2 uVar8;
  undefined2 extraout_DX_05;
  byte *in_BX;
  undefined4 *puVar9;
  int unaff_BP;
  byte *unaff_SI;
  byte *pbVar10;
  byte *pbVar11;
  byte *pbVar12;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined4 uVar13;
  
  (*(code *)*(undefined2 *)(G_savebx + 0x70))();
  pbVar12 = (byte *)((ulong)*(undefined4 *)(unaff_BP + 0xc) >> 0x10);
  pbVar10 = (byte *)(byte *)*(undefined4 *)(unaff_BP + 0xc);
  iVar7 = *(int *)(unaff_BP + 0x10);
  *(undefined1 *)(unaff_BP + -9) = 0;
  for (; iVar7 != 0; iVar7 = iVar7 + -1) {
    iVar6 = 0xff;
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pbVar1 = pbVar10;
      pbVar10 = pbVar10 + 1;
    } while (*pbVar1 != 0);
  }
  if (*(int *)(unaff_BP + 0x12) == 0) {
    *(undefined2 *)(unaff_BP + -8) = 0x8c;
  }
  else {
    *(undefined2 *)(unaff_BP + -8) = 0x270;
  }
  bVar3 = *pbVar10;
  if (bVar3 == 0x25) {
    *(undefined1 *)(unaff_BP + -9) = 1;
  }
  else if (0x40 < bVar3) {
    if (0x5a < bVar3) {
      if ((bVar3 < 0x61) || (0x7a < bVar3)) goto L_0e46;
      bVar3 = bVar3 - 0x20;
    }
    unaff_SI[0x6a84] = bVar3;
  }
L_0e46:
  *(int *)(unaff_BP + -6) = (int)pbVar10;
  uVar8 = 0;
L_0e49:
  while( true ) {
    bVar3 = *pbVar10;
    pbVar11 = pbVar10 + 1;
    if (bVar3 == 0) break;
    if (bVar3 == 0xd) {
      pbVar11 = pbVar10;
      pbVar10 = (byte *)*(undefined2 *)(unaff_BP + 0x12);
switchD_2000_0eb3_caseD_6c:
      if (pbVar10 != (byte *)0x0) {
        in_BX = (byte *)0xd;
        goto L_0eb8;
      }
      if (G_cursorx == G_txtwx) goto L_0edc;
      (*(code *)*(undefined2 *)(G_savebx + 0x40))(in_BX);
      uVar8 = extraout_DX_04;
      if ((uint)(G_txtwy + G_txtwh) <=
          G_cursory) {
        ovl_173e();
        break;
      }
    }
    else {
      if (bVar3 != 0x25) goto code_r0x00020e60;
      bVar3 = *pbVar11;
      in_BX = (byte *)(uint)bVar3;
      if ((bVar3 < 0x61) || (0x7a < bVar3)) {
L_0eb8:
        pbVar10 = (byte *)(*(int *)(DAT_2000_01ed + -0x728a) + *(int *)(unaff_BP + -8));
        s_Leader_2000_01f1._0_2_ = SUB42((ulong)*(undefined4 *)pbVar10 >> 0x10,0);
        DAT_2000_01ef = (undefined2)*(undefined4 *)pbVar10;
        EXE_slot0x1ef(in_BX);
        uVar8 = extraout_DX_00;
        in_BX = pbVar10;
        goto L_0edc;
      }
      uVar4 = (uint)(byte)(bVar3 + 0x9f);
      in_BX = (byte *)(uVar4 * 2);
      pbVar10 = in_BX;
      switch(bVar3) {
      case 0x61:
        uVar8 = 0x2000;
        in_BX = *(byte **)&G_curpla;
        goto code_r0x00020fa4;
      case 0x62:
code_r0x00020fa4:
        in_BX = *(byte **)(unaff_SI + (int)in_BX * 2 + 0x2b26);
        if (in_BX[7] == 1) {
          pbVar10 = (byte *)0xf3b;
        }
        else {
          pbVar10 = (byte *)0xf43;
        }
        break;
      default:
        unaff_SI = (byte *)*(undefined2 *)0x1ed;
        goto L_0eb8;
      case 100:
        pbVar10 = *(byte **)&G_deftxtparms+6;
        break;
      case 0x66:
        in_BX = (byte *)(uVar4 * 4);
        unaff_SI = *(byte **)(in_BX + (int)&G_heroptr);
        goto L_0f4e;
      case 0x67:
        (*(code *)*(undefined2 *)(G_savebx + 0x2fc))
                  (in_BX,&G_prtwrk,10,in_BX);
        unaff_SI = &G_prtwrk;
        uVar8 = extraout_DX_02;
        goto L_0f4e;
      case 0x69:
        &G_scroll[0] = 0;
        &G_scroll[1] = 0;
        &G_flickerkey[0] = 0;
        &G_flickerkey[1] = 0;
        pbVar10 = pbVar12;
        (*(code *)*(undefined2 *)(G_savebx + 0x308))(in_BX);
        (*(code *)*(undefined2 *)(G_savebx + 0x224))(8,in_BX);
        (*(code *)*(undefined2 *)(G_savebx + 0x220))(in_BX);
        while( true ) {
          iVar7 = (*(code *)*(undefined2 *)(G_savebx + 0x304))
                            (0,&G_mousests,in_BX);
          if ((iVar7 != 0) ||
             (iVar7 = (*(code *)*(undefined2 *)(G_savebx + 0x304))
                                (1,&G_mousests,in_BX), iVar7 != 0))
          goto L_115c;
          iVar7 = (*(code *)*(undefined2 *)(G_savebx + 0x30c))(in_BX);
          if (iVar7 != 0) break;
          (*(code *)*(undefined2 *)(G_savebx + 0x70))(in_BX);
          puVar9 = (undefined4 *)(*(int *)(DAT_2000_01ed + -0x728a) + *(int *)(unaff_BP + -8));
          s_Leader_2000_01f1._0_2_ = SUB42((ulong)*puVar9 >> 0x10,0);
          DAT_2000_01ef = (undefined2)*puVar9;
          EXE_slot0x1ef(0x19);
          (*(code *)*(undefined2 *)(G_savebx + 0x220))(puVar9);
          ovl_16dd();
          G_cursorx = G_cursorx + -2;
          (*(code *)*(undefined2 *)(G_savebx + 0x70))(puVar9);
          in_BX = (byte *)(*(int *)(DAT_2000_01ed + -0x728a) + *(int *)(unaff_BP + -8));
          s_Leader_2000_01f1._0_2_ = SUB42((ulong)*(undefined4 *)in_BX >> 0x10,0);
          DAT_2000_01ef = (undefined2)*(undefined4 *)in_BX;
          EXE_slot0x1ef(0x1a);
          (*(code *)*(undefined2 *)(G_savebx + 0x220))();
          ovl_16dd();
          G_cursorx = G_cursorx + -2;
        }
        uVar8 = (*(code *)*(undefined2 *)(G_savebx + 0x90))(in_BX);
        G_flickerkey = uVar8;
        (*(code *)*(undefined2 *)(G_savebx + 0x308))(in_BX);
L_115c:
        (*(code *)*(undefined2 *)(G_savebx + 0x70))(in_BX);
        in_BX = (byte *)(*(int *)(DAT_2000_01ed + -0x728a) + *(int *)(unaff_BP + -8));
        s_Leader_2000_01f1._0_2_ = SUB42((ulong)*(undefined4 *)in_BX >> 0x10,0);
        DAT_2000_01ef = (undefined2)*(undefined4 *)in_BX;
        pbVar2 = pbVar12;
        pbVar12 = unaff_SI;
        EXE_slot0x1ef(0x20);
        unaff_SI = pbVar2;
        *(byte **)&G_scroll = pbVar10;
        uVar8 = extraout_DX_03;
        goto L_0edc;
      case 0x6a:
        bVar3 = *unaff_SI;
        uVar5 = (undefined1)((uint)in_BX >> 8);
        uVar4 = CONCAT11(uVar5,bVar3);
        if (bVar3 < 0x41) goto L_0f51;
        if (0x5a < bVar3) goto L_0f51;
        uVar4 = CONCAT11(uVar5,bVar3 + 0x20);
        goto L_0f51;
      case 0x6c:
        goto switchD_2000_0eb3_caseD_6c;
      case 0x6d:
        pbVar10 = *(byte **)&G_othername;
        break;
      case 0x6e:
        in_BX = *(byte **)(unaff_SI + uVar4 * 4 + 0x2b26);
        if (in_BX[7] == 1) {
          pbVar10 = (byte *)0xf3b;
        }
        else {
          pbVar10 = (byte *)0xf3f;
        }
        break;
      case 0x6f:
        in_BX = (byte *)0x1626;
      case 0x70:
        while( true ) {
          bVar3 = pbVar11[1];
          if ((bVar3 < 0x30) || (0x39 < bVar3)) break;
          *in_BX = bVar3;
          in_BX = in_BX + 1;
          pbVar11 = pbVar11 + 1;
        }
        in_BX[0] = 0x2e;
        in_BX[1] = 0x5d;
        in_BX[2] = 0;
        pbVar10 = (byte *)0x1616;
        uVar8 = 0x2000;
        break;
      case 0x73:
        (*(code *)*(undefined2 *)(G_savebx + 0x300))
                  (G_deftxtparms,0,uVar8,10,in_BX);
        unaff_SI = &G_prtwrk;
        uVar8 = extraout_DX_05;
L_0f4e:
        while( true ) {
          uVar4 = (uint)*unaff_SI;
L_0f51:
          uVar13 = CONCAT22(uVar8,uVar4);
          unaff_SI = unaff_SI + 1;
          if (*(char *)(unaff_BP + -9) == '\x01') {
            uVar13 = ovl_16b9();
          }
          uVar8 = (undefined2)((ulong)uVar13 >> 0x10);
          if ((int)uVar13 == 0) break;
          in_BX = (byte *)(*(int *)(DAT_2000_01ed + -0x728a) + *(int *)(unaff_BP + -8));
          s_Leader_2000_01f1._0_2_ = SUB42((ulong)*(undefined4 *)in_BX >> 0x10,0);
          DAT_2000_01ef = (undefined2)*(undefined4 *)in_BX;
          EXE_slot0x1ef((int)uVar13);
          uVar8 = extraout_DX_01;
        }
        unaff_SI = DAT_2000_01ed;
        goto L_0edc;
      case 0x75:
        in_BX = *(byte **)(unaff_SI + uVar4 * 4 + 0x2b26);
        if (in_BX[7] == 1) {
          pbVar10 = (byte *)0xf47;
        }
        else {
          pbVar10 = (byte *)0xf4b;
        }
        break;
      case 0x77:
        in_BX = *(byte **)(unaff_SI + uVar4 * 4 + 0x2b26);
        if (in_BX[7] == 1) {
          pbVar10 = (byte *)0xf31;
        }
        else {
          pbVar10 = (byte *)0xf37;
        }
        break;
      case 0x79:
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      case 0x7a:
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      while( true ) {
        pbVar1 = pbVar10;
        pbVar10 = pbVar10 + 1;
        uVar13 = CONCAT22(uVar8,(uint)*pbVar1);
        if (*(char *)(unaff_BP + -9) == '\x01') {
          uVar13 = ovl_16b9();
        }
        uVar8 = (undefined2)((ulong)uVar13 >> 0x10);
        if ((int)uVar13 == 0) break;
        in_BX = (byte *)(*(int *)(DAT_2000_01ed + -0x728a) + *(int *)(unaff_BP + -8));
        s_Leader_2000_01f1._0_2_ = SUB42((ulong)*(undefined4 *)in_BX >> 0x10,0);
        DAT_2000_01ef = (undefined2)*(undefined4 *)in_BX;
        EXE_slot0x1ef((int)uVar13);
      }
      unaff_SI = DAT_2000_01ed;
    }
L_0edc:
    pbVar10 = pbVar11 + 1;
  }
  goto L_0ee0;
code_r0x00020e60:
  in_BX = (byte *)(*(int *)(DAT_2000_01ed + -0x728a) + *(int *)(unaff_BP + -8));
  s_Leader_2000_01f1._0_2_ = SUB42((ulong)*(undefined4 *)in_BX >> 0x10,0);
  DAT_2000_01ef = (undefined2)*(undefined4 *)in_BX;
  EXE_slot0x1ef(bVar3);
  uVar8 = extraout_DX;
  pbVar10 = pbVar11;
  if ((*(int *)(unaff_BP + 0x12) == 0) &&
     ((uint)(G_txtwy + G_txtwh) <=
      G_cursory)) {
    ovl_173e();
L_0ee0:
    (*(code *)*(undefined2 *)(G_savebx + 0x220))(in_BX);
    unaff_SI[-0x7b69] = 1;
    ovl_01d3();
    return;
  }
  goto L_0e49;
}


// ===== FAR_PRTAWRDX @ 2000:129c
// FAILED Low-level Error: Bad instruction count exceeded:
    ...
    Instruction at (ram,0x00021682) overlaps instruction at (ram,0x00021681)

// ===== ovl_16b9 @ 2000:16b9

uint __cdecl16near ovl_16b9(void)

{
  byte bVar1;
  uint in_AX;
  uint uVar2;
  int unaff_BP;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  bVar1 = (byte)in_AX;
  if (0x40 < bVar1) {
    uVar2 = in_AX;
    if (0x5a < bVar1) {
      if ((bVar1 < 0x61) || (0x7a < bVar1)) goto L_16d7;
      uVar2 = (uint)(byte)(bVar1 - 0x20);
    }
    *(undefined1 *)(DAT_2000_01ed + 0x6a84) = (char)uVar2;
  }
L_16d7:
  *(undefined1 *)(unaff_BP + -9) = 0;
  return in_AX;
}


// ===== ovl_16dd @ 2000:16dd

void __cdecl16near ovl_16dd(void)

{
  undefined2 *puVar1;
  uint in_AX;
  uint uVar2;
  int iVar3;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar2 = in_AX >> 3;
  iVar3 = 8;
  do {
    if (G_animoff == '\0') {
      puVar1 = (undefined2 *)(G_savebx + 0x314);
      EXE_Motion(in_BX,uVar2);
    }
    else {
      puVar1 = (undefined2 *)(G_savebx + 0x454);
      EXE_TwitchMouse();
    }
    puVar1 = (undefined2 *)(G_savebx + 0x310);
    EXE_delay(uVar2);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


// ===== ovl_173e @ 2000:173e

/* WARNING: Control flow encountered bad instruction data */

void __cdecl16near ovl_173e(void)

{
  byte *pbVar1;
  undefined2 *puVar2;
  byte bVar3;
  undefined1 extraout_AH;
  uint uVar4;
  int iVar5;
  int iVar6;
  int in_BX;
  int unaff_SI;
  byte *pbVar7;
  undefined2 unaff_DS;
  undefined1 uVar8;
  undefined4 uVar9;
  undefined2 in_stack_00000000;
  undefined2 uVar10;
  
  uVar10 = G_musregptr;
  G_musregptr = G_musregstartptr + 0x50;
  puVar2 = (undefined2 *)(G_savebx + 0x220);
  EXE_ShowMouse();
  _ovl_173e = G_curmen;
  puVar2 = (undefined2 *)(G_savebx + 0xb4);
  EXE_Menu(2,in_BX,uVar10);
  ovl_173e = CONCAT11(extraout_AH,G_comflgs);
  G_comflgs = 1;
  DAT_2000_172d = &DAT_2000_1728;
  DAT_2000_171c = 0;
  DAT_2000_171e = G_scraplines - 4;
  DAT_2000_1720 = G_txtwx + -2;
  DAT_2000_1724 = G_txtwx + G_txtww;
  DAT_2000_1722 = G_txtwy + -2;
  DAT_2000_1726 = DAT_2000_1722 + G_txtwh + -6;
  DAT_2000_1733 = 0x13;
L_17ce:
  ovl_1960();
L_17d1:
  iVar6 = &G_mnuparms;
switchD_2000_1837_caseD_48:
  puVar2 = (undefined2 *)(G_savebx + 0x3f4);
  uVar9 = EXE_HandleMouse(iVar6,0,in_BX);
  uVar8 = (int)uVar9 == 0;
  if ((bool)uVar8) {
    puVar2 = (undefined2 *)(G_savebx + 0x94);
    uVar9 = EXE_ReadKbd(0);
  }
  else {
    if ((int)uVar9 == 1) goto L_1845;
    uVar8 = 0;
  }
  iVar6 = (int)((ulong)uVar9 >> 0x10);
  pbVar7 = (byte *)DAT_2000_172d;
  iVar5 = 5;
  do {
    bVar3 = (byte)uVar9;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pbVar1 = pbVar7;
    pbVar7 = pbVar7 + 1;
    uVar8 = bVar3 == *pbVar1;
  } while (!(bool)uVar8);
  if ((bool)uVar8) {
L_1845:
    DAT_2000_171c = DAT_2000_171e;
    ovl_18da();
    DAT_2000_171c = 0xffff;
    ovl_1960();
    if (_ovl_173e != 9) {
      puVar2 = (undefined2 *)(G_savebx + 0xb4);
      EXE_Menu(_ovl_173e,in_BX);
      G_comflgs = (char)ovl_173e;
    }
    puVar2 = (undefined2 *)(G_savebx + 0x70);
    EXE_HideMouse(in_BX);
    G_musregptr = in_stack_00000000;
    return;
  }
  uVar8 = (undefined1)((ulong)uVar9 >> 8);
  if ((bVar3 < 0x31) || (0x39 < bVar3)) {
    uVar4 = CONCAT11(bVar3,uVar8);
  }
  else {
    in_BX = 0x1704;
    uVar4 = CONCAT11(uVar8,*(undefined1 *)(ulong)(((uint)uVar9 & 0xff) + 0x1704));
  }
  if ((uVar4 < 0x47) || (0x51 < uVar4)) goto L_17d1;
  in_BX = (uVar4 - 0x47) * 2;
  switch(uVar4) {
  case 0x47:
    break;
  default:
    goto switchD_2000_1837_caseD_48;
  case 0x49:
    goto switchD_2000_1837_caseD_49;
  case 0x4b:
  case 0x4e:
    if (in_BX == 0) goto L_17d1;
    DAT_2000_171c = DAT_2000_171c + 1;
    break;
  case 0x4d:
switchD_2000_1837_caseD_4d:
    break;
  case 0x4f:
    if (*(uint *)0x171e < DAT_2000_171c) {
      DAT_2000_171c = DAT_2000_171e;
      goto switchD_2000_1837_caseD_4d;
    }
    break;
  case 0x50:
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  case 0x51:
    out(iVar6,(char)DAT_2000_171c);
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
  ovl_18da();
  goto L_17ce;
switchD_2000_1837_caseD_49:
  goto L_17d1;
}


// ===== ovl_18da @ 2000:18da

void __cdecl16near ovl_18da(void)

{
  byte *pbVar1;
  char *pcVar2;
  char cVar3;
  undefined2 *puVar4;
  byte bVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar4 = (undefined2 *)(G_savebx + 0x5c);
  EXE_ClrTxtWnd();
  ovl_18da = 0;
  pbVar1 = (byte *)(DAT_2000_171c + &G_scraplptrs);
  bVar5 = (byte)&G_scrap;
  pcVar6 = (char *)CONCAT11((char)((uint)&G_scrap >> 8) + CARRY1(bVar5,*pbVar1),
                            bVar5 + *pbVar1);
  iVar7 = 4;
  iVar8 = DAT_2000_171c;
  do {
    while( true ) {
      pcVar2 = pcVar6;
      pcVar6 = pcVar6 + 1;
      cVar3 = *pcVar2;
      if (cVar3 == '\0') goto L_1948;
      if (cVar3 == '\r') break;
      if (cVar3 == '\x05') {
        ovl_18da = ovl_18da ^ 1;
      }
      puVar4 = (undefined2 *)(*(int *)(DAT_2000_01ed + -0x728a) + 0x8c);
      EXE_ClrTxtWnd(cVar3);
    }
    if (*(int *)(DAT_2000_01ed + 0x2b22) != *(int *)(DAT_2000_01ed + 0x6ae5)) {
      puVar4 = (undefined2 *)(*(int *)(DAT_2000_01ed + -0x728a) + 0x40);
      EXE_ClrTxtWnd(iVar8);
    }
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
L_1948:
  if (ovl_18da == 1) {
    puVar4 = (undefined2 *)(*(int *)(DAT_2000_01ed + -0x728a) + 1000);
    EXE_ClrTxtWnd(iVar8);
  }
  return;
}


// ===== ovl_1960 @ 2000:1960

void ovl_1960(void)

{
  undefined2 *puVar1;
  int iVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar5;
  char cVar6;
  
  puVar1 = (undefined2 *)(G_savebx + 0x70);
  EXE_HideMouse();
  uVar3 = 0;
  bVar5 = false;
  if (DAT_2000_171c != -1) {
    bVar5 = DAT_2000_171c != 0;
    uVar3 = 0;
    if (DAT_2000_171c != DAT_2000_171e) {
      uVar3 = 1;
    }
  }
  uVar4 = CONCAT11(bVar5,uVar3);
  if (bVar5 == false) {
    puVar1 = (undefined2 *)(G_savebx + 0x444);
    EXE_DisableArrow(0,in_BX);
  }
  if ((char)uVar4 == '\0') {
    puVar1 = (undefined2 *)(G_savebx + 0x444);
    EXE_DisableArrow(1,in_BX);
  }
  iVar2 = DAT_2000_1733;
  DAT_2000_1731 = uVar4;
  if ((char)((uint)uVar4 >> 8) != '\0') {
    puVar1 = (undefined2 *)(G_savebx + 0x448);
    EXE_EnableArrow(DAT_2000_1720,DAT_2000_1722,0,in_BX,DAT_2000_1733);
    iVar2 = iVar2 + 1;
  }
  cVar6 = (char)uVar4;
  puVar1 = (undefined2 *)(G_savebx + 0x318);
  EXE_moveabc(iVar2,DAT_2000_1720,DAT_2000_1722,
                     (int)G_oppscr,
                     (int)((ulong)G_oppscr >> 0x10),in_BX);
  iVar2 = 0x15;
  if (cVar6 != '\0') {
    iVar2 = 0x15;
    puVar1 = (undefined2 *)(G_savebx + 0x448);
    EXE_EnableArrow(DAT_2000_1724,DAT_2000_1726,1,in_BX,0x15);
    iVar2 = iVar2 + 1;
  }
  puVar1 = (undefined2 *)(G_savebx + 0x318);
  EXE_moveabc(iVar2,DAT_2000_1724,DAT_2000_1726,
                     (int)G_oppscr,
                     (int)((ulong)G_oppscr >> 0x10),in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0x220);
  EXE_ShowMouse(in_BX);
  return;
}


// ===== ovl_198a @ 2000:198a

void __cdecl16near ovl_198a(void)

{
  undefined2 *puVar1;
  int iVar2;
  undefined2 in_DX;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  char cVar3;
  
  if ((char)((uint)in_DX >> 8) == '\0') {
    puVar1 = (undefined2 *)(G_savebx + 0x444);
    EXE_DisableArrow(0);
  }
  if ((char)in_DX == '\0') {
    puVar1 = (undefined2 *)(G_savebx + 0x444);
    EXE_DisableArrow(1,in_BX);
  }
  iVar2 = DAT_2000_1733;
  DAT_2000_1731 = in_DX;
  if ((char)((uint)in_DX >> 8) != '\0') {
    puVar1 = (undefined2 *)(G_savebx + 0x448);
    EXE_EnableArrow(DAT_2000_1720,DAT_2000_1722,0,in_BX,DAT_2000_1733);
    iVar2 = iVar2 + 1;
  }
  cVar3 = (char)in_DX;
  puVar1 = (undefined2 *)(G_savebx + 0x318);
  EXE_moveabc(iVar2,DAT_2000_1720,DAT_2000_1722,
                     (int)G_oppscr,
                     (int)((ulong)G_oppscr >> 0x10),in_BX);
  iVar2 = 0x15;
  if (cVar3 != '\0') {
    iVar2 = 0x15;
    puVar1 = (undefined2 *)(G_savebx + 0x448);
    EXE_EnableArrow(DAT_2000_1724,DAT_2000_1726,1,in_BX,0x15);
    iVar2 = iVar2 + 1;
  }
  puVar1 = (undefined2 *)(G_savebx + 0x318);
  EXE_moveabc(iVar2,DAT_2000_1724,DAT_2000_1726,
                     (int)G_oppscr,
                     (int)((ulong)G_oppscr >> 0x10),in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0x220);
  EXE_ShowMouse(in_BX);
  return;
}


// ===== FAR_e249 @ 2000:1a4d

void FAR_e249(void)

{
  undefined2 *puVar1;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (*(char *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0x23) == '\0') {
    puVar1 = (undefined2 *)(G_savebx + 0x260);
    EXE_IComTxt(0x117);
    ovl_01d3();
    return;
  }
  puVar1 = (undefined2 *)(G_savebx + 0x260);
  EXE_IComTxt(0x118);
  puVar1 = (undefined2 *)(G_savebx + 0x3cc);
  EXE_song(0xc,in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0x3d0);
  EXE_finishsong(in_BX);
  ovl_01d3();
  return;
}


// ===== FAR_DISTITEM @ 2000:1ab4

void FAR_DISTITEM(void)

{
  undefined1 *puVar1;
  undefined2 *puVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  undefined2 uVar6;
  int iVar7;
  int iVar8;
  int in_BX;
  int unaff_BP;
  int unaff_SI;
  undefined1 *puVar9;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  s_Include__f__2000_1a9e[3] = '\0';
  puVar2 = (undefined2 *)(G_savebx + 0x54);
  EXE_SetTxtWnd(1);
  uVar4 = ovl_1ed6();
  *(uint *)(unaff_BP + -6) = uVar4;
  if (*(char *)(unaff_BP + 0xe) == '\0') {
    if ((char)(uVar4 >> 8) != '\0') {
      uVar4 = ovl_1e2b();
    }
  }
  else {
    uVar4 = uVar4 & 0xff;
    *(undefined1 *)(unaff_BP + -5) = 0;
  }
  if (1 < uVar4) {
    if (G_curmpg == 0x5e) {
      puVar2 = (undefined2 *)(G_savebx + 0x260);
      EXE_IComTxt(0xf1,in_BX);
    }
    else {
      iVar7 = *(int *)(*(int *)(unaff_BP + 0xc) * 2 + &G_heroptr);
      G_ISheroptr = iVar7;
      if (*(byte *)(iVar7 + 0xb8) < 2) {
        iVar7 = *(int *)(unaff_BP + 0xe);
        G_poolflag = iVar7;
        *(undefined2 *)(unaff_BP + -8) = 0xffff;
        if (iVar7 == 0) {
          *(undefined2 *)(unaff_BP + -8) = *(undefined2 *)(unaff_BP + 0xc);
        }
        puVar9 = (undefined1 *)&G_poollist;
        for (iVar7 = 0x5d; iVar7 != 0; iVar7 = iVar7 + -1) {
          puVar1 = puVar9;
          puVar9 = puVar9 + 1;
          *puVar1 = 0xff;
        }
        iVar8 = 0x5d;
        iVar7 = 0;
        *(undefined2 *)(unaff_BP + -10) = 0;
        do {
          bVar3 = (byte)iVar7;
          if (((bVar3 < 9) ||
              ((0x30 < bVar3 &&
               ((bVar3 < 0x4c || ((0x4f < bVar3 && ((bVar3 < 0x53 || (0x59 < bVar3)))))))))) &&
             (puVar2 = (undefined2 *)(G_savebx + 0x158),
             iVar5 = EXE_IComTxt(iVar7,*(undefined2 *)(unaff_BP + -8),
                                        &G_invinfobuf), iVar5 != 0)) {
            LOCK();
            iVar5 = *(int *)(unaff_BP + -10);
            *(int *)(unaff_BP + -10) = in_BX;
            UNLOCK();
            *(undefined1 *)(iVar5 + &G_poollist) = (char)iVar7;
            LOCK();
            in_BX = *(int *)(unaff_BP + -10);
            *(int *)(unaff_BP + -10) = iVar5 + 1;
            UNLOCK();
          }
          iVar7 = iVar7 + 1;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        if (*(char *)(unaff_BP + -10) == '\0') {
          uVar6 = 0x35;
          if (*(char *)(unaff_BP + 0xe) == '\0') {
            uVar6 = 0x34;
          }
          puVar2 = (undefined2 *)(G_savebx + 0x260);
          EXE_IComTxt(uVar6,in_BX);
        }
        else {
          puVar2 = (undefined2 *)(G_savebx + 0x260);
          EXE_IComTxt(0x2b);
          puVar2 = (undefined2 *)(G_savebx + 0x174);
          iVar7 = EXE_ListSel(*(undefined2 *)(unaff_BP + -10),
                                     *(undefined2 *)(in_BX + 0x324),*(undefined2 *)(in_BX + 0x326),
                                     in_BX);
          if (iVar7 != -1) {
            *(uint *)(unaff_BP + -0xe) = (uint)*(byte *)(iVar7 + &G_poollist);
            if (*(char *)(unaff_BP + 0xe) == '\0') {
              iVar7 = G_ISheroptr;
              puVar2 = (undefined2 *)(G_savebx + 0x158);
              EXE_SearchInv(*(undefined2 *)(unaff_BP + -0xe),
                                 G_curpla,&G_invinfobuf);
              if (*(char *)(unaff_BP + -0xe) == '\0') {
                uVar4 = *(uint *)(iVar7 + 0xcc);
              }
              else {
                uVar4 = (uint)G_invinfobuf;
              }
              *(uint *)(unaff_BP + -0xc) = uVar4;
              puVar2 = (undefined2 *)(G_savebx + 0x168);
              EXE_DecObj(iVar7,G_invinfobuf+2,uVar4,in_BX);
              iVar7 = 0;
              iVar8 = 6;
              do {
                iVar5 = *(int *)(iVar7 + &G_heroptr);
                if ((*(int *)(iVar7 + &G_party) != 0xff) &&
                   ((s_Include__f__2000_1a9e[3] != '\0' || (*(byte *)(iVar5 + 0xb8) < 2)))) {
                  uVar4 = ((*(uint *)(unaff_BP + -6) >> 1) + *(int *)(unaff_BP + -0xc)) /
                          *(uint *)(unaff_BP + -6);
                  puVar2 = (undefined2 *)(G_savebx + 0x164);
                  iVar5 = EXE_IncObj(iVar5,*(undefined2 *)(unaff_BP + -0xe),uVar4,
                                             in_BX);
                  if (iVar5 != 0) {
                    *(int *)(unaff_BP + -0xc) = *(int *)(unaff_BP + -0xc) - uVar4;
                  }
                  *(int *)(unaff_BP + -6) = *(int *)(unaff_BP + -6) + -1;
                }
                iVar7 = iVar7 + 2;
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
              if (*(int *)(unaff_BP + -0xc) != 0) {
                puVar2 = (undefined2 *)(G_savebx + 0x164);
                EXE_IncObj(G_ISheroptr,
                                   *(undefined2 *)(unaff_BP + -0xe),*(undefined2 *)(unaff_BP + -0xc)
                                   ,in_BX);
              }
              puVar2 = (undefined2 *)(G_savebx + 0x260);
              EXE_IComTxt(0x37,in_BX);
            }
            else {
              uVar4 = 0;
              *(undefined2 *)(unaff_BP + -0xc) = 0;
              do {
                if (uVar4 != G_curpla) {
                  iVar7 = *(int *)(uVar4 * 2 + &G_heroptr);
                  uVar4 = uVar4 & 0x7fff;
                  if ((*(byte *)(iVar7 + 0xb8) < 2) &&
                     (puVar2 = (undefined2 *)(G_savebx + 0x158),
                     iVar8 = EXE_IComTxt(*(undefined2 *)(unaff_BP + -0xe),uVar4,
                                                &G_invinfobuf), iVar8 != 0)) {
                    if (*(char *)(unaff_BP + -0xe) == '\0') {
                      uVar6 = *(undefined2 *)(iVar7 + 0xcc);
                    }
                    else {
                      uVar6 = CONCAT11((char)(uVar4 >> 8),G_invinfobuf);
                    }
                    *(undefined2 *)(unaff_BP + -0xc) = uVar6;
                    puVar2 = (undefined2 *)(G_savebx + 0x164);
                    iVar8 = EXE_IncObj(G_ISheroptr,
                                               *(undefined2 *)(unaff_BP + -0xe),
                                               *(undefined2 *)(unaff_BP + -0xc),in_BX);
                    if (iVar8 == 0) {
                      puVar2 = (undefined2 *)(G_savebx + 0x158);
                      EXE_SearchInv(*(undefined2 *)(unaff_BP + -0xe),
                                         G_curpla,&G_invinfobuf);
                      if (*(char *)(unaff_BP + -0xe) == '\0') {
                        iVar8 = 9999 - *(int *)(G_ISheroptr + 0xcc);
                      }
                      else {
                        iVar8 = 99 - (uint)G_invinfobuf;
                      }
                      *(int *)(unaff_BP + -0xc) = iVar8;
                      puVar2 = (undefined2 *)(G_savebx + 0x164);
                      EXE_IncObj(G_ISheroptr,
                                         *(undefined2 *)(unaff_BP + -0xe),
                                         *(undefined2 *)(unaff_BP + -0xc),in_BX);
                      puVar2 = (undefined2 *)(G_savebx + 0x158);
                      EXE_SearchInv(*(undefined2 *)(unaff_BP + -0xe),uVar4,
                                         &G_invinfobuf);
                      puVar2 = (undefined2 *)(G_savebx + 0x168);
                      EXE_DecObj(iVar7,G_invinfobuf+2,
                                         *(undefined2 *)(unaff_BP + -0xc),in_BX);
                      goto L_1def;
                    }
                    puVar2 = (undefined2 *)(G_savebx + 0x168);
                    EXE_DecObj(iVar7,G_invinfobuf+2,
                                       *(undefined2 *)(unaff_BP + -0xc));
                  }
                }
                uVar4 = uVar4 + 1;
              } while (uVar4 < 6);
              puVar2 = (undefined2 *)(G_savebx + 0x260);
              EXE_IComTxt(0x37,in_BX);
            }
L_1def:
            if (G_curscn == '\x03') {
              puVar2 = (undefined2 *)(G_savebx + 0x328);
              EXE_StatS4(G_ISheroptr,0,in_BX);
            }
          }
        }
      }
      else {
        ovl_1f02();
      }
    }
  }
  puVar2 = (undefined2 *)(G_savebx + 0x44);
  EXE_SetMnu(&G_mnuparms,in_BX);
  ovl_01d3();
  return;
}


// ===== ovl_1e2b @ 2000:1e2b

undefined2 __cdecl16near ovl_1e2b(void)

{
  byte bVar1;
  undefined2 *puVar2;
  undefined2 in_AX;
  int iVar3;
  undefined2 in_DX;
  undefined2 in_BX;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined2 uVar4;
  
  if ((byte)((uint)in_AX >> 8) < 2) {
    G_deftxtparms+6 = in_DX;
    G_deftxtparms+8 = unaff_DS;
  }
  else {
    G_deftxtparms+6 = 0x1aae;
    G_deftxtparms+8 = 0x2000;
  }
  puVar2 = (undefined2 *)(G_savebx + 0x5c);
  EXE_ClrTxtWnd();
  puVar2 = (undefined2 *)(G_savebx + 0xe4);
  EXE_InitScrap(in_BX);
  ovl_06bd();
  puVar2 = (undefined2 *)(G_savebx + 0xec);
  EXE_PrtScrap(0xff,in_BX);
  uVar4 = G_animoff;
  G_animoff = 1;
  puVar2 = (undefined2 *)(G_savebx + 0x108);
  iVar3 = EXE_SetYN(in_BX);
  G_animoff = uVar4;
  if (iVar3 == 0) {
    s_Include__f__2000_1a9e[3] = '\x01';
    LOCK();
    bVar1 = *(byte *)(unaff_BP + -5);
    *(byte *)(unaff_BP + -5) = 0;
    UNLOCK();
    *(int *)(unaff_BP + -6) = *(int *)(unaff_BP + -6) + (uint)bVar1;
  }
  else if (iVar3 != -1) {
    *(undefined1 *)(unaff_BP + -5) = 0;
  }
  puVar2 = (undefined2 *)(G_savebx + 0xb4);
  EXE_Menu(3,in_BX);
  puVar2 = (undefined2 *)(G_savebx + 0xb8);
  EXE_InitCom(0x1e27,0x2000,8,in_BX);
  return *(undefined2 *)(unaff_BP + -6);
}


// ===== ovl_1ed6 @ 2000:1ed6

undefined2 __cdecl16near ovl_1ed6(void)

{
  undefined2 uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar1 = 0;
  iVar4 = 0;
  iVar3 = 6;
  do {
    if (*(int *)(iVar4 + &G_party) != 0xff) {
      cVar2 = (char)((uint)uVar1 >> 8);
      if (*(byte *)(*(int *)(iVar4 + &G_heroptr) + 0xb8) < 2) {
        uVar1 = CONCAT11(cVar2,(char)uVar1 + '\x01');
      }
      else {
        uVar1 = CONCAT11(cVar2 + '\x01',(char)uVar1);
      }
    }
    iVar4 = iVar4 + 2;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return uVar1;
}


// ===== ovl_1f02 @ 2000:1f02

void __cdecl16near ovl_1f02(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar1 = G_curpla;
  G_curpla = 0;
  puVar2 = (undefined2 *)(G_savebx + 0x260);
  EXE_IComTxt(0xd7);
  G_curpla = uVar1;
  return;
}


// ===== FAR_INT62_0a @ 2000:1f20

void FAR_INT62_0a(void)

{
  int iVar1;
  byte bVar2;
  undefined2 *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined2 uVar7;
  int in_BX;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar8;
  
  iVar6 = *(int *)(*(int *)(unaff_BP + 0xc) * 2 + &G_heroptr);
  if (((*(byte *)(iVar6 + 0xbd) & 0x80) != 0) && (G_curmpg == 0x5e)) {
    puVar3 = (undefined2 *)(G_savebx + 0x54);
    EXE_SetTxtWnd(1);
    puVar3 = (undefined2 *)(G_savebx + 0x260);
    EXE_IComTxt(0x113,in_BX);
    goto L_21ae;
  }
  G_ISheroptr = iVar6;
  puVar3 = (undefined2 *)(G_savebx + 0x54);
  EXE_SetTxtWnd(1);
  puVar3 = (undefined2 *)(G_savebx + 0x260);
  EXE_IComTxt(0x26);
  puVar3 = (undefined2 *)(G_savebx + 0x1c0);
  uVar4 = EXE_HeroSel(1,0);
  if ((uVar4 < 0x100) && (uVar4 != *(uint *)(unaff_BP + 0xc))) {
    *(uint *)(unaff_BP + -6) = uVar4;
    iVar6 = *(int *)(uVar4 * 2 + &G_heroptr);
    bVar8 = false;
    ovl_21c6(*(undefined2 *)(unaff_BP + 0xc));
    if (bVar8) goto L_21ae;
    puVar3 = (undefined2 *)(G_savebx + 0x260);
    EXE_IComTxt(0x2b);
    puVar3 = (undefined2 *)(G_savebx + 0x2cc);
    uVar4 = EXE_ItemSel(*(undefined2 *)(unaff_BP + 0xc));
    if (uVar4 < 0x28) {
      *(uint *)(unaff_BP + -8) = uVar4;
      if (((*(byte *)(G_ISheroptr + 0xbd) & 0x80) != 0) ||
         ((puVar3 = (undefined2 *)(G_savebx + 0x2d0),
          iVar5 = EXE_ItemSel(G_ISheroptr,iVar6,
                                     *(undefined2 *)(unaff_BP + -8),
                                     *(char *)(unaff_BP + -6) == '\x06'), iVar5 != 0 &&
          (puVar3 = (undefined2 *)(G_savebx + 0x2d4),
          iVar5 = EXE_ItemSel(G_ISheroptr,iVar6,
                                     *(undefined2 *)(unaff_BP + -8)), iVar5 != 0)))) {
        LOCK();
        iVar5 = G_ISheroptr;
        G_ISheroptr = iVar6;
        UNLOCK();
        LOCK();
        iVar6 = *(int *)(unaff_BP + -8);
        *(int *)(unaff_BP + -8) = in_BX;
        UNLOCK();
        bVar2 = *(byte *)(iVar6 + iVar5 + 0x2b);
        if (bVar2 == 0) {
          uVar4 = *(uint *)(iVar5 + 0xcc);
        }
        else {
          uVar4 = (uint)*(byte *)(iVar6 + iVar5 + 0x53);
        }
        LOCK();
        iVar1 = G_ISheroptr;
        G_ISheroptr = iVar5;
        UNLOCK();
        LOCK();
        in_BX = *(int *)(unaff_BP + -8);
        *(int *)(unaff_BP + -8) = iVar6;
        UNLOCK();
        *(uint *)(unaff_BP + -10) = (uint)bVar2;
        *(uint *)(unaff_BP + -0xc) = uVar4;
        if ((*(byte *)(G_ISheroptr + 0xbd) & 0x80) != 0) {
          G_corpsexfer = 1;
        }
        if (*(char *)(unaff_BP + -6) == '\x06') {
          puVar3 = (undefined2 *)(G_savebx + 0x168);
          EXE_DecObj(G_ISheroptr,
                             *(undefined2 *)(unaff_BP + -8),uVar4,in_BX);
          puVar3 = (undefined2 *)(G_savebx + 0x260);
          EXE_IComTxt(0x2c,in_BX);
        }
        else {
          if ((8 < bVar2) &&
             ((bVar2 < 0x31 ||
              ((0x4b < bVar2 && ((bVar2 < 0x50 || ((0x52 < bVar2 && (bVar2 < 0x5a)))))))))) {
            uVar4 = 1;
          }
          iVar6 = 1;
          if (uVar4 != 1) {
            G_deftxtparms = uVar4;
            puVar3 = (undefined2 *)(G_savebx + 0x260);
            EXE_IComTxt(0x61,in_BX,uVar4);
            puVar3 = (undefined2 *)(G_savebx + 0x40);
            EXE_MyRet(in_BX);
            puVar3 = (undefined2 *)(G_savebx + 0x140);
            iVar6 = EXE_GetNum(0,uVar4,in_BX);
            puVar3 = (undefined2 *)(G_savebx + 0x5c);
            EXE_ClrTxtWnd(in_BX);
            *(int *)(unaff_BP + -0xc) = iVar6;
          }
          *(int *)(unaff_BP + -0xe) = iVar6;
          if ((iVar6 != 0) &&
             (puVar3 = (undefined2 *)(G_savebx + 0x168),
             iVar6 = EXE_ClrTxtWnd(G_ISheroptr,
                                        *(undefined2 *)(unaff_BP + -8),
                                        *(undefined2 *)(unaff_BP + -0xc),in_BX), iVar6 != 0)) {
            puVar3 = (undefined2 *)(G_savebx + 0x164);
            iVar6 = EXE_IncObj(iVar1,*(undefined2 *)(unaff_BP + -10),
                                       *(undefined2 *)(unaff_BP + -0xc),in_BX);
            if (iVar6 == 0) {
              puVar3 = (undefined2 *)(G_savebx + 0x164);
              EXE_IncObj(G_ISheroptr,
                                 *(undefined2 *)(unaff_BP + -10),*(undefined2 *)(unaff_BP + -0xc),
                                 in_BX);
            }
            else {
              G_deftxtparms = *(undefined2 *)(unaff_BP + -0xe);
              puVar3 = (undefined2 *)(G_savebx + 0x13c);
              EXE_SetTxtObj(*(undefined2 *)(unaff_BP + -10),in_BX);
              G_othername = iVar1;
              G_othername+2 = unaff_DS;
              uVar7 = 0x28;
              if (*(int *)(unaff_BP + -0xe) != 1) {
                uVar7 = 0x29;
              }
              puVar3 = (undefined2 *)(G_savebx + 0x260);
              EXE_IComTxt(uVar7,in_BX);
            }
          }
        }
        if (G_curscn == '\x03') {
          puVar3 = (undefined2 *)(G_savebx + 0x328);
          EXE_StatS4(G_ISheroptr,0,in_BX);
        }
      }
      goto L_21ae;
    }
  }
  puVar3 = (undefined2 *)(G_savebx + 0x5c);
  EXE_ClrTxtWnd(in_BX);
L_21ae:
  puVar3 = (undefined2 *)(G_savebx + 0x44);
  EXE_SetMnu(&G_mnuparms,in_BX);
  ovl_01d3();
  return;
}


// ===== ovl_21c6 @ 2000:21c6

void __cdecl16near ovl_21c6(undefined2 param_1)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  int in_AX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if ((in_AX != 6) && (G_curmpg == '^')) {
    uVar1 = G_curpla;
    G_curpla = param_1;
    puVar2 = (undefined2 *)(G_savebx + 0x1d4);
    EXE_ChkRng(*(undefined1 *)(in_AX + &G_p1x),
                       *(undefined1 *)(in_AX + &G_p1y),1,1);
    G_curpla = uVar1;
  }
  return;
}


// ===== ovl_221d @ 2000:221d

/* WARNING: Unable to track spacebase fully for stack */

void ovl_221d(int param_1)

{
  int *piVar1;
  char *pcVar2;
  undefined2 *puVar3;
  code *pcVar4;
  char cVar5;
  int in_CX;
  int iVar6;
  undefined2 uVar7;
  int in_BX;
  int unaff_BP;
  int unaff_SI;
  int unaff_DI;
  char *pcVar8;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar9;
  
  if ((*(byte *)(param_1 + 0xbd) & 0x80) != 0) {
    G_corpsexfer = 1;
  }
  piVar1 = (int *)(in_BX + &OV_0x4c);
  *piVar1 = *piVar1 + in_CX;
  uVar7 = 0x2f;
  if ((*(byte *)(*(int *)(unaff_BP + 0xb) + 0xb8) < 2) &&
     (cVar5 = *(char *)(*(int *)(unaff_BP + 0xb) + *(int *)(unaff_BP + 0xf) + 0x2b), cVar5 != '\x11'
     )) {
    bVar9 = true;
    if ((*(int *)(unaff_BP + 0xd) == 0) ||
       (bVar9 = *(uint *)(unaff_BP + 0xd) == &G_member0+1319U,
       &G_member0+1319U <= *(uint *)(unaff_BP + 0xd))) {
      *(undefined2 *)(param_1 + -2) = 0x2000;
      pcVar8 = (char *)0x2239;
      iVar6 = 8;
      do {
        if (iVar6 == 0) break;
        iVar6 = iVar6 + -1;
        pcVar2 = pcVar8;
        pcVar8 = pcVar8 + 1;
        bVar9 = cVar5 == *pcVar2;
      } while (!bVar9);
      if (bVar9) goto L_22a1;
    }
    uVar7 = 0x31;
    cVar5 = (char)*(undefined2 *)(unaff_BP + 0xf);
    if (cVar5 != *(char *)(*(int *)(unaff_BP + 0xb) + 0xbf)) {
      uVar7 = 0x30;
      pcVar8 = (char *)(*(int *)(unaff_BP + 0xb) + 0xc0);
      bVar9 = pcVar8 == (char *)0x0;
      iVar6 = 6;
      *(undefined2 *)(param_1 + -2) = unaff_DS;
      do {
        if (iVar6 == 0) break;
        iVar6 = iVar6 + -1;
        pcVar2 = pcVar8;
        pcVar8 = pcVar8 + 1;
        bVar9 = cVar5 == *pcVar2;
      } while (!bVar9);
      if (!bVar9) goto L_22af;
    }
  }
L_22a1:
  *(int *)(param_1 + -2) = in_BX;
  *(undefined2 *)(param_1 + -4) = uVar7;
  puVar3 = (undefined2 *)(G_lookprt+1 + 0x260);
  uVar7 = puVar3[1];
  pcVar4 = (code *)*puVar3;
  *(undefined2 *)(param_1 + -6) = 0x2000;
  *(undefined2 *)(param_1 + -8) = 0x22ab;
  (*pcVar4)();
L_22af:
  ovl_01d3();
  return;
}


// ===== FAR_OK2GIVE @ 2000:223d

void FAR_OK2GIVE(void)

{
  char *pcVar1;
  undefined2 *puVar2;
  char cVar3;
  int iVar4;
  undefined2 uVar5;
  int unaff_BP;
  int unaff_SI;
  char *pcVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar7;
  
  uVar5 = 0x2f;
  if ((*(byte *)(*(int *)(unaff_BP + 0xc) + 0xb8) < 2) &&
     (cVar3 = *(char *)(*(int *)(unaff_BP + 0xc) + *(int *)(unaff_BP + 0x10) + 0x2b),
     cVar3 != '\x11')) {
    bVar7 = true;
    if ((*(int *)(unaff_BP + 0xe) == 0) ||
       (bVar7 = *(uint *)(unaff_BP + 0xe) == &G_member6U,
       &G_member6U <= *(uint *)(unaff_BP + 0xe))) {
      pcVar6 = (char *)0x2239;
      iVar4 = 8;
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        pcVar1 = pcVar6;
        pcVar6 = pcVar6 + 1;
        bVar7 = cVar3 == *pcVar1;
      } while (!bVar7);
      if (bVar7) goto L_22a1;
    }
    uVar5 = 0x31;
    cVar3 = (char)*(undefined2 *)(unaff_BP + 0x10);
    if (cVar3 != *(char *)(*(int *)(unaff_BP + 0xc) + 0xbf)) {
      uVar5 = 0x30;
      pcVar6 = (char *)(*(int *)(unaff_BP + 0xc) + 0xc0);
      bVar7 = pcVar6 == (char *)0x0;
      iVar4 = 6;
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        pcVar1 = pcVar6;
        pcVar6 = pcVar6 + 1;
        bVar7 = cVar3 == *pcVar1;
      } while (!bVar7);
      if (!bVar7) goto L_22af;
    }
  }
L_22a1:
  puVar2 = (undefined2 *)(G_savebx + 0x260);
  EXE_IComTxt(uVar5);
L_22af:
  ovl_01d3();
  return;
}


// ===== FAR_INCOBJ @ 2000:22b2

void FAR_INCOBJ(void)

{
  char *pcVar1;
  undefined1 *puVar2;
  byte *pbVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined2 uVar6;
  undefined2 *puVar7;
  long lVar8;
  char cVar9;
  byte bVar10;
  uint uVar11;
  byte bVar12;
  int iVar13;
  int iVar14;
  int unaff_BP;
  int unaff_SI;
  undefined1 *puVar15;
  byte *pbVar16;
  undefined1 *puVar17;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar18;
  
  if (*(int *)(unaff_BP + 0x10) == 0) goto L_23fc;
  G_othername = *(undefined2 *)(unaff_BP + 0xc);
  G_othername+2 = unaff_DS;
  iVar5 = *(int *)(unaff_BP + 0xc);
  lVar8 = (ulong)*(uint *)(*(int *)(unaff_BP + 0xe) * 2 + G_lootvalptr) *
          (ulong)*(uint *)(unaff_BP + 0x10);
  uVar11 = (uint)lVar8;
  if (((int)((ulong)lVar8 >> 0x10) != 0) || (30000 < uVar11)) {
    uVar11 = 30000;
  }
  *(uint *)(unaff_BP + -8) = uVar11;
  *(undefined2 *)(unaff_BP + -6) = 0xffff;
  bVar10 = *(byte *)(unaff_BP + 0xe);
  bVar18 = bVar10 == 9;
  if ((bVar10 < 9) ||
     ((0x30 < bVar10 &&
      ((bVar18 = bVar10 == 0x4c, bVar10 < 0x4c ||
       ((0x4f < bVar10 &&
        ((bVar18 = bVar10 == 0x53, bVar10 < 0x53 || (bVar18 = bVar10 == 0x59, 0x59 < bVar10)))))))))
     ) {
    pbVar16 = (byte *)(iVar5 + 0x2b);
    iVar14 = 0x28;
    do {
      if (iVar14 == 0) break;
      iVar14 = iVar14 + -1;
      pbVar3 = pbVar16;
      pbVar16 = pbVar16 + 1;
      bVar18 = bVar10 == *pbVar3;
    } while (!bVar18);
    if (!bVar18) goto L_2383;
    iVar14 = 0x27 - iVar14;
    *(int *)(unaff_BP + -6) = iVar14;
    iVar13 = *(int *)(unaff_BP + 0x10);
    if (bVar10 == 0) {
      uVar11 = iVar13 + *(int *)(iVar5 + 0xcc);
      if (9999 < uVar11) {
L_236f:
        puVar7 = (undefined2 *)(G_savebx + 0x260);
        EXE_IComTxt(0x32);
        goto L_23fc;
      }
    }
    else {
      bVar12 = (char)iVar13 + *(char *)(iVar14 + iVar5 + 0x53);
      uVar11 = CONCAT11((char)((uint)iVar13 >> 8),bVar12);
      if (99 < bVar12) goto L_236f;
    }
  }
  else {
L_2383:
    if (*(char *)(iVar5 + 0x52) != -1) {
      puVar7 = (undefined2 *)(G_savebx + 0x260);
      EXE_IComTxt(0x33);
      goto L_23fc;
    }
    iVar14 = 0;
    while (*(byte *)(iVar14 + iVar5 + 0x2b) <= bVar10) {
      iVar14 = iVar14 + 1;
    }
    *(int *)(unaff_BP + -6) = iVar14;
    iVar14 = 0x27 - iVar14;
    if (iVar14 != 0) {
      puVar17 = (undefined1 *)(iVar5 + 0x52);
      puVar15 = (undefined1 *)(iVar5 + 0x51);
      for (iVar13 = iVar14; iVar13 != 0; iVar13 = iVar13 + -1) {
        puVar4 = puVar17;
        puVar17 = puVar17 + -1;
        puVar2 = puVar15;
        puVar15 = puVar15 + -1;
        *puVar4 = *puVar2;
      }
      puVar17 = (undefined1 *)(iVar5 + 0x7a);
      puVar15 = (undefined1 *)(iVar5 + 0x79);
      for (; iVar14 != 0; iVar14 = iVar14 + -1) {
        puVar4 = puVar17;
        puVar17 = puVar17 + -1;
        puVar2 = puVar15;
        puVar15 = puVar15 + -1;
        *puVar4 = *puVar2;
      }
      iVar14 = 6;
      iVar13 = 0;
      uVar6 = *(undefined2 *)(unaff_BP + -6);
      do {
        cVar9 = (char)uVar6;
        if (cVar9 <= *(char *)(iVar13 + iVar5 + 0xc0)) {
          pcVar1 = (char *)(iVar13 + iVar5 + 0xc0);
          *pcVar1 = *pcVar1 + '\x01';
        }
        iVar13 = iVar13 + 1;
        iVar14 = iVar14 + -1;
      } while (iVar14 != 0);
      if (cVar9 <= *(char *)(iVar5 + 0xbf)) {
        *(char *)(iVar5 + 0xbf) = *(char *)(iVar5 + 0xbf) + '\x01';
      }
    }
    iVar14 = *(int *)(unaff_BP + -6);
    uVar11 = *(uint *)(unaff_BP + 0x10);
    bVar10 = (byte)*(undefined2 *)(unaff_BP + 0xe);
  }
  if (bVar10 == 0) {
    *(uint *)(iVar5 + 0xcc) = uVar11;
    uVar11 = 0;
  }
  *(undefined1 *)(iVar14 + iVar5 + 0x53) = (char)uVar11;
  *(byte *)(iVar14 + iVar5 + 0x2b) = bVar10;
  ovl_2402();
L_23fc:
  ovl_01d3();
  return;
}


// ===== ovl_2402 @ 2000:2402

void __cdecl16near ovl_2402(void)

{
  int in_AX;
  uint uVar1;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (OV_0xb8 == '\x02') {
    uVar1 = in_AX + OV_0xd0;
    if (30000 < uVar1) {
      uVar1 = 30000;
    }
    OV_0xd0 = uVar1;
  }
  return;
}


// ===== FAR_DECOBJ @ 2000:241a

void FAR_DECOBJ(void)

{
  char *pcVar1;
  int iVar2;
  undefined1 *puVar3;
  byte bVar4;
  char cVar5;
  int iVar6;
  undefined2 *puVar7;
  undefined2 uVar8;
  int iVar9;
  int iVar10;
  undefined2 uVar11;
  int in_BX;
  int unaff_BP;
  int unaff_SI;
  undefined1 *puVar12;
  undefined1 *puVar13;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  if (*(int *)(unaff_BP + 0x10) == 0) goto L_2500;
  iVar6 = *(int *)(unaff_BP + 0xc);
  LOCK();
  iVar9 = *(int *)(unaff_BP + 0xe);
  *(int *)(unaff_BP + 0xe) = in_BX;
  UNLOCK();
  bVar4 = *(byte *)(iVar9 + iVar6 + 0x2b);
  uVar11 = CONCAT11(*(undefined1 *)(iVar9 + iVar6 + 0x53),bVar4);
  LOCK();
  iVar10 = *(int *)(unaff_BP + 0xe);
  *(int *)(unaff_BP + 0xe) = iVar9;
  UNLOCK();
  *(undefined2 *)(unaff_BP + -6) = uVar11;
  if ((bVar4 < 9) ||
     ((0x30 < bVar4 && ((bVar4 < 0x4c || ((0x4f < bVar4 && ((bVar4 < 0x53 || (0x59 < bVar4))))))))))
  {
    uVar8 = 0;
    if (bVar4 == 0) {
      uVar8 = *(undefined2 *)(iVar6 + 0xcc);
      uVar11 = 0;
    }
    iVar9 = CONCAT11((char)((uint)uVar8 >> 8),(char)uVar8 + (char)((uint)uVar11 >> 8)) -
            *(int *)(unaff_BP + 0x10);
    if (iVar9 < 0) {
      puVar7 = (undefined2 *)(G_savebx + 0x260);
      EXE_IComTxt(0x25,iVar10);
      goto L_2500;
    }
    if ((char)uVar11 == '\0') {
      *(int *)(iVar6 + 0xcc) = iVar9;
    }
    else {
      LOCK();
      iVar2 = *(int *)(unaff_BP + 0xe);
      *(int *)(unaff_BP + 0xe) = iVar10;
      UNLOCK();
      *(undefined1 *)(iVar2 + iVar6 + 0x53) = (char)iVar9;
      LOCK();
      *(int *)(unaff_BP + 0xe) = iVar2;
      UNLOCK();
    }
    if (iVar9 != 0) goto L_2500;
  }
  iVar9 = 0x27 - *(int *)(unaff_BP + 0xe);
  if (iVar9 != 0) {
    puVar13 = (undefined1 *)(iVar6 + 0x2b + *(int *)(unaff_BP + 0xe));
    puVar12 = puVar13;
    for (iVar10 = iVar9; puVar12 = puVar12 + 1, iVar10 != 0; iVar10 = iVar10 + -1) {
      puVar3 = puVar13;
      puVar13 = puVar13 + 1;
      *puVar3 = *puVar12;
    }
    puVar13 = (undefined1 *)(iVar6 + 0x53 + *(int *)(unaff_BP + 0xe));
    puVar12 = puVar13;
    for (; puVar12 = puVar12 + 1, iVar9 != 0; iVar9 = iVar9 + -1) {
      puVar3 = puVar13;
      puVar13 = puVar13 + 1;
      *puVar3 = *puVar12;
    }
    iVar9 = 6;
    iVar10 = 0;
    cVar5 = *(char *)(unaff_BP + 0xe);
    do {
      if (cVar5 < *(char *)(iVar10 + iVar6 + 0xc0)) {
        pcVar1 = (char *)(iVar10 + iVar6 + 0xc0);
        *pcVar1 = *pcVar1 + -1;
      }
      iVar10 = iVar10 + 1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    if (cVar5 < *(char *)(iVar6 + 0xbf)) {
      *(char *)(iVar6 + 0xbf) = *(char *)(iVar6 + 0xbf) + -1;
    }
  }
  *(undefined1 *)(iVar6 + 0x52) = 0xff;
  *(undefined1 *)(iVar6 + 0x7a) = 0;
L_2500:
  ovl_01d3();
  return;
}


// ===== FAR_LISTSEL @ 2000:2506

void FAR_LISTSEL(void)

{
  undefined2 *puVar1;
  char cVar2;
  uint uVar3;
  undefined2 uVar4;
  int iVar5;
  undefined2 in_BX;
  int unaff_BP;
  int unaff_SI;
  int iVar6;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  if (*(int *)(unaff_BP + 0xc) != 0) {
    puVar1 = (undefined2 *)(G_savebx + 0x288);
    EXE_BreakPoint();
    puVar1 = (undefined2 *)(G_savebx + 0x58);
    EXE_SetMnuWnd(6,in_BX);
    puVar1 = (undefined2 *)(G_savebx + 0x468);
    EXE_ClrMnuWndX(in_BX);
    *(undefined2 *)(unaff_BP + -10) = 0;
    *(undefined2 *)(unaff_BP + -0xe) = 0;
    *(undefined2 *)(unaff_BP + -0x10) = 0;
    *(undefined2 *)(unaff_BP + -0x12) = 0;
    *(undefined2 *)(unaff_BP + -0x14) = 0;
    LOCK();
    uVar4 = G_scroll;
    G_scroll = 0;
    UNLOCK();
    *(undefined2 *)(unaff_BP + -6) = uVar4;
    *(uint *)(unaff_BP + -8) = G_mnuwh >> 3;
    *(undefined2 *)(unaff_BP + -0xc) = 0x101;
    *(undefined2 *)(unaff_BP + -0x18) = G_musregptr;
    G_musregptr = G_musregstartptr + 0x50;
    puVar1 = (undefined2 *)(G_savebx + 0x44c);
    EXE_SetMenuRegs(6,0xffff,in_BX);
    DAT_2000_1720 = G_mnuwx + -2;
    DAT_2000_1724 = G_mnuwx + G_mnuww;
    DAT_2000_1722 = G_mnuwy + -2;
    DAT_2000_1726 = DAT_2000_1722 + G_mnuwh + -6;
    DAT_2000_1733 = 0x11;
    ovl_2a45();
    do {
      if (*(char *)(unaff_BP + -0xb) == '\0') {
        ovl_29ee();
      }
      if (*(char *)(unaff_BP + -0xc) != '\0') {
        *(undefined2 *)(unaff_BP + -0xc) = 0;
        G_cursory = G_mnuwy;
        iVar5 = *(int *)(unaff_BP + -8);
        iVar6 = 0;
        do {
          G_cursorx = G_mnuwx;
          uVar3 = *(int *)(unaff_BP + -0x10) + iVar6;
          if (uVar3 < *(uint *)(unaff_BP + 0xc)) {
            EXE_slot0xe(uVar3,in_BX);
          }
          else {
            ovl_2a1a();
          }
          G_cursory = G_cursory + 8;
          iVar6 = iVar6 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        ovl_27be();
      }
      ovl_29ee();
      puVar1 = (undefined2 *)(G_savebx + 0x50);
      EXE_PageFlip();
      *(undefined2 *)(unaff_BP + -0x12) = *(undefined2 *)(unaff_BP + -0xe);
      *(undefined2 *)(unaff_BP + -0x14) = *(undefined2 *)(unaff_BP + -0x10);
      while( true ) {
        if (G_swsta == '\0') {
          puVar1 = (undefined2 *)(G_savebx + 0x314);
          EXE_Motion();
        }
        puVar1 = (undefined2 *)(G_savebx + 0x3f4);
        iVar5 = EXE_HandleMouse(0,0);
        if (iVar5 != 0) break;
        puVar1 = (undefined2 *)(G_savebx + 0x94);
        iVar5 = EXE_ReadKbd(0);
        if (iVar5 != 0) goto L_26ba;
        if (G_swsta == '\0') {
          puVar1 = (undefined2 *)(G_savebx + 0x3f8);
          EXE_HiPla();
        }
      }
      if (0x1a < iVar5) goto L_26cb;
      if (G_swsta == '\0') {
        puVar1 = (undefined2 *)(G_savebx + 0x3fc);
        EXE_HiEra();
      }
      uVar3 = (*(int *)(unaff_BP + -0x10) + iVar5) - 1;
      if ((int)uVar3 < *(int *)(unaff_BP + 0xc)) {
        ovl_29ee(uVar3);
        ovl_29ee();
        goto L_2737;
      }
L_26ba:
      if (G_swsta == '\0') {
        puVar1 = (undefined2 *)(G_savebx + 0x3fc);
        EXE_HiEra();
      }
L_26cb:
      puVar1 = (undefined2 *)(G_savebx + 0x400);
      uVar4 = EXE_NormKey(iVar5);
      *(undefined2 *)(unaff_BP + -0x16) = uVar4;
      if ((0x30 < (byte)uVar4) && ((byte)uVar4 < 0x3a)) {
        *(undefined1 *)(unaff_BP + -0x15) = 0;
        uVar4 = 0;
      }
      cVar2 = (char)uVar4;
      if (cVar2 == '\0') {
        ovl_27df();
      }
      else if (cVar2 == '\x1b') {
        *(undefined2 *)(unaff_BP + -10) = 0x101;
      }
      else if ((cVar2 == ' ') || (cVar2 == '\r')) {
        *(undefined1 *)(unaff_BP + -10) = 1;
        *(undefined1 *)(unaff_BP + -0x16) = (char)*(undefined2 *)(unaff_BP + -0xe);
      }
      else {
        ovl_276f();
      }
    } while (*(char *)(unaff_BP + -10) == '\0');
    if (*(char *)(unaff_BP + -9) == '\0') {
      uVar3 = (uint)*(byte *)(unaff_BP + -0x16);
    }
    else {
      uVar3 = 0xffff;
    }
L_2737:
    puVar1 = (undefined2 *)(G_savebx + 0x70);
    EXE_HideMouse(in_BX,uVar3);
    ovl_198a();
    G_scroll = *(undefined2 *)(unaff_BP + -6);
    puVar1 = (undefined2 *)(G_savebx + 0x468);
    EXE_ClrMnuWndX(in_BX);
    G_musregptr = *(undefined2 *)(unaff_BP + -0x18);
    puVar1 = (undefined2 *)(G_savebx + 0x450);
    EXE_UndoMenuRegs(in_BX);
  }
  ovl_01d3();
  return;
}


// ===== ovl_276f @ 2000:276f

void __cdecl16near ovl_276f(void)

{
  byte *pbVar1;
  byte in_AL;
  int iVar2;
  int unaff_BP;
  int unaff_SI;
  byte *pbVar3;
  uint uVar4;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar5;
  bool bVar6;
  
  if (in_AL < 0x41) {
    return;
  }
  if (0x5a < in_AL) {
    return;
  }
  pbVar3 = (byte *)(&G_listselletters+1 + *(int *)(unaff_BP + -0xe));
  iVar2 = (*(int *)(unaff_BP + 0xc) + -1) - *(int *)(unaff_BP + -0xe);
  bVar5 = iVar2 == 0;
  bVar6 = bVar5;
  if (iVar2 != 0) {
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      pbVar1 = pbVar3;
      pbVar3 = pbVar3 + 1;
      bVar5 = in_AL == *pbVar1;
    } while (!bVar5);
    bVar6 = false;
    if (bVar5) goto L_279d;
  }
  pbVar3 = (byte *)&G_listselletters;
  iVar2 = *(int *)(unaff_BP + 0xc);
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pbVar1 = pbVar3;
    pbVar3 = pbVar3 + 1;
    bVar6 = in_AL == *pbVar1;
  } while (!bVar6);
  if (!bVar6) {
    return;
  }
L_279d:
  *(undefined2 *)(unaff_BP + -0xe) = pbVar3 + (-1 - &G_listselletters);
  uVar4 = (int)(pbVar3 + (-1 - &G_listselletters)) - *(int *)(unaff_BP + -0x10);
  if (((int)uVar4 < 0) || (*(uint *)(unaff_BP + -8) <= uVar4)) {
    *(undefined2 *)(unaff_BP + -0x10) = *(undefined2 *)(unaff_BP + -0xe);
    *(undefined1 *)(unaff_BP + -0xc) = 1;
  }
  return;
}


// ===== ovl_27be @ 2000:27be

void ovl_27be(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x70);
  EXE_HideMouse();
  ovl_198a();
  return;
}


// ===== ovl_27df @ 2000:27df

void __cdecl16near ovl_27df(void)

{
  int iVar1;
  undefined2 *puVar2;
  undefined2 in_AX;
  char cVar5;
  int iVar3;
  uint uVar4;
  undefined2 in_BX;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  cVar5 = (char)((uint)in_AX >> 8);
  if (cVar5 == 'O') {
    *(undefined1 *)(unaff_BP + -0xc) = 1;
    iVar3 = *(int *)(unaff_BP + 0xc);
    *(int *)(unaff_BP + -0xe) = iVar3;
    *(int *)(unaff_BP + -0xe) = *(int *)(unaff_BP + -0xe) + -1;
    iVar3 = iVar3 - *(int *)(unaff_BP + -8);
    if (iVar3 < 0) {
      iVar3 = 0;
    }
    *(int *)(unaff_BP + -0x10) = iVar3;
    return;
  }
  if ((cVar5 == 'P') || (cVar5 == 'M')) {
    uVar4 = *(int *)(unaff_BP + -0xe) + 1;
    if (*(uint *)(unaff_BP + 0xc) <= uVar4) {
      return;
    }
    *(uint *)(unaff_BP + -0xe) = uVar4;
    if (uVar4 != *(int *)(unaff_BP + -0x10) + *(int *)(unaff_BP + -8)) {
      return;
    }
    *(int *)(unaff_BP + -0x10) = *(int *)(unaff_BP + -0x10) + 1;
    ovl_29ee();
    puVar2 = (undefined2 *)(G_savebx + 0x50);
    EXE_PageFlip(in_BX);
    puVar2 = (undefined2 *)(G_savebx + 0x70);
    EXE_HideMouse(in_BX);
    *(undefined2 *)(unaff_BP + -0x12) = *(undefined2 *)(unaff_BP + -0xe);
    *(undefined2 *)(unaff_BP + -0x14) = *(undefined2 *)(unaff_BP + -0x10);
    iVar3 = 8;
    do {
      puVar2 = (undefined2 *)(G_savebx + 0x284);
      EXE_ScrlUD(G_mnuwx,
                         G_mnuwy,
                         G_mnuwx + G_mnuww,
                         G_mnuwy + G_mnuwh + -1,in_BX);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    puVar2 = (undefined2 *)(G_savebx + 0x4c);
    EXE_CopyScreen(in_BX);
    puVar2 = (undefined2 *)(G_savebx + 0x220);
    EXE_ShowMouse(in_BX);
    G_cursory = G_mnuwy + G_mnuwh + -8;
  }
  else {
    if (cVar5 == 'Q') {
      if ((uint)(*(int *)(unaff_BP + 0xc) - *(int *)(unaff_BP + -0x10)) <= *(uint *)(unaff_BP + -8))
      {
        *(int *)(unaff_BP + -0xe) = *(int *)(unaff_BP + 0xc) + -1;
        return;
      }
      *(undefined1 *)(unaff_BP + -0xc) = 1;
      iVar3 = *(int *)(unaff_BP + -8);
      if ((uint)(*(int *)(unaff_BP + 0xc) - *(int *)(unaff_BP + -0x10)) <= iVar3 + 1U) {
        iVar1 = *(int *)(unaff_BP + 0xc);
        *(int *)(unaff_BP + -0xe) = iVar1 + -1;
        *(int *)(unaff_BP + -0x10) = iVar1 - iVar3;
        return;
      }
      *(int *)(unaff_BP + -0xe) = *(int *)(unaff_BP + -0xe) + iVar3;
      *(int *)(unaff_BP + -0x10) = *(int *)(unaff_BP + -0x10) + iVar3;
      if (*(uint *)(unaff_BP + 0xc) <= *(uint *)(unaff_BP + -0xe)) {
        iVar3 = *(uint *)(unaff_BP + 0xc) - 1;
        *(int *)(unaff_BP + -0xe) = iVar3;
        *(int *)(unaff_BP + -0x10) = (iVar3 - *(int *)(unaff_BP + -8)) + 1;
      }
      return;
    }
    if ((cVar5 != 'H') && (cVar5 != 'K')) {
      if (cVar5 == 'G') {
        if (*(int *)(unaff_BP + -0x10) != 0) {
          *(undefined1 *)(unaff_BP + -0xc) = 1;
        }
        *(undefined2 *)(unaff_BP + -0xe) = 0;
        *(undefined2 *)(unaff_BP + -0x10) = 0;
        return;
      }
      if (cVar5 == 'I') {
        if (*(int *)(unaff_BP + -0x10) == 0) {
          *(undefined2 *)(unaff_BP + -0xe) = 0;
          return;
        }
        *(undefined1 *)(unaff_BP + -0xc) = 1;
        uVar4 = *(uint *)(unaff_BP + -8);
        if (*(uint *)(unaff_BP + -0xe) < uVar4) {
          *(undefined2 *)(unaff_BP + -0xe) = 0;
          *(undefined2 *)(unaff_BP + -0x10) = 0;
          return;
        }
        *(int *)(unaff_BP + -0xe) = *(int *)(unaff_BP + -0xe) - uVar4;
        if (*(uint *)(unaff_BP + -0x10) <= uVar4) {
          *(undefined2 *)(unaff_BP + -0x10) = 0;
          return;
        }
        *(int *)(unaff_BP + -0x10) = *(int *)(unaff_BP + -0x10) - uVar4;
      }
      return;
    }
    uVar4 = *(int *)(unaff_BP + -0xe) - 1;
    if ((int)uVar4 < 0) {
      return;
    }
    *(uint *)(unaff_BP + -0xe) = uVar4;
    if (*(uint *)(unaff_BP + -0x10) <= uVar4) {
      return;
    }
    *(int *)(unaff_BP + -0x10) = *(int *)(unaff_BP + -0x10) + -1;
    ovl_29ee();
    puVar2 = (undefined2 *)(G_savebx + 0x50);
    EXE_PageFlip(in_BX);
    *(undefined2 *)(unaff_BP + -0x12) = *(undefined2 *)(unaff_BP + -0xe);
    *(undefined2 *)(unaff_BP + -0x14) = *(undefined2 *)(unaff_BP + -0x10);
    puVar2 = (undefined2 *)(G_savebx + 0x70);
    EXE_HideMouse(in_BX);
    iVar3 = 8;
    do {
      puVar2 = (undefined2 *)(G_savebx + 0x404);
      EXE_ScrlDD(G_mnuwx,
                         G_mnuwy,
                         G_mnuwx + G_mnuww,
                         G_mnuwy + G_mnuwh + -1,in_BX);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    puVar2 = (undefined2 *)(G_savebx + 0x4c);
    EXE_CopyScreen(in_BX);
    puVar2 = (undefined2 *)(G_savebx + 0x220);
    EXE_ShowMouse(in_BX);
    G_cursory = G_mnuwy;
  }
  G_cursorx = G_mnuwx;
  EXE_slot0xe(*(undefined2 *)(unaff_BP + -0xe),in_BX);
  ovl_29ee();
  ovl_27be();
  return;
}


// ===== ovl_29ee @ 2000:29ee

void __cdecl16near ovl_29ee(void)

{
  undefined2 *puVar1;
  int in_AX;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar2 = in_AX * 8 + G_mnuwy;
  puVar1 = (undefined2 *)(G_savebx + 0x45c);
  EXE_XorBlockX(G_mnuwx,iVar2,
                     G_mnuwx + G_mnuww,iVar2 + 8);
  return;
}


// ===== ovl_2a1a @ 2000:2a1a

void __cdecl16near ovl_2a1a(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x460);
  EXE_ClrAreaX(G_cursorx,G_cursory,
                     G_mnuwx + G_mnuww,
                     G_cursory + 8,G_txtbkgd);
  return;
}


// ===== ovl_2a45 @ 2000:2a45

void __cdecl16near ovl_2a45(void)

{
  undefined2 *puVar1;
  int iVar2;
  undefined2 in_BX;
  int unaff_BP;
  int unaff_SI;
  int iVar3;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  undefined2 uVar4;
  
  puVar1 = (undefined2 *)(G_savebx + 0x70);
  EXE_HideMouse();
  uVar4 = G_suppresstext;
  G_suppresstext = 1;
  iVar2 = *(int *)(unaff_BP + 0xc);
  iVar3 = 0;
  do {
    EXE_slot0xe(iVar3,in_BX);
    *(undefined1 *)(iVar3 + &G_listselletters) = G_firstletter;
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  G_suppresstext = uVar4;
  puVar1 = (undefined2 *)(G_savebx + 0x220);
  EXE_ShowMouse(in_BX);
  return;
}


// ===== FAR_ITEMSEL @ 2000:2a86

void FAR_ITEMSEL(void)

{
  undefined2 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  bool bVar5;
  int iVar6;
  
  iVar6 = *(int *)(*(int *)(unaff_BP + 0xc) * 2 + &G_heroptr);
  G_ISheroptr = iVar6;
  bVar5 = *(int *)(iVar6 + 0xcc) != 0;
  if (bVar5) {
    G_listsellist = 0;
  }
  uVar3 = (uint)bVar5;
  iVar2 = 0x28;
  iVar4 = 0;
  do {
    if (*(char *)(iVar4 + iVar6 + 0x53) != '\0') {
      *(int *)(uVar3 * 2 + &G_listsellist) = iVar4;
      uVar3 = (uVar3 & 0x7fff) + 1;
    }
    iVar4 = iVar4 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar6 = G_savebx;
  if (uVar3 == 0) {
    puVar1 = (undefined2 *)(G_savebx + 0x260);
    EXE_IComTxt(0x3d,iVar6);
  }
  else {
    puVar1 = (undefined2 *)(G_savebx + 0x174);
    iVar2 = EXE_ListSel(uVar3,*(undefined2 *)(iVar6 + 0x34c),
                               *(undefined2 *)(iVar6 + 0x34e),iVar6);
    if (iVar2 == -1) {
      puVar1 = (undefined2 *)(G_savebx + 0x5c);
      EXE_ClrTxtWnd(iVar6);
    }
  }
  ovl_01d3();
  return;
}


// ===== FAR_MEMSPLSEL @ 2000:2b12

void switchD_2000:44de::FAR_MEMSPLSEL(void)

{
  undefined2 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int iVar5;
  
  iVar5 = *(int *)(*(int *)(unaff_BP + 0xc) * 2 + &G_heroptr);
  G_ISheroptr = iVar5;
  uVar3 = 0;
  iVar2 = 0x2a;
  iVar4 = 0;
  do {
    if (*(char *)(iVar4 + iVar5 + 0x7b) != '\0') {
      *(int *)(uVar3 * 2 + &G_listsellist) = iVar4;
      uVar3 = (uVar3 & 0x7fff) + 1;
    }
    iVar4 = iVar4 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar5 = G_savebx;
  if (uVar3 != 0) {
    puVar1 = (undefined2 *)(G_savebx + 0x260);
    EXE_IComTxt(0x2b,iVar5,uVar3);
    puVar1 = (undefined2 *)(G_savebx + 0x174);
    EXE_ListSel(uVar3,*(undefined2 *)(iVar5 + 0x350),*(undefined2 *)(iVar5 + 0x352),
                       iVar5);
  }
  ovl_01d3();
  return;
}


// ===== FAR_WEAPSEL @ 2000:2b86

void FAR_WEAPSEL(void)

{
  byte bVar1;
  undefined2 *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int iVar6;
  
  iVar6 = *(int *)(*(int *)(unaff_BP + 0xc) * 2 + &G_heroptr);
  G_ISheroptr = iVar6;
  uVar4 = 0;
  iVar3 = 0x28;
  iVar5 = 0;
  do {
    bVar1 = *(byte *)(iVar5 + iVar6 + 0x2b);
    if ((8 < bVar1) && (bVar1 < 0x1f)) {
      *(int *)(uVar4 * 2 + &G_listsellist) = iVar5;
      uVar4 = (uVar4 & 0x7fff) + 1;
    }
    iVar5 = iVar5 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar6 = G_savebx;
  if (uVar4 != 0) {
    puVar2 = (undefined2 *)(G_savebx + 0x260);
    EXE_IComTxt(0x2b,iVar6,uVar4);
    puVar2 = (undefined2 *)(G_savebx + 0x174);
    EXE_ListSel(uVar4,*(undefined2 *)(iVar6 + 0x354),*(undefined2 *)(iVar6 + 0x356),
                       iVar6);
  }
  ovl_01d3();
  return;
}


// ===== ovl_2c1b @ 2000:2c1b

void ovl_2c1b(void)

{
  undefined2 *puVar1;
  int iVar2;
  int *piVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  piVar3 = (int *)((uint)G_lookdata + G_tdata+2);
  G_lookdata+1 = (char)*piVar3;
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap(G_tdata);
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap(G_comtxtptr);
  if (G_swcomb == '\0') {
    for (piVar3 = (int *)G_loc+12; (char)*piVar3 != '\0';
        piVar3 = (int *)((int)piVar3 + 3)) {
      if (*piVar3 == G_lookdata+2) {
        if ((*(byte *)(piVar3 + 1) & 0x80) != 0) {
          puVar1 = (undefined2 *)(G_savebx + 0xc0);
          iVar2 = EXE_IsItNPC(&G_wrkamt,piVar3,*(byte *)(piVar3 + 1) & 0x7f);
          if ((iVar2 == 0) || (G_wrkamt < 0x20)) break;
        }
        if (G_losresult != 0) {
          puVar1 = (undefined2 *)(G_savebx + 0xe8);
          EXE_AddScrap(G_loc+10);
          DAT_2000_2c03 = 2;
        }
        break;
      }
    }
  }
  if (G_lookprt != '\0') {
    puVar1 = (undefined2 *)(G_savebx + 0xec);
    EXE_PrtScrap(DAT_2000_2c03,piVar3);
  }
  G_lookprt = 1;
  ovl_01d3();
  return;
}


// ===== FAR_GREET @ 2000:2d06

void FAR_GREET(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar7;
  undefined4 uVar8;
  
  G_npcno = 0xff;
  puVar2 = (undefined2 *)(G_savebx + 0x1a4);
  iVar4 = EXE_Mark(&G_lookdata,10);
  if (iVar4 == -1) goto L_308b;
  G_zp_1415 = G_lookdata+2;
  puVar2 = (undefined2 *)(G_savebx + 0x138);
  uVar8 = EXE_IsItPla(&G_lookwho,in_BX);
  iVar4 = (int)((ulong)uVar8 >> 0x10);
  if ((int)uVar8 == 1) {
    G_npcptr = iVar4;
    if (iVar4 == G_curpla) {
      puVar2 = (undefined2 *)(G_savebx + 0x260);
      EXE_IComTxt(0xc,iVar4);
      goto L_308b;
    }
    puVar2 = (undefined2 *)(G_savebx + 0x1b4);
    EXE_RoomPgm(iVar4,iVar4);
    puVar2 = (undefined2 *)(G_savebx + 0xe8);
    EXE_AddScrap(G_comtxtptr);
    puVar2 = (undefined2 *)(G_savebx + 0xec);
    EXE_PrtScrap(3,iVar4);
    iVar4 = G_npcptr * 2;
    G_npcno = *(undefined2 *)(iVar4 + &G_party);
    G_npccat = 1;
    G_othername = *(undefined2 *)(iVar4 + &G_heroptr);
    G_othername+2 = unaff_DS;
    puVar2 = (undefined2 *)(G_savebx + 0x2b0);
    EXE_Tobo(G_npcno,iVar4);
  }
  else {
    puVar2 = (undefined2 *)(G_savebx + 0xc0);
    iVar5 = EXE_IsItNPC(&G_lookwho,iVar4);
    if (iVar5 == 0) {
      puVar2 = (undefined2 *)(G_savebx + 0x5c);
      EXE_ClrTxtWnd(iVar4);
      puVar2 = (undefined2 *)(G_savebx + 0xe4);
      EXE_InitScrap(iVar4);
      puVar2 = (undefined2 *)(G_savebx + 0xe8);
      EXE_AddScrap(G_comtxtptr);
      ovl_2c1b();
      return;
    }
    G_npcptr = iVar5;
    uVar1 = G_lookwho;
    G_npcno = uVar1;
    if ((((byte)uVar1 < 0xfa) &&
        (puVar2 = (undefined2 *)(G_savebx + 0x2b0),
        EXE_AddScrap(uVar1,iVar4), G_npcno < 0x20)) &&
       (puVar2 = (undefined2 *)(G_savebx + 0x29c),
       iVar5 = EXE_AddScrap(G_npcno,iVar4), iVar5 != 0)) {
      G_npccat = 4;
      puVar2 = (undefined2 *)(G_savebx + 0x438);
      EXE_AssSays(iVar4);
      ovl_2f7e();
      return;
    }
    if ((G_indisguise == 0) &&
       ((char)*(undefined2 *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0xbf) !=
        -1)) {
      puVar2 = (undefined2 *)(G_savebx + 0xd0);
      EXE_GameSound(0xe,iVar4);
      puVar2 = (undefined2 *)(G_savebx + 0x260);
      EXE_IComTxt(0x12,iVar4);
      goto L_308b;
    }
    if (G_npcno == -3) {
      G_swgreet = 0xfd;
      goto L_308b;
    }
    bVar7 = G_swgreet == '\x02';
    if (bVar7) {
      ovl_31bc();
      if (bVar7) {
        G_swgreet = 0xfe;
        goto L_308b;
      }
    }
    else if (G_swgreet != '\0') {
      G_swgreet = 0xff;
      goto L_308b;
    }
    if (G_npcno < 0xfa) {
      FAR_GREETKNPC();
      return;
    }
    G_deftxtparms+2 = G_loc+53;
    if ((byte)((char)*(undefined2 *)
                      (*(int *)(G_curpla * 2 + &G_heroptr) + 0x13) +
              G_tailorcharm) < G_loc+53) {
      ovl_308e();
      goto L_308b;
    }
    G_npccat = 5;
    puVar2 = (undefined2 *)(G_savebx + 0x104);
    EXE_UseMindstone(iVar4);
    if (G_loc+59 == -1) {
      puVar2 = (undefined2 *)(G_savebx + 0xe8);
      EXE_AddScrap(G_comtxtptr);
    }
    else {
      puVar2 = (undefined2 *)(G_savebx + 0xe8);
      EXE_AddScrap(G_loc+10);
    }
    puVar2 = (undefined2 *)(G_savebx + 0xec);
    EXE_PrtScrap(3,iVar4);
  }
L_2faf:
  do {
    puVar2 = (undefined2 *)(G_savebx + 0xb4);
    EXE_Menu(8,iVar4);
    puVar2 = (undefined2 *)(G_savebx + 0xb8);
    EXE_InitCom(0x2c0f,0x2000,9);
    do {
      while( true ) {
        while( true ) {
          while( true ) {
            puVar2 = (undefined2 *)(G_savebx + 0x48);
            uVar6 = EXE_Parser(&G_mnuparms,0);
            if (uVar6 == 0xffff) goto L_308b;
            if (uVar6 == 0xfd) {
              puVar2 = (undefined2 *)(G_savebx + 0x1b0);
              EXE_RestorP();
              goto L_2faf;
            }
            if (uVar6 < 2) {
              if (uVar6 != 1) {
                FAR_GREET();
                return;
              }
              puVar2 = (undefined2 *)(G_savebx + 0x31c);
              EXE_Talk();
              goto L_2faf;
            }
            if (3 < uVar6) break;
            if (uVar6 != 3) {
              puVar2 = (undefined2 *)(G_savebx + 0x424);
              EXE_Offer();
              goto L_2faf;
            }
            puVar2 = (undefined2 *)(G_savebx + 0x428);
            bVar3 = EXE_ToAssign();
            if (bVar3 != 0) goto joined_r0x00023054;
          }
          if (uVar6 < 6) break;
          if (uVar6 < 8) {
            puVar2 = (undefined2 *)(G_savebx + 0x434);
            EXE_BuySell(uVar6);
            goto L_2faf;
          }
          if (uVar6 == 8) goto L_308b;
        }
        if (uVar6 != 5) break;
        puVar2 = (undefined2 *)(G_savebx + 0x430);
        bVar3 = EXE_Dismiss();
        if (1 < bVar3) goto L_308b;
        if (bVar3 != 1) goto L_2faf;
      }
      puVar2 = (undefined2 *)(G_savebx + 0x42c);
      bVar3 = EXE_Invite();
    } while (bVar3 == 0);
joined_r0x00023054:
  } while (bVar3 < 2);
L_308b:
  ovl_01d3();
  return;
}


// ===== FAR_GREETKNPC @ 2000:2f52

void FAR_GREETKNPC(void)

{
  undefined2 *puVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_npccat = 3;
  puVar1 = (undefined2 *)(G_savebx + 0x11c);
  iVar3 = EXE_FindBit(&G_met,G_npcno);
  if (iVar3 == 0) {
    puVar1 = (undefined2 *)(G_savebx + 0x420);
    EXE_FirstMeet(in_BX);
  }
  else {
    puVar1 = (undefined2 *)(G_savebx + 0x41c);
    EXE_SecondMeet(in_BX);
  }
L_2faf:
  do {
    puVar1 = (undefined2 *)(G_savebx + 0xb4);
    EXE_Menu(8,in_BX);
    puVar1 = (undefined2 *)(G_savebx + 0xb8);
    EXE_InitCom(0x2c0f,0x2000,9);
    do {
      while( true ) {
        while( true ) {
          while( true ) {
            puVar1 = (undefined2 *)(G_savebx + 0x48);
            uVar4 = EXE_Parser(&G_mnuparms,0);
            if (uVar4 == 0xffff) goto L_308b;
            if (uVar4 == 0xfd) {
              puVar1 = (undefined2 *)(G_savebx + 0x1b0);
              EXE_RestorP();
              goto L_2faf;
            }
            if (uVar4 < 2) {
              if (uVar4 != 1) {
                FAR_GREET();
                return;
              }
              puVar1 = (undefined2 *)(G_savebx + 0x31c);
              EXE_Talk();
              goto L_2faf;
            }
            if (3 < uVar4) break;
            if (uVar4 != 3) {
              puVar1 = (undefined2 *)(G_savebx + 0x424);
              EXE_Offer();
              goto L_2faf;
            }
            puVar1 = (undefined2 *)(G_savebx + 0x428);
            bVar2 = EXE_ToAssign();
            if (bVar2 != 0) {
              if (bVar2 < 2) goto L_2faf;
              goto L_308b;
            }
          }
          if (uVar4 < 6) break;
          if (uVar4 < 8) {
            puVar1 = (undefined2 *)(G_savebx + 0x434);
            EXE_BuySell(uVar4);
            goto L_2faf;
          }
          if (uVar4 == 8) goto L_308b;
        }
        if (uVar4 != 5) break;
        puVar1 = (undefined2 *)(G_savebx + 0x430);
        bVar2 = EXE_Dismiss();
        if (1 < bVar2) goto L_308b;
        if (bVar2 != 1) goto L_2faf;
      }
      puVar1 = (undefined2 *)(G_savebx + 0x42c);
      bVar2 = EXE_Invite();
    } while (bVar2 == 0);
    if (1 < bVar2) {
L_308b:
      ovl_01d3();
      return;
    }
  } while( true );
}


// ===== ovl_2f7e @ 2000:2f7e

void ovl_2f7e(void)

{
  undefined2 *puVar1;
  byte bVar2;
  uint uVar3;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap(G_comtxtptr);
  puVar1 = (undefined2 *)(G_savebx + 0xec);
  EXE_PrtScrap(3,in_BX);
L_2faf:
  do {
    puVar1 = (undefined2 *)(G_savebx + 0xb4);
    EXE_Menu(8,in_BX);
    puVar1 = (undefined2 *)(G_savebx + 0xb8);
    EXE_InitCom(0x2c0f,0x2000,9);
    do {
      while( true ) {
        while( true ) {
          while( true ) {
            puVar1 = (undefined2 *)(G_savebx + 0x48);
            uVar3 = EXE_Parser(&G_mnuparms,0);
            if (uVar3 == 0xffff) goto L_308b;
            if (uVar3 == 0xfd) {
              puVar1 = (undefined2 *)(G_savebx + 0x1b0);
              EXE_RestorP();
              goto L_2faf;
            }
            if (uVar3 < 2) {
              if (uVar3 != 1) {
                FAR_GREET();
                return;
              }
              puVar1 = (undefined2 *)(G_savebx + 0x31c);
              EXE_Talk();
              goto L_2faf;
            }
            if (3 < uVar3) break;
            if (uVar3 != 3) {
              puVar1 = (undefined2 *)(G_savebx + 0x424);
              EXE_Offer();
              goto L_2faf;
            }
            puVar1 = (undefined2 *)(G_savebx + 0x428);
            bVar2 = EXE_ToAssign();
            if (bVar2 != 0) {
              if (bVar2 < 2) goto L_2faf;
              goto L_308b;
            }
          }
          if (uVar3 < 6) break;
          if (uVar3 < 8) {
            puVar1 = (undefined2 *)(G_savebx + 0x434);
            EXE_BuySell(uVar3);
            goto L_2faf;
          }
          if (uVar3 == 8) goto L_308b;
        }
        if (uVar3 != 5) break;
        puVar1 = (undefined2 *)(G_savebx + 0x430);
        bVar2 = EXE_Dismiss();
        if (1 < bVar2) goto L_308b;
        if (bVar2 != 1) goto L_2faf;
      }
      puVar1 = (undefined2 *)(G_savebx + 0x42c);
      bVar2 = EXE_Invite();
    } while (bVar2 == 0);
    if (1 < bVar2) {
L_308b:
      ovl_01d3();
      return;
    }
  } while( true );
}


// ===== ovl_308e @ 2000:308e

void __cdecl16near ovl_308e(void)

{
  undefined2 *puVar1;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_30cd();
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap(G_comtxtptr);
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap(G_comtxtptr);
  puVar1 = (undefined2 *)(G_savebx + 0xec);
  EXE_PrtScrap(1,in_BX);
  return;
}


// ===== ovl_30cd @ 2000:30cd

void __cdecl16near ovl_30cd(void)

{
  undefined2 *puVar1;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined4 uVar2;
  
  puVar1 = (undefined2 *)(G_savebx + 0x5c);
  EXE_ClrTxtWnd();
  puVar1 = (undefined2 *)(G_savebx + 0xe4);
  EXE_InitScrap(in_BX);
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  EXE_AddScrap(G_comtxtptr);
  G_npctyp = *(undefined1 *)(G_npcptr + 2);
  puVar1 = (undefined2 *)(G_savebx + 0xe8);
  uVar2 = EXE_AddScrap(G_comtypptr);
  G_othername = (int)uVar2;
  G_othername+2 = (int)((ulong)uVar2 >> 0x10);
  return;
}


// ===== FAR_ICANT @ 2000:3120

void FAR_ICANT(void)

{
  undefined2 *puVar1;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_3188();
  if (G_npcno == -0x5a) {
    puVar1 = (undefined2 *)(G_savebx + 0xe8);
    EXE_AddScrap(G_comtxtptr);
    if ((G_events+15 & 8) == 0) {
      puVar1 = (undefined2 *)(G_savebx + 0xe8);
      EXE_AddScrap(G_comtxtptr);
    }
  }
  else {
    puVar1 = (undefined2 *)(G_savebx + 0xe8);
    EXE_AddScrap(G_comtxtptr);
  }
  puVar1 = (undefined2 *)(G_savebx + 0xec);
  EXE_PrtScrap(3,in_BX);
  ovl_01d3();
  return;
}


// ===== ovl_3188 @ 2000:3188

void __cdecl16near ovl_3188(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_npccat == '\x01') {
    puVar1 = (undefined2 *)(G_savebx + 0x1b4);
    EXE_RoomPgm(G_npcptr);
    return;
  }
  if (G_npccat == '\x03') {
    puVar1 = (undefined2 *)(G_savebx + 0x244);
    EXE_Offer1();
    return;
  }
  puVar1 = (undefined2 *)(G_savebx + 0x104);
  EXE_UseMindstone();
  return;
}


// ===== ovl_31bc @ 2000:31bc

void __cdecl16near ovl_31bc(void)

{
  char *pcVar1;
  int iVar2;
  int unaff_SI;
  char *pcVar3;
  undefined2 unaff_DS;
  
  pcVar3 = (char *)G_loc+6;
  iVar2 = 0xff;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar1 = pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (*pcVar1 != '\0');
  iVar2 = CONCAT11((char)((uint)iVar2 >> 8),-((char)iVar2 + '\x01'));
  pcVar3 = pcVar3 + -iVar2;
  do {
    if (iVar2 == 0) {
      return;
    }
    iVar2 = iVar2 + -1;
    pcVar1 = pcVar3;
    pcVar3 = pcVar3 + 1;
  } while ((char)G_npcno != *pcVar1);
  return;
}


// ===== FAR_DISGUISE @ 2000:31db

void FAR_DISGUISE(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_indisguise = 1;
  ovl_01d3();
  return;
}


// ===== FAR_SHIELD @ 2000:31e5

void FAR_SHIELD(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_offense = 0;
  puVar1 = (undefined2 *)(G_savebx + 0x2b4);
  FAR_DISGUISE = EXE_GetMagSkl();
  if (G_curspl != 0x10) {
    FAR_DISGUISE = FAR_DISGUISE >> 3;
  }
  G_zp_16 = 9;
  G_offense = 0;
  ovl_3228();
  ovl_01d3();
  return;
}


// ===== FAR_ENERGY @ 2000:320e

void FAR_ENERGY(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_zp_16 = 0xc;
  G_offense = 0;
  ovl_3228();
  ovl_01d3();
  return;
}


// ===== FAR_HEAL @ 2000:3216

void FAR_HEAL(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_zp_16 = 10;
  G_offense = 0;
  ovl_3228();
  ovl_01d3();
  return;
}


// ===== ovl_3228 @ 2000:3228

void __cdecl16near ovl_3228(void)

{
  undefined1 uVar1;
  char cVar2;
  char cVar3;
  undefined2 *puVar4;
  uint uVar5;
  int iVar6;
  undefined2 uVar7;
  int iVar8;
  undefined1 extraout_DH;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  bool bVar9;
  
  puVar4 = (undefined2 *)(G_savebx + 0x208);
  uVar5 = EXE_SpelTarg();
  if (((bool)in_CF) || (0x17 < uVar5)) {
    return;
  }
  puVar4 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(10,in_BX);
  if ((G_swcomb == '\x01') || (G_curmpg != 1)) {
    uVar1 = G_zp_16;
    G_zp_1415 = G_rec2+1;
    if (G_targetof < 6) {
      in_BX = G_targetof;
      cVar2 = *(char *)(in_BX + &G_p1x);
      cVar3 = *(char *)(in_BX + &G_p1y);
      uVar7 = CONCAT11(cVar3,cVar2);
      if (G_swcomb == '\0') {
        uVar7 = CONCAT11(cVar3 - G_winy,cVar2 - G_winxy);
      }
      G_zp_1415 = uVar7;
    }
    puVar4 = (undefined2 *)(G_savebx + 0x360);
    EXE_Spef4(CONCAT11(extraout_DH,uVar1),G_targetof,in_BX)
    ;
  }
  if (G_targetof < 6) {
    iVar6 = *(int *)(G_targetof * 2 + &G_heroptr);
  }
  else {
    puVar4 = (undefined2 *)(G_savebx + 0x2d8);
    iVar6 = EXE_FillVillain(G_targetof,in_BX);
  }
  if ((*(byte *)(iVar6 + 0xbd) & 0x80) != 0) goto L_32cc;
  if ((G_curspl == 8) || (G_curspl == 0x14)) {
    if ('\x05' < G_targetof) {
      if ((G_rec2 & 1) != 0) {
        G_rec2 = G_rec2 & 0xfe;
        iVar6 = *(int *)((G_rec2+3 - 5) * 2 + &G_monsptr);
        G_rec2+19 = *(undefined1 *)(iVar6 + 7);
        G_rec2+20 = *(undefined1 *)(iVar6 + 8);
      }
      uVar7 = ovl_349a();
      G_rec2+10 = uVar7;
      puVar4 = (undefined2 *)(G_savebx + 0x40c);
      EXE_PutRec2(iVar6);
      puVar4 = (undefined2 *)(G_savebx + 0x410);
      EXE_GetRec1q(G_curpla,iVar6);
      goto L_3377;
    }
    puVar4 = (undefined2 *)(G_savebx + 0x414);
    iVar8 = EXE_UpHitptsHook(iVar6,iVar6);
joined_r0x00023372:
    if (iVar8 == 0) {
L_32cc:
      uVar7 = 0x95;
      goto L_33df;
    }
  }
  else {
    if (G_curspl == 0xc) {
      puVar4 = (undefined2 *)(G_savebx + 0x408);
      iVar8 = EXE_UpEnergyHook(iVar6,iVar6);
      goto joined_r0x00023372;
    }
    bVar9 = G_curspl < 0x1a;
    if (G_curspl != 0x1a) {
      ovl_33fd();
      if (!bVar9) goto L_3377;
      goto L_32cc;
    }
    ovl_3440();
    if (bVar9) goto L_32cc;
  }
L_3377:
  if (G_swcomb == '\x01') {
    puVar4 = (undefined2 *)(G_savebx + 0x40c);
    EXE_PutRec2(iVar6);
  }
  puVar4 = (undefined2 *)(G_savebx + 0x1d0);
  EXE_SetName(G_targetof,iVar6);
  iVar6 = G_targetof;
  if (iVar6 < 6) {
    iVar6 = iVar6 * 2;
    puVar4 = (undefined2 *)(G_savebx + 0xd4);
    EXE_IsHeTr(*(undefined2 *)(iVar6 + &G_heroptr),iVar6);
  }
  uVar7 = 0x5c;
  if (((G_curspl != 8) && (G_curspl != 0x14)) &&
     (uVar7 = 0x5d, G_curspl != 0xc)) {
    uVar7 = 0x5e;
    if (G_curspl != 0x10) {
      uVar7 = 0xcf;
    }
    G_deftxtparms+2 = FAR_DISGUISE;
  }
L_33df:
  puVar4 = (undefined2 *)(G_savebx + 0x260);
  EXE_IComTxt(uVar7,iVar6);
  puVar4 = (undefined2 *)(G_savebx + 0x338);
  EXE_AutoPause(G_UserDelay,iVar6);
  return;
}


// ===== ovl_3240 @ 2000:3240

void __cdecl16near ovl_3240(void)

{
  undefined1 uVar1;
  char cVar2;
  char cVar3;
  undefined2 *puVar4;
  int iVar5;
  undefined2 uVar6;
  int iVar7;
  undefined1 extraout_DH;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar8;
  
  puVar4 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(10);
  if ((G_swcomb == '\x01') || (G_curmpg != 1)) {
    uVar1 = G_zp_16;
    G_zp_1415 = G_rec2+1;
    if (G_targetof < 6) {
      in_BX = G_targetof;
      cVar2 = *(char *)(in_BX + &G_p1x);
      cVar3 = *(char *)(in_BX + &G_p1y);
      uVar6 = CONCAT11(cVar3,cVar2);
      if (G_swcomb == '\0') {
        uVar6 = CONCAT11(cVar3 - G_winy,cVar2 - G_winxy);
      }
      G_zp_1415 = uVar6;
    }
    puVar4 = (undefined2 *)(G_savebx + 0x360);
    EXE_Spef4(CONCAT11(extraout_DH,uVar1),G_targetof,in_BX)
    ;
  }
  if (G_targetof < 6) {
    iVar5 = *(int *)(G_targetof * 2 + &G_heroptr);
  }
  else {
    puVar4 = (undefined2 *)(G_savebx + 0x2d8);
    iVar5 = EXE_FillVillain(G_targetof,in_BX);
  }
  if ((*(byte *)(iVar5 + 0xbd) & 0x80) != 0) goto L_32cc;
  if ((G_curspl == 8) || (G_curspl == 0x14)) {
    if ('\x05' < G_targetof) {
      if ((G_rec2 & 1) != 0) {
        G_rec2 = G_rec2 & 0xfe;
        iVar5 = *(int *)((G_rec2+3 - 5) * 2 + &G_monsptr);
        G_rec2+19 = *(undefined1 *)(iVar5 + 7);
        G_rec2+20 = *(undefined1 *)(iVar5 + 8);
      }
      uVar6 = ovl_349a();
      G_rec2+10 = uVar6;
      puVar4 = (undefined2 *)(G_savebx + 0x40c);
      EXE_PutRec2(iVar5);
      puVar4 = (undefined2 *)(G_savebx + 0x410);
      EXE_GetRec1q(G_curpla,iVar5);
      goto L_3377;
    }
    puVar4 = (undefined2 *)(G_savebx + 0x414);
    iVar7 = EXE_UpHitptsHook(iVar5,iVar5);
joined_r0x00023372:
    if (iVar7 == 0) {
L_32cc:
      uVar6 = 0x95;
      goto L_33df;
    }
  }
  else {
    if (G_curspl == 0xc) {
      puVar4 = (undefined2 *)(G_savebx + 0x408);
      iVar7 = EXE_UpEnergyHook(iVar5,iVar5);
      goto joined_r0x00023372;
    }
    bVar8 = G_curspl < 0x1a;
    if (G_curspl != 0x1a) {
      ovl_33fd();
      if (!bVar8) goto L_3377;
      goto L_32cc;
    }
    ovl_3440();
    if (bVar8) goto L_32cc;
  }
L_3377:
  if (G_swcomb == '\x01') {
    puVar4 = (undefined2 *)(G_savebx + 0x40c);
    EXE_PutRec2(iVar5);
  }
  puVar4 = (undefined2 *)(G_savebx + 0x1d0);
  EXE_SetName(G_targetof,iVar5);
  iVar5 = G_targetof;
  if (iVar5 < 6) {
    iVar5 = iVar5 * 2;
    puVar4 = (undefined2 *)(G_savebx + 0xd4);
    EXE_IsHeTr(*(undefined2 *)(iVar5 + &G_heroptr),iVar5);
  }
  uVar6 = 0x5c;
  if (((G_curspl != 8) && (G_curspl != 0x14)) &&
     (uVar6 = 0x5d, G_curspl != 0xc)) {
    uVar6 = 0x5e;
    if (G_curspl != 0x10) {
      uVar6 = 0xcf;
    }
    G_deftxtparms+2 = FAR_DISGUISE;
  }
L_33df:
  puVar4 = (undefined2 *)(G_savebx + 0x260);
  EXE_IComTxt(uVar6,iVar5);
  puVar4 = (undefined2 *)(G_savebx + 0x338);
  EXE_AutoPause(G_UserDelay,iVar5);
  return;
}


// ===== ovl_33fd @ 2000:33fd

void __cdecl16near ovl_33fd(void)

{
  byte bVar1;
  undefined2 *puVar2;
  char cVar3;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  bVar1 = *(byte *)(in_BX + 0xbb);
  if (0x62 < bVar1) {
    return;
  }
  FAR_DISGUISE = FAR_DISGUISE + bVar1;
  if (FAR_DISGUISE < 100) {
    cVar3 = FAR_DISGUISE;
  }
  else {
    cVar3 = 'c' - bVar1;
    FAR_DISGUISE = 99;
  }
  puVar2 = (undefined2 *)(G_savebx + 0xdc);
  EXE_IncSta(G_targetof,0xbb,cVar3);
  return;
}


// ===== ovl_3440 @ 2000:3440

void __cdecl16near ovl_3440(void)

{
  undefined2 *puVar1;
  byte bVar2;
  uint uVar3;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  bVar2 = *(byte *)(in_BX + 0x13);
  if (0xb < bVar2) {
    return;
  }
  FAR_DISGUISE = FAR_DISGUISE + bVar2;
  if (FAR_DISGUISE < 0xd) {
    bVar2 = FAR_DISGUISE;
  }
  else {
    bVar2 = 0xc - bVar2;
    FAR_DISGUISE = 0xc;
  }
  uVar3 = (uint)bVar2;
  puVar1 = (undefined2 *)(G_savebx + 0xdc);
  EXE_IncSta(G_targetof,0x13,uVar3);
  puVar1 = (undefined2 *)(G_savebx + 0xdc);
  EXE_IncSta(G_targetof,0x2a,uVar3,in_BX);
  return;
}


// ===== ovl_349a @ 2000:349a

uint __cdecl16near ovl_349a(void)

{
  byte in_AL;
  int unaff_SI;
  undefined2 unaff_DS;
  
  while( true ) {
    if ((char)in_AL < '\x06') {
      return (uint)*(byte *)(*(int *)((uint)in_AL * 2 + &G_heroptr) + 0xa6);
    }
    if (in_AL != 0x16) break;
    in_AL = G_cloneno;
  }
  return *(uint *)*(undefined2 *)
                   ((*(byte *)(*(int *)((uint)in_AL * 2 + &G_crecptrs) + 3) - 5) * 2 +
                    &G_monsptr);
}


// ===== FAR_ZISHOXE @ 2000:34d4

void FAR_ZISHOXE(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar4;
  
  puVar2 = (undefined2 *)(G_savebx + 0x2b4);
  FAR_DISGUISE = EXE_GetMagSkl();
  FAR_DISGUISE = FAR_DISGUISE >> 1;
  G_zp_16 = 9;
  uVar1 = G_curspl;
  G_curspl = 0x10;
  puVar2 = (undefined2 *)(G_savebx + 0x5c);
  EXE_ClrTxtWnd(in_BX);
  puVar2 = (undefined2 *)(G_savebx + 0xe4);
  EXE_InitScrap(in_BX);
  G_targetof = 0;
  iVar3 = 6;
  uVar4 = 0;
  if (G_swcomb != '\0') {
    iVar3 = 0x18;
  }
  do {
    ovl_353e();
    if (!(bool)uVar4) {
      ovl_3240();
    }
    G_targetof = G_targetof + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  G_curspl = uVar1;
  ovl_01d3();
  return;
}


// ===== FAR_ZENGRL @ 2000:34ef

void FAR_ZENGRL(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 uVar4;
  
  G_zp_16 = 0xc;
  uVar1 = G_curspl;
  G_curspl = 0x14;
  puVar2 = (undefined2 *)(G_savebx + 0x5c);
  EXE_ClrTxtWnd();
  puVar2 = (undefined2 *)(G_savebx + 0xe4);
  EXE_InitScrap(in_BX);
  G_targetof = 0;
  iVar3 = 6;
  uVar4 = 0;
  if (G_swcomb != '\0') {
    iVar3 = 0x18;
  }
  do {
    ovl_353e();
    if (!(bool)uVar4) {
      ovl_3240();
    }
    G_targetof = G_targetof + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  G_curspl = uVar1;
  ovl_01d3();
  return;
}


// ===== ovl_353e @ 2000:353e

void __cdecl16near ovl_353e(void)

{
  undefined2 *puVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar2 = G_targetof * 2;
  if (G_swcomb == '\0') {
    if (G_locspec == 1) {
      puVar1 = (undefined2 *)(G_savebx + 0x39c);
      EXE_WaitForSound(iVar2);
    }
    if (*(int *)(iVar2 + &G_party) == 0xff) {
      return;
    }
    return;
  }
  iVar2 = *(int *)(iVar2 + &G_crecptrs);
  if ((*(byte *)(iVar2 + 5) & 0x98) != 0) {
    return;
  }
  if (*(char *)(iVar2 + 4) == '\0') {
    puVar1 = (undefined2 *)(G_savebx + 0x418);
    EXE_GetRec2q(*(undefined1 *)(iVar2 + 0x1f),iVar2,iVar2);
    return;
  }
  return;
}


// ===== FAR_SKILLUP @ 2000:35ae

void FAR_SKILLUP(void)

{
  undefined2 *puVar1;
  byte bVar2;
  int iVar3;
  undefined1 uVar5;
  uint uVar4;
  uint uVar6;
  int extraout_DX;
  int iVar7;
  undefined1 *puVar8;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar7 = G_wpnt;
  if (G_swcast != '\0') {
    iVar7 = CONCAT11((char)((uint)iVar7 >> 8),4);
  }
  if (iVar7 == 0) {
    iVar7 = 5;
  }
  G_zp_0A = (char)iVar7 + -1;
  if ((*(byte *)(iVar7 + 0x3728) & *(byte *)(G_curpla + &G_sklbits)) == 0)
  {
    iVar3 = G_zp_0A + 0x17;
    iVar7 = *(int *)(G_curpla * 2 + &G_heroptr);
    puVar8 = (undefined1 *)(iVar7 + iVar3);
    uVar5 = (undefined1)((uint)iVar3 >> 8);
    uVar4 = CONCAT11(uVar5,*puVar8);
    puVar1 = (undefined2 *)(G_savebx + 0x2ec);
    bVar2 = EXE_MaxSkill(iVar7,CONCAT11(uVar5,G_zp_0A),
                               puVar8,iVar7);
    if ((byte)uVar4 < bVar2) {
      uVar6 = 0;
      if (G_zp_0A < 5) {
        uVar6 = (uint)*(byte *)(extraout_DX + 0x372e);
      }
      if (uVar4 < 0x32) {
        uVar6 = (0x32 - uVar4 >> 2) + uVar6;
      }
      else {
        uVar4 = uVar4 - 0x32 >> 1;
        if (uVar6 < uVar4) {
          uVar6 = 1;
        }
        else {
          uVar6 = uVar6 - uVar4;
        }
      }
      puVar1 = (undefined2 *)(G_savebx + 0x134);
      iVar7 = extraout_DX;
      uVar4 = EXE_RndCo(100,extraout_DX);
      if ((uVar4 < uVar6) &&
         (puVar1 = (undefined2 *)(G_savebx + 0xdc),
         iVar3 = EXE_RndCo(G_curpla,
                                    G_zp_0A + '\x17',1,iVar7), iVar3 != 0)) {
        bVar2 = G_zp_0A;
        if (bVar2 < 5) {
          iVar7 = G_curpla;
          *(byte *)(iVar7 + &G_sklbits) =
               *(byte *)(iVar7 + &G_sklbits) | *(byte *)(bVar2 + 0x3729);
        }
        puVar1 = (undefined2 *)(G_savebx + 0x2e8);
        EXE_SetTxtSkill((uint)bVar2,iVar7);
        puVar1 = (undefined2 *)(G_savebx + 0xe4);
        EXE_InitScrap(iVar7);
        puVar1 = (undefined2 *)(G_savebx + 0x5c);
        EXE_ClrTxtWnd(iVar7);
        puVar1 = (undefined2 *)(G_savebx + 0xe8);
        EXE_AddScrap(G_comtxtptr);
        puVar1 = (undefined2 *)(G_savebx + 0xec);
        EXE_PrtScrap(3,iVar7);
        puVar1 = (undefined2 *)(G_savebx + 0xe4);
        EXE_InitScrap(iVar7);
        puVar1 = (undefined2 *)(G_savebx + 0xd0);
        EXE_GameSound(0xd,iVar7);
        puVar1 = (undefined2 *)(G_savebx + 0x39c);
        EXE_WaitForSound(iVar7);
        ovl_01d3();
        return;
      }
    }
  }
  ovl_01d3();
  return;
}


// ===== FAR_SKILLUP0 @ 2000:35d8

void FAR_SKILLUP0(void)

{
  undefined2 *puVar1;
  byte bVar2;
  int iVar3;
  undefined1 uVar5;
  uint uVar4;
  uint uVar6;
  int extraout_DX;
  undefined1 *puVar7;
  int iVar8;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar3 = G_zp_0A + 0x17;
  iVar8 = *(int *)(G_curpla * 2 + &G_heroptr);
  puVar7 = (undefined1 *)(iVar8 + iVar3);
  uVar5 = (undefined1)((uint)iVar3 >> 8);
  uVar4 = CONCAT11(uVar5,*puVar7);
  puVar1 = (undefined2 *)(G_savebx + 0x2ec);
  bVar2 = EXE_MaxSkill(iVar8,CONCAT11(uVar5,G_zp_0A),puVar7
                             ,iVar8);
  if ((byte)uVar4 < bVar2) {
    uVar6 = 0;
    if (G_zp_0A < 5) {
      uVar6 = (uint)*(byte *)(extraout_DX + 0x372e);
    }
    if (uVar4 < 0x32) {
      uVar6 = (0x32 - uVar4 >> 2) + uVar6;
    }
    else {
      uVar4 = uVar4 - 0x32 >> 1;
      if (uVar6 < uVar4) {
        uVar6 = 1;
      }
      else {
        uVar6 = uVar6 - uVar4;
      }
    }
    puVar1 = (undefined2 *)(G_savebx + 0x134);
    iVar8 = extraout_DX;
    uVar4 = EXE_RndCo(100,extraout_DX);
    if ((uVar4 < uVar6) &&
       (puVar1 = (undefined2 *)(G_savebx + 0xdc),
       iVar3 = EXE_RndCo(G_curpla,
                                  G_zp_0A + '\x17',1,iVar8), iVar3 != 0)) {
      bVar2 = G_zp_0A;
      if (bVar2 < 5) {
        iVar8 = G_curpla;
        *(byte *)(iVar8 + &G_sklbits) =
             *(byte *)(iVar8 + &G_sklbits) | *(byte *)(bVar2 + 0x3729);
      }
      puVar1 = (undefined2 *)(G_savebx + 0x2e8);
      EXE_SetTxtSkill((uint)bVar2,iVar8);
      puVar1 = (undefined2 *)(G_savebx + 0xe4);
      EXE_InitScrap(iVar8);
      puVar1 = (undefined2 *)(G_savebx + 0x5c);
      EXE_ClrTxtWnd(iVar8);
      puVar1 = (undefined2 *)(G_savebx + 0xe8);
      EXE_AddScrap(G_comtxtptr);
      puVar1 = (undefined2 *)(G_savebx + 0xec);
      EXE_PrtScrap(3,iVar8);
      puVar1 = (undefined2 *)(G_savebx + 0xe4);
      EXE_InitScrap(iVar8);
      puVar1 = (undefined2 *)(G_savebx + 0xd0);
      EXE_GameSound(0xd,iVar8);
      puVar1 = (undefined2 *)(G_savebx + 0x39c);
      EXE_WaitForSound(iVar8);
      ovl_01d3();
      return;
    }
  }
  ovl_01d3();
  return;
}


// ===== FAR_SPEF2 @ 2000:37a2

void FAR_SPEF2(void)

{
  undefined2 uVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar1 = G_zp_1415;
  G_zp_1415 = G_rec2+1;
  G_egadrawcode = 0;
  G_egaeffectstimer = 0x5dc;
  iVar2 = 3;
  do {
    ovl_3abe();
    ovl_3abe();
    ovl_3abe();
    ovl_3abe();
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  ovl_3abe();
  G_zp_1415 = uVar1;
  ovl_01d3();
  return;
}


// ===== FAR_SPEF3 @ 2000:3827

void FAR_SPEF3(void)

{
  undefined2 uVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar1 = G_zp_1415;
  G_zp_1415 = G_rec2+1;
  G_egadrawcode = 0;
  G_egaeffectstimer = 1000;
  ovl_3abe();
  ovl_3bdf(1);
  ovl_3abe();
  ovl_3bdf(1);
  ovl_3abe();
  ovl_3bdf(1);
  ovl_3abe();
  ovl_3bdf(1);
  ovl_3abe();
  G_zp_1415 = uVar1;
  ovl_01d3();
  return;
}


// ===== FAR_SPEF3SINGLE @ 2000:38c3

void FAR_SPEF3SINGLE(void)

{
  undefined2 uVar1;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar1 = G_zp_1415;
  G_zp_1415 = *(undefined2 *)(unaff_BP + 0xc);
  G_egadrawcode = 0;
  G_egaeffectstimer = 0x9c4;
  ovl_3abe();
  ovl_3abe();
  G_zp_1415 = uVar1;
  ovl_01d3();
  return;
}


// ===== FAR_SPEF4 @ 2000:3904

void FAR_SPEF4(void)

{
  undefined2 *puVar1;
  int iVar2;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int iVar3;
  
  G_egadrawcode = 0;
  G_egaeffectstimer = 1;
  iVar2 = 4;
  do {
    ovl_3abe();
    ovl_3bdf(3);
    if ((G_swcomb == '\0') ||
       (iVar3 = *(int *)(*(int *)(unaff_BP + 0xe) * 2 + &G_crecptrs),
       *(char *)(iVar3 + 0xe) == '\0')) {
      ovl_3abe();
    }
    else {
      puVar1 = (undefined2 *)(G_savebx + 0x120);
      EXE_RestBG(G_zp_1415 & 0xff,
                         G_zp_1415 >> 8,iVar3);
      puVar1 = (undefined2 *)(G_savebx + 0x50);
      EXE_PageFlip(iVar3);
    }
    ovl_3bdf(1);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  ovl_01d3();
  return;
}


// ===== FAR_SPEF5 @ 2000:398a

void FAR_SPEF5(void)

{
  undefined2 *puVar1;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(0xf);
  ovl_3b52(*(uint *)(unaff_BP + 0xc) & 0xff,*(uint *)(unaff_BP + 0xc) >> 8,0x3989,0x2000,3,1);
  ovl_01d3();
  return;
}


// ===== FAR_SPEF5_A @ 2000:39b9

void FAR_SPEF5_A(void)

{
  undefined2 *puVar1;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(10);
  ovl_3b52(*(uint *)(unaff_BP + 0xc) & 0xff,*(uint *)(unaff_BP + 0xc) >> 8,0x3989,0x2000,2,3);
  ovl_01d3();
  return;
}


// ===== FAR_SPEF6 @ 2000:39ee

void FAR_SPEF6(void)

{
  undefined2 *puVar1;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(0xb);
  ovl_3b52(*(uint *)(unaff_BP + 0xc) & 0xff,*(uint *)(unaff_BP + 0xc) >> 8,0x39ec,0x2000,2,2);
  ovl_01d3();
  return;
}


// ===== FAR_SPEF7 @ 2000:3a1d

void FAR_SPEF7(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x340);
  EXE_MFXInit();
  G_egadrawcode = 0;
  G_egaeffectstimer = 200;
  G_egaeffectssound = 0x10;
  G_egaeffectsflag = 7;
  iVar3 = 10;
  do {
    uVar4 = (uint)*(byte *)(unaff_BP + 0xe);
    G_mfxtnum = (uint)*(byte *)(uVar4 + &G_pltilno);
    uVar2 = ovl_3f59();
    G_mfxcoords = uVar2;
    G_mfxcnt = 2;
    if (G_egaeffectsflag+1 == *(char *)(unaff_BP + -6)) {
      G_egaeffectsflag+1 = G_egaeffectsflag+1 + '\x01';
    }
    puVar1 = (undefined2 *)(G_savebx + 0x2f8);
    EXE_movectileFX(0,0,0,uVar4);
    *(undefined1 *)(unaff_BP + -6) = G_egaeffectsflag+1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  G_egaeffectstimer = 1000;
  uVar2 = G_zp_1415;
  G_zp_1415 = *(undefined2 *)(unaff_BP + 0xc);
  ovl_3abe();
  G_zp_1415 = uVar2;
  ovl_01d3();
  return;
}


// ===== ovl_3abe @ 2000:3abe

void __cdecl16near ovl_3abe(void)

{
  undefined2 *puVar1;
  undefined2 in_AX;
  uint in_CX;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined4 uVar2;
  
  G_xorcolorcode = (char)in_AX;
  G_egaeffectsflag = CONCAT11((char)((uint)in_AX >> 8),(char)in_CX);
  uVar2 = ovl_3f59();
  puVar1 = (undefined2 *)(G_savebx + 0x2f8);
  EXE_movectileFX(in_CX >> 8,(char)uVar2,(char)((ulong)uVar2 >> 8),in_BX);
  return;
}


// ===== FAR_BANG @ 2000:3aee

void FAR_BANG(void)

{
  undefined2 *puVar1;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(3);
  ovl_3b52(*(undefined2 *)(unaff_BP + 0xc),*(undefined2 *)(unaff_BP + 0xe),
                *(int *)(unaff_BP + 0x10) + 0x3aec,0x2000,3,1);
  ovl_01d3();
  return;
}


// ===== FAR_ACIDBANG @ 2000:3b23

void FAR_ACIDBANG(void)

{
  undefined2 *puVar1;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(3);
  ovl_3b52(*(uint *)(unaff_BP + 0xc) & 0xff,*(uint *)(unaff_BP + 0xc) >> 8,0x3b21,0x2000,4,1);
  ovl_01d3();
  return;
}


// ===== ovl_3b52 @ 2000:3b52

void __cdecl16near
ovl_3b52(undefined2 param_1,undefined2 param_2,char *param_3,undefined2 param_4,
             undefined2 param_5,int param_6)

{
  undefined2 *puVar1;
  undefined2 in_BX;
  char *pcVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  char *pcVar3;
  
  G_workx = param_1;
  G_worky = param_2;
  puVar1 = (undefined2 *)(G_savebx + 0x388);
  EXE_EraMrk();
  puVar1 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip(in_BX);
  do {
    for (pcVar2 = param_3; *pcVar2 != '\0'; pcVar2 = pcVar2 + 1) {
      puVar1 = (undefined2 *)(G_savebx + 0x1cc);
      pcVar3 = pcVar2;
      EXE_OrTile(*pcVar2,param_1,param_2,pcVar2);
      puVar1 = (undefined2 *)(G_savebx + 0x50);
      EXE_PageFlip(pcVar3);
      puVar1 = (undefined2 *)(G_savebx + 0x388);
      EXE_EraMrk(pcVar3);
      ovl_3bdf(param_5);
    }
    param_6 = param_6 + -1;
  } while (param_6 != 0);
  puVar1 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip(pcVar2);
  return;
}


// ===== ovl_3bdf @ 2000:3bdf

void __cdecl16near ovl_3bdf(int param_1)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x310);
  EXE_delay(param_1 << 6);
  return;
}


// ===== FAR_INVERTWINDOW @ 2000:3bf8

void FAR_INVERTWINDOW(void)

{
  byte bVar1;
  undefined2 *puVar2;
  int iVar3;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  iVar3 = *(int *)(unaff_BP + 0xc) * 2;
  bVar1 = *(byte *)(iVar3 + 0x3750);
  *(uint *)(unaff_BP + -6) = (uint)bVar1;
  *(uint *)(unaff_BP + -10) = (uint)bVar1;
  bVar1 = *(byte *)(iVar3 + 0x3764);
  *(uint *)(unaff_BP + -8) = (uint)bVar1;
  *(uint *)(unaff_BP + -0xc) = (uint)bVar1;
  *(int *)(unaff_BP + -10) = *(int *)(unaff_BP + -10) + (uint)*(byte *)(iVar3 + 0x378c);
  *(int *)(unaff_BP + -0xc) = *(int *)(unaff_BP + -0xc) + (uint)*(byte *)(iVar3 + 0x3778);
  puVar2 = (undefined2 *)(G_savebx + 900);
  EXE_viaptr_puVar2(*(undefined2 *)(unaff_BP + -6),*(undefined2 *)(unaff_BP + -8),
                     *(undefined2 *)(unaff_BP + -10),*(undefined2 *)(unaff_BP + -0xc),iVar3);
  puVar2 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound(*(undefined2 *)(unaff_BP + 0xe),iVar3);
  puVar2 = (undefined2 *)(G_savebx + 0x39c);
  EXE_WaitForSound(iVar3);
  puVar2 = (undefined2 *)(G_savebx + 900);
  EXE_WaitForSound(*(undefined2 *)(unaff_BP + -6),*(undefined2 *)(unaff_BP + -8),
                     *(undefined2 *)(unaff_BP + -10),*(undefined2 *)(unaff_BP + -0xc),iVar3);
  ovl_01d3();
  return;
}


// ===== FAR_MULTIBANG @ 2000:3c7e

void FAR_MULTIBANG(void)

{
  int unaff_BP;
  undefined2 unaff_SS;
  
  ovl_3caa(0x3c7c,1,*(undefined2 *)(unaff_BP + 0xc));
  ovl_01d3();
  return;
}


// ===== FAR_MULTITHING @ 2000:3c93

void FAR_MULTITHING(void)

{
  int unaff_BP;
  undefined2 unaff_SS;
  
  ovl_3caa(0x3b21,5,*(undefined2 *)(unaff_BP + 0xc));
  ovl_01d3();
  return;
}


// ===== ovl_3caa @ 2000:3caa

void __cdecl16near ovl_3caa(int param_1,undefined2 param_2,undefined2 param_3)

{
  int *piVar1;
  char cVar2;
  undefined2 uVar3;
  undefined2 *puVar4;
  uint uVar5;
  int iVar6;
  int unaff_SI;
  undefined2 unaff_DS;
  
  while( true ) {
    _FAR_SPEF2 = 1;
    ovl_3caa = 1;
    iVar6 = 0;
    do {
      uVar5 = *(uint *)(iVar6 + &G_bangstg);
      if (uVar5 != 5) {
        _FAR_SPEF2 = 0;
        piVar1 = (int *)(iVar6 + &G_bangstg);
        *piVar1 = *piVar1 + 1;
        if (uVar5 == 0x20) {
          uVar5 = 4;
          *(undefined2 *)(iVar6 + &G_bangstg) = 5;
        }
        if (uVar5 == 0x1f) {
          uVar5 = 0;
        }
        if (uVar5 < 6) {
          if (*(uint *)(iVar6 + &G_bangstg) < 5) {
            ovl_3caa = 0;
          }
          uVar3 = *(undefined2 *)(iVar6 + &G_bangy);
          G_workx = *(undefined2 *)(iVar6 + &G_bangx);
          G_worky = uVar3;
          puVar4 = (undefined2 *)(G_savebx + 0x388);
          EXE_EraMrk(iVar6);
          cVar2 = *(char *)(uVar5 + param_1);
          if (cVar2 != '\0') {
            _FAR_SPEF2 = 0;
            puVar4 = (undefined2 *)(G_savebx + 0x1cc);
            EXE_OrTile(cVar2,G_workx,
                               G_worky,(char *)(uVar5 + param_1));
          }
        }
      }
      iVar6 = iVar6 + 2;
    } while (iVar6 < 399);
    puVar4 = (undefined2 *)(G_savebx + 0x50);
    EXE_PageFlip(iVar6);
    if (ovl_3caa != 1) {
      puVar4 = (undefined2 *)(G_savebx + 0xd0);
      EXE_GameSound(param_3,iVar6);
    }
    if (_FAR_SPEF2 == 1) break;
    ovl_3bdf(param_2);
  }
  puVar4 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip(iVar6);
  return;
}


// ===== FAR_BIGBANG @ 2000:3d91

void FAR_BIGBANG(void)

{
  undefined2 *puVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  iVar6 = 2;
  G_bangstg = 1;
  G_bangx = *(undefined2 *)(unaff_BP + 0xc);
  G_bangy = *(undefined2 *)(unaff_BP + 0xe);
  cVar3 = -1;
  do {
    cVar2 = -1;
    do {
      bVar4 = G_bangx + cVar2;
      bVar5 = G_bangy + cVar3;
      if ((bVar4 < 0xb) && (bVar5 < 9)) {
        *(uint *)(iVar6 + &G_bangx) = (uint)bVar4;
        *(uint *)(iVar6 + &G_bangy) = (uint)bVar5;
        *(undefined2 *)(iVar6 + &G_bangstg) = 0;
        iVar6 = iVar6 + 2;
      }
      cVar2 = cVar2 + '\x01';
    } while (cVar2 != '\x02');
    cVar3 = cVar3 + '\x01';
  } while (cVar3 != '\x02');
  puVar1 = (undefined2 *)(G_savebx + 0x2c4);
  EXE_MultiBang(3,iVar6);
  ovl_01d3();
  return;
}


// ===== FAR_BONG @ 2000:3df6

void FAR_BONG(void)

{
  char *pcVar1;
  undefined2 *puVar2;
  undefined2 in_BX;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  G_workx = *(undefined2 *)(unaff_BP + 0xc);
  G_worky = *(undefined2 *)(unaff_BP + 0xe);
  G_zp_13 = 1;
  DAT_2000_374d = 3;
  DAT_2000_374c = 5;
  DAT_2000_374e = 10;
  do {
    G_zp_12 = DAT_2000_374d;
    do {
      puVar2 = (undefined2 *)(G_savebx + 0x1cc);
      EXE_OrTile(G_zp_12,
                         G_workx,G_worky,in_BX
                        );
      puVar2 = (undefined2 *)(G_savebx + 0x50);
      EXE_PageFlip();
      puVar2 = (undefined2 *)(G_savebx + 0xd0);
      EXE_GameSound(DAT_2000_374e);
      puVar2 = (undefined2 *)(G_savebx + 0x388);
      EXE_EraMrk();
      G_zp_12 = G_zp_12 + '\x01';
    } while (G_zp_12 < DAT_2000_374c);
    pcVar1 = (char *)&G_zp_13;
    *pcVar1 = *pcVar1 + -1;
  } while (*pcVar1 != '\0');
  puVar2 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip(in_BX);
  ovl_01d3();
  return;
}


// ===== FAR_ZAP @ 2000:3e88

void FAR_ZAP(void)

{
  undefined1 uVar1;
  int iVar2;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar1 = (undefined1)*(undefined2 *)(unaff_BP + 0xc);
  G_zp_16 = uVar1;
  G_blastx+8 = uVar1;
  uVar1 = (undefined1)*(undefined2 *)(unaff_BP + 0xc);
  G_zp_17 = uVar1;
  G_blasty+8 = uVar1;
  G_zp_12 = 0x54;
  iVar2 = 4;
  do {
    ovl_3eb1();
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  ovl_01d3();
  return;
}


// ===== ovl_3eb1 @ 2000:3eb1

void ovl_3eb1(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  uint uVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_zp_13 = 0;
  do {
    G_zp_10 = G_zp_16;
    uVar3 = (uint)G_zp_13;
    puVar2 = (undefined2 *)(G_savebx + 0x118);
    EXE_SearSq(uVar3,uVar3);
    uVar1 = G_zp_10;
    *(undefined1 *)(uVar3 + &G_blastx) = (char)uVar1;
    *(undefined1 *)(uVar3 + &G_blasty) = (char)((uint)uVar1 >> 8);
    if ((G_zp_10 < 0xb) && (G_zp_11 < 9)) {
      puVar2 = (undefined2 *)(G_savebx + 0x1cc);
      EXE_OrTile(G_zp_12,uVar3);
      puVar2 = (undefined2 *)(G_savebx + 0x50);
      EXE_PageFlip(uVar3);
      puVar2 = (undefined2 *)(G_savebx + 0xd0);
      EXE_GameSound(3,uVar3);
      puVar2 = (undefined2 *)(G_savebx + 0x388);
      EXE_EraMrk(uVar3);
    }
    G_zp_13 = G_zp_13 + '\x01';
  } while (G_zp_13 < 8);
  ovl_01d3();
  return;
}


// ===== FAR_SPEF1 @ 2000:3f2f

void FAR_SPEF1(void)

{
  char *pcVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  undefined2 uVar4;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  uVar4 = *(undefined2 *)(unaff_BP + 0xc);
  uVar2 = *(undefined2 *)(unaff_BP + 0xe);
  G_workx = uVar4;
  G_worky = uVar2;
  G_zp_13 = 4;
  DAT_2000_374d = 0xd;
  DAT_2000_374c = 0xf;
  DAT_2000_374e = 10;
  do {
    G_zp_12 = DAT_2000_374d;
    do {
      puVar3 = (undefined2 *)(G_savebx + 0x1cc);
      EXE_OrTile(G_zp_12,
                         G_workx,G_worky,uVar4
                        );
      puVar3 = (undefined2 *)(G_savebx + 0x50);
      EXE_PageFlip();
      puVar3 = (undefined2 *)(G_savebx + 0xd0);
      EXE_GameSound(DAT_2000_374e);
      puVar3 = (undefined2 *)(G_savebx + 0x388);
      EXE_EraMrk();
      G_zp_12 = G_zp_12 + '\x01';
    } while (G_zp_12 < DAT_2000_374c);
    pcVar1 = (char *)&G_zp_13;
    *pcVar1 = *pcVar1 + -1;
  } while (*pcVar1 != '\0');
  puVar3 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip(uVar4);
  ovl_01d3();
  return;
}


// ===== ovl_3f59 @ 2000:3f59

undefined2 __cdecl16near ovl_3f59(void)

{
  char in_AL;
  char in_AH;
  
  return CONCAT11(in_AH * '\x10' + '\b',in_AL * '\x04' + '\x04');
}


// ===== FAR_LOADSOUNDS @ 2000:4131
// FAILED Low-level Error: Bad instruction count exceeded:
    ...
    No pcode could be generated at address: r0x0002769c
// ===== FAR_INITSOUNDS @ 2000:4342
// FAILED Low-level Error: Bad instruction count exceeded:
    ...
    No pcode could be generated at address: r0x0002ff2e
// ===== FAR_GAMESOUND @ 2000:4369
// FAILED Low-level Error: Bad instruction count exceeded:
    ...
    Instruction at (ram,0x00020c08) overlaps instruction at (ram,0x00020c06)

// ===== FAR_INT62_17 @ 2000:4428

void FAR_INT62_17(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_e_soundon == 0) {
    puVar1 = (undefined2 *)(G_savebx + 0x310);
    EXE_delay(1000);
    ovl_01d3();
    return;
  }
                    /* WARNING: Could not emulate address calculation at 0x00024449 */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)*(undefined2 *)((uint)G_e_soundboard * 2 + 0x4426))();
  return;
}


// ===== FAR_OFFSOUNDS @ 2000:449b

void FAR_OFFSOUNDS(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
                    /* WARNING: Could not emulate address calculation at 0x000244a3 */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)*(undefined2 *)((uint)G_e_soundboard * 2 + 0x4499))();
  return;
}


// ===== FAR_KILLSOUNDS @ 2000:44d1

/* WARNING: Control flow encountered bad instruction data */

void FAR_KILLSOUNDS(void)

{
  undefined2 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  int iVar5;
  
  switch(G_e_soundboard) {
  case 0:
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  case 1:
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  case 2:
    iVar5 = *(int *)(*(int *)(unaff_BP + 0xc) * 2 + &G_heroptr);
    G_ISheroptr = iVar5;
    uVar3 = 0;
    iVar2 = 0x2a;
    iVar4 = 0;
    break;
  default:
    G_e_soundboard = 0;
    ovl_01d3();
    return;
  }
  do {
    if (*(char *)(iVar4 + iVar5 + 0x7b) != '\0') {
      *(int *)(uVar3 * 2 + &G_listsellist) = iVar4;
      uVar3 = (uVar3 & 0x7fff) + 1;
    }
    iVar4 = iVar4 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar5 = G_savebx;
  if (uVar3 != 0) {
    puVar1 = (undefined2 *)(G_savebx + 0x260);
    EXE_IComTxt(0x2b,iVar5,uVar3);
    puVar1 = (undefined2 *)(G_savebx + 0x174);
    EXE_ListSel(uVar3,*(undefined2 *)(iVar5 + 0x350),*(undefined2 *)(iVar5 + 0x352),
                       iVar5);
  }
  ovl_01d3();
  return;
}


