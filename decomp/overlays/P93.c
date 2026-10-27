// ===== ovl_0254 @ 1ca8:0254

int __cdecl16near ovl_0254(void)

{
  return iRam000004f8 + 0x1f00;
}


// ===== ovl_0271 @ 1ca8:0271

/* WARNING: Possible PIC construction at 0x0001cedb: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0001cede) */

void ovl_0271(void)

{
  undefined2 *puVar1;
  char *pcVar2;
  char *pcVar3;
  byte *pbVar4;
  char cVar5;
  byte bVar6;
  undefined2 *puVar7;
  char cVar8;
  byte bVar9;
  undefined1 uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int extraout_DX;
  int extraout_DX_00;
  int extraout_DX_01;
  int iVar15;
  byte extraout_DH;
  int in_BX;
  byte *unaff_SI;
  int unaff_DI;
  byte *pbVar16;
  undefined2 unaff_DS;
  undefined1 uVar17;
  bool bVar18;
  undefined1 uStack_7;
  undefined1 uStack_5;
  undefined2 uVar19;
  
  iVar14 = 0x1ca8;
  ovl_0254();
  &G_RENTPTR[0] = 0;
  &G_RENTPTR[1] = 0;
  unaff_SI[-0x7b62] = 1;
  ovl_1099();
  ovl_1137();
  if ((unaff_SI[-0x638a] & 0x38) != 0) {
    ovl_1151();
    ovl_0cb9();
  }
L_0296:
  uVar10 = (undefined1)iVar14;
  if ((unaff_SI[-0x638a] & 6) == 0) {
    EXE_InitMap(uVar10);
    EXE_FillWindow(uVar10,(char)G_winxy,
               (char)((uint)G_winxy >> 8));
    if ((unaff_SI[-0x638a] & 0x30) != 0) {
      ovl_0c23();
    }
  }
  else {
    EXE_InitMap(uVar10);
    G_crossovlycall = *(int *)(in_BX + 0x14c) + 3;
    G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14e);
    EXE_crossovlycall(iVar14);
    G_crossovlycall = *(int *)(in_BX + 0x14c) + 0x30;
    G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14e);
    EXE_crossovlycall(iVar14);
  }
L_0306:
  uVar10 = (undefined1)iVar14;
  EXE_Menu(uVar10,(char)G_CAMPMNUNUM);
  EXE_InitCom(uVar10,(char)&OV_0x130,uVar10,(char)G_CAMPMNULEN);
