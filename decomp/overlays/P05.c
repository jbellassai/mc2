// ===== ovl_02fe @ 1ca8:02fe

int __cdecl16near ovl_02fe(void)

{
  int iVar1;
  undefined2 unaff_DS;
  
  iVar1 = iRam000004f8 + -0x100;
  *(undefined2 *)(*piRam000004fc + -0x728a) = piRam000004fc;
  return iVar1;
}


// ===== ovl_031f @ 1ca8:031f

void ovl_031f(void)

{
  undefined2 *puVar1;
  char *pcVar2;
  byte *pbVar3;
  undefined1 uVar4;
  code *pcVar5;
  byte bVar6;
  char cVar7;
  byte bVar8;
  uint uVar9;
  undefined1 extraout_AH;
  undefined2 uVar10;
  undefined1 extraout_AH_00;
  int iVar11;
  char cVar12;
  char *pcVar13;
  byte *pbVar14;
  int in_BX;
  int iVar15;
  int *piVar16;
  char *unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar17;
  int iStack0002;
  undefined2 uVar18;
  
  ovl_02fe();
  &G_winxy[0] = '\0';
  &G_winxy[1] = '\0';
  &G_curseg[0] = '\0';
  &G_curseg[1] = '\0';
  OV_0x10e = 0;
  OV_0x10f = 0;
  OV_0x11c = 0xff;
  &G_lookprt[0] = '\x01';
  &G_lookprt[1] = '\0';
  if ((unaff_SI[0x44] == '\x14') && (unaff_SI[0x2055] == '\t')) {
    OV_0x10e = 1;
  }
  iVar11 = 4;
  iVar15 = 0;
  do {
    *(undefined2 *)(iVar15 + &OV_0x106) = *(undefined2 *)(unaff_SI + iVar15 + 0x2055);
    iVar15 = iVar15 + 2;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  if (unaff_SI[0x205b] == '\0') {
    ovl_1315();
    ovl_19b0();
  }
  else {
    ovl_12bc();
    ovl_1a0d();
  }
  EXE_InitMap();
  EXE_NewLoc&G_loc+40;
  G_currm = (uint)OV_0x106;
  G_locspec = (uint)OV_0x10d;
  ovl_1a90();
  EXE_ProAss();
L_03b1:
  EXE_InitMap();
  ovl_1732();
  ovl_1b30();
L_03bc:
  do {
    EXE_Menu(5);
    EXE_InitCom(&OV_0x3e0,0x1000,0xe);
    ovl_1742();
L_03dd:
    ovl_171b();
    puVar1 = (undefined2 *)(in_BX + 0x48);
    in_BX = 0;
    uVar9 = EXE_viaptr_puVar1(0x1000,&G_mnuparms);
    if (G_restarting != 0) {
      unaff_SI[-0x7b68] = '\0';
      return;
    }
    if (uVar9 == 0xfd) goto L_03b1;
    if (uVar9 == 0xfe) goto L_03bc;
    unaff_SI[-0x7290] = -1;
    if (uVar9 != 6) {
      if (uVar9 == 5) {
        if ((((OV_0x10e != '\0') || (unaff_SI[-0x7b63] != '\x01')) ||
            (OV_0x10f == '\x01')) ||
           (((byte)unaff_SI[G_curpla + 0x3e] < 5 ||
            ((byte)unaff_SI[G_curpla + 0x38] < 4)))) {
          EXE_LoadOvly(0x5d,&OV_0x2100,0x1000);
          EXE_RoomPgm();
          EXE_Reload91();
          if ((unaff_SI[-0x7b63] == '\x01') && (OV_0x10f != '\x01')) {
            LOCK();
            iVar11 = G_currm;
            G_currm = in_BX;
            UNLOCK();
            cVar12 = unaff_SI[iVar11 + 0x200d];
            LOCK();
            in_BX = G_currm;
            G_currm = iVar11;
            UNLOCK();
            if (CONCAT11(extraout_AH,cVar12) == 0) {
              ovl_19b0();
              ovl_167f();
            }
          }
          goto L_03b1;
        }
        uVar18 = 0xff;
        EXE_SetTxtWnd(1,in_BX,0x24,0xff);
        EXE_ClrTxtWnd();
        EXE_InitScrap();
        EXE_AddScrap(G_comtxtptr);
        EXE_PrtScrap(uVar18);
        EXE_GameSound(0xe);
      }
      else {
        if (unaff_SI[-0x7b68] == -1) {
          unaff_SI[-0x7b68] = '\x01';
          cVar12 = unaff_SI[-0x7b63];
          if (cVar12 == '\x01') {
            iStack0002 = in_BX;
            EXE_UseMindstone();
            cVar12 = *(char *)((uint)OV_0x106 + &OV_0x343);
            cVar7 = unaff_SI[OV_0x106 + 0x200d];
            OV_0x88e = cVar12;
            OV_0x891 = cVar7;
            if (cVar7 == '\0') {
              unaff_SI[0x6a89] = cVar12;
              ovl_1b3e();
              EXE_PrtScrap(0xff);
              unaff_SI[0x6a89] = 'c';
              ovl_167f();
            }
            else {
              unaff_SI[0x6a89] = cVar7;
              ovl_1b3e();
              if (0x62 < OV_0x891) {
                in_BX = 0xff;
                EXE_PrtScrap();
                goto L_03bc;
              }
              ovl_1b3e();
              EXE_PrtScrap();
              unaff_SI[0x6a89] = 'c' - OV_0x891;
            }
            iVar11 = EXE_SetYN();
            if (iVar11 == 0) {
              EXE_UseMindstone();
              ovl_1b3e();
              EXE_PrtScrap();
              in_BX = 0x1000;
              uVar9 = EXE_GetNum();
              if (uVar9 == 0) {
                EXE_ClrTxtWnd();
                goto L_03bc;
              }
              OV_0x3ca = (char)uVar9;
              OV_0x88f = (uVar9 & 0xff) * (uint)OV_0x88e;
              if (*(uint *)(*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0xcc) <
                  OV_0x88f) {
                EXE_SetTxtWnd(1);
                EXE_ClrTxtWnd();
                EXE_InitScrap();
                EXE_AddScrap(G_comtxtptr);
                in_BX = -0x2cae;
                EXE_PrtScrap();
                goto L_03bc;
              }
              EXE_DecObj0();
              unaff_SI[OV_0x106 + 0x200d] =
                   unaff_SI[OV_0x106 + 0x200d] + OV_0x3ca;
              puVar1 = (undefined2 *)(iStack0002 + 0x104);
              iStack0002 = 0x1000;
              EXE_viaptr_puVar1();
            }
            else {
              EXE_UseMindstone();
            }
            ovl_1b3e();
            in_BX = -0x2d47;
            EXE_PrtScrap();
            goto L_03bc;
          }
          if (cVar12 == '\x02') {
L_0909:
            EXE_UseMindstone();
            iVar11 = -0x2c6b;
            ovl_1b3e();
            ovl_1b3e();
            if (OV_0x11c == -1) {
              uVar18 = *(undefined2 *)((uint)OV_0x106 * 2 + &OV_0x14d);
              OV_0x1c1 = uVar18;
              G_deftxtparms = uVar18;
              ovl_1b3e();
              ovl_1696();
              puVar1 = (undefined2 *)(in_BX + 0x108);
              in_BX = iVar11;
              iVar11 = EXE_viaptr_puVar1();
              if (iVar11 != 0) goto L_03bc;
              OV_0x1c5 =
                   (char)*(undefined2 *)
                          (*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 6);
              bVar6 = *(byte *)((uint)OV_0x106 + &OV_0x201);
              OV_0x1c3 = bVar6;
              iVar11 = (uint)bVar6 * 6;
              OV_0x3d0 =
                   CONCAT11((char)((uint)iVar11 >> 8),(char)iVar11 + OV_0x1c5);
              bVar6 = *(byte *)(*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) +
                                OV_0x1c3 + 0x17);
              LOCK();
              iVar11 = OV_0x3d0;
              OV_0x3d0 = in_BX;
              UNLOCK();
              bVar8 = *(byte *)(iVar11 + &OV_0x27f);
              LOCK();
              iVar15 = OV_0x3d0;
              OV_0x3d0 = iVar11;
              UNLOCK();
              if (bVar8 <= bVar6) {
                if (bVar6 == 0) {
                  EXE_UseMindstone();
                  ovl_1b3e();
                  in_BX = 0xff;
                  EXE_PrtScrap();
                }
                else {
                  EXE_UseMindstone();
                  in_BX = -0x2b93;
                  ovl_1b3e();
                  ovl_1b3e();
                  ovl_1b3e();
                  ovl_1b3e();
                  ovl_1b3e();
                  EXE_PrtScrap();
                }
                goto L_03bc;
              }
              OV_0x3d2 = 0;
              cVar12 = (char)*(undefined2 *)
                              (*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0x14);
              bVar6 = cVar12 - 4;
              if (bVar6 != 0 && '\x03' < cVar12) {
                OV_0x3d2 = bVar6 >> 1;
              }
              cVar12 = *(char *)((uint)OV_0x106 + &OV_0x1dd);
              cVar7 = cVar12 - OV_0x3d2;
              if (cVar7 == '\0' || cVar12 < OV_0x3d2) {
                cVar7 = '\x01';
              }
              unaff_SI[0x6a89] = cVar7;
              OV_0x3ca = cVar7;
              ovl_167f();
              in_BX = 0x1000;
              iVar11 = EXE_SetYN();
              if (iVar11 != 0) goto L_03bc;
              if (*(uint *)(*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0xcc) <
                  OV_0x1c1) {
                uVar18 = 0xff;
                EXE_SetTxtWnd(1,in_BX,0x25,0xff);
                EXE_ClrTxtWnd();
                EXE_InitScrap();
                EXE_AddScrap(G_comtxtptr);
                EXE_PrtScrap(uVar18);
                goto L_03bc;
              }
              EXE_DecObj0(0,OV_0x1c1);
              ovl_167f();
              uVar18 = G_curpla;
              OV_0x11c = (char)uVar18;
              OV_0x11e = 0;
              uVar4 = *(undefined1 *)
                       (CONCAT11((char)((uint)uVar18 >> 8),OV_0x1c3) + unaff_DI +
                       0x26d);
              iVar11 = *(int *)(unaff_SI + G_curpla * 2 + 0x2b26);
              *(char *)(iVar11 + 0xb9) = OV_0x1c3 + '\n';
              *(undefined1 *)(iVar11 + 0xd7) = uVar4;
              goto L_0b11;
            }
            ovl_1b3e();
            puVar1 = (undefined2 *)(in_BX + 0xec);
            in_BX = -0x2a37;
            EXE_viaptr_puVar1();
          }
          else if (cVar12 == '\x03') {
L_0b50:
            if (OV_0x11c == -1) {
              cVar12 = *(char *)((uint)OV_0x106 + &OV_0x307);
              OV_0xc4e = cVar12;
              OV_0x118 = cVar12 + 'Z';
              cVar12 = *(char *)(*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) +
                                (uint)(byte)(cVar12 + 0x24));
              OV_0x1c3 = cVar12;
              unaff_SI[0x6a89] = cVar12;
              EXE_UseMindstone();
              ovl_1b3e();
              if ((byte)*(undefined2 *)
                         (*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0xb8) < 2) {
                uVar18 = G_scrapptr;
                uVar10 = EXE_AddScrap(G_loc+10);
                G_scrapptr = uVar18;
                G_deftxtparms+4 = uVar10;
                if (OV_0x1c3 != '\0') {
                  EXE_AddScrap(G_loc+10);
                  ovl_1696();
                  iVar11 = EXE_SetYN();
                  if (iVar11 == 0) {
                    EXE_UseMindstone();
                    if (G_curpla != 0) {
                      EXE_AddScrap(G_loc+10);
                    }
                    ovl_1696();
                    iVar11 = G_curpla;
                    OV_0x11c = (char)iVar11;
                    iVar11 = *(int *)(unaff_SI + iVar11 * 2 + 0x2b26);
                    *(undefined1 *)(iVar11 + 0xb9) = OV_0x118;
                    *(undefined2 *)(iVar11 + 0xd7) =
                         CONCAT11(unaff_SI[4],OV_0x1c3);
                    *(undefined2 *)(iVar11 + 0xd9) =
                         CONCAT11(OV_0x106,unaff_SI[2]);
                    *(undefined1 *)(iVar11 + 0xdb) = 0;
                  }
                  else {
                    puVar1 = (undefined2 *)(in_BX + 0x5c);
                    in_BX = -0x294a;
                    EXE_viaptr_puVar1();
                  }
                  goto L_03bc;
                }
                ovl_1696();
              }
              else {
                ovl_1696();
              }
            }
            else {
              EXE_UseMindstone();
              ovl_1b3e();
              puVar1 = (undefined2 *)(in_BX + 0xec);
              in_BX = 0xff;
              EXE_viaptr_puVar1(0x1000);
            }
          }
          goto L_03dd;
        }
        if (unaff_SI[-0x7b68] == -3) {
          unaff_SI[-0x7b68] = '\0';
          bVar6 = unaff_SI[-0x7b63];
          uVar9 = (uint)bVar6;
          if (bVar6 == 2) goto L_0909;
          if (bVar6 == 3) goto L_0b50;
          if (bVar6 == 4) {
            iVar11 = OV_0x11c;
            if ((char)iVar11 != -1) {
              if (iVar11 == G_curpla) {
                ovl_167f();
              }
              else {
                EXE_UseMindstone();
                G_othername = *(undefined2 *)(unaff_SI + iVar11 * 2 + 0x2b26)
                ;
                G_othername+2 = unaff_DS;
                ovl_1696();
              }
              goto L_03bc;
            }
            EXE_ClrMnuWnd();
            EXE_UseMindstone();
            ovl_1b3e();
            EXE_PrtScrap(0xff);
            EXE_MyRet();
            puVar1 = (undefined2 *)(in_BX + 0x188);
            in_BX = 0x15;
            iVar11 = EXE_viaptr_puVar1(0x1000,&G_wrkstr);
            if (iVar11 == -1) goto L_03bc;
            uVar18 = EXE_WMatch(&G_wrkstr,G_loc+18);
            if ((char)uVar18 == -1) goto L_0d35;
            OV_0x11b = (char)uVar18;
            pcVar13 = (char *)(&OV_0x2f7 +
                              CONCAT11((char)((uint)uVar18 >> 8),
                                       (OV_0x106 + -0x7c) * '\x05'));
            bVar17 = pcVar13 == (char *)0x0;
            iVar11 = 5;
            break;
          }
          if (bVar6 == 5) {
            EXE_UseMindstone();
            if (G_curpla == 0) {
              ovl_1b3e();
              EXE_PrtScrap(0xff);
              iVar11 = EXE_SetYN();
              if (iVar11 == 0) {
                ovl_167f();
              }
              else {
                ovl_167f();
              }
            }
            else {
              ovl_1b3e();
              ovl_1696();
              puVar1 = (undefined2 *)(in_BX + 0x108);
              in_BX = -0x25cf;
              iVar11 = EXE_viaptr_puVar1();
              if (iVar11 == 0) {
                if ((char)*(undefined2 *)
                           (*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 6) ==
                    '\x01') {
                  if (OV_0x11e == -1) {
                    do {
                      ovl_167f();
                      G_scrap = G_loc+10;
                      G_scrap+2 = unaff_DS;
                      &G_scrap+4[0] = '\b';
                      &G_scrap+4[1] = '\t';
                      EXE_ScrMenu(2,&G_scrap+4);
                      unaff_SI[0x6b5c] = '\b';
                      puVar1 = (undefined2 *)(in_BX + 0xb8);
                      in_BX = 2;
                      EXE_viaptr_puVar1(0x1000,&OV_0x3ee,0x1000);
                      while( true ) {
                        iVar11 = EXE_Parser(&G_mnuparms,0);
                        if (iVar11 == -1) goto L_03bc;
                        if (iVar11 == 0xfd) break;
                        if (iVar11 == 0) {
                          ovl_167f();
                          iVar11 = ovl_1231();
                          if (iVar11 == 0) {
                            ovl_167f();
                            goto L_03bc;
                          }
                          puVar1 = (undefined2 *)(in_BX + 0x174);
                          in_BX = &OV_0x136a;
                          iVar11 = EXE_viaptr_puVar1(0x1000,iVar11);
                          if (iVar11 == -1) goto L_03bc;
                          OV_0x118 = unaff_SI[iVar11 + -0x74b2] + -0x2b;
                          goto L_11d2;
                        }
                        if (iVar11 == 1) goto L_10aa;
                      }
                      EXE_RestorP();
                    } while( true );
                  }
                  EXE_UseMindstone();
                  ovl_1b3e();
                  puVar1 = (undefined2 *)(in_BX + 0xec);
                  in_BX = 0xff;
                  EXE_viaptr_puVar1(0x1000);
                }
                else {
                  ovl_167f();
                }
              }
            }
            goto L_03bc;
          }
        }
        if (unaff_SI[-0x7b61] != -1) {
          LOCK();
          cVar12 = unaff_SI[-0x7b61];
          unaff_SI[-0x7b61] = -1;
          UNLOCK();
          if (cVar12 == '@') goto L_03b1;
          unaff_SI[-0x7b61] = cVar12;
          EXE_NoUse();
          goto L_03dd;
        }
        if (unaff_SI[-0x7b5f] != -1) {
          uVar18 = 0xff;
          EXE_SetTxtWnd(1,in_BX,0x83,0xff);
          EXE_ClrTxtWnd();
          EXE_InitScrap();
          EXE_AddScrap(G_comtxtptr);
          EXE_PrtScrap(uVar18);
          unaff_SI[-0x7b5f] = -1;
          goto L_03dd;
        }
        if (unaff_SI[0x6b5c] == '\x05') {
          iVar11 = EXE_RMove(uVar9);
          if (iVar11 == 2) {
            OV_0x3cb = G_loc+16;
L_068d:
            if ((*(char *)((uint)(byte)unaff_SI[-0x7b63] + &OV_0x1cd) == -1) ||
               (OV_0x11e != '\0')) {
              uVar18 = 0xff;
              EXE_SetTxtWnd(1,in_BX,0x23,0xff);
              EXE_ClrTxtWnd();
              EXE_InitScrap();
              EXE_AddScrap(G_comtxtptr);
              EXE_PrtScrap(uVar18);
              iVar11 = EXE_SetYN();
            }
            else {
              G_othername =
                   *(undefined2 *)(unaff_SI + OV_0x11c * 2 + 0x2b26);
              G_othername+2 = unaff_DS;
              ovl_167f();
              puVar1 = (undefined2 *)(in_BX + 0x108);
              in_BX = 0x1000;
              iVar11 = EXE_viaptr_puVar1();
            }
            if (iVar11 == 0) {
              iVar11 = 10;
              do {
                *(undefined1 *)(*(int *)(unaff_SI + iVar11 + 0x2b26) + 0xb9) = 0xff;
                iVar15 = iVar11 + -1;
                iVar11 = iVar11 + -2;
              } while (0 < iVar15);
              uVar18 = *(undefined2 *)
                        ((uint)*(byte *)(OV_0x3cb + 2) * 4 +
                        G_loc+14);
              bVar6 = (byte)uVar18;
              unaff_SI[0x4e] = bVar6;
              if (bVar6 < 3) {
                unaff_SI[0x4c] = -1;
              }
              unaff_SI[0x50] = (char)((uint)uVar18 >> 8);
              cVar12 = *(char *)(OV_0x3cb + 5);
              if (unaff_SI[0x4e] == '\x01') {
                cVar12 = -1;
              }
              G_pwinxy = *(undefined2 *)(OV_0x3cb + 3);
              unaff_SI[0x52] = cVar12;
              unaff_SI[-0x7b68] = '\0';
              return;
            }
            goto L_03bc;
          }
          if (iVar11 == 1) {
            if (((unaff_SI[-0x7b63] == '\x01') && (unaff_SI[-0x76d0] == '\b')) &&
               (unaff_SI[-0x76cf] == '\x04')) {
              ovl_16a5();
            }
            else {
              for (piVar16 = *(int **)&G_loc+16; (char)*piVar16 != -1;
                  piVar16 = piVar16 + 3) {
                if (G_zp_1415 == *piVar16) {
                  OV_0x3cb = piVar16;
                  goto L_068d;
                }
              }
              EXE_GameSound(0xe);
            }
          }
          else if (iVar11 != 0) goto L_03dd;
          if (unaff_SI[-0x7b69] != '\0') {
            EXE_ClrTxtWnd();
            unaff_SI[-0x7b69] = '\0';
          }
        }
      }
      goto L_03dd;
    }
    if (unaff_SI[-0x7b63] == '\x05') {
      ovl_0771();
      goto L_03dd;
    }
    if (OV_0x11e != '\0') {
      EXE_CalUpd();
      if (*unaff_SI == '\0') {
        ovl_17bd();
      }
      goto L_03dd;
    }
    EXE_Menu(0xf);
    EXE_InitCom(&OV_0x3ee,0x1000,1);
    do {
      EXE_CalUpd();
      ovl_171b();
      if (*unaff_SI == '\0') {
        ovl_17bd();
      }
      puVar1 = (undefined2 *)(in_BX + 0x94);
      in_BX = 0;
      iVar11 = EXE_viaptr_puVar1(0x1000);
    } while ((iVar11 == 0) && (OV_0x11e == '\0'));
  } while( true );
  while( true ) {
    iVar11 = iVar11 + -1;
    pcVar2 = pcVar13;
    pcVar13 = pcVar13 + 1;
    bVar17 = OV_0x11b == *pcVar2;
    if (bVar17) break;
    if (iVar11 == 0) break;
  }
  if (bVar17) {
    OV_0x1c7 = pcVar13 + (-1 - &OV_0x2f7);
    EXE_UseMindstone();
    ovl_1b3e();
    EXE_PrtScrap(0xff);
    puVar1 = (undefined2 *)(in_BX + 0x108);
    in_BX = 0x1000;
    iVar11 = EXE_viaptr_puVar1();
    if (iVar11 == 0) {
      bVar8 = (byte)*(undefined2 *)
                     (*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0x1f);
      OV_0x1c3 = bVar8;
      LOCK();
      iVar11 = OV_0x1c7;
      OV_0x1c7 = in_BX;
      UNLOCK();
      bVar6 = *(byte *)(iVar11 + &OV_0x30b);
      LOCK();
      in_BX = OV_0x1c7;
      OV_0x1c7 = iVar11;
      UNLOCK();
      if (bVar8 < bVar6) {
        ovl_167f();
      }
      else {
        LOCK();
        iVar11 = OV_0x1c7;
        OV_0x1c7 = in_BX;
        UNLOCK();
        cVar12 = *(char *)(iVar11 + unaff_DI + 799);
        cVar7 = *(char *)(iVar11 + &OV_0x333);
        LOCK();
        in_BX = OV_0x1c7;
        OV_0x1c7 = iVar11;
        UNLOCK();
        if (cVar12 == '\0') {
          uVar18 = (undefined2)((ulong)G_lvarbuf >> 0x10);
          OV_0x1c9 =
               *(undefined2 *)((int)G_lvarbuf + 5);
          OV_0x1cb = uVar18;
          iVar11 = ((byte)(100U - OV_0x1c3) >> 2) + 1;
          do {
            EXE_CalUpd();
            ovl_171b();
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
          ovl_167f();
          iVar15 = 0;
          EXE_PrtWrd(G_comtxtptr);
          LOCK();
          iVar11 = OV_0x1c7;
          OV_0x1c7 = iVar15;
          UNLOCK();
          bVar6 = *(byte *)(iVar11 + &OV_0x333);
          LOCK();
          in_BX = OV_0x1c7;
          OV_0x1c7 = iVar11;
          UNLOCK();
          pbVar14 = (byte *)&OV_0x38b;
          for (uVar9 = (uint)bVar6; uVar9 != 0; uVar9 = uVar9 - 1) {
            iVar11 = 0xff;
            do {
              if (iVar11 == 0) break;
              iVar11 = iVar11 + -1;
              pbVar3 = pbVar14;
              pbVar14 = pbVar14 + 1;
            } while (*pbVar3 != 0);
          }
          for (; *pbVar14 != 0; pbVar14 = pbVar14 + 1) {
            uVar9 = (uint)*pbVar14;
            EXE_ClrTxtWnd(in_BX,uVar9);
            EXE_InitScrap();
            EXE_AddScrap((int)OV_0x1c9,
                       (int)((ulong)OV_0x1c9 >> 0x10),uVar9);
            EXE_PrtScrap(1);
          }
        }
        else {
          OV_0x3ca = cVar12;
          OV_0x116 = cVar7 + '.';
          iVar11 = EXE_SearchInv(OV_0x116,
                              G_curpla,&OV_0x3d5,0x1000);
          if (iVar11 == 0) {
            EXE_SetTxtObj(OV_0x116);
            ovl_167f();
          }
          else {
            bVar6 = OV_0x1c3 >> 4;
            if (bVar6 < OV_0x3ca) {
              cVar12 = OV_0x3ca - bVar6;
            }
            else {
              cVar12 = '\x01';
            }
            OV_0x3ca = cVar12;
            unaff_SI[0x6a89] = cVar12;
            ovl_167f();
            puVar1 = (undefined2 *)(in_BX + 0x108);
            in_BX = 0x1000;
            iVar11 = EXE_viaptr_puVar1();
            if (iVar11 == 0) {
              LOCK();
              iVar11 = OV_0x1c7;
              OV_0x1c7 = in_BX;
              UNLOCK();
              cVar12 = *(char *)(iVar11 + &OV_0x333);
              LOCK();
              in_BX = OV_0x1c7;
              OV_0x1c7 = iVar11;
              UNLOCK();
              OV_0x118 = cVar12;
              EXE_SetTxtObj(cVar12 + '.');
              ovl_167f();
              iVar11 = *(int *)(unaff_SI + G_curpla * 2 + 0x2b26);
              cVar12 = OV_0x118;
              *(char *)(iVar11 + 0xb9) = cVar12;
              *(undefined2 *)(iVar11 + 0xd7) = CONCAT11(extraout_AH_00,cVar12 + '.');
L_0b11:
              *(undefined1 *)(iVar11 + 0xd8) = (char)*(undefined2 *)(unaff_SI + 4);
              *(undefined1 *)(iVar11 + 0xd9) = (char)*(undefined2 *)(unaff_SI + 2);
              *(undefined1 *)(iVar11 + 0xda) = OV_0x106;
              *(undefined1 *)(iVar11 + 0xdb) = OV_0x3ca;
            }
          }
        }
      }
    }
  }
  else {
L_0d35:
    EXE_UseMindstone();
    ovl_1b3e();
    puVar1 = (undefined2 *)(in_BX + 0xec);
    in_BX = 0xff;
    EXE_viaptr_puVar1(0x1000);
  }
  goto L_03bc;
L_10aa:
  ovl_167f();
  EXE_SetTxtObj(0);
  G_scrap = G_deftxtparms+4;
  G_scrap+2 = unaff_DS;
  pcVar5 = INT_0x60_handler;
  uVar18 = (*pcVar5)();
  EXE_ScrMenu(uVar18);
  unaff_SI[0x6b5c] = '\b';
  puVar1 = (undefined2 *)(in_BX + 0xb8);
  in_BX = &OV_0x3ee;
  EXE_viaptr_puVar1(0x1000);
  do {
    uVar9 = EXE_Parser(&G_mnuparms,0);
    if (uVar9 == 0xffff) goto L_03bc;
    if (uVar9 == 0xfd) goto code_r0x0001dba2;
  } while (6 < uVar9);
  bVar6 = *(byte *)((uint)OV_0x106 + &OV_0x2c7);
  cVar12 = '(';
  while (bVar17 = (bool)(bVar6 & 1), bVar6 = bVar6 >> 1, !bVar17) {
    cVar12 = cVar12 + '\x01';
  }
  for (; uVar9 != 0; uVar9 = uVar9 - 1) {
    do {
      cVar12 = cVar12 + '\x01';
      bVar17 = (bool)(bVar6 & 1);
      bVar6 = bVar6 >> 1;
    } while (!bVar17);
  }
  OV_0x118 = cVar12;
  ovl_167f();
  puVar1 = (undefined2 *)(in_BX + 0x108);
  in_BX = 0x1000;
  iVar11 = EXE_viaptr_puVar1();
  if (iVar11 == 0) {
    if (199 < *(uint *)(*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0xcc)) {
      EXE_DecObj0(0,200);
L_11d2:
      EXE_SetTxtWnd(1);
      EXE_ClrTxtWnd();
      EXE_InitScrap();
      ovl_1b3e();
      if (G_curpla != 0) {
        ovl_1b3e();
      }
      puVar1 = (undefined2 *)(in_BX + 0xec);
      in_BX = 0xff;
      EXE_viaptr_puVar1(0x1000);
      OV_0x3ca = 7;
      iVar11 = *(int *)(unaff_SI + G_curpla * 2 + 0x2b26);
      *(undefined1 *)(iVar11 + 0xb9) = OV_0x118;
      *(undefined2 *)(iVar11 + 0xd6) = G_juldate;
      goto L_0b11;
    }
    uVar18 = 0xff;
    EXE_SetTxtWnd(1,in_BX,0x25,0xff);
    EXE_ClrTxtWnd();
    EXE_InitScrap();
    EXE_AddScrap(G_comtxtptr);
    EXE_PrtScrap(uVar18);
  }
  goto L_03bc;
code_r0x0001dba2:
  EXE_RestorP();
  goto L_10aa;
}


