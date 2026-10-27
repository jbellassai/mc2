// ===== ovl_00b3 @ 1ca8:00b3

void ovl_00b3(void)

{
  ovl_0fa9();
  return;
}


// ===== ovl_00b7 @ 1ca8:00b7

void ovl_00b7(void)

{
  ovl_0828();
  return;
}


// ===== ovl_00bb @ 1ca8:00bb

void ovl_00bb(void)

{
  ovl_0a87();
  return;
}


// ===== ovl_00bf @ 1ca8:00bf

void ovl_00bf(void)

{
  ovl_0343();
  return;
}


// ===== ovl_00c3 @ 1ca8:00c3

void ovl_00c3(void)

{
  ovl_035a();
  return;
}


// ===== ovl_00c7 @ 1ca8:00c7

void ovl_00c7(void)

{
  ovl_03d5();
  return;
}


// ===== ovl_00cb @ 1ca8:00cb

void ovl_00cb(void)

{
  ovl_10a7();
  return;
}


// ===== ovl_00cf @ 1ca8:00cf

void ovl_00cf(void)

{
  ovl_1033();
  return;
}


// ===== ovl_00d3 @ 1ca8:00d3

void ovl_00d3(void)

{
  ovl_0ed8();
  return;
}


// ===== ovl_00d7 @ 1ca8:00d7

void ovl_00d7(void)

{
  ovl_0828();
  return;
}


// ===== ovl_00db @ 1ca8:00db

void ovl_00db(void)

{
  ovl_03d0();
  return;
}


// ===== ovl_00df @ 1ca8:00df

void ovl_00df(void)

{
  ovl_114d();
  return;
}


// ===== ovl_00e3 @ 1ca8:00e3

void ovl_00e3(void)

{
  ovl_1093();
  return;
}


// ===== ovl_00e7 @ 1ca8:00e7

void ovl_00e7(void)

{
  ovl_1144();
  return;
}


// ===== ovl_00eb @ 1ca8:00eb

void ovl_00eb(void)

{
  ovl_090d();
  return;
}


// ===== ovl_00ef @ 1ca8:00ef

void ovl_00ef(void)

{
  ovl_06b7();
  return;
}


// ===== ovl_00f3 @ 1ca8:00f3

void ovl_00f3(void)

{
  ovl_0b2b();
  return;
}


// ===== ovl_00f7 @ 1ca8:00f7

void ovl_00f7(void)

{
  ovl_09ed();
  return;
}


// ===== ovl_00fb @ 1ca8:00fb

void ovl_00fb(void)

{
  ovl_05db();
  return;
}


// ===== ovl_00ff @ 1ca8:00ff

void ovl_00ff(void)

{
  ovl_0adb();
  return;
}


// ===== ovl_0103 @ 1ca8:0103

void ovl_0103(void)