L_0324:
  while( true ) {
    while( true ) {
      do {
        &G_WHATACTV[0] = 0xff;
        &G_WHATACTV[1] = 0;
        iVar11 = EXE_Parser(uVar10,(char)&G_mnuparms,0);
        if (iVar11 == -1) goto L_046b;
        if (iVar11 == 0xfd) goto L_0296;
        if (iVar11 == 0xfe) goto L_0306;
      } while (iVar11 == 0xff);
      uVar12 = ovl_11d2();
      if (uVar12 < 2) {
        if (uVar12 == 0) {
          iVar11 = EXE_UseItem(uVar10,(char)G_curpla,0);
          if (iVar11 == 0) {
            EXE_NoUse(uVar10);
          }
          goto L_0296;
        }
        EXE_RecSpl(uVar10,(char)G_curpla);
        goto L_0306;
      }
      if (3 < uVar12) break;
      if (uVar12 != 3) {
        ovl_11e7();
        &G_WHATACTV[0] = 0;
        &G_WHATACTV[1] = 0;
        ovl_0fda();
        puVar1 = (undefined2 *)(in_BX + 0x108);
        in_BX = -0x2a33;
        iVar11 = EXE_ListSel(iVar14);
        if (iVar11 == -1) goto L_0306;
        if (iVar11 == 0) {
          EXE_InitScrap(uVar10);
          EXE_ClrTxtWnd(uVar10);
          iVar15 = 0;
          iVar11 = 6;
          do {
            if (*(int *)(unaff_SI + iVar15 + 0x21) != 0xff) {
              G_othername = *(undefined2 *)(unaff_SI + iVar15 + 0x2b26);
              G_othername+2 = unaff_DS;
              uVar17 = (undefined1)iVar11;
              uStack_5 = (undefined1)((uint)iVar11 >> 8);
              ovl_0bd5();
              iVar11 = CONCAT11(uStack_5,uVar17);
            }
            iVar15 = iVar15 + 2;
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
          EXE_PrtScrap(uVar10,0xff);
        }
        else {
          EXE_InitScrap(uVar10);
          EXE_ClrTxtWnd(uVar10);
          G_othername =
               *(undefined2 *)(unaff_SI + G_curpla * 2 + 0x2b26);
          G_othername+2 = unaff_DS;
          ovl_0bd5();
          iVar11 = 0xff;
          EXE_PrtScrap(uVar10,0xff,in_BX);
          in_BX = iVar11;
        }
        goto L_0296;
      }
      iVar11 = *(int *)(unaff_SI + G_curpla * 2 + 0x2b26);
      uVar19 = *(undefined2 *)(iVar11 + 0x1a);
      G_othername = iVar11;
      G_othername+2 = unaff_DS;
      if ((char)uVar19 == '\0') {
        uVar17 = 0x2d;
      }
      else {
        if (*(char *)(iVar11 + 0xcb) != -1) {
          bVar18 = *(char *)(iVar11 + 0xb9) == '\0';
          if (bVar18) {
            *(undefined1 *)(iVar11 + 0xb9) = 0xff;
          }
          uStack_7 = (undefined1)in_BX;
          uVar17 = (undefined1)((uint)in_BX >> 8);
          EXE_Magic(uVar10);
          in_BX = CONCAT11(uVar17,uStack_7);
          if ((unaff_SI[-0x638a] & 0x38) != 0) {
            ovl_0cc9();
          }
          if (bVar18) {
            *(undefined1 *)(*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0xb9) = 0;
          }
          goto L_0296;
        }
        uVar17 = 0x40;
      }
      EXE_IComTxt(uVar10,uVar17);
    }
    if (5 < uVar12) break;
    if (uVar12 == 5) {
      iVar11 = ovl_0cdf();
      if (iVar11 != 0) {
        iVar15 = iVar14;
        iVar13 = in_BX;
        iVar11 = EXE_ListSel(uVar10,(char)iVar11,(char)&OV_0xeb2);
        in_BX = iVar15;
        if (iVar11 != -1) {
          ovl_0dfd(unaff_SI[iVar11 + -0x6363]);
          *(undefined1 *)
           (*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + iVar13 + 0xc0) = 0xff;
          ovl_0fda();
        }
        goto L_0296;
      }
L_0d68:
      ovl_0fda();
      puVar1 = (undefined2 *)(in_BX + 0xd0);
      in_BX = iVar14;
      EXE_ListSel(iVar14,0xe);
    }
    else {
      ovl_11e7();
      iVar11 = EXE_ChkMag(iVar14);
      bVar18 = false;
      if (iVar11 != 0) {
        ovl_100d();
        if (bVar18) {
          ovl_0fda();
        }
        else {
          iVar15 = 0;
          iVar11 = 0x53;
          do {
            iVar13 = EXE_SearchInv(iVar14,(char)iVar11,(char)G_curpla,
                                (char)&G_BOOKINV);
            if (iVar13 != 0) {
              ovl_0a15();
              iVar11 = extraout_DX_01;
            }
            iVar11 = iVar11 + 1;
          } while ((byte)iVar11 < 0x5a);
          if (iVar15 == 0) {
            ovl_0fda();
          }
          else {
            puVar1 = (undefined2 *)(in_BX + 0x174);
            in_BX = &OV_0xb48;
            iVar11 = EXE_ListSel(uVar10,(char)iVar15,&OV_0xb48,iVar14);
            if (iVar11 != -1) {
              bVar9 = unaff_SI[iVar11 + -0x74b2];
              G_WHATITEM = (uint)bVar9;
              EXE_SetTxtSpell(uVar10,bVar9);
              iVar11 = *(int *)(unaff_SI + G_curpla * 2 + 0x2b26);
              *(undefined1 *)(iVar11 + 0xd7) = (char)G_WHATITEM;
              *(undefined1 *)(iVar11 + 0xb9) = 1;
              uVar17 = (undefined1)in_BX;
              uStack_5 = (undefined1)((uint)in_BX >> 8);
              uVar10 = EXE_LrnTim(uVar10,(char)G_WHATITEM,
                                  (char)G_curpla);
              in_BX = CONCAT11(uStack_5,uVar17);
              *(undefined1 *)(iVar11 + 0xa7) = uVar10;
              ovl_0fda();
            }
          }
        }
        goto L_0296;
      }
      iVar11 = 0x2d;
      EXE_IComTxt(uVar10,0x2d,in_BX);
      in_BX = iVar11;
    }
  }
  uVar17 = uVar12 < 7;
  if (uVar12 < 8) {
    if (uVar12 == 7) {
      uVar17 = 0;
      if ((unaff_SI[-0x638a] & 3) == 0) {
        ovl_0fda();
        goto L_0324;
      }
      ovl_11e7();
      &G_WHATACTV[0] = 9;
      &G_WHATACTV[1] = 0;
      uVar19 = 0xd331;
      ovl_1027();
      if ((bool)uVar17) goto L_0324;
      ovl_100d(uVar19);
      if (!(bool)uVar17) {
        *(undefined1 *)(extraout_DX + 0xb9) = 9;
        ovl_0fda();
        goto L_0324;
      }
    }
    else {
      ovl_11e7();
      &G_WHATACTV[0] = 6;
      &G_WHATACTV[1] = 0;
      uVar19 = 0xd362;
      ovl_1027();
      if ((bool)uVar17) goto L_0324;
      ovl_100d(uVar19);
      if (!(bool)uVar17) {
        *(undefined1 *)(extraout_DX_00 + 0xb9) = 6;
        ovl_0fda();
        goto L_0324;
      }
    }
L_08bb:
    ovl_0fda(uVar19);
    goto L_0324;
  }
  if (uVar12 < 10) {
    if (uVar12 == 9) {
      ovl_0cdf();
      iVar11 = *(int *)(unaff_SI + G_curpla * 2 + 0x2b26);
      uVar12 = 0;
      iVar15 = 0;
      do {
        bVar9 = *(byte *)(uVar12 + iVar11 + 0x2b);
        if (bVar9 == 0xff) break;
        if ((0x1e < bVar9) && (bVar9 < 0x31)) {
          bVar6 = *(byte *)(uVar12 + iVar11 + 0x53);
          unaff_SI[iVar15 + -0x74b2] = bVar9;
          unaff_SI[iVar15 + -0x7488] = bVar6;
          unaff_SI[iVar15 + -0x745e] = (byte)uVar12;
          uVar17 = (undefined1)iVar15;
          uStack_5 = (undefined1)((uint)iVar15 >> 8);
          iVar13 = ovl_0f21();
          iVar15 = CONCAT11(uStack_5,uVar17);
          if (iVar13 == -1) {
            iVar15 = iVar15 + 1;
          }
        }
        uVar12 = uVar12 + 1;
      } while (uVar12 < 0x28);
      if (iVar15 == 0) goto L_0d68;
      iVar11 = iVar14;
      iVar15 = EXE_ListSel(uVar10,(char)iVar15,(char)&OV_0x104b,iVar14,in_BX);
      in_BX = iVar11;
      if (iVar15 == -1) goto L_0296;
      G_WHATITEM =
           CONCAT11(unaff_SI[iVar15 + -0x745e],unaff_SI[iVar15 + -0x74b2]);
      ovl_0d25();
      if ((unaff_SI[-0x6351] & extraout_DH) != 0) {
        iVar11 = 6;
        pbVar16 = &G_GARBLIST;
        goto code_r0x0001d93b;
      }
      uVar19 = ovl_0f21();
      G_PUTSLOT = uVar19;
      &G_GARBMSG[0] = 0xe;
      &G_GARBMSG[1] = 0;
      goto L_0eeb;
    }
    uVar17 = 0;
    if ((unaff_SI[-0x638a] & 2) == 0) {
      EXE_IComTxt(uVar10,0x24);
    }
    else {
      ovl_11e7();
      &G_WHATACTV[0] = 3;
      &G_WHATACTV[1] = 0;
      uVar19 = 0xd390;
      ovl_1027();
      if (!(bool)uVar17) {
        if ((char)*(undefined2 *)
                   (*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0xbd) != '\0')
        goto L_08bb;
        *(undefined1 *)(*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0xb9) = 3;
        ovl_0fda(uVar19);
      }
    }
    goto L_0324;
  }
  if (0xb < uVar12) {
    if ((((unaff_SI[-0x638a] & 4) != 0) && (uVar12 = uVar12 - 0x31, uVar12 < 9)) && (uVar12 != 4)) {
      uVar12 = uVar12 * 3 + 0xc;
      bVar9 = CARRY2(uVar12,*(uint *)(in_BX + 0x14c));
      G_crossovlycall = uVar12 + *(uint *)(in_BX + 0x14c);
      G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14e);
      EXE_crossovlycall(iVar14);
      if ((bVar9 & 1) == 0) {
        G_crossovlycall = *(int *)(in_BX + 0x14c) + 0x18;
        G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14e);
        EXE_crossovlycall(iVar14);
        iVar11 = -0x3122;
        goto SUB_1ca8_04d4;
      }
      if (unaff_SI[-0x7b62] == 0) goto L_046b;
    }
    goto L_0324;
  }
  if (uVar12 == 0xb) goto L_046b;
  ovl_11e7();
  iVar11 = -0x30d5;
  ovl_0fda();
  if ((unaff_SI[-0x638a] & 4) != 0) goto L_0324;
  EXE_Menu(uVar10,0xf,in_BX,iVar11);
  EXE_InitCom(uVar10,(char)&OV_0x130,uVar10,1);