// ===== ovl_0771 @ 1ca8:0771

void ovl_0771(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_ClrTxtWnd(0x1ca8);
  EXE_InitScrap(0x1ca8);
  ovl_1b3e();
  EXE_PrtScrap(0x1ca8,0xff);
  return;
}


// ===== ovl_1231 @ 1ca8:1231

int ovl_1231(void)

{
  char *pcVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int unaff_SI;
  char *pcVar7;
  undefined2 unaff_DS;
  bool bVar8;
  
  iVar2 = *(int *)(G_curpla * 2 + &G_heroptr);
  cVar3 = 'S';
  iVar4 = 7;
  iVar6 = 0;
  bVar8 = true;
  do {
    iVar5 = 0x28;
    pcVar7 = (char *)(iVar2 + 0x2b);
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      pcVar1 = pcVar7;
      pcVar7 = pcVar7 + 1;
      bVar8 = cVar3 == *pcVar1;
    } while (!bVar8);
    if (bVar8) {
      *(char *)(iVar6 + &G_scrap2+12) = cVar3;
      iVar6 = iVar6 + 1;
    }
    cVar3 = cVar3 + '\x01';
    bVar8 = cVar3 == '\0';
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
      return iVar6;
    }
  } while( true );
}


// ===== FUN_1000_dcea @ 1000:dcea

