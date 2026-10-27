// ===== ovl_0129 @ 1ca8:0129

int ovl_0129(void)

{
  return iRam000004f8 + -0x100;
}


// ===== ovl_0146 @ 1ca8:0146

void ovl_0146(void)

{
  char cVar1;
  uint uVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  int *piVar5;
  byte bVar6;
  undefined1 uVar7;
  int iVar8;
  int iVar9;
  uint in_BX;
  int unaff_SI;
  undefined2 *puVar10;
  undefined2 *puVar11;
  int unaff_DI;
  int *piVar12;
  undefined2 unaff_DS;
  bool bVar13;
  undefined2 uVar14;
  
  ovl_0129();
  G_winxy = 0;
  G_curseg = 0;
  G_swgreet = 0;
  G_curbfl = 0xff;
  G_lookprt = 1;
  bVar6 = G_rmdata;
  OV_0x16b = bVar6;
  G_currm = bVar6;
  if (bVar6 < 0x28) {
    EXE_LoadMap(0,0,0x47);
    if (G_curter != 0) {
      puVar11 = (undefined2 *)&G_thismap;
      puVar10 = (undefined2 *)((int)puVar11 + (uint)G_curter * 0x65);
      for (iVar8 = 0x32; iVar8 != 0; iVar8 = iVar8 + -1) {
        puVar4 = puVar11;
        puVar11 = puVar11 + 1;
        puVar3 = puVar10;
        puVar10 = puVar10 + 1;
        *puVar4 = *puVar3;
      }
      for (iVar8 = 1; iVar8 != 0; iVar8 = iVar8 + -1) {
        puVar4 = puVar11;
        puVar11 = (undefined2 *)((int)puVar11 + 1);
        puVar3 = puVar10;
        puVar10 = (undefined2 *)((int)puVar10 + 1);
        *(undefined1 *)puVar4 = *(undefined1 *)puVar3;
      }
    }
  }
  puVar11 = (undefined2 *)&G_thismap;
  puVar10 = (undefined2 *)&OV_0x106;
  for (iVar8 = 0x32; iVar8 != 0; iVar8 = iVar8 + -1) {
    puVar4 = puVar10;
    puVar10 = puVar10 + 1;
    puVar3 = puVar11;
    puVar11 = puVar11 + 1;
    *puVar4 = *puVar3;
  }
  *(undefined1 *)puVar10 = *(undefined1 *)puVar11;
  EXE_InitMap();
  EXE_InitNPC();
  ovl_050f();
  EXE_FixMusRegs();
  if (OV_0x16b < 0x28) {
    ovl_0441();
  }
L_01e8:
  do {
    EXE_InitMap();
    EXE_FillWindow(0,0);
L_01fa:
    do {
      do {
        EXE_Menu(5);
        EXE_InitCom(&OV_0x1c6,0x1000,0xe);
        do {
          while( true ) {
            do {
              while( true ) {
                while( true ) {
                  iVar8 = EXE_Parser(&G_mnuparms,0);
                  if (G_restarting != 0) {
                    return;
                  }
                  if (iVar8 == 0xfd) goto L_01e8;
                  if (iVar8 == 0xfe) goto L_01fa;
                  G_lookdata = 0xff;
                  if (iVar8 == 5) {
                    EXE_LoadOvly(0x5d,&OV_0x2100,0x1000);
                    EXE_RoomPgm();
                    EXE_Reload91();
                    goto L_01e8;
                  }
                  if (G_used == -1) break;
                  LOCK();
                  cVar1 = G_used;
                  G_used = -1;
                  UNLOCK();
                  if (cVar1 == '@') goto L_01e8;
                  G_used = cVar1;
                  EXE_NoUse();
                }
                if (G_whspnum == -1) break;
                uVar14 = 0xff;
                EXE_SetTxtWnd(1,in_BX,0x83,0xff);
                EXE_ClrTxtWnd();
                EXE_InitScrap();
                EXE_AddScrap(G_comtxtptr);
                EXE_PrtScrap(uVar14);
                G_whspnum = 0xff;
              }
            } while (G_curmen != '\x05');
            iVar8 = EXE_RMove(iVar8);
            if (iVar8 == 2) {
              uVar14 = 0xff;
              EXE_SetTxtWnd(1,in_BX,0x23,0xff);
              EXE_ClrTxtWnd();
              EXE_InitScrap();
              EXE_AddScrap(G_comtxtptr);
              EXE_PrtScrap(uVar14);
              iVar8 = EXE_SetYN();
              if (iVar8 == 0) {
                ovl_042a();
                EXE_ResLocD(in_BX);
                return;
              }
              goto L_01fa;
            }
            if (iVar8 == 0) break;
            if (iVar8 == 1) {
              EXE_GameSound(0xe);
            }
          }
          iVar8 = unaff_SI + G_curpla;
          bVar13 = iVar8 == 0;
          iVar8 = CONCAT11(*(undefined1 *)(iVar8 + 0x3e),*(undefined1 *)(iVar8 + 0x38));
          piVar12 = (int *)&OV_0x1a6;
          iVar9 = 0xf;
          do {
            if (iVar9 == 0) break;
            iVar9 = iVar9 + -1;
            piVar5 = piVar12;
            piVar12 = piVar12 + 1;
            bVar13 = iVar8 == *piVar5;
          } while (!bVar13);
        } while (!bVar13);
        OV_0x1d5 = iVar8;
        OV_0x1d7 = (0xe - iVar9) * 2;
        iVar8 = OV_0x16e;
        G_deftxtparms+2 = *(undefined1 *)(iVar8 + &OV_0x172);
        EXE_SetTxtObj(iVar8 + 0x33);
        ovl_04dd();
        uVar2 = 0x1000;
        iVar8 = EXE_SetYN(in_BX);
        in_BX = uVar2;
      } while (iVar8 != 0);
      LOCK();
      uVar2 = G_curpla;
      G_curpla = in_BX;
      UNLOCK();
      uVar14 = *(undefined2 *)(uVar2 * 2 + &G_heroptr);
      LOCK();
      in_BX = G_curpla;
      G_curpla = uVar2 & 0x7fff;
      UNLOCK();
      uVar7 = (undefined1)((uint)OV_0x16e >> 8);
      iVar8 = EXE_IncObj(uVar14,CONCAT11(uVar7,(char)OV_0x16e + '3')
                         ,CONCAT11(uVar7,G_deftxtparms+2));
    } while (iVar8 == 0);
    OV_0x170 = OV_0x170 + -1;
    iVar8 = OV_0x170 * 2;
    LOCK();
    puVar3 = (undefined2 *)(iVar8 + &OV_0x1a6);
    uVar14 = *puVar3;
    *puVar3 = 0xffff;
    UNLOCK();
    if (iVar8 != OV_0x1d7) {
      *(undefined2 *)(OV_0x1d7 + &OV_0x1a6) = uVar14;
    }
    if ((OV_0x16b & 1) == 0) {
      OV_0x16d = OV_0x16d + -0x10;
    }
    else {
      OV_0x16d = OV_0x16d + -1;
    }
    ovl_042a();
    ovl_04dd();
  } while( true );
}