SUB_1ca8_04d4:
  do {
    &G_WHATPLA[0] = 5;
    &G_WHATPLA[1] = 0;
    do {
      if (*(int *)(unaff_SI + G_WHATPLA * 2 + 0x21) != 0xff) {
        iVar15 = *(int *)(unaff_SI + G_WHATPLA * 2 + 0x2b26);
        G_CURCOND1 = *(undefined2 *)(iVar15 + 0xbd);
        G_othername = iVar15;
        G_othername+2 = unaff_DS;
        cVar8 = (char)*(undefined2 *)
                       (*(int *)(unaff_SI + G_WHATPLA * 2 + 0x2b26) + 0xb9);
        if (cVar8 == '\0') {
          if ((*unaff_SI & 1) == 0) {
            if (((unaff_SI[-0x638a] & 2) == 0) ||
               (iVar11 = EXE_SearchInv(iVar14,0x52,(char)G_WHATPLA,
                                    (char)&G_IINFO), iVar11 != 0)) {
              ovl_07e5();
            }
            else {
              ovl_07e5();
            }
            iVar11 = -0x2fe6;
            ovl_0813();
          }
        }
        else {
          uVar10 = (undefined1)iVar14;
          if (cVar8 == '\x01') {
            if (G_CURCOND1 == 0) {
              iVar15 = *(int *)(unaff_SI + G_WHATPLA * 2 + 0x2b26);
              if ((char)*(undefined2 *)(iVar15 + 0xa7) == '\0') {
                bVar9 = *(byte *)(iVar15 + 0xd7);
                uVar12 = (uint)bVar9;
                G_WHATITEM = uVar12;
                if (*(byte *)(iVar15 + uVar12 + 0x7b) < 99) {
                  pcVar2 = (char *)(iVar15 + uVar12 + 0x7b);
                  *pcVar2 = *pcVar2 + '\x01';
                }
                uVar17 = (undefined1)in_BX;
                uStack_5 = (undefined1)((uint)in_BX >> 8);
                EXE_SetTxtSpell(uVar10,bVar9);
                puVar7 = (undefined2 *)(CONCAT11(uStack_5,uVar17) + 0x160);
                uVar10 = EXE_viaptr_puVar7(uVar10,(char)G_WHATITEM,
                                            (char)G_WHATPLA);
                in_BX = CONCAT11(uStack_5,uVar17);
                *(undefined1 *)(iVar15 + 0xa7) = uVar10;
                ovl_0fda();
              }
              else {
                *(char *)(iVar15 + 0xa7) = *(char *)(iVar15 + 0xa7) + -1;
              }
            }
            else {
              ovl_1061();
            }
          }
          else if (cVar8 == '\x03') {
            if (unaff_SI[-0x636f] == 0) {
              if ((*unaff_SI == 0) || (*unaff_SI == 0x1e)) {
                uVar19 = EXE_RndCo(uVar10,100,in_BX,iVar11);
                G_DICEROLL = uVar19;
                unaff_SI[-0x6375] =
                     (byte)(*(uint *)(*(int *)(unaff_SI + G_WHATPLA * 2 + 0x2b26)
                                     + 0x28) >> 1) & 0x7f;
                cVar8 = *(char *)((uint)unaff_SI[0x273d] + &OV_0x103);
                iVar14 = 0x1000;
                cVar5 = *(char *)(G_weather + &OV_0x10d);
                if ((cVar8 != -1) &&
                   (((cVar5 != -1 && (bVar9 = cVar8 + cVar5 + unaff_SI[-0x6375], -1 < (char)bVar9))
                    && (unaff_SI[-0x6371] <= bVar9)))) {
                  EXE_IncObj(0,(char)*(undefined2 *)
                                      (unaff_SI + G_WHATPLA * 2 + 0x2b26),0x31,1)
                  ;
                  ovl_0fda();
                  EXE_Wait(0,0xfa);
                  EXE_ClrTxtWnd();
                  iVar15 = in_BX;
                  EXE_InitScrap();
                  unaff_SI[-0x76da] = 0x11;
                  iVar11 = G_curpla;
                  G_curpla = G_WHATPLA;
                  uVar10 = 0;
                  EXE_SkillUp0();
                  in_BX = CONCAT11(0x10,uVar10);
                  G_curpla = iVar15;
                }
              }
            }
            else {
              ovl_1061();
            }
          }
          else if (cVar8 == '\x06') {
            if (G_CURCOND1 == 0) {
              ovl_0849();
              iVar15 = 100;
              iVar11 = in_BX;
              uVar19 = EXE_RndCo(uVar10);
              in_BX = iVar15;
              G_DICEROLL = uVar19;
              if (unaff_SI[-0x6371] <=
                  (byte)*(undefined2 *)
                         (*(int *)(unaff_SI + G_WHATPLA * 2 + 0x2b26) + 0x25)) {
                ovl_0849();
              }
            }
            else {
              ovl_1061();
            }
          }
          else if (unaff_SI[-0x636f] != 0) {
            ovl_1061();
          }
        }
      }
      pbVar4 = &G_WHATPLA;
      *(int *)pbVar4 = *(int *)pbVar4 + -1;
    } while (-1 < *(int *)pbVar4);
    uVar10 = (undefined1)iVar14;
    EXE_CalUpd(uVar10);
    if ((unaff_SI[-0x638a] & 2) != 0) {
      G_crossovlycall = *(int *)(in_BX + 0x14c) + 6;
      G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14e);
      EXE_crossovlycall(iVar14);
      G_crossovlycall = *(int *)(in_BX + 0x14c) + 9;
      G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14e);
      EXE_crossovlycall(iVar14);
      if (G_docmbt != 0) {
        EXE_ClrMnuWnd(uVar10,in_BX);
        goto L_046b;
      }
    }
    if ((unaff_SI[-0x638a] & 4) != 0) {
      return;
    }
    iVar15 = EXE_HandleMouse(uVar10,0,1);
    if ((iVar15 != 0) || (iVar15 = EXE_ReadKbd(uVar10,0), iVar15 != 0))
    goto L_07dd;
    LOCK();
    pcVar3 = *(char **)&G_RENTPTR;
    G_RENTPTR = in_BX;
    UNLOCK();
    cVar8 = *pcVar3;
    LOCK();
    in_BX = G_RENTPTR;
    *(char **)&G_RENTPTR = pcVar3;
    UNLOCK();
    if ((pcVar3 != (char *)0x0) && (cVar8 == '\0')) {
L_046b:
      iVar14 = 6;
      iVar11 = 0;
      do {
        if (*(int *)(unaff_SI + iVar11 + 0x21) != 0xff) {
          *(undefined1 *)(*(int *)(unaff_SI + iVar11 + 0x2b26) + 0xb9) = 0xff;
        }
        iVar11 = iVar11 + 2;
        iVar14 = iVar14 + -1;
      } while (iVar14 != 0);
      unaff_SI[-0x7b62] = 0;
      if ((unaff_SI[-0x638a] & 0x30) != 0) {
        ovl_11b3();
      }
      ovl_0ca4();
      return;
    }
  } while( true );
  while( true ) {
    iVar11 = iVar11 + -1;
    pbVar4 = pbVar16;
    pbVar16 = pbVar16 + 1;
    if (extraout_DH == *pbVar4) break;
code_r0x0001d93b:
    if (iVar11 == 0) break;
  }
  G_PUTSLOT = (uint)unaff_SI[-0x635e - iVar11];
  ovl_0dfd();
  G_deftxtparms+6 = G_deftxtparms+4;
  G_deftxtparms+8 = unaff_DS;
  &G_GARBMSG[0] = 0x11;
  &G_GARBMSG[1] = 0;
L_0eeb:
  uVar12 = G_WHATITEM;
  *(undefined1 *)
   (*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + G_PUTSLOT +
   0xc0) = (char)(uVar12 >> 8);
  EXE_SetTxtObj(iVar14,uVar12 & 0xff);
  ovl_0fda();
  goto L_0296;
L_07dd:
  EXE_ClrTxtWnd(uVar10);
  goto L_0306;
}


// ===== ovl_07e5 @ 1ca8:07e5

void ovl_07e5(void)