void __cdecl16far FUN_1000_dcea(int param_1)

{
  undefined2 uVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_02fe();
  uVar1 = G_scroll;
  G_scroll = 0;
  LOCK();
  UNLOCK();
  LOCK();
  UNLOCK();
  EXE_SetTxtObj(0x1ca8,*(undefined1 *)(param_1 + &G_scrap2+12));
  EXE_PrtWrdX(0x1ca8,&OV_0x3dd,0x1ca8,0);
  EXE_Pad(0x1ca8,in_BX);
  G_scroll = uVar1;
  return;
}


// ===== ovl_12bc @ 1ca8:12bc

void ovl_12bc(void)

{
  int *piVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  int unaff_SI;
  undefined2 *puVar6;
  int unaff_DI;
  undefined2 *puVar7;
  undefined2 unaff_DS;
  
  G_rmtyp = 0;
  OV_0x3cd = 0;
  puVar6 = (undefined2 *)*(undefined2 *)((G_rmdata + 1) * 2 + &G_loc)
  ;
  puVar7 = (undefined2 *)&G_loc;
  for (iVar4 = 0x9e3; iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar3 = puVar7;
    puVar7 = puVar7 + 1;
    puVar2 = puVar6;
    puVar6 = puVar6 + 1;
    *puVar3 = *puVar2;
  }
  for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
    puVar3 = puVar7;
    puVar7 = (undefined2 *)((int)puVar7 + 1);
    puVar2 = puVar6;
    puVar6 = (undefined2 *)((int)puVar6 + 1);
    *(undefined1 *)puVar3 = *(undefined1 *)puVar2;
  }
  iVar4 = 0x14;
  iVar5 = 0;
  do {
    piVar1 = (int *)(iVar5 + &G_loc);
    *piVar1 = *piVar1 + &G_loc;
    iVar5 = iVar5 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  OV_0x3cf =
       (char)((uint)*(undefined2 *)G_loc+8 >> 8);
  ovl_1af6();
  return;
}