{
  undefined2 unaff_DS;
  code *in_stack_00000000;
  
  *(undefined2 *)(*piRam000004fc + -0x728a) = piRam000004fc;
                    /* WARNING: Could not recover jumptable at 0x0001cba5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*in_stack_00000000)();
  return;
}


// ===== ovl_012b @ 1ca8:012b

undefined2 ovl_012b(void)

{
  int iVar1;
  undefined2 uVar2;
  int unaff_BP;
  int unaff_SI;
  undefined2 unaff_SS;
  undefined2 unaff_DS;
  
  ovl_0103();
  uVar2 = 0;
  iVar1 = *(int *)(*(int *)(unaff_BP + 6) * 2 + &G_crecptrs);
  if (((G_curphase != '\x01') || (*(char *)(iVar1 + 0x1e) != '\0')) &&
     ((*(byte *)(iVar1 + 5) & 0xd8) == 0)) {
    uVar2 = 1;
  }
  return uVar2;
}


// ===== ovl_0151 @ 1ca8:0151

void ovl_0151(void)

{
  ovl_0103();
  ovl_0160();
  return;
}


// ===== ovl_015c @ 1ca8:015c

void ovl_015c(void)

{
  ovl_0160();
  return;
}


// ===== ovl_0160 @ 1ca8:0160

void ovl_0160(void)

{
  undefined2 in_AX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  LOCK();
  G_curpla = in_AX;
  UNLOCK();
  ovl_0479();
  G_curatt = G_curpla;
  ovl_0a87();
  ovl_0269();
  ovl_0475();
  EXE_PrtW3();
  EXE_SumStat();
  ovl_034e();
  return;
}


// ===== ovl_018c @ 1ca8:018c

void ovl_018c(void)

{
  ovl_0103();
  ovl_01ab();
  return;
}


// ===== ovl_019a @ 1ca8:019a

void ovl_019a(void)

{
  ovl_01a6();
  return;
}


// ===== ovl_01a6 @ 1ca8:01a6

void ovl_01a6(void)

{
  undefined2 *puVar1;
  undefined1 uVar3;
  int iVar2;
  int iVar4;
  int iVar5;
  uint in_DX;
  int iVar6;
  int unaff_SI;
  undefined2 unaff_DS;
  
  uVar3 = (undefined1)(in_DX >> 8);
  iVar6 = G_savebx;
  G_TILEXY = (char)in_DX;
  G_TILEY = uVar3;
  puVar1 = (undefined2 *)(iVar6 + 0x120);
  EXE_RestBG(in_DX & 0xff,uVar3,iVar6);
  iVar6 = &G_crecs;
  iVar4 = 0x18;
  do {
    if (*(int *)(iVar6 + 1) == G_TILEXY) {
      ovl_0479();
      break;
    }
    iVar6 = iVar6 + 0x21;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar6 = G_savebx;
  if (G_cmbtyp != '\0') {
    iVar5 = 0x1f;
    iVar4 = &G_assgn0;
    do {
      iVar2 = EXE_AssignedHere(iVar4);
      if ((iVar2 != 0) && (*(int *)(iVar4 + 3) == G_TILEXY)) {
        EXE_NPCDraw();
        break;
      }
      iVar4 = iVar4 + 0x19;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  ovl_041e();
  if (*(char *)(iVar6 + &G_globemap) != '\0') {
    ovl_042f();
  }
  return;
}


// ===== ovl_01ab @ 1ca8:01ab

void ovl_01ab(void)

{
  undefined2 *puVar1;
  undefined1 in_AL;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 in_DL;
  int iVar5;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar5 = G_savebx;
  G_TILEXY = in_AL;
  G_TILEY = in_DL;
  puVar1 = (undefined2 *)(iVar5 + 0x120);
  EXE_RestBG();
  iVar5 = &G_crecs;
  iVar3 = 0x18;
  do {
    if (*(int *)(iVar5 + 1) == G_TILEXY) {
      ovl_0479();
      break;
    }
    iVar5 = iVar5 + 0x21;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar5 = G_savebx;
  if (G_cmbtyp != '\0') {
    iVar4 = 0x1f;
    iVar3 = &G_assgn0;
    do {
      iVar2 = EXE_AssignedHere(iVar3);
      if ((iVar2 != 0) && (*(int *)(iVar3 + 3) == G_TILEXY)) {
        EXE_NPCDraw();
        break;
      }
      iVar3 = iVar3 + 0x19;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  ovl_041e();
  if (*(char *)(iVar5 + &G_globemap) != '\0') {
    ovl_042f();
  }
  return;
}


// ===== ovl_023d @ 1ca8:023d

void ovl_023d(void)

{
  ovl_0103();
  ovl_025f();
  return;
}


// ===== ovl_024a @ 1ca8:024a

void ovl_024a(void)

{
  ovl_0103();
  ovl_0269();
  return;
}


// ===== ovl_0257 @ 1ca8:0257

void ovl_0257(void)

{
  ovl_0269();
  return;
}


// ===== ovl_025b @ 1ca8:025b

void ovl_025b(void)

{
  ovl_025f();
  return;
}


// ===== ovl_025f @ 1ca8:025f

uint ovl_025f(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  uint in_AX;
  int iVar3;
  int unaff_SI;
  undefined2 *puVar4;
  undefined2 *puVar5;
  undefined2 unaff_DS;
  
  puVar5 = (undefined2 *)&G_rec2;
  *(undefined1 *)puVar5 = 0x11;
  puVar4 = (undefined2 *)*(undefined2 *)(unaff_SI + in_AX * 2 + -0x7a70);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
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
  return in_AX & 0x7fff;
}


// ===== ovl_0269 @ 1ca8:0269

uint ovl_0269(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  uint in_AX;
  int iVar3;
  int unaff_SI;
  undefined2 *puVar4;
  undefined2 *puVar5;
  undefined2 unaff_DS;
  
  puVar5 = (undefined2 *)&G_rec1;
  puVar4 = (undefined2 *)*(undefined2 *)(unaff_SI + in_AX * 2 + -0x7a70);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
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
  return in_AX & 0x7fff;
}


// ===== ovl_0289 @ 1ca8:0289

void ovl_0289(void)

{
  ovl_0103();
  ovl_02a9();
  return;
}


// ===== ovl_0292 @ 1ca8:0292

void ovl_0292(void)

{
  ovl_0103();
  ovl_02a3();
  return;
}


// ===== ovl_029b @ 1ca8:029b

void ovl_029b(void)

{
  ovl_02a9();
  return;
}


// ===== ovl_029f @ 1ca8:029f

void ovl_029f(void)

{
  ovl_02a3();
  return;
}


// ===== ovl_02a3 @ 1ca8:02a3

void ovl_02a3(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  int unaff_SI;
  undefined2 *puVar4;
  undefined2 *puVar5;
  undefined2 unaff_DS;
  
  puVar4 = (undefined2 *)&G_rec2;
  puVar5 = (undefined2 *)
           *(undefined2 *)((uint)G_rec2+31 * 2 + &G_crecptrs);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
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
  return;
}


// ===== ovl_02a9 @ 1ca8:02a9

void ovl_02a9(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  int iVar3;
  int unaff_SI;
  undefined2 *puVar4;
  undefined2 *puVar5;
  undefined2 unaff_DS;
  
  puVar4 = (undefined2 *)&G_rec1;
  puVar5 = (undefined2 *)
           *(undefined2 *)((uint)G_rec1+31 * 2 + &G_crecptrs);
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
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
  return;
}


// ===== ovl_02d5 @ 1ca8:02d5

void ovl_02d5(void)

{
  ovl_0103();
  ovl_030b();
  return;
}


// ===== ovl_02de @ 1ca8:02de

void ovl_02de(void)

{
  ovl_02e2();
  return;
}


// ===== ovl_02e2 @ 1ca8:02e2

void ovl_02e2(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_rec1+31 < '\x06') {
    ovl_0343();
  }
  ovl_02a9();
  return;
}


// ===== ovl_02fd @ 1ca8:02fd

void ovl_02fd(void)

{
  ovl_0305();
  return;
}


// ===== ovl_0301 @ 1ca8:0301

void ovl_0301(void)

{
  ovl_030b();
  return;
}


// ===== ovl_0305 @ 1ca8:0305

void ovl_0305(void)

{
  int iVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_rec1+31 < 6) {
    iVar1 = *(int *)((uint)G_rec1+31 * 2 + &G_heroptr);
    *(undefined1 *)(iVar1 + 0xbd) = G_rec1;
    *(undefined1 *)(iVar1 + 0xca) = G_rec1+10;
    *(undefined1 *)(iVar1 + 0xbb) = G_rec1+12;
    *(undefined1 *)(iVar1 + 0xba) = G_rec1+13;
  }
  return;
}


// ===== ovl_030b @ 1ca8:030b

void ovl_030b(void)

{
  int iVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_rec2+31 < 6) {
    iVar1 = *(int *)((uint)G_rec2+31 * 2 + &G_heroptr);
    *(undefined1 *)(iVar1 + 0xbd) = G_rec2;
    *(undefined1 *)(iVar1 + 0xca) = G_rec2+10;
    *(undefined1 *)(iVar1 + 0xbb) = G_rec2+12;
    *(undefined1 *)(iVar1 + 0xba) = G_rec2+13;
  }
  return;
}


// ===== ovl_0343 @ 1ca8:0343

void ovl_0343(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_034a @ 1ca8:034a

void ovl_034a(void)

{
  ovl_034e();
  return;
}


// ===== ovl_034e @ 1ca8:034e

void ovl_034e(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x50);
  EXE_PageFlip(G_savebx);
  return;
}


// ===== ovl_035a @ 1ca8:035a

void ovl_035a(void)

{
  return;
}


// ===== ovl_035b @ 1ca8:035b

void ovl_035b(void)

{
  return;
}


// ===== ovl_035c @ 1ca8:035c

void ovl_035c(void)

{
  code *pcVar1;
  
  ovl_0103();
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_0387 @ 1ca8:0387

void __cdecl16far ovl_0387(void)

{
  ovl_03a1();
  return;
}


// ===== ovl_0394 @ 1ca8:0394

void __cdecl16near ovl_0394(void)

{
  ovl_03a1();
  return;
}


// ===== ovl_03a1 @ 1ca8:03a1

void __cdecl16near ovl_03a1(void)

{
  return;
}


// ===== ovl_03c7 @ 1ca8:03c7

void ovl_03c7(void)

{
  ovl_03cb();
  return;
}


// ===== ovl_03cb @ 1ca8:03cb

void ovl_03cb(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_03d0 @ 1ca8:03d0

void ovl_03d0(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_03d5 @ 1ca8:03d5

undefined2 ovl_03d5(void)

{
  undefined2 *puVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if ((G_zp_1415 < 0xb) && (G_zp_15 < 9)) {
    iVar4 = &G_crecs;
    iVar3 = 0x18;
    do {
      if (*(int *)(iVar4 + 1) == G_zp_1415) goto L_0405;
      iVar4 = iVar4 + 0x21;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    puVar1 = (undefined2 *)(G_savebx + 0xc4);
    uVar2 = EXE_ChkWlk(G_savebx);
  }
  else {
L_0405:
    uVar2 = 0;
  }
  return uVar2;
}


// ===== ovl_040a @ 1ca8:040a

void ovl_040a(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_0419 @ 1ca8:0419

void ovl_0419(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_041e @ 1ca8:041e

void ovl_041e(void)

{
  return;
}


// ===== ovl_042f @ 1ca8:042f

void ovl_042f(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_0434 @ 1ca8:0434

void ovl_0434(void)

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


// ===== ovl_0468 @ 1ca8:0468

void ovl_0468(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xd0);
  EXE_GameSound();
  return;
}


// ===== ovl_0475 @ 1ca8:0475

void ovl_0475(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x100);
  EXE_PDraw(G_curpla);
  return;
}


// ===== ovl_0479 @ 1ca8:0479

void ovl_0479(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x100);
  EXE_PDraw();
  return;
}


// ===== ovl_0486 @ 1ca8:0486

void ovl_0486(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x178);
  EXE_PrtWrd(G_comtxtptr);
  return;
}


// ===== ovl_049a @ 1ca8:049a

void ovl_049a(void)

{
  undefined2 *puVar1;
  uint in_AX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x124);
  EXE_Wait((int)((in_AX & 0xff) * (uint)G_UserDelay) >> 2);
  return;
}


// ===== ovl_04af @ 1ca8:04af

void ovl_04af(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x134);
  EXE_RndCo();
  return;
}


// ===== ovl_04bc @ 1ca8:04bc

void ovl_04bc(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x1d0);
  EXE_SetName(G_curtar);
  return;
}


// ===== ovl_04c0 @ 1ca8:04c0

void ovl_04c0(void)

{
  undefined2 *puVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0x1d0);
  EXE_SetName();
  return;
}


// ===== ovl_04fd @ 1ca8:04fd

void ovl_04fd(void)

{
  ovl_0103();
  ovl_050a();
  return;
}


// ===== ovl_0506 @ 1ca8:0506

void ovl_0506(void)

{
  ovl_050a();
  return;
}


// ===== ovl_050a @ 1ca8:050a

void ovl_050a(void)

{
  undefined2 *puVar1;
  char *pcVar2;
  undefined2 *puVar3;
  code *pcVar4;
  char cVar5;
  byte bVar6;
  undefined2 uVar7;
  int iVar8;
  uint uVar9;
  undefined1 uVar10;
  int extraout_DX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar11;
  undefined1 uVar12;
  undefined2 in_stack_0000000c;
  int iStack0014;
  
  if (G_swauto != 0) {
    G_zp_1415 = G_rec2+1;
    return;
  }
  ovl_09ed();
  if ((G_rec1 & 0xf0) != 0) {
    return;
  }
  ovl_01a6();
  ovl_034e();
  if (G_rec1+7 == -1) {
L_0585:
    uVar10 = G_rec1+1;
    iStack0014 = in_BX;
  }
  else {
    ovl_025f();
    uVar10 = G_rec2+1;
    uVar12 = G_rec2+2;
    iStack0014 = in_BX;
    if (G_swcast == '\0') {
      uVar7 = 1;
      if (0x19 < G_rec1+15) {
        uVar7 = 100;
      }
      G_wrkamt = uVar7;
      iVar8 = EXE_ChkRng(uVar10,uVar12,G_wrkamt,0);
      if (iVar8 != 1) goto L_0585;
    }
  }
  iVar8 = EXE_Target(uVar10);
  if (iVar8 == -1) {
    return;
  }
  uVar7 = CONCAT11(G_worky,G_workx);
  G_TILEXY = uVar7;
  G_zp_1415 = uVar7;
  iVar8 = ovl_03d0();
  if (G_swcast == '\0') {
    if (iVar8 != 0x18) {
      if ((char)iVar8 == G_rec1+31) {
        return;
      }
      goto ovl_05db;
    }
    G_curtar = 0x18;
    G_TARHEROPTR = 0;
  }
  else {
ovl_05db:
    G_curtar = iVar8;
    if (iVar8 != 0x18) {
      uVar12 = ovl_025f();
      if (((G_swcast == '\0') || (G_rec2+14 == '\0')) ||
         (G_rec2+31 == G_curpla)) {
        if (((G_rec2+4 == '\0') && (G_rec1+4 == '\0')) &&
           ((G_swauto != 1 &&
            ((G_swcast == '\0' || (G_offense == 1)))))) {
          EXE_ClrTxtWnd();
          EXE_InitScrap();
          EXE_AddScrap(G_comtxtptr);
          EXE_PrtScrap();
          iVar8 = EXE_SetYN();
          if (iVar8 != 0) {
            return;
          }
        }
        ovl_0abd();
        if (G_rec2+14 == '\0') {
          G_rec1+7 = uVar12;
          G_rec1+8 = G_TILEXY;
        }
      }
      else {
        G_curtar = 0x18;
      }
    }
    if (G_swcast != '\0') {
      return;
    }
  }
  iVar8 = ovl_0a2b();
  if (iVar8 < 3) {
    iVar8 = EXE_ChkRng();
    if (iVar8 != 1) {
      return;
    }
    EXE_SetTxtWnd();
    G_zp_12 = G_rec1+1;
    ovl_0b2b();
    ovl_0cde();
    if (G_curtar != 0x18) {
      ovl_02a3();
    }
    G_zp_10 = in_stack_0000000c;
    G_rec1+14 = 0;
    ovl_02a9();
    ovl_09df();
    ovl_034e();
    ovl_0468();
    cVar5 = G_ARESULT;
    if (((cVar5 != '\0') && (cVar5 != '\x04')) && (cVar5 != '\x03')) {
      if (G_rec1+3 == '\x12') {
        ovl_0468();
        puVar1 = (undefined2 *)(iStack0014 + 0x358);
        iStack0014 = 0x1ca8;
        EXE_Spef2();
      }
      ovl_0468();
    }
    ovl_049a();
    ovl_09e8();
    if (G_curtar != 0x18) {
      uVar7 = G_wpnt;
      cVar5 = ovl_0a20();
      G_wpnt = uVar7;
      if ((cVar5 < '\x03') && (bVar6 = ovl_04af(), G_rec2+22 < bVar6)) {
        G_rec2+7 = (char)G_curatt;
        G_rec2+8 = G_rec1+1;
        G_rec2+5 = G_rec2+5 & 0xbf;
      }
    }
  }
  else {
    iVar8 = ovl_09ac();
    if (iVar8 != 0) {
      return;
    }
    if (G_curatt < 6) {
      iVar8 = EXE_SearchInv();
      if (iVar8 != 1) {
        ovl_0434();
        return;
      }
      EXE_DecObj0();
    }
    ovl_0468();
    if (G_wpnt != 3) {
      G_zp_12 = G_rec1+1;
      ovl_0b2b();
      ovl_09df();
      ovl_034e();
    }
    if (G_wpnt != 3) {
      pcVar4 = INT_0x61_handler;
      (*pcVar4)();
    }
    ovl_1144();
    ovl_049a();
    if (G_wpnt != 3) {
      ovl_09e8();
      ovl_034e();
    }
    if (G_curtar != 0x18) {
      ovl_1033();
    }
    if (G_ARESULT == -1) {
      ovl_0419();
      ovl_040a();
    }
  }
  ovl_034e();
  bVar6 = G_ARESULT;
  if (((bVar6 == 0) || (bVar6 == 3)) || (bVar11 = bVar6 < 4, bVar6 == 4)) {
    puVar3 = (undefined2 *)(G_savebx + 0x5c);
    EXE_ClrTxtWnd();
    goto L_08af;
  }
  ovl_14b2();
  if (bVar11) {
    ovl_0adb();
    return;
  }
  uVar12 = G_curatt < 6;
  if ((int)G_curatt < 6) {
    EXE_SkillUp();
    uVar12 = G_rec1+15 != -1;
    if ((G_rec1+15 != -1) && (ovl_0a63(), !(bool)uVar12)) {
      uVar12 = 0;
      if (G_ATTWEAPPTR != 0) {
        uVar9 = *(byte *)(G_ATTWEAPPTR + 0x28) & 0xff7f;
        bVar6 = (byte)uVar9;
        iVar8 = iStack0014;
        if (bVar6 < 0x5a) {
          uVar12 = bVar6 < 0x19;
          if (0x18 < bVar6) {
            bVar6 = ovl_04af();
            uVar12 = (byte)(uVar9 >> 1) < bVar6;
            iVar8 = iStack0014;
            if (!(bool)uVar12) goto L_07e0;
          }
        }
        else {
L_07e0:
          *(undefined1 *)(G_ATTWEAPPTR + 0x28) = 0xe2;
          G_suppresstext = 1;
          EXE_Sheathe();
          G_suppresstext = 0;
          ovl_0486();
          uVar12 = G_cursorx < G_txtww;
          if (!(bool)uVar12) {
            EXE_MyRet();
            EXE_MyRet();
          }
          iStack0014 = G_UserDelay;
          EXE_AutoPause();
        }
      }
    }
  }
  ovl_14b2();
  if ((bool)uVar12) {
    ovl_0adb();
    return;
  }
  ovl_0bc2();
  G_rec2+5 = G_rec2+5 & 0xfe;
  if (G_ARESULT == -1) {
    G_rec2 = 0x80;
    G_rec2+5 = G_rec2+5 & 2;
    G_rec2+5 = G_rec2+5 | 0x80;
    G_rec2+13 = 0;
    G_rec2+30 = G_GLOBEHIT;
    EXE_FirsTil();
    *(undefined1 *)(G_curtar + &G_pltilno) =
         *(undefined1 *)(extraout_DX + 5);
    if (G_rec2+3 == '\x1e') {
      pcVar4 = INT_0x61_handler;
      (*pcVar4)();
      goto L_08af;
    }
    if (G_curtar < 6) {
      G_rec2+4 = 0;
      ovl_09d1();
    }
  }
  ovl_02a3();
  ovl_030b();
  ovl_01a6();
  ovl_034e();
L_08af:
  if (G_ARESULT == -1) {
    ovl_0adb();
  }
  if ((G_swcast == '\0') && (G_curatt < 6)) {
    iVar8 = G_ATTHEROPTR;
    pcVar2 = (char *)(iVar8 + 0xba);
    *pcVar2 = *pcVar2 + -2;
    if (*pcVar2 < '\0') {
      *(undefined1 *)(iVar8 + 0xba) = 0;
    }
    puVar3 = (undefined2 *)(G_savebx + 0xd4);
    EXE_IsHeTr();
    ovl_02e2();
    if ((G_ARESULT != '\x04') && (G_ARESULT != '\0')) {
      ovl_0a6e();
    }
  }
  return;
}


// ===== ovl_05db @ 1ca8:05db

void ovl_05db(undefined2 param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  char *pcVar2;
  undefined2 uVar3;
  undefined2 *puVar4;
  code *pcVar5;
  char cVar6;
  byte bVar7;
  int in_AX;
  int iVar8;
  uint uVar9;
  int extraout_DX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar10;
  undefined1 uVar11;
  int iStack000c;
  
  G_curtar = in_AX;
  iStack000c = in_BX;
  if (in_AX != 0x18) {
    uVar11 = ovl_025f();
    if (((G_swcast == '\0') || (G_rec2+14 == '\0')) ||
       (G_rec2+31 == G_curpla)) {
      if (((G_rec2+4 == '\0') && (G_rec1+4 == '\0')) &&
         ((G_swauto != 1 &&
          ((G_swcast == '\0' || (G_offense == 1)))))) {
        EXE_ClrTxtWnd();
        EXE_InitScrap();
        EXE_AddScrap(G_comtxtptr);
        EXE_PrtScrap(0xff);
        iVar8 = EXE_SetYN();
        if (iVar8 != 0) {
          return;
        }
      }
      ovl_0abd();
      iStack000c = in_BX;
      if (G_rec2+14 == '\0') {
        G_rec1+7 = uVar11;
        G_rec1+8 = G_TILEXY;
      }
    }
    else {
      G_curtar = 0x18;
      iStack000c = in_BX;
    }
  }
  if (G_swcast != '\0') {
    return;
  }
  iVar8 = ovl_0a2b();
  if (iVar8 < 3) {
    iVar8 = EXE_ChkRng(G_zp_1415 & 0xff,
                       G_zp_1415 >> 8,1,1);
    if (iVar8 != 1) {
      return;
    }
    EXE_SetTxtWnd(1);
    G_zp_12 = G_rec1+1;
    ovl_0b2b();
    ovl_0cde();
    if (G_curtar != 0x18) {
      ovl_02a3();
    }
    G_zp_10 = param_2;
    G_rec1+14 = 0;
    ovl_02a9();
    ovl_09df();
    ovl_034e();
    ovl_0468();
    cVar6 = G_ARESULT;
    if (((cVar6 != '\0') && (cVar6 != '\x04')) && (cVar6 != '\x03')) {
      if (G_rec1+3 == '\x12') {
        ovl_0468();
        puVar1 = (undefined2 *)(iStack000c + 0x358);
        iStack000c = 0x1ca8;
        EXE_Spef2();
      }
      ovl_0468();
    }
    ovl_049a();
    ovl_09e8();
    if (G_curtar != 0x18) {
      uVar3 = G_wpnt;
      cVar6 = ovl_0a20();
      G_wpnt = uVar3;
      if ((cVar6 < '\x03') && (bVar7 = ovl_04af(), G_rec2+22 < bVar7)) {
        G_rec2+7 = (char)G_curatt;
        G_rec2+8 = G_rec1+1;
        G_rec2+5 = G_rec2+5 & 0xbf;
      }
    }
  }
  else {
    iVar8 = ovl_09ac();
    if (iVar8 != 0) {
      return;
    }
    if (G_curatt < 6) {
      iVar8 = EXE_SearchInv(0x51,G_curatt,&G_invinfobuf);
      if (iVar8 != 1) {
        ovl_0434();
        return;
      }
      EXE_DecObj0(0x51);
    }
    ovl_0468();
    if (G_wpnt != 3) {
      G_zp_12 = G_rec1+1;
      ovl_0b2b();
      ovl_09df();
      ovl_034e();
    }
    if (G_wpnt != 3) {
      pcVar5 = INT_0x61_handler;
      (*pcVar5)();
    }
    ovl_1144();
    ovl_049a();
    if (G_wpnt != 3) {
      ovl_09e8();
      ovl_034e();
    }
    if (G_curtar != 0x18) {
      ovl_1033();
    }
    if (G_ARESULT == -1) {
      ovl_0419();
      ovl_040a();
    }
  }
  ovl_034e();
  bVar7 = G_ARESULT;
  if (((bVar7 == 0) || (bVar7 == 3)) || (bVar10 = bVar7 < 4, bVar7 == 4)) {
    puVar4 = (undefined2 *)(G_savebx + 0x5c);
    EXE_ClrTxtWnd();
    goto L_08af;
  }
  ovl_14b2();
  if (bVar10) {
    ovl_0adb();
    return;
  }
  uVar11 = G_curatt < 6;
  if ((int)G_curatt < 6) {
    EXE_SkillUp();
    uVar11 = G_rec1+15 != -1;
    if ((G_rec1+15 != -1) && (ovl_0a63(), !(bool)uVar11)) {
      uVar11 = 0;
      if (G_ATTWEAPPTR != 0) {
        uVar9 = *(byte *)(G_ATTWEAPPTR + 0x28) & 0xff7f;
        bVar7 = (byte)uVar9;
        iVar8 = iStack000c;
        if (bVar7 < 0x5a) {
          uVar11 = bVar7 < 0x19;
          if (0x18 < bVar7) {
            bVar7 = ovl_04af();
            uVar11 = (byte)(uVar9 >> 1) < bVar7;
            iVar8 = iStack000c;
            if (!(bool)uVar11) goto L_07e0;
          }
        }
        else {
L_07e0:
          *(undefined1 *)(G_ATTWEAPPTR + 0x28) = 0xe2;
          G_suppresstext = 1;
          EXE_Sheathe();
          G_suppresstext = 0;
          ovl_0486();
          uVar11 = G_cursorx < G_txtww;
          if (!(bool)uVar11) {
            EXE_MyRet();
            EXE_MyRet();
          }
          iStack000c = G_UserDelay;
          EXE_AutoPause();
        }
      }
    }
  }
  ovl_14b2();
  if ((bool)uVar11) {
    ovl_0adb();
    return;
  }
  ovl_0bc2();
  G_rec2+5 = G_rec2+5 & 0xfe;
  if (G_ARESULT == -1) {
    G_rec2 = 0x80;
    G_rec2+5 = G_rec2+5 & 2;
    G_rec2+5 = G_rec2+5 | 0x80;
    G_rec2+13 = 0;
    G_rec2+30 = G_GLOBEHIT;
    EXE_FirsTil();
    *(undefined1 *)(G_curtar + &G_pltilno) =
         *(undefined1 *)(extraout_DX + 5);
    if (G_rec2+3 == '\x1e') {
      pcVar5 = INT_0x61_handler;
      (*pcVar5)();
      goto L_08af;
    }
    if (G_curtar < 6) {
      G_rec2+4 = 0;
      ovl_09d1();
    }
  }
  ovl_02a3();
  ovl_030b();
  ovl_01a6();
  ovl_034e();
L_08af:
  if (G_ARESULT == -1) {
    ovl_0adb();
  }
  if ((G_swcast == '\0') && (G_curatt < 6)) {
    iVar8 = G_ATTHEROPTR;
    pcVar2 = (char *)(iVar8 + 0xba);
    *pcVar2 = *pcVar2 + -2;
    if (*pcVar2 < '\0') {
      *(undefined1 *)(iVar8 + 0xba) = 0;
    }
    puVar4 = (undefined2 *)(G_savebx + 0xd4);
    EXE_IsHeTr();
    ovl_02e2();
    if ((G_ARESULT != '\x04') && (G_ARESULT != '\0')) {
      ovl_0a6e();
    }
  }
  return;
}


// ===== ovl_06b7 @ 1ca8:06b7

void ovl_06b7(undefined2 param_1)

{
  undefined2 *puVar1;
  char *pcVar2;
  undefined2 uVar3;
  undefined2 *puVar4;
  code *pcVar5;
  char cVar6;
  byte bVar7;
  uint uVar8;
  int extraout_DX;
  int in_BX;
  int iVar9;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar10;
  undefined1 uVar11;
  int iStack000a;
  
  EXE_SetTxtWnd(1);
  G_zp_12 = G_rec1+1;
  ovl_0b2b();
  ovl_0cde();
  iStack000a = in_BX;
  if (G_curtar != 0x18) {
    ovl_02a3();
    iStack000a = in_BX;
  }
  G_zp_10 = param_1;
  G_rec1+14 = 0;
  ovl_02a9();
  ovl_09df();
  ovl_034e();
  ovl_0468();
  cVar6 = G_ARESULT;
  if (((cVar6 != '\0') && (cVar6 != '\x04')) && (cVar6 != '\x03')) {
    if (G_rec1+3 == '\x12') {
      ovl_0468();
      puVar1 = (undefined2 *)(iStack000a + 0x358);
      iStack000a = 0x1ca8;
      EXE_Spef2();
    }
    ovl_0468();
  }
  ovl_049a();
  ovl_09e8();
  if (G_curtar != 0x18) {
    uVar3 = G_wpnt;
    cVar6 = ovl_0a20();
    G_wpnt = uVar3;
    if ((cVar6 < '\x03') && (bVar7 = ovl_04af(), G_rec2+22 < bVar7)) {
      G_rec2+7 = (char)G_curatt;
      G_rec2+8 = G_rec1+1;
      G_rec2+5 = G_rec2+5 & 0xbf;
    }
  }
  ovl_034e();
  bVar7 = G_ARESULT;
  if (((bVar7 == 0) || (bVar7 == 3)) || (bVar10 = bVar7 < 4, bVar7 == 4)) {
    puVar4 = (undefined2 *)(G_savebx + 0x5c);
    EXE_ClrTxtWnd();
    goto L_08af;
  }
  ovl_14b2();
  if (bVar10) {
    ovl_0adb();
    return;
  }
  uVar11 = G_curatt < 6;
  if ((int)G_curatt < 6) {
    EXE_SkillUp();
    uVar11 = G_rec1+15 != -1;
    if ((G_rec1+15 != -1) && (ovl_0a63(), !(bool)uVar11)) {
      uVar11 = 0;
      if (G_ATTWEAPPTR != 0) {
        uVar8 = *(byte *)(G_ATTWEAPPTR + 0x28) & 0xff7f;
        bVar7 = (byte)uVar8;
        iVar9 = iStack000a;
        if (bVar7 < 0x5a) {
          uVar11 = bVar7 < 0x19;
          if (0x18 < bVar7) {
            bVar7 = ovl_04af();
            uVar11 = (byte)(uVar8 >> 1) < bVar7;
            iVar9 = iStack000a;
            if (!(bool)uVar11) goto L_07e0;
          }
        }
        else {
L_07e0:
          *(undefined1 *)(G_ATTWEAPPTR + 0x28) = 0xe2;
          G_suppresstext = 1;
          EXE_Sheathe();
          G_suppresstext = 0;
          ovl_0486();
          uVar11 = G_cursorx < G_txtww;
          if (!(bool)uVar11) {
            EXE_MyRet();
            EXE_MyRet();
          }
          iStack000a = G_UserDelay;
          EXE_AutoPause();
        }
      }
    }
  }
  ovl_14b2();
  if ((bool)uVar11) {
    ovl_0adb();
    return;
  }
  ovl_0bc2();
  G_rec2+5 = G_rec2+5 & 0xfe;
  if (G_ARESULT == -1) {
    G_rec2 = 0x80;
    G_rec2+5 = G_rec2+5 & 2;
    G_rec2+5 = G_rec2+5 | 0x80;
    G_rec2+13 = 0;
    G_rec2+30 = G_GLOBEHIT;
    EXE_FirsTil();
    *(undefined1 *)(G_curtar + &G_pltilno) =
         *(undefined1 *)(extraout_DX + 5);
    if (G_rec2+3 == '\x1e') {
      pcVar5 = INT_0x61_handler;
      (*pcVar5)();
      goto L_08af;
    }
    if (G_curtar < 6) {
      G_rec2+4 = 0;
      ovl_09d1();
    }
  }
  ovl_02a3();
  ovl_030b();
  ovl_01a6();
  ovl_034e();
L_08af:
  if (G_ARESULT == -1) {
    ovl_0adb();
  }
  if ((G_swcast == '\0') && (G_curatt < 6)) {
    iVar9 = G_ATTHEROPTR;
    pcVar2 = (char *)(iVar9 + 0xba);
    *pcVar2 = *pcVar2 + -2;
    if (*pcVar2 < '\0') {
      *(undefined1 *)(iVar9 + 0xba) = 0;
    }
    puVar4 = (undefined2 *)(G_savebx + 0xd4);
    EXE_IsHeTr();
    ovl_02e2();
    if ((G_ARESULT != '\x04') && (G_ARESULT != '\0')) {
      ovl_0a6e();
    }
  }
  return;
}


// ===== ovl_0828 @ 1ca8:0828

void ovl_0828(void)

{
  char *pcVar1;
  int iVar2;
  undefined2 *puVar3;
  code *pcVar4;
  int extraout_DX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined1 in_CF;
  
  ovl_14b2();
  if ((bool)in_CF) {
    ovl_0adb();
    return;
  }
  ovl_0bc2();
  G_rec2+5 = G_rec2+5 & 0xfe;
  if (G_ARESULT == -1) {
    G_rec2 = 0x80;
    G_rec2+5 = G_rec2+5 & 2;
    G_rec2+5 = G_rec2+5 | 0x80;
    G_rec2+13 = 0;
    G_rec2+30 = G_GLOBEHIT;
    EXE_FirsTil();
    *(undefined1 *)(G_curtar + &G_pltilno) =
         *(undefined1 *)(extraout_DX + 5);
    if (G_rec2+3 == '\x1e') {
      pcVar4 = INT_0x61_handler;
      (*pcVar4)();
      goto L_08af;
    }
    if (G_curtar < 6) {
      G_rec2+4 = 0;
      ovl_09d1();
    }
  }
  ovl_02a3();
  ovl_030b();
  ovl_01a6();
  ovl_034e();
L_08af:
  if (G_ARESULT == -1) {
    ovl_0adb();
  }
  if ((G_swcast == '\0') && (G_curatt < 6)) {
    iVar2 = G_ATTHEROPTR;
    pcVar1 = (char *)(iVar2 + 0xba);
    *pcVar1 = *pcVar1 + -2;
    if (*pcVar1 < '\0') {
      *(undefined1 *)(iVar2 + 0xba) = 0;
    }
    puVar3 = (undefined2 *)(G_savebx + 0xd4);
    EXE_IsHeTr();
    ovl_02e2();
    if ((G_ARESULT != '\x04') && (G_ARESULT != '\0')) {
      ovl_0a6e();
    }
  }
  return;
}


// ===== ovl_090d @ 1ca8:090d

void ovl_090d(void)

{
  char *pcVar1;
  undefined2 *puVar2;
  code *pcVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  int extraout_DX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar7;
  undefined1 uVar8;
  
  if (G_curatt < 6) {
    iVar6 = EXE_SearchInv(0x51,G_curatt,&G_invinfobuf);
    if (iVar6 != 1) {
      ovl_0434();
      return;
    }
    EXE_DecObj0(0x51,1);
  }
  ovl_0468();
  if (G_wpnt != 3) {
    G_zp_12 = G_rec1+1;
    ovl_0b2b();
    ovl_09df();
    ovl_034e();
  }
  if (G_wpnt != 3) {
    pcVar3 = INT_0x61_handler;
    (*pcVar3)();
  }
  ovl_1144();
  ovl_049a();
  if (G_wpnt != 3) {
    ovl_09e8();
    ovl_034e();
  }
  if (G_curtar != 0x18) {
    ovl_1033();
  }
  if (G_ARESULT == -1) {
    ovl_0419();
    ovl_040a();
  }
  ovl_034e();
  bVar4 = G_ARESULT;
  if (((bVar4 == 0) || (bVar4 == 3)) || (bVar7 = bVar4 < 4, bVar4 == 4)) {
    puVar2 = (undefined2 *)(G_savebx + 0x5c);
    EXE_ClrTxtWnd();
    goto L_08af;
  }
  ovl_14b2();
  if (bVar7) {
    ovl_0adb();
    return;
  }
  uVar8 = G_curatt < 6;
  if ((int)G_curatt < 6) {
    EXE_SkillUp();
    uVar8 = G_rec1+15 != -1;
    if ((G_rec1+15 != -1) && (ovl_0a63(), !(bool)uVar8)) {
      uVar8 = 0;
      if (G_ATTWEAPPTR != 0) {
        uVar5 = *(byte *)(G_ATTWEAPPTR + 0x28) & 0xff7f;
        bVar4 = (byte)uVar5;
        iVar6 = in_BX;
        if (bVar4 < 0x5a) {
          uVar8 = bVar4 < 0x19;
          if (0x18 < bVar4) {
            bVar4 = ovl_04af();
            uVar8 = (byte)(uVar5 >> 1) < bVar4;
            iVar6 = in_BX;
            if (!(bool)uVar8) goto L_07e0;
          }
        }
        else {
L_07e0:
          *(undefined1 *)(G_ATTWEAPPTR + 0x28) = 0xe2;
          G_suppresstext = 1;
          EXE_Sheathe();
          G_suppresstext = 0;
          ovl_0486();
          uVar8 = G_cursorx < G_txtww;
          if (!(bool)uVar8) {
            EXE_MyRet();
            EXE_MyRet();
          }
          in_BX = G_UserDelay;
          EXE_AutoPause();
        }
      }
    }
  }
  ovl_14b2();
  if ((bool)uVar8) {
    ovl_0adb();
    return;
  }
  ovl_0bc2();
  G_rec2+5 = G_rec2+5 & 0xfe;
  if (G_ARESULT == -1) {
    G_rec2 = 0x80;
    G_rec2+5 = G_rec2+5 & 2;
    G_rec2+5 = G_rec2+5 | 0x80;
    G_rec2+13 = 0;
    G_rec2+30 = G_GLOBEHIT;
    EXE_FirsTil();
    *(undefined1 *)(G_curtar + &G_pltilno) =
         *(undefined1 *)(extraout_DX + 5);
    if (G_rec2+3 == '\x1e') {
      pcVar3 = INT_0x61_handler;
      (*pcVar3)();
      goto L_08af;
    }
    if (G_curtar < 6) {
      G_rec2+4 = 0;
      ovl_09d1();
    }
  }
  ovl_02a3();
  ovl_030b();
  ovl_01a6();
  ovl_034e();
L_08af:
  if (G_ARESULT == -1) {
    ovl_0adb();
  }
  if ((G_swcast == '\0') && (G_curatt < 6)) {
    iVar6 = G_ATTHEROPTR;
    pcVar1 = (char *)(iVar6 + 0xba);
    *pcVar1 = *pcVar1 + -2;
    if (*pcVar1 < '\0') {
      *(undefined1 *)(iVar6 + 0xba) = 0;
    }
    puVar2 = (undefined2 *)(G_savebx + 0xd4);
    EXE_IsHeTr();
    ovl_02e2();
    if ((G_ARESULT != '\x04') && (G_ARESULT != '\0')) {
      ovl_0a6e();
    }
  }
  return;
}


// ===== ovl_09ac @ 1ca8:09ac

void ovl_09ac(void)

{
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_ChkRng(G_zp_1415 & 0xff,G_zp_1415 >> 8,1,0);
  return;
}


// ===== ovl_09c8 @ 1ca8:09c8

void ovl_09c8(void)

{
  ovl_0103();
  ovl_0828();
  return;
}


// ===== ovl_09d1 @ 1ca8:09d1

void ovl_09d1(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_09d6 @ 1ca8:09d6

void ovl_09d6(void)

{
  ovl_0103();
  ovl_09df();
  return;
}


// ===== ovl_09df @ 1ca8:09df

void ovl_09df(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_09e8 @ 1ca8:09e8

void ovl_09e8(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


// ===== ovl_09ed @ 1ca8:09ed

void ovl_09ed(void)

{
  undefined2 *puVar1;
  int iVar2;
  int unaff_SI;
  undefined2 *puVar3;
  undefined2 unaff_DS;
  
  G_curatt = G_curpla;
  ovl_0269();
  ovl_0a87();
  puVar3 = (undefined2 *)&G_JMPFLGS;
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    puVar1 = puVar3;
    puVar3 = puVar3 + 1;
    *puVar1 = 0;
  }
  return;
}


// ===== ovl_0a18 @ 1ca8:0a18

void ovl_0a18(void)

{
  ovl_0a2b();
  return;
}


// ===== ovl_0a1c @ 1ca8:0a1c

void ovl_0a1c(void)

{
  ovl_0a20();
  return;
}


// ===== ovl_0a20 @ 1ca8:0a20

void ovl_0a20(void)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  int in_BX;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  cVar1 = G_rec2+15;
  iVar4 = &G_rec2;
  ovl_0394(iVar4);
  cVar2 = *(char *)(iVar4 + &OV_0xb0d);
  uVar3 = CONCAT11(cVar1,cVar2);
  if (cVar2 == -1) {
    if (cVar1 == -1) {
      uVar3 = 0;
    }
    else {
      ovl_107f();
      uVar3 = (uint)*(byte *)(in_BX + 2);
    }
  }
  G_wpnt = uVar3 & 0xff;
  return;
}


// ===== ovl_0a2b @ 1ca8:0a2b

void ovl_0a2b(void)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  int in_BX;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  cVar1 = G_rec1+15;
  iVar4 = &G_rec1;
  ovl_0394(iVar4);
  cVar2 = *(char *)(iVar4 + &OV_0xb0d);
  uVar3 = CONCAT11(cVar1,cVar2);
  if (cVar2 == -1) {
    if (cVar1 == -1) {
      uVar3 = 0;
    }
    else {
      ovl_107f();
      uVar3 = (uint)*(byte *)(in_BX + 2);
    }
  }
  G_wpnt = uVar3 & 0xff;
  return;
}


// ===== ovl_0a63 @ 1ca8:0a63

void ovl_0a63(void)

{
  ovl_107f();
  return;
}


// ===== ovl_0a6e @ 1ca8:0a6e

void ovl_0a6e(void)

{
  int iVar1;
  int in_BX;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar3;
  int in_stack_00000000;
  
  LOCK();
  iVar1 = G_ATTWEAPPTR;
  G_ATTWEAPPTR = in_BX;
  UNLOCK();
  bVar3 = false;
  iVar2 = 0;
  if (iVar1 != 0) {
    ovl_0a63(iVar1);
    iVar2 = in_stack_00000000;
    if (!bVar3) {
      *(char *)(in_stack_00000000 + 0x28) = *(char *)(in_stack_00000000 + 0x28) + '\x01';
    }
  }
  LOCK();
  G_ATTWEAPPTR = iVar2;
  UNLOCK();
  return;
}


// ===== ovl_0a87 @ 1ca8:0a87

void ovl_0a87(void)

{
  int iVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = &G_villain;
  if (G_curatt < 6) {
    iVar1 = *(int *)(G_curatt * 2 + &G_heroptr);
  }
  G_ATTHEROPTR = iVar1;
  iVar2 = 0;
  if (*(char *)(iVar1 + 0xbf) != -1) {
    iVar2 = (uint)*(byte *)(iVar1 + 0xbf) + iVar1 + 0x2b;
  }
  G_ATTWEAPPTR = iVar2;
  return;
}


// ===== ovl_0abd @ 1ca8:0abd

void ovl_0abd(void)

{
  int iVar1;
  int unaff_SI;
  undefined2 unaff_DS;
  
  iVar1 = &G_villain;
  if (G_curtar < 6) {
    iVar1 = *(int *)(G_curtar * 2 + &G_heroptr);
  }
  G_TARHEROPTR = iVar1;
  return;
}


// ===== ovl_0adb @ 1ca8:0adb

void ovl_0adb(void)

{
  char in_AL;
  int iVar1;
  int iVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (G_rec1+7 == in_AL) {
    G_rec1+7 = 0xff;
  }
  if (G_rec2+7 == in_AL) {
    G_rec2+7 = 0xff;
  }
  iVar2 = G_crecptrs;
  iVar1 = 0x18;
  do {
    if (*(char *)(iVar2 + 7) == in_AL) {
      *(undefined1 *)(iVar2 + 7) = 0xff;
    }
    iVar2 = iVar2 + 0x21;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ===== ovl_0b2b @ 1ca8:0b2b

void ovl_0b2b(void)

{
  int iVar1;
  char cVar2;
  char cVar3;
  char *pcVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  cVar2 = G_zp_1415 - G_zp_12;
  cVar3 = G_zp_13 - G_zp_15;
  G_TILEXY = CONCAT11(cVar3,cVar2);
  G_DIRIDX = 0;
  if (cVar2 < '\0') {
    G_DIRIDX = G_DIRIDX | 8;
    G_TILEXY = -G_TILEXY;
  }
  if (cVar3 < '\0') {
    G_DIRIDX = G_DIRIDX | 4;
    G_TILEY = -G_TILEY;
  }
  if ((char)(G_TILEY + '\x02') <=
      (char)(G_TILEXY * '\x03')) {
    G_DIRIDX = G_DIRIDX | 2;
  }
  if ((char)(G_TILEY * '\x03') <=
      (char)(G_TILEXY + '\x01')) {
    G_DIRIDX = G_DIRIDX | 1;
  }
  iVar1 = *(int *)(&OV_0xc0b + G_DIRIDX + G_DIRIDX);
  G_CURDIR = iVar1;
  pcVar4 = (char *)(&OV_0x193 + iVar1);
  G_zp_10 =
       CONCAT11(pcVar4[8] + G_zp_13,*pcVar4 + G_zp_12);
  return;
}


// ===== ovl_0bc2 @ 1ca8:0bc2

void ovl_0bc2(void)

{
  int iVar1;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  EXE_SetTxtWnd(1);
  EXE_ClrTxtWnd();
  if (G_GLOBEHIT == '\x01') {
    ovl_04c0();
    ovl_0434();
    iVar1 = in_BX;
  }
  else {
    ovl_04c0();
    ovl_0486();
    ovl_0486();
    iVar1 = ovl_04bc();
    if ((uint)((iVar1 * 2 + G_cursorx) - G_txtwx) <
        G_txtww) {
      ovl_0486();
      iVar1 = in_BX;
      if (9 < (uint)((G_txtww + G_txtwx) -
                    G_cursorx)) {
        ovl_0486();
        iVar1 = G_HIT;
        EXE_PrtNum();
      }
    }
    else {
      G_cursorx = G_cursorx + -2;
      ovl_0486();
      iVar1 = in_BX;
    }
  }
  EXE_MyRet();
  ovl_0486();
  EXE_PrtNum();
  if (G_swcast == '\0') {
    if (G_SWNIFT == '\0') {
      G_deftxtparms+2 = G_rec2+16;
    }
    else {
      G_SWNIFT = 0;
      G_deftxtparms+2 = G_rec2+29;
    }
  }
  else {
    if (G_GLOBEHIT != '\0') goto L_0c9c;
    G_deftxtparms+2 = G_rec2+12;
  }
  ovl_0486();
L_0c9c:
  ovl_0486();
  EXE_PrtNum();
  if (G_ARESULT == '\x02') {
    EXE_MyRet();
    ovl_0486();
    if (G_rec2+3 != '$') {
      EXE_MyRet();
      ovl_0486();
    }
  }
  EXE_AutoPause();
  return;
}


// ===== ovl_0cde @ 1ca8:0cde

void ovl_0cde(void)

{
  byte *pbVar1;
  char *pcVar2;
  int *piVar3;
  undefined2 uVar4;
  int iVar5;
  char cVar6;
  byte bVar7;
  int iVar8;
  undefined1 extraout_AH;
  byte bVar9;
  byte bVar10;
  char *in_BX;
  char *pcVar11;
  uint uVar12;
  int unaff_SI;
  undefined2 unaff_DS;
  bool bVar13;
  
  if (G_curtar == 0x18) {
    if (G_swcast == '\0') {
      G_ARESULT = 4;
      return;
    }
    G_ARESULT = 1;
    return;
  }
  if ((G_rec2 & 0x80) != 0) {
    G_ARESULT = 3;
    return;
  }
  if (G_swcast != '\0') {
    G_ARESULT = 1;
    return;
  }
  bVar13 = false;
  if ((*(byte *)(G_ATTHEROPTR + 0xa5) & 0x10) == 0) {
    ovl_0fcf();
    if ((((!bVar13) && ((G_rec2 & 0x70) == 0)) &&
        (G_rec1+14 == '\0')) &&
       ((G_rec2+3 != ' ' && (G_timestop == '\0')))) {
      cVar6 = '\0';
      if (G_rec1+15 != -1) {
        ovl_107f();
        if (*(int *)(in_BX + 7) != 0) {
          pcVar11 = (char *)(*(int *)(in_BX + 7) + -1);
          do {
            pcVar11 = pcVar11 + 1;
            if (*pcVar11 == -1) goto L_0d87;
          } while (*pcVar11 != G_rec2+3);
          in_BX = (char *)G_savebx;
          goto L_0e0b;
        }
L_0d87:
        cVar6 = in_BX[5];
      }
      in_BX = (char *)G_savebx;
      bVar7 = ovl_04af();
      bVar9 = cVar6 + G_rec1+23;
      if (G_rec2+14 != '\0') {
        bVar9 = bVar9 >> 1;
      }
      bVar10 = bVar9 + 0x32 + G_rec2+20 * -8;
      if (((byte)(bVar9 + 0x32) < (byte)(G_rec2+20 * '\b') || bVar10 == 0) ||
         (bVar10 < bVar7)) {
        iVar8 = G_curtar;
        *(undefined1 *)(iVar8 + &G_JMPFLGS) = 1;
        uVar12 = iVar8 * 2;
        *(undefined2 *)(uVar12 + &G_SAVPXY) = G_rec2+1;
        ovl_0419(in_BX);
        uVar4 = G_zp_10;
        G_rec2+1 = uVar4;
        if (G_curtar < 6) {
          *(undefined1 *)((uVar12 >> 1) + &G_p1x) = (char)uVar4;
          *(undefined1 *)((uVar12 >> 1) + &G_p1y) = (char)((uint)uVar4 >> 8);
        }
        ovl_02a3();
        ovl_0479();
        G_ARESULT = 0;
        return;
      }
    }
  }
  else {
    pbVar1 = (byte *)(G_ATTHEROPTR + 0xa5);
    *pbVar1 = *pbVar1 & 0xef;
  }
L_0e0b:
  G_HIT = 0;
  G_DAM = 0;
  if ((byte)((char)G_wpnt - 1U) < 3) {
    ovl_107f();
    cVar6 = ((in_BX[4] + G_rec1+18) - *in_BX) * '\x02' + in_BX[1];
    iVar8 = CONCAT11(extraout_AH,cVar6);
    if ((G_rec2+3 == '$') && (G_rec1+15 == '\x10')) {
      iVar8 = CONCAT11(extraout_AH,cVar6 * '\x04');
    }
    in_BX = (char *)G_savebx;
    if (G_wpnt != 3) goto L_0e5f;
    G_HIT = iVar8;
  }
  else {
    iVar8 = CONCAT11((char)((uint)G_wpnt >> 8),
                     G_rec1+18);
L_0e5f:
    G_HIT = iVar8;
    if ((G_curatt < 6) &&
       ((*(byte *)(G_ATTHEROPTR + 0xa5) & 0x20) != 0)) {
      pbVar1 = (byte *)(G_ATTHEROPTR + 0xa5);
      *pbVar1 = *pbVar1 & 0xdf;
      G_HIT = G_HIT + iVar8 * 2;
    }
  }
  if ((G_curtar < 6) && (G_rec2+29 != '\0')) {
    pcVar2 = (char *)&G_rec2+29;
    cVar6 = *pcVar2;
    *pcVar2 = *pcVar2 + -1;
    if (SBORROW1(cVar6,'\x01') == *pcVar2 < '\0') {
      G_DAM = 0;
      G_SWNIFT = 1;
      if (G_rec2+29 < '\x01') {
        pbVar1 = (byte *)(G_TARHEROPTR + 0xa5);
        *pbVar1 = *pbVar1 & 0xbf;
      }
      goto SUB_1ca8_0ed8;
    }
  }
  G_SWNIFT = 0;
  bVar7 = (byte)G_HIT;
  if (G_rec2+16 < bVar7) {
    G_DAM =
         CONCAT11((char)((uint)G_HIT >> 8),
                  bVar7 - G_rec2+16);
  }
  else {
    G_DAM = 0;
  }
SUB_1ca8_0ed8:
  iVar5 = G_DAM;
  piVar3 = (int *)&G_rec2+10;
  iVar8 = *piVar3;
  *piVar3 = *piVar3 - iVar5;
  if (*piVar3 == 0 || SBORROW2(iVar8,iVar5) != *piVar3 < 0) {
    G_ARESULT = 0xff;
    G_rec2+10 = 0;
    G_rec2+5 = G_rec2+5 | 0x80;
    if ((G_rec2+4 != '\0') && ((G_rec2+5 & 4) != 0)) {
      G_rec2+5 = G_rec2+5 & 0xfb;
      G_crossovlycall = *(int *)(in_BX + 0x14c) + 6;
      G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14e);
      EXE_crossovlycall();
    }
    return;
  }
  G_ARESULT = 1;
  if ((((G_swcast != '\0') || ((G_rec2 & 1) != 0)) ||
      (G_rec2+3 == '\x1c')) ||
     ((G_DAM == 0 ||
      (bVar7 = ovl_04af(),
      (byte)((G_rec1+23 >> 3) + G_rec1+19) <= bVar7)))) {
    return;
  }
  G_ARESULT = G_ARESULT + '\x01';
  G_rec2 = G_rec2 | 1;
  G_rec2+20 = 0;
  G_rec2+19 = 0;
  G_rec2+30 = 1;
  if (G_curtar < 6) {
    iVar8 = G_TARHEROPTR;
    pbVar1 = (byte *)(iVar8 + 0xbd);
    *pbVar1 = *pbVar1 | 1;
    (**(code **)(in_BX + 0xd4))(iVar8);
  }
  return;
}


// ===== ovl_0fa0 @ 1ca8:0fa0

void ovl_0fa0(void)

{
  ovl_0103();
  ovl_0fa9();
  return;
}


// ===== ovl_0fa9 @ 1ca8:0fa9

void ovl_0fa9(void)

{
  int *piVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  uint in_AX;
  int in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  
  G_HIT = in_AX;
  bVar5 = G_rec2+12;
  if (in_AX < bVar5) {
    bVar5 = (byte)G_HIT;
    G_DAM = 0;
  }
  else {
    G_DAM = in_AX - bVar5;
  }
  G_rec2+12 = G_rec2+12 - bVar5;
  iVar4 = G_DAM;
  piVar1 = (int *)&G_rec2+10;
  iVar3 = *piVar1;
  *piVar1 = *piVar1 - iVar4;
  if (*piVar1 == 0 || SBORROW2(iVar3,iVar4) != *piVar1 < 0) {
    G_ARESULT = 0xff;
    G_rec2+10 = 0;
    G_rec2+5 = G_rec2+5 | 0x80;
    if ((G_rec2+4 != '\0') && ((G_rec2+5 & 4) != 0)) {
      G_rec2+5 = G_rec2+5 & 0xfb;
      G_crossovlycall = *(int *)(in_BX + 0x14c) + 6;
      G_crossovlycall+2 = *(undefined2 *)(in_BX + 0x14e);
      EXE_crossovlycall();
    }
    return;
  }
  G_ARESULT = 1;
  if ((((G_swcast != '\0') || ((G_rec2 & 1) != 0)) ||
      (G_rec2+3 == '\x1c')) ||
     ((G_DAM == 0 ||
      (bVar5 = ovl_04af(),
      (byte)((G_rec1+23 >> 3) + G_rec1+19) <= bVar5)))) {
    return;
  }
  G_ARESULT = G_ARESULT + '\x01';
  G_rec2 = G_rec2 | 1;
  G_rec2+20 = 0;
  G_rec2+19 = 0;
  G_rec2+30 = 1;
  if (G_curtar < 6) {
    iVar3 = G_TARHEROPTR;
    pbVar2 = (byte *)(iVar3 + 0xbd);
    *pbVar2 = *pbVar2 | 1;
    EXE_IsHeTr(iVar3);
  }
  return;
}


// ===== ovl_0fcf @ 1ca8:0fcf

void ovl_0fcf(void)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  G_DODGEADJ = 1;
  do {
    G_zp_1415 = G_rec2+1;
    iVar3 = (G_CURDIR & 0x7f) * 2 + G_DODGEADJ;
    iVar4 = CONCAT11((char)((uint)iVar3 >> 8),*(undefined1 *)(iVar3 + G_loc+20));
    cVar2 = *(char *)(iVar4 + &OV_0x19b);
    G_zp_1415 =
         G_zp_1415 + *(char *)(iVar4 + &OV_0x193);
    G_zp_15 = G_zp_15 + cVar2;
    iVar3 = ovl_03d5();
    if (iVar3 == 1) {
      ovl_041e();
      if (*(char *)(iVar4 + &G_globemap) == '\0') {
        G_zp_10 = G_zp_1415;
        return;
      }
    }
    piVar1 = (int *)&G_DODGEADJ;
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
  } while (SBORROW2(iVar3,1) == *piVar1 < 0);
  return;
}


// ===== ovl_1033 @ 1ca8:1033

void ovl_1033(undefined2 param_1,undefined2 param_2)

{
  bool bVar1;
  uint uVar2;
  int unaff_SI;
  undefined2 unaff_DS;
  
  ovl_02a3();
  uVar2 = 0x17;
  do {
    if (*(char *)(uVar2 + &G_JMPFLGS) == '\x01') {
      *(undefined1 *)(uVar2 + &G_JMPFLGS) = 0;
      ovl_025f();
      ovl_0419();
      uVar2 = uVar2 * 2;
      G_rec2+1 = *(undefined2 *)(uVar2 + &G_SAVPXY);
      ovl_02a3();
      uVar2 = uVar2 >> 1;
      if (uVar2 < 6) {
        *(undefined1 *)(uVar2 + &G_p1x) = (char)param_2;
        *(undefined1 *)(uVar2 + &G_p1y) = (char)((uint)param_2 >> 8);
      }
      param_2 = 0xdaf3;
      ovl_01a6();
    }
    bVar1 = 0 < (int)uVar2;
    uVar2 = uVar2 - 1;
  } while (bVar1);
  ovl_025f();
  return;
}


// ===== ovl_107f @ 1ca8:107f

undefined4 ovl_107f(void)

{
  undefined2 in_AX;
  
  return CONCAT22((int)((ulong)CONCAT11((char)((uint)in_AX >> 8),(char)in_AX + -9) * 9 >> 0x10),
                  in_AX);
}


// ===== ovl_1093 @ 1ca8:1093

void ovl_1093(void)

{
  int unaff_DI;
  
  OV_0x123b = 1;
  OV_0x123c = 0;
  OV_0x1240 = 0;
  return;
}


// ===== ovl_10a7 @ 1ca8:10a7

void ovl_10a7(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  OV_0x123b = 1;
  OV_0x123c = 0;
  OV_0x1240 = 0;
  iVar4 = G_crecptrs;
  iVar3 = 0x18;
  uVar2 = (uint)G_rec1+4;
  do {
    *(undefined1 *)(iVar3 + &G_pathblk+1) = 1;
    cVar1 = (char)uVar2;
    uVar2 = CONCAT11(*(char *)(iVar4 + 4),cVar1);
    if (((cVar1 != *(char *)(iVar4 + 4)) && ((*(byte *)(iVar4 + 5) & 0x98) == 0)) &&
       (*(char *)(iVar4 + 0xe) == '\0')) {
      ovl_025f(iVar3);
      G_zp_1415 = G_rec2+1;
      iVar3 = -0x247f;
      ovl_114d();
      OV_0x1240 = OV_0x1240 + 1;
      *(undefined1 *)(iVar3 + &G_pathblk+1) = (char)G_pathblk;
    }
    iVar4 = iVar4 + 0x21;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar4 = G_savebx;
  EXE_GameSound(2);
  EXE_MultiBang(3,iVar4);
  return;
}


// ===== ovl_1144 @ 1ca8:1144

void ovl_1144(void)

{
  char *pcVar1;
  byte *pbVar2;
  undefined2 uVar3;
  code *pcVar4;
  char cVar5;
  undefined2 in_AX;
  char cVar7;
  char extraout_AH;
  int iVar6;
  byte extraout_DL;
  byte extraout_DL_00;
  byte bVar8;
  byte extraout_DL_01;
  byte extraout_DH;
  byte bVar9;
  byte extraout_DH_00;
  byte extraout_DH_01;
  uint uVar10;
  int iVar11;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar12;
  
  OV_0x123b = 0;
  OV_0x1242 = 0;
  G_pathblk = 0;
  G_MISLTYPE = in_AX;
  G_zp_12 = G_rec1+1;
  ovl_0b2b();
  ovl_143f();
  cVar7 = G_zp_1415;
  cVar5 = cVar7 - G_zp_12;
  bVar12 = cVar7 < G_zp_12;
  if (bVar12) {
    cVar5 = -cVar5;
  }
  uVar10 = (uint)bVar12;
  cVar7 = G_zp_15 - G_zp_13;
  if (G_zp_15 < G_zp_13) {
    uVar10 = uVar10 + 2;
    cVar7 = -cVar7;
  }
  bVar8 = *(byte *)(uVar10 + &OV_0x1233);
  bVar9 = *(byte *)(uVar10 + &OV_0x1237);
  G_TILEXY = G_zp_12;
  iVar11 = 0;
  G_GRESH = cVar5;
  pcVar1 = (char *)&G_GRESH;
  cVar5 = *pcVar1;
  *pcVar1 = *pcVar1 - cVar7;
  if (SBORROW1(cVar5,cVar7) != *pcVar1 < '\0') goto L_11c5;
  G_GRESH = G_GRESH >> 1;
  while( true ) {
    pbVar2 = (byte *)&G_TILEXY;
    bVar12 = CARRY1(*pbVar2,bVar8);
    *pbVar2 = *pbVar2 + bVar8;
    *(undefined1 *)(iVar11 + &G_PATH) = 1;
    iVar11 = iVar11 + 1;
    ovl_137a();
    bVar8 = extraout_DL;
    bVar9 = extraout_DH;
    if (bVar12) break;
    pcVar1 = (char *)&G_GRESH;
    cVar7 = *pcVar1;
    *pcVar1 = *pcVar1 - extraout_AH;
    if (SBORROW1(cVar7,extraout_AH) != *pcVar1 < '\0') {
L_11c5:
      do {
        pbVar2 = (byte *)&G_TILEY;
        bVar12 = CARRY1(*pbVar2,bVar9);
        *pbVar2 = *pbVar2 + bVar9;
        *(undefined1 *)(iVar11 + &G_PATH) = 2;
        iVar11 = iVar11 + 1;
        cVar7 = ovl_137a();
        bVar8 = extraout_DL_00;
        bVar9 = extraout_DH_00;
        if (bVar12) goto L_11dc;
        pcVar1 = (char *)&G_GRESH;
        cVar5 = *pcVar1;
        *pcVar1 = *pcVar1 + cVar7;
      } while (SCARRY1(cVar5,cVar7) != *pcVar1 < '\0');
    }
  }
L_11dc:
  *(undefined2 *)(iVar11 + &G_MISLTYPE+1) = 0;
  OV_0x123e = 0x1f - OV_0x1240;
  uVar3 = G_zp_12;
  G_TILEXY = uVar3;
  G_MISLXY = uVar3;
  G_FIRSTPLT = 1;
  G_SWDIAG = 0;
  iVar11 = 0;
  while ((G_zp_1415 != G_TILEXY ||
         ((G_MISLTYPE != -1 &&
          ((ovl_0cde(), G_ARESULT == '\0' ||
           (G_ARESULT == '\x04'))))))) {
    if (OV_0x123b == '\x01') {
      if (G_SWDIAG != 1) {
        if (G_FIRSTPLT == '\x01') {
          G_FIRSTPLT = 0;
        }
        uVar10 = G_TILEXY;
        LOCK();
        iVar6 = OV_0x123c;
        OV_0x123c = iVar11;
        UNLOCK();
        *(uint *)(iVar6 + &G_bangx) = uVar10 & 0xff;
        *(uint *)(iVar6 + &G_bangy) = uVar10 >> 8;
        *(undefined2 *)(iVar6 + &G_bangstg) = OV_0x123e;
        OV_0x123e = OV_0x123e + -1;
        LOCK();
        iVar11 = OV_0x123c;
        OV_0x123c = iVar6 + 2;
        UNLOCK();
        if ((OV_0x1242 != 1) && (iVar6 = ovl_132a(), iVar6 == 1)) {
          *(undefined1 *)(iVar11 + &G_PATH) = 0;
        }
      }
    }
    else {
      ovl_138c();
      bVar8 = extraout_DL_01;
      bVar9 = extraout_DH_01;
    }
    uVar10 = *(uint *)(iVar11 + &G_PATH);
    if ((char)uVar10 == '\0') break;
    if ((uVar10 & 1) != 0) {
      G_TILEXY = G_TILEXY + bVar8;
    }
    if ((uVar10 & 2) != 0) {
      G_TILEY = G_TILEY + bVar9;
    }
    iVar11 = iVar11 + 1;
    if ((G_SWDIAG == '\x01') || ((char)uVar10 == (char)(uVar10 >> 8))) {
      G_SWDIAG = 0;
    }
    else {
      G_SWDIAG = 1;
    }
  }
  G_SWDIAG = 0;
  if (OV_0x123b == '\x01') {
    uVar10 = G_TILEXY;
    LOCK();
    iVar6 = OV_0x123c;
    OV_0x123c = iVar11;
    UNLOCK();
    *(uint *)(iVar6 + &G_bangx) = uVar10 & 0xff;
    *(uint *)(iVar6 + &G_bangy) = uVar10 >> 8;
    *(int *)(iVar6 + &G_bangstg) = OV_0x123e + -0x1f;
    OV_0x123c = iVar6 + 2;
  }
  else if (G_MISLTYPE != -1) {
    ovl_138c();
    ovl_01a6();
  }
  if (G_MISLTYPE == 8) {
    pcVar4 = INT_0x61_handler;
    (*pcVar4)();
  }
  return;
}


// ===== ovl_114d @ 1ca8:114d

void ovl_114d(void)

{
  char *pcVar1;
  byte *pbVar2;
  undefined2 uVar3;
  code *pcVar4;
  char cVar5;
  undefined2 in_AX;
  char cVar7;
  char extraout_AH;
  int iVar6;
  byte extraout_DL;
  byte extraout_DL_00;
  byte bVar8;
  byte extraout_DL_01;
  undefined2 in_DX;
  byte extraout_DH;
  byte bVar9;
  byte extraout_DH_00;
  byte extraout_DH_01;
  uint uVar10;
  int iVar11;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  bool bVar12;
  
  OV_0x1242 = in_DX;
  G_pathblk = 0;
  G_MISLTYPE = in_AX;
  G_zp_12 = G_rec1+1;
  ovl_0b2b();
  ovl_143f();
  cVar7 = G_zp_1415;
  cVar5 = cVar7 - G_zp_12;
  bVar12 = cVar7 < G_zp_12;
  if (bVar12) {
    cVar5 = -cVar5;
  }
  uVar10 = (uint)bVar12;
  cVar7 = G_zp_15 - G_zp_13;
  if (G_zp_15 < G_zp_13) {
    uVar10 = uVar10 + 2;
    cVar7 = -cVar7;
  }
  bVar8 = *(byte *)(uVar10 + &OV_0x1233);
  bVar9 = *(byte *)(uVar10 + &OV_0x1237);
  G_TILEXY = G_zp_12;
  iVar11 = 0;
  G_GRESH = cVar5;
  pcVar1 = (char *)&G_GRESH;
  cVar5 = *pcVar1;
  *pcVar1 = *pcVar1 - cVar7;
  if (SBORROW1(cVar5,cVar7) != *pcVar1 < '\0') goto L_11c5;
  G_GRESH = G_GRESH >> 1;
  while( true ) {
    pbVar2 = (byte *)&G_TILEXY;
    bVar12 = CARRY1(*pbVar2,bVar8);
    *pbVar2 = *pbVar2 + bVar8;
    *(undefined1 *)(iVar11 + &G_PATH) = 1;
    iVar11 = iVar11 + 1;
    ovl_137a();
    bVar8 = extraout_DL;
    bVar9 = extraout_DH;
    if (bVar12) break;
    pcVar1 = (char *)&G_GRESH;
    cVar7 = *pcVar1;
    *pcVar1 = *pcVar1 - extraout_AH;
    if (SBORROW1(cVar7,extraout_AH) != *pcVar1 < '\0') {
L_11c5:
      do {
        pbVar2 = (byte *)&G_TILEY;
        bVar12 = CARRY1(*pbVar2,bVar9);
        *pbVar2 = *pbVar2 + bVar9;
        *(undefined1 *)(iVar11 + &G_PATH) = 2;
        iVar11 = iVar11 + 1;
        cVar7 = ovl_137a();
        bVar8 = extraout_DL_00;
        bVar9 = extraout_DH_00;
        if (bVar12) goto L_11dc;
        pcVar1 = (char *)&G_GRESH;
        cVar5 = *pcVar1;
        *pcVar1 = *pcVar1 + cVar7;
      } while (SCARRY1(cVar5,cVar7) != *pcVar1 < '\0');
    }
  }
L_11dc:
  *(undefined2 *)(iVar11 + &G_MISLTYPE+1) = 0;
  OV_0x123e = 0x1f - OV_0x1240;
  uVar3 = G_zp_12;
  G_TILEXY = uVar3;
  G_MISLXY = uVar3;
  G_FIRSTPLT = 1;
  G_SWDIAG = 0;
  iVar11 = 0;
  while ((G_zp_1415 != G_TILEXY ||
         ((G_MISLTYPE != -1 &&
          ((ovl_0cde(), G_ARESULT == '\0' ||
           (G_ARESULT == '\x04'))))))) {
    if (OV_0x123b == '\x01') {
      if (G_SWDIAG != 1) {
        if (G_FIRSTPLT == '\x01') {
          G_FIRSTPLT = 0;
        }
        uVar10 = G_TILEXY;
        LOCK();
        iVar6 = OV_0x123c;
        OV_0x123c = iVar11;
        UNLOCK();
        *(uint *)(iVar6 + &G_bangx) = uVar10 & 0xff;
        *(uint *)(iVar6 + &G_bangy) = uVar10 >> 8;
        *(undefined2 *)(iVar6 + &G_bangstg) = OV_0x123e;
        OV_0x123e = OV_0x123e + -1;
        LOCK();
        iVar11 = OV_0x123c;
        OV_0x123c = iVar6 + 2;
        UNLOCK();
        if ((OV_0x1242 != 1) && (iVar6 = ovl_132a(), iVar6 == 1)) {
          *(undefined1 *)(iVar11 + &G_PATH) = 0;
        }
      }
    }
    else {
      ovl_138c();
      bVar8 = extraout_DL_01;
      bVar9 = extraout_DH_01;
    }
    uVar10 = *(uint *)(iVar11 + &G_PATH);
    if ((char)uVar10 == '\0') break;
    if ((uVar10 & 1) != 0) {
      G_TILEXY = G_TILEXY + bVar8;
    }
    if ((uVar10 & 2) != 0) {
      G_TILEY = G_TILEY + bVar9;
    }
    iVar11 = iVar11 + 1;
    if ((G_SWDIAG == '\x01') || ((char)uVar10 == (char)(uVar10 >> 8))) {
      G_SWDIAG = 0;
    }
    else {
      G_SWDIAG = 1;
    }
  }
  G_SWDIAG = 0;
  if (OV_0x123b == '\x01') {
    uVar10 = G_TILEXY;
    LOCK();
    iVar6 = OV_0x123c;
    OV_0x123c = iVar11;
    UNLOCK();
    *(uint *)(iVar6 + &G_bangx) = uVar10 & 0xff;
    *(uint *)(iVar6 + &G_bangy) = uVar10 >> 8;
    *(int *)(iVar6 + &G_bangstg) = OV_0x123e + -0x1f;
    OV_0x123c = iVar6 + 2;
  }
  else if (G_MISLTYPE != -1) {
    ovl_138c();
    ovl_01a6();
  }
  if (G_MISLTYPE == 8) {
    pcVar4 = INT_0x61_handler;
    (*pcVar4)();
  }
  return;
}


// ===== ovl_132a @ 1ca8:132a

undefined2 ovl_132a(void)

{
  undefined2 *puVar1;
  char cVar2;
  char *pcVar3;
  int unaff_SI;
  undefined2 unaff_DS;
  
  puVar1 = (undefined2 *)(G_savebx + 0xf4);
  cVar2 = EXE_Locate(G_TILEXY & 0xff,
                             G_TILEXY >> 8,G_savebx);
  pcVar3 = (char *)G_tdata+4;
  G_pathblk = 1;
  for (; *pcVar3 != -1; pcVar3 = pcVar3 + 1) {
    if (*pcVar3 == cVar2) {
      G_pathblk = 0;
      goto L_1374;
    }
  }
  do {
    if (*pcVar3 == -1) {
L_1374:
      return G_pathblk;
    }
    if (*pcVar3 == cVar2) {
      G_pathblk = 0;
      goto L_1374;
    }
    pcVar3 = pcVar3 + 1;
  } while( true );
}


// ===== ovl_137a @ 1ca8:137a

void ovl_137a(void)

{
  int unaff_SI;
  undefined2 unaff_DS;
  
  if (((byte)G_TILEXY < 0xb) &&
     ((byte)((uint)G_TILEXY >> 8) < 9)) {
    return;
  }
  return;
}


// ===== ovl_138c @ 1ca8:138c

void ovl_138c(void)

{
  undefined2 *puVar1;
  undefined2 in_BX;
  int unaff_SI;
  undefined2 unaff_DS;
  undefined4 uVar2;
  int in_stack_00000000;
  undefined2 uVar3;
  
  if (G_SWDIAG == 1) {
    return;
  }
  uVar3 = in_BX;
  ovl_132a();
  if (G_MISLTYPE != -1) {
    if ((G_FIRSTPLT != '\x01') && (G_MISLTYPE != 8)) {
      ovl_01a6(G_TILEXY);
      G_TILEXY = uVar3;
      ovl_1482();
    }
    if (G_MISLTYPE == 8) {
      puVar1 = (undefined2 *)(G_savebx + 0x50);
      EXE_PageFlip(in_BX,G_MISLTILE);
      G_egadrawcode = 0;
      G_egaeffectstimer = 1000;
      G_egaeffectsflag = 3;
      uVar2 = ovl_142f();
      puVar1 = (undefined2 *)(G_savebx + 0x2f8);
      EXE_movectileFX((int)((ulong)uVar2 >> 0x10),(uint)uVar2 & 0xff,(uint)uVar2 >> 8,
                         in_BX);
    }
    else {
      ovl_042f();
      ovl_034e();
    }
  }
  G_MISLXY = G_TILEXY;
  G_FIRSTPLT = 0;
  if (G_pathblk == 1) {
    *(undefined1 *)(in_stack_00000000 + &G_PATH) = 0;
    G_ARESULT = 0;
  }
  return;
}


// ===== ovl_142f @ 1ca8:142f

undefined2 ovl_142f(void)

{
  char in_AL;
  char in_AH;
  
  return CONCAT11(in_AH * '\x10' + '\b',in_AL * '\x04' + '\x04');
}


// ===== ovl_143f @ 1ca8:143f

void ovl_143f(void)

{
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (G_MISLTYPE == 0) {
    G_MISLTILE =
         (uint)*(byte *)(&G_weaptiles+28 +
                        *(int *)(G_CURDIR * 2 + &OV_0x1a3));
    return;
  }
  G_MISLTILE = (uint)*(byte *)(G_MISLTYPE + &OV_0x1579);
  return;
}


// ===== ovl_1482 @ 1ca8:1482

undefined2 ovl_1482(void)

{
  char cVar1;
  undefined2 in_AX;
  int unaff_SI;
  int unaff_DI;
  undefined2 unaff_DS;
  
  if (('\0' < G_MISLTYPE) && (G_MISLTYPE < '\x05')) {
    cVar1 = *(char *)((uint)G_MISLTYPE + &OV_0x1579);
    G_MISLTILE = G_MISLTILE + '\x01';
    if ((byte)(cVar1 + 2U) < G_MISLTILE) {
      G_MISLTILE = cVar1;
    }
  }
  return in_AX;
}


// ===== ovl_14b2 @ 1ca8:14b2

void ovl_14b2(void)

{
  code *pcVar1;
  
  pcVar1 = INT_0x61_handler;
  (*pcVar1)();
  return;
}