// ===== ovl_042a @ 1ca8:042a

void ovl_042a(void)

{
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  *(undefined1 *)((OV_0x16b >> 1) + &G_mushsta) =
       OV_0x16d;
  return;
}


// ===== ovl_0441 @ 1ca8:0441

void ovl_0441(void)

{
  undefined2 *puVar1;
  byte bVar2;
  undefined2 uVar3;
  int iVar4;
  uint uVar5;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 *puVar6;
  undefined2 unaff_DS;
  
  puVar6 = (undefined2 *)&OV_0x1a6;
  for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar1 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar1 = 0xffff;
  }
  bVar2 = *(char *)(G_loc+18 + OV_0x16b) - 0x33;
  OV_0x16e = bVar2;
  OV_0x186 = *(undefined1 *)((uint)bVar2 + &OV_0x17c);
  uVar5 = OV_0x16b;
  bVar2 = *(byte *)(&G_mushsta + (uVar5 >> 1));
  OV_0x16d = bVar2;
  if ((OV_0x16b & 1) == 0) {
    bVar2 = bVar2 >> 4;
  }
  else {
    bVar2 = bVar2 & 0xf;
  }
  OV_0x170 = bVar2;
  uVar5 = CONCAT11((byte)(uVar5 >> 9),bVar2);
  if (bVar2 == 0) {
    EXE_SetTxtWnd(1);
    EXE_ClrTxtWnd();
    EXE_InitScrap();
    EXE_AddScrap(G_loc+10);
    EXE_PrtScrap(0xff,in_BX);
    return;
  }
  do {
    uVar3 = EXE_PlacePerson(*(undefined1 *)(uVar5 + &OV_0x187),
                       *(undefined1 *)(uVar5 + &OV_0x196));
    *(undefined2 *)(uVar5 * 2 + &OV_0x1a4) = uVar3;
    uVar5 = (uVar5 & 0x7fff) - 1;
  } while (uVar5 != 0);
  return;
}


// ===== ovl_050f @ 1ca8:050f

void ovl_050f(void)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  int iVar5;
  uint uVar6;
  int in_BX;
  uint uVar7;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_NewPXY();
  iVar5 = 6;
  uVar6 = 0;
  do {
    LOCK();
    puVar1 = (undefined1 *)(uVar6 + &G_p1x);
    uVar2 = *puVar1;
    *puVar1 = 0xff;
    UNLOCK();
    LOCK();
    puVar1 = (undefined1 *)(uVar6 + &G_p1y);
    uVar3 = *puVar1;
    *puVar1 = 0xff;
    UNLOCK();
    uVar7 = uVar6 & 0x7fff;
    if (*(int *)(uVar6 * 2 + &G_party) != 0xff) {
      uVar4 = EXE_PlacePerson(uVar2,uVar3);
      *(undefined1 *)(uVar7 + &G_p1x) = (char)uVar4;
      *(undefined1 *)(uVar7 + &G_p1y) = (char)((uint)uVar4 >> 8);
    }
    uVar6 = uVar7 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}


// ===== ovl_055a @ 1ca8:055a

void ovl_055a(void)

{
  uint uVar1;
  uint *puVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  int iVar3;
  undefined2 unaff_DS;
  undefined4 uVar4;
  int iVar5;
  
  ovl_0129();
  EXE_ClearShadowMap();
  puVar2 = (uint *)&OV_0x1a6;
  while ((char)*puVar2 != -1) {
    uVar1 = *puVar2 >> 8;
    uVar4 = ovl_05a9();
    iVar3 = (int)((ulong)G_oppscr >> 0x10);
    iVar5 = in_BX;
    EXE_movectile(OV_0x186,((int)uVar4 + 1) * 4,(uVar1 * 2 + 1) * 8,
               (int)G_oppscr,iVar3,in_BX,(int)((ulong)uVar4 >> 0x10));
    in_BX = iVar3;
    puVar2 = (uint *)(iVar5 + 2);
  }
  return;
}


// ===== ovl_05a9 @ 1ca8:05a9

undefined4 ovl_05a9(void)

{
  undefined2 in_AX;
  undefined2 in_DX;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_Locate();
  *(undefined1 *)(G_zp_0A + 0x1c68) = (char)OV_0x186;
  return CONCAT22(in_DX,in_AX);
}