// ===== ovl_1315 @ 1ca8:1315

void ovl_1315(void)

{
  code *pcVar1;
  byte bVar2;
  undefined2 extraout_DX;
  undefined2 extraout_DX_00;
  undefined2 extraout_DX_01;
  byte bVar3;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar4 = 0;
  bVar2 = OV_0x106;
  while (*(byte *)(iVar4 + &OV_0x3ba) <= bVar2) {
    iVar4 = iVar4 + 1;
  }
  bVar3 = (byte)iVar4;
  G_rmtyp = bVar3;
  OV_0x3cd = bVar2 - *(char *)(iVar4 + &OV_0x3b9);
  if ((bVar3 == 2) && (0x5b < OV_0x106)) {
    G_rmtyp = 1;
    OV_0x3cd = OV_0x3cd + -0x14;
    OV_0x10f = 1;
  }
  if ((bVar3 != 0) && (bVar3 < 4)) {
    G_swgreet = 1;
  }
  if (OV_0x106 == -0x7c) {
    pcVar1 = INT_0x60_handler;
    (*pcVar1)();
  }
  if (OV_0x10f != '\0') {
    bVar2 = (byte)(0x80 >> (OV_0x3cd & 7));
    if (OV_0x3cd < 8) {
      G_beenflg+1 = G_beenflg+1 | bVar2;
    }
    else {
      *(byte *)(unaff_SI + 100) = *(byte *)(unaff_SI + 100) | bVar2;
    }
  }
  OV_0x3cf =
       *(undefined1 *)(G_loc+8 + OV_0x3cd + 1);
  ovl_1af6();
  ovl_16fa();
  G_loc+16 = extraout_DX;
  ovl_16fa();
  G_loc+2 = extraout_DX_00;
  ovl_16fa();
  G_loc+4 = extraout_DX_01;
  if (G_rmtyp == '\x02') {
    ovl_1ad5();
  }
  else if (G_rmtyp == '\x03') {
    ovl_1ad5();
  }
  return;
}