{
  int iVar1;
  byte in_AL;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = *(int *)(G_WHATPLA * 2 + &G_heroptr);
  if ((*(byte *)(iVar1 + 0xbd) & 10) != 0) {
    in_AL = in_AL >> 1;
  }
  if ((byte)*(undefined2 *)(iVar1 + 0xca) < in_AL) {
    *(char *)(iVar1 + 0xca) = *(char *)(iVar1 + 0xca) + '\x01';
  }
  return;
}


// ===== ovl_0813 @ 1ca8:0813

void ovl_0813(void)

{
  int iVar1;
  byte in_AL;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = *(int *)(G_WHATPLA * 2 + &G_heroptr);
  if ((*(byte *)(iVar1 + 0xbd) & 10) != 0) {
    in_AL = in_AL >> 1;
  }
  if ((byte)*(undefined2 *)(iVar1 + 0xba) < in_AL) {
    *(char *)(iVar1 + 0xba) = *(char *)(iVar1 + 0xba) + '\x01';
    EXE_IsHeTr(iVar1);
  }
  return;
}


// ===== ovl_0849 @ 1ca8:0849

uint ovl_0849(void)

{
  uint uVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  
  G_OTHERPLA = G_WHATPLA;
  do {
    uVar1 = ovl_0886();
    if (!(bool)in_CF) {
      return uVar1;
    }
    do {
      G_OTHERPLA = G_OTHERPLA + 1;
      while( true ) {
        uVar1 = G_OTHERPLA;
        if (uVar1 == G_WHATPLA) {
          return uVar1;
        }
        if (uVar1 < 6) break;
        G_OTHERPLA = 0;
      }
      uVar1 = *(uint *)(uVar1 * 2 + &G_party);
      in_CF = uVar1 < 0xff;
    } while (uVar1 == 0xff);
  } while( true );
}


// ===== ovl_0886 @ 1ca8:0886

void ovl_0886(void)