// ===== ovl_1411 @ 1ca8:1411

void ovl_1411(void)

{
  ovl_02fe();
  ovl_141f();
  return;
}


// ===== ovl_141f @ 1ca8:141f

void ovl_141f(int param_1)

{
  undefined2 *puVar1;
  int iVar2;
  int in_BX;
  int unaff_BP;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  EXE_Offer1(0x1ca8);
  if (*(char *)(unaff_BP + 6) == '\x06') {
    while( true ) {
      param_1 = in_BX;
      ovl_156a();
      if (0xe < G_armcnt) {
        ovl_1696();
        return;
      }
      ovl_1696();
      iVar2 = EXE_ListSel(OV_0x150f,&OV_0x172c);
      if (iVar2 == -1) break;
      OV_0x116 = *(undefined1 *)(iVar2 + &OV_0x1507);
      iVar2 = EXE_IncObj(*(undefined2 *)(G_curpla * 2 + &G_heroptr),
                         OV_0x116);
      if (iVar2 == 0) {
        return;
      }
      G_armcnt = G_armcnt + '\x01';
      if (0xe < G_armcnt) break;
      EXE_Offer1();
      ovl_1696();
      puVar1 = (undefined2 *)(param_1 + 0x108);
      param_1 = 0x1000;
      iVar2 = EXE_viaptr_puVar1();
      if (iVar2 != 0) break;
      in_BX = -0x20be;
      EXE_slot0x1244();
    }
  }
  else {
    if ((G_armcnt == '\0') ||
       (ovl_15b7(), OV_0x150f == 0)) {
      ovl_1696();
      return;
    }
    ovl_1696();
    iVar2 = EXE_ListSel(OV_0x150f,&OV_0x172c,0x1000);
    if (iVar2 != -1) {
      OV_0x116 = *(undefined1 *)(iVar2 + &OV_0x1507);
      iVar2 = EXE_SearchInv(OV_0x116,G_curpla,
                         &OV_0x3d5);
      if (iVar2 == 0) {
        EXE_SetTxtObj();
        ovl_167f();
        return;
      }
      EXE_DecObj0(OV_0x116);
      G_armcnt = G_armcnt + -1;
    }
  }
  EXE_Offer1();
  ovl_1696();
  return;
}


// ===== ovl_156a @ 1ca8:156a

void ovl_156a(void)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar4 = 0;
  OV_0x150f = 0;
  iVar3 = 8;
  do {
    bVar2 = *(byte *)(iVar4 + &OV_0x14ff);
    if (bVar2 < 0x28) {
      if (0x1e < bVar2) {
        EXE_SrchArm();
      }
    }
    else {
      EXE_SrchHelm();
    }
    LOCK();
    iVar1 = OV_0x150f;
    OV_0x150f = in_BX;
    UNLOCK();
    *(byte *)(iVar1 + &OV_0x1507) = bVar2;
    LOCK();
    in_BX = OV_0x150f;
    OV_0x150f = iVar1 + 1;
    UNLOCK();
    iVar4 = iVar4 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}


// ===== ovl_15b7 @ 1ca8:15b7

void ovl_15b7(void)

{
  char *pcVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar7;
  
  iVar5 = 0;
  OV_0x150f = 0;
  iVar4 = 8;
  do {
    uVar2 = *(undefined1 *)(iVar5 + &OV_0x14ff);
    iVar3 = EXE_SearchInv(uVar2,G_curpla,&OV_0x3d5,0x1000);
    if (iVar3 != 0) {
      pcVar6 = (char *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0xc0);
      bVar7 = pcVar6 == (char *)0x0;
      iVar3 = 6;
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        pcVar1 = pcVar6;
        pcVar6 = pcVar6 + 1;
        bVar7 = (char)OV_0x3d7 == *pcVar1;
      } while (!bVar7);
      if (!bVar7) {
        LOCK();
        iVar3 = OV_0x150f;
        OV_0x150f = in_BX;
        UNLOCK();
        *(undefined1 *)(iVar3 + &OV_0x1507) = uVar2;
        LOCK();
        in_BX = OV_0x150f;
        OV_0x150f = iVar3 + 1;
        UNLOCK();
      }
    }
    iVar5 = iVar5 + 1;
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
      return;
    }
  } while( true );
}


// ===== FUN_1000_e0ac @ 1000:e0ac

void __cdecl16far FUN_1000_e0ac(int param_1)

{
  undefined2 uVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_02fe();
  uVar1 = G_scroll;
  G_scroll = 0;
  LOCK();
  UNLOCK();
  LOCK();
  UNLOCK();
  EXE_SetTxtObj(*(undefined1 *)(param_1 + &OV_0x1507));
  EXE_PrtWrdX(&OV_0x3dd,0x1000,0);
  EXE_Pad(in_BX);
  G_scroll = uVar1;
  return;
}