{
  int in_AX;
  int iVar1;
  byte *pbVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = 0x28;
  pbVar2 = (byte *)(*(int *)(in_AX * 2 + &G_heroptr) + 0x53);
  do {
    if (0x80 < *pbVar2) {
      *pbVar2 = *pbVar2 - 1;
      return;
    }
    pbVar2 = pbVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_0a15 @ 1ca8:0a15

void ovl_0a15(void)

{
  int iVar1;
  int in_CX;
  int iVar2;
  int in_DX;
  int unaff_SI;
  int iVar3;
  undefined2 unaff_DS;
  
  iVar1 = (in_DX - 0x53U & 0xff) * 6;
  iVar3 = iVar1 + *(int *)(G_curpla * 2 + &G_heroptr);
  iVar2 = 6;
  do {
    *(undefined1 *)(in_CX + &G_blasty+5) = *(undefined1 *)(iVar3 + 0x7b);
    *(undefined1 *)(in_CX + &G_scrap2+12) = (char)iVar1;
    iVar1 = iVar1 + 1;
    in_CX = in_CX + 1;
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


// ===== ovl_0a48 @ 1ca8:0a48

void __cdecl16far ovl_0a48(int param_1)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_0254();
  uVar2 = G_scroll;
  G_scroll = 0;
  LOCK();
  UNLOCK();
  uVar1 = *(undefined1 *)(param_1 + &G_scrap2+12);
  LOCK();
  UNLOCK();
  G_deftxtparms+2 = *(undefined1 *)(param_1 + &G_blasty+5);
  EXE_SetTxtSpell(uVar1);
  EXE_PrtWrdX(&OV_0x128,0x1ca8,0);
  EXE_Pad(in_BX);
  G_scroll = uVar2;
  return;
}


// ===== ovl_0bd5 @ 1ca8:0bd5

void ovl_0bd5(void)

{
  int iVar1;
  uint uVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  int in_stack_00000000;
  
  ovl_1027();
  if ((bool)in_CF) {
    return;
  }
  iVar1 = *(int *)(in_stack_00000000 * 2 + &G_heroptr);
  uVar2 = *(uint *)(iVar1 + 0xbd);
  if ((uVar2 & 8) != 0) {
    ovl_0f9d();
    return;
  }
  if ((uVar2 & 4) != 0) {
    ovl_0f9d();
    return;
  }
  if ((uVar2 & 0x4000) == 0) {
    *(undefined1 *)(iVar1 + 0xb9) = 0;
    ovl_0f9d();
    return;
  }
  ovl_0f9d();
  return;
}


// ===== ovl_0c23 @ 1ca8:0c23

void ovl_0c23(void)

{
  int iVar1;
  int iVar2;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_ClearShadowMap();
  iVar2 = 6;
  iVar1 = 0;
  do {
    if ((*(int *)(iVar1 + &G_party) != 0xff) &&
       (*(char *)(*(int *)(iVar1 + &G_heroptr) + 0xb9) == '\0')) {
      ovl_0c5a();
    }
    iVar1 = CONCAT11((char)((uint)iVar1 >> 8),(char)iVar1 + '\x02');
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  EXE_PageFlip(in_BX);
  return;
}


// ===== ovl_0c5a @ 1ca8:0c5a

int ovl_0c5a(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int in_AX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar1 = *(undefined1 *)(in_AX + &G_p1x);
  uVar2 = *(undefined1 *)(in_AX + &G_p1y);
  G_zp_10 = CONCAT11(uVar2,uVar1);
  EXE_OrTile(0x17,uVar1,uVar2);
  EXE_Locate(G_zp_10 & 0xff,G_zp_10 >> 8);
  *(undefined1 *)(G_zp_0A + 0x1c68) = 0x17;
  return in_BX;
}


// ===== ovl_0ca4 @ 1ca8:0ca4

void ovl_0ca4(void)

{
  int iVar1;
  int iVar2;
  int in_BX;
  undefined2 unaff_DS;
  
  iVar2 = 6;
  iVar1 = 0;
  do {
    EXE_SetPlTilNo(iVar1);
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


// ===== ovl_0cb9 @ 1ca8:0cb9

void ovl_0cb9(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 6;
  iVar1 = 0;
  do {
    ovl_0cc9(iVar2,iVar1);
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}


// ===== ovl_0cc9 @ 1ca8:0cc9

void ovl_0cc9(void)

{
  int in_AX;
  int extraout_DX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_FirsTil();
  *(undefined1 *)(in_AX + &G_pltilno) = *(undefined1 *)(extraout_DX + 8);
  return;
}


// ===== ovl_0cdf @ 1ca8:0cdf

int ovl_0cdf(void)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  byte extraout_DH;
  uint uVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = *(int *)(G_curpla * 2 + &G_heroptr);
  iVar3 = 0;
  uVar4 = 0;
  G_GARBWORN = 0;
  do {
    if (*(char *)(uVar4 + iVar1 + 0xc0) != -1) {
      uVar2 = ovl_0d25();
      G_GARBWORN = G_GARBWORN | extraout_DH;
      *(undefined1 *)(iVar3 + &G_WORNLIST) = uVar2;
      *(undefined1 *)(iVar3 + &G_WEARLIST) = (char)uVar4;
      *(byte *)(iVar3 + &G_GARBLIST) = extraout_DH;
      iVar3 = iVar3 + 1;
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < 6);
  return iVar3;
}


// ===== ovl_0d25 @ 1ca8:0d25

void ovl_0d25(void)

{
  return;
}


// ===== ovl_0dfd @ 1ca8:0dfd

void ovl_0dfd(void)

{
  char in_AL;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SetTxtObj(*(undefined1 *)
                     (*(int *)(G_curpla * 2 + &G_heroptr) +
                     (uint)(byte)(in_AL + 0x2b)));
  return;
}


// ===== ovl_0f21 @ 1ca8:0f21

undefined4 ovl_0f21(void)

{
  char *pcVar1;
  int iVar2;
  char in_AL;
  int iVar3;
  int unaff_SI;
  char *pcVar4;
  undefined2 unaff_DS;
  bool bVar5;
  
  iVar2 = *(int *)(G_curpla * 2 + &G_heroptr);
  pcVar4 = (char *)(iVar2 + 0xc0);
  bVar5 = pcVar4 == (char *)0x0;
  iVar3 = 6;
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar1 = pcVar4;
    pcVar4 = pcVar4 + 1;
    bVar5 = in_AL == *pcVar1;
  } while (!bVar5);
  if (!bVar5) {
    iVar3 = 6;
  }
  return CONCAT22(iVar2,5 - iVar3);
}


// ===== ovl_0f4b @ 1ca8:0f4b

void __cdecl16far ovl_0f4b(int param_1)

{
  undefined2 uVar1;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  ovl_0254();
  uVar1 = G_scroll;
  G_scroll = 0;
  LOCK();
  UNLOCK();
  LOCK();
  UNLOCK();
  EXE_SetTxtObj(*(undefined1 *)(param_1 + &G_scrap2+12));
  EXE_PrtWrdX(&OV_0x125,0x1ca8,0);
  EXE_Pad(in_BX);
  G_scroll = uVar1;
  return;
}


// ===== ovl_0f9d @ 1ca8:0f9d

void ovl_0f9d(void)

{
  undefined1 *puVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  int in_BX;
  int unaff_SI;
  int unaff_DI;
  undefined1 *puVar5;
  undefined2 unaff_DS;
  
  EXE_AddScrap(&OV_0x13d,0x1ca8);
  uVar3 = G_txtww >> 1;
  cVar2 = (char)(G_scrapptr % (uVar3 & 0xff));
  if (cVar2 != '\0') {
    iVar4 = CONCAT11((byte)(G_txtww >> 9),(char)uVar3 - cVar2);
    puVar5 = (undefined1 *)(&G_scrap + G_scrapptr);
    G_scrapptr = G_scrapptr + iVar4;
    for (; iVar4 != 0; iVar4 = iVar4 + -1) {
      puVar1 = puVar5;
      puVar5 = puVar5 + 1;
      *puVar1 = 0x20;
    }
  }
  return;
}


// ===== ovl_0fda @ 1ca8:0fda

void ovl_0fda(void)

{
  undefined2 in_AX;
  int in_BX;
  int unaff_DI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  EXE_InitScrap();
  EXE_AddScrap(&OV_0x13d,0x1ca8,in_AX);
  EXE_PrtScrap(0xff,in_BX);
  return;
}


// ===== ovl_100d @ 1ca8:100d

void ovl_100d(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (*(int *)(*(int *)(G_curpla * 2 + &G_heroptr) + 0xbd) == 0) {
    return;
  }
  return;
}


// ===== ovl_1027 @ 1ca8:1027

void ovl_1027(void)

{
  int iVar1;
  undefined2 uVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = *(int *)(G_curpla * 2 + &G_heroptr);
  uVar2 = *(undefined2 *)(iVar1 + 6);
  G_othername = iVar1;
  G_othername+2 = unaff_DS;
  if (((char)uVar2 != '\x04') || (G_sailsw == '\0')) {
    return;
  }
  if (G_WHATACTV == '\0') {
    ovl_0f9d();
    return;
  }
  ovl_0fda();
  return;
}


// ===== ovl_1061 @ 1ca8:1061

void ovl_1061(void)

{
  int iVar1;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = *(int *)(G_WHATPLA * 2 + &G_heroptr);
  if ((char)*(undefined2 *)(iVar1 + 0xb9) != -1) {
    *(undefined1 *)(iVar1 + 0xb9) = 0xff;
    ovl_0fda();
    EXE_PrtWrd(G_comtxtptr);
  }
  return;
}


// ===== ovl_1099 @ 1ca8:1099

void ovl_1099(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_CAMPMNUNUM = 0xd;
  G_CAMPMNULEN = 0xc;
  if (G_curmpg == '\x01') {
    if (G_sailsw == '\0') {
      G_CAMPSITE = 2;
      return;
    }
    G_CAMPSITE = 4;
    return;
  }
  if (G_curmpg == '\a') {
    G_CAMPSITE = 8;
    return;
  }
  if (G_curmpg != '\x05') goto L_1126;
  if (G_rmdata+6 == '\0') {
    if (G_currm < 0x40) goto L_1126;
    if (G_currm < 0x48) {
      G_RENTPTR = unaff_SI + G_currm + 0x200d;
      G_CAMPSITE = 0x20;
      return;
    }
    if ((G_currm < 0x5c) || (0x6b < G_currm))
    goto L_1126;
    if (G_currm < 0x6c) goto L_111f;
  }
  if ((G_locspec == '\x14') && (G_currm == '\t')) {
L_111f:
    G_CAMPSITE = 0x10;
    return;
  }
L_1126:
  G_CAMPSITE = 1;
  G_CAMPMNUNUM = 0x16;
  G_CAMPMNULEN = 5;
  return;
}


// ===== ovl_1137 @ 1ca8:1137

void ovl_1137(void)

{
  byte bVar1;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if ((G_CAMPSITE & 2) != 0) {
    bVar1 = EXE_HighStat(0x24);
    G_CARPADJ = bVar1 >> 1;
  }
  return;
}


// ===== ovl_1151 @ 1ca8:1151

void ovl_1151(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  undefined1 *puVar3;
  undefined2 *puVar4;
  byte bVar5;
  int iVar6;
  int in_BX;
  int unaff_SI;
  undefined2 *puVar7;
  undefined2 *puVar8;
  int unaff_DI;
  undefined1 *puVar9;
  undefined2 unaff_DS;
  undefined2 uVar10;
  
  puVar8 = (undefined2 *)&G_CAMPPXY;
  puVar7 = (undefined2 *)&G_p1x;
  for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar4 = puVar8;
    puVar8 = puVar8 + 1;
    puVar1 = puVar7;
    puVar7 = puVar7 + 1;
    *puVar4 = *puVar1;
  }
  puVar9 = (undefined1 *)&G_p1x;
  if ((G_CAMPSITE & 0x30) == 0) {
    puVar8 = (undefined2 *)&OV_0x119;
    uVar10 = 0x1ca8;
  }
  else {
    puVar8 = (undefined2 *)G_loc+28;
    uVar10 = unaff_DS;
    if (((G_CAMPSITE & 0x20) != 0) &&
       (bVar5 = (byte)G_currm, bVar5 < 0x5c)) {
      puVar8 = (undefined2 *)((int)puVar8 + (int)(char)(bVar5 * '\f'));
    }
  }
  iVar6 = 6;
  do {
    puVar1 = puVar8;
    puVar8 = puVar8 + 1;
    uVar2 = *puVar1;
    puVar9[6] = (char)((uint)uVar2 >> 8);
    puVar3 = puVar9;
    puVar9 = puVar9 + 1;
    *puVar3 = (char)uVar2;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  EXE_FixMusRegs();
  return;
}


// ===== ovl_11b3 @ 1ca8:11b3

void ovl_11b3(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  int in_BX;
  int unaff_SI;
  undefined2 *puVar4;
  undefined2 *puVar5;
  undefined2 unaff_DS;
  
  puVar5 = (undefined2 *)&G_p1x;
  puVar4 = (undefined2 *)&G_CAMPPXY;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    puVar2 = puVar5;
    puVar5 = puVar5 + 1;
    puVar1 = puVar4;
    puVar4 = puVar4 + 1;
    *puVar2 = *puVar1;
  }
  EXE_FixMusRegs();
  return;
}


// ===== ovl_11d2 @ 1ca8:11d2

void ovl_11d2(void)

{
  return;
}


// ===== ovl_11e7 @ 1ca8:11e7

/* WARNING: Possible PIC construction at 0x0001cedb: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x0001cede) */

void ovl_11e7(void)

{
  undefined2 *puVar1;
  char *pcVar2;
  char *pcVar3;
  byte *pbVar4;
  char cVar5;
  byte bVar6;
  undefined2 *puVar7;
  char cVar8;
  byte bVar9;
  undefined1 uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  undefined2 uVar14;
  int iVar15;
  int iVar16;
  int extraout_DX;
  int extraout_DX_00;
  int extraout_DX_01;
  int iVar17;
  byte extraout_DH;
  int iVar18;
  int in_BX;
  byte *unaff_SI;
  byte *pbVar19;
  int unaff_DI;
  undefined2 unaff_DS;
  undefined1 uVar20;
  bool bVar21;
  undefined1 uStack_3;
  undefined1 uVar22;
  undefined1 uStack_1;
  
  iVar15 = 0x1ca8;
  if ((unaff_SI[-0x638a] & 1) == 0) {
    return;
  }
  uVar20 = (undefined1)in_BX;
  uStack_1 = (undefined1)((uint)in_BX >> 8);
  EXE_IComTxt(0xa8,0x24);
  iVar18 = CONCAT11(uStack_1,uVar20);
L_0324:
  do {
    while( true ) {
      &G_WHATACTV[0] = 0xff;
      &G_WHATACTV[1] = 0;
      uVar20 = (undefined1)iVar15;
      iVar11 = EXE_Parser(uVar20,(char)&G_mnuparms,0);
      if (iVar11 == -1) goto L_046b;
      iVar17 = iVar18;
      if (iVar11 == 0xfd) goto L_0296;
      if (iVar11 != 0xfe) break;
L_0306:
      uVar20 = (undefined1)iVar15;
      EXE_Menu(uVar20,(char)G_CAMPMNUNUM);
      EXE_InitCom(uVar20,(char)&OV_0x130,uVar20,(char)G_CAMPMNULEN);
    }
  } while (iVar11 == 0xff);
  uVar12 = ovl_11d2();
  if (uVar12 < 2) {
    if (uVar12 == 0) {
      iVar11 = EXE_UseItem(uVar20,(char)G_curpla,0);
      iVar17 = iVar18;
      if (iVar11 == 0) {
        EXE_NoUse(uVar20);
      }
      goto L_0296;
    }
    EXE_RecSpl(uVar20,(char)G_curpla);
    goto L_0306;
  }
  if (uVar12 < 4) {
    if (uVar12 == 3) {
      iVar11 = *(int *)(unaff_SI + G_curpla * 2 + 0x2b26);
      uVar14 = *(undefined2 *)(iVar11 + 0x1a);
      G_othername = iVar11;
      G_othername+2 = unaff_DS;
      if ((char)uVar14 == '\0') {
        uVar10 = 0x2d;
      }
      else {
        if (*(char *)(iVar11 + 0xcb) != -1) {
          bVar21 = *(char *)(iVar11 + 0xb9) == '\0';
          if (bVar21) {
            *(undefined1 *)(iVar11 + 0xb9) = 0xff;
          }
          uStack_3 = (undefined1)iVar18;
          uVar10 = (undefined1)((uint)iVar18 >> 8);
          EXE_Magic(uVar20);
          iVar17 = CONCAT11(uVar10,uStack_3);
          if ((unaff_SI[-0x638a] & 0x38) != 0) {
            ovl_0cc9();
          }
          if (bVar21) {
            *(undefined1 *)(*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0xb9) = 0;
          }
          goto L_0296;
        }
        uVar10 = 0x40;
      }
      EXE_IComTxt(uVar20,uVar10);
      goto L_0324;
    }
    ovl_11e7();
    &G_WHATACTV[0] = 0;
    &G_WHATACTV[1] = 0;
    ovl_0fda();
    puVar1 = (undefined2 *)(iVar18 + 0x108);
    iVar18 = -0x2a33;
    iVar11 = EXE_SetYN();
    if (iVar11 == -1) goto L_0306;
    if (iVar11 == 0) {
      EXE_slot0xd6b1(uVar20);
      EXE_slot0xd629(uVar20);
      iVar17 = 0;
      iVar11 = 6;
      do {
        if (*(int *)(unaff_SI + iVar17 + 0x21) != 0xff) {
          G_othername = *(undefined2 *)(unaff_SI + iVar17 + 0x2b26);
          G_othername+2 = unaff_DS;
          uVar10 = (undefined1)iVar11;
          uStack_1 = (undefined1)((uint)iVar11 >> 8);
          ovl_0bd5();
          iVar11 = CONCAT11(uStack_1,uVar10);
        }
        iVar17 = iVar17 + 2;
        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);
      EXE_PrtScrap(uVar20,0xff);
      iVar17 = iVar18;
    }
    else {
      EXE_slot0xd6b1(uVar20);
      EXE_slot0xd629(uVar20);
      G_othername =
           *(undefined2 *)(unaff_SI + G_curpla * 2 + 0x2b26);
      G_othername+2 = unaff_DS;
      ovl_0bd5();
      EXE_PrtScrap(uVar20);
      iVar17 = 0xff;
    }
  }
  else {
    iVar17 = iVar15;
    if (5 < uVar12) {
      uVar10 = uVar12 < 7;
      if (uVar12 < 8) {
        if (uVar12 == 7) {
          uVar20 = 0;
          if ((unaff_SI[-0x638a] & 3) == 0) {
            ovl_0fda();
            goto L_0324;
          }
          ovl_11e7();
          &G_WHATACTV[0] = 9;
          &G_WHATACTV[1] = 0;
          ovl_1027();
          if ((bool)uVar20) goto L_0324;
          ovl_100d();
          if (!(bool)uVar20) {
            *(undefined1 *)(extraout_DX + 0xb9) = 9;
            ovl_0fda();
            goto L_0324;
          }
        }
        else {
          ovl_11e7();
          &G_WHATACTV[0] = 6;
          &G_WHATACTV[1] = 0;
          ovl_1027();
          if ((bool)uVar10) goto L_0324;
          ovl_100d();
          if (!(bool)uVar10) {
            *(undefined1 *)(extraout_DX_00 + 0xb9) = 6;
            ovl_0fda();
            goto L_0324;
          }
        }
L_08bb:
        ovl_0fda();
        goto L_0324;
      }
      if (uVar12 < 10) {
        if (uVar12 == 9) {
          ovl_0cdf();
          iVar11 = *(int *)(unaff_SI + G_curpla * 2 + 0x2b26);
          uVar12 = 0;
          iVar16 = 0;
          do {
            bVar9 = *(byte *)(uVar12 + iVar11 + 0x2b);
            if (bVar9 == 0xff) break;
            if ((0x1e < bVar9) && (bVar9 < 0x31)) {
              bVar6 = *(byte *)(uVar12 + iVar11 + 0x53);
              unaff_SI[iVar16 + -0x74b2] = bVar9;
              unaff_SI[iVar16 + -0x7488] = bVar6;
              unaff_SI[iVar16 + -0x745e] = (byte)uVar12;
              uVar10 = (undefined1)iVar16;
              uStack_1 = (undefined1)((uint)iVar16 >> 8);
              iVar13 = ovl_0f21();
              iVar16 = CONCAT11(uStack_1,uVar10);
              if (iVar13 == -1) {
                iVar16 = iVar16 + 1;
              }
            }
            uVar12 = uVar12 + 1;
          } while (uVar12 < 0x28);
          if (iVar16 == 0) goto L_0d68;
          iVar18 = EXE_ListSel(uVar20,(char)iVar16,(char)&OV_0x104b);
          if (iVar18 != -1) {
            G_WHATITEM =
                 CONCAT11(unaff_SI[iVar18 + -0x745e],unaff_SI[iVar18 + -0x74b2]);
            ovl_0d25();
            if ((unaff_SI[-0x6351] & extraout_DH) == 0) {
              uVar14 = ovl_0f21();
              G_PUTSLOT = uVar14;
              &G_GARBMSG[0] = 0xe;
              &G_GARBMSG[1] = 0;
            }
            else {
              iVar18 = 6;
              pbVar19 = &G_GARBLIST;
              do {
                if (iVar18 == 0) break;
                iVar18 = iVar18 + -1;
                pbVar4 = pbVar19;
                pbVar19 = pbVar19 + 1;
              } while (extraout_DH != *pbVar4);
              G_PUTSLOT = (uint)unaff_SI[-0x635e - iVar18];
              ovl_0dfd();
              G_deftxtparms+6 = G_deftxtparms+4;
              G_deftxtparms+8 = unaff_DS;
              &G_GARBMSG[0] = 0x11;
              &G_GARBMSG[1] = 0;
            }
            *(undefined1 *)
             (*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) +
              G_PUTSLOT + 0xc0) =
                 (char)((uint)G_WHATITEM >> 8);
            EXE_SetTxtObj();
            ovl_0fda();
          }
          goto L_0296;
        }
        uVar10 = 0;
        if ((unaff_SI[-0x638a] & 2) == 0) {
          EXE_IComTxt(uVar20,0x24);
        }
        else {
          ovl_11e7();
          &G_WHATACTV[0] = 3;
          &G_WHATACTV[1] = 0;
          ovl_1027();
          if (!(bool)uVar10) {
            if ((char)*(undefined2 *)
                       (*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0xbd) != '\0')
            goto L_08bb;
            *(undefined1 *)(*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + 0xb9) = 3;
            ovl_0fda();
          }
        }
      }
      else if (uVar12 < 0xc) {
        if (uVar12 == 0xb) goto L_046b;
        ovl_11e7();
        ovl_0fda();
        if ((unaff_SI[-0x638a] & 4) == 0) {
          EXE_Menu(uVar20,0xf);
          EXE_InitCom(uVar20,(char)&OV_0x130,uVar20,1);
SUB_1ca8_04d4:
          while( true ) {
            &G_WHATPLA[0] = 5;
            &G_WHATPLA[1] = 0;
            do {
              if (*(int *)(unaff_SI + G_WHATPLA * 2 + 0x21) != 0xff) {
                iVar11 = *(int *)(unaff_SI + G_WHATPLA * 2 + 0x2b26);
                G_CURCOND1 = *(undefined2 *)(iVar11 + 0xbd);
                G_othername = iVar11;
                G_othername+2 = unaff_DS;
                cVar8 = (char)*(undefined2 *)
                               (*(int *)(unaff_SI + G_WHATPLA * 2 + 0x2b26) +
                               0xb9);
                if (cVar8 == '\0') {
                  if ((*unaff_SI & 1) == 0) {
                    if (((unaff_SI[-0x638a] & 2) == 0) ||
                       (iVar11 = EXE_SearchInv(iVar15,0x52,(char)G_WHATPLA,
                                            (char)&G_IINFO), iVar11 != 0)) {
                      ovl_07e5();
                    }
                    else {
                      ovl_07e5();
                    }
                    ovl_0813();
                  }
                }
                else {
                  uVar20 = (undefined1)iVar15;
                  if (cVar8 == '\x01') {
                    if (G_CURCOND1 == 0) {
                      iVar11 = *(int *)(unaff_SI + G_WHATPLA * 2 + 0x2b26);
                      if ((char)*(undefined2 *)(iVar11 + 0xa7) == '\0') {
                        bVar9 = *(byte *)(iVar11 + 0xd7);
                        uVar12 = (uint)bVar9;
                        G_WHATITEM = uVar12;
                        if (*(byte *)(iVar11 + uVar12 + 0x7b) < 99) {
                          pcVar2 = (char *)(iVar11 + uVar12 + 0x7b);
                          *pcVar2 = *pcVar2 + '\x01';
                        }
                        uVar10 = (undefined1)iVar18;
                        uStack_1 = (undefined1)((uint)iVar18 >> 8);
                        EXE_SetTxtSpell(uVar20,bVar9);
                        puVar7 = (undefined2 *)(CONCAT11(uStack_1,uVar10) + 0x160);
                        uVar20 = EXE_viaptr_puVar7(uVar20,(char)G_WHATITEM
                                                    ,(char)G_WHATPLA);
                        iVar18 = CONCAT11(uStack_1,uVar10);
                        *(undefined1 *)(iVar11 + 0xa7) = uVar20;
                        ovl_0fda();
                      }
                      else {
                        *(char *)(iVar11 + 0xa7) = *(char *)(iVar11 + 0xa7) + -1;
                      }
                    }
                    else {
                      ovl_1061();
                    }
                  }
                  else if (cVar8 == '\x03') {
                    if (unaff_SI[-0x636f] == 0) {
                      if ((*unaff_SI == 0) || (*unaff_SI == 0x1e)) {
                        uVar14 = EXE_RndCo(uVar20,100);
                        G_DICEROLL = uVar14;
                        unaff_SI[-0x6375] =
                             (byte)(*(uint *)(*(int *)(unaff_SI +
                                                      G_WHATPLA * 2 + 0x2b26) +
                                             0x28) >> 1) & 0x7f;
                        cVar8 = *(char *)((uint)unaff_SI[0x273d] + &OV_0x103);
                        iVar15 = 0x1000;
                        cVar5 = *(char *)(G_weather + &OV_0x10d);
                        if (((cVar8 != -1) &&
                            ((cVar5 != -1 &&
                             (bVar9 = cVar8 + cVar5 + unaff_SI[-0x6375], -1 < (char)bVar9)))) &&
                           (unaff_SI[-0x6371] <= bVar9)) {
                          EXE_IncObj(0,(char)*(undefined2 *)
                                              (unaff_SI + G_WHATPLA * 2 + 0x2b26)
                                     ,0x31,1);
                          ovl_0fda();
                          EXE_Wait(0);
                          EXE_ClrTxtWnd();
                          EXE_InitScrap();
                          unaff_SI[-0x76da] = 0x11;
                          G_curpla = G_WHATPLA;
                          uVar20 = 0;
                          EXE_SkillUp0();
                          G_curpla = iVar18;
                          iVar18 = CONCAT11(0x10,uVar20);
                        }
                      }
                    }
                    else {
                      ovl_1061();
                    }
                  }
                  else if (cVar8 == '\x06') {
                    if (G_CURCOND1 == 0) {
                      ovl_0849();
                      iVar11 = 100;
                      uVar14 = EXE_RndCo(uVar20);
                      G_DICEROLL = uVar14;
                      if (unaff_SI[-0x6371] <=
                          (byte)*(undefined2 *)
                                 (*(int *)(unaff_SI + G_WHATPLA * 2 + 0x2b26) +
                                 0x25)) {
                        ovl_0849();
                      }
                      iVar18 = iVar11;
                    }
                    else {
                      ovl_1061();
                    }
                  }
                  else if (unaff_SI[-0x636f] != 0) {
                    ovl_1061();
                  }
                }
              }
              pbVar4 = &G_WHATPLA;
              *(int *)pbVar4 = *(int *)pbVar4 + -1;
            } while (-1 < *(int *)pbVar4);
            uVar20 = (undefined1)iVar15;
            EXE_CalUpd(uVar20);
            if ((unaff_SI[-0x638a] & 2) != 0) {
              G_crossovlycall = *(int *)(iVar18 + 0x14c) + 6;
              G_crossovlycall+2 = *(undefined2 *)(iVar18 + 0x14e);
              EXE_crossovlycall();
              G_crossovlycall = *(int *)(iVar18 + 0x14c) + 9;
              G_crossovlycall+2 = *(undefined2 *)(iVar18 + 0x14e);
              EXE_crossovlycall();
              if (G_docmbt != 0) {
                EXE_ClrMnuWnd(uVar20);
                goto L_046b;
              }
            }
            if ((unaff_SI[-0x638a] & 4) != 0) {
              return;
            }
            iVar11 = EXE_HandleMouse(uVar20,0,1);
            if ((iVar11 != 0) ||
               (iVar11 = EXE_ReadKbd(uVar20,0), iVar11 != 0)) break;
            LOCK();
            pcVar3 = *(char **)&G_RENTPTR;
            G_RENTPTR = iVar18;
            UNLOCK();
            cVar8 = *pcVar3;
            LOCK();
            iVar18 = G_RENTPTR;
            *(char **)&G_RENTPTR = pcVar3;
            UNLOCK();
            if ((pcVar3 != (char *)0x0) && (cVar8 == '\0')) goto L_046b;
          }
          EXE_ClrTxtWnd(uVar20);
          goto L_0306;
        }
      }
      else if ((((unaff_SI[-0x638a] & 4) != 0) && (uVar12 = uVar12 - 0x31, uVar12 < 9)) &&
              (uVar12 != 4)) {
        uVar12 = uVar12 * 3 + 0xc;
        bVar9 = CARRY2(uVar12,*(uint *)(iVar18 + 0x14c));
        G_crossovlycall = uVar12 + *(uint *)(iVar18 + 0x14c);
        G_crossovlycall+2 = *(undefined2 *)(iVar18 + 0x14e);
        EXE_crossovlycall();
        if ((bVar9 & 1) == 0) {
          G_crossovlycall = *(int *)(iVar18 + 0x14c) + 0x18;
          G_crossovlycall+2 = *(undefined2 *)(iVar18 + 0x14e);
          EXE_crossovlycall();
          goto SUB_1ca8_04d4;
        }
        if (unaff_SI[-0x7b62] == 0) {
L_046b:
          iVar15 = 6;
          iVar18 = 0;
          do {
            if (*(int *)(unaff_SI + iVar18 + 0x21) != 0xff) {
              *(undefined1 *)(*(int *)(unaff_SI + iVar18 + 0x2b26) + 0xb9) = 0xff;
            }
            iVar18 = iVar18 + 2;
            iVar15 = iVar15 + -1;
          } while (iVar15 != 0);
          unaff_SI[-0x7b62] = 0;
          if ((unaff_SI[-0x638a] & 0x30) != 0) {
            ovl_11b3();
          }
          ovl_0ca4();
          return;
        }
      }
      goto L_0324;
    }
    if (uVar12 == 5) {
      iVar11 = ovl_0cdf();
      if (iVar11 != 0) {
        iVar11 = EXE_ListSel(uVar20,(char)iVar11,(char)&OV_0xeb2);
        if (iVar11 != -1) {
          ovl_0dfd();
          *(undefined1 *)
           (*(int *)(unaff_SI + G_curpla * 2 + 0x2b26) + iVar18 + 0xc0) = 0xff;
          ovl_0fda();
        }
        goto L_0296;
      }
L_0d68:
      ovl_0fda();
      EXE_GameSound();
      iVar18 = iVar15;
      goto L_0324;
    }
    ovl_11e7();
    iVar11 = EXE_ChkMag();
    bVar21 = false;
    if (iVar11 == 0) {
      EXE_IComTxt(uVar20);
      iVar18 = 0x2d;
      goto L_0324;
    }
    ovl_100d();
    if (bVar21) {
      ovl_0fda();
      iVar17 = iVar18;
    }
    else {
      iVar16 = 0;
      iVar11 = 0x53;
      do {
        iVar17 = EXE_SearchInv(iVar15,(char)iVar11,(char)G_curpla,
                            (char)&G_BOOKINV);
        if (iVar17 != 0) {
          ovl_0a15();
          iVar11 = extraout_DX_01;
        }
        iVar11 = iVar11 + 1;
      } while ((byte)iVar11 < 0x5a);
      if (iVar16 == 0) {
        ovl_0fda();
        iVar17 = iVar18;
      }
      else {
        iVar17 = &OV_0xb48;
        iVar18 = EXE_ListSel(uVar20,(char)iVar16);
        if (iVar18 != -1) {
          bVar9 = unaff_SI[iVar18 + -0x74b2];
          G_WHATITEM = (uint)bVar9;
          EXE_slot0xca4(uVar20,bVar9);
          iVar18 = *(int *)(unaff_SI + G_curpla * 2 + 0x2b26);
          *(undefined1 *)(iVar18 + 0xd7) = (char)G_WHATITEM;
          *(undefined1 *)(iVar18 + 0xb9) = 1;
          uVar22 = (undefined1)iVar17;
          uStack_1 = (undefined1)((uint)iVar17 >> 8);
          uVar10 = EXE_slot0xca8(uVar20,(char)G_WHATITEM,
                              (char)G_curpla);
          iVar17 = CONCAT11(uStack_1,uVar22);
          *(undefined1 *)(iVar18 + 0xa7) = uVar10;
          ovl_0fda();
        }
      }
    }
  }
L_0296:
  if ((unaff_SI[-0x638a] & 6) == 0) {
    EXE_InitMap(uVar20);
    EXE_FillWindow(uVar20,(char)G_winxy,
               (char)((uint)G_winxy >> 8));
    iVar18 = iVar17;
    if ((unaff_SI[-0x638a] & 0x30) != 0) {
      ovl_0c23();
      iVar18 = iVar17;
    }
  }
  else {
    EXE_InitMap(uVar20);
    G_crossovlycall = *(int *)(iVar17 + 0x14c) + 3;
    G_crossovlycall+2 = *(undefined2 *)(iVar17 + 0x14e);
    EXE_crossovlycall();
    G_crossovlycall = *(int *)(iVar17 + 0x14c) + 0x30;
    G_crossovlycall+2 = *(undefined2 *)(iVar17 + 0x14e);
    EXE_crossovlycall();
    iVar18 = iVar17;
  }
  goto L_0306;
}