// ===== ovl_167f @ 1ca8:167f

void ovl_167f(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(0x1ca8,1);
  EXE_ClrTxtWnd(0x1ca8);
  EXE_InitScrap(0x1ca8);
  ovl_1b3e();
  EXE_PrtScrap(0x1ca8,0xff);
  return;
}


// ===== ovl_16a5 @ 1ca8:16a5

void ovl_16a5(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 uVar1;
  undefined2 unaff_DS;
  
  uVar1 = 0x1ca8;
  if ((*(byte *)(G_curpla + &G_p1y) < 5) ||
     (uVar1 = 0x1000,
     *(char *)(CONCAT11((char)((uint)G_curpla >> 8),
                        OV_0x106) + &G_member6+6765) != '\0')) {
    ovl_19b0();
    EXE_InitMap(uVar1);
    EXE_FillWindow(uVar1,0,0);
    return;
  }
  G_npcptr = G_loc+2;
  G_npccat = 5;
  EXE_UseMindstone();
  ovl_1b3e();
  EXE_PrtScrap(0xff);
  return;
}


// ===== ovl_16fa @ 1ca8:16fa

void ovl_16fa(void)

{
  char *pcVar1;
  int iVar2;
  char *in_DX;
  int iVar3;
  int unaff_DI;
  undefined2 unaff_DS;
  
  iVar3 = OV_0x3cd;
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


// ===== ovl_171b @ 1ca8:171b

void ovl_171b(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (*(int *)(unaff_SI + 2) != OV_0x110) {
    ovl_1732();
    EXE_InitMap();
    ovl_1b30();
  }
  return;
}


// ===== ovl_1732 @ 1ca8:1732

void ovl_1732(void)

{
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_InitNPC(0x1ca8);
  OV_0x110 = *(undefined2 *)(unaff_SI + 2);
  return;
}


// ===== ovl_1742 @ 1ca8:1742

void ovl_1742(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int *piVar5;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x11e = 0xff;
  iVar2 = 0x1f;
  pcVar4 = (char *)&G_assgn0;
  while ((((*pcVar4 == -1 || (pcVar4[5] == '\b')) ||
          ((uint)(byte)pcVar4[1] != G_locspec)) ||
         ((uint)(byte)pcVar4[2] != G_currm))) {
    pcVar4 = pcVar4 + 0x19;
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) {
      iVar3 = 6;
      piVar5 = (int *)&G_party;
      iVar2 = G_heroptr;
      cVar1 = '\0';
      while ((*piVar5 == 0xff || (*(char *)(iVar2 + 0xb9) == -1))) {
        cVar1 = cVar1 + '\x01';
        piVar5 = piVar5 + 1;
        iVar2 = iVar2 + 0xdc;
        iVar3 = iVar3 + -1;
        if (iVar3 == 0) {
          return;
        }
      }
      OV_0x11c = cVar1;
      OV_0x11e = 0;
      return;
    }
  }
  OV_0x11c = *pcVar4;
  OV_0x11e = 1;
  return;
}


// ===== ovl_17bd @ 1ca8:17bd

void ovl_17bd(void)

{
  char *pcVar1;
  byte *pbVar2;
  int *piVar3;
  byte *pbVar4;
  byte bVar5;
  int iVar6;
  undefined1 *puVar7;
  int in_BX;
  int iVar8;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  int in_stack_00000000;
  undefined2 uVar9;
  int iVar10;
  
  OV_0x112 = 5;
  do {
    iVar6 = OV_0x112 * 2;
    if (*(int *)(iVar6 + &G_party) != 0xff) {
      iVar6 = *(int *)(iVar6 + &G_heroptr);
      if (*(char *)(iVar6 + 0xb9) != -1) {
        OV_0x118 = *(char *)(iVar6 + 0xb9);
        G_othername = iVar6;
        G_othername+2 = unaff_DS;
        if (((char)*(undefined2 *)(iVar6 + 0xd8) != *(char *)(unaff_SI + 4)) &&
           ((char)((uint)*(undefined2 *)(iVar6 + 0xd8) >> 8) == *(char *)(unaff_SI + 2))) {
          OV_0x3ca = (char)((uint)*(undefined2 *)(iVar6 + 0xda) >> 8);
          if (OV_0x118 < 0x5a) {
            if (OV_0x3ca != '\0') {
              pcVar1 = (char *)&OV_0x3ca;
              *pcVar1 = *pcVar1 + -1;
              if (*pcVar1 != '\0') goto L_198d;
            }
            EXE_SetTxtWnd(1);
            EXE_ClrTxtWnd();
            EXE_InitScrap();
            if (G_rmtyp == '\x02') {
              ovl_1b3e();
              ovl_1b3e();
              G_deftxtparms+2 =
                   (char)*(undefined2 *)
                          (*(int *)(OV_0x11c * 2 + &G_heroptr) + 0xd7);
              ovl_1b3e();
              iVar6 = 0xff;
              iVar8 = 0x1000;
              uVar9 = 0xe307;
              EXE_PrtScrap();
              *(undefined1 *)(iVar8 + 0xb9) = 0xff;
              puVar7 = (undefined1 *)
                       (iVar8 + CONCAT11((char)((uint)OV_0x118 >> 8),
                                         (char)OV_0x118 + '\r'));
              OV_0x3d0 = puVar7;
              OV_0x1c3 = *puVar7;
              bVar5 = (char)*(undefined2 *)
                             (*(int *)(OV_0x11c * 2 + &G_heroptr) + 0xd7) +
                      OV_0x1c3;
              if (99 < bVar5) {
                bVar5 = 99;
              }
              LOCK();
              pbVar4 = (byte *)OV_0x3d0;
              OV_0x3d0 = uVar9;
              UNLOCK();
              *pbVar4 = bVar5;
              in_BX = OV_0x3d0;
            }
            else {
              iVar6 = in_stack_00000000;
              if (G_rmtyp == '\x04') {
                uVar9 = G_curpla;
                G_curpla = OV_0x112;
                iVar6 = in_BX;
                EXE_SetTxtObj(OV_0x118 + 0x2e,in_BX,uVar9);
                ovl_167f();
                G_curpla = in_stack_00000000;
                iVar8 = *(int *)(OV_0x112 * 2 + &G_heroptr);
                OV_0x114 = iVar8;
                *(undefined1 *)(iVar8 + 0xb9) = 0xff;
                iVar10 = 0x1000;
                EXE_SearchInv(OV_0x118 + 0x2e,
                           OV_0x112,&OV_0x3d5);
                LOCK();
                iVar8 = OV_0x114;
                OV_0x114 = iVar10;
                UNLOCK();
                iVar8 = iVar8 + OV_0x3d7;
                pbVar2 = (byte *)(iVar8 + 0x53);
                *pbVar2 = *pbVar2 | 0x80;
                LOCK();
                in_BX = OV_0x114;
                OV_0x114 = iVar8;
                UNLOCK();
              }
            }
            OV_0x11e = 0xff;
            OV_0x11c = 0xff;
            in_stack_00000000 = iVar6;
          }
          else {
            OV_0x3ca = OV_0x3ca + '\x01';
            if (OV_0x118 < 0x5e) {
              iVar6 = *(int *)(OV_0x11c * 2 + &G_heroptr);
              EXE_IncObj(iVar6,0,*(uint *)(iVar6 + 0xd7) & 0xff);
            }
          }
L_198d:
          *(undefined1 *)(*(int *)(OV_0x112 * 2 + &G_heroptr) + 0xdb) =
               OV_0x3ca;
        }
      }
    }
    piVar3 = (int *)&OV_0x112;
    *piVar3 = *piVar3 + -1;
    if (*piVar3 < 0) {
      return;
    }
  } while( true );
}


// ===== ovl_19b0 @ 1ca8:19b0

void ovl_19b0(void)

{
  char *pcVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  int in_BX;
  int iVar6;
  int unaff_SI;
  int unaff_DI;
  char *pcVar7;
  undefined2 unaff_DS;
  
  uVar2 = *(undefined1 *)((uint)G_rmtyp + &OV_0x11f);
  uVar3 = *(undefined1 *)((uint)G_rmtyp + &OV_0x128);
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
      iVar5 = CONCAT11(*(undefined1 *)((8 - iVar5) + &OV_0x13a),
                       *(undefined1 *)((8 - iVar5) + &OV_0x131)) + CONCAT11(uVar3,uVar2);
      *(undefined1 *)(iVar6 + &G_p1x) = (char)iVar5;
      *(undefined1 *)(iVar6 + &G_p1y) = (char)((uint)iVar5 >> 8);
    }
    iVar6 = iVar6 + 1;
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
      EXE_FixMusRegs();
      return;
    }
  } while( true );
}


// ===== ovl_1a0d @ 1ca8:1a0d

void ovl_1a0d(void)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int in_BX;
  char *pcVar7;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  uVar3 = 0;
  OV_0x3d3 = 0;
  pcVar7 = (char *)G_loc+16;
  while( true ) {
    if (*pcVar7 == -1) break;
    OV_0x3d3 = OV_0x3d3 + '\x01';
    if (*pcVar7 == '\0') {
      uVar3 = uVar3 | 2;
    }
    else if (pcVar7[1] == '\0') {
      uVar3 = uVar3 | 4;
    }
    else if (*pcVar7 == '\n') {
      uVar3 = uVar3 | 8;
    }
    else if (pcVar7[1] == '\b') {
      uVar3 = uVar3 | 0x10;
    }
    pcVar7 = pcVar7 + 6;
  }
  OV_0x3d4 = (byte)uVar3;
  if (1 < OV_0x3d3) {
    if ((G_lastdir & 1) == 0) {
      uVar3 = (uint)((byte)uVar3 & *(byte *)((G_lastdir >> 1) + &OV_0x16c)
                    );
    }
    else {
      LOCK();
      iVar1 = G_lastdir;
      G_lastdir = in_BX;
      UNLOCK();
      uVar3 = (uint)*(byte *)(iVar1 + &OV_0x163);
      LOCK();
      in_BX = G_lastdir;
      G_lastdir = iVar1;
      UNLOCK();
    }
  }
  iVar1 = *(int *)(uVar3 + &OV_0x143);
  iVar6 = 0;
  iVar4 = 6;
  do {
    if (*(int *)(iVar6 * 2 + &G_party) != 0xff) {
      pcVar7 = (char *)&G_formatn;
      iVar5 = 9;
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar2 = pcVar7;
        pcVar7 = pcVar7 + 1;
      } while ((char)iVar6 != *pcVar2);
      iVar5 = CONCAT11(*(undefined1 *)((8 - iVar5) + &OV_0x13a),
                       *(undefined1 *)((8 - iVar5) + &OV_0x131)) + iVar1;
      *(undefined1 *)(iVar6 + &G_p1x) = (char)iVar5;
      *(undefined1 *)(iVar6 + &G_p1y) = (char)((uint)iVar5 >> 8);
    }
    iVar6 = iVar6 + 1;
    iVar4 = iVar4 + -1;
    if (iVar4 == 0) {
      EXE_FixMusRegs(in_BX);
      return;
    }
  } while( true );
}


// ===== ovl_1a90 @ 1ca8:1a90

void ovl_1a90(void)

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
      uVar4 = EXE_PlacePerson(0x1ca8,uVar2,uVar3);
      *(undefined1 *)(uVar7 + &G_p1x) = (char)uVar4;
      *(undefined1 *)(uVar7 + &G_p1y) = (char)((uint)uVar4 >> 8);
    }
    uVar6 = uVar7 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}


// ===== ovl_1ad5 @ 1ca8:1ad5

void ovl_1ad5(void)

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
  ovl_1b3e();
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


// ===== ovl_1af6 @ 1ca8:1af6

void ovl_1af6(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  undefined1 in_DL;
  int in_BX;
  int unaff_SI;
  undefined2 *puVar4;
  int unaff_DI;
  undefined2 *puVar5;
  undefined2 unaff_DS;
  
  EXE_LoadMap(0x1ca8,in_DL,0,0x47);
  if (OV_0x3cf != 0) {
    puVar5 = (undefined2 *)&G_thismap;
    puVar4 = (undefined2 *)((int)puVar5 + (uint)OV_0x3cf * 0x65);
    for (iVar3 = 0x32; iVar3 != 0; iVar3 = iVar3 + -1) {
      puVar2 = puVar5;
      puVar5 = puVar5 + 1;
      puVar1 = puVar4;
      puVar4 = puVar4 + 1;
      *puVar2 = *puVar1;
    }
    for (iVar3 = 1; iVar3 != 0; iVar3 = iVar3 + -1) {
      puVar2 = puVar5;
      puVar5 = (undefined2 *)((int)puVar5 + 1);
      puVar1 = puVar4;
      puVar4 = (undefined2 *)((int)puVar4 + 1);
      *(undefined1 *)puVar2 = *(undefined1 *)puVar1;
    }
  }
  return;
}


// ===== ovl_1b30 @ 1ca8:1b30

void ovl_1b30(void)

{
  int in_BX;
  undefined2 unaff_DS;
  
  EXE_FillWindow(0x1ca8,0,0);
  return;
}


// ===== ovl_1b3e @ 1ca8:1b3e

void ovl_1b3e(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_AddScrap(0x1ca8,G_loc+10);
  return;
}


